# include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HAK 10 
#define BOYUT 4

struct n {
 		float puan;
 		char *isim;
 		n* next;
 };
 typedef n node;
 
node* ekleSirali(node*r,float x,char *isim);	
void bastir(node*r); 
void Dizi_goruntule(int dizi[]);
void Yazdir(int a , int b);
float PuanHesapla(int a ,int b,int hak);
int Line_size();
int bulmak();
node* Linke_kopyala(node* r);
node* Sil_kucuk(node* r);
float Enkucuk(node* r);

 
int main()
 {
 	node* root = NULL;
 	srand(time(NULL));
    int rastgele[BOYUT];
    int kullanici[BOYUT]; 
    int temp=(rand()%9);
    rastgele[0]=temp;
    
    int line_size = bulmak();
    
    for(int i = 1; i < BOYUT; i++){
    	temp=(rand()%9);
        for(int j = 0; j < i; j++){
    	    if (rastgele[j] == temp){
             i--;
             break;
            }
             else
             rastgele[i] = temp;	        
	    }       
    }
    int sayida_bulunan ;
	int sayac_dogru_yerde ;
	int sayac_yanlis_yerde ;
	int arti = 0;
	int eksi = 0;
	int hak;
	for( hak = 1 ; hak <= HAK ; hak++)
    {
 	    sayida_bulunan = 0 ;
 	    sayac_dogru_yerde = 0;
     	sayac_yanlis_yerde = 0;
     	int a = 0;
 	    printf("\n");
        while(a < BOYUT){
    	    printf("%d Rakami giriniz ( 0 - 9 ) : " ,a+1);
        	scanf("%d",&kullanici[a]);
    	    a++;
    	}
    	for(int s = 0; s < BOYUT; s++){
		    for(int t = 0; t < BOYUT; t++){
		     	if(kullanici[s] == rastgele[t])
			     sayida_bulunan++ ;
	     	}
	     	if(kullanici[s] == rastgele[s])
		    sayac_dogru_yerde++ ;
	    }
	    sayac_yanlis_yerde = sayida_bulunan - sayac_dogru_yerde ;
	    
	    printf("\n");
	    Dizi_goruntule(kullanici);
        Yazdir(sayac_yanlis_yerde,sayac_dogru_yerde);
        arti += sayac_dogru_yerde;
        eksi += sayac_yanlis_yerde;
        
        if(sayac_dogru_yerde == BOYUT){
        	if(line_size == 10){
        	  root = Linke_kopyala(root);
        	  bastir(root);
        	   float kucuk = Enkucuk(root);
        	   node a;
        	   a.isim = (char*)malloc(sizeof(char)*30);
        	   a.puan = PuanHesapla(arti, eksi, hak);
        	   if(kucuk < a.puan){
        	   	    root = Sil_kucuk(root);
        	        bastir(root);
        	        FILE *file = fopen("file.txt","a+");
        	        printf("isminizi giriniz : ");
        	        scanf("%s",a.isim);
        	        fprintf(file,"%s  %f\n",a.isim,a.puan);
        	        fclose(file);
			    }
        	   
			}else{
				printf("\n");
				FILE *file = fopen("file.txt","a+");
        	    node a;
        	    a.isim = (char*)malloc(sizeof(char)*30);
   	            printf("isminiz giriniz : ");
   	            scanf("%s",a.isim);
   	            a.puan = PuanHesapla(arti, eksi, hak);
   	            fprintf(file,"%s  %f\n",a.isim,a.puan);
   	            fclose(file);
			}
        
        	break;
        }else if(hak == HAK){
     	    printf("\nUzgunuz 10 hakkiniz tukendi...!\n");
     	  
            if(line_size == 10){
        	    root = Linke_kopyala(root);
        	    bastir(root);
        	    float kucuk = Enkucuk(root);
        	    printf("Enkucuk : %f \n",kucuk);
        	    node a;
        	    a.isim = (char*)malloc(sizeof(char)*30);
        	    a.puan = PuanHesapla(arti, eksi, hak);
        	    if(kucuk < a.puan){
        	   	    root = Sil_kucuk(root);
        	        bastir(root);
        	        FILE *file = fopen("file.txt","a+");
        	        printf("isminizi giriniz : ");
        	        scanf("%s",a.isim);
        	        fprintf(file,"%s  %f\n",a.isim,a.puan);
        	        fclose(file);
			    }
	    
			}else{
				printf("\n");
				FILE *file = fopen("file.txt","a+");
        	    node a;
        	    a.isim = (char*)malloc(sizeof(char)*30);
   	            printf("isminiz giriniz : ");
   	            scanf("%s",a.isim);
   	            a.puan = PuanHesapla(arti, eksi, hak);
   	            fprintf(file,"%s  %f \n",a.isim,a.puan);
   	            fclose(file);
			}    
	           
        }
    }
  
 	return 0;
}

