#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_PALAVRAS 10
#define TAM 100

char const tabelaDePalavras[NUM_PALAVRAS][TAM] = {
    "BATATA$E um turberculo",
    "AIPIM$Usa-se para fazer sagu",
    "COMPUTACAO$Melhor curso do mundo",
    "CHIMARRAO$Se toma numa cuia",
    "LAGARTO$Lacoste de elo baixo",
    "MARACUJA$Fruta",
    "SOCORRO$Pedido de ajuda",
    "TATU$Animal",
    "FLORESTA$Amazonia",
    "ARARA$Papagaio vip"};

void atualiza_palavra(char *palavra, int *letras_corretas, int tam_palavra, char letra);

int verifica_letra(char *palavra, int tam_palavra, char letra);

char *escolhe_palavra(char tabelaDePalavras[][TAM], int num_palavras);

void separa_string(char *str, char *str1, char *str2, char separador);

void mostra_palavra(char *palavra, int *letras_corretas, int tam_palavra, char *str2, int erros);

int main()
{
    char *definicao;
    char *dica;
    char str1[20];
    char str2[30];
    int chances = 10;
    char *palavra = escolhe_palavra(tabelaDePalavras, NUM_PALAVRAS);
    separa_string(palavra, str1, str2, '$');

    int tam_palavra = strlen(str1);
    int letras_corretas[tam_palavra];

    for (int i = 0; i < tam_palavra; i++)
    {
        letras_corretas[i] = 0;
    }

    int erros = 0;

    printf("Bem-vindo ao jogo da forca!\n");
    printf("A palavra tem %d letras.\n", tam_palavra);

    while (1)
    {
        mostra_palavra(str1, letras_corretas, tam_palavra, str2, erros);

        char letra;

        printf("Digite uma letra: ");
        scanf(" %c", &letra);
        letra = toupper(letra);
        if (letra == '0')
        {
            break;
        }

        if (verifica_letra(str1, tam_palavra, letra))
        {
            printf("Acertou!\n");
            atualiza_palavra(palavra, letras_corretas, tam_palavra, letra);
        }
        else
        {
            printf("Errou!\n");
            erros++;
        }

        if (erros >= 10)
        {
            printf("Voce perdeu! A palavra era: %s\n", str1);
            break;
        }

        int acertou_todas = 1;

        for (int i = 0; i < tam_palavra; i++)
        {
            if (!letras_corretas[i])
            {
                acertou_todas = 0;
                break;
            }
        }

        if (acertou_todas)
        {
            mostra_palavra(str1, letras_corretas, tam_palavra, str2, erros);
            printf("Parabens, voce acertou a palavra!\n");
            break;
        }
    }

    return 0;
}

char *escolhe_palavra(char tabelaDePalavras[][TAM], int num_palavras)
{
    srand(time(NULL));

    int indice = rand() % num_palavras;

    return tabelaDePalavras[indice];
}

void separa_string(char *str, char *str1, char *str2, char separador)
{

    char *posicao_separador = strchr(str, separador);

    strncpy(str1, str, posicao_separador - str);
    str1[posicao_separador - str] = '\0';

    strncpy(str2, posicao_separador + 1, strlen(posicao_separador + 1));
    str2[strlen(posicao_separador + 1)] = '\0';
}

void mostra_palavra(char *palavra, int *letras_corretas, int tam_palavra, char *str2, int erros)
{
    printf("\nDICA: %s\n", str2);
    printf("\n");
    printf("Chances: %d\n", (10 - erros));
    for (int i = 0; i < tam_palavra; i++)
    {
        if (letras_corretas[i])
        {
            printf("%c ", palavra[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void atualiza_palavra(char *palavra, int *letras_corretas, int tam_palavra, char letra)
{
    for (int i = 0; i < tam_palavra; i++)
    {
        if (palavra[i] == letra)
        {
            letras_corretas[i] = 1;
        }
    }
}

int verifica_letra(char *palavra, int tam_palavra, char letra)
{
    for (int i = 0; i < tam_palavra; i++)
    {
        if (palavra[i] == letra)
        {
            return 1;
        }
    }
    return 0;
}