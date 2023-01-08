// Ce fichier est responsable de la modification du segment de mémoire partagé 

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

  // Joint le segment de mémoire à la même adresse mémoire que ce script
  char* mem_ptr = shmat(mem_id, 0, 0); // 0 signifie qu'on laisse l'OS choisir
  if (mem_ptr == (void*) - 1) report_and_die("failed_on_shmat");
  
  return mem_ptr;
}

int main() {
  int len = 14;
  key_t key = 9876;

  char* mem_ptr = setup(key, len, 0666);
  *mem_ptr = 'h'; // On change le H avec h 

  puts(mem_ptr); // afficher la string pour confirmer
  return 0;

}