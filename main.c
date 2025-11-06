#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define tam 32000
#define vet 20

typedef struct item{
    int chave;
    double valor;
}item;

void troca(item *a, item *b) {
    item aux = *a;
    *a = *b;
    *b = aux;
}

void insertionSort(item *v, int n){
    clock_t start_time = clock();

    int i, j;
    struct item aux;
    for(i = 1; i < n; i++){
        aux = v[i];
        for(j = i-1; j >= 0 && v[j].chave < aux.chave; j--){
            v[j + 1] = v[j];
        }
    v[j + 1] = aux;
    }
    clock_t end_time = clock();
    printf(" %.4f s      ", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}

int particaoLI(item *v, int LI, int LS){
    int e=LI, d=LS;
    item pivo=v[e], aux;
    while(e < d){
        while((v[e].chave >= pivo.chave) && (e<LS)){
            e++;
        }
        while((v[d].chave < pivo.chave) && (d>LI)){
            d--;
        }
        if(e < d){
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
        }
    }
    aux = v[LI];
    v[LI] = v[d];
    v[d] = aux;

    return d;
}

void quickSortLI_Auxiliar(item *v, int LI, int LS){
    if(LI < LS){
        int p = particaoLI(v, LI, LS);
        quickSortLI_Auxiliar(v, LI, p-1);
        quickSortLI_Auxiliar(v, p+1, LS);
    }
}

void quickSortLI(item *v, int LI, int LS){
    clock_t start_time = clock();

    quickSortLI_Auxiliar(v, LI, LS);

    clock_t end_time = clock();
    printf(" %.4f s      ", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}


int particaoMEIO(item *v, int LI, int LS){
    int e=LI, d=LS;
    item pivo = v[(LS+LI)/2], aux;
    while(e < d){
        while((v[e].chave>= pivo.chave)&& (e<LS)){
            e++;
        }
        while((v[d].chave< pivo.chave)&&(d>LI)){
            d--;
        }
        if(e<d){
            aux = v[e];
            v[e]=v[d];
            v[d]=aux;
            e++;
            d--;
        }
    }
return e;
}

void quickSortMEIO_Auxiliar(item *v, int LI, int LS){
    if(LI<LS){
        int p = particaoMEIO(v,LI,LS);
        quickSortMEIO_Auxiliar(v,LI,p-1);
        quickSortMEIO_Auxiliar(v,p+1,LS);
    }
}

void quickSortMEIO(item *v, int LI, int LS){
    clock_t start_time = clock();
    quickSortMEIO_Auxiliar(v, LI, LS);
    clock_t end_time = clock();
    printf(" %.4f s      ", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}

int particaoLS(item *v, int LI, int LS){
    int e=LI, d=LS;
    item pivo = v[d], aux;
    while(e < d){
        while((v[e].chave > pivo.chave)&& (e<LS)){
            e++;
        }
        while((v[d].chave <= pivo.chave)&&(d>LI)){
            d--;
        }
        if(e<d){
            aux = v[e];
            v[e] = v[d];
            v[d] = aux;
        }
    }
    aux = v[LS];
    v[LS] = v[e];
    v[e] = aux;
return e;
}

void quickSortLS_Auxiliar(item *v, int LI, int LS){
    if(LI < LS){
        int p = particaoLS(v, LI, LS);
        quickSortLS_Auxiliar(v, LI, p-1);
        quickSortLS_Auxiliar(v, p+1, LS);
    }
}

void quickSortLS(item *v, int LI, int LS){
    clock_t start_time = clock();
    quickSortLS_Auxiliar(v, LI, LS);
    clock_t end_time = clock();
    printf(" %.4f s      ", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}



int randomIntNumber(int min, int max){
    return min + rand() %(max - min + 1);
}

double randomDouble(double min, double max){
    double r = (double) rand() / RAND_MAX;
    return min + r * (max - min);
}


void random(item v[]){
    for(int i = 0; i < tam; i++){
        v[i].chave = randomIntNumber(100000, 300000);       //perguntar se tem que ter intervalo nessa fun��o
        v[i].valor = randomDouble(100000, 500000); // fazer fun��o para gerar numero real aleatorio
    }
}

//arrumar isso aq
item * crescente(item v[]){
    int inicio = randomIntNumber(100000, 300000);
    for(int i = 0; i < tam; i++){
        v[i].chave = inicio;
        inicio += 100;
        v[i].valor = randomDouble(100000.0, 500000.0);
    }
    return v;
}

void printVetor(item v[]) {
    for (int i = 0; i < tam; i++) {
        printf("Pos %d -> chave: %d  |  valor: %.2lf\n",
               i, v[i].chave, v[i].valor);
    }
}


int main(){
    int semente = 2202;
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }


printf("\t Crescente \n      insSort        Quick[Li]      Quick[Meio]    Quick[Ls]\n");

    for(int i = 0; i < vet; i++){
        printf("#%2d: ", i+1);


        srand(semente + i);
        crescente(v);
        insertionSort(v, tam);

        srand(semente + i);
        crescente(v);
        quickSortLI(v, 0, tam-1);

        srand(semente + i);
        crescente(v);
        quickSortMEIO(v, 0, tam-1);

        srand(semente + i);
        crescente(v);
        quickSortLS(v, 0, tam-1);

        printf("\n");
    }

    printf("\n\t Aleatorio \n      insSort        Quick[Li]      Quick[Meio]    Quick[Ls]\n");


    for(int i = 0; i < vet; i++){
        printf("#%2d: ", i+1);


        srand(semente + i);
        random(v);
        insertionSort(v, tam);

        srand(semente + i);
        random(v);
        quickSortLI(v, 0, tam-1);

        srand(semente + i);
        random(v);
        quickSortMEIO(v, 0, tam-1);

        srand(semente + i);
        random(v);
        quickSortLS(v, 0, tam-1);

        printf("\n");
    }


/*
//20 insertion sort crescentes
for(int i=0; i< vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        fprintf(stderr, "Erro de aloca��o de mem�ria!\n");
        return 1;
    }

    srand(semente + i);
    crescente(v);
    printf("| InsertionSort | (Crescente) | #%d: ", i + 1);
    insertionSort(v, tam);

}
printf("----------------------------------------\n");

//20insertion sorts aleatorios
for(int i=0; i< vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }

    srand(semente + i);
    random(v);

    printf("| InsertionSort | (aleatorio) | #%d: ", i + 1);
    insertionSort(v, tam);
}

printf("----------------------------------------\n");

//20quicksorts crescente [Li]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    crescente(v);

    printf("| Quicksort[LI] | (Crescente) | #%d: ", i + 1);
    quickSortLI(v, 0, tam-1);
}

printf("----------------------------------------\n");

//20quicksorts aleatorio [Li]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    random(v);

    printf("| Quicksort[LI] | (aleatorio) | #%d: ", i + 1);
    quickSortLI(v, 0, tam-1);
}

printf("----------------------------------------\n");

//20quicksorts crescente [meio]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    crescente(v);

    printf("| Quicksort[MEIO] | (Crescente) | #%d: ", i + 1);
    quickSortMEIO(v, 0, tam-1);
}

printf("----------------------------------------\n");

//20quicksorts aleatorio [meio]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    random(v);

    printf("| Quicksort[MEIO] | (Aleatorio) | #%d: ", i + 1);
    quickSortMEIO(v, 0, tam-1);
}

printf("----------------------------------------\n");

//20quicksorts crescente [Ls]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    crescente(v);

    printf("| Quicksort[LS] | (Crescente) | #%d: ", i + 1);
    quickSortLS(v, 0, tam-1);
}

printf("----------------------------------------\n");

//20quicksorts aleatorio [Ls]
for(int i = 0; i < vet; i++){
    item *v = (item *)malloc(tam * sizeof(item));
    if(v == NULL){
        printf("Erro de aloca��o de mem�ria!\n");
        return 1;
    }
    srand(semente + i);
    random(v);

    printf("| Quicksort[LS] | (Aleatorio) | #%d: ", i + 1);
    quickSortLS(v, 0, tam-1);
}
*/
free(v);

return 0;

}
///remover vetores dos la�os e dar free(v) nele dps
///arrumar parti��o LS
///arrumar parti��o MEIO
///fazer la�o aleat�rio(INSERTION SORT, QUICKSORT[LI], QUICKSORT[MEIO], QUICKSORT[LS])
