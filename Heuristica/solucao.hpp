#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "tiposEstruturas.hpp"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solucao
{
public:
	Solucao();
	~Solucao();
	Solucao(vector<associacaoTurmaProfessor> novo_associacao_turma_professor, vector<associacaoSlotTurma> novo_associacao_slot_turma,vector<associacaoTurmaSala> novo_associacao_turma_sala);
	void setIteracaoEncontrada(int i);
	int getIteracaoEncontrada();

	void setContadorRefinamento(int c);
	int getContadorRefinamento();
	vector<associacaoTurmaProfessor> getAssociacaoTurmaProfessor();

	vector<associacaoSlotTurma>  getAssociacaoSlotTurma();
	vector<associacaoTurmaSala> getAssociacaoTurmaSala();

	void swap_entre_professores_turma(turma_id origem, int novoSiape);
	void swap_entre_turmas_professores(turma_id origem, turma_id destino);
	void swap_entre_turmas(int index1, int index2);
	void remover_relacao_turma_sala(int id);
	void adicionar_nova_relacao_turma_sala(string codSala, string componenteCurricular);
	void atualizar_relacao_slot_turma(int indice, int dia, int horario, int id_dia_horario, string componenteCurricular,  string codSala);	
private:		
	vector<associacaoTurmaProfessor> associacao_turma_professor;
	vector<associacaoSlotTurma> associacao_slot_turma;
	vector<associacaoTurmaSala> associacao_turma_sala;	
	int iteracao_encontrada;

	int contadorRefinamento;
	
};
#endif


