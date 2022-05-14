#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int *fila;
    int *columna;
    //int *submatriz;
    int i,j,k;
    for(i=0;i<9;i++){
      columna=(int*) calloc(9, sizeof(int));
      for(j=0;j<9;j++){
           k=n->sudo[i][j];
          if(columna[k-1]==k) return 0;
          else if(columna[k-1]==0) columna[k-1]=k;
          printf("%d", n->sudo[i][j]);
      }
      printf("\n");
    }
    for(j=0;j<9;j++){
      fila=(int*) calloc(9, sizeof(int));
      for(i=0;i<9;i++){
          k=n->sudo[i][j];
          if(fila[k-1]==0) fila[k-1]=k;
          else if(fila[k-1]==k) return 0;
          //printf("%d", fila[k-1]);
      }
      //printf("\n");
    }
    /*for(i=0;i<9;i+=3){
      for(j=0;j<9;j+=3){
        submatriz=(int*) calloc(9, sizeof(int));
        for (k=i;k<i+3;k++)
        {
          for(l=j;j<j+3;l++){
            if(submatriz[n->sudo[i][j]]==n->sudo[i][j]) return 0;
            else if(submatriz[n->sudo[i][j]]==0) submatriz[n->sudo[i][j]]=n->sudo[i][j];
          }
        }  
      }
    }*/
    return 1;
}


List* get_adj_nodes(Node* n){
    List* lista=createList();
    int i,j,k;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[i][j]==0){
          printf(" el numero =0 es %d\n\n", n->sudo[i][j]);
          for(k=1;k<10;k++){
            n->sudo[i][k]=k;
            if(is_valid(n)){
                Node* adj=copy(n);
                pushBack(lista, adj);
                printf("esValido\n");
                break;
            }
            printf("pasando por el for del adj\n");
          }
          return lista;
        }
      }
    }
  return lista;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/