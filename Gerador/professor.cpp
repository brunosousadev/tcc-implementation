#include "professor.hpp"


Professor::Professor(){

}
Professor::Professor(int code){
	codeProfessor = code;
}
Professor::~Professor(){

}

int Professor::getCodeProfessor(){
	return codeProfessor;
}

vector<int> Professor::getDiasPreferiveis(){
	return diasPreferiveis;
}
int Professor::getCargaHoraria(){
	return cargaHoraria;
}
vector<Turma*> Professor::getTurmas(){
	return turmas;
}

void Professor::setCodeProfessor(int code){
	codeProfessor = code;
}

void Professor::adicionarDiaPreferivel(int dia){
	diasPreferiveis.push_back(dia);
}

void Professor::setCargaHoraria(int cargar){
	cargaHoraria = cargar;
}

void Professor::adicionarTurma(Turma* novaTurma){
	turmas.push_back(novaTurma);
}
