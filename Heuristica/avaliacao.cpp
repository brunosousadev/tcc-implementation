#include "avaliacao.hpp"


Avaliacao::Avaliacao(){

}

Avaliacao::~Avaliacao(){
	delete(operacoesUteis);
}


bool Avaliacao::verificar_todo_professor_cumpriu_carga_horaria(vector<Turma*> turmas, vector<Professor*> professores, vector<associacaoTurmaProfessor> associacao_turma_professor){
	vector<int> result  = operacoesUteis->verificar_professor_cumprir_carga_trabalho(turmas, professores,associacao_turma_professor);

	if(result.size() > 0)
		return false;
	else return true;

}
valores_quebraDia_quebraTurma Avaliacao::calcularFO(vector<associacaoTurmaProfessor> alocacao_turma_professor,vector<associacaoSlotTurma> alocacao_slot_turma,vector<Professor*> professores){
	operacoesUteis = new OperacoesUteis();

	map<int, vector<string>> turmas_professor = operacoesUteis->get_turmas_pro_professor(professores, alocacao_turma_professor);
	
	unsigned int penalidade_professor_turma  = calcular_penalidade_professor_turma(professores, turmas_professor);
	
	unsigned int penalidade_professor_dia  = calcular_penalidade_professor_dia(professores, turmas_professor, alocacao_slot_turma);	

	delete(operacoesUteis);

	return valores_quebraDia_quebraTurma(penalidade_professor_turma, penalidade_professor_dia);
}


unsigned int Avaliacao::calcular_penalidade_professor_turma(vector<Professor*> professores, map<int, vector<string>> resultado){
		unsigned int acumulador = 0;
		for(auto& pro: professores){
			acumulador+=get_quantidade_diferenca_turmas_alocadas_turmas_preferiveis(resultado.find(pro->getSiape())->second,pro->getTurmasComFamiliaridade());
		}				
		return (acumulador*beta);
}

unsigned int Avaliacao::calcular_penalidade_professor_dia(vector<Professor*> professores, map<int, vector<string>> turmas_professores, vector<associacaoSlotTurma> alocacao_slot_turma){
	unsigned int acumulador = 0;	
	vector<associacaoSlotTurma_indice> aux;
	for (map<int, vector<string>>::iterator i = turmas_professores.begin(); i != turmas_professores.end(); ++i){
		aux = operacoesUteis->get_associacao_turma_id_horario(i->first,professores,i->second,alocacao_slot_turma);					
			acumulador+= aux.size();		
	}
	return (acumulador*alfa);
}


int Avaliacao::get_quantidade_diferenca_dias_alocadas_dias_preferiveis(vector<int> dias_preferiveis, vector<troca_dia_horario> dias_alocados){
	int total = 0;	
	int qntDiasAlocados = dias_alocados.size();
	int qntDiasPreferiveis  = dias_preferiveis.size();
	troca_dia_horario dia_horario;
	bool flag;
	for(int d = 0 ; d< qntDiasAlocados; d++){
		dia_horario  = dias_alocados[d];
		flag = true;
		for (int dp = 0; dp < qntDiasPreferiveis; ++dp){
			if(dia_horario.dia == dias_preferiveis[dp]){
				flag = false;
				break;
			}
		}		
		if(flag){
			total++;
		}
	}
	return total;
}

int Avaliacao::get_quantidade_diferenca_turmas_alocadas_turmas_preferiveis(vector<string> componenteCurricularesAux, vector<Turma*> turmas){
	int qntComponenteCurriculares = componenteCurricularesAux.size();
	int total = 0;	
	bool flag;
	for (int i = 0; i < qntComponenteCurriculares; ++i){		
		flag = true;
		for(auto& turma: turmas){
			if(turma->getComponenteCurricular() == componenteCurricularesAux[i]){
				flag = false;
				break;
			}
		}		
		if(flag){
			total++;
		}
	}
	return total;
}
