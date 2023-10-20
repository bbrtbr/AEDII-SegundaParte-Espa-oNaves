// bibliotecas e definições de structs e funções
#include "priority.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define Ok true
#define Err false

// Funções
void clear();
int randomNum(int min, int max);
void print(Fila *fila);
int fatorial(int n);

bool permRegistrada(Recurso permRegs[][MAX_REC], int nPerm, Recurso rec[3]);

char **split(const char *str, char separator, int *count);
void dropSplit(char **strings, int count);

Result lerArquivo(Fila *fila, char *nome);
void escreverArquivo(Fila *fila, char *nome);

Nave novaNave();
Passageiro novoPassageiro();
Recurso novoRecurso();

int main(void)
{
  // Inicialização da semente para geração de números aleatórios
  srand((unsigned)time(NULL));

  // Criação de uma fila
  Fila *fila = nova();
  int nPerm = fatorial(MAX_REC);
  Recurso permRegs[nPerm][MAX_REC];
  int nNaves = 0;

  if (!lerArquivo(fila, "dados.txt"))
  {
    return 1;
  }

  while (true)
  {
    clear();
    int opcao = 0;

    // Menu de Espaçonaves
    printf("Menu de Espaçonaves\n\n");
    print(fila);
    printf("1 - Inserir nave\n");

    if (!vazia(fila))
    {
      printf("2 - Remover nave com maior prioridade\n");
      printf("3 - Salvar no arquivo\n");
    }
    printf("\n0 - Sair\n\n");

    printf("> ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      inserir(fila, novaNave());
      break;

    case 2: {
      Nave *t = topo(fila);

      if (!permRegistrada(permRegs, nPerm, t->recursos)) {
        memcpy(permRegs[nPerm], t->recursos, sizeof(int) * MAX_REC);
        nPerm++;
      }

      if (nNaves >= nPerm) {
        printf("A abertura se expandiu!\n");

        nNaves = 0;
        memset(permRegs, 0, sizeof(permRegs));
      }
      
      removerTopo(fila);
      break;
    }
    
    case 3:
      escreverArquivo(fila, "dados.txt");
      break;

    case 0:
      // Finaliza o programa
      return 0;
    }
  }

  // Libera a memória alocada para a fila
  dropFila(fila);
  return 0;
}

void clear()
{
  system(CLEAR);
}

// Função para gerar um número aleatório
int randomNum(int min, int max)
{
  return min + rand() % max;
}

void print(Fila *fila)
{
  for (int i = 0; i < fila->numNaves; i++)
  {
    printf("%d | Prioridade: %d\n", i + 1, fila->naves[i].prioridade);
  }

  if (!vazia(fila))
    printf("\n");
}

int fatorial(int n) {
  if (n <= 1) return 1;
  return n * fatorial(n - 1);
}

bool permRegistrada(Recurso permRegs[][MAX_REC], int nPerm, Recurso rec[3]) {
    for (int i = 0; i < nPerm; i++) {
        bool eq = true;

        for (int j = 0; j < 3; j++) {
            if (strcmp(permRegs[i][j].nome, rec[j].nome) != 0) {
                eq = false;
                break;
            }
        }

        if (eq) return true;
    }

    return false;
}

// Função para dividir uma string em substrings com base em um separador
char **split(const char *str, char separator, int *count)
{
  int startIndex = 0, endIndex = 0;
  int numTokens = 0;
  int strLength = strlen(str);

  // Loop para contar o número de substrings
  for (int i = 0; i <= strLength; i++)
  {
    if (str[i] == separator || i == strLength)
    {
      endIndex = i;
      numTokens++;
      startIndex = endIndex + 1;
    }
  }

  // Aloca memória para armazenar as substrings
  char **strings = (char **)malloc(numTokens * sizeof(char *));
  if (strings == NULL)
  {
    *count = 0;
    return NULL;
  }

  // Reinicializa as variáveis para reutilização
  startIndex = 0;
  endIndex = 0;
  int tokenIndex = 0;

  // Substrings
  for (int i = 0; i <= strLength; i++)
  {
    if (str[i] == separator || i == strLength)
    {
      endIndex = i;

      // Calcula o tamanho da substring
      int tokenLength = endIndex - startIndex;

      strings[tokenIndex] = (char *)malloc((tokenLength + 1) * sizeof(char));

      if (strings[tokenIndex] == NULL)
      {

        for (int j = 0; j < tokenIndex; j++)
        {
          free(strings[j]);
        }

        free(strings);
        *count = 0;
        return NULL;
      }

      strncpy(strings[tokenIndex], str + startIndex, tokenLength);
      strings[tokenIndex][tokenLength] = '\0';

      tokenIndex++;
      startIndex = endIndex + 1;
    }
  }

  *count = numTokens;
  return strings;
}

