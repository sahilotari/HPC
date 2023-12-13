#include <stdio.h>
#include <omp.h>
#include <time.h>
#define N 4
void matrixVectorMult(int mat[N][N],int vec[N],int result[N]){
    #pragma omp parallel for
    for(int i=0;i<N;i++){
        result[i]=0;
        for(int j=0;j<N;j++){
            result[i]+=mat[i][j]*vec[j];
        }
    }
}
int main(){
    double startTime = omp_get_wtime();
    int mat[N][N];
    int c=1;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            mat[i][j] = c++;
        }
    }
    int vec[N];
    for(int i=1; i<=N; i++){
        vec[i-1] = i;
    }
    int result[N];
    matrixVectorMult(mat,vec,result);
    printf("Matrix-Vector Multiplication Result:\n");
    for(int i=0;i<N;i++){
        printf("%d",result[i]);
    }
    printf("\n");
    double endTime = omp_get_wtime();
    printf("Execution time:%f",endTime-startTime);
    return 0;
}