#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Structs
typedef struct Data { // struct para armazenar a data de entrada dos pacientes
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Registro { // struct para armazenar o registro de cada paciente
    char nome[20];
    int idade;
    char rg[13];
    Data* entrada;
} Registro;

typedef struct ELista { // struct para o elemento na lista
    struct ELista* proximo;
    Registro* registro;
} ELista;

typedef struct { // struct de lista
    ELista* primeiro;
    int qtde;
} Lista;

typedef struct EFila { // struct para o elemento na fila
    struct EFila* proximo;
    struct EFila* anterior;
    Registro* registro;
} EFila;

typedef struct { // struct de fila
    EFila* head;
    EFila* tail;
    int qtde;
} Fila;

typedef struct EABB { // struct para o vertice na arvore binaria
    Registro* registro;
    struct EABB* esq;
    struct EABB* dir;
    struct EABB* pai;
} EABB;

typedef struct { // struct de arvore binaria
    EABB* raiz;
    int qtde;
} ABB;

typedef struct EPilha { // struct para o elemento na pilha
    struct EPilha* anterior;
    struct EPilha* proximo;
    int tipo; // 0 para dequeue e 1 para enqueue
    Registro* registro;
} EPilha;

typedef struct { // struct de pilha
    EPilha* topo;
    int qtd;
} Pilha;

// Funções da biblioteca

Registro* busca_paciente(Lista* lista, char rg[13]);

// Referentes a lista
Lista* criar_lista();
ELista* criar_paciente(Registro* registro);
Registro* registrar(char nome[20], int idade, char rg[13], int dia, int mes, int ano);
void inserir(Lista* lista, Registro* registro);
void mostrar_lista(Lista* lista);
void mostrar_registro(Lista* lista, char rg[13]);
void mudar_nome(Lista* lista, char rg[13], char nomeAtualizado[20]);
void mudar_idade(Lista* lista, char rg[13], int idadeAtualizada);
void remover_paciente(Lista* lista, char rg[13]);

// Referentes a fila
Fila* criar_fila();
EFila* criar_paciente_fila(Registro* registro);
void enqueue(Fila* fila, Registro* registro);
void enqueue_primeiro(Fila *fila, Registro* registro);
Registro* dequeue(Fila* fila);
Registro* dequeue_ultimo(Fila* fila);
void mostrar_fila(Fila* fila);

// Referentes a árvore binária
EABB* cria_vertice(Registro* registro);
ABB* cria_arvore();
void in_ordem(EABB* raiz);
void inserir_ano(ABB* arvore, Registro* registro);
void inserir_mes(ABB* arvore, Registro* registro);
void inserir_dia(ABB* arvore, Registro* registro);
void inserir_idade(ABB* arvore, Registro* registro);
void liberar_arvore(EABB* vertice);
void mostrar_registro_ano(Lista* lista, ABB* arvore);
void mostrar_registro_mes(Lista* lista, ABB* arvore);
void mostrar_registro_dia(Lista* lista, ABB* arvore);
void mostrar_registro_idade(Lista* lista, ABB* arvore);

// Referentes a pilha
EPilha* criar_celula(int tipo, Registro* registro);
Pilha* criar_pilha();
void empilhar(Pilha* pilha, int tipo, Registro* registro);
Registro* desempilhar(Pilha* pilha);
int retorna_tipo(Pilha* pilha);
void desfazer(Pilha* pilha, Fila* fila);

// Referentes a arquivo
void salvar_lista(Lista* lista, const char* arquivo);
void carregar_lista(Lista* lista, const char* arquivo);

#endif // BIBLIOTECA_H