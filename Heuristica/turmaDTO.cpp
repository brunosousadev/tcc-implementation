#include "turmaDTO.hpp"

TurmaDTO::TurmaDTO(){

}

TurmaDTO::~TurmaDTO(){

}

TurmaDTO::TurmaDTO(string componente, int valor){
	componenteCurricular= componente;
	carga=valor;
}
TurmaDTO::TurmaDTO(int valor){
	carga=valor;	
}

string TurmaDTO::getComponenteCurricular(){
	return componenteCurricular;
}

int TurmaDTO::getCarga(){
 return carga;
}

void TurmaDTO::imprimir(){
	cout <<  "[ComponenteCurricular: " <<  componenteCurricular << " | carga: " << carga<<"\n";
}