#include "engine/io/r_path.h"
#include <string.h>

// void 
// r_path_a_get_file_name_without_extension(char* path, char* file_name) {
//     char *lastdot, *lastsep;
//     char dot = '.';
//     char sep = '\\';

//     if (path == NULL)
//         return;

//     strcpy(file_name, path);
//     lastdot = strrchr (file_name, dot);
//     lastsep = (sep == 0) ? NULL : strrchr (file_name, sep);

//     // If it has an extension separator.
//     if (lastdot != NULL) {
//         if (lastsep != NULL) {
//             if (lastsep < lastdot) {
//                 *lastdot = '\0';
//             }
//         } else {
//             *lastdot = '\0';
//         }
//     }
// }


void r_path_get_filename_without_extension(const char* path, char* file_name) {
  char* tmp_name = basename(path);
  char c = tmp_name[0];
  int i = 0;
  
  while (c != 0) {
    if (c == '.') {
      memcpy(file_name, tmp_name, i);
      file_name[i+1] = 0;
      break;
    }
    c = tmp_name[++i];
  }
}

void r_path_get_file_extension(const char* file_name, char* result) {
  char* name = basename(file_name);
  int start = 0;
  int end = 0;

  while(name[start]!='.') {
    if (name[start]==0) {
      return;
    }
    start++;
  }

  end = start;

  while (name[end++]!=0);
  memcpy(result, name+start, end - start -1);
}