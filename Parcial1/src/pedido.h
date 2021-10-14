#ifndef PEDIDO_H_
#define PEDIDO_H_

typedef struct{
	int kilosHDPE;
	int kilosLDPE;
	int kilosPP;
}eResiduos;

typedef struct{
    int id;
    int idCliente;
    int estado;
    int kilosRecoleccion;
    eResiduos residuos;
    int isEmpty;
}ePedido;

#endif /* PEDIDO_H_ */



/** \brief  Para indicar que todas las posiciones estan vacias,
 *          esta funcion coloca el flag (isEmpty) en True en
 *          todas las posiciones del array
 *
 * \param   array de Empleados
 * \param   limite del array de Empleados
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int pedido_inicializarArrayPedidos(ePedido* arrayPedidos, int limite);

 /**
 * \brief Carga al array de clientes con el indice recibido por parametro
 * \param array de Cliente
 * \param limite de array de Cliente
 * \param indice del array donde guardará el empleado
 * \return 0 si la entrada es correcta
 */
int pedido_crearPedido(ePedido* arrayPedidos, int limite, int index);

/**
 * \brief Alta de una empleado sin usar ciclos (solo para pruebas)
 * \param array de Empleados
 * \param limite de array de Empleados
 * \param name del empleado
 * \param lastname del empleado
 * \param salary salario del empleado
 * \param sector sector del empleado
 * \return 0 si la entrada es correcta
 */
int pedido_altaForzada(ePedido* arrayPedidos,int limite,int estado, int kilosRecoleccion, int idCliente, int HDPE, int LDPE, int PP);

/**
 * \brief Muestra el array de Empleados de forma encolumnada.
 * \param array de Empleados
 * \param limite de array de Empleados
 * \return 0 si la entrada es correcta
 */
int pedido_imprimirPedidos(ePedido* arrayPedidos,int limite);

/**
 * \brief Busca una posicion vacia del array
 * \param array de Empleado
 * \param limite de array de Empleados
 * \return -1 o -2 si falla
 */
int pedido_buscarPosicionLibre(ePedido* arrayPedidos,int limite);

/** \brief  Muestra la lista de empleados solo con el nombre, apellido y ID del
            empleado
 * \param   arrayClientes  array de Empleados
 * \param   limit  limite del array de Empleados
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 *
 */
int pedido_mostrarPedidosIds(ePedido* arrayPedidos,int limite);

int pedido_procesarPedido(ePedido* arrayPedidos, int limite, int index);

int pedido_mostrarCantidadPedidos(ePedido* arrayPedidos, int limite, int index);


