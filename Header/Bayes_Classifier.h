#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Amostra{
    int N_Classe;
    float *Features;
}Amostra;

typedef struct Lista_Amostras{
    Amostra amostra;
    struct Lista_Amotras *prox;
}Lista_Amostras;

typedef struct Matrizes{
    float Qtd_Amostras_Classe;
    float M_Determinante_Covariancia;
    float *Medio;
    float *Desvio_padrao;
    float **Dispersao;
    float **Covariancia;
    float **Covariancia_Invertida;
}Matrizes;

void Divide(char simbolo, char texto[50], char **resultado);
int Preenche_Lista_Amostras(Lista_Amostras **lista_amostras,Matrizes **matrizes,int q_Classes,int q_Features);
int Adiciona(Lista_Amostras **lista_amostras,int N_Classe, int q_Features, char **V_valores);
void Imprime(int qf, Lista_Amostras *lista_amostras);

Lista_Amostras **Cria_Lista_Amostras(int qC);


int Cria_Medio(int qFeatures,Matrizes **matrizes, int N_Classe);
int Cria_Desvio_Padrao(int qFeatures,Matrizes **matrizes,int N_Classe);
int Cria_Dispersao(int qFeatures,Matrizes **matrizes,int N_Classe);
int Cria_Covariancia(int qFeatures,Matrizes **matrizes,int N_Classe);
int Cria_Covariancia_Invertida(int qFeatures,Matrizes **matrizes,int N_Classe);

Matrizes **Cria_Vetor_Matrizes(int q_Classes,int q_Features);


void Media(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe);
void Desvio_Padrao(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe);
void Matriz_Dispersao(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe);
void Matriz_Covariancia(Matrizes *matrizes, int qF, int classe);
int Inverte_Matriz(Matrizes *matrizes, int qF, int classe);
int Modulo_Determinante_Covariancia(Matrizes *matrizes, int qF, int classe);
int Multiplicacao_Matrizes(Amostra *Ponto, Matrizes *matrizes, float *E, int qF, int classe);
int Gi(Amostra *Ponto, Matrizes *matrizes, float *E, float *gi, int qF,int classe);
void Preenche_Ponto(Amostra *Ponto, int qF);

int Cria_Vetor_Expoentes(int qC, float **E);
int Cria_Vetor_gi(int qC, float **gi);
Amostra *Cria_Ponto(int qF);

void Copia_Matriz(int l, int c, float **M, float **C);
void Transforma_Triangular(int l, int c, float **M);
float Determinante(int l, int c, float **M);

char **Libera_value(char **value, int q_Features);
Lista_Amostras *Libera_Lista_Amostras_In(Lista_Amostras *lista_amostras);
Lista_Amostras **Libera_Lista_Amostras_Out(Lista_Amostras **lista_amostras, int q_Features, int q_Classes);
Matrizes *Libera_Matrizes_In(Matrizes *matrizes, int q_Features);
Matrizes **Libera_Matrizes_Out(Matrizes **matrizes, int q_Features, int q_Classes);
float *Libera_Vetor(float *V, int qC);
Amostra *Libera_Ponto(Amostra *Ponto);


#endif // HEADER_H_INCLUDED
