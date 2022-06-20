#include <dataStructures.h>
#include <rdp.h>
#include <monitor.h>
#include <politica.h>
#include <pthread.h>
#include <cpuProcess.h>

void loop() {}

void setup() {
   Serial.begin(115200);
   main();
}

void printVector(o_vector p_vector)
{
     Serial.print("{ ");
     for (int i = 0; i < p_vector.size; i++)
     {
         Serial.print(p_vector.vector[i]);
     }
     Serial.print("}\n");
}
int main(){
    pthread_attr_t atrib;
    pthread_t c[5];

    pthread_attr_init(&atrib);

    monitor_o mymonitor;
    rdp_o rdp;
    monitor_o *monitor = &mymonitor;
    cpuProcess_o tShooter[5];

    int *shootArray[2];

    int shootSequence1[2] = {0, 2}; // Productor
    int shootSequence2[2] = {1, 3}; // Consumidor

    shootArray[0] = shootSequence1;
    shootArray[1] = shootSequence2;

    pthread_mutex_t mutex;
    pthread_cond_t espera[TRANSITIONS];
    int boolQuesWait[TRANSITIONS] = {0};

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < TRANSITIONS; i++)
    {
        pthread_cond_init(&espera[i], NULL);
    }
    if(new_rdp(&rdp)==ALLOC_ERROR)
    {
        Serial.print("ERROR DE ALOCACION\n");
        exit(1);
    }
    if(new_monitor(&mymonitor, mutex, espera, boolQuesWait, &rdp)==ALLOC_ERROR)
    {
        Serial.print("ERROR DE ALOCACION\n");
        exit(1);
    }

    for (int i = 0; i < PRODUCTOR; i++)
    {
        new_cpuProcess(&tShooter[i], shootArray[0], 2, monitor, i);
    }

    for (int i = PRODUCTOR; i < PRODUCTOR + CONSUMIDOR; i++)
    {
        new_cpuProcess(&tShooter[i], shootArray[1], 2, monitor, i);
    }

    for (int i = 0; i < (PRODUCTOR + CONSUMIDOR); i++)
        pthread_create(&c[i], &atrib, (void * (*)(void*))(&tShooter[i])->metodos->run, (cpuProcess_o *)&tShooter[i]);

    for (int i = 0; i < (PRODUCTOR + CONSUMIDOR); i++)
    {
        pthread_join(c[i], NULL);
    }

    if (DEBUG)
        Serial.print("\nFinalizo la ejecucion\n");
        
    monitor->metodos->cleanMonitor(monitor);
    rdp.metodos->cleanRDP(&rdp);
}
