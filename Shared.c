#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024  // Tamanho do segmento de memória compartilhada

int main() {
    // Gera uma chave única para o segmento de memória compartilhada
    key_t key = ftok("shmfile", 65);

    // Cria o segmento de memória compartilhada
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget falhou");
        exit(1);
    }

    // Anexa o segmento de memória ao espaço de endereçamento do processo
    char *shared_memory = (char*) shmat(shmid, NULL, 0);
    if (shared_memory == (char*) -1) {
        perror("shmat falhou");
        exit(1);
    }

    // Cria um processo filho
    pid_t pid = fork();

    if (pid < 0) {
        perror("Falha no fork");
        exit(1);
    }

    if (pid == 0) {  // Código do processo filho
        // Escreve uma mensagem na memória compartilhada
        printf("Processo filho escrevendo na memória compartilhada...\n");
        strcpy(shared_memory, "Olá do processo filho!");
        printf("Mensagem do filho: %s\n", shared_memory);
        exit(0);
    } else {  // Código do processo pai
        // Espera um pouco para garantir que o filho escreva primeiro
        sleep(1);
        printf("Processo pai leu da memória compartilhada: %s\n", shared_memory);

        // Desanexa o segmento de memória
        if (shmdt(shared_memory) == -1) {
            perror("shmdt falhou");
            exit(1);
        }

        // Remove o segmento de memória compartilhada
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl falhou");
            exit(1);
        }
    }

    return 0;
}
