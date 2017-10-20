/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autores: Lucía Rivas y Daniel Santo-Tomás
 * Version: 1.0
 * Fecha: 29/09/2017
 *
 */


#include "ordenacion.h"
#include <stdio.h>
#include <stdlib.h>

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

/***************************************************/
/* Funcion: MergeSort    Fecha:20/10/2017          */
/* Funcion que ordena una tabla                    */
/***************************************************/
int MergeSort(int* tabla, int ip, int iu){
	if(!tabla || ip < 0 || ip > iu) return ERR;
	if(ip == iu) return OK;

	int M;

	M = (ip + iu)/2;
	if(MergeSort(tabla,ip,M) == ERR) return ERR;
	if(MergeSort(tabla,M+1,iu) == ERR) return ERR;
	return Merge(tabla,ip,iu,M);
}

/***************************************************/
/* Funcion: Merge   Fecha:20/10/2017               */
/* Funcion que combina los dos lados de una tabla  */
/*  ambos ordenados                                */
/***************************************************/
int Merge(int* tabla, int ip, int iu, int imedio){
	if(!tabla) return ERR;

	int i, j, k,cont = 0;
	int *aux;
	aux = (int*)malloc(sizeof(int)*(iu-ip+1));
	if(!aux) return ERR;

	i = ip;
	j = imedio + 1;
	k = ip;

	while(i <= imedio && j <= iu){
		cont++;
		if (tabla[i] < tabla[j]){
			aux[k - ip] = tabla[i];
			i++;
		}
		else {
			aux[k - ip] = tabla[j];
			j++;
		}
		k++;
	}

	if (i > imedio){
		while(j <= iu) {
			aux[k - ip] = tabla[j];
			j++;
			k++;
		}
	}

	else if ( j > iu){
		while(i <= imedio){
			aux[k - ip] = tabla[i];
			i++;
			k++;
		}
	}

	for(i = ip; i <= iu; i++){
		tabla[i] = aux[i - ip];
	}
	free(aux);
	return cont;
}

/***************************************************/
/* Funcion: QuickSort   Fecha:20/10/2017               */
/* Funcion que ordena una tabla                    */
/***************************************************/



int QuickSort(int* tabla, int ip, int iu){
	if(!tabla || ip < 0 || ip > iu) return ERR;
	if(ip == iu) return OK;
	int M;
  int* pos;

	M = partir(tabla,ip,iu,pos);

	if(ip < M-1) QuickSort(tabla,ip,M-1);
	if(M+1 < iu) QuickSort(tabla,M+1,iu);

	return OK;
}
