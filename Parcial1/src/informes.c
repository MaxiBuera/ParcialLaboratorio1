#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "localidad.h"
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

		printf("\n\tID de pedidos\tCUIT del Cliente\tDireccion del Cliente\tCantidad de kilos a recolectar");
		printf("\n\t------------------------------------------------------------------------------------------------------------------------");
		for(i=0;i<limite;i++){

			if (!arrayPedidos[i].isEmpty && arrayPedidos[i].estado == estado){

				idCliente = cliente_encontrarClientePorId(arrayClientes, limitClientes, arrayPedidos[i].idCliente);

				printf("\n\t%d\t",arrayPedidos[i].id+1);
				printf("\t%s\t\t%s",arrayClientes[idCliente].cuit,arrayClientes[idCliente].direccion);
				printf("\t\t\t%d",arrayPedidos[i].kilosRecoleccion);
			}
		}
	}

	return retorno;
}

int informes_listaPedidosPendientesPorLocalidad(eLocalidad* arrayLocalidades, int limiteLocalidades, ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int localidad, int indiceLocalidad){

	int retorno = -1;
	int i;
	int idCliente;
	int cantidadPedidosLocalidad = 0;

	if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = -2;

		for(i=0;i<limitePedidos;i++){

			retorno = 0;
			idCliente = arrayPedidos[i].idCliente;

			if (!arrayPedidos[i].isEmpty && arrayPedidos[i].estado == PENDIENTE){

				if (arrayClientes[idCliente].idLocalidad == localidad){

					cantidadPedidosLocalidad++;
				}
			}
		}

		printf("\n\nCantidad de pedidos Pendientes para la localidad: %s",arrayLocalidades[indiceLocalidad].descripcion);
		printf("\n\t%d pedidos pendientes",cantidadPedidosLocalidad);
	}

	return retorno;
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


/*char* imprimirModo(int modoInforme){
	char modo[20];

	switch(modoInforme){

	    case PENDIENTE:
	    	strcpy(modo,"pendientes");
	    	break;
	    case COMPLETADO:
	    	strcpy(modo,"completos");
	    	break;
	    case 3:
	    	strcpy(modo,""); //pendientes y completos
	    	break;
	}

	return modo;
}*/


int imprimirIdClienteConMasPedidosPendientes_Completos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int cantidadPedidosMAX, int modoInforme){

	int retorno = -1;
	int i,j;
	int cantidadPedidos = 0;

	if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

		for(i=0;i<limiteClientes;i++){

			if(!arrayClientes[i].isEmpty){

				for(j=0;j<limitePedidos;j++){

					if(arrayPedidos[j].idCliente == arrayClientes[i].id){

						if(arrayPedidos[j].estado == modoInforme)// PENDIENTE - COMPLETO
							cantidadPedidos++;
					}
				}
			}

			if(cantidadPedidos == cantidadPedidosMAX){

				//indiceCliente = cliente_encontrarClientePorId(arrayClientes,limiteClientes,arrayClientes[i].id);
				printf("\n\tCliente ID %d - %s",arrayClientes[i].id+1,arrayClientes[i].nombreEmpresa);
			}

			cantidadPedidos = 0;
		}
	}

	return retorno;
}


int imprimirIdClienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int cantidadPedidosMAX){

	int retorno = -1;
	int i,j;
	int cantidadPedidos = 0;

	if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

		for(i=0;i<limiteClientes;i++){

			if(!arrayClientes[i].isEmpty){

				for(j=0;j<limitePedidos;j++){

					if(arrayPedidos[j].idCliente == arrayClientes[i].id)

						cantidadPedidos++;
				}
			}

			if(cantidadPedidos == cantidadPedidosMAX){

				printf("\n\tID de Cliente %d",arrayClientes[i].id+1);
			}

			cantidadPedidos = 0;
		}
	}

	return retorno;
}


int informes_clienteConMasPedidosPendientes_Completos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int modoInforme){
    int retorno = -1;
    int cantidadPedidos = 0;
    int cantidadPedidosMAX = 0;
    int i;
    int j;


    if(limitePedidos > 0 && arrayPedidos != NULL && limiteClientes > 0 && arrayClientes != NULL)
	{
		retorno = 0;

        for(i=0;i<limiteClientes;i++){

            if(!arrayClientes[i].isEmpty){

                for(j=0;j<limitePedidos;j++){

					if(arrayPedidos[j].idCliente == arrayClientes[i].id){

						if(arrayPedidos[j].estado == modoInforme)// PENDIENTE - COMPLETO
							cantidadPedidos++;
					}
                }
            }

            if(cantidadPedidos > cantidadPedidosMAX){

            	cantidadPedidosMAX = cantidadPedidos;
            }

            cantidadPedidos = 0;
        }

        printf("\nID del cliente con mas pedidos %s:", !modoInforme ? "pendientes" : "completos" );
        imprimirIdClienteConMasPedidosPendientes_Completos(arrayPedidos,limitePedidos,arrayClientes,limiteClientes,cantidadPedidosMAX,modoInforme);
	}

    return retorno;
}



int informes_clienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes){
    int retorno = -1;
    int cantidadPedidos = 0;
    int cantidadPedidosMAX = 0;
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
            }

            if(cantidadPedidos > cantidadPedidosMAX){

                cantidadPedidosMAX = cantidadPedidos;
            }

            cantidadPedidos = 0;
        }

        printf("\nID del cliente con mas pedidos: ");
        imprimirIdClienteConMasPedidos(arrayPedidos,limitePedidos,arrayClientes,limiteClientes,cantidadPedidosMAX);
	}

    return retorno;
}
