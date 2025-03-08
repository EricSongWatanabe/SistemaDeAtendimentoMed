#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

// funcao que retorna o registro do paciente atraves do RG
Registro* busca_paciente(Lista* lista, char rg[13]){ 
    if(lista->qtde == 0){
        return NULL;
    }
    ELista *atual = lista->primeiro;
    while(atual != NULL && strcmp(atual->registro->rg, rg) != 0){
        atual = atual->proximo;
    }
    if (atual == NULL){
        return NULL;
    }
    return atual->registro;
}

// =============================================== LISTA ===============================================

// funcao para criar uma nova lista
Lista* criar_lista() {
    Lista* lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    return lista;  
}

// funcao para criar um novo paciente para lista
ELista* criar_paciente(Registro* registro) {
    ELista* paciente = malloc(sizeof(ELista));
    paciente->registro = registro;
    paciente->proximo = NULL;
    return paciente;
}

// funcao para registrar um paciente
Registro* registrar(char nome[20], int idade, char rg[13], int dia, int mes, int ano) {

    Registro* registro = malloc(sizeof(Registro));
    strcpy(registro->nome, nome);
    registro->idade = idade;
    strcpy(registro->rg, rg);
    registro->entrada = malloc(sizeof(Data));
    registro->entrada->dia = dia;
    registro->entrada->mes = mes;
    registro->entrada->ano = ano;
    return registro; // retorna o ponteiro para Registro
}

// funcao para inserir um paciente na lista
void inserir(Lista* lista, Registro* registro) { 
    ELista* novo = criar_paciente(registro);
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->qtde++;
}

// funcao para mostrar a lista de pacientes
void mostrar_lista(Lista* lista) {
    if(lista->qtde == 0){
        printf("Lista vazia\n");
    }
    ELista* atual = lista->primeiro;
    while(atual != NULL) {
        printf("\nNome: %s\n", atual->registro->nome);
        printf("Idade: %d\n", atual->registro->idade);
        printf("RG: %s\n", atual->registro->rg);
        printf("Data de entrada: %d/%d/%d\n", atual->registro->entrada->dia, atual->registro->entrada->mes, atual->registro->entrada->ano);
        atual = atual->proximo;
    }
    printf("\n");
}

// funcao para mostrar o registro especifico
void mostrar_registro(Lista* lista, char rg[13]) {
    ELista *atual = lista->primeiro;
    while(atual != NULL && strcmp(atual->registro->rg, rg) != 0) {
        atual = atual->proximo;
    }
    if(atual == NULL) {
        printf("Paciente nao encontrado.\n");
    } else {
        printf("\nNome: %s\n", atual->registro->nome);
        printf("Idade: %d\n", atual->registro->idade);
        printf("RG: %s\n", atual->registro->rg);
        printf("Data de entrada: %d/%d/%d\n\n", atual->registro->entrada->dia, atual->registro->entrada->mes, atual->registro->entrada->ano);
    }
}

// funcao para atualizar o nome
void mudar_nome(Lista* lista, char rg[13], char nomeAtualizado[20]){
    ELista *atual = lista->primeiro;
    while(atual != NULL && strcmp(atual->registro->rg, rg) != 0) {
        atual = atual->proximo;
    }
    if(atual == NULL) {
        printf("Paciente nao encontrado.\n");
    } else{
        strcpy(atual->registro->nome, nomeAtualizado);
    }
}

// funcao para atualizar a idade
void mudar_idade(Lista* lista, char rg[13], int idadeAtualizada){
    ELista *atual = lista->primeiro;
    while(atual != NULL && strcmp(atual->registro->rg, rg) != 0) {
        atual = atual->proximo;
    }
    if(atual == NULL) {
        printf("Paciente nao encontrado.\n");
    } else{
        atual->registro->idade = idadeAtualizada;
    }
}