void dropSplit(char **strings, int count)
{
  if (strings != NULL)
  {
    for (int i = 0; i < count; i++)
    {
      free(strings[i]);
    }

    free(strings);
  }
}

// Função para escrever os dados da fila
void escreverArquivo(Fila *fila, char *nome)
{
  FILE *file = fopen(nome, "w");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }

  for (int i = 0; i < fila->numNaves; i++)
  {
    // Escreve as informações da fila no arquivo
    fprintf(file, "%d,%d", fila->naves[i].prioridade, fila->naves[i].numPassageiros);

    for (int j = 0; j < fila->naves[i].numPassageiros; j++)
    {
      Passageiro pass = fila->naves[i].passageiros[j];
      fprintf(file, ",%s,%s,%d,%d", pass.nome, pass.planeta, pass.idade, pass.id);
    }

    fprintf(file, ",%d", fila->naves[i].numRecursos);

    for (int j = 0; j < fila->naves[i].numRecursos; j++)
    {
      Recurso rec = fila->naves[i].recursos[j];
      fprintf(file, ",%s,%d", rec.nome, rec.quantidade);
    }

    fprintf(file, "\n");
  }

  fclose(file);
  printf("Dados salvos com sucesso no arquivo '%s'.\n", nome);
}

// Função para ler dados de um arquivo e preencher a fila
Result lerArquivo(Fila *fila, char *nome)
{
  FILE *file = fopen(nome, "r");
  char line[MAX_LEN];

  if (file == NULL)
  {
    return Err;
  }

  while (fgets(line, sizeof(line), file) != NULL)
  {
    int length = 0;
    char **strings = split(line, ',', &length);

    if (strings == NULL)
      return Err;

    Nave nave;
    int index = 0;

    // Lê as informações da linha e preenche a estrutura Nave
    nave.prioridade = atoi(strings[index++]);
    int countPass = atoi(strings[index++]);

    for (int i = 0; i < countPass; i++)
    {
      Passageiro pass;

      strcpy(pass.nome, strings[index++]);
      strcpy(pass.planeta, strings[index++]);
      pass.idade = atoi(strings[index++]);
      pass.id = atoi(strings[index++]);

      nave.passageiros[i] = pass;
    }

    int countRec = atoi(strings[index++]);

    for (int i = 0; i < countRec; i++)
    {
      Recurso rec;

      strcpy(rec.nome, strings[index++]);
      rec.quantidade = atoi(strings[index++]);

      nave.recursos[i] = rec;
    }

    // Insere a nave na fila e libera a memória alocada para as substrings
    inserir(fila, nave);
    dropSplit(strings, length);
  }

  fclose(file);
  return Ok;
}

Nave novaNave()
{
  Nave nave;

  nave.tipo = randomNum(1, 10);
  nave.prioridade = randomNum(0, 100);
  int probabilidade = randomNum(1, 10);

  if (probabilidade == 1)
  {
    nave.prioridade = randomNum(0, 100);
    printf("Foi detectado um passageiro doente ou clandestino, trocando prioridade.\n");
  }

  printf("Digite o número de passageiros: ");
  scanf("%d", &nave.numPassageiros);

  for (int i = 0; i < nave.numPassageiros; i++)
  {
    printf("\nPassageiro #%d\n", i + 1);
    nave.passageiros[i] = novoPassageiro();
  }

  printf("Digite o número de recursos: ");
  scanf("%d", &nave.numRecursos);

  for (int i = 0; i < nave.numRecursos; i++)
  {
    printf("\nRecurso #%d\n", i + 1);
    nave.recursos[i] = novoRecurso();
  }

  return nave;
}

Passageiro novoPassageiro()
{
  Passageiro passageiro;

  passageiro.id = randomNum(0, 100);

  printf("Digite o nome do passageiro: ");
  scanf("%s", passageiro.nome);

  printf("Digite a idade do passageiro: ");
  scanf("%d", &passageiro.idade);

  printf("Digite o planeta do passageiro: ");
  scanf("%s", passageiro.planeta);

  return passageiro;
}

Recurso novoRecurso()
{
  Recurso recurso;

  printf("Nome do recurso transportado: ");
  scanf("%s", recurso.nome);

  printf("Quantidade do recurso transportado: ");
  scanf("%d", &recurso.quantidade);

  return recurso;
}
