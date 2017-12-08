/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autores: Daniel Santo-Tomás y Lucía Rivas
 * Version: 1.0
 * Fecha: 6-10-2017
 *
 */

#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:6/10/2017*/
/*                                                 */
/* Grupo 1201                                      */
/* Lucía Rivas y Daniel Santo-Tomás                */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
    if(!metodo || !ptiempo || n_perms<=0 || N<=0) return ERR;
    int **perms;
    int i, min = -1, max = -1, aux;
    double secs = 0, med = 0;
    struct timeval t_ini, t_fin;


    perms = genera_permutaciones(n_perms,N);
    if(!perms) return ERR;

    for(i = 0; i < n_perms; i++){
	gettimeofday(&t_ini, NULL);
	aux = metodo(perms[i], 0, N-1);
	gettimeofday(&t_fin, NULL);
        secs += (double)(t_fin.tv_sec + (double)t_fin.tv_usec/1000000) - (double)(t_ini.tv_sec + (double)t_ini.tv_usec/1000000);
	med += aux;
    	if(min == -1 && max == -1) {
		min = aux;
            	max = aux;
		continue;
	}

	if(aux < min) min = aux;
	if(aux > max) max = aux;

    }

    ptiempo->N = N;
    ptiempo->n_elems = n_perms;
    ptiempo->max_ob = max;
    ptiempo->min_ob = min;
    ptiempo->medio_ob = (med/n_perms);
    ptiempo->tiempo = (secs/n_perms);

    for(i = 0;i < n_perms; i++){
	free(perms[i]);
    }

    free(perms);

    return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion              */
/*  Fecha: 6/10/2017                               */
/* Grupo 1201                                      */
/* Lucía Rivas y Daniel Santo-Tomás                */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
    if(!metodo || !fichero || num_min <=0 || num_max <= num_min || incr <= 0 || n_perms <= 0 ) return ERR;

    int i;

    PTIEMPO tiempo = (PTIEMPO)malloc(sizeof(TIEMPO)*(((num_max - num_min)/incr) + 1));
    PTIEMPO aux;
    if(!tiempo) return ERR;

    aux = tiempo;

    for(i = num_min ; i <= num_max ; i += incr){
      printf("tamaño %d\n",i);
	if(tiempo_medio_ordenacion( metodo,n_perms, i, aux)== ERR) return ERR;
	aux++;
    }

    if(guarda_tabla_tiempos(fichero, tiempo, (((num_max - num_min)/incr) + 1)) == ERR) return ERR;

    free(tiempo);

    return OK;

}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:6/10/2017   */
/*                                                 */
/* Grupo 1201                                      */
/* Lucía Rivas y Daniel Santo-Tomás                */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
    if(!fichero || !tiempo || n_tiempos <= 0 ) return ERR;

    FILE *f = NULL;
    int i;
    PTIEMPO aux;

    aux = tiempo;

    f = fopen(fichero,"w");
    if (!f) return ERR;

    for(i = 0; i <n_tiempos ; i++){
         fprintf(f,"%d %.20f %lf %d %d \n",aux->N, aux->tiempo, aux->medio_ob, aux->max_ob, aux->min_ob);
	 aux++;
    }

    fclose(f);

    return OK;
}

/***************************************************/
/* Funcion: tiempo_medio_busqueda                  */
/* Fecha: 24/11/2017                               */
/* Grupo 1201                                      */
/* Lucía Rivas y Daniel Santo-Tomás                */
/***************************************************/
short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
  int orden,
  int N,
  int n_veces,
  PTIEMPO ptiempo){

if(!metodo || !generador) return ERR;

PDICC d;
int *perm,*claves;
int max = -1, min = -1, i, aux = 0, ppos;
double secs = 0, med = 0;
struct timeval t_ini, t_fin;

d = ini_diccionario(N,orden);
if(!d) return ERR;
perm = genera_perm(N);
if(!perm){
  free(d);
  return ERR;
}

if(insercion_masiva_diccionario (d, perm, N) == ERR){
  free(perm);
  free(d);
  return ERR;
}

claves = (int*)malloc(sizeof(int)*N*n_veces);
if(!claves){
  free(d);
  return ERR;
}

generador(claves, n_veces*N, N);

for(i = 0; i < N*n_veces; i++){
  gettimeofday(&t_ini, NULL);
  aux = busca_diccionario(d, claves[i], &ppos, metodo);


	gettimeofday(&t_fin, NULL);
  if(aux == ERR){
    free(claves);
    free(d);
    return ERR;
  }

  secs += (double)(t_fin.tv_sec + (double)t_fin.tv_usec/1000000) - (double)(t_ini.tv_sec + (double)t_ini.tv_usec/1000000);
  med += aux;
  if(min == -1 && max == -1) {
    min = aux;
    max = aux;
    continue;
  }

  if(aux < min) min = aux;
  if(aux > max) max = aux;

}

ptiempo->N = N;
ptiempo->n_elems = N*n_veces;
ptiempo->max_ob = max;
ptiempo->min_ob = min;
ptiempo->medio_ob = (med/(N*n_veces));
ptiempo->tiempo = (secs/(N*n_veces));

free(claves);
libera_diccionario(d);
free(perm);

return OK;

}


/***************************************************/
/* Funcion: genera_tiempos_busqueda                */
/* Fecha: 24/11/2017                               */
/* Grupo 1201                                      */
/* Lucía Rivas y Daniel Santo-Tomás                */
/***************************************************/

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
  int orden, char* fichero,
  int num_min, int num_max,
  int incr, int n_veces){

    if(!metodo || !generador || !fichero || num_min <=0 || num_max <= num_min || incr <= 0 || n_veces <= 0 ) return ERR;

    int i;

    PTIEMPO tiempo = (PTIEMPO)malloc(sizeof(TIEMPO)*(((num_max - num_min)/incr) + 1));
    PTIEMPO aux;
    if(!tiempo) return ERR;

    aux = tiempo;

    for(i = num_min ; i <= num_max ; i += incr){
      printf("tamaño %d\n",i);
      if(tiempo_medio_busqueda( metodo, generador, orden, i, n_veces, aux)== ERR) return ERR;
      aux++;
    }

    if(guarda_tabla_tiempos(fichero, tiempo, (((num_max - num_min)/incr) + 1)) == ERR) return ERR;

    free(tiempo);

    return OK;
  }
