#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char* const args[] = {"./fileStatus", "tmp", 0};
  int ret = execv("./fileStatus", args);
  if (-1 == ret) {
    perror("execv(...) error");
    exit(-1);
  }
  else 
    printf("I'm here\n");
  return 0;
}