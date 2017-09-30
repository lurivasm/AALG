/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: 
 * Version: 1.0
 * Fecha: 29/09/2017
 *
 */


#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha:29/09/2017                   */
/* Funcion que ordena una tabla                             */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu)
{
	if(!tabla || ip<0 || iu<0) return ERR;
	int cont,i,j,aux;
	cont =0;

	for(i = iu; i >= ip+1; i--){
		for(j = ip; j <= i-1; j++){
			cont++;
			if(tabla[j] > tabla[j+1]){
				aux = tabla[j];
				tabla[j] = tabla[j+1];
	 			tabla[j+1] = aux;
			}
		}
	}

	return cont;
}



