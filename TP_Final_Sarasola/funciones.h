#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <strings.h>


typedef struct
{
    uint8_t id;
    uint8_t dest;
    uint8_t siz;
    uint8_t *data;
    uint16_t crc;
}datos_t;

int validar_parametros(int argc);



/// Ordenar paquetes por ID con qsort ///
void OrdenarID(datos_t *paquetes, uint8_t longitud);
int funcionQueCompara(const void* a_ptr, const void* b_ptr);

/// Imprimir datos en pantalla ///
void Imprimir(datos_t *paquetes, uint8_t longitud);

/// Eliminar corchetes dobles '<','>' ///
datos_t *Eliminar_Dobles(datos_t *paquetes, uint32_t cantidad_paquetes);


#endif // FUNCIONES_H_INCLUDED
