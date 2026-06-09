#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* =========================================================
   TETRIS STACK - NÍVEL MESTRE
   Fila Circular + Pilha + Integração Estratégica
   ========================================================= */

#define TAM_FILA 5
#define TAM_PILHA 3

/* ================= STRUCT ================= */

/* Representa uma peça do jogo */
typedef struct
{
    char tipo;   // Ex: I, O, T, L
    int id;      // identificador único
} Peca;

/* ================= ESTRUTURAS GLOBAIS ================= */

Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int inicio = 0;
int fim = 0;
int totalFila = 0;

int topo = -1;
int idGlobal = 1;

/* ================= FUNÇÕES AUXILIARES ================= */

/* Gera peça aleatória */
Peca gerarPeca()
{
    Peca p;

    char tipos[] = {'I', 'O', 'T', 'L'};

    p.tipo = tipos[rand() % 4];
    p.id = idGlobal++;

    return p;
}

/* ================= FILA ================= */

/* Inicializa fila com 5 peças */
void inicializarFila()
{
    for(int i = 0; i < TAM_FILA; i++)
    {
        fila[i] = gerarPeca();
        totalFila++;
    }
}

/* Verifica fila cheia */
bool filaCheia()
{
    return totalFila == TAM_FILA;
}

/* Verifica fila vazia */
bool filaVazia()
{
    return totalFila == 0;
}

/* Enfileirar */
void enqueue()
{
    if(filaCheia())
        return;

    fila[fim] = gerarPeca();

    fim = (fim + 1) % TAM_FILA;
    totalFila++;
}

/* Desenfileirar */
Peca dequeue()
{
    Peca p = fila[inicio];

    inicio = (inicio + 1) % TAM_FILA;
    totalFila--;

    enqueue(); // mantém fila sempre cheia

    return p;
}

/* Mostra fila */
void mostrarFila()
{
    printf("\n===== FILA =====\n");

    for(int i = 0; i < totalFila; i++)
    {
        int index = (inicio + i) % TAM_FILA;

        printf("[%c - %d] ",
               fila[index].tipo,
               fila[index].id);
    }

    printf("\n");
}

/* ================= PILHA ================= */

/* Verifica pilha cheia */
bool pilhaCheia()
{
    return topo == TAM_PILHA - 1;
}

/* Verifica pilha vazia */
bool pilhaVazia()
{
    return topo == -1;
}

/* Push */
void push(Peca p)
{
    if(pilhaCheia())
        return;

    pilha[++topo] = p;
}

/* Pop */
Peca pop()
{
    return pilha[topo--];
}

/* Mostra pilha */
void mostrarPilha()
{
    printf("\n===== PILHA =====\n");

    for(int i = topo; i >= 0; i--)
    {
        printf("[%c - %d] ",
               pilha[i].tipo,
               pilha[i].id);
    }

    printf("\n");
}

/* ================= OPERAÇÕES ================= */

/* Jogar peça (fila) */
void jogarPeca()
{
    Peca p = dequeue();

    printf("\nJogou peça: %c - %d\n", p.tipo, p.id);
}

/* Reservar peça (fila → pilha) */
void reservarPeca()
{
    if(filaVazia() || pilhaCheia())
        return;

    Peca p = dequeue();

    push(p);

    printf("\nPeça reservada!\n");
}

/* Usar peça da pilha */
void usarPeca()
{
    if(pilhaVazia())
        return;

    Peca p = pop();

    printf("\nUsou peça da reserva: %c - %d\n",
           p.tipo, p.id);
}

/* Troca frente da fila com topo da pilha */
void trocarUm()
{
    if(filaVazia() || pilhaVazia())
        return;

    int indexFila = inicio;

    Peca temp = fila[indexFila];

    fila[indexFila] = pilha[topo];
    pilha[topo] = temp;

    printf("\nTroca realizada (1 elemento)!\n");
}

/* Troca 3 primeiros da fila com pilha */
void trocarTres()
{
    if(totalFila < 3 || topo < 2)
        return;

    for(int i = 0; i < 3; i++)
    {
        int indexFila = (inicio + i) % TAM_FILA;

        Peca temp = fila[indexFila];
        fila[indexFila] = pilha[topo - i];
        pilha[topo - i] = temp;
    }

    printf("\nTroca de 3 elementos realizada!\n");
}

/* ================= MENU ================= */

void mostrarMenu()
{
    printf("\n===== TETRIS STACK =====\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça da reserva\n");
    printf("4 - Trocar 1 elemento\n");
    printf("5 - Trocar 3 elementos\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

/* ================= MAIN ================= */

int main()
{
    srand(time(NULL));

    int opcao;

    inicializarFila();

    do
    {
        mostrarFila();
        mostrarPilha();
        mostrarMenu();

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                jogarPeca();
                break;

            case 2:
                reservarPeca();
                break;

            case 3:
                usarPeca();
                break;

            case 4:
                trocarUm();
                break;

            case 5:
                trocarTres();
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
