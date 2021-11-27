#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct{
    int id;
    char nombreEmpresa[40];
    char cuit[10];
    char direccion[40];
    int idLocalidad;
    int isEmpty;
}eCliente;

#endif /* CLIENTE_H_ */


/** \brief  Para indicar que todas las posiciones estan vacias,
 *          esta funcion coloca el flag (isEmpty) en True en
 *          todas las posiciones del array
 *
 * \param   array de Clientes
 * \param   limite del array de Clientes
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int cliente_inicializarArrayClientes(eCliente* arrayClientes, int limite);

 /**
 * \brief Carga al array de clientes con el indice recibido por parametro
 * \param array de Cliente
 * \param limite de array de Cliente
 * \param indice del array donde guardará el pedido
 * \return 0 si la entrada es correcta
 */
int cliente_nuevoCliente(eCliente* arrayClientes, int limite, int index, eLocalidad* arrayLocalidades, int limiteLocalidades);

/**
 * \brief Modifica el array de un Clientes
 * \param arrayClientes array de Clientes
 * \param limit  limite del array de Clientes
 * \param id pedido a buscar
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 */
int cliente_actualizarCliente(eCliente* arrayClientes, int limite,int index, eLocalidad* arrayLocalidades, int limiteLocalidades);

/** \brief  Muestra la lista de Clientes solo con el nombre, apellido y ID del
            pedido
 * \param   arrayClientes  array de Clientes
 * \param   limit  limite del array de Clientes
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 *
 */
int cliente_mostrarClientesIds(eCliente* arrayClientes,int limite);

/**
 * \brief Baja de un cliente
 * \param array de clientes
 * \param limite de array de Clientes
 * \param id a buscar
 * \return -1 o -2 si falla
 */
int cliente_eliminarCliente(eCliente* arrayClientes, int limite, int index);

/**
 * \brief Busca una posicion vacia del array
 * \param array de clientes
 * \param limite de array de Clientes
 * \return -1 o -2 si falla
 */
int cliente_buscarPosicionLibre(eCliente* arrayClientes,int limite);

/**
 * \brief Busca id dentro del array
 * \param array de Clientes
 * \param limite de array de Clientes
  * \param id a buscar
 * \return indice del cliente, -1 o -2 si falla
 */
int cliente_encontrarClientePorId(eCliente* arrayClientes,int limite, int id);


/**
 * \brief Alta de una cliente sin usar ciclos (solo para pruebas)
 * \param array de Clientes
 * \param limite de array de Clientes
 * \param nombreEmpresa del cliente
 * \param cuit del cliente
 * \param direccion del cliente
 * \param idLocalidad localidad del cliente
 * \return 0 si la entrada es correcta
 */
int cliente_altaForzada(eCliente* arrayClientes,int limite,char* nombreEmpresa,char* cuit, char* direccion,int idLocalidad);

/**
 * \brief Muestra el array de clientes de forma encolumnada.
 * \param array de clientes
 * \param limite de array de clientes
 * \param array de pedidos
 * \param limite de array de pedidos
 * \return 0 si la entrada es correcta
 */
int cliente_imprimirClientes(eCliente* arrayClientes,int limite, ePedido* arrayPedidos, int limitePedidos);

/**
 * \brief Muestra los pedidos pendientes junto a los datos del cliente
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \return 0 si la entrada es correcta
 */
int cliente_mostrarPedidosIds(ePedido* arrayPedidos,int limite, eCliente* arrayClientes, int limiteClientes);
