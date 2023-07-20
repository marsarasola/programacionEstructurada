#include "funciones.h"
#include "archivos.h"
#include "memoria.h"
#include "crc_16.h"

uint16_t Checked_crc(datos_t *paquetes, uint8_t size, int cont)
{
    uint8_t *input; //Creo un nuevo vector en el cual guardo id, dest, size y data
    Reserva_Memoria(size+3,&input); //Reservo memoria con el tamaño de size de cada paquete + 3 por los datos de id, dest, size
    uint16_t crc;

    if(input == NULL)
    {
        printf("\nError en la reserva de memoria.\n");
    }
    else
    {
        input[0] = paquetes[cont].id; //Almaceno todos los datos
        input[1] = paquetes[cont].dest;
        input[2] = size;

        for(int j=3; j<size+3; j++)
        {
            input[j] = paquetes[cont].data[j-3];
        }

    }

    //calculate_checksum recibe el vector input con los datos recien almacenados y su tamaño
    crc = calculate_checksum(input, size+3); //La funcion nos retorna el dato de crc que corresponde a cada paquete
    free(input); //Liberamos memoria
    return crc; //Retornamos el valor correcto de crc para poder comparar en la funcion Levantar_Datos()
}
