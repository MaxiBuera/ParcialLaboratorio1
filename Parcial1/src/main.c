#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utn.h"
#include "pedido.h"
#include "cliente.h"
#include "informes.h"
#define OCCUPIED 0
#define FREE 1
#define CLIENTES 100
#define PEDIDOS 10
#define PENDIENTE 0
#define COMPLETADO 1


int main()
{
	setbuf(stdout, NULL);
    int menu;
    int index;
    int auxiliarId;
    int flag = 1; // Para entregar debe ser 0
    char opcion[40];
    int flagAdd;

    eCliente arrayClientes[CLIENTES];
    ePedido arrayPedidos[PEDIDOS];

    cliente_inicializarArrayClientes(arrayClientes,CLIENTES);
    pedido_inicializarArrayPedidos(arrayPedidos,PEDIDOS);

    //Solo para testear
    cliente_altaForzada(arrayClientes,CLIENTES,"Telefonica","12345678","Calle Falsa 123","CABA");
    cliente_altaForzada(arrayClientes,CLIENTES,"Walmart","78945612","Av. Siempre Viva 742","GBA");
    cliente_altaForzada(arrayClientes,CLIENTES,"Asdzxc","45678912","Metropolis 456","Interior");

    pedido_altaForzada(arrayPedidos,PEDIDOS,PENDIENTE,20,0,0,0,0);
    pedido_altaForzada(arrayPedidos,PEDIDOS,COMPLETADO,100,1,80,10,10);
    pedido_altaForzada(arrayPedidos,PEDIDOS,COMPLETADO,100,0,80,10,5);
    pedido_altaForzada(arrayPedidos,PEDIDOS,PENDIENTE,10,2,0,0,0);
    pedido_altaForzada(arrayPedidos,PEDIDOS,PENDIENTE,30,2,0,0,0);

    cliente_imprimirClientes(arrayClientes,CLIENTES,arrayPedidos,PEDIDOS);
    pedido_imprimirPedidos(arrayPedidos,PEDIDOS);

    do{

        getValidInt("\n\n1.Alta de Cliente\n"
        		"2.Modificar datos del Cliente\n"
        		"3.Baja de Cliente\n"
        		"4.Crear Pedido de Recoleccion\n"
        		"5.Procesar residuos\n"
        		"6.Imprimir Clientes\n"
        		"7.Imprimir Pedidos Pendientes\n"
        		"8.Imprimir Pedidos Procesados\n"
        		"9.Ingresar una localidad e indicar la cantidad de pedidos pendientes para dicha localidad\n"
        		"10.Cantidad de kilos de polipropileno reciclado promedio por cliente (kilos totales / cantidad de clientes)\n"
        		"11.Cliente con mas pedidos pendientes\n"
        		"12.Cliente con mas pedidos completados\n"
        		"14.Salir\n","\nNo valida\n",&menu,1,14,1);
        switch(menu)
        {

            case 1:

                index = cliente_buscarPosicionLibre(arrayClientes,CLIENTES);
                if(index >= 0){
                    flagAdd = cliente_nuevoCliente(arrayClientes,CLIENTES,index);
                    if(flagAdd == 0)
                        flag = 1;
                }
                else{

                    printf("\nDebe ingresar un cliente\n");
                }
                break;

            case 2:

                if(flag!=0){
                	cliente_mostrarClientesIds(arrayClientes,CLIENTES);
                    getValidInt("\tID Cliente a modificar: ","\nID No valido\n",&auxiliarId,0,CLIENTES,2);
                    cliente_actualizarCliente(arrayClientes,CLIENTES,auxiliarId-1);
               }
                else{

                    printf("\nDebe ingresar un empleado\n");
                }
                break;

            case 3:

                if(flag!=0){
                	cliente_mostrarClientesIds(arrayClientes,CLIENTES);
                    getValidInt("\nID Cliente a eliminar: ","\nID No valido\n",&auxiliarId,0,CLIENTES,2);
                    cliente_eliminarCliente(arrayClientes,CLIENTES,auxiliarId-1);
                }
                else{

                    printf("\nDebe ingresar un empleado\n");
                }
                break;

            case 4:

                if(flag!=0){
                	cliente_mostrarClientesIds(arrayClientes,CLIENTES);
                	getValidInt("\nIngrese ID de Cliente: ","\nID No valido\n",&auxiliarId,0,PEDIDOS,2);
                	index = pedido_buscarPosicionLibre(arrayPedidos,PEDIDOS);
                	pedido_crearPedido(arrayPedidos,PEDIDOS,index);
                }
                    else{

                        printf("\nDebe ingresar un empleado\n");
                }
                break;
            case 5:

				if (flag != 0) {
					if(pedido_mostrarPedidosIds(arrayPedidos, PEDIDOS) == 0){

						getValidInt("\nIngrese ID de Pedido: ", "\nID No valido\n", &auxiliarId, 0, PEDIDOS, 2);
						pedido_procesarPedido(arrayPedidos,PEDIDOS,auxiliarId-1);
					}

					else {

						printf("\n\tSin Pedidos");
					}

				} else {

					printf("\nDebe ingresar un empleado\n");
				}
				break;

            case 6:

            	if (flag != 0) {

            		cliente_imprimirClientes(arrayClientes,CLIENTES,arrayPedidos,PEDIDOS);
            	} else {

            		printf("\nDebe ingresar un empleado\n");
            	}
            	break;

            case 7:

            	if (flag != 0) {

            		informes_imprimirPedidosSegunEstado(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES,PENDIENTE);
            	} else {

            		printf("\nDebe ingresar un empleado\n");
            	}
            	break;
            case 8:

             	if (flag != 0) {

             		informes_imprimirPedidosSegunEstado(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES,COMPLETADO);
                } else {

                	printf("\nDebe ingresar un empleado\n");
                }
                break;

            case 9:
            	if (flag != 0) {
            		getValidString("\nIngrese Localidad a buscar: ","\nDato no Valido","\nError. Localidad no Valida",opcion,40,2);
            		informes_listaPedidosPendientesPorLocalidad(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES,opcion);
            	} else {

            		printf("\nDebe ingresar un empleado\n");
            	}
            	break;

            case 10:
            	if (flag != 0) {

            		informes_polipropilenoRecicladoPromedioPorCliente(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES);
            	} else {

            	     printf("\nDebe ingresar un empleado\n");
            	}
            	break;
            case 11:
            	if (flag != 0) {

            		informes_clienteConMasPedidosPendientes(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES);
            	} else {

            	     printf("\nDebe ingresar un empleado\n");
            	}
            	break;
            case 12:
            	if (flag != 0) {

            		informes_clienteConMasPedidosCompletados(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES);
            	} else {

            	     printf("\nDebe ingresar un empleado\n");
            	}
            	break;
            case 13:
            	if (flag != 0) {

            		informes_clienteConMasPedidos(arrayPedidos,PEDIDOS,arrayClientes,CLIENTES);
            	} else {

            	     printf("\nDebe ingresar un empleado\n");
            	}
            	break;
        }
    }while(menu != 14);


    return 0;
}

