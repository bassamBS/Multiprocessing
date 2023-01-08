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

char *setup(key_t key, int byte_count, int flags) {
  // Obtient la mémoire partagée et son identifiant
  int mem_id = shmget(key, byte_count, flags);

  if (mem_id < 0) report_and_die("failed on shmget");

  // Joint le segment de mémoire dans l'adresse mémoire de ce script
  char* mem_ptr = shmat(mem_id, 0, 0); // 0 signifie qu'on laisse l'OS choisir
  if (mem_ptr == (void*) - 1) report_and_die("failed_on_shmat");
  
  return mem_ptr;
}

int main() {
  const char* greeting = "Hello world!";
  int len = strlen(greeting) + 1;
  key_t key = 9876;
}