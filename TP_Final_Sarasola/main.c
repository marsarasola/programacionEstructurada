#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "funciones.h"
#include "memoria.h"
#include "archivos.h"
#include "crc_check.h"
#include "crc_16.h"


int main(int argc, char* argv[])
{
    if(validar_parametros(argc)!=0)
    {
        printf("\n Error. No se estan pasando la cantidad de argumentos necesarios.\n");
    }
    else
    {

        datos_t *paquetes = NULL;
        uint32_t cantidad_de_paquetes = 0; //defino cantidad de paquetes 0, lo paso a la funcion levantar datos por referencia para que se guarde la cantidad total de paquetes luego de recorrer todo el archivo
        int dest; //Aca se guardara el numero de destinatario, en mi caso el 2
        sscanf(argv[1], "%d", &dest);

        paquetes = Levantar_Datos(paquetes, &cantidad_de_paquetes, argv[2], dest); //Levantamos los datos del archivo bin, brindado por la catedra

        OrdenarID(paquetes, cantidad_de_paquetes); //Orden de los paquetes segun cada id
        //Imprimir(paquetes, cantidad_de_paquetes); //Muestra en pantalla todos los paquetes ordenamos por id

        paquetes = Eliminar_Dobles(paquetes, cantidad_de_paquetes); //Elimina cuando encuentra '<' o '>' seguidos
        grabar_archivo_bin(paquetes, cantidad_de_paquetes, argv[3]); //Crea la imagen bmp

        liberar_memoria(paquetes, cantidad_de_paquetes); //Libera memoria
    }

    return 0;
}

