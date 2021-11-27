
/**
 * \brief imprime los pedidos segun el estado del pedido
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \return 0 si la entrada es correcta
 */
int informes_imprimirPedidosSegunEstado(ePedido* arrayPedidos, int limite, eCliente* arrayClientes, int limiteClientes, int estado);

/**
 * \brief imprime los pedidos pendientes con el id de la localidad pasada por parametro
 * \param array de localidades
 * \param limite de array de localidades
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \param indices de clientes
 * \return 0 si la entrada es correcta
 */
int informes_listaPedidosPendientesPorLocalidad(eLocalidad* arrayLocalidades, int limiteLocalidades, ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int localidad, int indiceLocalidad);

/**
 * \brief calcula el promedio por cliente de un tipo de plastico reciclado
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \return 0 si la entrada es correcta
 */
int informes_polipropilenoRecicladoPromedioPorCliente(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);

/**
 * \brief Muestra el maximo de pedidos de uno o mas clientes con el estado pasado por parametro
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \param estado del pedido
 * \return 0 si la entrada es correcta
 */
int informes_clienteConMasPedidosPendientes_Completos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int modoInforme);

/**
 * \brief Muestra el maximo de pedidos de uno o mas clientes
 * \param array de pedidos
 * \param limite de array de pedidos
 * \param array de clientes
 * \param limite de array de clientes
 * \return 0 si la entrada es correcta
 */
int informes_clienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);
