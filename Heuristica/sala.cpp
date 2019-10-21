#include "sala.hpp"


Sala::Sala(){

}

Sala::Sala(string cod, int nTipo, int nQuantidadeDeTurmasAlocada, int nAlocadaBloco, Grade NgradeHorario[][5]){
    codSala = cod;
    tipoSala = nTipo;
    quantidadeDeTurmasAlocada = nQuantidadeDeTurmasAlocada;
    alocadaBloco = nAlocadaBloco;
    int horario,dia,count =5; 
    for(horario = 0; horario < (count -1); horario++)
    {        
        for(dia = 0; dia < count; dia++)
        {
            if(NgradeHorario[horario][dia].status){
                gradeHorario[horario][dia].status = 1;                                                           
                gradeHorario[horario][dia].turma = new Turma(NgradeHorario[horario][dia].turma->getComponenteCurricular(),
                                                            NgradeHorario[horario][dia].turma->getCreditoTeorico(),
                                                            NgradeHorario[horario][dia].turma->getCreditoPratico(),
                                                            NgradeHorario[horario][dia].turma->getNomeTurma(),
                                                            NgradeHorario[horario][dia].turma->getTipo(),
                                                            NgradeHorario[horario][dia].turma->getSiapeProfessor(),
                                                            NgradeHorario[horario][dia].turma->getAlocada());                 
            }else{
                gradeHorario[horario][dia].status = 0;            
                gradeHorario[horario][dia].turma = new Turma();                    
            }
        }
    }    
}
Sala::Sala(string cod, int tipoS){
    // 4 HORÁRIOS X 5 DIAS DA SEMANA 
    codSala = cod;
    tipoSala = tipoS;
    int horario,dia,count =5; 
    quantidadeDeTurmasAlocada = 0;
    alocadaBloco= 0;
    for(horario = 0; horario < (count -1); horario++)
    {        
        for(dia = 0; dia < count; dia++)
        {          
            gradeHorario[horario][dia].status = 0;            
            gradeHorario[horario][dia].turma = new Turma();                    
        }   
    }
}

Sala::~Sala(){

}

string Sala::getCodSala(){
    return codSala;
}

int  Sala::getTipoSala(){
    return tipoSala;
}

string Sala::getNomeSala(){
    if(getTipoSala()) return "Sala";
    else return "Lab.";      
}

void Sala::setCodSala(string  cod){
    codSala = cod;
}

void Sala::setTipoSala(int tipo){
    tipoSala = tipo;
}

bool Sala::trocarTurmasDeAlocacoes(string componenteCurricular1, string componenteCurricular2){
    
    AuxTrocaTurmas aux1 = procurarTurmaIJ(componenteCurricular1);
    AuxTrocaTurmas aux2 = procurarTurmaIJ(componenteCurricular2);
    
    if(aux1.horario == -1 || aux2.horario==-1) return false;

    Grade temp= gradeHorario[aux1.horario][aux1.dia];    

    gradeHorario[aux1.horario][aux1.dia]= gradeHorario[aux2.horario][aux2.dia];    
    gradeHorario[aux2.horario][aux2.dia] = temp;

    
    return true;
}

AuxTrocaTurmas Sala::procurarTurmaIJ(string componenteCurricular){
    int horario,dia,count =5;     
    AuxTrocaTurmas result;
    result.horario=-1;
    result.dia=-1;

     for(horario = 0; horario < (count -1); horario++)
    {        
        for(dia = 0; dia < count; dia++)
        {
            if(gradeHorario[horario][dia].turma->getComponenteCurricular() == componenteCurricular){
                result.horario=horario;
                result.dia=dia;
                return result;
            }
        }
    }
    return result;

}

bool Sala::removerTurma(int horario, int dia){
    if(horario < 0 || horario > 4 || dia< 0 || dia > 5) return false;
    
    gradeHorario[horario][dia].status = 0;    
    gradeHorario[horario][dia].turma = new Turma();
    quantidadeDeTurmasAlocada--;

    return true;

}
bool Sala::alocarTurma(Turma *turma, int horario, int dia){    
       
    if(horario < 0 || horario > 4 || dia< 0 || dia > 5) return false;

    if(gradeHorario[horario][dia].status) return false;
 
    gradeHorario[horario][dia].status = 1;    
    gradeHorario[horario][dia].turma = turma;
    quantidadeDeTurmasAlocada++;
    return true;
}

Turma* Sala::getTurma(int horario, int dia){
	return gradeHorario[horario][dia].turma;
}

bool Sala::verificarGradeCheia(){
    if(quantidadeDeTurmasAlocada == capacidadeTotalDaGrade) return true;
    else return false;
}


int Sala::getAlocadaBloco(){
    return alocadaBloco;
}

void Sala::setAlocadaBloco(int value){
    alocadaBloco = value;
}


int Sala::verificarDisponibilidadeHorarioDia(int horario, int dia){
    if(horario < 0 || horario > 4 || dia< 0 || dia > 5) return 0;
    
    return gradeHorario[horario][dia].status;
}


int Sala::verificarSalaComportarTurma(int qntCreditos){
    if((qntCreditos + quantidadeDeTurmasAlocada) == capacidadeTotalDaGrade) return 1;
    else return 0;
}

vector<int> Sala::diasDaTurmaAlocada(string componenteCurricular){
    vector<int> acumulador;
    int horario,dia,count =5;  
      for(horario = 0; horario < (count -1); horario++){        
        for(dia = 0; dia < count; dia++){
            if(gradeHorario[horario][dia].turma->getComponenteCurricular() == componenteCurricular)            
                acumulador.push_back(dia);
        }
    }

    return acumulador;
}

int Sala::getQuantidadeDeTurmasAlocada(){
    return quantidadeDeTurmasAlocada;
}

int Sala::getCapacidadeTotalDaGrade(){
    return capacidadeTotalDaGrade;
}

void Sala::imprirSituacaoLacuna(int horario, int dia){
    cout << gradeHorario[horario][dia].status << "\n";
}

void Sala::imprimirGradeHorario(){
    int horario,dia,count =5;  
      for(horario = 0; horario < (count -1); horario++){        
        for(dia = 0; dia < count; dia++){
            printf("grade[%d][%d]= [ %d ]",horario, dia,gradeHorario[horario][dia].status);            
        }
        cout << "\n";
    }
}

AuxTrocaTurmas Sala::procurarLacunaDia(int dia){
    int horario,count =5;  
    AuxTrocaTurmas  resultado;
    resultado.horario = -1;
    resultado.dia = dia;
    for(horario = 0; horario < (count -1); horario++){
        if(gradeHorario[horario][dia].status == 0){
            resultado.horario = horario;
        }
    }
    return resultado;
}

AuxTrocaTurmas Sala::procurarLacuna(){
    int horario,dia,count =5;  
    AuxTrocaTurmas  resultado;
    resultado.horario = -1;
    resultado.dia = -1;
    for(horario = 0; horario < (count -1); horario++){        
        for(dia = 0; dia < count; dia++){
            if(gradeHorario[horario][dia].status == 0){
                resultado.horario = horario;
                resultado.dia = dia;
                return resultado;
            }                
        }
    }
    return resultado;
}



