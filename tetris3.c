#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// === Definicoes ===
#define TAM_FILA 5
#define TAM_PILHA 3

// === Struct da peca ===
typedef struct {
    char nome;  // Tipo: I, O, T, L
    int id;     // ID unico
} Peca;

// === Fila circular ===
Peca fila[TAM_FILA];
int frente = 0;
int tras = 0;
int totalFila = 0;

// === Pilha ===
Peca pilha[TAM_PILHA];
int topo = -1;

// === ID global ===
int proximoID = 0;

// === Funcao para gerar peca aleatoria ===
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];  // sorteia tipo
    nova.id = proximoID++;
    return nova;
}

// Inserir na fila circular
void enfileirar(Peca p) {
    if (totalFila < TAM_FILA) {
        fila[tras] = p;
        tras = (tras + 1) % TAM_FILA;
        totalFila++;
    }
}

// Remover da fila circular
Peca desenfileirar() {
    Peca removida = {' ', -1};
    if (totalFila > 0) {
        removida = fila[frente];
        frente = (frente + 1) % TAM_FILA;
        totalFila--;
    }
    return removida;
}

// Empilhar na pilha
int empilhar(Peca p) {
    if (topo < TAM_PILHA - 1) {
        topo++;
        pilha[topo] = p;
        return 1;
    }
    return 0;
}

// Desempilhar da pilha
Peca desempilhar() {
    Peca p = {' ', -1};
    if (topo >= 0) {
        p = pilha[topo];
        topo--;
    }
    return p;
}

// Mostrar o estado atual
void exibirEstado() {
    printf("\n=== Estado Atual ===\n");
    printf("Fila de pecas:\t");
    int i = frente;
    for (int c = 0; c < totalFila; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva (Topo -> Base):\t");
    for (int j = topo; j >= 0; j--) {
        printf("[%c %d] ", pilha[j].nome, pilha[j].id);
    }
    printf("\n=====================\n");
}

// Trocar uma peca da fila com uma da pilha
void trocarPeca() {
    if (topo >= 0 && totalFila > 0) {
        Peca temp = pilha[topo];
        pilha[topo] = fila[frente];
        fila[frente] = temp;
        printf("Troca realizada com sucesso!\n");
    } else {
        printf("Troca impossivel. Pilha ou fila vazia.\n");
    }
}

// Trocar 3 da fila com 3 da pilha
void trocarMultiplas() {
    if (topo >= 2 && totalFila >= 3) {
        for (int i = 0; i < 3; i++) {
            int posFila = (frente + i) % TAM_FILA;
            Peca temp = fila[posFila];
            fila[posFila] = pilha[topo - i];
            pilha[topo - i] = temp;
        }
        printf("Troca multipla realizada com sucesso!\n");
    } else {
        printf("Nao ha pecas suficientes para troca multipla.\n");
    }
}

// Funcao principal
int main() {
    srand(time(NULL));  // inicializa gerador de numeros aleatorios

    // Preenche a fila inicial com 5 pecas
    while (totalFila < TAM_FILA) {
        enfileirar(gerarPeca());
    }

    int opcao;
    do {
        exibirEstado();
        printf("\nOpcoes:\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para pilha de reserva\n");
        printf("3 - Usar peca da pilha de reserva\n");
        printf("4 - Trocar peca da fila com a da pilha\n");
        printf("5 - Trocar 3 da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Opcao escolhida: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Peca usada = desenfileirar();
                if (usada.id != -1) {
                    printf("Peca [%c %d] jogada!\n", usada.nome, usada.id);
                    enfileirar(gerarPeca());
                } else {
                    printf("Fila vazia.\n");
                }
                break;
            }
            case 2: {
                if (topo < TAM_PILHA - 1 && totalFila > 0) {
                    Peca movida = desenfileirar();
                    empilhar(movida);
                    printf("Peca [%c %d] enviada para pilha.\n", movida.nome, movida.id);
                    enfileirar(gerarPeca());
                } else {
                    printf("Nao foi possivel enviar a peca para a pilha.\n");
                }
                break;
            }
            case 3: {
                Peca usada = desempilhar();
                if (usada.id != -1)
                    printf("Peca [%c %d] usada da pilha.\n", usada.nome, usada.id);
                else
                    printf("Pilha vazia!\n");
                break;
            }
            case 4:
                trocarPeca();
                break;
            case 5:
                trocarMultiplas();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}
