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

  pid_t cpid = fork(); // Appel système pour créer un child process 
  if (cpid < 0) report_and_die("Le child process n'a pas pu être crée");

  printf("CPID: %d\n", cpid);

  if (0 == cpid) { // Ce code est exécuté par le child process
    close(pipeFDs[WriteEnd]);
    while (read(pipeFDs[ReadEnd], &buf, 1) > 0) 
      write(STDOUT_FILENO, &buf, sizeof(buf));
    close(pipeFDs[ReadEnd]);
    _exit(0); // Signal envoyé au parent que le child process est terminé
  } else { // Ce code est exécuté par le parent process
    close(pipeFDs[ReadEnd]);
    write(pipeFDs[WriteEnd], msg, strlen(msg));
    close(pipeFDs[WriteEnd]);
    wait(0); // Attend que le child process soit terminé
    exit(0);
  }

  return 0;
}