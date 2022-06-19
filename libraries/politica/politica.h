#ifndef _POLITICA_
#define _POLITICA_

#include "rdp.h"

typedef struct politica politica_o;

/**
 * @brief Estructura donde se definen los metodos de la estructura politica.
 * 
 */
struct politica_metodos
{

    int (*signalPolitic)(politica_o *, int *boolQuesWait, int index);
};

/**
 * @brief Estructura que representa la clase politica, encargada de decidir que hilo debe despertarse.
 *  rdp: Puntero a una estructura red de petri.
 *  metodos: Estructura con punteros a funciones.
 */
struct politica
{
    rdp_o *rdp;

    const struct politica_metodos *metodos;
};

// Funciones
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void new_politica(politica_o *p_politica, rdp_o *rdp);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif