// Ce fichier est responsable de l'allocation de mémoire et de mettre une donnée

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

void report_and_die(const char* msg) {
  perror(msg); 
  exit(-1);
}

