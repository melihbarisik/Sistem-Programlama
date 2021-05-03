#include<stdio.h>
#include<stdlib.h>
#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include <string.h>
#include "libfdr/jval.h"


char* ayikla(char* kelime)
{
   char* kelimeSon;
   char* mallocKelime = malloc(25 * sizeof(char*));
   char harf;
   int j=0;
   for(int i =0; kelime[i]!='\0'; i++)
   {
      if(kelime[i] != '{'&& kelime[i] != '}'&& kelime[i] != '"' && kelime[i] !=':' && kelime[i]!= ',' && kelime[i] != '\t')
      {
        mallocKelime[j]= kelime[i];
        j++;
      }
   }
   
  return mallocKelime;
}


void agacaYerlestir(JRB b,char* key, char* value)
{
  (void) jrb_insert_str(b,strdup(key),new_jval_s(strdup(value)));
}


void traverse(JRB b, JRB bn)
{
 jrb_traverse(bn, b) 
 {
    printf("%s", bn->val.s);  
    printf("%s \n", bn->key.s);  
 }
    
}


void okuVeYerlestir(JRB b, JRB bn,IS is, char* opsiyon)
{
  int i,j;
  
  while (get_line(is) >= 0) {
      i=0;
      j=0;
      char* key;
      char* value;
      int flag=0;
    for (i = 0; i < is->NF; i++) {
    
    if(i != 0 || i != (is->NF)-1)
    {
    	flag=1;
      if(i % 2 ==0)
      {
        key = ayikla(is->fields[j]);	    
      }
      else
      {
        value = ayikla(is->fields[j]);	     
      }
      j++;
     }
    }
    if(strcmp(opsiyon,"-e"))
    {
      if(flag == 1) agacaYerlestir(b,value,key);
    }
    else if(strcmp(opsiyon,"-d"))
    {
      if(flag == 1) agacaYerlestir(b,key,value);
    }
  }
}

int main(int argc, char **argv)
{
  return 0; 
}
