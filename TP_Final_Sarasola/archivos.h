#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "funciones.h"

/// Recuperar datos del archivo bin ///
datos_t *Levantar_Datos(datos_t *paquetes, uint32_t *longitud, const char* nombre, int dest);

/// Crear imagen bmp ///
void grabar_archivo_bin(datos_t *paquetes, uint32_t cantidad_paquetes, const char* nombre);

#endif // ARCHIVOS_H_INCLUDED
