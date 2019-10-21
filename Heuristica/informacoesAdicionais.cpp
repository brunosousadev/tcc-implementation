#include "informacoesAdicionais.hpp"


InformacoesAdicionais::InformacoesAdicionais(){

}

InformacoesAdicionais::~InformacoesAdicionais(){

}

vector<int> InformacoesAdicionais::getDiasSemana(){
    return diasSemana;
}

vector<int> InformacoesAdicionais::getDiasSemanaComMuitoFeriado(){
    return diasDaSemanaComMuitoFeriado;
}

vector<int> InformacoesAdicionais::getSlotsHorarios(){
    return slotsHorarios;
}


void InformacoesAdicionais::addDiaSemana(int dia){
    diasSemana.push_back(dia);
}


void InformacoesAdicionais::addSlotHorario(int horario){
    slotsHorarios.push_back(horario);
}

void InformacoesAdicionais::addDiaSemanaComMuitoFeriado(int diaF){
    diasDaSemanaComMuitoFeriado.push_back(diaF);
}

