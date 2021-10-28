#ifndef LOCALIDAD_H_
#define LOCALIDAD_H_

typedef struct{
    int id;
    char descripcion[40];
    int isEmpty;
}eLocalidad;

#endif /* LOCALIDAD_H_ */


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
int localidad_inicializarArrayLocalidades(eLocalidad* arrayLocalidades, int limite);

 /**
 * \brief Carga al array de clientes con el indice recibido por parametro
 * \param array de Cliente
 * \param limite de array de Cliente
 * \param indice del array donde guardará el empleado
 * \return 0 si la entrada es correcta
 */
int localidad_nuevoCliente(eLocalidad* arrayLocalidades, int limite, int index);


/**
 * \brief Busca una posicion vacia del array
 * \param array de Empleado
 * \param limite de array de Empleados
 * \return -1 o -2 si falla
 */
int localidad_buscarPosicionLibre(eLocalidad* arrayLocalidades,int limite);

/**
 * \brief Muestra el array de Empleados de forma encolumnada.
 * \param array de Empleados
 * \param limite de array de Empleados
 * \return 0 si la entrada es correcta
 */
int localidad_imprimirLocalidades(eLocalidad* arrayLocalidades,int limite);


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
int localidad_altaForzada(eLocalidad* arrayLocalidades,int limite,char* descripcion);

/**
 * \brief Busca id dentro del array
 * \param array de Empleados
 * \param limite de array de Empleados
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int localidad_encontrarLocalidad(eLocalidad* arrayLocalidades,int limite, char* descripcion);

int localidadNextId();
