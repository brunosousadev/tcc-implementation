/*
Nestá classe vou ter que implementar as operações utilizadas no métodos de vizinhanças para 
ficar mais legivel

*/
#ifndef VERIFICACOES_H
#define VERIFICACOES_H

#include "tiposEstruturas.hpp"
#include "professor.hpp"

#include <map>
#include<vector>


using namespace std;


class Verificacoes
{
public:
	Verificacoes();
	~Verificacoes();

	vector<string> get_turmas_professor(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	map<int, vector<string>> get_turmas_pro_professor(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	vector<int> getDiasPreferiveis(vector<Professor*> professores, int siape);
	vector<associacaoSlotTurma_indice> get_associacao_turma_id_horario(int siape, vector<Professor*> professores, vector<string> componentesCurriulares, vector<associacaoSlotTurma> alocacao_slot_turma);
	map<int, vector<associacaoSlotTurma_indice>> get_professores_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma);
	int verificar_pertence_conjunto(vector<int> dias , int dia);
};
#endif