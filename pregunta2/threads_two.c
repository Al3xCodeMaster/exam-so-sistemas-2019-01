#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"
#include "mycommon.h"
#include <unistd.h>

volatile float v = 0;
puerta miPuerta;
pthread_cond_t operationSucess;

void *worker1(void *arg) 
{
	
    sleep(2);
    int z = 25;
    int y = 350;
    cerrar_puerta(miPuerta);
    v = (float) z/y;
    pthread_cond_signal(&operationSucess); 
    abrir_puerta(miPuerta);
    return NULL;
}

void *worker2(void *arg) 
{    
    int x = 1250;
    cerrar_puerta(miPuerta);
    pthread_cond_wait(&operationSucess,&miPuerta);
    v = x*v;
    abrir_puerta(miPuerta);
    return NULL;
}

int main(int argc, char *argv[])
{
    //if (argc != 2) { 
	//fprintf(stderr, "usage: threads <loops>\n"); 
	//exit(1); 
    //} 
    pthread_t p1, p2;
    crear_puerta(miPuerta);
    Pthread_create(&p1, NULL, worker1, NULL); 
    Pthread_create(&p2, NULL, worker2, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value   : %f\n", v);
    destruir_puerta(miPuerta);
    return 0;
}
