#include "turma.hpp"


Turma::Turma(){

}

Turma::~Turma(){

}
Turma::Turma(string nome){
    nomeTurma = nome;
}

Turma::Turma(string componentC, string nome){
    componenteCurricular = componentC;
    nomeTurma = nome;
}
Turma::Turma(string componentC, int creditoT, int creditoP, string nome, int tipoT, int siape){
    componenteCurricular = componentC;
    creditoTeorico = creditoT;
    creditoPratico = creditoP;
    nomeTurma = nome;

    if(tipoT == 1) tipo = OBRIGATORIA;
        else 
            tipo = OPTATIVA;   

    siapeProfessor = siape;
    alocada = 0;

    setCaracteristicaTurma(creditoT,creditoP);
}

Turma::Turma(string componentC, int creditoT, int creditoP, string nome, int tipoT){
    componenteCurricular = componentC;
    creditoTeorico = creditoT;
    creditoPratico = creditoP;
    nomeTurma = nome;
	siapeProfessor = -1;    
    if(tipoT == 1) tipo = OBRIGATORIA;
    else tipo = OPTATIVA;    

    setCaracteristicaTurma(creditoT,creditoP);

    alocada = 0;    
}

Turma::Turma(string componentC, int creditoT, int creditoP, string nome, TipoTurma tipoT,int siapeP, int nAlocada){
    componenteCurricular = componentC;
    creditoTeorico = creditoT;
    creditoPratico = creditoP;
    nomeTurma = nome;
    siapeProfessor = siapeP; 

    if(tipoT == 1) tipo = OBRIGATORIA;
    else tipo = OPTATIVA;    
    alocada = nAlocada;    

    setCaracteristicaTurma(creditoT,creditoP);
    
}

string Turma::getComponenteCurricular(){
    return componenteCurricular;
}

int Turma::getCreditoPratico(){
    return creditoPratico;
}

int Turma::getCreditoTeorico(){
    return creditoTeorico;
}

string Turma::getNomeTurma(){
    return nomeTurma;
}

TipoTurma Turma::getTipo(){
    return tipo;
}

int Turma::getSiapeProfessor(){
    return siapeProfessor;
}

int Turma::getAlocada(){
    return alocada;
}
CaracteristicaTurma Turma::getCaracteristicaTurma(){
    return caracteristica;
}

void Turma::setComponenteCurricular(string componente){
    componenteCurricular = componente;
}

void Turma::setCreditoTeorico(int creditoT){
    creditoTeorico = creditoT;
}

void Turma::setCreditoPratico(int creditoP){
    creditoPratico = creditoP;
}

void Turma::setNomeTurma(string nome){
    nomeTurma = nome;
}

void Turma::setTipo(TipoTurma tipoT){
    tipo = tipoT;
}

void Turma::setSiapeProfessor(int siape){
    siapeProfessor = siape;
}

void Turma::setAlocada(int valor){
    alocada = valor;
}


/*
    0 - TEORICA
    1 - TEORICA_PRATICA
    2 - PRATICA
*/
void Turma::setCaracteristicaTurma(int teorica, int pratica){
    if(teorica > 0 && pratica > 0) caracteristica = TEORICA_PRATICA;
    else if(pratica > 0) caracteristica = PRATICA;
    else  caracteristica = TEORICA;
}


string Turma::getNomeCaracteristicaTurma(){
    if(caracteristica == 0) return "TEORICA";
    if(caracteristica == 1) return "TEORICA_PRATICA";
    if(caracteristica == 2) return  "PRATICA";
}

void Turma::imprimir(){
    cout << "[ Turma: " <<  getComponenteCurricular() << " CredT: " <<  creditoTeorico << " CredP: " <<  creditoPratico << " nomeTurma: " << nomeTurma << " siapeProfessor: "<< siapeProfessor << " alocada: "<< alocada << " ]\n";
}

int Turma::getCargaHorariaTotal(){
    return creditoTeorico+ creditoPratico;   
}


