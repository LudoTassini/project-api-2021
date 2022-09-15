#include <stdio.h>
#include <stdlib.h>
#define INF_INT 1000000000

typedef struct{
	int indice;
	int somma;
} grafo;

void AGGIUNGI_GRAFO(int indice, int nodi, int* cammino_minimo, int** matrice);
void TOP_K(grafo* chart, int lim, int k);
int ATOI(int str[], int dim);
int POW(int base, int esponente);
int DIJKSTRA(int** Grafo, int nodi, int s);
void SWAP(grafo* chart, int x, int y);
void MAX_HEAPIFY(grafo* heap, int ind, int k);

int main(void){
    
    int d=0, k=0, cont=0;
	int lettera;
	int cifre=0;
	int i, flag=1;
	int somma_Dijkstra=0;
	int** matr;
	int input[8];
	
	for(i=0; i<8; i++)
		input[i]=' ';
	
	i=0;
    do{
        lettera=getchar_unlocked();
        if(lettera==' '){
            d=ATOI(input, cifre);
			for(i=0; i<cifre; i++)
				input[i]=' ';
			i=0;
			cifre=0;
        }
        else if(lettera=='\n'){
            k=ATOI(input, cifre);
			for(i=0; i<cifre; i++)
				input[i]=' ';
            flag=0;
        }
        else{
			input[i]=lettera-48;
			i++;
			cifre++;
        }
    }while(flag!=0);
	
	grafo* classifica=malloc(k*sizeof(grafo));
	for(i=0; i<k; i++)
        classifica[i].somma=INF_INT;

	matr=(int**)malloc(d*sizeof(int*));
	for(i=0; i<d; i++)
		matr[i]=(int*)malloc(d*sizeof(int));

	flag=1;
    do{
        lettera=getchar_unlocked();
        if(lettera=='A'){
			while(lettera!='\n')
				lettera=getchar_unlocked();
            AGGIUNGI_GRAFO(cont, d, &somma_Dijkstra, matr);
            if(somma_Dijkstra<classifica[0].somma){
				classifica[0].indice=classifica[k-1].indice;
				classifica[0].somma=classifica[k-1].somma;
				classifica[k-1].somma=-INF_INT;
			 	MAX_HEAPIFY(classifica, 0, k);
				classifica[k-1].somma=somma_Dijkstra;
				classifica[k-1].indice=cont;
				i=k-1;
				while(i>0 && classifica[(i-1)/2].somma<classifica[i].somma){
					SWAP(classifica, (i-1)/2, i);
					i=(i-1)/2;
				}
            }
            cont++;
        }
        else{
            if(lettera=='T'){
                while(lettera!='\n')
					lettera=getchar_unlocked();
				i=0;
				if(cont>=k){
        			i=k;
					TOP_K(classifica, i, k);
				}
    			else{
        			i=cont;
					if(i!=0)
                		TOP_K(classifica, i, k);
					else
						printf("\n");
				}
            }
            else 
				flag=0;
        }
    }while(flag!=0);
	
	free(classifica);
	for(i=0; i<d; i++)
		free(matr[i]);
	free(matr);	

    return 0;

}

void AGGIUNGI_GRAFO(int indice, int nodi, int* cammino_minimo, int** matrice){
    
    int i, j;
	int input[8];
    int pos=0, cifre=0;
	int carattere=0;

    for(i=0; i<nodi; i++){
        j=0;
        while(j!=nodi){
            carattere=getchar_unlocked();
            if(carattere==',' || carattere=='\n'){
                matrice[i][j]=ATOI(input, cifre);
                j++;
				for(pos=0; pos<cifre; pos++)
					input[pos]=' ';
				cifre=0;
				pos=0;
            }
            else{
                input[pos]=carattere-48;
				pos++;
				cifre++;
            }
        }
    }
    
    *cammino_minimo=DIJKSTRA(matrice, nodi, 0);

}

void TOP_K(grafo* chart, int lim, int k){
    
	int i=k-1;

	while(i>=0 && lim>0){
		if(chart[i].somma!=INF_INT){
			if(lim==1)
				printf("%d\n", chart[i].indice);
			else
				printf("%d ", chart[i].indice);
			lim--;
		}
		i--;
	}

}

int ATOI(int str[], int dim){
    
	int i, ris=0;
	int num1, num2;
	
	for(i=0; i<dim; i++){
		num1=str[i];
		num2=POW(10, dim-i-1);
		ris=ris+(num1*num2);
	}

	return ris;
    
}

int POW(int base, int esponente){

	int i, ris=1;

	for(i=0; i<esponente; i++)
		ris=ris*base;
	
	return ris;	

}

int DIJKSTRA(int** Grafo, int nodi, int s){
    
    int dist[nodi], visitati[nodi];
    int i;
	int cont=0, v, u;
    int somma=0, min;
    
    for(i=0; i<nodi; i++){
        dist[i]=INF_INT;
        visitati[i]=0;
    }
    dist[s]=0;

    for(cont=0; cont<nodi-1; cont++){
        min=INF_INT;
		u=0;
        for(v=0; v<nodi; v++){
            if(visitati[v]==0 && dist[v]<=min){
                min=dist[v];
				u=v;
            }
        }
        visitati[u]=1;
        for(v=0; v<nodi; v++){
            if(dist[u]!=INF_INT && Grafo[u][v]!=0 && visitati[v]==0 && dist[u]+Grafo[u][v]<dist[v])
                dist[v]=dist[u]+Grafo[u][v];
        }
    }

    for(i=1; i<nodi; i++){
        if(dist[i]!=INF_INT)
            somma=somma+dist[i];
    }
    return somma;
    
}

void SWAP(grafo* chart, int x, int y){

	int t1=0, t2=0;

	t1=chart[x].indice;
	t2=chart[x].somma;

	chart[x].indice=chart[y].indice;
	chart[x].somma=chart[y].somma;

	chart[y].indice=t1;
	chart[y].somma=t2;

}

void MAX_HEAPIFY(grafo* heap, int ind, int k){
    
    int sx=2*ind+1, dx=2*ind+2, pos_max;

    if(sx<k && heap[sx].somma>heap[ind].somma)
        pos_max=sx;
    else
        pos_max=ind;
    
    if(dx<k && heap[dx].somma>heap[pos_max].somma)
        pos_max=dx;
    if(pos_max!=ind){
        SWAP(heap, ind, pos_max);
        MAX_HEAPIFY(heap, pos_max, k);
    }

}
