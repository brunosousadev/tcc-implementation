#ifndef TIPOESTRUTURAS_H
#define TIPOESTRUTURAS_H

#include "turma.hpp"


#include <string>
using std::string;

#include <vector>
using std::vector;


struct associacaoTurmaProfessor{
	string componenteCurricular;
	int siape;
	associacaoTurmaProfessor(string componente, int valor){
		this->componenteCurricular = componente;
		this->siape = valor;
	}
	associacaoTurmaProfessor(){

	}
};


struct associacaoSlotTurma{	
	string codSala;
	int id_dia_horario;
	int dia, horario;
	string componenteCurricular;
	associacaoSlotTurma(){

	}
	associacaoSlotTurma(int dia_horario, string componente, int dia, int horario, string codSala){
			this->id_dia_horario = dia_horario;
			this->componenteCurricular = componente;
			this->dia = dia;
			this->horario = horario;
			this->codSala = codSala;
	}
};

struct associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot
{
	int posicao_no_vetor_de_relacao_turma_sala;
	int id_dia_horario;
	int dia, horario;
	string componenteCurricular;
	int posicao_no_vetor_de_relacao_turma_slot;

	associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot(){

	}

	associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot(int posicao_no_vetor_de_relacao_turma_sala,int id_dia_horario,int dia, int horario,string componenteCurricular,int posicao_no_vetor_de_relacao_turma_slot){
		this->posicao_no_vetor_de_relacao_turma_sala = posicao_no_vetor_de_relacao_turma_sala;
		this->id_dia_horario = id_dia_horario;
		this->dia = dia;
		this->horario = horario;
		this->componenteCurricular = componenteCurricular;
		this->posicao_no_vetor_de_relacao_turma_slot = posicao_no_vetor_de_relacao_turma_slot;
	}

};

struct associacaoTurmaSala_com_posicao_no_respectivo_vetor{
	string codSala;
	string componenteCurricular;		
	int posicao_no_vetor_de_relacao_turma_sala;
	associacaoTurmaSala_com_posicao_no_respectivo_vetor(){}

	associacaoTurmaSala_com_posicao_no_respectivo_vetor(string codSala, string componenteCurricular, int posicao_no_vetor_de_relacao_turma_sala){
		this->codSala = codSala;
		this->componenteCurricular = componenteCurricular;
		this->posicao_no_vetor_de_relacao_turma_sala = posicao_no_vetor_de_relacao_turma_sala;
	}
};

struct associacaoTurmaSala{
	string codSala;
	string componenteCurricular;		
	associacaoTurmaSala(){

	}
	associacaoTurmaSala(string sala, string componente){
		this->codSala = sala;
		this->componenteCurricular = componente;
	}
	
};

struct troca_dia_horario
{
	int id_dia_horario;
	int dia, horario;
	troca_dia_horario(){

	}
	troca_dia_horario(int id_dia_horario, int dia, int horario){
		this->id_dia_horario = id_dia_horario;
		this->dia = dia;
		this->horario = horario;
	}
};

struct valores_quebraDia_quebraTurma
{
	unsigned int relacaoProfessorTurma;
	unsigned int relacaoProfessorDia;	
	
	valores_quebraDia_quebraTurma(){
		
	}
	valores_quebraDia_quebraTurma(unsigned int relacaoProfessorTurma,unsigned int relacaoProfessorDia){
		this->relacaoProfessorTurma = relacaoProfessorTurma;
		this->relacaoProfessorDia = relacaoProfessorDia;
	}	
};



struct AuxTrocaTurmas{ 
	int horario, dia;
	AuxTrocaTurmas(){

	}
	AuxTrocaTurmas(int dia, int horario){
		this->dia = dia;
		this->horario = horario;
	}
};

struct Grade{ 
	int status; 
	Turma* turma; 
};

struct associacaoSlotTurma_indice
{
	associacaoSlotTurma  valor;
	int indice;
	associacaoSlotTurma_indice(){

	}
	associacaoSlotTurma_indice(associacaoSlotTurma  valor, int  id){
		this->valor = valor;
		this->indice = id;
	}
};


struct associacao_slot_turma_indice_com_turma_sala_indice
{	
	associacaoSlotTurma_indice slot_turma_indice;
	int posicao_turma_sala;
	associacao_slot_turma_indice_com_turma_sala_indice(){

	}

	associacao_slot_turma_indice_com_turma_sala_indice(associacaoSlotTurma_indice slot_turma_indice, int posicao_turma_sala){
		this->slot_turma_indice = slot_turma_indice;
		this->posicao_turma_sala = posicao_turma_sala;
	}
};




struct Dados
{
	//Solução e representada pelos 3 vetores ai embaixo
	vector<associacaoTurmaProfessor> associacao_turma_professor;
	vector<associacaoSlotTurma> associacao_slot_turma;
	vector<associacaoTurmaSala> associacao_turma_sala;	

	valores_quebraDia_quebraTurma valorFOFinal;
	valores_quebraDia_quebraTurma valorFOConstrucao;
	
	float tempo_construcao_inicial;
	int quantidade_vezes_melhorada;
	
	float tempo_total_de_solucao;
	bool status_da_solucao;
	// QUANTIAS VEZES EU REFINEI 
	int contadorRefinamento;
	// QUAL ITERAÇÃO ENCONTREI 
	int iteracao_encontrada;
	
	int possivel_quantidade_total_quebra_na_relacao_professor_turma;
	int possivel_quantidade_total_quebra_na_relacao_professor_dias;

	Dados(){
	
	}	
	Dados(valores_quebraDia_quebraTurma valorFOFinal, valores_quebraDia_quebraTurma valorFOConstrucao, float tempo_construcao_inicial, int quantidade_vezes_melhorada){
		

		this->valorFOFinal = valorFOFinal;
		this->valorFOConstrucao = valorFOConstrucao;
		this->tempo_construcao_inicial = tempo_construcao_inicial;
		this->quantidade_vezes_melhorada = quantidade_vezes_melhorada;
	}		
};

struct turma_id{
	int idPosicao;
	string componenteCurricular;
	turma_id(){

	}
	turma_id(int idPosicao, string componenteCurricular){
		this->idPosicao = idPosicao;
		this->componenteCurricular = componenteCurricular;
	}
};
struct _2IndexDiferente
{
	int index1, index2;
	_2IndexDiferente(){

	}

	_2IndexDiferente(int index1, int index2){
		this->index1 = index1;
		this->index2 = index2;
	}
};

#endif

/*
https://stackoverflow.com/questions/1127396/struct-constructor-in-c
*/