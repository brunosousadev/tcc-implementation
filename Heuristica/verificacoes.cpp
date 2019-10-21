#include "verificacoes.hpp"


Verificacoes::Verificacoes(){

}

Verificacoes::~Verificacoes(){

}

vector<string> Verificacoes::get_turmas_professor(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor){
	vector<string> resultado;
	for(auto& turma_professor : alocacao_turma_professor){
		if(turma_professor.siape == siape)
			resultado.push_back(turma_professor.componenteCurricular);
	}
	return resultado;
}

map<int, vector<string>> Verificacoes::get_turmas_pro_professor(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
	map<int, vector<string>> resultado;
	int siape;
	for(auto& pro: professores){
		siape =pro->getSiape();
		resultado.insert(pair<int, vector<string>>(siape,get_turmas_professor(siape,alocacao_turma_professor)));
	}
	return resultado;
}

/*
	Se estiver dentro do conjunto vai retornar 1
	caso contrario 0
*/
int Verificacoes::verificar_pertence_conjunto(vector<int> dias , int dia){
	for(auto& d: dias){
		if(d == dia)  return 1;
	}

	return 0;
}

vector<int> Verificacoes::getDiasPreferiveis(vector<Professor*> professores, int siape){
	vector<int> vazio;
	for(auto& p : professores){
		if(p->getSiape() == siape)
			return p->getDiasPreferiveisTrabalho();
	}
	return vazio;
}

vector<associacaoSlotTurma_indice> Verificacoes::get_associacao_turma_id_horario(int siape, vector<Professor*> professores, vector<string> componentesCurriulares, vector<associacaoSlotTurma> alocacao_slot_turma){
	vector<associacaoSlotTurma_indice> resultado;
	int dia_horario;
	
	vector<int> dias = getDiasPreferiveis(professores, siape);

	int tamanho  = alocacao_slot_turma.size();
	for (int i = 0; i < tamanho; i++){
		dia_horario = alocacao_slot_turma[i].dia;			

		if(verificar_pertence_conjunto(dias, dia_horario)== 0){
			resultado.push_back(associacaoSlotTurma_indice(alocacao_slot_turma[i],i));					
		}		
	}
	return resultado;
}
map<int, vector<associacaoSlotTurma_indice>> Verificacoes::get_professores_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma){
	map<int, vector<associacaoSlotTurma_indice>> resultado;
	map<int, vector<string>> turmas_professores =  get_turmas_pro_professor(professores, alocacao_turma_professor);
	vector<associacaoSlotTurma_indice> aux;

	for (map<int, vector<string>>::iterator i = turmas_professores.begin(); i != turmas_professores.end(); ++i){
		aux = get_associacao_turma_id_horario(i->first,professores,i->second,alocacao_slot_turma);
		if(aux.size() > 0){
				resultado.insert(pair<int,vector<associacaoSlotTurma_indice>>(i->first,aux));
			}
	}

	return resultado;
}
