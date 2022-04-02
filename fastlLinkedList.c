#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct list{
    int value;
    struct list *next;
    struct list *below;
}list;

int kacSeviye(list *head){
	int i=1;
	list *iter=head;
	while(iter->below!=NULL){
		iter=iter->below;
		i++;
	}
	return i;
}

int *randomla(int n){
    
    int i, *dizi=(int*)malloc(n*sizeof(int));

    srand(time(NULL)); 
    
    for(i=0 ; i<n ; i++)
        dizi[i]=i;

    for (i=0 ; i<n ; i++) {    
        int temp = dizi[i];
        int randomIndex = rand() % n;

        dizi[i]           = dizi[randomIndex];
        dizi[randomIndex] = temp;
    }

    return dizi;

}

int *sortDizi(int *dizi, int n){
    int i, j, temp;

    for(i=0;i<n;i++)
        for(j=0;j<n-i-1;j++){
            if(dizi[j] > dizi[j+1]){
                temp=dizi[j];
                dizi[j]=dizi[j+1];
                dizi[j+1]=temp;
            }
        }

    return dizi;
}

void listeYazdir(list *head){
    int i, j, seviye=1;
    list *iter=head,*iter2=head;
    do{
    	printf("%d. seviye  ",seviye);
        do{
        	iter=iter->next;
            printf("%d -> ",iter->value);
        }while(iter->next!=NULL);
        printf("NULL\n\n");
        iter2=iter2->below;	
        iter=iter2;
        seviye++;
    }while(iter2!=NULL); 
}

list *ustSeviyelerOlustur(list*head, int n, int *dizi, int *random){
	int i, *arr;
	list *iter=(list*)malloc(sizeof(list)), *iter2=head;
	iter->below=head;
	head=iter;
	arr=sortDizi(random, n);
	for(i=0;i<n;i++){
		iter->next=(list*)malloc(sizeof(list));
		iter=iter->next;
		while(iter2->value!=dizi[arr[i]]){
			iter2=iter2->next;
		}
		iter->value=dizi[arr[i]];
		iter->below=iter2;
	}
	iter->next=NULL;
	if(n==1){
		return head;
	}
	return ustSeviyelerOlustur(head, (n+1)/2, dizi, random);
}

list *ilkSeviyeOlustur(list*head, int n, int *dizi){
	int i;

	head=(list*)malloc(sizeof(list));
	list *iter=head;

	iter->below=NULL;

	for(i=0;i<n;i++){
		iter->next=(list*)malloc(sizeof(list));
        iter=iter->next;
        iter->value=dizi[i];
        iter->below=NULL;
	}
	iter->next=NULL;

	return head;
}

int listedeAra(list *head, int a){
	int seviye=1, b=0, i;
	list *iter1=head;
	
	b=kacSeviye(head);
	
	for(i=0;i<b;i++){
		while(iter1->next!=NULL && iter1->next->value <= a){
			iter1=iter1->next;
			if(iter1->value==a){
				printf("Sayi bulundu!! %d. seviyede\n\n",seviye);
				return 1;
			}
		}
		iter1=iter1->below;	
		seviye++;
	}
	
	return 0;
}

list *freeList(list *head, int n){
	int i;
	list *iter, *iter2;
	for(i=0;i<n;i++){
		iter=head;
		head=head->below;
		while(iter->next!=NULL){
			iter2=iter;
			iter=iter->next;
			free(iter2);  
		}
		free(iter);	
	}
	return head;
}

list *araEkle(list *head, int yeni){
	list *iter=head, *iter2;

	while(iter->next!=NULL && iter->next->value < yeni)
		iter=iter->next;
	
	if(iter->next==NULL){
		iter->next=(list*)malloc(sizeof(list));
        iter=iter->next;
        iter->value=yeni;
        iter->next=NULL;
        return head;
	}

	iter2=(list*)malloc(sizeof(list));

	iter2->value=yeni;

	iter2->next=iter->next;

	iter->next=iter2;

	return head;
}

