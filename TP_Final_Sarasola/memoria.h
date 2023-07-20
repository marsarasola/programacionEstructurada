#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED
#include "funciones.h"

/// Reserva y realocacion de memoria ///
datos_t* Reserva_Memoria_Struct(uint8_t sizee);
void realocacion_memoria(datos_t **dato, uint8_t longitud);
void Reserva_Memoria(uint8_t longitud, uint8_t **dato);

/// Liberar memoria ///
void liberar_memoria(datos_t *paquetes, uint32_t cantidad_paquetes);

#endif // MEMORIA_H_INCLUDED
