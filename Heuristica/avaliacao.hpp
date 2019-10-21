#ifndef avaliacaoH
#define avaliacaoH

#include <vector>
#include <iostream>


#include "professor.hpp"
#include "turma.hpp"
#include "tiposEstruturas.hpp"
#include "operacoesUteis.hpp"
using namespace std;

class Avaliacao
{
public:
	Avaliacao();
	~Avaliacao();
	valores_quebraDia_quebraTurma  calcularFO(vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma, vector<Professor*> professores);
	bool verificar_todo_professor_cumpriu_carga_horaria(vector<Turma*> turmas, vector<Professor*> professores, vector<associacaoTurmaProfessor> associacao_turma_professor);
private:

	unsigned int calcular_penalidade_professor_turma(vector<Professor*> professores, map<int, vector<string>> resultado);
	unsigned int calcular_penalidade_professor_dia(vector<Professor*> professores,map<int, vector<string>> resultado, vector<associacaoSlotTurma> alocacao_slot_turma);
	int get_quantidade_diferenca_dias_alocadas_dias_preferiveis(vector<int> dias_preferiveis,vector<troca_dia_horario> dias_alocados);
	int get_quantidade_diferenca_turmas_alocadas_turmas_preferiveis(vector<string> componenteCurricularesAux, vector<Turma*> turmas);

	OperacoesUteis * operacoesUteis;
	
	/*
		Estão com mesmo valor do modelo matemático!
	*/

	int alfa = 1;
	int beta = 1;


	

};
#endif