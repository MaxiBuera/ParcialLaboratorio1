#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "pedido.h"
#include "cliente.h"
#define SECTOR 10
#define MINSALARY 1
#define MAXSALARY 300000
#define OCCUPIED 0
#define FREE 1
#define PENDIENTE 0
#define COMPLETADO 1

static int nextId();


void cliente_normalizeTextString(char textString[]){

    int j,i;
    i = strlen(textString);

    for(j=0;j<i;j++){

        if(j==0){

            textString[j] = toupper(textString[j]);
        }
        else{

            textString[j] = tolower(textString[j]);
        }
    }
}

int cliente_inicializarArrayClientes(eCliente* arrayClientes, int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
        	arrayClientes[i].id = -1;
            strcpy(arrayClientes[i].nombreEmpresa,"");
            strcpy(arrayClientes[i].cuit,"");
            strcpy(arrayClientes[i].direccion,"");
            strcpy(arrayClientes[i].localidad,"");
            arrayClientes[i].isEmpty = FREE;

        }
    }
    return retorno;
}

int cliente_nuevoCliente(eCliente* arrayClientes, int limite, int index){

    int retorno = -1;
    char nombreEmpresaAux[40];
    char cuitAux[10];
    char direccionAux[40];
    char localidadAux[40];
    int id;

    if(limite > 0 && arrayClientes != NULL){

        retorno = -2;

        if(getStringLetras("\nIngrese nombre de la empresa: ",nombreEmpresaAux)){

            if(getStringNumeros("Ingrese cuit: ",cuitAux)){

            	if(getStringAlfaNumerico("Ingrese direccion: ",direccionAux)){

            		if(getStringLetras("Ingrese localidad: ",localidadAux)){


            			id = nextId();
                        cliente_normalizeTextString(nombreEmpresaAux);
                        strcpy(arrayClientes[index].nombreEmpresa,nombreEmpresaAux);

                        cliente_normalizeTextString(cuitAux);
                        strcpy(arrayClientes[index].cuit,cuitAux);

                        cliente_normalizeTextString(direccionAux);
                        strcpy(arrayClientes[index].direccion,direccionAux);

                        cliente_normalizeTextString(localidadAux);
                        strcpy(arrayClientes[index].localidad,localidadAux);

                        arrayClientes[index].isEmpty = OCCUPIED;
                        arrayClientes[index].id = id;
                        printf("\n\tCliente Agregado...");
                        printf("\n\tID del Cliente: %d", id+1);
                        retorno = 0;
                    }
                }
            }
        }
    }

    if(retorno != 0){

        printf("\nError\n");
    }

    return retorno;

}

int cliente_buscarPosicionLibre(eCliente* arrayClientes,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayClientes[i].isEmpty == FREE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int cliente_altaForzada(eCliente* arrayClientes,int limite,char* nombreEmpresa,char* cuit, char* direccion,char* localidad)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayClientes != NULL)
    {
        i = cliente_buscarPosicionLibre(arrayClientes,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(arrayClientes[i].nombreEmpresa,nombreEmpresa);
            strcpy(arrayClientes[i].cuit,cuit);
            strcpy(arrayClientes[i].direccion,direccion);
            strcpy(arrayClientes[i].localidad,localidad);
            //------------------------------
            //------------------------------
            arrayClientes[i].id = nextId();
            arrayClientes[i].isEmpty = OCCUPIED;
        }
        retorno = 0;
    }
    return retorno;
}

int cliente_imprimirClientes(eCliente* arrayClientes,int limite, ePedido* arrayPedidos, int limitPedidos){

    int retorno = -1;
    int cantidadPedidosPendientes;
    int i;
    if(limite > 0 && arrayClientes != NULL && limitPedidos > 0 && arrayPedidos != NULL)
    {
        retorno = 0;
        printf("\n\tNombre Empresa\t\tCuit\t\tDireccion\t\tLocalidad\tID\tPedidos de recoleccion en estado Pendiente");
        printf("\n\t-------------------------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayClientes[i].isEmpty)
            {

        		cantidadPedidosPendientes = pedido_mostrarCantidadPedidos(arrayPedidos,limitPedidos,arrayClientes[i].id);

           		printf("\n\t%s\t\t%s\t%s\t\t%s\t\t%d\t\t%d",arrayClientes[i].nombreEmpresa,arrayClientes[i].cuit,arrayClientes[i].direccion,arrayClientes[i].localidad,arrayClientes[i].id+1,cantidadPedidosPendientes);
           	}
        }
    }
    return retorno;
}

int cliente_encontrarClientePorId(eCliente* arrayClientes,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayClientes[i].isEmpty == OCCUPIED && arrayClientes[i].id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int cliente_mostrarClientesIds(eCliente* arrayClientes,int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayClientes != NULL)
    {
        retorno = 0;
        printf("\n\tNombre Empresa\tID");
        printf("\n\t----------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayClientes[i].isEmpty)
            {

           		printf("\n%16s %9d",arrayClientes[i].nombreEmpresa,arrayClientes[i].id+1);
        	}
        }
    }
    printf("\n\n");
    return retorno;
}

void cliente_menuUpdateCliente(eCliente* arrayClientes, int index){

    int opc;
    char direccionAux[40];
    char localidadAux[40];

    printf("\nCliente a Modificar: %s",arrayClientes[index].nombreEmpresa);

    do{

        getValidInt("\n\n\t1.Modificar Direccion\n\t2.Modificar Localidad\n\t3.Listo\n","\nNo valida\n",&opc,1,3,1);
        switch(opc)
        {
            case 1:
                if(getStringLetras("\nIngrese direccion: ",direccionAux)){

                    cliente_normalizeTextString(direccionAux);
                    strcpy(arrayClientes[index].direccion,direccionAux);
                    printf("\nDireccion Modificada...");
                }
                break;
            case 2:
                if(getStringLetras("Ingrese localidad: ",localidadAux)){

                    cliente_normalizeTextString(localidadAux);
                    strcpy(arrayClientes[index].localidad,localidadAux);
                    printf("\nApellido Modificado...");
                }
                break;
        }
    }while(opc != 3);
}

int cliente_actualizarCliente(eCliente* arrayClientes, int limite,int index){

    int i;
    int retorno = -1;

    i = cliente_encontrarClientePorId(arrayClientes,limite,index);
    if(i >= 0)
    {
        cliente_menuUpdateCliente(arrayClientes,i);
        arrayClientes[i].isEmpty = OCCUPIED;
        retorno = 0;
    }
    else{

        printf("\nError. Vuelva a intentar");
    }
    return retorno;
}

int cliente_eliminarCliente(eCliente* arrayClientes, int limite,int index){

    int retorno = -1;
    int i;
    char confirm;
    i = cliente_encontrarClientePorId(arrayClientes,limite,index);
    if(i >= 0)
    {
        printf("\nCliente a eliminar: %s",arrayClientes[i].nombreEmpresa);
        confirm = getChar("\n¿Desea eliminar el cliente? [s/n]: ");
        if(confirm == 's' || confirm == 'S'){
            arrayClientes[i].isEmpty = FREE;
            printf("\n\n\tCliente Eliminado...");
            retorno = 0;
        }
        else if(confirm == 'n' || confirm == 'N'){

            printf("\n\tCliente No Eliminado...");
            return retorno;
        }
    }
    else{

        printf("\nID Cliente no encontrado");
    }
    return retorno;
}



static int nextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}
