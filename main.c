#include <stdio.h>
#include <stdlib.h>

typedef struct bi{              //Struct para formar a lista
    int value;              //Inteiro que contem o digito
    struct bi* NEXT;        //Ponteiro para apontar ao próximo elemento da lista
} DIGIT;

DIGIT* insert(int numb){   //Função para inserir um elemento na lista
    DIGIT* pntr;            //Ponteiro usado para alocar o novo elemento da lista
    pntr=calloc(1,sizeof(DIGIT));   
    if(pntr == NULL){ printf("Erro na alocacao"); return NULL;}     //Verificação de erro na alocação
    pntr->value=numb;
    return pntr;
}

void check(DIGIT** a){                      //Função para retirar os digitos 0 desnecessários na lista
    DIGIT* pntr;                //Ponteiro para se localizar na lista
    DIGIT* aux = NULL;          //Ponteiro auxiliar para marcar um endereço ou para desalocar um 
    for(pntr=*a; pntr!=NULL; pntr=pntr->NEXT){       //Algoritmo para procurar o último 1 da lista e marcar o endereço
        if(pntr->value==1){
            aux=pntr;
        }
    }
    if(aux==NULL){                                  //Verificação para caso a lista não tenha nenhum digito 1
        aux=*a;
        *a=NULL;
    }
    if(aux->NEXT!=NULL){                            //Algoritmo para desalocar os 0 no final da lista
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

int get_size(DIGIT* a){                     //Função que retorna o tamanho da lista
    DIGIT* pntr;                //Ponteiro para manipular a lista
    int count = 0;              //Contador
    
    for(pntr=a; pntr!=NULL; pntr=pntr->NEXT)
        count++;

    return count;
}

void print(DIGIT** a){                           //Função que imprime a saída e desaloca seus elementos um por um
    DIGIT* pntr;            //Dois ponteiros usados para manipular a lista e desalocar
    DIGIT* aux;

    printf("%d ", get_size(*a));   //Obter o tamanho da saída

    if(a==NULL){                    //Caso a saída seja nula
        printf("0\n");
        return;
    }
    pntr = *a;                      
    while(pntr!=NULL){              //Algoritmo que imprime o valor de um elemento e o desaloca da lista
        printf("%d", pntr->value);
        aux=pntr;
        pntr=pntr->NEXT;
        free(aux);
    }
    printf("\n");
} 

int sum(DIGIT** result, DIGIT** a){    //Função que soma a lista dada a lista do resultado final
    DIGIT* pntr;            //Três ponteiros para auxiliar na soma, manipulação e desalocação dos elementos da lista
    DIGIT* pntr2;
    DIGIT* aux;
    int plus = 0;           //Inteiro usado para realizar o "vai um" da soma

    pntr=*result;
    pntr2=*a;

    while(pntr!=NULL || pntr2!=NULL){           //Loop que faz a soma enquanto as duas listas não acabam
        if(pntr!=NULL && pntr2!=NULL){          //Caso para quando os dois ponteiros não são nulos
            pntr->value+=(pntr2->value+plus);
        }else if(pntr==NULL && pntr2!=NULL){    //Caso quando o ponteiro da lista do resultado é nulo e o outro não...
            aux->NEXT=insert(pntr2->value+plus);//... precisando alocar um novo elemento para a lista
            if(aux->NEXT==NULL) return -1;
            pntr=aux->NEXT;
        }else if(pntr!=NULL && pntr2==NULL){    //Caso em que a lista dada chegou no fim mas a do resultado ainda não
            pntr->value+=plus;
        }

        if(pntr->value>1){          //Algortimo para determinar o "vai um"
            plus = 1;
            pntr->value-=2;
        }else{
            plus = 0;
        }

        if(pntr2!=NULL){        //Algortimo que desaloca o elemento da lista dada e passa para o próximo
            aux=pntr2;
            pntr2=pntr2->NEXT;
            free(aux);
        }
        if(pntr!=NULL){         //Algoritmo que passa o ponteiro para o próximo elemento da lista do resultado 
            aux=pntr;
            pntr=pntr->NEXT;
        }
    }
    if(plus==1){                //Caso em que as duas listas chegam ao fim, mas ainda há um "vai um"
        aux->NEXT=insert(1);
        if(aux->NEXT==NULL) return -1;
    }
    return 0;
}

int main(int argc, char const *argv[]){
    DIGIT* result;              //Ponteiro para a lista do resultado
    DIGIT* numbers;             //Ponteiro para a lista dada
    DIGIT* pntr = NULL;         //Ponteiro auxiliar
    int numb;                   //Inteiro para o valor dado a ser colocado
    int n;                      //Inteiro com o número de elementos que serão somados
    int size;                   //Inteiro para determinar o tamanho da lista dada
    int aux;                    //Inteiro auxiliar usado no loop
    int aux2 = 0;                   //Inteiro para garantir que a soma foi realizada

    scanf("%d", &n);
    result=(DIGIT*)calloc(1,sizeof(DIGIT));     //Cria o primeiro elemento para a lista resultado

    for(aux=0; aux<n; aux++){           //Loop que cria a lista dada e a insere na lista resultado 
        scanf("%d", &size);
        getchar();
       
        numb=getchar()-'0';
        numbers=insert(numb);
        if(numbers==NULL) return -1;
        pntr=numbers;

        for(size--; size>0; size--){
            numb=getchar()-'0';
            if(numb=='\n'-'0') break;
        
            pntr->NEXT=insert(numb);
            if(numbers==NULL) return -1;
            
            pntr=pntr->NEXT;
            if(size==1) while(getchar()!='\n'); //Algoritmo para limpar o buffer caso seja inserido mais digitos do que foi predeterminado
        }
        check(&numbers);                //Organiza a lista e a encurta, se necessário
        aux2=sum(&result, &numbers);    //Soma a lista dada a lista resultado
        if(aux2!=0) return -1;
    }
    check(&result);         //Checagem final da lista resultado para ver se não há um zero desnecessário
    print(&result);         //Imprime a saída e desaloca os elementos da lista
    free(result);           //Libera o espaço da memória ao ponteiro da lista resultado

    return 0;
}