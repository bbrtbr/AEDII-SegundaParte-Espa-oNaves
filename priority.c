#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "priority.h"

#define MAX_LEN 100
#define Result bool

#define Ok true
#define Err false

Fila *nova()
{
  Fila *fila = (Fila *)malloc(sizeof(Fila));

  if (fila == NULL)
  {
    printf("Um erro ocorreu ao alocar a nave.\n");
    return NULL;
  }

  fila->numNaves = 0;
  return fila;
}

void dropFila(Fila *fila)
{
  free(fila);
}

Result inserir(Fila *fila, Nave elemento)
{
  if (cheia(fila))
    return Err;

  fila->naves[fila->numNaves] = elemento;
  elevar(fila, fila->numNaves);
  fila->numNaves++;

  return Ok;
}

Result removerTopo(Fila *fila)
{
  if (vazia(fila))
    return Err;

  fila->numNaves--;
  fila->naves[0] = fila->naves[fila->numNaves];
  abaixar(fila, 0);

  return Ok;
}

Nave *topo(Fila *fila)
{
  if (vazia(fila))
    return NULL;

  return &(fila->naves[0]);
}

void elevar(Fila *fila, int indexFilho)
{
  int indexPai = (indexFilho - 1) / 2;
  Nave nave;

  while ((indexFilho > 0) && (fila->naves[indexPai].prioridade < fila->naves[indexFilho].prioridade))
  {
    nave = fila->naves[indexFilho];

    fila->naves[indexFilho] = fila->naves[indexPai];
    fila->naves[indexPai] = nave;

    indexFilho = indexPai;
    indexPai = (indexPai - 1) / 2;
  }
}

void abaixar(Fila *fila, int indexPai)
{
  int indexFilho = 2 * indexPai + 1;
  Nave nave;

  while (indexFilho < fila->numNaves)
  {
    if (indexFilho < fila->numNaves - 1 && fila->naves[indexFilho].prioridade < fila->naves[indexFilho + 1].prioridade)
    {
      indexFilho++;
    }

    if (fila->naves[indexPai].prioridade >= fila->naves[indexFilho].prioridade)
    {
      break;
    }

    nave = fila->naves[indexPai];
    fila->naves[indexPai] = fila->naves[indexFilho];
    fila->naves[indexFilho] = nave;

    indexPai = indexFilho;
    indexFilho = 2 * indexPai + 1;
  }
}

bool cheia(Fila *fila)
{
  if (fila->numNaves >= MAX_LEN)
    return true;
  return false;
}

bool vazia(Fila *fila)
{
  if (fila->numNaves <= 0)
    return true;
  return false;
}