// funcao para remover paciente da lista
void remover_paciente(Lista *lista, char rg[13]){
    ELista *atual = lista->primeiro;
    ELista *anterior = NULL;
    while(atual != NULL && strcmp(atual->registro->rg, rg) != 0){
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL){
        printf("Paciente nao encontrado!\n");
    } else {
        if(anterior == NULL){
            lista->primeiro = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        lista->qtde--;
        free(atual);
    }
}



// =============================================== FILA ===============================================

// funcao para criar fila
Fila *criar_fila(){
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;
    return fila;
}

// funcao para criar um paciente para fila
EFila *criar_paciente_fila(Registro* registro){
    EFila *paciente = malloc(sizeof(EFila));
    paciente->anterior = NULL;
    paciente->proximo = NULL;
    paciente->registro = registro;
    return paciente;
}

// funcao de enfileirar o paciente na fila
void enqueue(Fila *fila, Registro* registro){
    EFila *novo = criar_paciente_fila(registro);
    if(fila->qtde == 0){
        fila->head = novo;
    } else{
        fila->tail->proximo = novo;
        novo->anterior = fila->tail;
    }
    fila->tail = novo;
    fila->qtde++;
}

// função de enfileirar o paciente no início da fila 
void enqueue_primeiro(Fila *fila, Registro* registro){
    EFila *novo = criar_paciente_fila(registro);
    if(fila->qtde == 0){
        fila->head = novo;
        fila->tail = novo;
    } else {
        novo->proximo = fila->head;
        fila->head->anterior = novo;
        fila->head = novo;
    }
    
    fila->qtde++;
}


// funcao de desenfileirar o paciente da fila
Registro* dequeue(Fila *fila){
    if(fila->qtde >0){
        Registro* registro = fila->head->registro;
        EFila *temp = fila->head;
        fila->head = fila->head->proximo;
        if(fila->qtde == 1){
            fila->tail = NULL;
        } else {
            fila->head->anterior = NULL;
        }
        fila->qtde--;
        free(temp);
        return registro;
    } 
    return NULL;
}

// funcao de desenfileirar o ultimo paciente da fila
Registro* dequeue_ultimo(Fila *fila){
    if(fila->qtde >0){
        Registro* registro = fila->tail->registro;
        EFila *temp = fila->tail;
        fila->tail = fila->tail->anterior;
        if(fila->qtde == 1){
            fila->tail = NULL;
        } else {
            fila->tail->proximo = NULL;
        }
        fila->qtde--;
        free(temp);
        return registro;
    } 
    return NULL;
}

// funcao para mostrar a fila
void mostrar_fila(Fila *fila){
    int cont = 1;
    if(fila->qtde == 0){
        printf("Fila vazia\n");
    }
    EFila *atual = fila->head;
    while(atual != NULL){
        printf("\nPosicao: %d", cont);
        printf("\nNome: %s\n", atual->registro->nome);
        printf("Idade: %d\n", atual->registro->idade);
        printf("RG: %s\n", atual->registro->rg);
        printf("Data de entrada: %d/%d/%d\n", atual->registro->entrada->dia, atual->registro->entrada->mes, atual->registro->entrada->ano);
        cont++;
        atual = atual->proximo;
    }
    printf("\n");
}


// =============================================== ARVORE BINARIA DE BUSCA ===============================================


// funcao para criar vertice
EABB *cria_vertice(Registro* registro){
	EABB* novo = malloc(sizeof(EABB));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;
	novo->registro = registro;
	
	return novo;
}

// funcao para criar arvore
ABB *cria_arvore(){
	ABB* arvore = malloc(sizeof(ABB));
	arvore->raiz = NULL;
	arvore->qtde = 0;
	return arvore;
}

void in_ordem(EABB *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->esq);
        printf("\nNome: %s\n", raiz->registro->nome);
        printf("Idade: %d\n", raiz->registro->idade);
        printf("RG: %s\n", raiz->registro->rg);
        printf("Data de entrada: %d/%d/%d\n\n", raiz->registro->entrada->dia, raiz->registro->entrada->mes, raiz->registro->entrada->ano);
        in_ordem(raiz->dir);
    }
}

// funcao para inserir em ordem de acordo com o dia
void inserir_dia(ABB* arvore, Registro* registro) {
    EABB* novo = cria_vertice(registro);
    if (arvore->qtde == 0){
        arvore->raiz = novo;
    } 
    else {
        EABB* atual = arvore->raiz;
        EABB* anterior = NULL;
        while (atual != NULL){
            anterior = atual; 
            if (registro->entrada->dia <= atual->registro->entrada->dia) {
                atual = atual->esq; 
            } 
            else {
                atual = atual->dir;
            }
        }
        if (registro->entrada->dia <= anterior->registro->entrada->dia){
            anterior->esq = novo;
        } 
        else {
            anterior->dir = novo;
        }
        novo->pai = anterior;
    }
    arvore->qtde++;
}

