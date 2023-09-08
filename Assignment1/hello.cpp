#include <stdio.h>
#include <omp.h>
using namespace std;
void printHello();
int main(){
    #pragma omp parallel num_threads(8)
    printHello();
    return 0;
}
void printHello(){
    int threadNum = omp_get_thread_num();
    printf("Printing Hello from %d \n",threadNum);
}

