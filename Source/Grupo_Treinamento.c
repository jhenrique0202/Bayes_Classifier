#include "../Header/Bayes_Classifier.h"

char **Libera_value(char **value, int q_Features){
    int i;

    for(i=0;i<q_Features;i++){
        free((value)[i]);
    }
    free(value);
    return NULL;
}



Lista_Amostras *Libera_Lista_Amostras_In(Lista_Amostras *lista_amostras){
    Lista_Amostras *aux;
    float *aux2;

    while(lista_amostras != NULL){
        aux = lista_amostras;
        (lista_amostras) = (lista_amostras)->prox;

        aux2 =  aux->amostra.Features;
        free(aux2);
        aux2 = NULL;

        free(aux);
        aux = NULL;
    }
    free(lista_amostras);
    return NULL;
}

Lista_Amostras **Libera_Lista_Amostras_Out(Lista_Amostras **lista_amostras, int q_Features, int q_Classes){
    int i;

    for(i=0;i<q_Classes;i++){
        lista_amostras[i] = Libera_Lista_Amostras_In(lista_amostras[i]);
    }
    free(lista_amostras);
    return NULL;
}



Matrizes *Libera_Matrizes_In(Matrizes *matrizes, int q_Features){
    int i;

    free(matrizes->Medio);
    free(matrizes->Desvio_padrao);
    matrizes->Medio = matrizes->Desvio_padrao = NULL;

    for(i=0;i<q_Features;i++){
        free(matrizes->Covariancia[i]);
        free(matrizes->Covariancia_Invertida[i]);
        free(matrizes->Dispersao[i]);
    }

    free(matrizes->Covariancia);
    free(matrizes->Covariancia_Invertida);
    free(matrizes->Dispersao);

    matrizes->Covariancia = matrizes->Covariancia_Invertida = matrizes->Dispersao = NULL;
    return NULL;
}

Matrizes **Libera_Matrizes_Out(Matrizes **matrizes, int q_Features, int q_Classes){
    int i;
    for(i=0;i<q_Classes;i++){
        matrizes[i] = Libera_Matrizes_In(matrizes[i], q_Features);
    }
    free(matrizes);
    return NULL;
}



void Divide(char simbolo, char texto[50], char **resultado){
    int i,j,k,l,m;
    i = j = k = m = 0;
    while(1){
        while(texto[i] != simbolo && texto[i] != '\0'){
            i++;
        }
        l = j;
        while(l<i){
            resultado[k][m] = texto[l];
            m++;
            l++;
        }
        resultado[k][m]= '\0';
        ///printf("%s\n", resultado[k]);
        m = 0;
        k++;
        if(texto[i] == '\0'){
            break;
        }
        i++;
        j = i;
    }
    }

int Preenche_Lista_Amostras(Lista_Amostras **lista_amostras,Matrizes **matrizes,int q_Classes,int q_Features){
    FILE *f;
    char read[50],Classe_anterior[50];
    char **value;
    int i;
    float j;

    value = (char**)malloc(q_Features*sizeof(char*));
    if(value == NULL){
        printf("Erro");
        return 0;
    }
    else{
        for(i=0;i<q_Features+1;i++){
            value[i] = (char*)malloc(50*sizeof(char));
            value[i][0] = '\0';
        }
        f = fopen(".\\Data\\Iris.txt", "r");
        if(f == NULL){
            printf("Erro");
            return 0;
        }
        else{
            i = 0;
            j = 0;
            if(fscanf(f, "%s", &read) == 1){
                Divide(',',read,value);
                strcpy(Classe_anterior,value[q_Features]);
                ///printf("%s\n", Classe_anterior);
                if(Adiciona((&lista_amostras[i]), i,q_Features,value)){
                    j++;
                    while(fscanf(f, "%s", &read) == 1){
                        ///printf("%s\n", read);
                        Divide(',',read,value);
                        ///printf("%s\n", Classe_anterior);
                        ///printf("%s %s %s %s %s\n", value[0],value[1],value[2],value[3],value[4]);
                        if(strcmp(value[4], Classe_anterior) == 0){
                            ///printf("%p", V_Classes[0]);
                            if(Adiciona((&lista_amostras[i]), i,q_Features,value)){
                                j++;
                            }
                            else{
                                return 0;
                            }
                        }
                        else{
                            matrizes[i]->Qtd_Amostras_Classe = j;
                            ///printf("%f\n", (*QtdAmostras)[i]);
                            j = 0;
                            i++;
                            strcpy(Classe_anterior,value[q_Features]);
                            if(Adiciona((&lista_amostras[i]), i,q_Features,value)){
                               j++;
                            }
                            else{
                                return 0;
                            }
                        }
                    }
                    matrizes[i]->Qtd_Amostras_Classe = j;
                    ///printf("%f\n", (*QtdAmostras)[i]);
                    fclose(f);
                    value = Libera_value(value, q_Features);
                    return 1;
                }
                else{
                    printf("Erro");
                    return 0;
                }
            }
        }
    }
}

