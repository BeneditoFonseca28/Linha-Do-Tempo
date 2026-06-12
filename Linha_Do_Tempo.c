#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>  

void escreverHistoria() {
    int ano;
    char categoria[100], historia[1000];
    FILE *arquivo;
    printf("\nDigite o ano: ");
    scanf("%d", &ano);
    getchar();
    printf("Digite a categoria(ex: familia, trabalho, viagem, amigos...): ");
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';
    printf("Escreva sua historia aqui: ");
    fgets(historia, 1000, stdin);
    historia[strcspn(historia, "\n")] = '\0';
    arquivo = fopen("historias.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo, tente novamente.\n");
    }
    else {
        fprintf(arquivo, "ANO: %d\n", ano);
        fprintf(arquivo, "Categoria: %s\n", categoria);
        fprintf(arquivo, "HISTORIA: %s", historia);
        fprintf(arquivo, "\n----------------------------\n");
        fclose(arquivo);
        printf("\nHistoria salva com sucesso!\n");
    }
}

int main()
{
    srand(time(NULL));
    int controle = 1, anoArquivo, encontrou, opcao, ano, editou = 0, opcaoEditar, excluiu = 0, numAleatorio, status = 0, achouAno;
    int exclusao;
    char categoria[100], historia[1000], linha[500], novaHistoria[1000], blocoAno[50], blocoCategoria[100], blocoHistoria[1000];
    char frases[5][100] = {
        "Qual sua brincadeira favorita na infancia? ",
        "Como foi seu primeiro namoro? ",
        "Qual seu doce favorito? ",
        "Qual foi sua melhor viagem? ",
        "Qual seu estilo musical? "
    };
    FILE *arquivo;

    do
    {
        system("cls");
        printf("======================================\n");
        printf("    BEM VINDO A SUA LINHA DO TEMPO    \n");
        printf("======================================\n");
        printf("\nEscolha uma opcao: \n");
        printf("\n0 - Sair");
        printf("\n1 - Escrever uma nova historia");
        printf("\n2 - Ver todas as historias");
        printf("\n3 - Buscar por ano");
        printf("\n4 - Editar historia");
        printf("\n5 - Excluir uma historia");
        printf("\n6 - Sugestao de historia");
        printf("\n\nOpcao: ");
        scanf("%d", &opcao);
        switch(opcao)
        {
            case 0:
                controle = 0;
                printf("\nPrograma finalizado!\n");
                break;
            case 1:
                do
                {
                    system("cls");
                    printf("\nDigite o ano: ");
                    scanf("%d", &ano);
                    getchar();
                    printf("Digite a categoria(ex: familia, trabalho, viagem, amigos...): ");
                    fgets(categoria, 100, stdin);
                    categoria[strcspn(categoria, "\n")] = '\0';
                    printf("Escreva sua historia aqui: ");
                    fgets(historia, 1000, stdin);
                    historia[strcspn(historia, "\n")] = '\0';
                    arquivo = fopen("historias.txt", "a");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo, tente novamente.\n");
                    }
                    else {
                        fprintf(arquivo, "ANO: %d\n", ano);
                        fprintf(arquivo, "Categoria: %s\n", categoria);
                        fprintf(arquivo, "HISTORIA: %s", historia);
                        fprintf(arquivo, "\n----------------------------\n");
                        fclose(arquivo);
                        printf("\nHistoria salva com sucesso!\n");
                    }
                    printf("\n\nDeseja escrever mais uma historia? 1-Sim / 0-Nao: ");
                    scanf("%d", &status);
                }while(status != 0);
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            case 2:
                system("cls");
                encontrou = 0;
                arquivo = fopen("historias.txt", "r");
                if (arquivo == NULL) {
                    encontrou = 1;
                    printf("Nenhuma historia encontrada!\n");
                } else {
                    printf("====================================\n");
                    printf("        TODAS AS HISTORIAS          \n");
                    printf("====================================\n\n");
                    while (fgets(linha, 500, arquivo) != NULL) {
                        printf("%s", linha);
                        encontrou = 1;
                    }
                    fclose(arquivo);
                }
                if (encontrou == 0){
                    printf("Voce nao tem historias escritas!\n");
                }
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            case 3:
                do
                {
                    system("cls");
                    achouAno = 0;
                    encontrou = 0;
                    printf("\nDigite o ano que deseja buscar: ");
                    scanf("%d", &ano);
                    arquivo = fopen("historias.txt", "r");
                    while (fgets(linha, 500, arquivo) != NULL) {
                        if (sscanf(linha, "ANO: %d", &anoArquivo) == 1) {
                            if (anoArquivo == ano) {
                                encontrou = 1;
                                achouAno = 1;
                                printf("\n====================================\n");
                                printf("     HISTORIAS DO ANO: %d\n", ano);
                                printf("====================================\n\n");
                                printf("%s", linha);
                            }
                            else{
                                encontrou = 0;
                            }
                        }
                        else{
                            if (encontrou == 1) {
                                printf("%s", linha);
                            }
                        }
                    }
                    fclose(arquivo);
                    if (achouAno == 0) { 
                        printf("Nenhuma historia encontrada para o ano %d!\n", ano);
                    }
                    printf("\n\nDeseja buscar mais historias? 1-Sim / 0-Nao: ");
                    scanf("%d", &status);
                }while(status != 0);
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            case 4:
                do
                {
                    system("cls");
                    FILE *temp;
                    printf("\nDigite o ano da historia que deseja editar: ");
                    scanf("%d", &ano);
                    getchar();
                    arquivo = fopen("historias.txt", "r");
                    temp = fopen("temp.txt", "w");
                    if (arquivo == NULL) {
                        printf("\nNenhuma historia encontrada!\n");
                    }
                    else {
                        encontrou = 0;
                        editou = 0;
                        while (fgets(linha, 500, arquivo) != NULL) {
                            if (sscanf(linha, "ANO: %d", &anoArquivo) == 1) {
                                if (anoArquivo == ano) {
                                    encontrou = 1;
                                }
                                sprintf(blocoAno, "%s", linha);
                            }
                            else {
                                if (strncmp(linha, "Categoria:", 10) == 0) {
                                    sprintf(blocoCategoria, "%s", linha);
                                }
                                else {
                                    if (strncmp(linha, "HISTORIA:", 9) == 0) {
                                        sprintf(blocoHistoria, "%s", linha);
                                    }
                                    else {
                                        if (strncmp(linha, "---", 3) == 0) {
                                            if (encontrou == 1) {
                                                system("cls");
                                                printf("Historia encontrada:\n\n");
                                                printf("%s", blocoAno);
                                                printf("%s", blocoCategoria);
                                                printf("%s", blocoHistoria);
                                                printf("----------------------------\n");
                                                printf("\nO que deseja fazer?\n");
                                                printf("\n1 - Reescrever a historia\n");
                                                printf("2 - Voltar ao menu\n");
                                                printf("\nOpcao: ");
                                                scanf("%d", &opcaoEditar);
                                                getchar();
                                                if (opcaoEditar == 1) {
                                                    printf("\nDigite a nova historia: ");
                                                    fgets(novaHistoria, 1000, stdin);
                                                    novaHistoria[strcspn(novaHistoria, "\n")] = '\0';
                                                    fprintf(temp, "%s", blocoAno);
                                                    fprintf(temp, "%s", blocoCategoria);
                                                    fprintf(temp, "HISTORIA: %s\n", novaHistoria);
                                                    fprintf(temp, "----------------------------\n");
                                                    editou = 1;
                                                }
                                                else {
                                                    fprintf(temp, "%s", blocoAno);
                                                    fprintf(temp, "%s", blocoCategoria);
                                                    fprintf(temp, "%s", blocoHistoria);
                                                    fprintf(temp, "----------------------------\n");
                                                    editou = 2;
                                                }
                                                encontrou = 0;
                                            }
                                            else {
                                                fprintf(temp, "%s", blocoAno);
                                                fprintf(temp, "%s", blocoCategoria);
                                                fprintf(temp, "%s", blocoHistoria);
                                                fprintf(temp, "----------------------------\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        fclose(arquivo);
                        fclose(temp);
                        if (editou == 1) {
                            remove("historias.txt");
                            rename("temp.txt", "historias.txt");
                            printf("\nHistoria editada com sucesso!\n");
                        }
                        else {
                            if (editou == 0) {
                                remove("temp.txt");
                                printf("\nNenhuma historia encontrada para o ano %d!\n", ano);
                            }
                        }
                    }
                    printf("\n\nDeseja editar outra historia? 1-Sim / 0-Nao: ");
                    scanf("%d", &status);
                }while(status != 0);
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            case 5:
                system("cls");
                do
                {
                    FILE *temp2;
                    excluiu = 0;
                    exclusao = 0;
                    printf("\nDigite o ano da historia que deseja excluir: ");
                    scanf("%d", &ano);
                    getchar();
                    arquivo = fopen("historias.txt", "r");
                    temp2 = fopen("temp2.txt", "w");
                    if (arquivo == NULL) {
                        printf("\nNenhuma historia encontrada!\n");
                    }
                    else {
                        encontrou = 0;
                        while (fgets(linha, 500, arquivo) != NULL) {
                            if (sscanf(linha, "ANO: %d", &anoArquivo) == 1) {
                                if (anoArquivo == ano) {
                                    encontrou = 1;
                                } else {
                                    encontrou = 0;
                                }
                                sprintf(blocoAno, "%s", linha);
                            }
                            else {
                                if (strncmp(linha, "Categoria:", 10) == 0) {
                                    sprintf(blocoCategoria, "%s", linha);
                                }
                                else {
                                    if (strncmp(linha, "HISTORIA:", 9) == 0) {
                                        sprintf(blocoHistoria, "%s", linha);
                                    }
                                    else {
                                        if (strncmp(linha, "---", 3) == 0) {
                                            if (encontrou == 1) {
                                                system("cls");
                                                printf("Historia encontrada:\n\n");
                                                printf("%s", blocoAno);
                                                printf("%s", blocoCategoria);
                                                printf("%s", blocoHistoria);
                                                printf("----------------------------\n");
                                                printf("\nTem certeza que deseja excluir?\n");
                                                printf("1 - Sim, excluir\n");
                                                printf("2 - Nao, voltar ao menu\n");
                                                printf("\nOpcao: ");
                                                scanf("%d", &opcaoEditar);
                                                getchar();
                                                if (opcaoEditar == 1) {
                                                    excluiu = 1;
                                                    exclusao = 1;
                                                }
                                                else {
                                                    fprintf(temp2, "%s", blocoAno);
                                                    fprintf(temp2, "%s", blocoCategoria);
                                                    fprintf(temp2, "%s", blocoHistoria);
                                                    fprintf(temp2, "----------------------------\n");
                                                }
                                                encontrou = 0;
                                            }
                                            else {
                                                fprintf(temp2, "%s", blocoAno);
                                                fprintf(temp2, "%s", blocoCategoria);
                                                fprintf(temp2, "%s", blocoHistoria);
                                                fprintf(temp2, "----------------------------\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        fclose(arquivo);
                        fclose(temp2);
                        if (exclusao == 1) {
                            remove("historias.txt");
                            rename("temp2.txt", "historias.txt");
                            printf("\nHistoria excluida com sucesso!\n");
                        }
                        else {
                            remove("temp2.txt");
                            if (excluiu == 0) {
                                printf("\nHistoria nao encontrada!");
                            }
                        }
                    }
                    printf("\n\nDeseja exluir outra historia? 1-Sim / 0-Nao: ");
                    scanf("%d", &status);
                }while(status != 0);
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            case 6:
                system("cls");
                printf("Sugestao de historia: ");
                numAleatorio = rand() % 5;
                printf("%s\n", frases[numAleatorio]);
                escreverHistoria();
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
                break;
            default:
                system("cls");
                printf("\nErro! Opcao invalida.");
                printf("\nAperte qualquer tecla para voltar ao menu de opcoes: ");
                getch();
        }
    }while(controle != 0);
    return 0;
}