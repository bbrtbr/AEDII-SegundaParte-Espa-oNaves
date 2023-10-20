#ifndef PRIORITY_H
#define PRIORITY_H

#include <stdbool.h>

#define MAX_LEN 100
#define MAX_REC 3
#define Result bool

typedef struct
{
  char nome[MAX_LEN];
  int quantidade;
} Recurso;

typedef struct
{
  int id;
  char nome[MAX_LEN];
  char planeta[MAX_LEN];
  int idade;
} Passageiro;

typedef struct
{
  int prioridade;

  Passageiro passageiros[MAX_LEN];
  int numPassageiros;

  Recurso recursos[MAX_REC];
  int numRecursos;

  int tipo;
} Nave;

typedef struct
{
  Nave naves[MAX_LEN];
  int numNaves;
} Fila;

Fila *nova();
void dropFila(Fila *fila);

Result inserir(Fila *fila, Nave elemento);
Result removerTopo(Fila *fila);

Nave *topo(Fila *fila);

void elevar(Fila *fila, int indexFilho);
void abaixar(Fila *fila, int indexPai);

bool cheia(Fila *fila);
bool vazia(Fila *fila);

#endif