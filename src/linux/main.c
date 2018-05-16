#define _GNU_SOURCE
#include <sys/mman.h>
#include "lib_loader.c"
#include "../app/r_app.h"

long
get_file_creation(char* file_name) {
  struct stat st;
  stat(file_name, &st);
  return (long)st.st_ctime;
}

long
milliseconds_elapsed(Timespan start, Timespan end) {
  return (long)(1000.0 * (end.time - start.time) +
                (end.millitm - start.millitm));
}

void
spin(u32 milliseconds) {
  Timespan start, end;
  ftime(&start);
  ftime(&end);
  while (milliseconds_elapsed(start, end) < milliseconds) {
    ftime(&end);
  }
}

#define APP_LIB_NAME "libr_app.so"
#define TMP_APP_LIB_NAME "tmp_libr_app.so"

void
load_app_code(App_Code* code) {
  code->create =
      (App_State * (*)(App_Memory*)) fn(code->lib_handle, "app_create");
  code->init = (void (*)(App_State*))fn(code->lib_handle, "app_init");
  code->load = (void (*)(App_State*))fn(code->lib_handle, "app_load");
  code->input = (void (*)(App_State*))fn(code->lib_handle, "app_input");
  code->update = (void (*)(App_State*))fn(code->lib_handle, "app_update");
  code->render = (void (*)(App_State*))fn(code->lib_handle, "app_render");
  code->unload = (void (*)(App_State*))fn(code->lib_handle, "app_unload");
  code->destroy = (void (*)(App_State*))fn(code->lib_handle, "app_destroy");
}

App_Code
load_app() {
  App_Code code = {};
  code.lib_handle = load_lib(APP_LIB_NAME);
  load_app_code(&code);
  return code;
}

void
reload_app(App_Code* code) {
  code->lib_handle =
      reload_lib(code->lib_handle, APP_LIB_NAME, TMP_APP_LIB_NAME);
  load_app_code(code);
}

App_Memory
allocate_memory() {

#if _DEBUG
  void* base_addr = (void*)terabytes(1);
#else
  void* base_addr = 0;
#endif

  App_Memory memory;
  memory.permanent_size = megabytes(64);
  memory.transient_size = megabytes(512);

  u64 total_memory_size = memory.permanent_size + memory.transient_size;

  memory.permanent_addr = mmap(base_addr,
                               total_memory_size,
                               PROT_NONE,
                               MAP_PRIVATE | MAP_ANONYMOUS,
                               -1,
                               0);
  memory.transient_addr =
      (void*)(memory.permanent_addr + memory.permanent_size);

  u32 res = mprotect(
      memory.permanent_addr, total_memory_size, PROT_READ | PROT_WRITE);

  // note: (filipe)
  // if mprotect() fails we could not allocate all memory necessary and we
  // should quit

  assert(res == 0);
  return memory;
}

int
main(int argc, char** args) {
  App_Code app = load_app();
  App_Memory memory = allocate_memory();
  App_State* state = app.create(&memory);

  // note: (filipe)
  // window must be created in the main or else it would be lost when reloading
  window_create(state->window);

  app.init(state);
  app.load(state);

  i64 last_modified = 0;
  bool should_reload = false;

  while (state->running) {
    if (should_reload) {

      app.unload(state);
      spin(100);
      reload_app(&app);
      app.load(state);

      should_reload = false;
    }

    if (get_file_creation(APP_LIB_NAME) > last_modified) {
      last_modified = get_file_creation(APP_LIB_NAME);
      should_reload = true;
    }

    app.input(state);
    app.update(state);
    app.render(state);
  }

  // todo: (filipe)
  // should we not manually release our memory?
  // munmap(memory.permanent_storage_addr, memory.permanent_storage_size);
  app.unload(state);
  app.destroy(state);

  return 0;
}