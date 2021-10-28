#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "localidad.h"
#include "pedido.h"
#include "cliente.h"
#define SECTOR 10
#define MINSALARY 1
#define MAXSALARY 300000
#define OCUPADO 0
#define LIBRE 1
#define PENDIENTE 0
#define COMPLETADO 1

int localidadNextId();

int localidad_inicializarArrayLocalidades(eLocalidad* arrayLocalidades, int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayLocalidades != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
        	arrayLocalidades[i].id = -1;
            strcpy(arrayLocalidades[i].descripcion,"");
            arrayLocalidades[i].isEmpty = LIBRE;
        }
    }
    return retorno;
}

int localidad_nuevaLocalidad(eLocalidad* arrayLocalidades, int limite, int index){

    int retorno = -1;
    char descripcionAux[40];
    int id;

    if(limite > 0 && arrayLocalidades != NULL){

        retorno = -2;

        if(getStringLetras("\nIngrese localidad: ", descripcionAux)){

        	id = localidadNextId();
            normalizeTextString(descripcionAux);
            strcpy(arrayLocalidades[index].descripcion,descripcionAux);

            arrayLocalidades[index].isEmpty = OCUPADO;
            arrayLocalidades[index].id = id;
            printf("\n\tLocalidad Agregada...");
            retorno = 0;
        }
    }

    if(retorno != 0){

        printf("\nError\n");
    }

    return retorno;

}

int localidad_buscarPosicionLibre(eLocalidad* arrayLocalidades,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayLocalidades != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayLocalidades[i].isEmpty == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int localidad_imprimirLocalidades(eLocalidad* arrayLocalidades,int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayLocalidades != NULL)
    {
        retorno = 0;
        printf("\n\n\tNombre Localidad\tID Localidad");
        printf("\n\t------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayLocalidades[i].isEmpty)
            {

           		printf("\n\t%s\t\t%d",arrayLocalidades[i].descripcion,arrayLocalidades[i].id);
           	}
        }
    }
    return retorno;
}


int localidad_altaForzada(eLocalidad* arrayLocalidades,int limite,char* descripcion)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayLocalidades != NULL)
    {
        i = localidad_buscarPosicionLibre(arrayLocalidades,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(arrayLocalidades[i].descripcion,descripcion);
            //------------------------------
            //------------------------------
            arrayLocalidades[i].id = localidadNextId();
            arrayLocalidades[i].isEmpty = OCUPADO;
        }
        retorno = 0;
    }
    return retorno;
}

int localidad_encontrarLocalidad(eLocalidad* arrayLocalidades,int limite, char* descripcion)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayLocalidades != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayLocalidades[i].isEmpty == OCUPADO && !strcmp(arrayLocalidades[i].descripcion, descripcion))
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int localidadNextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}
