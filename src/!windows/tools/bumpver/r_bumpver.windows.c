#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

typedef struct version {
  int major;
  int minor;
  int patch;
  int build;
} version;

char* optarg = NULL;
int optind = 1;

int
getopt(int argc, char* const argv[], const char* optstring) {
  if ((optind >= argc) || (argv[optind][0] != '-') || (argv[optind][0] == 0)) {
    return -1;
  }

  int opt = argv[optind][1];
  const char* p = strchr(optstring, opt);

  if (p == NULL) {
    return '?';
  }
  if (p[1] == ':') {
    optind++;
    if (optind >= argc) {
      return '?';
    }
    optarg = argv[optind];
    optind++;
  }
  optind++;
  return opt;
}

version //
bump_version(const char* file_name, int bump) {

  char tmp_file_name[SHORT_STRING_LENGTH] = {0};
  GetTempFileNameA(".", "\0", 0, tmp_file_name);
  FILE* read_file = fopen(file_name, "r");
  FILE* write_file = fopen(tmp_file_name, "w");

  char c = '\0';
  while (c != '\n') {
    fread(&c, 1, 1, read_file);
    fwrite(&c, 1, 1, write_file);
  }

  int major = 0;
  int minor = 0;
  int patch = 0;
  int build = 0;

  fscanf(read_file, "#define VER_FILEVERSION %d,%d,%d,%d\n", &major, &minor, &patch, &build);

  switch (bump) {
  case 0:
    major++;
    break;
  case 1:
    minor++;
    break;
  case 2:
    patch++;
    break;
  case 3:
    build++;
    break;
  default:
    break;
  }

  fprintf(write_file, "#define VER_FILEVERSION %d,%d,%d,%d\n", major, minor, patch, build);
  fprintf(
      write_file, "#define VER_FILEVERSION_STR \"%d.%d.%d.%d\\0\"\n", major, minor, patch, build);
  fprintf(write_file, "#define VER_PRODUCTVERSION %d,%d,%d,%d\n", major, minor, patch, build);
  fprintf(write_file,
          "#define VER_PRODUCTVERSION_STR \"%d.%d.%d.%d\\0\"\n\n",
          major,
          minor,
          patch,
          build);

  int a;
  fscanf(read_file, "#define VER_FILEVERSION_STR \"%d.%d.%d.%d\\0\"\n", &a, &a, &a, &a);
  fscanf(read_file, "#define VER_PRODUCTVERSION %d,%d,%d,%d\n", &a, &a, &a, &a);
  fscanf(read_file, "#define VER_PRODUCTVERSION_STR \"%d.%d.%d.%d\\0\"\n", &a, &a, &a, &a);

  while (1) {
    fread(&c, 1, 1, read_file);
    if (feof(read_file))
      break;
    fwrite(&c, 1, 1, write_file);
  }

  fclose(read_file);
  fclose(write_file);

  DeleteFileA(file_name);
  CopyFileA(tmp_file_name, file_name, FALSE);
  DeleteFileA(tmp_file_name);
  return (version){major, minor, patch, build};
}

int
main(int argc, char* argv[]) {
  int opt = 0;
  int bump = 3;
  while (opt != -1) {
    opt = getopt(argc, argv, "Mnpb");
    switch (opt) {
    case 'M': {
      version v = bump_version(argv[optind], 0);
      printf("bumped major version: %d.%d.%d.%d\n", v.major, v.minor, v.patch, v.build);
    } break;
    case 'm': {
      version v = bump_version(argv[optind], 1);
      printf("bumped minor version: %d.%d.%d.%d\n", v.major, v.minor, v.patch, v.build);
    } break;
    case 'p': {
      version v = bump_version(argv[optind], 2);
      printf("bumped patch version: %d.%d.%d.%d\n", v.major, v.minor, v.patch, v.build);
    } break;
    case 'b': {
      version v = bump_version(argv[optind], 3);
      printf("bumped build version: %d.%d.%d.%d\n", v.major, v.minor, v.patch, v.build);
    } break;
    case '?':
      printf("help\n");
      exit(0);
    }
  }

  return 0;
}