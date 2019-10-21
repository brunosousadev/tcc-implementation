
#include "professor.hpp"



Professor::Professor(){

}

Professor::Professor(int si, string nomeP){
    siape = si;
    nome = nomeP;
}
Professor::Professor(int si, string nomeP, int cargH, vector<Turma*> turmas, vector<int> dias){
    siape = si;
    nome = nomeP;
    cargHorariaTrabalho = cargH;
    turmasComFamiliaridade = turmas;
    diasPreferiveisTrabalho = dias;
}
Professor::Professor(int si, string nomeP, int cargH, vector<Turma*> turmas, vector<int> dias, vector<Turma*> turmasA){
    siape = si;
    nome = nomeP;
    cargHorariaTrabalho = cargH;
    turmasComFamiliaridade = turmas;
    diasPreferiveisTrabalho = dias;
    turmasAlocadas =turmasA;
}

Professor::~Professor(){

}

int Professor::getSiape(){
    return siape;
}
string Professor::getNome(){
    return nome;
}

int Professor::getCargHorariaTrabalho(){
    return cargHorariaTrabalho;
}

vector<Turma*> Professor::getTurmasComFamiliaridade(){
    return turmasComFamiliaridade;
}

vector<int> Professor::getDiasPreferiveisTrabalho(){
    return diasPreferiveisTrabalho;
}


vector<Turma*> Professor::getTurmasAlocadas(){
    return turmasAlocadas;
}


void Professor::addTurmaAlocada(Turma* turma){
    turma->setSiapeProfessor(siape);
    turmasAlocadas.push_back(turma);
}


/*
Metodo com a função de calcular quantas turmas foram alocados ao professor
que não estão compreendido nas turmas familiar do professor


    retorno: acumulado (quantidade de turmas que foram alocadas que não são do grupo familiar dele.)
*/

int Professor::calcularQntTurmasDif_Familiaridade(){
    int acumulado=0;    
    int qntTurmas  = turmasAlocadas.size();
    for (int i = 0; i < qntTurmas; i++){
        if(verificarTurmaFamiliar(turmasAlocadas[i]->getComponenteCurricular())) 
            acumulado++;
    }
    return acumulado;
}

/*
 Função tem como finalidade verificar se uma turma está dentro das turmas 
 que o professor tem familiaridade.

    Parametros: componentCurricular

    retorna 0 se encontrar e retorna 1 caso contrário
*/
int Professor::verificarTurmaFamiliar(string componenteCurricular){
    int tam = turmasComFamiliaridade.size();
    for (int i = 0; i < tam; i++){
        if(turmasComFamiliaridade[i]->getComponenteCurricular() == componenteCurricular) 
            return 0;
    }
    return 1;
}
/*
 Metodo para verificar se um dia está dentro dos dias preferiveis de trabalho do professor

    Parametros: dia

    retorno: 1 se estíver, 0 caso contrário

*/
int Professor::verificarContemDiaNosDiasPreferiveis(int dia){
    if((find(diasPreferiveisTrabalho.begin(), diasPreferiveisTrabalho.end(), dia) != diasPreferiveisTrabalho.end()) == false){
        return 1;
    }else{
        return 0;
    }    
}

/*
Metodo com a finalidade de verificar se o professor já cumpriu sua carga horária, ou seja,
se a carga horaria total das n turmas que foram alocadas para ele for equivalente a sua carga horaria

retorno: true se tiver cumprido, false caso contrário.

*/
bool Professor::verificarCumprimentoTotalCargaHorariaTrabalho(){
    int tam  = turmasAlocadas.size();
    int acumulador =0;
    for (int i = 0; i < tam; i++){
        acumulador+= (turmasAlocadas[i]->getCreditoTeorico() + turmasAlocadas[i]->getCreditoPratico());
    }

    if(acumulador == cargHorariaTrabalho) return true;
    else return false;
}


void Professor::adicionarTurmaComFamiliaridade(Turma* turma){

    turmasComFamiliaridade.push_back(turma);
}

void Professor::adicionarDiaPreferivei(int dia){
    diasPreferiveisTrabalho.push_back(dia);
}

void Professor::setCargHorariaTrabalho(int valor){
    cargHorariaTrabalho = valor;
}


void Professor::imprimir(){
    cout <<" ( siape: "<< siape << " | Nome: "<< nome << " | cargHorariaTrabalho: "<<cargHorariaTrabalho << " )\n";    
}