
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define maxSubThreads 4
#define maxEntrada 100000



typedef struct {
     int ini;
     int fim;
     int nivel;
} subVetores;
 int ventorInput[maxEntrada];
 int aux[maxEntrada];

 void *mergeSort(void * args){
   subVetores * margensVetor = args;
   pthread_t threadPivo, threadFinal;
 	if(margensVetor->ini < margensVetor->fim){

 		 int media = (margensVetor->ini+margensVetor->fim)/2;

 		subVetores *esq = malloc(sizeof (subVetores));
 		esq->ini = margensVetor->ini;
 		esq->fim = media;
 		esq->nivel = margensVetor->nivel+1;
 		subVetores *dir = malloc(sizeof (subVetores));
 		dir->ini = media+1;
 		dir->fim = margensVetor->fim;
 		dir->nivel = margensVetor->nivel+1;
 		if(margensVetor->nivel <= maxSubThreads){
 			pthread_create(&threadPivo, NULL, mergeSort, esq);
       pthread_join(threadPivo, NULL);
 			pthread_create(&threadFinal, NULL, mergeSort, dir);
       pthread_join(threadFinal, NULL);
 		}else{
       mergeSort(esq);
       mergeSort(dir);
     }

     int   id = media+1 ;
 		 int ie=margensVetor->ini;

      int i;
 		for(i = margensVetor->ini ; ie <= media && id <= margensVetor->fim ; i++){
 	    	if(ventorInput[ie] >= ventorInput[id]){
           aux[i] = ventorInput[id];
           id++;
 	      	}
 	      	else{
             aux[i] = ventorInput[ie];
 	        	ie++;
 	      	}
 	    }
 	    while(ie <= media){
 	      	aux[i] = ventorInput[ie];
 	      	i++;
 	      	ie++;
 	    }
 	    while(id <= margensVetor->fim){
 	      	aux[i] = ventorInput[id];
 	      	i++;
 	      	id++;
 	    }
 	    for(i = margensVetor->ini ; i <= margensVetor->fim ; i++){
 	      	ventorInput[i] = aux[i];
 	    }
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
	args->ini = 0;
	args->fim = size-1;
	args->nivel = 1;

  	mergeSort(args);

    for(int i = 0 ; i < size-1 ; i++)
    	printf("%d ", ventorInput[i]);
    printf("%d\n" , ventorInput[size-1]);

    return 0;

}
