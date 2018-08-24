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

void sum(DIGIT** result, DIGIT** a){
    DIGIT* pntr;
    DIGIT* pntr2;
    DIGIT* aux;
    int plus = 0;

    pntr=*result;
    pntr2=*a;

    while(pntr!=NULL && pntr2!=NULL){
        if(pntr!=NULL && pntr2!=NULL){
            pntr->value+=(pntr2->value+plus);
        }
        if(pntr==NULL && pntr2!=NULL){
            pntr=insert(pntr2->value+plus);
        }
        if(pntr!=NULL && pntr2==NULL){
            pntr->value+=plus;
        }

        if(pntr->value>1){
            plus = 1;
            pntr->value-=2;
        }else{
            plus = 0;
        }

        if(pntr!=NULL)
            pntr=pntr->NEXT;
        if(pntr2!=NULL){
            aux=pntr2;
            pntr2=pntr2->NEXT;
            free(aux);
        }
    }
    if(plus==1){
        pntr=insert(1);
    }
}

void print(DIGIT* a){                           //OK
    DIGIT* pntr;

    if(a==NULL){
        printf("It's empty\n");
        return;
    }

    for(pntr=a; pntr!=NULL; pntr=pntr->NEXT)
        printf("%d", pntr->value);
    printf("\n");
} 

void total(DIGIT** a, int n){
    int aux;
    for(aux = 1; aux<n; aux++){
        sum(&a[0],&a[aux]);
        printf("%d soma ", aux);
        print(a[0]);
    }
}  

int main(int argc, char const *argv[]){
    DIGIT** numbers;
    DIGIT* pntr = NULL;
    int numb;
    int n;
    int size;
    int aux;

    printf("Digite quantos numeros quer que sejam somados: ");
    scanf("%d", &n);
    numbers=(DIGIT**) calloc(n,sizeof(DIGIT*));

    for(aux=0; aux<n; aux++){
        printf("Digite o tamanho do numero: ");
        scanf("%d", &size);
        getchar();
       
        printf("Digite o numero: ");
        numb=getchar()-'0';
        numbers[aux]=insert(numb);
        if(numbers[aux]==NULL) return -1;
        pntr=numbers[aux];

        for(size--; size>0; size--){
            numb=getchar()-'0';
            pntr->NEXT=insert(numb);
            if(numbers[aux]==NULL) return -1;
            pntr=pntr->NEXT;
        }
        while(getchar()!='\n');
        check(&numbers[aux]);
        print(numbers[aux]);
    }
    total(numbers, n);
    check(&numbers[0]);
    print(numbers[0]);
    free(numbers);

    return 0;
}
