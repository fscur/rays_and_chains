#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include "engine/memory/r_memory.h"
#include "engine/memory/r_memory_arena.h"
#include "engine/plugins/r_plugin_loader.h"
#include "engine/plugins/r_plugin.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "r_memory.lib")

void //
get_temp_file_name(const char* file_name, char* tmp_file_name) {
  char tmp_path[MAX_PATH] = {0};
  char name[MAX_PATH] = {0};

  GetTempPathA(MAX_PATH, tmp_path);
  sprintf(name, "%s", PathFindFileNameA(file_name));
  sprintf(tmp_file_name, "%s%s", tmp_path, name);

  // char tmp_path[MAX_PATH] = {0};
  // char extension[MAX_PATH] = {0};
  // char name[MAX_PATH] = {0};
  // char tag[7] = {0};
  // SYSTEMTIME st;
  // sprintf(extension, "%s", PathFindExtensionA(file_name));
  // sprintf(name, "%s", PathFindFileNameA(file_name));
  // PathRemoveExtensionA(name);

  // sprintf(tmp_path, "%s", file_name);
  // PathRemoveFileSpecA(tmp_path);
  // GetLocalTime(&st);                                              // Local time
  // sprintf(tag, "%.2u%.2u%.2u", st.wHour, st.wMinute, st.wSecond); // 24h format

  // sprintf(tmp_file_name, "%s\\%s%s%s", tmp_path, name, tag, extension);
}

void get_pdb_file_name(const char* file_name, char* pdb_file_name) {
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
r_plugin_loader_load_plugin(r_memory_t* memory, const char* file_name) {

  char tmp_dll_file_name[MAX_PATH] = {0};
  char tmp_pdb_file_name[MAX_PATH] = {0};
  char pdb_file_name[MAX_PATH] = {0};

  get_temp_file_name(file_name, tmp_dll_file_name);
  get_pdb_file_name(file_name, pdb_file_name);
  get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  if (CopyFileA(file_name, tmp_dll_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);
    HMODULE plugin_handle = LoadLibraryA(tmp_dll_file_name);
    assert(plugin_handle != NULL);

    char plugin_name[MAX_FILE_NAME_LENGTH - 4] = {0};

    sprintf(plugin_name, "%s", PathFindFileNameA(file_name));
    PathRemoveExtensionA(plugin_name);

    char load_fn_name[MAX_FILE_NAME_LENGTH] = {"load_"};
    strcat(load_fn_name, plugin_name);

    char get_size_fn_name[MAX_FILE_NAME_LENGTH] = {"get_size_"};
    strcat(get_size_fn_name, plugin_name);

    R_PLUGIN_LOAD load_function = (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_handle, load_fn_name);

    R_PLUGIN_GET_SIZE get_size_function =
        (R_PLUGIN_GET_SIZE)r_plugin_loader_fn(plugin_handle, get_size_fn_name);

    size_t memory_size = get_size_function();
    r_memory_arena_t* memory_arena = r_memory_add_arena(memory, memory_size);
    void* memory_addr = r_memory_arena_push(memory_arena, memory_size);
    r_plugin_t* plugin = load_function(&r_plugin_loader_fn, memory_addr, plugin_handle);

    sprintf(plugin->name, "%s", plugin_name);
    sprintf(plugin->file_name, "%s", file_name);
    sprintf(plugin->tmp_file_name, "%s", tmp_dll_file_name);
    plugin->memory_size = memory_size;
    return plugin;
  }
  return NULL;
}

void //
r_plugin_loader_unload_plugin(r_plugin_t* plugin) {
  FreeLibrary(plugin->handle);
}

r_plugin_t* //
r_plugin_loader_reload_plugin(r_plugin_t* plugin) {
  // HMODULE new_plugin_handle = LoadLibraryA(plugin->file_name);

  char load_fn_name[MAX_FILE_NAME_LENGTH] = {"load_"};
  strcat(load_fn_name, plugin->name);

  // char get_size_fn_name[MAX_FILE_NAME_LENGTH] = {"get_size_"};
  // strcat(get_size_fn_name, plugin->name);

  //R_PLUGIN_LOAD load_function = (R_PLUGIN_LOAD)r_plugin_loader_fn(new_plugin_handle, load_fn_name);

  //R_PLUGIN_GET_SIZE get_size_function =
  //     (R_PLUGIN_GET_SIZE)r_plugin_loader_fn(new_plugin_handle, get_size_fn_name);

  // // todo: how to handle change in size?
  // assert(get_size_function() == plugin->memory_size);
  // FreeLibrary(new_plugin_handle);
  FreeLibrary(plugin->handle);
  while (!DeleteFileA(plugin->tmp_file_name));
  Sleep(500);

  char tmp_pdb_file_name[MAX_PATH] = {0};
  char pdb_file_name[MAX_PATH] = {0};
  get_pdb_file_name(plugin->file_name, pdb_file_name);
  get_temp_file_name(pdb_file_name, tmp_pdb_file_name);

  while (CopyFileA(plugin->file_name, plugin->tmp_file_name, false)) {
    CopyFileA(pdb_file_name, tmp_pdb_file_name, false);
    DeleteFileA(pdb_file_name);
    HMODULE plugin_handle = LoadLibraryA(plugin->tmp_file_name);
    assert(plugin_handle != NULL);
    R_PLUGIN_LOAD load_function = (R_PLUGIN_LOAD)r_plugin_loader_fn(plugin_handle, load_fn_name);
    r_plugin_t* new_plugin = load_function(&r_plugin_loader_fn, plugin->state_addr, plugin_handle);
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