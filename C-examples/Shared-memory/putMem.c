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

char* setup(key_t key, int byte_count, int flags) {
  // Obtient la mémoire partagée et son identifiant
  int mem_id = shmget(key, byte_count, flags);

  if (mem_id < 0) report_and_die("failed on shmget");

  // Joint le segment de mémoire à la même adresse mémoire que ce script
  char* mem_ptr = shmat(mem_id, 0, 0); // 0 signifie qu'on laisse l'OS choisir
  if (mem_ptr == (void*) - 1) report_and_die("failed_on_shmat");
  
  return mem_ptr;
}

int main() {
  const char* greeting = "Hello, world!";
  int len = strlen(greeting) + 1;
  key_t key = 9876;

  char* mem_ptr = setup(key, len, IPC_CREAT | 0666);
  memcpy(mem_ptr, greeting, len); // Copy le message dans le segment partagé

  // On attend que l'autre processus accède à la mémoire partagée;
  while (*mem_ptr == 'H') // l'autre processus modifiera le H en h
    sleep(1);
  printf("%s is new msg: putter is exiting...\n", mem_ptr);
  return 0;

}