/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Matheus de Oliveira Marçal
Matricula:201722040149
Descricao do programa: Problema da mochila - Algoritimo Tentativa e Erro
Data:08/09/2018
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
struct timeval inicio, fim;

typedef struct itm {                       //Estrutura dos itens
  int numero;
  int peso;
  int valor;
} item;
#define itens_mochila 500                   //Numero maximo de itens que pode entrar na mochila como informado pela professora
int valormax=0,tam_mochila,num_itens,j;     //Variaveis globais de todas as funções

int somacontador(int cont[])               //Função para somar todos os numeros de um vetor
{
  int soma=0;
  for (int i = 0; i < num_itens; ++i)
  {
    soma=soma+cont[i];
  }
  return soma;
}

void contador(int cont[],int posicao)       //Transforma um vetor int em um contador binario
{
  if(cont[posicao]==1)           //Faz ele contar em binario
    {
      cont[posicao]=0;   
      contador(cont,posicao+1);
    }
  else if(cont[posicao]==0)
    {
      cont[posicao]++;
    }
}

void erro(item itens[],int tam_mochila,int num_itens,item escolha[],item mochila[],int cont[])  //Função das tentativas
{
  while(somacontador(cont)!=num_itens)  //Enquanto a soma nao for igual ao numero de itens ou sera o vetor estar com (1,1,1,...,1) assim tendo olhado todas as possibilidades
  {
  contador(cont,0);   //Chama a função contador
  int flag=0 ,valorescolha=0,pesoescolha=0;   //Variaveis para comparação
  j=0;
    for(int k=0; escolha[k].peso!=0; k++)    //zera o vetor de escolha
      {
        escolha[k].valor=0;
        escolha[k].peso=0;
        escolha[k].numero=0;
      }
  for (int i = 0; i<num_itens; ++i)
  {
    if(cont[i]==1)          //Toda vez que o contador tiver 1 em uma casa quer dizer que o numero esta presente o item com o numero da casa esta na escolha
    {
      escolha[j]=itens[i];
      j++;                  //variavel j marcando onde ele pode entrar na escolha
      valorescolha=valorescolha+itens[i].valor;   //vamos salvando o valor total da escolha
      pesoescolha=pesoescolha+itens[i].peso;      // e o peso tambem
    }  if(pesoescolha>tam_mochila)
        break;
    
  }
    if(valorescolha>valormax && pesoescolha <=tam_mochila)    // se o valor for maior que o ja obtido e o couber na mochila coloca na mochila
      { 
        for (int v = 0; v < j; ++v)
          {
           mochila[v]=escolha[v];
          }  
        valormax=valorescolha;    //e salva o valor
      }   
  }
}

int main()
{
  long totalmicroseg, totalseg; //Variaveis para medir o tempo 
  gettimeofday(&inicio, NULL);    //Função para pegar o tempo q inicia
  int pesototal=0,valortotal=0;                           
  FILE *fp;     //Ponteiro Para abrir o arquivo
  fp = fopen("teste.txt","r");    //Arquivo com as variaveis de teste
  if (!fp)
    printf ("Erro na abertura do arquivo.");
    fscanf(fp,"%i",&tam_mochila);             //Escaneia os valores
    fscanf(fp,"%i",&num_itens);
    item itens [num_itens];
    item escolha [num_itens];
    for (int i=0;i<num_itens;i++)                 //Salva em um vetor de itens 
    {
      itens[i].numero=i;
      fscanf(fp,"%i %i",&itens[i].peso,&itens[i].valor);
      //printf(" %i %i %i\n",itens[i].numero,itens[i].peso,itens[i].valor );
    }
    printf("\n");
    fclose(fp);
    item aux;
    for(int i=0;i<num_itens;i++)
    {
      if(itens[0].peso<itens[1].peso)
      {
        aux=itens[0];
        itens[0]=itens[1];
        itens[1]=aux;
      }
      if(itens[i].peso<itens[i+1].peso)        //Ordena o vetor
      {
        aux=itens[i];
        itens[i]=itens[i+1];
        itens[i+1]=aux;
        i=0;
      }
    }
   
    int cont[num_itens];
    for (int i = 0; i < num_itens; ++i)
    {
        cont[i]=0;                          //Zera o contador
    }
  item mochila[itens_mochila];
  erro(itens,tam_mochila,num_itens,escolha,mochila,cont); //Chama a função das tentativas
  fp=fopen("resultado.txt","w+");
  if (!fp)
      printf ("Erro na abertura do arquivo.");
      for(int i=0; mochila[i].peso!=0; i++)
    	{
           	fprintf(fp, "Numero do item:%i - Peso do item: %i - Valor do item: %i\n", mochila[i].numero, mochila[i].peso, mochila[i].valor);
        		pesototal=pesototal+mochila[i].peso;
           	valortotal=valortotal+mochila[i].valor;
      }
      fprintf(fp, "Peso total: %i\n",pesototal );     // E o peso e o valor tambem
      fprintf(fp, "Valor total: %i\n",valortotal );

      fclose(fp);
   
  gettimeofday(&fim, NULL);
  totalseg = fim.tv_sec - inicio.tv_sec;
  totalmicroseg = fim.tv_usec - inicio.tv_usec;

  if (totalmicroseg <0)   // função para printar o tempo na tela
   { totalmicroseg += 1000000;
   totalseg -= 1;
   };
   printf ("\n");
   printf ("***************************************************************\n");
   printf ("Tempo total: %ld segundos e %ld microssegundos.\n", totalseg, totalmicroseg);
   printf ("***************************************************************\n");
   printf ("\n");
   return(0);

}
