#include "../Header/Bayes_Classifier.h"


void Media(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe){
    int i;
    Lista_Amostras *aux = lista_amostras;

    for(i=0; i<qF; i++){
        matrizes->Medio[i] = 0;
    }
    while(aux != NULL){
        for(i=0; i<qF; i++){
            matrizes->Medio[i] = aux->amostra.Features[i] + matrizes->Medio[i];
        }
        aux = aux->prox;
    }

    for(i=0; i<qF; i++){
        matrizes->Medio[i] = matrizes->Medio[i]/matrizes->Qtd_Amostras_Classe;
    }

    printf("Vetor Medio da classe %i:\n", classe);
    for(i=0;i<qF; i++){
        printf("%f\n",matrizes->Medio[i]);
    }
}

void Desvio_Padrao(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe){
    int i;
    Lista_Amostras *aux = lista_amostras;

    for(i=0; i<qF; i++){
        matrizes->Desvio_padrao[i] = 0;
    }
    while(aux != NULL){
        for(i=0; i<qF; i++){
            matrizes->Desvio_padrao[i] = pow(aux->amostra.Features[i] - matrizes->Medio[i],2) + matrizes->Desvio_padrao[i];
        }
        aux = aux->prox;
    }

    for(i=0; i<qF; i++){
        matrizes->Desvio_padrao[i] = sqrt(matrizes->Desvio_padrao[i]/matrizes->Qtd_Amostras_Classe);
    }

    printf("Vetor Desvio Padrao da classe %i:\n", classe);
    for(i=0;i<qF; i++){
        printf("%f\n",matrizes->Desvio_padrao[i]);
    }

}

void Matriz_Dispersao(Lista_Amostras *lista_amostras,Matrizes *matrizes, int qF, int classe){
    Lista_Amostras *aux;
    int i,j;

    for(i=0; i<qF; i++){
        for (j = 0; j<qF; j++){
            matrizes->Dispersao[i][j] = 0;
        }
    }
    for(i = 0; i<qF; i++){
        for(j = 0; j<qF; j++){
            aux = lista_amostras;
            while(aux != NULL){
                matrizes->Dispersao[i][j] = (aux->amostra.Features[i] - matrizes->Medio[i])*(aux->amostra.Features[j] - matrizes->Medio[j]) + matrizes->Dispersao[i][j];
                aux = aux->prox;
            }
        }
    }

    printf("Matriz de dispersao da classe %i:\n", classe);
    for(i=0; i<qF; i++){
        for (j = 0; j<qF; j++){
            if(j == qF-1){
                printf("%f\n", matrizes->Dispersao[i][j]);
            }
            else{
            printf("%f ", matrizes->Dispersao[i][j]);
            }
        }
    }
}

void Matriz_Covariancia(Matrizes *matrizes, int qF, int classe){
    int i,j;

    for(i=0; i<qF; i++){
        for (j = 0; j<qF; j++){
        matrizes->Covariancia[i][j] = matrizes->Dispersao[i][j]/(matrizes->Qtd_Amostras_Classe-1);
        }
    }
    printf("Matriz de Covariancia da classe %i:\n", classe);
    for(i=0; i<qF; i++){
        for (j = 0; j<qF; j++){
            if(j == qF-1){
                printf("%f\n", matrizes->Covariancia[i][j]);
            }
            else{
            printf("%f ", matrizes->Covariancia[i][j]);
            }
        }
    }
}

int Inverte_Matriz(Matrizes *matrizes, int qF, int classe){
    int i,j,k;
    float v1,v2,v3;
    float **A = (float**)malloc(qF*sizeof(float*));
    if(A == NULL){
        printf("Erro");
        return 0;
    }
    else{
        for(i=0;i<qF;i++){
            A[i] = (float*)malloc((2*qF)*sizeof(float));
        }
        for(i = 0; i<qF; i++){
            for(j=0;j<qF;j++){
                A[i][j] = matrizes->Covariancia[i][j];
            }
            for(j=qF;j<(2*qF);j++){
                if(j == i+qF){
                    A[i][j] = 1;
                }
                else{
                    A[i][j] = 0;
                }
            }
        }
        /*
        for(i=0; i<qF; i++){
            for (j = 0; j<(2*qF); j++){
                if(j == (2*qF)-1){
                    printf("%f\n", A[i][j]);
                }
                else{
                printf("%f ", A[i][j]);
                }
            }
        }
        */


        for(k = 0; k<qF; k++){
            v1 = A[k][k];
            for(i=0;i<qF;i++){
                if(i != k){
                    v2 = A[i][k];
                    for(j = k; j <(2*qF); j++){
                        A[i][j] = A[i][j] - ((A[k][j]*v2)/(v1));
                    }
                }
            }
        }

        for(i=0; i<qF; i++){
            v1 = A[i][i];
            for(j=0; j<(2*qF); j++){
                A[i][j] = A[i][j]/v1;
            }
        }

        for(i = 0;i<qF;i++){
            for(j=0; j<qF; j++){
                matrizes->Covariancia_Invertida[i][j] = A[i][j+qF];
            }
        }

        /*
        for(i=0; i<qF; i++){
            for (j = 0; j<qF; j++){
                if(j == qF-1){
                    printf("%f\n", matrizes->Covariancia_Invertida[i][j]);
                }
                else{
                printf("%f ", matrizes->Covariancia_Invertida[i][j]);
                }
            }
        }
        */
    }
}

