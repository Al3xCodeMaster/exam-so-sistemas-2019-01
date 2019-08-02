#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"
#include "mycommon.h"

volatile int counter = 0;
puerta miPuerta; 
int loops;

void *worker(void *arg) {
    int i;
    cerrar_puerta(miPuerta);
    for (i = 0; i < loops; i++) {    
    counter++;
    }
    abrir_puerta(miPuerta);
    return NULL;
}

int main(int argc, char *argv[]) {
    double timeInit = 0;
    double timeFinal = 0;
    double result = 0;
    if (argc != 2) { 
	fprintf(stderr, "usage: threads <loops>\n"); 
	exit(1); 
    } 
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    crear_puerta(miPuerta);
    printf("Initial value : %d\n", counter);
    timeInit = GetTime();
    Pthread_create(&p1, NULL, worker, NULL); 
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    timeFinal = GetTime();
    printf("Final value   : %d\n", counter);
    result = timeFinal - timeInit;
    printf("Program time: %f\n",result);
    destruir_puerta(miPuerta);
    return 0;
}
