#include "funciones.h"
#include "archivos.h"
#include "memoria.h"
#include "crc_check.h"

datos_t* Levantar_Datos(datos_t *paquetes, uint32_t *longitud, const char* nombre, int dest)
{
    FILE* f = fopen(nombre, "rb");
    int j = 0; //Defino un contador para asignarle lugar a cada paquete
    uint16_t crc; //En esta variable se almacenan los valores correctos de CRC para luego compararlo en cada paquete

    uint8_t h1;
    uint8_t id;

    paquetes = Reserva_Memoria_Struct(j+1); //Reservo memoria para toda la estructura con longitud j+1

    if(f==NULL)
    {
        printf("No se puede abrir el archivo.\n"); //Verifico que el archivo no este vacio
    }
    else
    {
        while (getc(f) != EOF)
        {
            fseek(f,-1,SEEK_CUR);
            fread(&h1,sizeof(uint8_t),1,f); //Levanto el comienzo de cada paquete h1
            if(h1 == '<') //Cada paquete comienza cuando aparece '<' que es igual a 60
            {
                fread(&id,sizeof(uint8_t),1,f);
                fread(&paquetes[j].dest, sizeof(uint8_t),1,f);

                if(paquetes[j].dest == dest) //Yo soy destinatario numero 2. Solo levanto los paquetes que le corresponden a mi destinatario
                {
                    paquetes[j].id = id;
                    fread(&paquetes[j].siz, sizeof(uint8_t),1,f); //Levanto el tamaño del campo data para cada paquete

                    Reserva_Memoria(paquetes[j].siz, &paquetes[j].data);//Reservo memoria para el campo data con la longitud  size que le corresponde a cada paquete

                    if(paquetes[j].data == NULL)
                    {
                        printf("\nError en la reserva de memoria del campo data.\n");
                    }
                    else
                    {
                        fread(paquetes[j].data,sizeof(uint8_t),paquetes[j].siz,f); //Levanto todo el vector data
                    }

                    fread(&paquetes[j].crc, sizeof(uint16_t),1,f); //Levanto el crc

                    //Analizamos paquete por paquete pasandole la estructura en cada posicion
                    crc = Checked_crc(paquetes, paquetes[j].siz, j); //Almaceno el valor del crc correcto que retorna la funcion Checked_crc en la variable "crc"

                    if(crc == paquetes[j].crc) //Comparo el valor del crc correcto con el valor de crc de cada paquete
                    {
                        j++; //Solo si el crc es correcto se incrementa el contador y la variable longitud (la cual representa la cantidad de paquetes)
                        (*longitud)++;
                    }
                    //Si el crc no corresponde, eliminamos el paquete completo

                    realocacion_memoria(&paquetes, j+1); //Realoco la memoria ya que cambia la cantidad de paquetes

                }
            }
        }
    }
    fclose(f);
    return paquetes;
}


void grabar_archivo_bin(datos_t *paquetes, uint32_t cantidad_paquetes, const char* nombre)
{
    if (cantidad_paquetes >= 5)
    {
        FILE *f = fopen(nombre,"wb");
        if (f==NULL)        //Si el archivo existe, se sobreescribe automáticamente.
        {
            printf("No se puede abrir el archivo.\n");
        }
        else
        {

            for(int j=0; j<cantidad_paquetes; j++)
            {
                fwrite(paquetes[j].data,sizeof(uint8_t)*paquetes[j].siz,1,f); //Bucle que recorre cada paquete y guarda en el archivo bmp a DATA
            }

            printf("\nGuardado con exito!");
        }
        fclose(f);
    }
    else
        {
            printf("No se genero un archivo bmp compatible.");
        }
}

