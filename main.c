#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
      pos = 0;
      
    int opcao;
    do{
      printf("\nMenu principal\n");
      printf("1 - Criar tarefa\n");
      printf("2 - Deletar tarefa\n");
      printf("3 - Listar tarefas\n");
      printf("4 - Salvar tarefas\n");
      printf("5 - Carregar tarefas\n");
      printf("0 - Sair\n");
      printf("Escolha uma opcao: ");

      scanf("%d", &opcao);
      clearBuffer();
      opcao--;
      if(opcao > 4){
        printf("Opcao invalida\n");
      }
      else if(opcao >= 0){
        ERROS erro = fs[opcao](tarefas, &pos);
        switch(erro){
          case MAX_TAREFA:
              printf("Nao e possivel criar mais tarefas\n");
            break;
          case OK:
              break;
          case SEM_TAREFAS:
              printf("Nao existem tarefas\n");
            break;
          case NAO_ENCONTRADO:
              printf("Tarefa nao encontrada\n");
            break;
          case ABRIR:
              printf("Nao foi possivel abrir o arquivo\n");
            break;
          case ESCREVER:
              printf("Nao foi possivel escrever no arquivo\n");
            break;
          case LER:
              printf("Nao foi possivel ler do arquivo\n");
            break;
          case FECHAR:
              printf("Nao foi possivel fechar o arquivo\n");
            break;
        }
      }
      else{
        printf("Sair...\n");
      }

    } while(opcao >= 0);
  
    fs[3](tarefas, &pos);
}