list *araSil(list *head, int sil){
	list *iter=head, *iter2;

	while(iter->next->value != sil)
		iter=iter->next;
	
	if(iter->next->next==NULL){
		iter2=iter->next;
		free(iter2);
        iter->next=NULL;
        return head;
	}

	iter2=iter->next;
	
	iter->next=iter2->next;

	free(iter2);

	return head;
}

int main(){

    int n, i, j=0, s, a=0, b=0, ara, *dizi, *random, yeni, k=0, sil, temp;  //oncelikle
    list *head;
    while(a==0){

        printf("--------------------------\n1.Liste olusturma\n2.Liste icinde arama\n3.Listeye eleman ekleme\n4.Listeden eleman silme\n5.Liste goruntuleme\n6.Cikis\n--------------------------\n\nUstteki seceneklerden birini seciniz\n\n");
        scanf("%d",&s);

        switch (s)
        {
        case 1:
        	
        	{
        		
        	if(b!=0){
        		printf("Zaten liste var!!!\n\n");
        		break;
    		}
    		
            printf("Kac eleman girmek istiyorsunuz?\n\n");
            scanf("%d",&n);

            dizi=(int*)malloc(n*sizeof(int));

            printf("Elemanlari sirayla giriniz(Karisik bir sekilde girerseniz sortlanacaktir).\n\n");

            for(i=0;i<n;i++)
                scanf("%d",&dizi[i]);
            
			random=(int*)malloc(n*sizeof(int));    
			random=randomla(n);
			
            dizi=sortDizi(dizi,n);
            head=ilkSeviyeOlustur(head,n,dizi);
            head=ustSeviyelerOlustur(head,(n+1)/2,dizi,random);
            listeYazdir(head);

            b=1;
            
            break;
            
			}
			
        case 2:
        	
            printf("Hangi elemani aramak istiyorsunuz?\n\n");
            scanf("%d",&ara);
            
            if(listedeAra(head,ara)==0)
            	printf("Sayi Bulunamadi\n\n");
            	
            
            break;

        case 3:
        	k=0;
        	printf("Eleman giriniz\n\n");
        	scanf("%d",&yeni);
        	for(i=0;i<n;i++)
        		if(dizi[i]==yeni){
        			printf("Eleman zaten bulunuyor!!\n\n");
        			k++;
				}
			if(k==0){
				n++;
				dizi=(int*)realloc(dizi,sizeof(int)*n);
	        	dizi[n-1]=yeni;		
	        	
	        	random=(int*)realloc(dizi,sizeof(int)*n);    
				random=randomla(n);
				
				dizi=sortDizi(dizi,n);
				
				for(i=0;i<n;i++)
					printf("%d ",dizi[i]);
					
				printf("\n\n");
				
	            head=freeList(head,(kacSeviye(head)-1));
	            head=araEkle(head,yeni);
	            head=ustSeviyelerOlustur(head,(n+1)/2,dizi,random);
	            listeYazdir(head);
            }
            break;

        case 4:
        	k=0;
            printf("Eleman giriniz\n\n");
        	scanf("%d",&sil);
        	for(i=0;i<n;i++)
        		if(dizi[i]==sil){
        			for(j=i;j<n-1;j++){
        				dizi[j]=dizi[j+1];	
					}
        			k=1;
        			break;
        		}
			
			if(k==0)
				printf("Silinecek eleman yok\n\n");
				
			if(k==1){
				n--;
				dizi=(int*)realloc(dizi,sizeof(int)*n);
				
				random=(int*)realloc(dizi,sizeof(int)*n);    
				random=randomla(n);
					
				head=freeList(head,(kacSeviye(head)-1));
				head=araSil(head,sil);
	            head=ustSeviyelerOlustur(head,(n+1)/2,dizi,random);
	            listeYazdir(head);
				
			}
            break;

        case 5:
            listeYazdir(head);
            break;

        case 6:
            a=1;
            printf("Cikis yapiliyor...\n");
            break;
        
        }
    }
    head=freeList(head,kacSeviye(head));
    free(dizi);
    free(random);
    return 0;
}