// funcao para inserir em ordem de acordo com o mes
void inserir_mes(ABB* arvore, Registro* registro) {
    EABB* novo = cria_vertice(registro);
    if (arvore->qtde == 0){
        arvore->raiz = novo;
    } 
    else {
        EABB* atual = arvore->raiz;
        EABB* anterior = NULL;
        while (atual != NULL){
            anterior = atual; 
            if (registro->entrada->mes <= atual->registro->entrada->mes) {
                atual = atual->esq; 
            } 
            else {
                atual = atual->dir;
            }
        }
        if (registro->entrada->mes <= anterior->registro->entrada->mes){
            anterior->esq = novo;
        } 
        else {
            anterior->dir = novo;
        }
        novo->pai = anterior;
    }
    arvore->qtde++;
}

// funcao para inserir em ordem de acordo com o ano
void inserir_ano(ABB* arvore, Registro* registro) {
    EABB* novo = cria_vertice(registro);
    if (arvore->qtde == 0){
        arvore->raiz = novo;
    } 
    else {
        EABB* atual = arvore->raiz;
        EABB* anterior = NULL;
        while (atual != NULL){
            anterior = atual; 
            if (registro->entrada->ano <= atual->registro->entrada->ano) {
                atual = atual->esq; 
            } 
            else {
                atual = atual->dir;
            }
        }
        if (registro->entrada->ano <= anterior->registro->entrada->ano){
            anterior->esq = novo;
        } 
        else {
            anterior->dir = novo;
        }
        novo->pai = anterior;
    }
    arvore->qtde++;
}

// funcao para inserir em ordem de acordo com o idade
void inserir_idade(ABB* arvore, Registro* registro) {
    EABB* novo = cria_vertice(registro);
    if (arvore->qtde == 0){
        arvore->raiz = novo;
    } 
    else {
        EABB* atual = arvore->raiz;
        EABB* anterior = NULL;
        while (atual != NULL){
            anterior = atual; 
            if (registro->idade <= atual->registro->idade) {
                atual = atual->esq; 
            } 
            else {
                atual = atual->dir;
            }
        }
        if (registro->idade <= anterior->registro->idade){
            anterior->esq = novo;
        } 
        else {
            anterior->dir = novo;
        }
        novo->pai = anterior;
    }
    arvore->qtde++;
}

// funcao para liberar memoria da arvore
void liberar_arvore(EABB* vertice) {
    if (vertice != NULL) {
        liberar_arvore(vertice->esq);
        liberar_arvore(vertice->dir);
        free(vertice);
    }
}

// funcao para imprimir a arvore binaria em ordem do dia
void mostrar_registro_dia(Lista* lista, ABB* arvore){
    ELista* atual = lista->primeiro;
    while (atual != NULL){
        inserir_dia(arvore, atual->registro);
        atual = atual->proximo;
    }
    EABB* raiz = arvore->raiz;
    in_ordem(raiz);
}

// funcao para imprimir a arvore binaria em ordem do mes
void mostrar_registro_mes(Lista* lista, ABB* arvore){
    ELista* atual = lista->primeiro;
    while (atual != NULL){
        inserir_mes(arvore, atual->registro);
        atual = atual->proximo;
    }
    EABB* raiz = arvore->raiz;
    in_ordem(raiz);
}

// funcao para imprimir a arvore binaria em ordem do ano
void mostrar_registro_ano(Lista* lista, ABB* arvore){
    ELista* atual = lista->primeiro;
    while (atual != NULL){
        inserir_ano(arvore, atual->registro);
        atual = atual->proximo;
    }
    EABB* raiz = arvore->raiz;
    in_ordem(raiz);
}

// funcao para imprimir a arvore binaria em ordem da idade
void mostrar_registro_idade(Lista* lista, ABB* arvore){
    ELista* atual = lista->primeiro;
    while (atual != NULL){
        inserir_idade(arvore, atual->registro);
        atual = atual->proximo;
    }
    EABB* raiz = arvore->raiz;
    in_ordem(raiz);
}


// =============================================== PILHA ===============================================


// funcao para criar elemento na pilha
EPilha *criar_celula(int tipo, Registro* registro){
    EPilha *celula = malloc(sizeof(EPilha));
    celula->anterior = NULL;
    celula->proximo = NULL;
    celula->tipo = tipo;
    celula->registro = registro;
    return celula;
}

// funcao para criar pilha 
Pilha *criar_pilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->qtd = 0;
    pilha->topo = NULL;
    return pilha;
}

