#include <windows.h>
#include "engine/plugins/r_plugin_loader.h"

void* //
r_plugin_loader_load_plugin(const wchar_t* file_name) {
  HMODULE plugin_handle = LoadLibrary(file_name);
  assert(plugin_handle != NULL);
  return plugin_handle;
}

void //
r_plugin_loader_unload_plugin(void* plugin_handle) {
  FreeLibrary(plugin_handle);
}

void* //
r_plugin_loader_reload_plugin(void* plugin_handle,
                              const wchar_t* file_name,
                              const wchar_t* tmp_file_name) {
  return NULL;
}

void* //
r_plugin_loader_fn(void* plugin_handle, const char* function_name) {
  void* function_address = (void*)GetProcAddress(plugin_handle, function_name);
  assert(function_address != NULL);
  return function_address;
}