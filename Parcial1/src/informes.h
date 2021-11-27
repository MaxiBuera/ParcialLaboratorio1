

int informes_imprimirPedidosSegunEstado(ePedido* arrayPedidos, int limite, eCliente* arrayClientes, int limiteClientes, int estado);

int informes_listaPedidosPendientesPorLocalidad(eLocalidad* arrayLocalidades, int limiteLocalidades, ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int localidad, int indiceLocalidad);

int informes_polipropilenoRecicladoPromedioPorCliente(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);

int informes_clienteConMasPedidosPendientes_Completos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes, int modoInforme);

int informes_clienteConMasPedidos(ePedido* arrayPedidos, int limitePedidos, eCliente* arrayClientes, int limiteClientes);
