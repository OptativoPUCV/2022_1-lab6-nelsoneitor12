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
    int *submatriz;
    int i,j,k, l, m;
    for(i=0;i<9;i++){
      columna=(int*) calloc(9, sizeof(int));
      fila=(int*) calloc(9, sizeof(int));
      for(j=0;j<9;j++){
           k=n->sudo[i][j];
           l=n->sudo[j][i];
          if(fila[l-1]==l && fila[l-1]!=0) return 0;
            fila[l-1]=l;
          if(columna[k-1]==k && columna[k-1]!=0) return 0;
            columna[k-1]=k;
      }
    }
    for(i=0;i<9;i+=3){
      for(j=0;j<9;j+=3){
        submatriz=calloc(9, sizeof(int));
        for(l=i;l<3;l++){
          for(m=j;m<3;m++){
            k=n->sudo[l][m];
            if(submatriz[k-1]==k && submatriz[k-1]!=0) return 0;
            submatriz[k-1]=k;
          }
        }
      }
    }
    
    return 1;
}


List* get_adj_nodes(Node* n){
    List* lista=createList();
    int i,j,k;
    Node *adj;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[i][j]==0){
          for(k=1;k<10;k++){
            n->sudo[i][j]=k;
            if (is_valid(n))
            {
              adj=copy(n);
              pushBack(lista, adj);
            }
          }
          n->sudo[i][j]=0;
          return lista;
        }
      }
    }
  return lista;
}


int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){ 
        if(n->sudo[i][j]==0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *S=createStack();
  push(S, initial);
  while (S){
     Node* n=top(S);
     pop(S);
     if (is_final(n)) return n;
     List* adj=get_adj_nodes(n);
     Node* aux= first(adj);
     while(aux){
        push(S,aux);
        aux=next(adj);
        (*cont)+=1;
     }
     free(n);
  }
  printf("el contador es:%d", *cont);
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