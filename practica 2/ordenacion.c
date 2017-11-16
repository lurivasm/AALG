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
/* Funcion: QuickSort   Fecha:20/10/2017           */
/* Funcion que ordena una tabla                    */
/***************************************************/

int QuickSort(int* tabla, int ip, int iu){
	if(!tabla || ip < 0 || ip > iu) return ERR;
	if(ip == iu) return OK;
	int OB = 0,pos = 0;


	OB += partir(tabla, ip, iu, &pos);
	if(OB == ERR) return ERR;

	if(ip < pos-1) OB += QuickSort(tabla, ip, pos-1);
	if(pos+1 < iu) OB += QuickSort(tabla, pos+1, iu);

	return OB;
}


/***************************************************/
/* Funcion: Partir      Fecha:20/10/2017           */
/* Funcion que parte una tabla para QuickSort      */
/***************************************************/

int partir(int *tabla, int ip, int iu, int *pos){
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	int k, cont = 0, aux, i;

	cont = medio_avg(tabla, ip, iu, pos);
	if(cont == ERR) return ERR;

	k = tabla[*pos];
	aux = tabla[ip];
	tabla[ip] = tabla[*pos];
	tabla[*pos] = aux;

	*pos = ip;
	for(i = ip+1; i <= iu; i++){
		cont++;
		if(tabla[i] < k){
			(*pos)++;
			aux = tabla[i];
			tabla[i] = tabla[*pos];
			tabla[*pos] = aux;
		}
	}
	aux = tabla[ip];
	tabla[ip] = tabla[*pos];
	tabla[*pos] = aux;
	return cont;
}



/***************************************************/
/* Funcion: Medio       Fecha:20/10/2017           */
/* Funcion que establece un pivote para QuickSort  */
/***************************************************/
int medio(int *tabla, int ip, int iu, int *pos){
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	*pos = ip;
	return 0;
}
/***************************************************/
/* Funcion: Medio_avg       Fecha:20/10/2017       */
/* Funcion que establece un pivote para QuickSort  */
/***************************************************/
int medio_avg(int *tabla, int ip, int iu, int *pos){
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	*pos = (ip + iu)/2;
	return 0;
}

/***************************************************/
/* Funcion: Medio_avg       Fecha:20/10/2017       */
/* Funcion que establece un pivote para QuickSort  */
/***************************************************/
int medio_stat(int *tabla, int ip, int iu, int *pos){
	if(!tabla || ip < 0 || ip > iu || !pos) return ERR;
	int m;
	m = (ip + iu)/2;

	if(tabla[ip] < tabla[iu]){
		if(tabla[iu] < tabla[m]) *pos = iu;
		if(tabla[m] < tabla[ip]) *pos = ip;
	}
	if(tabla[ip] < tabla)

	return 0;
}
