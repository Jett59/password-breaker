#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct context;

bool check(const char *password, struct context *context);

#define MAXLEN 64

// Return the time taken to break the password
double checkTime(struct context *context) {
  clock_t start = clock();
  char *password = calloc(MAXLEN + 1, sizeof(char));
  while (password[MAXLEN] == 0) {
    if (check(password, context)) {
      break;
    }
    int i = 0;
    do {
      if (password[i] == 0) {
        password[i] = 'a';
      } else if (password[i] == 'z') {
        password[i] = 'A';
      } else if (password[i] == 'Z') {
        password[i] = 'a';
        i++;
        continue;
      } else {
        password[i]++;
      }
      break;
    } while (true);
  }
  free(password);
  clock_t timeTaken = clock() - start;
  return (double)timeTaken / CLOCKS_PER_SEC;
}

struct context {
  const char *str;
};

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(
        stderr,
        "Supply a password to find out how long it would take to break it\n");
    return 1;
  }
  struct context context;
  context.str = argv[1];
  double timeTaken = checkTime(&context);
  printf("It took %.3fs\n", timeTaken);
  return 0;
}

bool check(const char *password, struct context *context) {
  return strcmp(password, context->str) == 0;
}