int Modulo_Determinante_Covariancia(Matrizes *matrizes, int qF, int classe){
    int i;
    float determinante;
    float **M = (float**)malloc(qF*sizeof(float*));
    if(M==NULL){
        printf("Erro");
        return 0;
    }
    else{
        for(i=0;i<qF;i++){
            M[i] = (float*)malloc(qF*sizeof(float));
        }
    }
    Copia_Matriz(qF,qF,matrizes->Covariancia,M);
    Transforma_Triangular(qF,qF,M);
    determinante = Determinante(qF,qF,M);

    printf("Determinante da matriz de Covariancia da classe %i: %f\n",classe, determinante);
    matrizes->M_Determinante_Covariancia = fabs(determinante);

    return 1;
}

int Multiplicacao_Matrizes(Amostra *Ponto, Matrizes *matrizes, float *E, int qF, int classe){
    float *A1;
    float *A2;
    int j,k;


    A1 = (float*)malloc(qF*sizeof(float));
    A2 = (float*)malloc(qF*sizeof(float));
    if(A1 == NULL || A2 == NULL){
        printf("Erro");
        return 0;
    }
    else{
        for(j=0;j<qF;j++){
            A1[j] = Ponto->Features[j] - matrizes->Medio[j];
            }
        }

        for(j=0;j<qF;j++){
            A2[j] = 0;
        }

        for(j=0;j<qF;j++){
            for(k=0;k<qF;k++){
                A2[j] = A1[k]*matrizes->Covariancia_Invertida[k][j] + A2[j];
            }
        }
        E[classe] = 0;
        for(j=0;j<qF;j++){
            E[classe] = E[classe] + A1[j]*A2[j];
        }
        printf("Expoente da classe %i: %f\n", classe, E[classe]);
        return 1;
}

int Gi(Amostra *Ponto, Matrizes *matrizes, float *E, float *gi, int qF,int classe){
    float valor;
    float ln_det;
    float Pw;

    if(Multiplicacao_Matrizes(Ponto, matrizes,E,qF,classe) == 0){
        return 0;
    }
    else{
        valor = -(E[classe]/2);
        ln_det = log(matrizes->M_Determinante_Covariancia);
        valor = valor - (ln_det/2);
        Pw = 0.333334;
        valor = valor + log(Pw);
        gi[classe] = valor;
        printf("g%i = %f\n", classe, gi[classe]);
        return 1;
    }
}

void Preenche_Ponto(Amostra *Ponto,int qF){
    int i;

    printf("Entre com as coordenadas do ponto X:\n");
    for(i=0;i<qF;i++){
        printf("x%i = ", i);
        scanf("%f", &((Ponto)->Features[i]));
    }
}



int Cria_Vetor_Expoentes(int qC, float **E){
    (*E) = (float*)malloc(qC*sizeof(float));
    if((*E) == NULL){
        printf("Erro");
        return 0;
    }
    else{
        return 1;
    }
}

int Cria_Vetor_gi(int qC, float **gi){
    (*gi) = (float*)malloc(qC*sizeof(float));
    if((*gi) == NULL){
        printf("Erro");
        return 0;
    }
    else{
        return 1;
    }
}

Amostra *Cria_Ponto(int qF){
    Amostra *Ponto = (Amostra*)malloc(sizeof(Amostra));
    if(Ponto == NULL){
        printf("Erro");
        return NULL;
    }
    else{
        Ponto->Features = (float*)malloc(qF*sizeof(float));
        if(Ponto->Features == NULL){
            return NULL;
        }
        else{
            return Ponto;
        }
    }
}



float *Libera_Vetor(float *V, int qC){

    free(V);
    return NULL;
}

Amostra *Libera_Ponto(Amostra *Ponto){

    free(Ponto->Features);
    Ponto->Features = NULL;
    free(Ponto);
    return NULL;
}


