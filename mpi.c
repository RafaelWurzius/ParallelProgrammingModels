#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    // Descobre o número de processos e o rank do processo atual
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  // Número de processos
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);  // Rank do processo atual

    // Buffer para mensagem que será enviada
    char message[30];

    if (world_rank == 0) {
        // O processo de rank 0 (mestre) recebe mensagens de todos os outros processos
        printf("Processo mestre (rank 0) aguardando mensagens...\n");
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(message, 30, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Processo mestre recebeu mensagem: '%s' do processo %d\n", message, i);
        }
    } else {
        // Cada processo envia uma mensagem para o processo de rank 0
        sprintf(message, "Olá do processo %d", world_rank);
        MPI_Send(message, 30, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}
