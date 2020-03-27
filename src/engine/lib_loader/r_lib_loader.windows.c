#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/lib_loader/r_lib_loader.h"
#include "engine/io/r_file.h"
#include "r_lib.h"

#pragma comment(lib, "Shlwapi.lib")

internal void //
r_lib_loader_get_temp_file_name(const char* file_name, char* tmp_file_name) {
  char tmp_path[R_SHORT_STRING_LENGTH] = {0};
  char name[R_SHORT_STRING_LENGTH] = {0};

  GetTempPathA(R_SHORT_STRING_LENGTH, tmp_path);
  sprintf(name, "%s", PathFindFileNameA(file_name));
  sprintf(tmp_file_name, "%s%s", tmp_path, name);
}

internal void
r_lib_loader_get_pdb_file_name(const char* file_name, char* pdb_file_name) {  
  char path[R_LONG_STRING_LENGTH];
  sprintf(path, "%s", file_name);

  PathRemoveFileSpecA(path);

  sprintf(pdb_file_name, "%s", file_name);
  PathRemoveExtensionA(pdb_file_name);
  sprintf(pdb_file_name, "%s.*.pdb", pdb_file_name);

  WIN32_FIND_DATAA ffd;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  hFind = FindFirstFileA(pdb_file_name, &ffd);
  FindClose(hFind);
  if (strlen(path) == 0)
    sprintf(pdb_file_name, "%s", ffd.cFileName);
  else
    sprintf(pdb_file_name, "%s\\%s", path, ffd.cFileName);
}

r_lib_t* //
r_lib_loader_load_lib(r_memory_t* memory, const char* file_name) {

  char tmp_dll_file_name[R_SHORT_STRING_LENGTH] = {0};
  char tmp_pdb_file_name[R_SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[R_SHORT_STRING_LENGTH] = {0};

  r_lib_loader_get_temp_file_name(file_name, tmp_dll_file_name);
  r_lib_loader_get_pdb_file_name(file_name, pdb_file_name);
  r_lib_loader_get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  if (!CopyFileA(file_name, tmp_dll_file_name, false))
    return NULL;

  CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
  DeleteFileA(pdb_file_name);
  HMODULE lib_handle = LoadLibraryA(tmp_dll_file_name);
  assert(lib_handle != NULL);

  char lib_name[R_SHORT_STRING_LENGTH - 4] = {0};

  sprintf(lib_name, "%s", PathFindFileNameA(file_name));
  PathRemoveExtensionA(lib_name);

  char load_fn_name[R_SHORT_STRING_LENGTH] = {0};
  char get_api_size_fn_name[R_SHORT_STRING_LENGTH] = {0};
  char get_size_fn_name[R_SHORT_STRING_LENGTH] = {0};

  sprintf(load_fn_name, "%s_%s", lib_name, "load");
  sprintf(get_api_size_fn_name, "%s_%s", lib_name, "get_api_size");
  sprintf(get_size_fn_name, "%s_%s", lib_name, "get_size");

  R_LIB_LOAD load = (R_LIB_LOAD)r_lib_loader_fn(lib_handle, load_fn_name);
  R_LIB_GET_SIZE get_api_size = (R_LIB_GET_SIZE)r_lib_loader_fn(lib_handle, get_api_size_fn_name);
  R_LIB_GET_SIZE get_size = (R_LIB_GET_SIZE)r_lib_loader_fn(lib_handle, get_size_fn_name);

  size_t lib_size = sizeof(r_lib_t);
  size_t api_size = get_api_size();
  size_t state_size = get_size();
  r_memory_arena_t* lib_memory_arena = r_memory_add_arena(memory, state_size + api_size + lib_size);
  void* api_memory_addr = r_memory_arena_push(lib_memory_arena, api_size);
  void* lib_memory_addr = r_memory_arena_push(lib_memory_arena, lib_size);
  void* state_memory_addr = r_memory_arena_push(lib_memory_arena, state_size);

  r_lib_load_info_t load_info = {0};
  load_info.fn = &r_lib_loader_fn;
  load_info.handle = lib_handle;
  load_info.api_memory_addr = api_memory_addr;
  load_info.lib_memory_addr = lib_memory_addr;
  load_info.state_memory_addr = state_memory_addr;

  r_lib_t* lib = (r_lib_t*)lib_memory_addr;
  lib->handle = lib_handle;
  lib->api = api_memory_addr;
  lib->memory_arena = lib_memory_arena;
  lib->state = state_memory_addr;

  r_string_copy_ansi(lib->name, lib_name);
  r_string_copy_ansi(lib->file_name, file_name);
  r_string_copy_ansi(lib->tmp_file_name, tmp_dll_file_name);
  
  r_file_a_get_last_modification(lib->file_name, &lib->last_modification);

  load(&load_info);
  return lib;
}

void //
r_lib_loader_destroy_lib(r_lib_t* lib) {
  r_lib_i* lib_api = (r_lib_i*)lib->api;
  lib_api->destroy(lib->state);
  FreeLibrary(lib->handle);
}

void //
r_lib_loader_reload_lib(r_lib_t* lib) {

  while (!DeleteFileA(lib->tmp_file_name))
    Sleep(1);

  char tmp_pdb_file_name[R_SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[R_SHORT_STRING_LENGTH] = {0};
  r_lib_loader_get_pdb_file_name(lib->file_name, pdb_file_name);
  r_lib_loader_get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  while (CopyFileA(lib->file_name, lib->tmp_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);

    HMODULE lib_handle = LoadLibraryA(lib->tmp_file_name);
    assert(lib_handle != NULL);

    char load_fn_name[R_SHORT_STRING_LENGTH] = {0};
    sprintf(load_fn_name, "%s_%s", lib->name, "load");

    R_LIB_LOAD load = //
        (R_LIB_LOAD)r_lib_loader_fn(lib_handle, load_fn_name);

    r_lib_load_info_t load_info = {0};
    load_info.fn = &r_lib_loader_fn;
    load_info.handle = lib_handle;
    load_info.lib_memory_addr = lib;

    load(&load_info);
    r_file_a_get_last_modification(lib->file_name, &lib->last_modification);
    lib->memory_arena = lib->memory_arena;
    lib->state = lib->state;
  }
}

void* //
r_lib_loader_fn(void* lib_handle, const char* function_name) {
  void* function_address = (void*)GetProcAddress(lib_handle, function_name);
  assert(function_address != NULL);
  return function_address;
}