#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
  srand(time(0));
  int tam_mochila,num_itens,peso,valor;
  printf("Digite o tamanho da mochila\n");
  scanf("%i",&tam_mochila);
  printf("Digite o numero de itens\n");
  scanf("%i",&num_itens);
  FILE *fp;
  fp=fopen("teste.txt","w+");
  fprintf(fp,"%i\n%i\n",tam_mochila,num_itens);
  for (int i=0;i<num_itens;i++){
    peso=rand()%(tam_mochila-1)+1;
    valor=rand()%30+1;
    fprintf(fp, "%i %i\n",peso,valor);
  }
  fclose(fp);
}
