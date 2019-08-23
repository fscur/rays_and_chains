// #include <string.h>
// #include <jansson/jansson.h>

// #pragma comment(lib, "jansson_d.lib")

/*
int
main(int argc, char* argv[]) {
  size_t i;
  char* text;
  json_t* root;
  json_error_t error;

  text = "[{\"name\":\"filipe\"}]";

  if (!text)
    return 1;

  root = json_loads(text, 0, &error);
  //free(text);

  if (!root) {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }

  if (!json_is_array(root)) {
    fprintf(stderr, "error: root is not an array\n");
    json_decref(root);
    return 1;
  }

  for (i = 0; i < json_array_size(root); i++) {
    json_t *data, *name;

    data = json_array_get(root, i);
    if (!json_is_object(data)) {
      fprintf(stderr, "error: commit data %d is not an object\n", (int)(i + 1));
      json_decref(root);
      return 1;
    }

    name = json_object_get(data, "name");
    if (!json_is_string(name)) {
      fprintf(stderr, "error: commit %d: sha is not a string\n", (int)(i + 1));
      return 1;
    }

    printf("%s\n", json_string_value(name));
  }

  json_decref(root);
  return 0;
}
*/