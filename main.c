#include <stdio.h>
#include <stdlib.h>

typedef struct bi{
    int value;
    struct bi* NEXT;
} DIGIT;

DIGIT* insert(int numb){                    //OK
    DIGIT* pntr;
    pntr=calloc(1,sizeof(DIGIT));
    pntr->value=numb;
    return pntr;
}

void check(DIGIT** a){                      //OK
    DIGIT* pntr;
    DIGIT*  aux = NULL;
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

int sum(DIGIT*** a, int n, int quant, int* plus){
    DIGIT* pntr;
    int final = 0;
    int aux;
    int flag;
    
    final+=(*plus);
    for(aux=0; aux<n; aux++){
        for(pntr=(*a)[aux]; quant>0 && pntr!=NULL; pntr=pntr->NEXT);
        if(pntr!=NULL && pntr->NEXT==NULL){
            final+=pntr->value;
            free(a[aux]);        
        }else if(pntr!=NULL){
            final+=pntr->value;
            (*a)[aux]=pntr->NEXT;
            free(pntr);
        }
    }
    *plus=final/2;
    
    for(aux=0;aux<n;aux++){
        if((*a)[aux]!=NULL){
            flag = 1;
            break;
        }else{
            flag = 0;
        }
    }
    
    if((*plus)!=0)
        flag = 1;

    final%=2;
    if(flag == 1){
        return final;
    }else{
        return -1;
    }
}

DIGIT* total(DIGIT*** a, int n, int quant, int* size){
    DIGIT* new;
    int plus = 0;

    new= (DIGIT*) calloc(1, sizeof(DIGIT));
    new->value= sum (a, n, quant, &plus);
    
    if(new->value==-1)
        return NULL;
    
    (*size)++;
    return new;
}

void print(DIGIT* a){                           //OK
    DIGIT* pntr;

    if(a==NULL){
        printf("It's empty");
        return;
    }

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
    //int plus = 0;

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

        for(aux2=1; aux2<size; aux2++){
            numb=getchar()-'0';
            pntr->NEXT=insert(numb);
            if(numbers[aux]==NULL) return -1;
            pntr=pntr->NEXT;
        }
        getchar();
        check(&numbers[aux]);
        print(numbers[aux]);
    }
    size = 0;

    result=total(&numbers, n, 1, &size);
    pntr = result;

    for(aux=2; pntr!=NULL ; aux++){
        pntr->NEXT=total(&numbers, n, aux, &size);
        pntr=pntr->NEXT;
    }
    check(&result);
    printf("%d ", size);
    print(result);
    free(numbers);
    return 0;
}
