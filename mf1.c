#include <stdio.h>
#include <stdlib.h>
#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include <string.h>
#include "libfdr/jval.h"


//Kilit dosyasinin varligi kontrol ediliyor.
void dosyaKontrolleri(IS is)
{
   if(is == NULL) { printf(".kilit Dosyası Bulunamadı. \n"); exit(0);}
   
}

void parametreKontrol(int argc, char** argv)
{
  if(argc != 4)
  {
    printf("Girilen parametre sayisi hatali. \n");
    printf("Kullanim sekli: ./program -e/d girisDosyasi cikisDosyasi \n");
    exit(0);
  }
  else
  {
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
    {
       printf("Parametreler bos birakilamaz.\n");
       exit(0);
    }
    else if(argv[2] != NULL)
    {
       FILE* fp;
       fp= fopen(argv[2],"r");
       if(fp == NULL)
       {
        printf("%s isimli dosya bulunamadi.\n",argv[2]);
        exit(0);
       }
       fclose(fp);
    }
  }
  
}

//Gelen kelime ve kodlar json formatından temizleniyor
char* ayikla(char* kelime)
{
  
   
   char* kelimeSon;
   char* mallocKelime = malloc(25 * sizeof(char*));
   char harf;
   int j=0;
   for(int i =0; kelime[i]!='\0'; i++)
   {
     
     if(kelime[1]=='0' || kelime[1]=='1') //Key degeri
     {
        
      	if(kelime[i] != '{'&& kelime[i] != '}'&& kelime[i] != '"' && kelime[i] !=':' && kelime[i] != '\t' && kelime[i] != ',') // Json formatları çıkarılıyor.
      	{   
          	mallocKelime[j]= kelime[i];
          	j++;
      	}
     }
   
     else 
     {
      	if(kelime[i] != '{'&& kelime[i] != '}'&& kelime[i] != '"' && kelime[i] !=':' && kelime[i] != '\t') // Json formatları çıkarılıyor.
      	{   
          	mallocKelime[j]= kelime[i];
          	j++;
      	}
     }
   
   }
   mallocKelime[j]='\0';
   return mallocKelime;
}


//Okunan key ve value değerleri agaca yerlestirme metodu
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

//Json formatından okunan kilit dosyası agaca yerlestiriliyor.
void okuVeYerlestir(JRB b, JRB bn,IS is, char* opsiyon)
{
  int i,j;
  
   while (get_line(is) >= 0) 
   {
      i=0;
      j=0;
      char* key;
      char* value;
      int flag=0;
    for (i = 0; i < is->NF; i++) 
    {
      if(i != 0 || i != (is->NF)-1)
      {    
    	 flag=1;
      	 if(i % 2 ==0)//Key mi value mu oldugununa bakılıyor
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
    
      if(strcmp(opsiyon,"-e")) //encription islemi secimi
      {
     	 if(flag == 1) agacaYerlestir(b,value,key);
      }
      else if(strcmp(opsiyon,"-d")) //decription islemi secimi
      {
    	 if(flag == 1) agacaYerlestir(b,key,value);
      }
    
    }
 }
 void encode(JRB b, char* girisDosyasi, JRB bn, FILE* fp)
{
   IS is;
   int i,j;
   
   is = new_inputstruct(girisDosyasi); 
   while (get_line(is) >= 0) 
   {
        for(i=0; i<is->NF; i++)
        { 
          JRB c;
          c= jrb_find_str(b,is->fields[i]); //Kelime value eslesmesine bakılıyor.
  
          if(c==NULL) fprintf(fp,"%s ", is->fields[i]); //Eslesen numaralar dosyaya yazdırılıyor.
          else fprintf(fp,"%s ", c->val.s);   //Eslesme olmayan kelimelerin kendileri dosyaya yazdırılıyor.
        } 
   }
   jettison_inputstruct(is);  
}

void decode(JRB b, char* girisDosyasi, JRB bn, FILE* fp)
{
   IS is;
   int i,j;
   
   is = new_inputstruct(girisDosyasi);
   
   while (get_line(is) >= 0) 
   {
        for(i=0; i<is->NF; i++)
        { 
          JRB c;
          c= jrb_find_str(b,is->fields[i]); //Value kelime eslesmesine bakılıyor.
  
          if(c==NULL) fprintf(fp,"%s ", is->fields[i]); //Eslesen valueler dosyaya yazdırılıyor.
          else fprintf(fp,"%s ", c->val.s);  //Eslesme olmayan valuelar kendileri dosyaya yazdırılıyor.
        }  
   }
     
   jettison_inputstruct(is);
}

void islemiBaslat(JRB b, JRB bn,IS  is,char* argvParametre, char* cikisDosyasi,char* girisDosyasi)
{
   FILE* fp;
  
   if(strcmp(argvParametre,"-e") == 0)
   {
     okuVeYerlestir(b,bn, is,argvParametre);
     fp= fopen(cikisDosyasi,"w+");
     encode(b,girisDosyasi,bn,fp); 
   }
   else if(strcmp(argvParametre,"-d") == 0)
   {
     okuVeYerlestir(b,bn, is,argvParametre);
     fp= fopen(cikisDosyasi,"w+");
     decode(b,girisDosyasi,bn,fp);
   }
   else
   {
    printf("Gecersiz Parametre Lutfen -e ya da -d kullanınız.\n");
   } 
}


int main(int argc, char **argv)
{
  JRB b;
  JRB bn;
  IS is;
  
  parametreKontrol(argc, argv);
  char* argvParametre = argv[1];
  char* girisDosyasi = argv[2];
  char* cikisDosyasi = argv[3];
  
  is = new_inputstruct(".kilit");
  b = make_jrb();
  
 
  dosyaKontrolleri(is);
  islemiBaslat(b, bn, is, argvParametre,cikisDosyasi,girisDosyasi);
  jettison_inputstruct(is);
  return 0;
}
