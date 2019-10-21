#ifndef operacoesUteisH
#define operacoesUteisH

#include "solucao.hpp"
#include "sala.hpp"
#include "bloco.hpp"
#include "turma.hpp"
#include "professor.hpp"
#include "professorDTO.hpp"
#include "turmaDTO.hpp"
#include "turmaOrdenacaoAglutinado.hpp"
#include "exportarDados.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class OperacoesUteis
{
public:
	OperacoesUteis();
	~OperacoesUteis();
	int quantidade_possivel_quebra_professor_turma(vector<Professor*> professores);
	int quantidade_possivel_quebra_professor_dias(vector<Professor*> professores);

	vector<int> get_id_dia_horario_componenteCurricular2(vector<associacaoSlotTurma> alocacao_slot_turma, string codSala);
	int verificar_lacuna_na_sala2(string codigoSala, int id_dia_horario_aux , vector<associacaoSlotTurma> alocar_slot_turma);
	Solucao construcao_inicial_aleatoria(vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas,bool ordenado, bool ordenado_crescente_ou_decrescente);
	
	map<int, vector<Turma*>> get_turmas_preferiveis_por_professor(vector<Professor*> professores);
	

	vector<associacaoSlotTurma_indice> get_associacao_turma_id_horario(int siape, vector<Professor*> professores, vector<string> componentesCurriulares, vector<associacaoSlotTurma> alocacao_slot_turma);
	
	map<int, vector<associacaoSlotTurma_indice>> get_professores_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma);
	

	_2IndexDiferente gerarIndexDiferentes(int maximo);

	void popular_matriz_mapeamento();

	vector<associacaoTurmaProfessor> alocar_turma_professor_ordenado_crescente_ou_decrescente(vector<Professor*> professores,vector<Turma*> turmas, bool flag);
	
	vector<AuxTrocaTurmas> converter_id_dia_horario_em_dia_horario(vector<int> valores);

	//[ TESTANDO ]
	vector<int> verificar_professor_cumprir_carga_trabalho(vector<Turma*> turmas, vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	map<int, vector<string>> get_professres_com_turmas_fora_das_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	map<string,int>  get_turmas_nao_alocadas_professor(vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<Turma*> turmas);
	map<int, vector<string>> get_turmas_pro_professor(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	vector<troca_dia_horario> get_id_dia_horario(vector<string> componenteCurriculares, vector<associacaoSlotTurma> alocacao_slot_turma);	
	vector<string> get_turmas_professor(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	vector<AuxTrocaTurmas> diferenca_com_matriz(vector<AuxTrocaTurmas> estaMatriz);
	Solucao copiar_solucao(Solucao s);
	
	//Métodos para serem utilizados na vizinhança
	map<int, vector<turma_id>> get_professores_com_turmas_fora_das_preferiveis_com_posicao_no_vetor_de_relacoes(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);	
	vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor> get_turmas_nas_salas(vector<string> componenteCurriculares, vector<associacaoTurmaSala> associacao_turma_sala);
	map<int, vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot>> get_professores_com_turmas_alocadas_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma, vector<associacaoTurmaSala> associacao_turma_sala);	

	int gerar_numero_aleatorio(int menor, int maior);
	vector<int> get_id_dia_horario_componenteCurricular(vector<associacaoSlotTurma> alocacao_slot_turma, vector<string> componenteCurriculares);

	vector<string>  get_componenteCurricular_turmas_sala_id(vector<associacaoTurmaSala>* alocacao_turma_sala, string codigo);
	vector<string>  get_componenteCurricular_turmas_sala_id_2(vector<associacaoTurmaSala> alocacao_turma_sala, string codigo);
	int getNumeroMatrizMapeamento(int horario, int dia);
	int verificar_relacao_diaHorario(int dia_horario, vector<int> dia_horario_sala);
	AuxTrocaTurmas converter_id_dia_horario_em_dia_horario_aux(int valores);
	vector<turma_id> get_turmas_professor_com_posicao_no_vetor_de_relacoes_aux(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor);
	map<int, vector<turma_id>> get_turmas_professor_com_posicao_no_vetor_de_relacoes(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor);
private:	
	

	AuxTrocaTurmas diferenca_com_matriz_aux(int dia, int horario, vector<AuxTrocaTurmas> estaMatriz);
	//Métodos para serem utilizados na vizinhança
	
	
	vector<turma_id>  get_diferenca_turmas_preferiveis_alocadas_com_posicao_no_vetor_de_relacoes(vector<Turma*> turmas, vector<turma_id>   alocadas_para_professor);

	void troca_turma_de_sala(string codigsalaAntiga, string componenteCurricular, vector<associacaoTurmaSala>* alocacao_turma_sala, vector<Sala*> salas);
	void ordenar_associacao_turma_sala(vector<associacaoTurmaSala> *associar_turma_sala);
	void alocar_turma_sala_aux(vector<associacaoTurmaSala>  *alocar_turma_sala, int quantidadeTurmas, string componenteCurricular, vector<Sala*> salas, bool flag);
	
	void alocar_turmas_nao_alocadas(vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma>* alocar_slot_turma, vector<associacaoTurmaSala> turmas_nao_alocadas, vector<Sala*> salas);

	int getIdSalaGerado(int minimo, int maximo, bool flag, vector<Sala*> salas);
	int verificar_turmaDTO(vector<TurmaOrdenacaoAglutinado> turmaOrdenacaoAglutinado, int valor);
	
	int verificar_lacuna_na_sala( vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma> alocar_slot_turma, string codigoSala, int id_dia_horario_aux);
	int verificar_relacao(vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma> alocar_slot_turma, string codigoSala, int id_dia_horario_aux);
	
	int calcular_valor_carga_horaria(map<string, int> turma_carga_horaria_total, vector<string> componenteCurricular);
	int procura_lacuna_na_grade_horario_da_sala(vector<int>  id_dias_horarios);

	
	vector<int> get_dias_preferiveis_professor(int siape, vector<Professor*> professores);
	
	
	vector<string> get_diferenca_turmas_preferiveis_alocadas(vector<Turma*> turmas, vector<string> componenteCurricular);
	
	vector<TurmaOrdenacaoAglutinado> converter_turmaDTO_em_turmaOrdenacaoAglutinado(vector<TurmaDTO> turmasTDO);
	vector<TurmaOrdenacaoAglutinado> converter_ordenar_turmas(vector<Turma*> turmas);
	vector<associacaoTurmaProfessor> copiar_associacao_turma_professor(vector<associacaoTurmaProfessor> associacao_turma_professor);
	vector<associacaoTurmaSala> copiar_associacao_turma_sala(vector<associacaoTurmaSala> associacao_turma_sala);		
	vector<associacaoSlotTurma> copiar_associacao_slot_turma(vector<associacaoSlotTurma> associacao_slot_turma);
	
	vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot> get_slot_das_turmas_do_professor_que_esta_fora_do_seu_dias_preferiveis(vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor> turma_sala_posicao, vector<int> diaspreferiveisDoProfessor, vector<associacaoSlotTurma> alocacao_slot_turma);

	vector<ProfessorDTO> converter_professor_professorDTO(vector<Professor*> professores);
	vector<ProfessorDTO> ordenar_professorDTO_crescente_ou_decrescente(vector<Professor*> professores, bool flag);
	vector<TurmaDTO> converter_turma_turmaDTO(vector<Turma*> turmas);

	map<int, vector<Turma*>> get_turma_preferiveis_por_professor(vector<Professor*> professores);
	
	map<string, int> get_carga_horaria_total_turmas(vector<Turma*> turmas);
	

	// [FUNCIONANDO]
	vector<associacaoTurmaProfessor> alocar_turma_professor_nao_ordenado(vector<Professor*> professores,vector<Turma*> turmas);		
	// [FUNCIONANDO]
	
	// [FUNCIONANDO]
	vector<associacaoTurmaSala> alocar_turma_sala(vector<Sala*> salas, vector<Turma*> turmas);
	// [FUNCIONANDO]
	vector<associacaoSlotTurma> alocar_slot_turma(vector<Turma*> turmas, vector<associacaoTurmaSala>* alocacao_turma_sala, vector<Sala*> salas);
	
	static bool ordenacao_turmasDTO(TurmaDTO& turma1, TurmaDTO& turma2);
	static bool ordencao_salas_turmas(associacaoTurmaSala& a, associacaoTurmaSala& b);
	static bool ordenar_professores_crescente(ProfessorDTO& professor1, ProfessorDTO& professor2);
	static bool ordenar_professores_decrescente(ProfessorDTO& professor1, ProfessorDTO& professor2);

	bool verificar_alocacao_turma(string componenteCurricular,vector<associacaoTurmaProfessor> alocacao_turma_professor);	


	troca_dia_horario  get_dia_horario(int id_dia_horario);
	// 4 HORÁRIOS X 5 DIAS DA SEMANA
	int matrizMapeamento[4][5];
};
#endif