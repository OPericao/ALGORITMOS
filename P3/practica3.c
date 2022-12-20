//Programa hecho por Antonio Parada Miranda (a.paradam) y Lucas Pineiro Anon
//(lucas.pineiro.anon) del grupo 3.1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

#define MAX 256000
#define nMuestras 13
#define nInicial 1000

struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

arbol creararbol();
int esarbolvacio(arbol);
posicion buscar(int, arbol);
arbol eliminararbol(arbol);
posicion hijoizquierdo(arbol);
posicion hijoderecho(arbol);
int elemento(posicion);
int numerorepeticiones(posicion);
int altura(arbol);
void visualizar(arbol);

double microsegundos();
void inicializar_semilla();
void aleatorio(int v [], int n);

arbol funcionInsertar(int v[], int n, arbol a);
void funcionBuscar(int v[], int n, arbol a);
void tablaArbol();
void tablaInsBus();
double medirTiempoBus();
double auxiliarTiempoBus();
double auxiliarTiempoIns();
void insercionNelementos();
void busquedaNelementos();

static struct nodo *crearnodo(int e) {
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("memoria agotada\n"); 
        exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol insertar(int e, arbol a){
    if (a == NULL){
        return crearnodo(e);
    }else if (e < a->elem){
        a->izq = insertar(e, a->izq);
    }else if (e > a->elem){
        a->der = insertar(e, a->der);
    }
    else
        a->num_repeticiones++;
    return a;
}

arbol creararbol(){
	arbol a;
    return a = NULL;
}

int esarbolvacio(arbol a){
    return (a==NULL);
}

posicion buscar(int dato, arbol a){
    if(esarbolvacio(a)){
        return NULL;
    }else{
        if(a->elem!=dato){
            if(dato<a->elem){
                return buscar(dato,a->izq);
            }else{
                return buscar(dato,a->der);
            }
        }
        return a;
    }
}

arbol eliminararbol(arbol a){
    if(!esarbolvacio(a)){
    	eliminararbol(a->izq);
        eliminararbol(a->der);       
        free(a);
        a = NULL;
    }
    return a;
}

posicion hizoizquierdo(arbol a){
    return a->izq;
}

posicion hijoderecho(arbol a){
    return a->der;
}

int elemento(posicion pos){
    return pos->elem;
}

int numerorepeticiones(posicion pos){
    return pos->num_repeticiones;
}

int altura(arbol a){
    int alt=-1;
    if(a!=NULL){
        if(a->der!=NULL){
            alt = altura(a->der);
        }else if(a->izq!=NULL){
            alt = altura(a->izq);
        }
        alt++;
    }
    return alt;
}

void visualizar(arbol a){
    if(a==NULL) printf("(");
	if(a!=NULL){
	if(a->izq!=NULL){
		printf("(");
		visualizar(a->izq);
	}
	if(a->izq==NULL) printf("(");
	printf(" %d ", a->elem);
	if(a->der!=NULL){
		visualizar(a->der);
		printf(")");
	}
	if(a->der==NULL) printf(")");
	}
	if(a==NULL) printf(")");
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 ){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}

arbol funcionInsertar(int v[], int n, arbol a){
	int i = 0;
    for(i=0;i<n;i++){
        a = insertar(v[i],a);
    }
    return a;
}

void funcionBuscar(int v[], int n, arbol a){
	int i = 0;
    for(i=0;i<n;i++){
        buscar(v[i],a);
    }
}

double medirTiempoBus(int v[], int n, arbol a){
    double t1,t2;
    aleatorio(v,n);    
    t1 = microsegundos();
    funcionBuscar(v,n,a);
    t2 = microsegundos();
    return (t2-t1);
}

double auxiliarTiempoIns(int v[],int k,int n,arbol a){
	arbol aAux,a2;
    double t1,t2,tIns,tElim,tTotal;
    aAux = creararbol();
    a2 = creararbol();
    int i = 0,j = 0;    
    t1 = microsegundos();
    for(i = 0; i < k; i++){
        a2 = funcionInsertar(v,n,a2);
        a2 = eliminararbol(a2);
    }
    t2 = microsegundos();
    tIns = (t2 - t1);    
    for(j = 0; j < k; j++){
        aleatorio(v,n);
        aAux = funcionInsertar(v,n,aAux);
    }    
    t1 = microsegundos();
    aAux = eliminararbol(aAux);
    t2 = microsegundos();
    tElim = (t2-t1);
    tTotal = (tIns - tElim)/k;
    return tTotal;
}

double auxiliarTiempoBus(int v[], int k, int n, arbol a){
    double t1,t2,t,tAux;
    int i = 0,j = 0;
    t1 = microsegundos();
    for(i = 0; i < k; i++){
    	   aleatorio(v,n);
        funcionBuscar(v,n,a);
    }
    t2 = microsegundos();
    t = (t2-t1);    
    t1 = microsegundos();
    for(j = 0; j < k; j++){
    	   aleatorio(v,n);
    }
    t2 = microsegundos();
    tAux = (t2-t1);
    return (t - tAux)/k;
}

void testA(){
	arbol b;
	b = creararbol();
	printf("Inserto un 10\n");
    b = insertar(10,b);
    printf("Inserto un 6\n");
    b = insertar(6,b);
    printf("Inserto un 17\n");
    b = insertar(17,b);
    printf("Inserto un 9\n");
    b = insertar(9,b);
    printf("Inserto un 12\n");
    b = insertar(12,b);
    printf("Inserto un 7\n");
    b = insertar(7,b);
    printf("Inserto un 14\n");
    b = insertar(14,b);
    printf("Inserto un 3\n");
    b = insertar(3,b);
    printf("Inserto un 19\n");
    b = insertar(19,b);
    printf("Inserto un 3\n");
    b = insertar(3,b);
    printf("arbol: ");
    visualizar(b);
    printf("\naltura del arbol: %d", altura(b));
    if(buscar(3,b)!=NULL){
        printf("\nbusco 3 y encuentro 3 repetido: %d veces", numerorepeticiones(buscar(3,b)));
    }else printf("\nbusco 3 y no encuentro nada");
    if(buscar(14,b)!=NULL){
    	printf("\nbusco 14 y encuentro 14 repetido: %d veces", numerorepeticiones(buscar(14,b)));
    }else printf("\nbusco 14 y no encuentro nada");
    if(buscar(1,b)!=NULL){
    	printf("\nbusco 1 y encuentro 1 repetido: %d veces", numerorepeticiones(buscar(1,b)));
    }else printf("\nbusco 1 y no encuentro nada");
    printf("\nborro todos los nodos liberando la memoria: ");
    b = eliminararbol(b);
    printf("\narbol vacio: ");
    visualizar(b);
    printf("\naltura del arbol: %d\n", altura(b));
}


int main(){
	inicializar_semilla();
	testA();
    tablaInsBus();
    tablaInsBus();
    tablaInsBus();
}


void tablaInsBus(){
    arbol a;
    a = creararbol();
    int v[MAX],n,k=1000;
    double vIns[nMuestras],vBus[nMuestras];
    double t_ins,t_bus,t1,t2;
    printf("\n%12sn%9st_ins (n)%12st_bus (n)\n","","","");
    for(n=nInicial;n<=MAX;n=n*2){
    	a = eliminararbol(a);
    	aleatorio(v,n);
        t1 = microsegundos();
        a = funcionInsertar(v,n,a);
        t2 = microsegundos();
        t_ins = t2 - t1;
        vIns[(int)(log(n/nInicial)/ log(2))] = t_ins;
        t_bus = medirTiempoBus(v,n,a);
        vBus[(int)(log(n/nInicial)/log(2))] = t_bus;
        if(t_ins<500){
            t_ins = auxiliarTiempoIns(v,k,n,a);
            vIns[(int)(log(n/nInicial)/log(2))] = t_ins;
        }
        if(t_bus<500){
            t_bus = auxiliarTiempoBus(v,k,n,a);
            vBus[(int)(log(n/nInicial)/log(2))] = t_bus;
        }
        if(t_ins<500){
            printf("(*)"); 
            printf("%12d%15.3f", n,vIns[(int)(log(n/nInicial)/log(2))]);
        } 
        else printf("   %12d%15.3f", n,vIns[(int)(log(n/nInicial)/log(2))]);
        if(t_bus<500){
        	printf("   (*)");
        	printf("%15.3f\n",vBus[(int)(log(n/nInicial)/log(2))]);    
        }
        else printf("      %15.3f\n",vBus[(int)(log(n/nInicial)/log(2))]);    
    }
    insercionNelementos(vIns);
    busquedaNelementos(vBus);
}

void insercionNelementos(double vIns[]){
    int n;
    double x, y, z;
    printf("\nInsercion de n elementos");
    printf("\n%13sn%11st(n)%7st(n)/n^1.1%4st(n)/n^1.28%4sf(n)/n^1.45\n","","","","","");
    for(n=nInicial;n<=MAX;n=n*2){
        x = vIns[(int)(log(n/nInicial)/log(2))]/pow(n,1.1);
        y = vIns[(int)(log(n/nInicial)/log(2))]/pow(n,1.28);
        z = vIns[(int)(log(n/nInicial)/log(2))]/pow(n,1.45);
        if(vIns[(int)(log(n/nInicial)/log(2))]<500){
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, vIns[(int)(log(n/nInicial)/log(2))], x, y, z);
        } else printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, vIns[(int)(log(n/nInicial)/log(2))], x, y, z);
    }
}

void busquedaNelementos(double vBus[]){
    int n;
    double x, y, z;
    printf("\nBusqueda de n elementos");
    printf("\n%13sn%11st(n)%7st(n)/n^1.1%4st(n)/n^1.28%4sf(n)/n^1.45\n","","","","","");
    for(n=nInicial;n<=MAX;n=n*2){
        x = vBus[(int)(log(n/nInicial)/log(2))]/pow(n,1.1);
        y = vBus[(int)(log(n/nInicial)/log(2))]/pow(n,1.28);
        z = vBus[(int)(log(n/nInicial)/log(2))]/pow(n,1.45);
        if(vBus[(int)(log(n/nInicial)/log(2))]<500){
            printf("(*)");
            printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, vBus[(int)(log(n/nInicial)/log(2))], x, y, z);
        } else printf("   %12d%15.3f%15.6f%15.6f%15.6f\n", n, vBus[(int)(log(n/nInicial)/log(2))], x, y, z);
    }
}















