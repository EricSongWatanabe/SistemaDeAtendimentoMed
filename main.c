#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

// gcc main.c biblioteca.c -o p
// ./p


int main(void) {
    Lista* lista = criar_lista(); // cria a lista a ser usada no programa
    Fila* fila = criar_fila(); // cria a fila a ser usada no programa
    Pilha* pilha = criar_pilha(); // cria a pilha a ser usada no programa
    int opcao;

    do { // o programa funciona enquanto o usuario nao digita "0" (opcao para sair)
        // exibir menu principal
        printf("=====================================\n");
        printf("[1] Cadastrar\n");
        printf("[2] Atendimento\n");
        printf("[3] Pesquisa\n");
        printf("[4] Desfazer\n");
        printf("[5] Carregar/Salvar\n");
        printf("[6] Sobre\n");
        printf("[0] Sair\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer

        switch(opcao) {
            case 1: { // opcao referente ao cadastro
                int subopcao;
                // exibir sub-menu da opcao 1
                printf("\n=====================================\n");
                printf("[1] Cadastrar novo paciente\n");
                printf("[2] Consultar paciente cadastrado\n");
                printf("[3] Mostrar lista completa\n");
                printf("[4] Atualizar dados de paciente\n");
                printf("[5] Remover paciente\n");
                printf("[0] Voltar\n");
                printf("=====================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &subopcao);
                getchar(); // limpa o buffer

                switch(subopcao) {
                    case 1: { // opcao para cadastro de um novo paciente e adicionar na lista
                        char nome[20];
                        int idade;
                        char rg[13];
                        int dia, mes, ano;

                        printf("\nDigite o nome do paciente: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strcspn(nome, "\n")] = 0;

                        printf("Digite a idade do paciente: ");
                        scanf("%d", &idade);
                        getchar(); // limpa o buffer

                        printf("Digite o RG do paciente: ");
                        fgets(rg, sizeof(rg), stdin);
                        rg[strcspn(rg, "\n")] = 0; // remove a nova linha na string

                        if (busca_paciente(lista, rg) != NULL) {
                            printf("\nPaciente com RG %s ja cadastrado\n", rg); 
                            break;    
                        }

                        printf("Digite a data de entrada (DD MM AAAA): ");
                        scanf("%d %d %d", &dia, &mes, &ano);
                        getchar(); // limpa o buffer

                        Registro* registro = registrar(nome, idade, rg, dia, mes, ano); // depois de coletar todas as informacoes, eh criado um registro para o paciente
                        inserir(lista, registro); // o registro do paciente eh adicionado na lista
                        printf("\nPaciente cadastrado com sucesso!\n");
                        break;
                    }
                    case 2: { // opcao para consulta de um paciente ja adicionado na lista
                        char rg[13];
                        printf("\nDigite o RG do paciente que deseja consultar: ");
                        fgets(rg, sizeof(rg), stdin);
                        rg[strcspn(rg, "\n")] = 0;
                        mostrar_registro(lista, rg); // busca o paciente pelo RG
                        break;
                    }
                    case 3: { // opcao para mostrar toda a lista de pacientes
                        printf("\nLista de pacientes cadastrados:\n\n");
                        mostrar_lista(lista); // funcao para exibir a lista
                        break;
                    }
                    case 4: { // opcao para atualizar os dados do paciente
                        char rg[13];
                        int opcao4;
                        printf("\nDigite o RG do paciente que deseja atualizar: ");
                        fgets(rg, sizeof(rg), stdin);
                        rg[strcspn(rg, "\n")] = 0;
                        printf("\n=====================================\n");
                        printf("[1] Atualizar nome\n");
                        printf("[2] Atualizar idade\n");
                        printf("=====================================\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcao4);
                        getchar(); // limpa o buffer

                        switch(opcao4){
                            case 1: { // atualizacao de nome
                                char nomeAtualizado[20];
                                printf("\nDigite o nome atualizado: ");
                                fgets(nomeAtualizado, sizeof(rg), stdin);
                                nomeAtualizado[strcspn(nomeAtualizado, "\n")] = 0;

                                mudar_nome(lista, rg, nomeAtualizado); // funcao para alterar o nome atraves do RG fornecido
                                printf("\nNome atualizado com sucesso!\n");
                                break;
                            }
                            case 2: { // atualizacao de idade
                                int idadeAtualizada;
                                printf("Digite a idade do paciente: ");
                                scanf("%d", &idadeAtualizada);
                                getchar(); // limpa o buffer

                                mudar_idade(lista, rg, idadeAtualizada); // funcao para alterar a idade atraves do RG fornecido
                                printf("\nIdade atualizada com sucesso!\n");
                                break;
                            } 
                            default:{ // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                                printf("Opcao invalida! Tente novamente.\n");
                                break;
                            }
                        }
                        
                        break;
                    }
                    case 5:{ // opcao para remocao de paciente
                        char rg[13];
                        printf("\nDigite o RG do paciente que deseja remover: ");
                        fgets(rg, sizeof(rg), stdin);
                        rg[strcspn(rg, "\n")] = 0;
                        remover_paciente(lista, rg); // funcao de remover o paciente da lista atraves do RG fornecido
                        printf("Paciente removido da lista\n");
                        break;
                    }
                    case 0:{ // opcao para voltar ao menu principal
                        printf("Voltando ao menu principal\n");
                        break;
                    }
                    default:{ // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                        printf("Opcao invalida! Tente novamente.\n");
                        break;
                    }
                }
                break;
            }



            case 2:{ // opcao referente ao atendimento
                int subopcao;
                // exibir sub-menu da opcao 2
                printf("\n=====================================\n");
                printf("[1] Enfileirar paciente\n");
                printf("[2] Desenfileirar paciente\n");
                printf("[3] Mostrar fila\n");
                printf("[0] Voltar\n");
                printf("=====================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &subopcao);
                getchar(); // limpa o buffer

                switch(subopcao){
                    case 1:{ // opcao para enfileiramento do paciente
                        char rg[13];
                        printf("\nDigite o RG do paciente que deseja inserir na fila: ");
                        fgets(rg, sizeof(rg), stdin);
                        rg[strcspn(rg, "\n")] = 0;
                        Registro* registro = busca_paciente(lista, rg); // busca o registro na lista de pacientes atraves do RG
                        if(registro == NULL){ // se nao encontrar o paciente, retorna mensagem de erro
                            printf("\nPaciente nao cadastrado ou dados invalidos.\n");
                        } else{
                            int tipo = 0;
                            empilhar(pilha, tipo, registro); // coloca na pilha a acao de enfileiramento realizada
                            enqueue(fila, registro); // enfileira o paciente
                            printf("\nPaciente enfileirado com sucesso!\n");
                        }
                        break;
                    }
                    case 2: { // opcao para desenfileiramento do paciente
                        Registro* pacienteAtendido = dequeue(fila); // resgata o registro do paciente desenfileirado
                        int tipo = 1;
                        empilhar(pilha, tipo, pacienteAtendido); // coloca na pilha a acao de desenfileiramento realizada
                        if(pacienteAtendido == NULL) { // se o paciente desenfileirado nao existir, retorna mensagem de erro
                            printf("\nFila vazia, nenhum paciente para atender.\n");
                        } else { // exibe os dados do paciente desenfileirado (atendido)
                            printf("\nPaciente atendido:\n");
                            printf("Nome: %s\n", pacienteAtendido->nome);
                            printf("Idade: %d\n", pacienteAtendido->idade);
                            printf("RG: %s\n", pacienteAtendido->rg);
                            printf("Data de entrada: %d/%d/%d\n", pacienteAtendido->entrada->dia, pacienteAtendido->entrada->mes, pacienteAtendido->entrada->ano);
                        }
                        break;
                    }
                    case 3: { // opcao para mostrar a fila de pacientes
                        printf("\nFila de pacientes:\n");
                        mostrar_fila(fila);
                        break;
                    }
                    case 0: { // opcao para voltar ao menu principal
                        printf("Voltando ao menu principal\n");
                        break;
                    }
                    default: { // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                        printf("Opcao invalida! Tente novamente.\n");
                        break;
                    }
                }
                break;
            }



            case 3:{ // opcao referente a pesquisa
                int subopcao;
                // exibir sub-menu da opcao 3
                printf("\n=====================================\n");
                printf("Mostrar os registros ordenados por:\n");
                printf("[1] Ano\n");
                printf("[2] Mes\n");
                printf("[3] Dia\n");
                printf("[4] Idade do paciente\n");
                printf("[0] Voltar\n");
                printf("=====================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &subopcao);
                getchar(); // limpa o buffer

                switch(subopcao) {
                    case 1:{ // opcao para mostrar os registros ordenados por ano
                        ABB* arvore = cria_arvore(); // cria uma arvore
                        mostrar_registro_ano(lista, arvore); // constroi a arvore ordenando por ano e exibe ela
                        liberar_arvore(arvore->raiz); // libera a arvore
                        break;
                    }
                    case 2:{ // opcao para mostrar os registros ordenados por mes
                        ABB* arvore = cria_arvore(); // cria uma arvore
                        mostrar_registro_mes(lista, arvore); // constroi a arvore ordenando por mes e exibe ela
                        liberar_arvore(arvore->raiz); // libera a arvore
                        break;
                    }
                    case 3:{ // opcao para mostrar os registros ordenados por dia
                        ABB* arvore = cria_arvore(); // cria uma arvore
                        mostrar_registro_dia(lista, arvore); // constroi a arvore ordenando por dia e exibe ela
                        liberar_arvore(arvore->raiz); // libera a arvore
                        break;
                    }
                    case 4:{ // opcao para mostrar os registros ordenados por idade do paciente
                        ABB* arvore = cria_arvore(); // cria uma arvore
                        mostrar_registro_idade(lista, arvore); // constroi a arvore ordenando por idade e exibe ela
                        liberar_arvore(arvore->raiz); // libera a arvore
                        break;
                    }
                    case 0: { // opcao para voltar ao menu principal
                        printf("Voltando ao menu principal\n");
                        break;
                    }
                    default:{ // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                        printf("Opcao invalida! Tente novamente.\n");
                        break;
                    }
                }
                break;
            }
            
            case 4:{ // opcao referente a funcao de desfazer
                desfazer(pilha, fila); // executa a funcao de desfazer da pilha na fila de atendimento
                break;
            }

            case 5: { // opcao referente a funcao de salvar/carregar a lista em um arquivo
                int subopcao;
                // exibir sub-menu da opcao 5
                printf("\n=====================================\n");
                printf("[1] Salvar lista em arquivo\n");
                printf("[2] Carregar lista de arquivo\n");
                printf("[0] Voltar\n");
                printf("=====================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &subopcao);
                getchar(); // limpa o buffer

                switch (subopcao) {
                    case 1: { // opcao de salvar a lista de pacientes em um arquivo
                        salvar_lista(lista, "lista_pacientes.txt");
                        break;
                    }
                    case 2: { // opcao de carregar a lista de pacientes do arquivo
                        carregar_lista(lista, "lista_pacientes.txt");
                        break;
                    }
                    case 0: // opcao para voltar ao menu principal
                        printf("Voltando ao menu principal\n");
                        break;
                    default: // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                        printf("Opcao invalida! Tente novamente.\n");
                        break;
                }
                break;
            }

            case 6:{ // "sobre" o programa
                printf("\nNome: Eric Song Watanabe\n");
                printf("Ciclo: 4 Semestre\n");
                printf("Curso: Cienca da Computacao\n");
                printf("Disciplina: Estrutura de Dados\n");
                printf("Data: 08/10/2024\n\n");
                break;
            }

            case 0: // opcao de encerrar o programa
                break;
            default: // caso o usuario digite uma opcao inexistente, imprime mensagem de erro e retorna
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while(opcao != 0); // condicao para o loop

    return 0;
}