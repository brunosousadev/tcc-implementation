#include <cstdlib>
#include <ctime>
#include <iostream>

#include "gerador.hpp"
#include "professor.hpp"
#include "turma.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	srand((unsigned)time(0)); //para gerar números		
	/*
	if(argc < 2){
		cout << "falta argumentos \n";
		return 0;
	}
	*/
							 //2,4,6,8,10,12,14
   	//vector<int> porcentagem= {10,10,0,20,20,30,10}; classe 4
	//vector<int> porcentagem= {0,0,0,10,30,30,30}; classe 2
	//vector<int> porcentagem= {30,30,10,0,0,0,0}; classe 3	
	Gerador g = Gerador();	
		
	int professor = 10;	
	for (int i = 1; i <=100; i++){
		g.executar(1,i,professor,porcentagem,10,2015);
		g = Gerador();
		professor+=5;
	}	
	return 0;
}
