#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *file = fopen(argv[1], "r");

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *tape = calloc(30000, sizeof(char));
  char *pointer = tape;
  char *code = malloc(fileSize + 1);
  fread(code, fileSize, 1, file);
  fclose(file);

  for (char *command = code; *command; command++) {
    switch (*command) {
    case '>':
      ++pointer;
      break;

    case '<':
      --pointer;
      break;

    case '+':
      ++*pointer;
      break;

    case '-':
      --*pointer;
      break;

    case '.':
      putchar(*pointer);
      break;

    case ',':
      *pointer = getchar();
      break;

    case '[':
      if (!*pointer) {
        int loop = 1;
        while (loop) {
          ++command;
          loop += (*command == '[') - (*command == ']');
        }
      }
      break;

    case ']':
      if (*pointer) {
        int loop = 1;
        while (loop) {
          --command;
          loop += (*command == ']') - (*command == '[');
        }
      }
      break;
    }
  }

  return 0;
}