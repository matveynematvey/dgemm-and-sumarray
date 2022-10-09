#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>

const int N = 10, t_count = 2;

typedef struct data{
    double s;
    double* a;
    int thread_num;
} data;

void* SumArray(void *p)
{
   data* ptr = (data*)p;
    int thread_part = ptr->thread_num;
  
    for (int i = 0; i < (N / t_count); i++)
        ptr->s += ptr->a[i];
}

void FillArray(const int N, double *V) {
   for (int i = 0; i < N; i++)    
         V[i] = i;
}

int main() {
   double totalSum = 0;
   double *A = (double*)malloc(N * sizeof(double));   //array to sum

   data arr[t_count];                                 //struct arr with part of array and thread_num
   pthread_t threads[t_count];                        

   FillArray(N, A);

   //init struct arr
   for (int i = 0; i < t_count; i++) {
      arr[i].thread_num = i;
      arr[i].s = 0;
      arr[i].a = &A[i*N/t_count];
   }

   for (int i = 0; i < t_count; i++)
      pthread_create(&threads[i], NULL, SumArray, &arr[i]);

   for (int i = 0; i < t_count; i++)
      pthread_join(threads[i], NULL);

   for (int i = 0; i < t_count; i++)
      totalSum += arr[i].s;

   printf("Sum of array: %f", totalSum);
}