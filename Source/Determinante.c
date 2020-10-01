#include "../Header/Bayes_Classifier.h"

void Copia_Matriz(int l, int c, float **M, float **C){
    int i,j;

    ///printf("%f %f %f\n", Cov[0][0], Cov[0][1], Cov[0][2], Cov[0][3]);
    /*
    for(i = 0; i<l; i++){
        for(j = 0; j<c; j++){
            C[i][j] = 0;
        }
    }
    */
    for(i = 0; i<l; i++){
        for(j = 0; j<c; j++){
            C[i][j] = M[i][j];
        }
    }
    /*
     for(i=0; i<l; i++){
        for (j = 0; j<c; j++){
            if(j == c-1){
                printf("%f\n", C[i][j]);
            }
            else{
            printf("%f ", C[i][j]);
            }
        }
    }
    */
}

void Transforma_Triangular(int l, int c, float **M){
    int i,j,k;
    float v1,v2;

    for(k=0; k<c; k++){
        v1 = M[k][k];
        ///printf("\n%f\n\n",v1);
        if( v1!= 0){
            for(i=0;i<l;i++){
                ///printf("A");
                if(i != k){
                    v2 = M[i][k];
                    for(j = k; j<c; j++){
                        M[i][j] = M[i][j] - ((M[k][j]*v2)/(v1));
                        ///printf("%f\n",M[i][j]);

                    }
                }
            }
        }
        else{
            break;
        }
    }
    /*
    for(i=0; i<l; i++){
        for (j = 0; j<c; j++){
            if(j == c-1){
                printf("%f\n", M[i][j]);
            }
            else{
            printf("%f ", M[i][j]);
            }
        }
    }
    */

}

float Determinante(int l, int c, float **M){
    float determinante = 1;
    int i;

    for(i=0; i<l;i++){
        determinante = determinante*M[i][i];
    }

    return determinante;
}
