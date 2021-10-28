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
#define MINRECOLECCION 1
#define MAXRECOLECCION 10000
#define PENDIENTE 0
#define COMPLETADO 1

static int nextId();

int pedido_inicializarArrayPedidos(ePedido* arrayPedidos, int limit){

    int retorno = -1;
    int i;
    if(limit > 0 && arrayPedidos != NULL)
    {
        retorno = 0;
        for(i=0;i<limit;i++)
        {
        	arrayPedidos[i].id = -1;
        	arrayPedidos[i].idCliente = -1;
            arrayPedidos[i].estado = -1;
            arrayPedidos[i].kilosRecoleccion = 0;
            arrayPedidos[i].residuos.kilosHDPE = 0;
            arrayPedidos[i].residuos.kilosLDPE = 0;
            arrayPedidos[i].residuos.kilosPP = 0;
            arrayPedidos[i].isEmpty = LIBRE;

        }
    }
    return retorno;
}

int pedido_buscarPosicionLibre(ePedido* arrayPedidos,int limit)
{
    int retorno = -1;
    int i;
    if(limit > 0 && arrayPedidos != NULL)
    {
        retorno = -2;
        for(i=0;i<limit;i++)
        {
            if(arrayPedidos[i].isEmpty == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int pedido_crearPedido(ePedido* arrayPedidos, int limit, int index){

    int retorno = -1;
    int kilosRecoleccionAux;
    int id;

    if(limit > 0 && arrayPedidos != NULL){

        retorno = -2;

        if(!getValidInt("Ingrese kilos a recolectar: ","\nError\n",&kilosRecoleccionAux,MINRECOLECCION,MAXRECOLECCION,2)){

        	id = nextId();
        	arrayPedidos[index].kilosRecoleccion = kilosRecoleccionAux;
        	arrayPedidos[index].estado = PENDIENTE;
        	arrayPedidos[index].id = id;
        	arrayPedidos[index].isEmpty = OCUPADO;
        	printf("\n\tPedido Generado...");
        	printf("\n\tID de Pedido: %d", id+1);
        	retorno = 0;
        }
    }

    if(retorno != 0){

        printf("\nError\n");
    }

    return retorno;
}


int pedido_altaForzada(ePedido* arrayPedidos,int limite,int estado, int kilosRecoleccion, int idCliente, int HDPE, int LDPE, int PP)
{
    int retorno = -1;
    int i;

    if(limite > 0 && arrayPedidos != NULL)
    {
        i = pedido_buscarPosicionLibre(arrayPedidos,limite);

        if(i >= 0)
        {

            retorno = 0;
            arrayPedidos[i].estado = estado;
            arrayPedidos[i].kilosRecoleccion = kilosRecoleccion;
            arrayPedidos[i].idCliente = idCliente;
            arrayPedidos[i].residuos.kilosHDPE = HDPE;
            arrayPedidos[i].residuos.kilosLDPE = LDPE;
            arrayPedidos[i].residuos.kilosPP = PP;
            //------------------------------
            //------------------------------
            arrayPedidos[i].id = nextId();
            arrayPedidos[i].isEmpty = OCUPADO;
        }
    }
    return retorno;
}

int printEstado(int estado){

	int retorno = -1;

	if(estado == PENDIENTE){

		printf("Pendiente");
		retorno = 0;
	}
	else if (estado == COMPLETADO) {

		printf("Completado");
		retorno = 0;
	} else {

		printf("Indefinido");
		retorno = -2;
	}

	return retorno;
}

int pedido_imprimirPedidos(ePedido* arrayPedidos,int limite){

    int retorno = -1;
    int i;

    if(limite > 0 && arrayPedidos != NULL)
    {
        retorno = 0;
        printf("\n\n\tKilos de Recoleccion\tEstado\t\tID Pedido\t\tID Cliente\tHDPE\tLDPE\tPP");
        printf("\n\t------------------------------------------------------------------------------------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayPedidos[i].isEmpty)
            {

           		printf("\n\t%d\t\t\t",arrayPedidos[i].kilosRecoleccion);
           		printEstado(arrayPedidos[i].estado);
           		printf("\t%d\t\t\t%d\t\t%d\t%d\t%d", arrayPedidos[i].id+1,arrayPedidos[i].idCliente+1,arrayPedidos[i].residuos.kilosHDPE,arrayPedidos[i].residuos.kilosLDPE,arrayPedidos[i].residuos.kilosPP);
           	}
        }
    }
    return retorno;
}

int pedido_encontrarPedidoById(ePedido* arrayPedidos,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && arrayPedidos != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(arrayPedidos[i].isEmpty == OCUPADO && arrayPedidos[i].id == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int pedido_mostrarPedidosIds(ePedido* arrayPedidos,int limite){

    int retorno = -1;
    int i;
    if(limite > 0 && arrayPedidos != NULL)
    {
        retorno = 1;
        printf("\n\tID de pedidos\tID de clientes");
        printf("\n\t-----------------------------");
        for(i=0;i<limite;i++)
        {
        	if(!arrayPedidos[i].isEmpty && arrayPedidos[i].estado == PENDIENTE)
            {
        		retorno = 0;
           		printf("\n\t%d\t\t%d",arrayPedidos[i].id+1,arrayPedidos[i].idCliente+1);
        	}
        }
    }
    printf("\n\n");
    return retorno;
}

int pedido_procesarPedido(ePedido* arrayPedidos, int limite, int index){

	int retorno = -1;
	int i;
	int HDPE = 0;
	int LDPE = 0;
	int PP = 0;
    int residuosDisponibles;
    int residuos;
    int flag = 0;

	i = pedido_encontrarPedidoById(arrayPedidos,limite,index);
	if(i >= 0)
	{
		residuosDisponibles = arrayPedidos[i].kilosRecoleccion;

		for(residuos=1;residuos<4;residuos++){


			switch(residuos){

				case 1:

					printf("\nKilos de residuos restantes: %d", residuosDisponibles);
					if (!getValidInt("\nIngrese kilos de HDPE (Polietileno de alta densidad): ", "\nValor No valido\n", &HDPE, 0, residuosDisponibles, 2)){

						residuosDisponibles = residuosDisponibles - HDPE;
					}
					break;

				case 2:
					printf("\nKilos de residuos restantes: %d", residuosDisponibles);
					if (!getValidInt("\nIngrese kilos de LDPE (Polietileno de baja densidad): ", "\nValor No valido\n", &LDPE, 0, residuosDisponibles, 2)){

						residuosDisponibles = residuosDisponibles - LDPE;
					}
					break;

				case 3:
					printf("\nKilos de residuos restantes: %d", residuosDisponibles);
					if (!getValidInt("\nIngrese kilos de PP (Polipropileno): ", "\nValor No valido\n", &PP, 0, residuosDisponibles, 2)){
						residuosDisponibles = residuosDisponibles - PP;
						flag++;
					}
					break;
			}

			if (residuosDisponibles == 0 || flag != 0){
				arrayPedidos[i].residuos.kilosHDPE = HDPE;
				arrayPedidos[i].residuos.kilosLDPE = LDPE;
				arrayPedidos[i].residuos.kilosPP = PP;
				arrayPedidos[i].estado = COMPLETADO;
				printf("\nPedido con el ID %d COMPLETADO\n", arrayPedidos[i].id+1);
				printf("\nResiduos reciclados:");
				printf("\n\t%d kilo(s) de HDPE (Polietileno de alta densidad)",arrayPedidos[i].residuos.kilosHDPE);
				printf("\n\t%d kilo(s) de LDPE (Polietileno de alta densidad)",arrayPedidos[i].residuos.kilosLDPE);
				printf("\n\t%d kilo(s) de PP (Polipropileno)",arrayPedidos[i].residuos.kilosPP);
				printf("\nResiduos desechados: %d kilo(s)",residuosDisponibles);
				break;
			}
		}


	}
	else{

	    printf("\nID Pedido no encontrado");
	}

	return retorno;
}

int pedido_mostrarCantidadPedidos(ePedido* arrayPedidos, int limite, int index){

	int i;
	int cantidadPedidos = 0;

	for(i=0;i<limite;i++){

		if (!arrayPedidos[i].isEmpty && arrayPedidos[i].idCliente == index && arrayPedidos[i].estado == PENDIENTE){

			cantidadPedidos++;
		}
	}

	return cantidadPedidos;
}


static int nextId()
{
    static int lastId = -1;
    lastId++;
    return lastId;
}
