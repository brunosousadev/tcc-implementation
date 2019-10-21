#include "turmaOrdenacaoAglutinado.hpp"


TurmaOrdenacaoAglutinado::TurmaOrdenacaoAglutinado(){ 

}

TurmaOrdenacaoAglutinado::~TurmaOrdenacaoAglutinado(){ 

}
TurmaOrdenacaoAglutinado::TurmaOrdenacaoAglutinado(int nValor, TurmaDTO turma){
	valor = nValor;
	quantidade=0;
	turmasDTOs.push_back(turma);
	quantidade++;
}

vector<TurmaDTO> TurmaOrdenacaoAglutinado::getTurmasDTOs(){
	return turmasDTOs;
}

int TurmaOrdenacaoAglutinado::getQuantidade(){ 
	return quantidade;
}

int TurmaOrdenacaoAglutinado::getValor(){ 
	return valor;
}

void TurmaOrdenacaoAglutinado::setTurmasDTOs(vector<TurmaDTO> turmas){ 
	turmasDTOs = turmas;
}

void TurmaOrdenacaoAglutinado::adicionarTurmaDTO(TurmaDTO turma){ 
	turmasDTOs.push_back(turma);
	quantidade++;	
}

void TurmaOrdenacaoAglutinado::setQuantidade(int nQuantidade){ 
	 quantidade = nQuantidade;
}

void TurmaOrdenacaoAglutinado::setValor(int nValor){ 
	valor  = nValor;
}

void TurmaOrdenacaoAglutinado::setQuantidadeMenor(int menos){
	quantidade-=menos;
}

TurmaDTO TurmaOrdenacaoAglutinado::getTurmaDTO(int id){
	if(turmasDTOs.size() >  0){
		TurmaDTO turmaDTO = TurmaDTO(turmasDTOs[id].getComponenteCurricular(), turmasDTOs[id].getCarga());
		turmasDTOs.erase(turmasDTOs.begin()+id);	 
		return turmaDTO;	
	}else{
		return TurmaDTO(-1);
	}
	
}
void TurmaOrdenacaoAglutinado::imprimir1(){
	//cout << "\n";
	cout << "[valor: " << valor << "| quantidade: "<< quantidade<<" ";
	//imprimir2();
	//cout << "\n";
}
void TurmaOrdenacaoAglutinado::imprimir2(){

	for(auto& t: turmasDTOs){
		cout << " ("<< t.getComponenteCurricular() << " ," <<  t.getCarga() << ")";
	}
}