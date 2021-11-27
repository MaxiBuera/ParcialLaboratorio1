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
 * \param   array de Pedidos
 * \param   limite del array de Pedidos
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int pedido_inicializarArrayPedidos(ePedido* arrayPedidos, int limite);

 /**
 * \brief Carga al array de pedidos con el indice recibido por parametro
 * \param array de Pedidos
 * \param limite de array de Pedidos
 * \param indice del array donde guardará el empleado
 * \return 0 si la entrada es correcta
 */
int pedido_crearPedido(ePedido* arrayPedidos, int limite, int index, int idCliente);

/**
 * \brief Alta de una empleado sin usar ciclos (solo para pruebas)
 * \param array de Pedidos
 * \param limite del array de Pedidos
 * \param estado del pedido
 * \param kilosRecoleccion del pedido
 * \param idCliente  del cliente
 * \param HDPE-LDPE-PP tipo de plastico
 * \return 0 si la entrada es correcta
 */
int pedido_altaForzada(ePedido* arrayPedidos,int limite,int estado, int kilosRecoleccion, int idCliente, int HDPE, int LDPE, int PP);

/**
 * \brief Muestra el array de Pedidos de forma encolumnada.
 * \param array de Pedidos
 * \param limite de array de Pedidos
 * \return 0 si la entrada es correcta
 */
int pedido_imprimirPedidos(ePedido* arrayPedidos,int limite);

/**
 * \brief Busca una posicion vacia del array
 * \param array de Pedidos
 * \param limite de array de Pedidos
 * \return -1 o -2 si falla
 */
int pedido_buscarPosicionLibre(ePedido* arrayPedidos,int limite);

/** \brief  Muestra la lista de Pedidos solo con el id del pedido y el id y nombre del
            cliente
 * \param   arrayClientes  array de Pedidos
 * \param   limit  limite del array de Pedidos
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 *
 */
int pedido_mostrarPedidosIds(ePedido* arrayPedidos,int limite);

/** \brief  Procesa los tipos de plasticos del pedido. Deja como Completado el pedido
 * \param   arrayClientes  array de Pedidos
 * \param   limit  limite del array de Pedidos
 * \param   index  indice del pedido
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 *
 */
int pedido_procesarPedido(ePedido* arrayPedidos, int limite, int index);

int pedido_mostrarCantidadPedidos(ePedido* arrayPedidos, int limite, int index);


