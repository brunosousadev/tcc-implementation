/*
#include <stdio.h>


// função que recebe o valor de troco N, o número de moedas disponíveis M,
// e um vetor com as moedas disponíveis m
// essa função deve retornar o número mínimo de moedas, de acordo com a estratégia gulosa
void  num_moedas(int N, int M, int *m, int *rastreio) {    

    // vamos supor que o vetor m esteja ordenado em ordem crescente
    // portanto, a moeda de maior valor está no final do vetor
    for(int i=M-1; i>=0; i--) {
        int aux = N/m[i]; // número de moedas de valor m[i]
        rastreio[i] = aux; // guarda a solução
        N -= aux * m[i]; // subtrai-se esse valor de N        
    }    
}


int main(int argc, char const *argv[])
{

	int M=4;

	int m[4]={2,4,6,8};
	int rastreio[M];
	int N = 4;

	num_moedas(N,M,&m,&rastreio);
	for (int i = 0; i < 4; i++)
	{
		printf("rastreio[%d]=%d\n",i,rastreio[i]);
	}



	return 0;
}

*/