#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Função que será executada pelas threads
void* print_message(void* arg) {
    char* message = (char*) arg;
    printf("%s\n", message);
    pthread_exit(NULL);  // Termina a thread
}

int main() {
    // Definindo duas threads
    pthread_t thread1, thread2;

    // Mensagens que serão passadas para as threads
    char* message1 = "Olá da Thread 1";
    char* message2 = "Olá da Thread 2";

    // Criando a primeira thread
    if (pthread_create(&thread1, NULL, print_message, (void*) message1) != 0) {
        perror("Erro ao criar thread 1");
        exit(1);
    }

    // Criando a segunda thread
    if (pthread_create(&thread2, NULL, print_message, (void*) message2) != 0) {
        perror("Erro ao criar thread 2");
        exit(1);
    }

    // Esperando as threads terminarem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Ambas as threads terminaram.\n");

    return 0;
}
