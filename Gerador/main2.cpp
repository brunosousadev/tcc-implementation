
/*
#include <iostream>
#include <vector>

using namespace std;



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

	num_moedas(N,M,m,rastreio);

	for (int i = 0; i < M; i++){
		cout <<rastreio[i] << "\n";
	}
	return 0;
}

#include <iostream>
#include <vector>

using namespace std;


struct tt
{
	int cc;
};
vector<tt> modificar(vector<tt> p){

		p[0].cc  = 21;

		return p;
}

int main(int argc, char const *argv[])
{

	vector<tt> c;

	tt aux; 
	aux.cc = 10;
	c.push_back(aux);
	cout <<  c[0].cc << "\n ";
	c = modificar(c);
	cout <<  c[0].cc << "\n ";


return 0;
}
*/