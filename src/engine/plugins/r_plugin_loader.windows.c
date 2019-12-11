#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"
#include "engine/io/r_file.h"

void //
get_temp_file_name(const char* file_name, char* tmp_file_name) {
  char tmp_path[SHORT_STRING_LENGTH] = {0};
  char name[SHORT_STRING_LENGTH] = {0};

  GetTempPathA(SHORT_STRING_LENGTH, tmp_path);
  sprintf(name, "%s", PathFindFileNameA(file_name));
  sprintf(tmp_file_name, "%s%s", tmp_path, name);
}

void
get_pdb_file_name(const char* file_name, char* pdb_file_name) {
  sprintf(pdb_file_name, "%s", file_name);
  PathRemoveExtensionA(pdb_file_name);
  sprintf(pdb_file_name, "%s.*.pdb", pdb_file_name);

  WIN32_FIND_DATAA ffd;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  hFind = FindFirstFileA(pdb_file_name, &ffd);
  FindClose(hFind);
  PathRemoveFileSpecA(pdb_file_name);
  sprintf(pdb_file_name, "%s\\%s", pdb_file_name, ffd.cFileName);
}

r_plugin_t* //
r_plugin_loader_load_plugin(r_memory_t* memory, r_plugin_t* plugins, const char* file_name) {

  char tmp_dll_file_name[SHORT_STRING_LENGTH] = {0};
  char tmp_pdb_file_name[SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[SHORT_STRING_LENGTH] = {0};

  get_temp_file_name(file_name, tmp_dll_file_name);
  get_pdb_file_name(file_name, pdb_file_name);
  get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  if (CopyFileA(file_name, tmp_dll_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);
    HMODULE plugin_handle = LoadLibraryA(tmp_dll_file_name);
    assert(plugin_handle != NULL);

    char plugin_name[SHORT_STRING_LENGTH - 4] = {0};

    sprintf(plugin_name, "%s", PathFindFileNameA(file_name));
    PathRemoveExtensionA(plugin_name);

    char load_fn_name[SHORT_STRING_LENGTH] = {"load_"};
    char get_size_fn_name[SHORT_STRING_LENGTH] = {"get_size_"};
    char get_id_fn_name[SHORT_STRING_LENGTH] = {"get_id_"};

    strcat(load_fn_name, plugin_name);
    strcat(get_size_fn_name, plugin_name);
    strcat(get_id_fn_name, plugin_name);

    R_PLUGIN_LOAD load_function = (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_handle, load_fn_name);

    R_PLUGIN_GET_SIZE get_size_function =
        (R_PLUGIN_GET_SIZE)r_plugin_loader_fn(plugin_handle, get_size_fn_name);

    R_PLUGIN_GET_ID get_id_function =
        (R_PLUGIN_GET_ID)r_plugin_loader_fn(plugin_handle, get_id_fn_name);

    u32 id = get_id_function();
    size_t memory_size = get_size_function();
    r_memory_arena_t* plugin_memory_arena = r_memory_add_arena(memory, memory_size);
    void* state_memory_addr = r_memory_arena_push(plugin_memory_arena, memory_size);

    r_plugin_load_info_t load_info = {0};
    load_info.fn = &r_plugin_loader_fn;
    load_info.handle = plugin_handle;
    load_info.plugin_memory_addr = (r_plugin_t*)&plugins[id - 256];
    load_info.state_memory_addr = state_memory_addr;

    r_plugin_t* plugin = load_function(&load_info);
    plugin->id = id;
    plugin->memory_arena = plugin_memory_arena;
    sprintf(plugin->name, "%s", plugin_name);
    sprintf(plugin->file_name, "%s", file_name);
    sprintf(plugin->tmp_file_name, "%s", tmp_dll_file_name);
    plugin->memory_size = memory_size;
    r_file_a_get_last_modification(plugin->file_name, &plugin->last_modification);
    return plugin;
  }
  return NULL;
}

void //
r_plugin_loader_destroy_plugin(r_plugin_t* plugin) {
  if (plugin->destroy)
    plugin->destroy(plugin->state);
  FreeLibrary(plugin->handle);
}

r_plugin_t* //
r_plugin_loader_reload_plugin(r_memory_t* memory, r_plugin_t* plugin) {

  while (!DeleteFileA(plugin->tmp_file_name))
    Sleep(1);

  char tmp_pdb_file_name[SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[SHORT_STRING_LENGTH] = {0};
  get_pdb_file_name(plugin->file_name, pdb_file_name);
  get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  while (CopyFileA(plugin->file_name, plugin->tmp_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);

    HMODULE plugin_handle = LoadLibraryA(plugin->tmp_file_name);
    assert(plugin_handle != NULL);

    char load_fn_name[SHORT_STRING_LENGTH] = {"load_"};
    char get_size_fn_name[SHORT_STRING_LENGTH] = {"get_size_"};

    strcat(load_fn_name, plugin->name);
    strcat(get_size_fn_name, plugin->name);

    R_PLUGIN_LOAD load_function = //
        (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_handle, load_fn_name);

    R_PLUGIN_GET_SIZE get_size_function = //
        (R_PLUGIN_GET_SIZE)r_plugin_loader_fn(plugin_handle, get_size_fn_name);

    r_plugin_load_info_t load_info = {0};
    load_info.fn = &r_plugin_loader_fn;
    load_info.handle = plugin_handle;
    load_info.plugin_memory_addr = plugin;
    load_info.state_memory_addr = plugin->state;

    r_plugin_t* new_plugin = load_function(&load_info);
    r_file_a_get_last_modification(new_plugin->file_name, &new_plugin->last_modification);
    new_plugin->memory_size = get_size_function();
    new_plugin->memory_arena = plugin->memory_arena;

    return new_plugin;
  }
  return NULL;
}

void* //
r_plugin_loader_fn(void* plugin_handle, const char* function_name) {
  void* function_address = (void*)GetProcAddress(plugin_handle, function_name);
  assert(function_address != NULL);
  return function_address;
}