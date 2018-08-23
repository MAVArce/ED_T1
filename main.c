#include <stdio.h>
#include <stdlib.h>

typedef struct bi{
    int value;
    struct bi* NEXT;
} DIGIT;

DIGIT* insert(int numb){
    DIGIT* pntr;
    pntr=calloc(1,sizeof(DIGIT));
    pntr->value=numb;
    return pntr;
}

void check(DIGIT** a){
    DIGIT* pntr;
    DIGIT* aux;

    for(pntr=*a; pntr!=NULL; pntr=pntr->NEXT){
        if(pntr->value==1){
            aux=pntr;
        }
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

void print(DIGIT* a){
    DIGIT* pntr;
    
    for(pntr=a; pntr!=NULL; pntr=pntr->NEXT)
        printf("%d", pntr->value);
    printf("\n");
}   

int main(int argc, char const *argv[]){
    DIGIT** numbers;
    DIGIT* result;
    DIGIT* pntr = NULL;
    int numb;
    int n;
    int size;
    int aux;
    int aux2;

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
        pntr=numbers[aux];

        for(aux2=1; aux2<size; aux2++){
            numb=getchar()-'0';
            pntr->NEXT=insert(numb);
            pntr=pntr->NEXT;
        }
        getchar();
        check(&numbers[aux]);
        print(numbers[aux]);
    }

    return 0;
}
