#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MaxWrite 256

int main() {
  srand(time(0)); // Générateur de nombre aléatoire

  const char* fifoName = "./myPipel";
  mkfifo(fifoName, 0666); // Lecture/Écriture pour user/group/others
  int fd = open(fifoName, O_CREAT |O_WRONLY); // Ouvre un bloc sur un FIFO

  int i;
  for (i = 0; i < MaxWrite; i++) {
    int n = rand();
    write(fd, &n, sizeof(int));
  }

  close(fd); // Ferme le FIFO
  unlink(fifoName); // Se débarasse du fichier sous-jacent
  return 0;
}