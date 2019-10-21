#include "solucao.hpp"


Solucao::Solucao(){
 	
}
Solucao::~Solucao(){

}

Solucao::Solucao(vector<associacaoTurmaProfessor> novo_associacao_turma_professor, 
	vector<associacaoSlotTurma> novo_associacao_slot_turma,vector<associacaoTurmaSala> novo_associacao_turma_sala){

	associacao_turma_professor = novo_associacao_turma_professor;
	associacao_slot_turma = novo_associacao_slot_turma;
	associacao_turma_sala = novo_associacao_turma_sala;	
	iteracao_encontrada = 0;
	contadorRefinamento=0;
}


vector<associacaoTurmaProfessor> Solucao::getAssociacaoTurmaProfessor(){
	return associacao_turma_professor;
}
vector<associacaoSlotTurma> Solucao::getAssociacaoSlotTurma(){
	return associacao_slot_turma;
}
vector<associacaoTurmaSala> Solucao::getAssociacaoTurmaSala(){
	return associacao_turma_sala;
}

void Solucao::swap_entre_turmas_professores(turma_id origem, turma_id destino){		
	associacao_turma_professor[destino.idPosicao].componenteCurricular = origem.componenteCurricular;
	associacao_turma_professor[origem.idPosicao].componenteCurricular = destino.componenteCurricular;
}

void Solucao::swap_entre_professores_turma(turma_id origem, int novoSiape){	
	associacao_turma_professor[origem.idPosicao].siape  = novoSiape;
}

void Solucao::swap_entre_turmas(int index1, int index2){
	string componenteCurricular = associacao_turma_professor[index1].componenteCurricular;
	associacao_turma_professor[index1].componenteCurricular = associacao_turma_professor[index2].componenteCurricular;
	associacao_turma_professor[index2].componenteCurricular = componenteCurricular;
}

void Solucao::remover_relacao_turma_sala(int id){
	associacao_turma_sala.erase(associacao_turma_sala.begin()+ id);
}

void Solucao::adicionar_nova_relacao_turma_sala(string codSala, string componenteCurricular){
	associacao_turma_sala.push_back(associacaoTurmaSala(codSala, componenteCurricular));
}


void Solucao::atualizar_relacao_slot_turma(int indice, int dia, int horario, int id_dia_horario, string componenteCurricular, string codSala){
	associacao_slot_turma[indice] = associacaoSlotTurma(id_dia_horario,componenteCurricular,dia,horario, codSala);
}


void Solucao::setIteracaoEncontrada(int i){
	iteracao_encontrada = i;
}
int Solucao::getIteracaoEncontrada(){
	return iteracao_encontrada;
}


void Solucao::setContadorRefinamento(int c){
	contadorRefinamento = c;
}

int Solucao::getContadorRefinamento(){
	return contadorRefinamento;
}