// funcao para empilhar na pilha
void empilhar(Pilha *pilha, int tipo, Registro* registro){
    EPilha *novo = criar_celula(tipo, registro);
    if (pilha->qtd > 0) {
        novo->anterior = pilha->topo;
        pilha->topo->proximo = novo;
    }
    pilha->topo = novo;
    pilha->qtd++;
}

// funcao para desempilhar da pilha
Registro* desempilhar(Pilha *pilha){
    if (pilha->qtd == 0) {
        printf("Nenhuma alteracao a ser feita\n");
        return NULL;
    }
    Registro* registro = pilha->topo->registro;
    EPilha *temp = pilha->topo;
    pilha->topo = pilha->topo->anterior;
    free(temp);
    pilha->qtd--;
    return registro;
}

// funcao para resgatar o tipo de operacao a ser feito
int retorna_tipo(Pilha *pilha){
    return pilha->topo->tipo;
}

// funcao para desfazer da fila
void desfazer(Pilha *pilha, Fila* fila){
    if (pilha->qtd == 0) {
        printf("Nenhuma alteracao a ser feita\n");
        return;
    }
    int tipo = retorna_tipo(pilha);
    Registro* ult = desempilhar(pilha);
    if(ult == NULL){
        return;
    }

    if(tipo == 0){
        printf("Dados do ultimo paciente adicionado:\n");
        printf("\nNome: %s\n", ult->nome);
        printf("Idade: %d\n", ult->idade);
        printf("RG: %s\n", ult->rg);
        printf("Data de entrada: %d/%d/%d\n", ult->entrada->dia, ult->entrada->mes, ult->entrada->ano);
        int opcao;
        
        printf("\nDeseja remover o ultimo paciente adicionado a fila?\n");
        printf("[0] Sim\n");
        printf("[1] Nao\n");
        printf("Digite sua resposta: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch(opcao){
            case 1:{
                empilhar(pilha, tipo, ult);
                break;
            }

            case 0:{
                dequeue_ultimo(fila);
                printf("Acao desfeita\n");
                break;
            }

            default: {
                empilhar(pilha, tipo, ult);
                printf("Opção inválida! Tente novamente.\n");
                break;
            }

        }
        return;
    }
    else if(tipo == 1){
        printf("Dados do ultimo paciente removido:\n");
        printf("\nNome: %s\n", ult->nome);
        printf("Idade: %d\n", ult->idade);
        printf("RG: %s\n", ult->rg);
        printf("Data de entrada: %d/%d/%d\n", ult->entrada->dia, ult->entrada->mes, ult->entrada->ano);
        int opcao;
        printf("\nDeseja reinserir o ultimo paciente removido a fila?\n");
        printf("[0] Sim\n");
        printf("[1] Nao\n");
        printf("Digite sua resposta: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch(opcao){
            case 1:{
                empilhar(pilha, tipo, ult);
                break;
            }

            case 0:{
                enqueue_primeiro(fila, ult);
                printf("Acao desfeita\n");
                break;
            }

            default: {
                empilhar(pilha, tipo, ult);
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }

        }
        return;
    }
}


// =============================================== ARQUIVO ===============================================


// funcao para salvar a lista de pacientes em um arquivo
void salvar_lista(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    ELista* atual = lista->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%s %d %s %d %d %d\n", atual->registro->nome, atual->registro->idade, atual->registro->rg, atual->registro->entrada->dia, atual->registro->entrada->mes, atual->registro->entrada->ano);
        atual = atual->proximo;
    }
    fclose(arquivo);
    printf("Lista salva com sucesso em %s\n", nomeArquivo);
}

// funcao para carregar a lista de pacientes de um arquivo
void carregar_lista(Lista* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para carregar.\n");
        return;
    }

    char nome[20], rg[13];
    int idade, dia, mes, ano;

    while (fscanf(arquivo, "%s %d %s %d %d %d\n", nome, &idade, rg, &dia, &mes, &ano) == 6) {
        Registro* novoRegistro = malloc(sizeof(Registro));
        novoRegistro->entrada = malloc(sizeof(Data));
        strcpy(novoRegistro->nome, nome);
        novoRegistro->idade = idade;
        strcpy(novoRegistro->rg, rg);
        novoRegistro->entrada->dia = dia;
        novoRegistro->entrada->mes = mes;
        novoRegistro->entrada->ano = ano;

        inserir(lista, novoRegistro);  // adiciona o paciente a lista
    }

    fclose(arquivo);
    printf("Lista carregada com sucesso de %s\n", nomeArquivo);
}
