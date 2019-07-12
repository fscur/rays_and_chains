#include "engine/io/r_path.h"

void 
r_path_a_get_file_name_without_extension(char* path, char* file_name) {
    char *lastdot, *lastsep;
    char dot = '.';
    char sep = '\\';

    if (path == NULL)
        return;

    strcpy(file_name, path);
    lastdot = strrchr (file_name, dot);
    lastsep = (sep == 0) ? NULL : strrchr (file_name, sep);

    // If it has an extension separator.
    if (lastdot != NULL) {
        if (lastsep != NULL) {
            if (lastsep < lastdot) {
                *lastdot = '\0';
            }
        } else {
            *lastdot = '\0';
        }
    }
}