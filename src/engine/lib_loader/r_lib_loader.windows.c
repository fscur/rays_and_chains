#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_block.h"
#include "engine/lib_loader/r_lib_loader.h"
#include "engine/io/r_file.h"

internal void //
r_lib_loader_get_temp_file_name(const char* file_name, char* tmp_file_name) {
  char tmp_path[SHORT_STRING_LENGTH] = {0};
  char name[SHORT_STRING_LENGTH] = {0};

  GetTempPathA(SHORT_STRING_LENGTH, tmp_path);
  sprintf(name, "%s", PathFindFileNameA(file_name));
  sprintf(tmp_file_name, "%s%s", tmp_path, name);
}

internal void
r_lib_loader_get_pdb_file_name(const char* file_name, char* pdb_file_name) {
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

void //
r_lib_loader_load_lib(r_memory_t* memory, r_lib_t* lib, const char* file_name) {

  char tmp_dll_file_name[SHORT_STRING_LENGTH] = {0};
  char tmp_pdb_file_name[SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[SHORT_STRING_LENGTH] = {0};

  r_lib_loader_get_temp_file_name(file_name, tmp_dll_file_name);
  r_lib_loader_get_pdb_file_name(file_name, pdb_file_name);
  r_lib_loader_get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  if (CopyFileA(file_name, tmp_dll_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);
    HMODULE lib_handle = LoadLibraryA(tmp_dll_file_name);
    assert(lib_handle != NULL);

    char lib_name[SHORT_STRING_LENGTH - 4] = {0};

    sprintf(lib_name, "%s", PathFindFileNameA(file_name));
    PathRemoveExtensionA(lib_name);

    char load_fn_name[SHORT_STRING_LENGTH] = {"load_"};
    char get_size_fn_name[SHORT_STRING_LENGTH] = {"get_size_"};
    char get_id_fn_name[SHORT_STRING_LENGTH] = {"get_id_"};

    strcat(load_fn_name, lib_name);
    strcat(get_size_fn_name, lib_name);
    strcat(get_id_fn_name, lib_name);

    R_LIB_LOAD load = (R_LIB_LOAD)r_lib_loader_fn(lib_handle, load_fn_name);
    R_LIB_GET_SIZE get_size = (R_LIB_GET_SIZE)r_lib_loader_fn(lib_handle, get_size_fn_name);
    R_LIB_GET_ID get_id = (R_LIB_GET_ID)r_lib_loader_fn(lib_handle, get_id_fn_name);

    u32 id = get_id();
    size_t memory_size = get_size();
    r_memory_block_t* lib_memory_block = r_memory_add_block(memory, memory_size);
    void* state_memory_addr = r_memory_block_push(lib_memory_block, memory_size);

    r_lib_load_info_t load_info = {0};
    load_info.fn = &r_lib_loader_fn;
    load_info.handle = lib_handle;
    load_info.lib_memory_addr = lib;
    load_info.state_memory_addr = state_memory_addr;

    lib->handle = lib_handle;
    lib->id = id;
    lib->memory_block = lib_memory_block;
    r_string_a_copy(lib_name, lib->name);
    r_string_a_copy(file_name, lib->file_name);
    r_string_a_copy(tmp_dll_file_name, lib->tmp_file_name);
    r_file_a_get_last_modification(lib->file_name, &lib->last_modification);

    load(&load_info);
  }
}

void //
r_lib_loader_destroy_lib(r_lib_t* lib) {
  // if (lib->destroy)
  //   lib->destroy(lib->state);
  FreeLibrary(lib->handle);
}

void //
r_lib_loader_reload_lib(r_memory_t* memory, r_lib_t* lib) {

  while (!DeleteFileA(lib->tmp_file_name))
    Sleep(1);

  char tmp_pdb_file_name[SHORT_STRING_LENGTH] = {0};
  char pdb_file_name[SHORT_STRING_LENGTH] = {0};
  r_lib_loader_get_pdb_file_name(lib->file_name, pdb_file_name);
  r_lib_loader_get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  while (CopyFileA(lib->file_name, lib->tmp_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);

    HMODULE lib_handle = LoadLibraryA(lib->tmp_file_name);
    assert(lib_handle != NULL);

    char load_fn_name[SHORT_STRING_LENGTH] = {"load_"};
    char get_size_fn_name[SHORT_STRING_LENGTH] = {"get_size_"};

    strcat(load_fn_name, lib->name);
    strcat(get_size_fn_name, lib->name);

    R_LIB_LOAD load_function = //
        (R_LIB_LOAD)r_lib_loader_fn(lib_handle, load_fn_name);

    r_lib_load_info_t load_info = {0};
    load_info.fn = &r_lib_loader_fn;
    load_info.handle = lib_handle;
    load_info.lib_memory_addr = lib;

    r_lib_t* new_lib = load_function(&load_info);
    r_file_a_get_last_modification(new_lib->file_name, &new_lib->last_modification);
    new_lib->memory_block = lib->memory_block;
  }
}

void* //
r_lib_loader_fn(void* lib_handle, const char* function_name) {
  void* function_address = (void*)GetProcAddress(lib_handle, function_name);
  assert(function_address != NULL);
  return function_address;
}