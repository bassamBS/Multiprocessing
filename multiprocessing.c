/** Ce script est un exemple d'appel système pour créer du multiprocessing **/

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ReadEnd 0
#define WriteEnd 1

void report_and_die(const char* msg) {
  perror(msg);
  exit(-1);
}

