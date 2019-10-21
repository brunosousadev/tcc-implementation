#include "professorDTO.hpp"


ProfessorDTO::ProfessorDTO(){

}
ProfessorDTO::~ProfessorDTO(){

}
ProfessorDTO::ProfessorDTO(int nSiape, int nCargaHoraria){
	siape = nSiape;
	cargaHoraria = nCargaHoraria;
}

int ProfessorDTO::getSiape(){
	return siape;
}
int ProfessorDTO::getCargaHoraria(){
	return cargaHoraria;
}

void ProfessorDTO::imprimir(){
	cout << "[SIAPE: "<< siape << " | cargaHoraria: "<< cargaHoraria <<"\n";
}