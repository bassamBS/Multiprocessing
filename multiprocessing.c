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

int main() {
  int pipeFDs[2]; // Array de descripteurs de fichier
  char buf;
  const char* msg = "Cette phrase est écrite par le process parent et affichée par le process enfant\n";

  if (pipe(pipeFDs) < 0) report_and_die("Erreur");

  pid_t cpid = fork(); // Child process 
  if (cpid < 0) report_and_die("Le child process n'a pas pu être crée");

  
  if (0 == cpid) { // Ce code est exécuté par le child process

  } else { // Ce code est exécuté par le parent process

  }

}