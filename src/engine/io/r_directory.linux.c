#include "engine/io/r_directory.h"
#include "engine/io/r_file_info.h"
#include "engine/io/r_path.h"
#include "engine/string/r_string.h"

#include <dirent.h>
#include <string.h>

typedef struct dirent directory_entry;

void //
r_directory_w_foreach_file(wchar_t* path, wchar_t* filter, void* callback, void* data) {
  
}

void //
r_directory_a_foreach_file(char* path, char* filter, void* callback, void* data) {
  directory_entry *dir;
  DIR *d = opendir(path);

  char extension[256] = {0};

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_name[0]== '.' || dir->d_name[1] == '.') {
        continue;
      }

      r_path_get_file_extension(dir->d_name, extension);
      if (r_string_compare_ansi(extension, filter) != 0) {
        continue;
      }

      r_file_info_a_t file_info = {0};
      sprintf(file_info.name, "%s", dir->d_name);
      sprintf(file_info.full_name, "%s/%s", path, dir->d_name);
      ((R_DIRECTORY_A_FOREACH_FILE_CALLBACK)callback)(file_info, (void*)data);
    }
    closedir(d);
  }
}