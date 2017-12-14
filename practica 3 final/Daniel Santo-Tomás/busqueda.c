/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden)
{
  PDICC d;
  d = (PDICC)malloc(sizeof(DICC));
  if(!d) return NULL;
  d->tamanio = tamanio;
  d->orden = orden;
  d->tabla = (int*)malloc(sizeof(int)*tamanio);
  d->n_datos = 0;
  if(!d->tabla){
    free(d);
    return NULL;
  }
  return d;
}

void libera_diccionario(PDICC pdicc)
{
  if(!pdicc) return;
  free(pdicc->tabla);
  free(pdicc);
  return;
}

int inserta_diccionario(PDICC pdicc, int clave)
{
	if(!pdicc) return ERR;
  pdicc->n_datos ++;
  if(pdicc->n_datos > pdicc->tamanio){
    pdicc->n_datos--;
    return ERR;
  }
  if(pdicc->orden == NO_ORDENADO){
      pdicc->tabla[pdicc->n_datos-1] = clave;
      return 0;
  }

  int cont = 0,i = 0,aux;
  pdicc->tabla[pdicc->n_datos-1] = clave;
  i = pdicc->n_datos-2;
  aux = clave;
  while(i >= 0 && pdicc->tabla[i] > aux ){
    cont++;
    pdicc->tabla[i+1] = pdicc->tabla[i];
    i--;
  }
  pdicc->tabla[i+1] = aux;

  return cont;
}

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
  if(!pdicc || !claves || n_claves < 1) return ERR;
  int i,cont = 0,contaux = 0;
  for(i = 0; i < n_claves; i++){
    contaux = inserta_diccionario(pdicc, claves[i]);
    if(contaux == ERR) return ERR;
    cont += contaux;
  }
  return cont;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	if(!pdicc || !ppos) return ERR;
  int cont = 0;

  cont = metodo(pdicc->tabla, 0, pdicc->n_datos -1, clave, ppos);
  if(cont == ERR) return ERR;
  return cont;
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos)
{
  if(!tabla || !ppos) return ERR;
  int m, cont  = 0, i;
  if(P > U){
    i = P;
    P = U;
    U = i;
  }
  while(P <= U){
    m = (U+P)/2;
    cont++;
    if(tabla[m] == clave) {
      *ppos = m;
      return cont;
    }
    if(clave < tabla[m]) U = m-1;
    else P = m+1;
  }
  return NO_ENCONTRADO;
}

int blin(int *tabla, int P, int U, int clave, int *ppos)
{
	if(!tabla || !ppos) return ERR;
  int i, cont = 0;
  if(P > U){
    i = P;
    P = U;
    U = i;
  }
  for(i = 0; i <= U; i++){
    cont++;
    if(tabla[i] == clave) {
      *ppos = i;
      return cont;
    }
  }
  return NO_ENCONTRADO;
}

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
	if(!tabla || !ppos) return ERR;
  int i, aux, cont = 0;
  if(P > U){
    i = P;
    P = U;
    U = i;
  }
  for(i = 0; i <= U; i++){
    cont++;
    if(tabla[i] == clave) {
      if(i == 0){
        *ppos = i;
        return cont;
      }
      aux = tabla[i];
      tabla[i] = tabla[i-1];
      tabla[i-1] = aux;
      *ppos = i - 1;
      return cont;
    }
  }
    return NO_ENCONTRADO;

}
