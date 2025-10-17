#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5    // Tamanho da fila de pecas
#define TAM_PILHA 3   // Tamanho da pilha de reserva

// Struct para representar uma peca
typedef struct {
    char nome; // Tipo da peca: 'I', 'O', 'T', 'L'
    int id;    // ID unico da peca
} Peca;

// Struct para fila circular
typedef struct {
    Peca fila[TAM_FILA];
    int frente;
    int tras;
} FilaCircular;

// Struct para pilha
typedef struct {
    Peca pilha[TAM_PILHA];
    int topo;
} Pilha;

// Tipos possiveis das pecas
char tipos[] = {'I', 'O', 'T', 'L'};
int id_geral = 0; // Contador para IDs unicos

// Funcao para gerar uma peca aleatoria
Peca gerarPeca() {
    Peca peca;
    peca.nome = tipos[rand() % 4];
    peca.id = id_geral++;
    return peca;
}

// Inicializa a fila com pecas
void inicializarFila(FilaCircular* fila) {
    fila->frente = 0;
    fila->tras = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        fila->fila[i] = gerarPeca();
        fila->tras = (fila->tras + 1) % TAM_FILA;
    }
}

// Inicializa a pilha (vazia)
void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

// Exibe o estado atual da fila e da pilha
void exibirEstado(FilaCircular* fila, Pilha* pilha) {
    printf("\nEstado atual:\n");

    // Fila
    printf("Fila de pecas\t\t");
    int i = fila->frente;
    while (i != fila->tras) {
        printf("[%c %d] ", fila->fila[i].nome, fila->fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    // Pilha
    printf("Pilha de reserva\t(Topo -> Base): ");
    for (int j = pilha->topo; j >= 0; j--) {
        printf("[%c %d] ", pilha->pilha[j].nome, pilha->pilha[j].id);
    }
    printf("\n");
}

// Jogar uma peca (remove da fila e adiciona nova no final)
void jogarPeca(FilaCircular* fila) {
    Peca pecaJogada = fila->fila[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;

    Peca nova = gerarPeca();
    fila->fila[fila->tras] = nova;
    fila->tras = (fila->tras + 1) % TAM_FILA;

    printf("Peca jogada: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
}

// Reservar uma peca (move da fila para a pilha)
void reservarPeca(FilaCircular* fila, Pilha* pilha) {
    if (pilha->topo < TAM_PILHA - 1) {
        pilha->topo++;
        pilha->pilha[pilha->topo] = fila->fila[fila->frente];
        fila->frente = (fila->frente + 1) % TAM_FILA;

        Peca nova = gerarPeca();
        fila->fila[fila->tras] = nova;
        fila->tras = (fila->tras + 1) % TAM_FILA;

        printf("Peca reservada: [%c %d]\n", pilha->pilha[pilha->topo].nome, pilha->pilha[pilha->topo].id);
    } else {
        printf("A pilha esta cheia! Nao e possivel reservar mais pecas.\n");
    }
}

// Usar uma peca reservada (remove do topo da pilha)
void usarPecaReservada(Pilha* pilha) {
    if (pilha->topo >= 0) {
        Peca usada = pilha->pilha[pilha->topo];
        pilha->topo--;
        printf("Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
    } else {
        printf("A pilha esta vazia! Nao ha pecas reservadas.\n");
    }
}

// Funcao principal (menu)
int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    FilaCircular fila;
    Pilha pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpcoes de Acao:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                reservarPeca(&fila, &pilha);
                break;
            case 3:
                usarPecaReservada(&pilha);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
