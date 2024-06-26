#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    char ch;
    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    if(tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade <= 10){
      
      clearBuffer();
      printf("Entre com a categoria: ");
      fgets(tarefas[*pos].categoria, TOTALCAT, stdin);
      tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';
      
      printf("Entre com a descricao: ");
      fgets(tarefas[*pos].descricao, TOTALDESC, stdin);
      tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';
      
      *pos = *pos + 1;

      return OK;
    }else{
      printf("Entre com uma prioridade de 1 a 10\n");
    printf("\n");
    }
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;
  
    char categoria_escolhida[TOTALCAT];
    printf("Categoria que deseja listar (deixe em branco para listar todas as tarefas): ");
    fgets(categoria_escolhida, sizeof(categoria_escolhida), stdin); 

  if (categoria_escolhida[strlen(categoria_escolhida) - 1] == '\n') {
      categoria_escolhida[strlen(categoria_escolhida) - 1] = '\0';
  }


    int encontrou_tarefas = 0;
    for(int i=0; i<*pos; i++){
      if(strcmp(tarefas[i].categoria, categoria_escolhida) == 0){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
        encontrou_tarefas = 1;
      }else if (strcmp(categoria_escolhida, "\0") == 0){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
        encontrou_tarefas = 1;
      }
    }
    if(encontrou_tarefas == 0){
      printf("Tarefas dessa categoria não encontradas");
    }
  
    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}

ERROS exportar(Tarefa tarefas[], int *pos){
  char nome_arquivo[100];
  printf("Escolha o nome do arquivo: ");
  scanf("%s", nome_arquivo);
  clearBuffer();
  
  char categoria_escolhida[TOTALCAT];
  printf("Categoria que deseja listar (deixe em branco para listar todas as tarefas): ");
  fgets(categoria_escolhida, sizeof(categoria_escolhida), stdin); 

  if (categoria_escolhida[strlen(categoria_escolhida) - 1] == '\n') {
      categoria_escolhida[strlen(categoria_escolhida) - 1] = '\0';
  }
  
  FILE *f = fopen(nome_arquivo, "w"); 
  if(f == NULL)
      return ABRIR;

  int qtd = 0;
  
  for (int i = 0; i < *pos; i++) {
     if(strcmp(tarefas[i].categoria, categoria_escolhida) == 0){
        fprintf(f, "Pos: %d\t", i+1);
        fprintf(f, "Prioridade: %d\t", tarefas[i].prioridade);
        fprintf(f, "Categoria: %s\t", tarefas[i].categoria);
        fprintf(f, "Descricao: %s\n", tarefas[i].descricao);
        qtd = qtd + 1;
     }else if (strcmp(categoria_escolhida, "\0") == 0){
        fprintf(f, "Pos: %d\t", i+1);
        fprintf(f, "Prioridade: %d\t", tarefas[i].prioridade);
        fprintf(f, "Categoria: %s\t", tarefas[i].categoria);
        fprintf(f, "Descricao: %s\n", tarefas[i].descricao);
        qtd = *pos;
    }
    
  }
  
  fprintf(f, "Quantidade de Tarefas: %d\n", qtd);
  
  if (fclose(f) != 0)
      return FECHAR;

  return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
