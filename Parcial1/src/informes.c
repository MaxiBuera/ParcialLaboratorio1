#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "pedido.h"
#include "cliente.h"
#include "informes.h"
#define SECTOR 10
#define MINSALARY 1
#define MAXSALARY 300000
#define OCCUPIED 0
#define FREE 1
#define MINRECOLECCION 1
#define MAXRECOLECCION 10000
#define PENDIENTE 0
#define COMPLETADO 1


int informes_imprimirPedidosSegunEstado(ePedido* arrayPedidos, int limite, eCliente* arrayClientes, int limitClientes, int estado){

	int retorno = -1;
	int i;
	int idCliente;

	if(limite > 0 && arrayPedidos != NULL && limitClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

		switch(estado){

			case PENDIENTE:

				printf("\n\tID de pedidos\tCUIT del Cliente\tDireccion del Cliente\tCantidad de kilos a recolectar");
				printf("\n\t------------------------------------------------------------------------------------------------------------------------");
				for(i=0;i<limite;i++){

					if (estado == arrayPedidos[i].estado && !arrayPedidos[i].isEmpty){

						idCliente = arrayPedidos[i].idCliente;

						printf("\n\t%d\t",arrayPedidos[i].id+1);
						printf("\t%s\t\t%s",arrayClientes[idCliente].cuit,arrayClientes[idCliente].direccion);
						printf("\t\t\t%d",arrayPedidos[i].kilosRecoleccion);
					}
				}
				break;
			case COMPLETADO:

				printf("\n\tID de pedidos\tCUIT del Cliente\tDireccion del Cliente\tCantidad de kilos a recolectar\tHDPE\tLDPE\tPP");
				printf("\n\t------------------------------------------------------------------------------------------------------------------------");

				for(i=0;i<limite;i++){

					if (estado == COMPLETADO && !arrayPedidos[i].isEmpty && arrayPedidos[i].estado == COMPLETADO) {

						idCliente = arrayPedidos[i].idCliente;

						printf("\n\t%d\t",arrayPedidos[i].id+1);
						printf("\t%s\t\t%s",arrayClientes[idCliente].cuit,arrayClientes[idCliente].direccion);
						printf("\t\t%d\t\t\t\t%d\t%d\t%d",arrayPedidos[i].kilosRecoleccion,arrayPedidos[i].residuos.kilosHDPE,arrayPedidos[i].residuos.kilosLDPE,arrayPedidos[i].residuos.kilosPP);

					}
				}
				break;
		}
	}


	return retorno;
}

int informes_listaPedidosPendientesPorLocalidad(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, char* localidad ){

	int returnValue = -1;
	int i;
	int idCliente;
	int cantidadPedidosLocalidad = 0;

	if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		returnValue = -2;

		for(i=0;i<limitePedidos;i++){

			returnValue = 0;
			idCliente = arrayPedidos[i].idCliente;

			if (!arrayPedidos[i].isEmpty && arrayPedidos[i].estado == PENDIENTE){

				if (!strcmp(arrayClientes[idCliente].localidad,localidad)){

					cantidadPedidosLocalidad++;
				}
			}
		}

		printf("\n\nCantidad de pedidos Pendientes para la localidad: %s",localidad);
		printf("\n\t%d pedidos pendientes",cantidadPedidosLocalidad);
	}

	return returnValue;
}


int informes_polipropilenoRecicladoPromedioPorCliente(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes){

	int retorno = -1;
	int i,j;
	int idCliente;
	int kilosPPTotales = 0;
	int cantidadClientes = 0;
	float promedioPPporCliente = 0;

	//(kilos totales / cantidad de clientes)


	if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

		for(i=0;i<limiteClientes;i++){

			if (!arrayClientes[i].isEmpty){

				idCliente = arrayClientes[i].id;

				for(j=0;j<limitePedidos;j++){

					if (!arrayPedidos[j].isEmpty && arrayPedidos[j].idCliente == idCliente){

						kilosPPTotales = kilosPPTotales + arrayPedidos[j].residuos.kilosPP;
					}
				}
				cantidadClientes++;
			}
		}

		promedioPPporCliente = (float)kilosPPTotales/(float)cantidadClientes;

		printf("\nCantidad de kilos de polipropileno reciclado promedio por cliente: %2.f",promedioPPporCliente);
	}

	return retorno;
}

//los siguientes informes:
//a) Cliente con más pedidos pendientes.
//b) Cliente con más pedidos completados.
//c) Cliente con más pedidos.


int informes_clienteConMasPedidosPendientes(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes){
    int retorno = -1;
    int cantidadPedidosPendientes = 0;
    int cantidadPedidosPendientesMAX = 0;
    int idClienteConMasPedidosPendientes;
    int i;
    int j;

    if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

        //printf("\nCliente con mas pedidos pendientes: ID Cliente(s): %d");
        for(i=0;i<limiteClientes;i++){

            if(!arrayClientes[i].isEmpty){

                for(j=0;j<limitePedidos;j++){

                if(arrayPedidos[j].idCliente == arrayClientes[i].id){

                    if(arrayPedidos[j].estado == PENDIENTE)
                        cantidadPedidosPendientes++;
                    }
                }
            }

            if(cantidadPedidosPendientes > cantidadPedidosPendientesMAX){

                cantidadPedidosPendientesMAX = cantidadPedidosPendientes;
                idClienteConMasPedidosPendientes = arrayClientes[i].id;
            }

            cantidadPedidosPendientes = 0;
        }

        printf("\nID del cliente con mas pedidos pendientes: ID Cliente %d",idClienteConMasPedidosPendientes+1);
	}

    return retorno;
}


int informes_clienteConMasPedidosCompletados(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes){
    int retorno = -1;
    int cantidadPedidosCompletados = 0;
    int cantidadPedidosCompletadosMAX = 0;
    int idClienteConMasPedidosCompletados;
    int i;
    int j;

    if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

        for(i=0;i<limiteClientes;i++){

            if(!arrayClientes[i].isEmpty){

                for(j=0;j<limitePedidos;j++){

                if(arrayPedidos[j].idCliente == arrayClientes[i].id){

                    if(arrayPedidos[j].estado == COMPLETADO)
                        cantidadPedidosCompletados++;
                    }
                }
            }

            if(cantidadPedidosCompletados > cantidadPedidosCompletadosMAX){

                cantidadPedidosCompletadosMAX = cantidadPedidosCompletados;
                idClienteConMasPedidosCompletados = arrayClientes[i].id;
            }

            cantidadPedidosCompletados = 0;
        }

        printf("\nID del cliente con mas pedidos completados: ID Cliente %d",idClienteConMasPedidosCompletados+1);
	}

    return retorno;
}


int informes_clienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes){
    int retorno = -1;
    int cantidadPedidos = 0;
    int cantidadPedidosMAX = 0;
    int idClienteConMasPedidos;
    int i;
    int j;

    if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

        for(i=0;i<limiteClientes;i++){

            if(!arrayClientes[i].isEmpty){

                for(j=0;j<limitePedidos;j++){

                if(arrayPedidos[j].idCliente == arrayClientes[i].id)


                    cantidadPedidos++;


            }

            if(cantidadPedidos > cantidadPedidosMAX){

                cantidadPedidosMAX = cantidadPedidos;
                idClienteConMasPedidos = arrayClientes[i].id;
            }

            cantidadPedidos = 0;
        }

        printf("\nID del cliente con mas pedidos: ID Cliente %d",idClienteConMasPedidos+1);
	}

    return retorno;
}

