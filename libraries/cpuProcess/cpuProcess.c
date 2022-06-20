#include "cpuProcess.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief Dispara las transiciones especificadas en la variable processList de cpuProcess.
 * 
 * @param cpuProcess Estructura que contiene la lista de transiciones a disparar y el numero de estas
 * @return void* NULL cuando el hilo debe terminar.
 */
void *run(cpuProcess_o *cpuProcess)
{

    if (DEBUG)
    {
        char aux2[100]="";
        strcat(aux2,"VOY A DISPARAR: ");
        char aux[10]="";
        itoa(cpuProcess->processList[0],aux,10);
        strcat(aux2,aux);
        strcat(aux2," y soy el hilo con id ");
        char aux3[10] = "";
        itoa(cpuProcess->id,aux3,10);
        strcat(aux2,aux3);
        strcat(aux2,"\n");
        stringPrint(aux2);
    }
    // sleep(1);
    int shootResult = 0;
    while (1)
    {
        for (int i = 0; i < (cpuProcess->processNum); i++)
        {
            if (DEBUG)
            {
                char aux2[100]="";
                strcat(aux2,"Nro de transicion a disparar: ");
                char aux[10]="";
                itoa(cpuProcess->processList[i],aux,10);
                strcat(aux2,aux);
                strcat(aux2," y soy el hilo con id ");
                char aux3[10] = "";
                itoa(cpuProcess->id,aux3,10);
                strcat(aux2,aux3);
                strcat(aux2,"\n");
                stringPrint(aux2);
            }
            shootResult = cpuProcess->monitor->metodos->shoot(cpuProcess->monitor, cpuProcess->processList[i]);

            if (DEBUG)
            {
                char aux2[100]="";
                strcat(aux2,"shootResult - ");
                char aux[10]="";
                itoa( shootResult,aux,10);
                strcat(aux2,aux);
                strcat(aux2," disparo- ");
                char aux3[10] = "";
                itoa(cpuProcess->processList[i],aux3,10);
                strcat(aux2,aux3);
                strcat(aux2,"\n");
                stringPrint(aux2);
            }

            if (shootResult == -1)
            {
                if (DEBUG)
                {
                    char aux2[100]="";
                    strcat(aux2,"Finalizado hilo con id: ");
                    char aux[10]="";
                    itoa(cpuProcess->id,aux,10);
                    strcat(aux2,aux);
                    strcat(aux2,"\n");
                    stringPrint(aux2);
                }
                return NULL;
            }
        }
    }
}

struct cpuProcess_metodos cpuMetodos = {
    .run = run};

/**
 * @brief Inicializa los valores de la estructura p_cpuProcess
 * 
 * @param p_cpuProcess Puntero a la estructura a inicializar
 * @param processList Vector con los indices de las transiciones a disparar
 * @param processNum Cantidad de transiciones que debe disparar
 * @param monitor Puntero al monitor que acciona la red de petri y dispara transiciones
 * @param id Id del hilo
 */
extern void new_cpuProcess(cpuProcess_o *p_cpuProcess, int *processList, int processNum, monitor_o *monitor, int id)
{
    p_cpuProcess->monitor = monitor;
    p_cpuProcess->processNum = processNum;
    p_cpuProcess->metodos = &cpuMetodos;
    p_cpuProcess->processList = processList;
    p_cpuProcess->id = id;
}