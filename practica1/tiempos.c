/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:6/10/2017*/
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
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
    clock_t t_ini, t_fin;

    perms = genera_permutaciones(n_perms,N);
    if(!perms) return ERR;

    for(i = 0; i < n_perms; i++){
	t_ini = clock();
	aux = metodo(perms[i], 0, N-1);
	t_fin = clock();
        secs += (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
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

    free(perms);  
 
    return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha: 6/10/2017*/
/*                                                 */
/* Vuestra documentacion                           */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
    if(!metodo || !fichero || num_min <=0 || num_max <= num_min || incr <= 0 || n_perms <= 0 ) return ERR;

    int i;

    PTIEMPO tiempo = (PTIEMPO)malloc(sizeof(TIEMPO)*(num_max - num_min + 1));
    PTIEMPO aux;
    if(!tiempo) return ERR;

    aux = tiempo;

    for(i = num_min ; i <= num_max ; i + incr){
	if(tiempo_medio_ordenacion( metodo,n_perms, i, tiempo) == ERR) return ERR;
	tiempo++;
    }

    if(guarda_tabla_tiempos(fichero, aux, (num_max - num_min + 1)) == ERR) return ERR;

    free(tiempo);

    return OK;

}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:6/10/2017   */
/*                                                 */
/* Vuestra documentacion (formato igual            */
/* que en el primer apartado):                     */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
    if(!fichero || !tiempo || n_tiempos <= 0 ) return ERR;

    FILE *f = NULL;
    int i;
    
    f = fopen(fichero,"w");
    if (!f) return ERR;

    for(i = 0; i <n_tiempos ; i++){
         fprintf(f,"%d %lf %lf %d %d \n",tiempo->N, tiempo->tiempo, tiempo->medio_ob, tiempo->max_ob, tiempo->min_ob);
	 tiempo++;
    }

    fclose(f);
    
    return OK;
}


