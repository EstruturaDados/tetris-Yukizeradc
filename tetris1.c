#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_FILA 5

// Estrutura que representa uma peca
typedef struct {
    char nome;
    int id;
} Peca;

// Variaveis da fila
Peca fila[TAMANHO_FILA];
int frente = 0;
int tras = 0;
int quantidade = 0;
int proximoID = 0;

// Funcao para gerar uma nova peca automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[proximoID % 4];
    nova.id = proximoID;
    proximoID++;
    return nova;
}

// Funcao para mostrar as pecas da fila
void mostrarFila() {
    printf("Fila de Pecas:\n");
    if (quantidade == 0) {
        printf("Fila vazia.\n");
    } else {
        for (int i = 0; i < quantidade; i++) {
            int indice = (frente + i) % TAMANHO_FILA;
            printf("[%c %d] ", fila[indice].nome, fila[indice].id);
        }
        printf("\n");
    }
}

int main() {
    int opcao;

    // Inicializa a fila com 5 pecas
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca();
        fila[tras] = p;
        tras = (tras + 1) % TAMANHO_FILA;
        quantidade++;
    }

    // Loop do menu
    do {
        mostrarFila();

        printf("\nOpcoes:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Inserir nova peca\n");
        printf("0 - Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (quantidade == 0) {
                printf("A fila ja esta vazia.\n");
            } else {
                Peca removida = fila[frente];
                frente = (frente + 1) % TAMANHO_FILA;
                quantidade--;
                printf("Peca jogada: [%c %d]\n", removida.nome, removida.id);
            }
        } else if (opcao == 2) {
            if (quantidade == TAMANHO_FILA) {
                printf("A fila esta cheia. Nao e possivel adicionar.\n");
            } else {
                Peca nova = gerarPeca();
                fila[tras] = nova;
                tras = (tras + 1) % TAMANHO_FILA;
                quantidade++;
                printf("Nova peca inserida: [%c %d]\n", nova.nome, nova.id);
            }
        } else if (opcao == 0) {
            printf("Saindo do programa.\n");
        } else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
