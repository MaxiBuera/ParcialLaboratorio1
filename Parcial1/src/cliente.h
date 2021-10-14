#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct{
    int id;
    char nombreEmpresa[40];
    char cuit[10];
    char direccion[40];
    char localidad[40];
    int isEmpty;
}eCliente;

#endif /* CLIENTE_H_ */


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
int cliente_inicializarArrayClientes(eCliente* arrayClientes, int limite);

 /**
 * \brief Carga al array de clientes con el indice recibido por parametro
 * \param array de Cliente
 * \param limite de array de Cliente
 * \param indice del array donde guardará el empleado
 * \return 0 si la entrada es correcta
 */
int cliente_nuevoCliente(eCliente* arrayClientes, int limite, int index);

/**
 * \brief Modifica el array de un empleado
 * \param arrayClientes array de Empleados
 * \param limit  limite del array de Empleados
 * \param id Empleado a buscar
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 */
int cliente_actualizarCliente(eCliente* arrayClientes, int limite, int index);


/** \brief  Muestra la lista de empleados solo con el nombre, apellido y ID del
            empleado
 * \param   arrayClientes  array de Empleados
 * \param   limit  limite del array de Empleados
 * \return  (-1) si hay error [limite invalido o puntero NULL] - (0) si Ok
 *
 */
int cliente_mostrarClientesIds(eCliente* arrayClientes,int limite);

/**
 * \brief Baja de un Empleado
 * \param array de Empleado
 * \param limite de array de Empleados
 * \param id a buscar
 * \return -1 o -2 si falla
 */
int cliente_eliminarCliente(eCliente* arrayClientes, int limite, int index);

/**
 * \brief Busca una posicion vacia del array
 * \param array de Empleado
 * \param limite de array de Empleados
 * \return -1 o -2 si falla
 */
int cliente_buscarPosicionLibre(eCliente* arrayClientes,int limite);

/**
 * \brief Busca id dentro del array
 * \param array de Empleados
 * \param limite de array de Empleados
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int cliente_encontrarClientePorId(eCliente* arrayClientes,int limite, int id);


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
int cliente_altaForzada(eCliente* arrayClientes,int limite,char* name,char* lastname, char* salary,char* sector);

/**
 * \brief Muestra el array de Empleados de forma encolumnada.
 * \param array de Empleados
 * \param limite de array de Empleados
 * \return 0 si la entrada es correcta
 */
int cliente_imprimirClientes(eCliente* arrayClientes,int limite, ePedido* arrayPedidos, int limitPedidos);

/** \brief Convierte la cadena pasado como parametro. El primer caracter será
           mayuscula mientras que el resto será minuscula
 *
 * \param textString    cadena de texto a convertir
 * \return -
 *
 */
void cliente_normalizeTextString(char textString[]);

