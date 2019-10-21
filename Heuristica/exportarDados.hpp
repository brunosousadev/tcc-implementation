#ifndef exportarDadosH
#define exportarDadosH

#include "bloco.hpp"
#include "sala.hpp"
#include "turma.hpp"
#include "professor.hpp"
#include "operacoesUteis.hpp"


#include "tiposEstruturas.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class ExportarDados{
public:
	ExportarDados();
	~ExportarDados();	
	
	void converter_estrutura_para_salas(vector<Bloco*> blocos, vector<Sala*> salas , vector<Turma*> turmas, Dados resultado, int codigo_arquivo, int i, int j , int k, int qntProfessores);
	void exportarRelacaoProfessor_turma(Dados resultados, int codigo_arquivo, int i, int j, int k);
	
private:

	vector<associacaoSlotTurma> getTurmasSala(vector<associacaoSlotTurma> associacao_slot_turma, string codSalaPesquisada);
	int getIdSala(vector<Sala*> salas, string codSalaP);
	int getIdTurma(vector<Turma*> turmas, string componenteCurricularP);
	
	//###############################################################

	void exportarInformacoesAdicionais(valores_quebraDia_quebraTurma valorFOInicial, valores_quebraDia_quebraTurma valorFOFinal,float tempo_construcao_inicial, float tempo_total_de_solucao,int quantidade_vezes_melhorada, int codigo_arquivo, int i, int j , int k, int qntTurmas, int qntProfessores, int contadorRefinamento, int iteracao_encontrada, int possivel_quantidade_total_quebra_na_relacao_professor_turma, int possivel_quantidade_total_quebra_na_relacao_professor_dias, bool status);
	bool exportarBlocos(vector<Bloco*> blocos, int codigo_arquivo, int i, int j, int k);
	string exportarBloco(Bloco* b);	
	bool exportarSalas(vector<Sala*> salas, int i, int j, int k);
	string exportarSala(Sala* s);	
	string horario(int id);
	
};
#endif
