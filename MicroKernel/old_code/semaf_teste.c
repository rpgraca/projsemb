#include <stdio.h>
#include "semaforos.c"

int main(){
  
  uint8_t semaf_id = 0;
  int8_t semaf_status = 0;
  int8_t semaf_result = 0;
  int8_t semaf_result_write = -2;
  int i = 0;
  
  semaf_result = Semaf_inicia(semaf_id);
  
  if(semaf_result == 0){
    printf("\nSemaforo [%i] Iniciado com Sucesso\n",semaf_id);  
  }
  else
  {
     printf("\nSemaforo [%i] ERRO: %i \n",semaf_id,semaf_result);  
  }
  
  
  //Teste de leitura
  for(i=0; i< 128; i++){
  semaf_result = Semaf_ler(semaf_id);
  printf("\n\nSemaforo [%i] Ocupação: %i \n",semaf_id,semaf_result);  
  
  semaf_result = Semaf_escrever(semaf_id);
  printf("Semaforo [%i] Pode escrever? %i",semaf_id,semaf_result);  
  } 
  
  //Teste de libertação leitura
  while(semaf_result_write != 0){
  semaf_result= Semaf_ler_liber(semaf_id);
  semaf_status = Semaf_estado(semaf_id);
  printf("\n\nSemaforo [%i] Ocupação: %i \n",semaf_id,semaf_status);
  
  semaf_result_write = Semaf_escrever(semaf_id);
  printf("Semaforo [%i] Pode escrever? %i",semaf_id,semaf_result_write);  
    
  } 
  
  //Teste de libertação escrita
  while(semaf_result != 1){
  semaf_status = Semaf_estado(semaf_id);
  printf("\n\nSemaforo [%i] Ocupação: %i \n",semaf_id,semaf_status);
  
  semaf_result = Semaf_ler(semaf_id);
  printf("Semaforo [%i] Pode ler? %i\n",semaf_id,semaf_result);  
  
  semaf_result_write = Semaf_escrever(semaf_id);
  printf("Semaforo [%i] Pode escrever? %i",semaf_id,semaf_result_write);  
  
  semaf_result_write = Semaf_escrever_liber(semaf_id);  
  } 
     
 printf("\n\n");
  
 return 0; 
}