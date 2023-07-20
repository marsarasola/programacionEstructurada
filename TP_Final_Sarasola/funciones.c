#include "funciones.h"
#include "crc_16.h"
#include "memoria.h"
#include "archivos.h"
#include "crc_check.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int validar_parametros(int argc)
{
    int aux=0;

    if(argc!=4)
    {
        aux=1;
    }
    return aux;
}

datos_t *Eliminar_Dobles(datos_t *paquetes, uint32_t cantidad_paquetes)
{
    for (int i=0; i<cantidad_paquetes; i++) //El bucle con contador i recorre todos los paquetes
    {
        for(int j=0; j<paquetes[i].siz; j++) //El bucle con el contador j recorre todo el campo data
        {
            if((paquetes[i].data[j] == '>' || paquetes[i].data[j] == '<') && (j<paquetes[i].siz)) //Busco la aparicion de '<' o '>', si los encuentra entran en la condicion
            {
                if(paquetes[i].data[j] == paquetes[i].data[j+1]) //Si data en la posicion j = '<' o '>' y la posicion que le sigue es igual entra en la condicion
                {
                    for(int x=j; x<paquetes[i].siz-1; x++) //Bucle con contador x para eliminar uno de los corchetes dobles y pisar la posicion
                    {
                        paquetes[i].data[x]=paquetes[i].data[x+1];
                    }
                    paquetes[i].siz--; //Restamos uno al tamaño siz del campo data, ya que eliminamos los corchetes dobles y disminuye su tamaño
                }
            }
        }
        realocacion_memoria(&paquetes, paquetes[i].siz); //Realocamos la memoria con el nuevo tamaño
    }

    return paquetes; //Retorno la estructura con los corchetes dobles eliminados para poder levantar la imagen bmp corretamente
}

void OrdenarID(datos_t *paquetes, uint8_t longitud)
{
    qsort(paquetes,longitud,sizeof(datos_t),funcionQueCompara); //Utilizo qsort: (estructura, la cantidad de paquetes, tamaño de cada elemento)
    //Funcion que compara: ordena el vector de forma ascendente
}

int funcionQueCompara(const void* a_ptr, const void* b_ptr)
{
    int aux;
    datos_t a=*(datos_t*)a_ptr; //Casteo a enteros
    datos_t b=*(datos_t*)b_ptr;

    if(a.id<b.id) //Compara los tamaños de id correspondiente a cada paquete
    {
        aux = -1;  //Si a<b retorna -1
    }
    else if(a.id>b.id)
    {
        aux = 1;  //Si a>b retorna 1
    }
    else
    {
        aux = 0;  //Si son iguales retorna 0
    }

    return aux;
}

//Imprimir en pantalla
void Imprimir(datos_t *paquetes, uint8_t longitud)
{
    for(int j=0; j<longitud; j++)
    {
        printf("\n\n%d %d %d ", paquetes[j].id, paquetes[j].dest, paquetes[j].siz);
        for(int i=0; i<paquetes[j].siz; i++)
        {
            printf(" %d ", paquetes[j].data[i]);
        }
        printf(" %d ", paquetes[j].crc);
    }
}



