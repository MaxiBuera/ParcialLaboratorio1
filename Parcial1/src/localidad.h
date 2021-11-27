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
 * \param   array de Localidades
 * \param   limite del array de Localidades
 *
 * \return 0 si la entrada es correcta, sino -1
 *
 */
int localidad_inicializarArrayLocalidades(eLocalidad* arrayLocalidades, int limite);

 /**
 * \brief Carga al array de Localidades con el indice recibido por parametro
 * \param array de Localidades
 * \param limite de array de Localidades
 * \param indice del array donde guardará la localidad
 * \return 0 si la entrada es correcta
 */
int localidad_nuevaLocalidad(eLocalidad* arrayLocalidades, int limite, int index);


/**
 * \brief Busca una posicion vacia del array
 * \param array de Localidades
 * \param limite de array de Localidades
 * \return -1 o -2 si falla
 */
int localidad_buscarPosicionLibre(eLocalidad* arrayLocalidades,int limite);

/**
 * \brief Muestra el array de Localidades de forma encolumnada.
 * \param array de Localidades
 * \param limite de array de Localidades
 * \return 0 si la entrada es correcta
 */
int localidad_imprimirLocalidades(eLocalidad* arrayLocalidades,int limite);


/**
 * \brief Alta de una empleado sin usar ciclos (solo para pruebas)
 * \param array de Localidades
 * \param limite de array de Localidades
 * \param descripcion de la localidad
 * \return 0 si la entrada es correcta
 */
int localidad_altaForzada(eLocalidad* arrayLocalidades,int limite,char* descripcion);

/**
 * \brief Busca id dentro del array
 * \param array de Localidades
 * \param limite de array de Localidades
  * \param id a buscar
 * \return -1 o -2 si falla
 */
int localidad_encontrarLocalidad(eLocalidad* arrayLocalidades,int limite, int idLocalidad);

int localidadNextId();
