#include <windows.h>
#include "engine/plugins/r_plugin_loader.h"

void* //
r_plugin_loader_load_plugin(char* file_name) {
  HMODULE plugin_handle = LoadLibraryA(file_name);
  assert(plugin_handle != NULL);
  return plugin_handle;
}

void //
r_plugin_loader_unload_plugin(void* plugin_handle) {
  FreeLibrary(plugin_handle);
}

void* //
r_plugin_loader_reload_plugin(void* plugin_handle, char* file_name, char* tmp_file_name) {
  return NULL;
}

void* //
r_plugin_loader_fn(void* plugin_handle, char* function_name) {
  void* function_address = (void*)GetProcAddress(plugin_handle, function_name);
  assert(function_address != NULL);
  return function_address;
}