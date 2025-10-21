#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoDado {
  char nome[100];
  float preco;
  unsigned quantidade;
} tipoDado;

typedef struct tipoNo {
  tipoDado dado;
  struct tipoNo *prox;
} tipoNo;

typedef struct tipoLista {
  tipoNo *prim;
  unsigned nProd;
  float total;
} tipoLista;

void criar(tipoLista *l1) {
  l1->prim = NULL;
  l1->nProd = 0;
  l1->total = 0;
}

void addProd(tipoLista *l1, tipoDado *dado) {
  float valor = dado->preco * dado->quantidade;
  tipoNo *no;
  no = (tipoNo *)malloc(sizeof(tipoNo));
  no->dado = *dado;
  no->prox = l1->prim;
  l1->prim = no;
  l1->total += valor;
}
}

void removeProd(tipoLista *l1, unsigned id) {
  tipoNo *aux, *temp;
  unsigned cont = 0;
  aux = l1->prim;

  // Remove se for o primeiro
  if (id == 0) {
    temp = l1->prim;
    l1->prim = aux->prox;
    temp->prox = NULL;
    free(temp);
    return;
  }

  while (aux && cont < id) {
    cont++;
    aux = aux->prox;
  }

  if (cont == id - 1) {
    temp = aux->prox;
    aux->prox = temp->prox;
    temp->prox = NULL;
    free(temp);
  }
}

void mostrarLista(tipoLista *lista) {
  tipoNo *aux;
  unsigned cont = 0;
  aux = lista->prim;

  system("clear");
  printf("---------------------------------------------------------------------"
         "\n");
  printf("                         LISTA DE COMPRAS                            "
         "\n");
  printf("---------------------------------------------------------------------"
         "\n");
  printf("%-4s  %-30s %10s %8s %12s\n", "ID", "NOME", "PREÇO", "QUANT.",
         "TOTAL");
  printf("---------------------------------------------------------------------"
         "\n");
  while (aux) {
    printf("%-4u  %-30.30s %10.2f %8u %12.2f\n", cont, aux->dado.nome,
           aux->dado.preco, aux->dado.quantidade,
           aux->dado.preco * aux->dado.quantidade);
    aux = aux->prox;
    cont++;
  }
  printf("---------------------------------------------------------------------"
         "\n");
  printf("%54s R$ %10.2f\n", "TOTAL DA COMPRA:", lista->total);
  printf("---------------------------------------------------------------------"
         "\n");
}

void lerDado(tipoDado *prod) {
  system("clear");
  printf("---------------------------------------------------------------------"
         "\n");
  printf("                         ADICIONAR PRODUTO                           "
         "\n");
  printf("---------------------------------------------------------------------"
         "\n");
  printf("Nome do produto: ");
  scanf("%100[^\n]", prod->nome);
  printf("Preço: R$ ");
  scanf("%f%*c", &prod->preco);
  printf("Quantidade: ");
  scanf("%u%*c", &prod->quantidade);
  printf("---------------------------------------------------------------------"
         "\n");
}

int main() {
  tipoLista lista;
  tipoDado produtoAux;
  unsigned choice = 1, idRemove;
  criar(&lista);

  while (choice) {
    system("clear");
    printf("-------------------------------------------------------------------"
           "--\n");
    printf("                    LISTA DE COMPRAS MANEIRA                       "
           "  \n");
    printf("-------------------------------------------------------------------"
           "--\n");
    printf("  1 - LISTAR PRODUTOS\n");
    printf("  2 - ADICIONAR ITEM\n");
    printf("  3 - DELETAR ITEM\n");
    printf("  0 - SAIR\n");
    printf("-------------------------------------------------------------------"
           "--\n");
    printf("Escolha uma opção: ");
    scanf("%u%*c", &choice);

    switch (choice) {
    case 1:
      mostrarLista(&lista);
      break;
    case 2:
      lerDado(&produtoAux);
      addProd(&lista, &produtoAux);
      break;
    case 3:
      printf("\nID do Produto para deleção: ");
      scanf("%u", &idRemove);
      removeProd(&lista, idRemove);
      printf("Produto removido com sucesso!\n");
      break;
    case 0:
      system("clear");
      printf("-----------------------------------------------------------------"
             "----\n");
      printf("                         Saindo do sistema...                    "
             "    \n");
      printf("-----------------------------------------------------------------"
             "----\n");
      break;
    default:
      printf("\n>>> Número Inválido <<<\n");
    }
    if (choice != 0) {
      printf("\n\nPressione ENTER para continuar...");
      getchar();
    }
  }
}
