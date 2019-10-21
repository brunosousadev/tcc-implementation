#include "turma.hpp"

Turma::Turma(){

}

Turma::~Turma(){

}

int Turma::getCodeTurma(){
	return codeTurma;
}

int Turma::getCargarHorariaTeorica(){
	return cargarHorariaTeorica;
}

int Turma::getCargarHorariaPratica(){
	return cargarHorariaPratica;
}

void Turma::setCodeTurma(int code){
	codeTurma = code;
}

void Turma::setCargarHorariaTeorica(int cargarT){
	cargarHorariaTeorica = cargarT;
}

void Turma::setCargarHorariaPratica(int cargarP){
	cargarHorariaPratica = cargarP;
}