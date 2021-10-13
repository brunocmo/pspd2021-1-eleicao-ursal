#include <stdio.h>
#include <stdlib.h>

typedef struct Candidato
{
    int nCandidato;
    int qtdVotos;
} Candidato;

//Definicoes Gerais
typedef int item;
#define key(A) (A)
#define less(A, B) (key(A) > key(B))
#define exch(A, B)    \
    {                 \
        item t = A;   \
        A = B, B = t; \
    }
#define cmpexch(A, B)   \
    {                   \
        if (less(B, A)) \
            exch(A, B); \
    }

//Funcoes
void ordena(Candidato *v, int l, int r);
void merge(Candidato *v, int l, int r1, int r2);

int main(int argc, char **argv)
{
    FILE *inputFile;

    int nSenadores, nDepFederal, nDepEstadual;
    int votoPresidente = 0, votoInvalido = 0, votoValido = 0, voto = 0;
    double maioriaPresidente;

    Candidato presidente[100] = {0, 0};
    Candidato senador[1000] = {0, 0};
    Candidato depFederal[10000] = {0, 0};
    Candidato depEstadual[100000] = {0, 0};

    inputFile = fopen(argv[1], "r");

    fscanf(inputFile, "%d %d %d\n", &nSenadores, &nDepFederal, &nDepEstadual);

    while (fscanf(inputFile, "%d", &voto) != EOF)
    {
        if (voto >= 10)
        {
            votoValido++;
            if (voto < 100)
            {
                presidente[voto].nCandidato = voto;
                presidente[voto].qtdVotos++;
                votoPresidente++;
            }
            else if (voto < 1000)
            {
                senador[voto].nCandidato = voto;
                senador[voto].qtdVotos++;
            }
            else if (voto < 10000)
            {
                depFederal[voto].nCandidato = voto;
                depFederal[voto].qtdVotos++;
            }
            else
            {
                depEstadual[voto].nCandidato = voto;
                depEstadual[voto].qtdVotos++;
            }
        }
        else
            votoInvalido++;
    }
    // Ordenar em ordem decrescente de acordo com qtdVotos.
    ordena(presidente, 0, 99);
    ordena(senador, 0, 999);
    ordena(depFederal, 0, 9999);
    ordena(depEstadual, 0, 99999);

    printf("%d %d\n", votoValido, votoInvalido);

    maioriaPresidente = votoPresidente * 0.51;

    if (presidente[0].qtdVotos > maioriaPresidente)
        printf("%d\n", presidente[0].nCandidato);
    else
        printf("Segundo turno\n");

    printf("%d", senador[0].nCandidato);
    for (int i = 1; i < nSenadores; i++)
        printf(" %d", senador[i].nCandidato);
    printf("\n");

    printf("%d", depFederal[0].nCandidato);
    for (int i = 1; i < nDepFederal; i++)
        printf(" %d", depFederal[i].nCandidato);
    printf("\n");

    printf("%d", depEstadual[0].nCandidato);
    for (int i = 1; i < nDepEstadual; i++)
        printf(" %d", depEstadual[i].nCandidato);
    printf("\n");

    return 0;
}

void ordena(Candidato *v, int l, int r)
{
    if (l >= r)
        return;
    int meio = (r + l) / 2;
    ordena(v, l, meio);
    ordena(v, meio + 1, r);
    merge(v, l, meio, r);
}

void merge(Candidato *v, int l, int r1, int r2)
{
    Candidato v2[100000];
    int k = 0;
    int i = l;
    int j = r1 + 1;

    while (i <= r1 && j <= r2)
    {
        if (less(v[i].qtdVotos, v[j].qtdVotos))
            v2[k++] = v[i++];
        else
            v2[k++] = v[j++];
    }

    while (i <= r1)
        v2[k++] = v[i++];
    while (j <= r2)
        v2[k++] = v[j++];

    k = 0;
    for (int i = l; i <= r2; i++)
    {
        v[i] = v2[k++];
    }

    return;
}