int bulmak(){
 	int len;
    int line_size;
    FILE *file = fopen("file.txt", "a+");
    if( file == NULL ){
        return(-1);
    }
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fclose(file);
    if(len <= 0)
    line_size = 0;
    else
    line_size = Line_size();
    return line_size; 
}
 
int Line_size()
{
	FILE *file = fopen("file.txt","r");
	node a;
	int sayi=0;
	a.isim = (char*)malloc(sizeof(char)*30);
	while(!feof(file))
	{
		fscanf(file,"%s  %f\n ",a.isim,&a.puan);
		sayi++;
	}
	fclose(file);
	
	return sayi;
}

float Enkucuk(node* r){
	node* iter = r;
	while( iter->next!= NULL){
		iter=iter->next;
	}	
	return iter->puan;
}

void bastir(node*r){
	node* iter=r;
	FILE *file = fopen("file.txt","w+");
	printf("\n");	
	while( iter!= NULL){		
		fprintf(file,"%s    %f \n",iter->isim,iter->puan);
		iter = iter->next;		
	}	
	fclose(file);
}

void Dizi_goruntule(int dizi[]){
		for(int s=0;s<BOYUT;s++){
        printf("%d",dizi[s]);
    }
 }

void Yazdir(int a , int b){
    printf(" => -%d,+%d " ,a,b);
    if(a == 0 && b == 0)
    {
    	printf("* Girilen rakamlardan hic biri sayida yok.");
	}else if(b == BOYUT)
	{
	  	printf("* Girilen rakamlardan %d tanesi de var,dogru yerdeler (Bildiniz!) .",b);
	}else{
		printf("* Girilen rakamlardan %d tanesi de var,%d dogru,%d yanlis yerde. ",a+b,b,a);
	}
}

float PuanHesapla(int a ,int b,int hak){
	float x = (float)(1000/hak) ;
	float y = (float)(a * (-b)) / (a - b);
	float puan = (10 * a) - (5 * b) + x - y;
	return puan;
}

node* Linke_kopyala(node* r){
	FILE *file = fopen("file.txt","r");
	node a[10];
    int i = 0;
	while(!feof(file)){
		a[i].isim = (char*)malloc(sizeof(char)*30);
		fscanf(file," %s  %f ",a[i].isim,&a[i].puan);
		r = ekleSirali(r,a[i].puan,a[i].isim);
		i++;
	}	
	fclose(file);
	
	return r ;
}

node* Sil_kucuk(node* r){
	node* iter = r;
	while(iter->next->next != NULL){
		iter = iter->next;
	}
	node*temp=iter->next;
	iter->next=NULL;
	free(temp);
	return r;
}

node* ekleSirali(node*r,float x,char *isim){
	if (r==NULL){
	r=(node*)malloc(sizeof(node));
	r->isim = (char*)malloc(sizeof(char)*30);
	r->next=NULL;
	r->puan=x;
	r->isim = isim;
	return r;
	}
	if(r->puan<x){
	node*temp=(node*)malloc(sizeof(node));
	temp->puan=x;
	temp->isim = (char*)malloc(sizeof(char)*30);
	temp->isim = isim;
	temp->next=r;
	return temp;
	}
	node*iter=r;
	while(iter->next!=NULL && iter->next->puan>x){
		iter=iter->next;
	}
	node*temp=(node*)malloc(sizeof(node));
	temp->next=iter->next;
	iter->next=temp;
	temp->puan=x;
	temp->isim = (char*)malloc(sizeof(char)*30);
	temp->isim = isim;
	return r;
}