int Adiciona(Lista_Amostras **lista_amostras,int N_Classe, int q_Features, char **V_valores){
    int i;
    Lista_Amostras *Novo = (Lista_Amostras*)malloc(sizeof(Lista_Amostras));

    Novo->amostra.Features = (float*)malloc(q_Features*sizeof(float));
    if(Novo->amostra.Features == NULL){
        printf("Erro");
        return 0;
    }
    else{
        for(i= 0; i<q_Features; i++){
            Novo->amostra.Features[i] = atof(V_valores[i]);
            ///printf("%f\n", Novo->Classe.Features[i]);
        }
        Novo->amostra.N_Classe = N_Classe;
        Novo->prox = (*lista_amostras);
        (*lista_amostras) = Novo;
        return 1;
    }
}

void Imprime(int qf, Lista_Amostras *lista_amostras){
    Lista_Amostras *aux = lista_amostras;
    int i;
    printf("Amostras da classe %i:\n", aux->amostra.N_Classe);
    while(aux != NULL){
        for(i = 0; i<qf; i++){
            printf("%f ", aux->amostra.Features[i]);
        }
        printf("%i\n", aux->amostra.N_Classe);
        aux = aux->prox;
    }
}

Lista_Amostras **Cria_Lista_Amostras(int qC){
    int i;
    Lista_Amostras **lista_amostra =(Lista_Amostras**)malloc(qC*sizeof(Lista_Amostras*));
    if(lista_amostra == NULL){
        printf("Erro\n");
        return NULL;
    }
    else{
        for(i=0;i<qC;i++){
            lista_amostra[i] = NULL;
        }
        return lista_amostra;
    }
}



int Cria_Medio(int qFeatures,Matrizes **matrizes, int N_Classe){

    (matrizes[N_Classe])->Medio = (float*)malloc(qFeatures*sizeof(float));
    if((matrizes[N_Classe])->Medio == NULL){
        return 0;
    }
    else{
        (matrizes[N_Classe])->Medio[0] = 0;
        return 1;
    }
}

int Cria_Desvio_Padrao(int qFeatures,Matrizes **matrizes,int N_Classe){

    (matrizes[N_Classe])->Desvio_padrao = (float*)malloc(qFeatures*sizeof(float));
    if((matrizes[N_Classe])->Desvio_padrao == NULL){
        return 0;
    }
    return 1;
}

int Cria_Dispersao(int qFeatures,Matrizes **matrizes,int N_Classe){
    int i;

    matrizes[N_Classe]->Dispersao = (float**)malloc(qFeatures*sizeof(float*));
    if(matrizes[N_Classe]->Dispersao == NULL){
        return 0;
    }
    for(i=0;i<qFeatures;i++){
        matrizes[N_Classe]->Dispersao[i] = (float*)malloc(qFeatures*sizeof(float));
    }
    return 1;

}

int Cria_Covariancia(int qFeatures,Matrizes **matrizes,int N_Classe){
    int i;

    matrizes[N_Classe]->Covariancia = (float**)malloc(qFeatures*sizeof(float*));
    if(matrizes[N_Classe]->Covariancia == NULL){
        return 0;
    }
    for(i=0;i<qFeatures;i++){
        matrizes[N_Classe]->Covariancia[i] = (float*)malloc(qFeatures*sizeof(float));
    }
    return 1;
}

int Cria_Covariancia_Invertida(int qFeatures,Matrizes **matrizes,int N_Classe){
    int i;

    matrizes[N_Classe]->Covariancia_Invertida = (float**)malloc(qFeatures*sizeof(float*));
    if(matrizes[N_Classe]->Covariancia_Invertida == NULL){
        return 0;
    }
    for(i=0;i<qFeatures;i++){
        matrizes[N_Classe]->Covariancia_Invertida[i] = (float*)malloc(qFeatures*sizeof(float));
    }
    return 1;
}

Matrizes **Cria_Vetor_Matrizes(int q_Classes,int q_Features){

    int i,j;
    Matrizes **Vetor_Matrizes = (Matrizes**)malloc(q_Classes*sizeof(Matrizes*));

    if(Vetor_Matrizes == NULL){
        printf("Erro");
        return NULL;
    }
    else{
        for(i=0;i<q_Classes;i++){
            Vetor_Matrizes[i] = (Matrizes*)malloc(sizeof(Matrizes));
            j=Cria_Medio(q_Features,Vetor_Matrizes,i);
            if(j == 0){
                printf("Erro");
                return NULL;
            }
            j=Cria_Desvio_Padrao(q_Features,Vetor_Matrizes,i);
            if(j == 0){
                printf("Erro");
                return NULL;
            }
            j = Cria_Dispersao(q_Features,Vetor_Matrizes,i);
            if(j == 0){
                printf("Erro");
                return NULL;
            }
            j = Cria_Covariancia(q_Features,Vetor_Matrizes,i);
            if(j == 0){
                printf("Erro");
                return NULL;
            }
            j = Cria_Covariancia_Invertida(q_Features,Vetor_Matrizes,i);
            if(j == 0){
                printf("Erro");
                return NULL;
            }
        }
        return Vetor_Matrizes;
    }
}

