#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "localidad.h"
#include "pedido.h"
#include "cliente.h"
#define SECTOR 10
#define LOCALIDADES 100
#define MINSALARY 1
#define MAXSALARY 300000
#define OCUPADO 0
#define LIBRE 1
#define PENDIENTE 0
#define COMPLETADO 1

static int nextId();

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
            arrayClientes[i].idLocalidad = -1;
            arrayClientes[i].isEmpty = LIBRE;

        }
    }
    return retorno;
}

int cliente_nuevoCliente(eCliente* arrayClientes, int limite, int index, eLocalidad* arrayLocalidades, int limiteLocalidades){

    int retorno = -1;
    char nombreEmpresaAux[40];
    char cuitAux[10];
    char direccionAux[40];
    int id;
    int idLocalidad;

    if(limite > 0 && arrayClientes != NULL){

        retorno = -2;

        if(getStringLetras("\nIngrese nombre de la empresa: ",nombreEmpresaAux)){

            if(getStringNumeros("Ingrese cuit: ",cuitAux)){

            	if(getStringAlfaNumerico("Ingrese direccion: ",direccionAux)){

        			localidad_imprimirLocalidades(arrayLocalidades,limiteLocalidades);

            		if(!getValidInt("Ingrese localidad: ","\nLocalidad no valida\n",&idLocalidad,0,LOCALIDADES,2)){

            			if(localidad_encontrarLocalidad(arrayLocalidades,limiteLocalidades,idLocalidad >= 0)){

            				id = nextId();

            				normalizeTextString(nombreEmpresaAux);
            				strcpy(arrayClientes[index].nombreEmpresa,nombreEmpresaAux);

							normalizeTextString(cuitAux);
							strcpy(arrayClientes[index].cuit,cuitAux);

							normalizeTextString(direccionAux);
							strcpy(arrayClientes[index].direccion,direccionAux);

							arrayClientes[index].idLocalidad = idLocalidad;
							arrayClientes[index].isEmpty = OCUPADO;
							arrayLocalidades[idLocalidad].isEmpty = OCUPADO;
							arrayClientes[index].id = id;

							printf("\n\tCliente Agregado...");
							printf("\n\tID del Cliente: %d", id+1);
							retorno = 0;
            			}
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
            if(arrayClientes[i].isEmpty == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int cliente_altaForzada(eCliente* arrayClientes,int limite,char* nombreEmpresa,char* cuit, char* direccion, int idLocalidad)
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
            arrayClientes[i].idLocalidad = idLocalidad;
            //------------------------------
            //------------------------------
            arrayClientes[i].id = nextId();
            arrayClientes[i].isEmpty = OCUPADO;
        }
        retorno = 0;
    }
    return retorno;
}

int cliente_imprimirClientes(eCliente* arrayClientes,int limite, ePedido* arrayPedidos, int limitePedidos){

    int retorno = -1;
    int cantidadPedidosPendientes;
    int i;
    if(limite > 0 && arrayClientes != NULL && limitePedidos > 0 && arrayPedidos != NULL)
    {
        retorno = 0;
        printf("\n\tNombre Empresa\t\tCuit\t\tDireccion\t\tID Localidad\tID\tPedidos de recoleccion en estado Pendiente");
        printf("\n\t---------------------------------------------------------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayClientes[i].isEmpty)
            {

        		cantidadPedidosPendientes = pedido_mostrarCantidadPedidos(arrayPedidos,limitePedidos,arrayClientes[i].id);

           		printf("\n\t%s\t\t%s\t%s\t\t%d\t\t%d\t\t%d",arrayClientes[i].nombreEmpresa,arrayClientes[i].cuit,arrayClientes[i].direccion,arrayClientes[i].idLocalidad,arrayClientes[i].id+1,cantidadPedidosPendientes);
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
            if(arrayClientes[i].isEmpty == OCUPADO && arrayClientes[i].id == id)
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

void cliente_menuUpdateCliente(eCliente* arrayClientes, int index, eLocalidad* arrayLocalidades, int limiteLocalidades){

    int opc;
    char direccionAux[40];
    int idLocalidad;
    int localidadValida;

    printf("\nCliente a Modificar: %s",arrayClientes[index].nombreEmpresa);

    do{

        getValidInt("\n\n\t1.Modificar Direccion\n\t2.Modificar Localidad\n\t3.Listo\n","\nNo valida\n",&opc,1,3,1);
        switch(opc)
        {
            case 1:
                if(getStringAlfaNumerico("Ingrese direccion: ",direccionAux)){

                    normalizeTextString(direccionAux);
                    strcpy(arrayClientes[index].direccion,direccionAux);
                    printf("\nDireccion Modificada...");
                }
                else{
                	printf("\nError");
                }
                break;
            case 2:
            	localidad_imprimirLocalidades(arrayLocalidades,limiteLocalidades);

            	if(!getValidInt("Ingrese localidad: ","\nError\n",&idLocalidad,0,LOCALIDADES,2)){

            		localidadValida = localidad_encontrarLocalidad(arrayLocalidades,limiteLocalidades,idLocalidad);
            		if(localidadValida >= 0){

            			arrayClientes[index].idLocalidad = idLocalidad;
						printf("\nLocalidad Modificada...");
            		}
            		else {
            			printf("\nError");
            		}
                }
                break;
        }
    }while(opc != 3);
}

int cliente_actualizarCliente(eCliente* arrayClientes, int limite,int index, eLocalidad* arrayLocalidades, int limiteLocalidades){

    int i;
    int retorno = -1;

    i = cliente_encontrarClientePorId(arrayClientes,limite,index);
    if(i >= 0)
    {

        cliente_menuUpdateCliente(arrayClientes,i,arrayLocalidades,limiteLocalidades);

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
            arrayClientes[i].isEmpty = LIBRE;
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


int cliente_mostrarPedidosIds(ePedido* arrayPedidos,int limite, eCliente* arrayClientes, int limiteClientes){

    int retorno = -1;
    int i;
    int indiceCliente;
    if(limite > 0 && arrayPedidos != NULL)
    {
        retorno = 1;
        printf("\n\tID de pedidos\tID de clientes\tCliente");
        printf("\n\t----------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayPedidos[i].isEmpty && arrayPedidos[i].estado == PENDIENTE)
            {
        		indiceCliente = cliente_encontrarClientePorId(arrayClientes, limiteClientes, arrayPedidos[i].idCliente);
           		printf("\n\t%d\t\t%d\t\t%s",arrayPedidos[i].id+1,arrayPedidos[i].idCliente+1,arrayClientes[indiceCliente].nombreEmpresa);
           		retorno = 0;
        	}
        }
    }
    printf("\n\n");
    return retorno;
}

static int nextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}
