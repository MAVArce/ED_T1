#include <stdio.h>
#include <stdlib.h>

typedef struct bi{
    int value;
    struct bi* NEXT;
} DIGIT;

DIGIT* insert(int numb){                    //OK
    DIGIT* pntr;
    pntr=calloc(1,sizeof(DIGIT));
    if(pntr == NULL){ printf("Erro na alocacao"); return NULL;}
    pntr->value=numb;
    return pntr;
}

void check(DIGIT** a){                      //OK
    DIGIT* pntr;
    DIGIT* aux = NULL;
    for(pntr=*a; pntr!=NULL; pntr=pntr->NEXT){
        if(pntr->value==1){
            aux=pntr;
        }
    }
    if(aux==NULL){
        *a=NULL;
        return;
    }
    if(aux->NEXT!=NULL){
        pntr=aux->NEXT;
        aux->NEXT=NULL;
        while(pntr!=NULL && aux!=NULL){    
            aux=pntr->NEXT;
            free(pntr);            
            if(aux!=NULL){
                pntr=aux->NEXT;
                free(aux);
            }
        }       
    }
}

int get_size(DIGIT* a){
    DIGIT* pntr;
    int count = 0;
    
    for(pntr=a; pntr!=NULL; pntr=pntr->NEXT)
        count++;

    return count;
}

void print(DIGIT* a){                           //OK
    DIGIT* pntr;

    printf("%d ", get_size(a));

    if(a==NULL){
        printf("0\n");
        return;
    }

    for(pntr=a; pntr!=NULL; pntr=pntr->NEXT)
        printf("%d", pntr->value);
    printf("\n");
} 

void sum(DIGIT** result, DIGIT** a){
    DIGIT* pntr;
    DIGIT* pntr2;
    DIGIT* aux;
    int plus = 0;

    pntr=*result;
    pntr2=*a;

    while(pntr!=NULL || pntr2!=NULL){
        if(pntr!=NULL && pntr2!=NULL){
            pntr->value+=(pntr2->value+plus);
        }else if(pntr==NULL && pntr2!=NULL){
            aux->NEXT=insert(pntr2->value+plus);
            pntr=aux->NEXT;
        }else if(pntr!=NULL && pntr2==NULL){
            pntr->value+=plus;
        }

        if(pntr->value>1){
            plus = 1;
            pntr->value-=2;
        }else{
            plus = 0;
        }

        if(pntr2!=NULL){
            aux=pntr2;
            pntr2=pntr2->NEXT;
            free(aux);
        }
        if(pntr!=NULL){
            aux = pntr;
            pntr=pntr->NEXT;
        }
    }
    if(plus==1){
        aux->NEXT=insert(1);
    }
}

void total(DIGIT** a, int n){
    int aux;
    for(aux = 1; aux<n; aux++){
        sum(&a[0],&a[aux]);
    }
}  

int main(int argc, char const *argv[]){
    DIGIT** numbers;
    DIGIT* pntr = NULL;
    int numb;
    int n;
    int size;
    int aux;

    scanf("%d", &n);
    numbers=(DIGIT**) calloc(n,sizeof(DIGIT*));

    for(aux=0; aux<n; aux++){
        scanf("%d", &size);
        getchar();
       
        numb=getchar()-'0';
        numbers[aux]=insert(numb);
        if(numbers[aux]==NULL) return -1;
        pntr=numbers[aux];

        for(size--; size>0; size--){
            numb=getchar()-'0';
            
            if(numb=='\n'-'0')
                break;
            
            pntr->NEXT=insert(numb);
            
            if(numbers[aux]==NULL) return -1;
            
            pntr=pntr->NEXT;
            
            if(size==1)
                while(getchar()!='\n');
        }
        check(&numbers[aux]);
    }
    total(numbers, n);
    check(&numbers[0]);
    print(numbers[0]);
    free(numbers);

    return 0;
}