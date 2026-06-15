#include "../models/despesa.h"
#include "ordenacao.h"

void bubblesort (Despesa lista[],int quantidade){
    
    int aux;
    
    for(int i=0; i < quantidade -1; i++){
        for(int j = 0; j < quantidade -i-1; j++){

            if(lista[j].valor > lista[j+1].valor){
                Despesa aux = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = aux;
            }
        }
    };
};

void selectionsort (Despesa lista[],int quantidade){

    for( int i=0 ; i < quantidade -1 ; i++ ){
        int menorpos = i;
        for(int j = i+1;j < quantidade; j++ ){
            if(lista[j].id < lista[menorpos].id){
                menorpos = j;
            }
        }
        Despesa aux = lista[i];
        lista[i]= lista[menorpos];
        lista[menorpos]=aux;
    };
};

void insertionsort(Despesa lista[], int quantidade) {
    for (int i = 1; i < quantidade; i++) {
        
        Despesa aux = lista[i]; // guarda a despesa inteira na mao
        int j = i - 1;
        
        while (j >= 0 && lista[j].categoria > aux.categoria) {
            lista[j+1] = lista[j]; // empurra para direita
            j--; // volta uma posicao para comparar com o anterior
        }
        
        lista[j+1] = aux; // coloca a despesa no lugar certo
    }
}

int buscabinaria(Despesa lista[], int quantidade, int idprocurado) {
    int esquerda = 0;
    int direita = quantidade - 1;
 
    while (esquerda <= direita) {// Calcula o meio atual
        int meio = (esquerda + direita) / 2;
 
        if (lista[meio].id == idprocurado) {
            return meio;// Encontrou — retorna a posição
        } else if (lista[meio].id < idprocurado) {            
            esquerda = meio + 1;// ID procurado está na metade direita
        } else {
            direita = meio - 1;// senao ID procurado esta na metade esquerda
        }
    }
    // Não encontrou
    return -1;
}