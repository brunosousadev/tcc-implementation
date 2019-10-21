#include "tabu.hpp"

Tabu::Tabu(){

}

Tabu::~Tabu(){

}

Tabu::Tabu(Solucao s, valores_quebraDia_quebraTurma fo){
	solucao = s;
	valorFO = fo;
}


Solucao Tabu::getSolucao(){
	return solucao;
}
 
valores_quebraDia_quebraTurma  Tabu::getValorFO(){
 return valorFO;
}
	

void Tabu::setSolucao(Solucao s){
	solucao = s;
}

void Tabu::setValorFO(valores_quebraDia_quebraTurma fo){
	valorFO = fo;
}
