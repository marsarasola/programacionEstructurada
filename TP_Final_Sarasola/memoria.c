#include "memoria.h"
#include "funciones.h"
#include "archivos.h"
#include "crc_check.h"

//Reserva de memoria para la estructura
datos_t* Reserva_Memoria_Struct(uint8_t size)
{
    datos_t* dato = (datos_t*)malloc(size*sizeof(datos_t));
    if (dato==NULL)
    {
        printf("Error en la reserva de memoria.\n");
    }

    return dato;
}

void Reserva_Memoria(uint8_t longitud, uint8_t **dato)
{
    *dato = (uint8_t*)calloc(longitud, sizeof(uint8_t));

}

void realocacion_memoria(datos_t **dato, uint8_t longitud)
{
    *dato = (datos_t*)realloc(*dato,longitud*sizeof(datos_t));

}

void liberar_memoria(datos_t *paquetes, uint32_t cantidad_paquetes)
{
    for(int i=0; i<cantidad_paquetes; i++)
    {
         free(paquetes[i].data);
    }
    free(paquetes);
}
