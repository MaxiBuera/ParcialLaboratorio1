

int informes_imprimirPedidosSegunEstado(ePedido* arrayPedidos, int limite, eCliente* arrayClientes, int limiteClientes, int estado);

int informes_listaPedidosPendientesPorLocalidad(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, char* localidad);

int informes_polipropilenoRecicladoPromedioPorCliente(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);



int informes_clienteConMasPedidosPendientes(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);


int informes_clienteConMasPedidosCompletados(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);


int informes_clienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);
