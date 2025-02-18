
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define maxSubThreads 4
#define maxEntrada 100000



typedef struct {
     int limEsq;
     int limDir;
     int n_subs;
} subVetores;
 int ventorInput[maxEntrada];
 int aux[maxEntrada];


 void ordenaVetores(int limEsq,int limDir,int media){
   int id=media+1;
   int countEsq=limEsq;
   int i;
   for(i = limEsq ; countEsq <= media && id <= limDir ; i++){
       if(ventorInput[countEsq] >= ventorInput[id]){
          aux[i] = ventorInput[id];
          id++;
         }
         else{
            aux[i] = ventorInput[countEsq];
           countEsq++;
         }
     }
     while(countEsq <= media){
         aux[i] = ventorInput[countEsq];
         i++;
         countEsq++;
     }
     while(id <= limDir){
         aux[i] = ventorInput[id];
         i++;
         id++;
     }
     for(i = limEsq ; i <= limDir ; i++){
         ventorInput[i] = aux[i];
     }
     for(i = limEsq ; countEsq <= media && id <= limDir ; i++){
         if(ventorInput[countEsq] >= ventorInput[id]){
            aux[i] = ventorInput[id];
            id++;
           }
           else{
              aux[i] = ventorInput[countEsq];
             countEsq++;
           }
       }
       while(countEsq <= media){
           aux[i] = ventorInput[countEsq];
           i++;
           countEsq++;
       }
       while(id <= limDir){
           aux[i] = ventorInput[id];
           i++;
           id++;
       }
       for(i = limEsq ; i <= limDir ; i++){
           ventorInput[i] = aux[i];
       }
       return;
 }


 void *mergeSort(void * args){
   subVetores * margensVetor = args;
   pthread_t threadPivo, threadFinal;
 	if(margensVetor->limEsq < margensVetor->limDir){
    subVetores *dir = malloc(sizeof (subVetores));
    subVetores *esq = malloc(sizeof (subVetores));
 		 int media = (margensVetor->limEsq+margensVetor->limDir)/2;


 		esq->limEsq = margensVetor->limEsq;
 		esq->limDir = media;
 		esq->n_subs = margensVetor->n_subs+1;

 		dir->limEsq = media+1;
 		dir->limDir = margensVetor->limDir;
 		dir->n_subs = margensVetor->n_subs+1;
 		if(margensVetor->n_subs <= maxSubThreads){
 			pthread_create(&threadPivo, NULL, mergeSort, esq);
       pthread_join(threadPivo, NULL);
 			pthread_create(&threadFinal, NULL, mergeSort, dir);
       pthread_join(threadFinal, NULL);
 		}else{
       mergeSort(esq);
       mergeSort(dir);
     }




 		ordenaVetores(margensVetor->limEsq,margensVetor->limDir, media);
 	}

 	return NULL;
 }


int main() {
	 int size = 0;
   char virgulas;
    while (scanf(" %d%c ", &ventorInput[size],&virgulas) != EOF){
      size++;
    }

	subVetores *args = malloc(sizeof (subVetores));
	args->limEsq = 0;
	args->limDir = size-1;
	args->n_subs = 1;

  	mergeSort(args);

    for(int i = 0 ; i < size-1 ; i++)
    	printf("%d ", ventorInput[i]);
    printf("%d\n" , ventorInput[size-1]);

    return 0;

}
