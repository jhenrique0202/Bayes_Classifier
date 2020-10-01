#include "../Header/Bayes_Classifier.h"

int main(){
    int qC,qF,i,j,k;
    float *E;
    float *gi;
    Lista_Amostras **lista_amostras;
    Matrizes **matrizes;
    Amostra *Ponto;

    printf("--------------------------------------------------\n");
    printf("\nClassificador de Bayes em C\n");
    printf("\n-------------------------------------------------\n");

    printf("Informe a quatidade de Classes de treinamento: ");
    scanf("%i", &qC);
    printf("Informe a quatidade de Caracteristicas de cada elemento: ");
    scanf("%i", &qF);

    lista_amostras = Cria_Lista_Amostras(qC);
    matrizes = Cria_Vetor_Matrizes(qC,qF);
    if(lista_amostras == NULL || matrizes == NULL){
        return 0;

    }
    else{
        if(Preenche_Lista_Amostras(lista_amostras,matrizes,qC,qF)){
            for(i=0;i<qC;i++){
                printf("\n-------------------\n\n");
                Imprime(qF,lista_amostras[i]);
            }
            printf("\n-------------------\n\n");

            for(i=0;i<qC;i++){
                Media(lista_amostras[i],matrizes[i],qF,i);
            }
            printf("\n-------------------\n\n");

            for(i=0;i<qC;i++){
                Desvio_Padrao(lista_amostras[i],matrizes[i],qF,i);
            }
            printf("\n-------------------\n\n");

            for(i=0;i<qC;i++){
                Matriz_Dispersao(lista_amostras[i],matrizes[i],qF,i);
            }
            printf("\n-------------------\n\n");

            for(i=0;i<qC;i++){
                Matriz_Covariancia(matrizes[i],qF,i);
            }
            printf("\n-------------------\n\n");

            for(i=0;i<qC;i++){
                j = Inverte_Matriz(matrizes[i],qF,i);
                if(j==0){
                    return 0;
                }
            }
            for(i=0;i<qC;i++){
                j = Modulo_Determinante_Covariancia(matrizes[i],qF,i);
                if(j == 0){
                    return 0;
                }
            }
            printf("\n-------------------\n\n");

            if(Cria_Vetor_Expoentes(qC,&E) == 0){
                return 0;
            }
            else{
                if(Cria_Vetor_gi(qC,&gi)==0){
                    return 0;
                }
                else{
                    Ponto = Cria_Ponto(qF);
                    if(Ponto == NULL){
                        return 0;
                    }
                    else{
                        k=1;
                        while(k == 1){
                            Preenche_Ponto(Ponto,qF);
                            for(i=0;i<qC;i++){
                                if(Gi(Ponto,matrizes[i],E,gi,qF,i) == 0){
                                    return 0;
                                }
                            }
                            printf("Deseja calcular outro ponto ?\n");
                            printf("1 - Sim | 0 - Nao: ");
                            scanf("%i", &k);
                        }
                        lista_amostras = Libera_Lista_Amostras_Out(lista_amostras,qF,qC);
                        matrizes = Libera_Matrizes_Out(matrizes, qF,qC);
                        Ponto = Libera_Ponto(Ponto);
                        gi = Libera_Vetor(gi, qC);
                        E = Libera_Vetor(E, qC);
                    }
                }
            }
        }
    }
    return 0;
}
