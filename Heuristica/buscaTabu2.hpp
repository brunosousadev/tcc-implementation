#ifndef BUSCATABU2_H
#define BUSCATABU2_H

#include "tiposEstruturas.hpp"
#include "avaliacao.hpp"
#include "operacoesUteis.hpp"

#include "tabu.hpp"

#include "professor.hpp"
#include "turma.hpp"
#include "sala.hpp"
#include "solucao.hpp"
#include <vector>



using namespace std;

class BuscaTabu2
{
public:
	BuscaTabu2();
	~BuscaTabu2();
	BuscaTabu2(int  maximoIteracoes, int maximoIteracoesSemMelhora, int tamanhoFilaTabu);
	Dados executar(vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas);


	void gerarMelhorVizinho(Solucao* solucao,valores_quebraDia_quebraTurma valhorSolucaoAtual, vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas);

private:
	void vizinhanca_professor_turma2(Solucao* solucao, vector<Professor*> professores);
	turma_id verificar_compatibilidade_entre_listas_indesejadas2(vector<turma_id> turmas_nao_desejadas_professor2, vector<Turma*> turmas_desejadas_professor1);
	Tabu procurar_melhor_solucao(Solucao solucao, valores_quebraDia_quebraTurma valorMelhorSolucao);

	void imprimir2(vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala);
	void imprimir(vector<int> id_dia_horario_sala_livre);
	void procurara_nova_sala(vector<int> diasDesejados, associacaoSlotTurma_indice turma_id, Solucao* solucao, string codSala, vector<Sala*> salas);
	int verificar_se_pertence(int  id_dia_horario, vector<int> id_dia_horario_sala);
	vector<int> encontrar_lacunas_na_matriz(vector<int> id_dias_horarios_sala);	

	vector<int> get_id_dia_horario_dentro_de_uma_sala(vector<associacaoSlotTurma> alocacao_turma_slot, string codSalaPesquisada);
	AuxTrocaTurmas comparar_vetor_lacuna_dias_desejados(vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala, vector<int> diasDesejados);
	int getIdSaladaTurma2(vector<associacaoTurmaSala> associacao_turma_sala, string componente);
	int getIdSaladaTurma(vector<associacaoTurmaSala> associacao_turma_sala, string componente, string codSala);
	Professor* getProfessorSiape(vector<Professor*> professores, int siape);
	void criarTabu(Solucao solucao, valores_quebraDia_quebraTurma valhorSolucaol);
	turma_id verificar_compatibilidade_entre_listas_indesejadas(vector<turma_id> turmas_nao_desejadas_professor2, vector<Turma*> turmas_desejadas_professor1);
	Professor* getProfessor(vector<Professor*> professores, string componente);
	
	void vizinhanca_professor_turma(Solucao* solucao, vector<Professor*> professores);

	void vizinhanca_professor_dia(Solucao* solucao, vector<Professor*> professores, vector<Sala*> salas);
	
	bool  verificar_professor_na_lista_dos__com_turmas_indesejadas(map<int, vector<turma_id>> professores_turmas_nao_desejadas, int siape);
	
	vector<Turma*> getTurmasComFamiliaridadeProfessor(vector<Professor*> professores, int siape);
	
	Avaliacao* avaliacao;
	OperacoesUteis* operacoesUteis;	
	//Número de interações que forneceu a melhor solução até o momento
	int melhorIteracao;
	// Número máximo de iterações permitidas
    int maxIteracoes;
    // Número máximo de iterações permitidas sem que haja melhora da solução
    int maxIteracoesSemMelhora;
    // Valor da melhor solução
    unsigned int valorMelhorSolucao;
    // Indica quantas melhoras foram obtidas
    int contadorMelhoras;
    // Contador de iterações
    int contadorIteracoes;
    // Tamanho máximo da Fila Tabu
    int tamanhoMaxFila;
    // Quantas vezes consegui refinar.
    int contadorRefinamento;

	vector<Tabu> filaTabu;
	
};
#endif