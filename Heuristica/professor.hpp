#ifndef PROFESSORH
#define PROFESSORH

#include "turma.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

class Professor
{
public:
	Professor();
	Professor(int si, string nomeP);
	Professor(int si, string nomeP, int cargH, vector<Turma*> turmas, vector<int> dias);
	Professor(int si, string nomeP, int cargH, vector<Turma*> turmas, vector<int> dias, vector<Turma*> turmasA);
	~Professor();
	
	int getSiape();
	int getCargHorariaTrabalho();
	int calcularQntTurmasDif_Familiaridade();
	int verificarContemDiaNosDiasPreferiveis(int dia);

	string getNome();

	vector<int> getDiasPreferiveisTrabalho();	
	vector<Turma*> getTurmasComFamiliaridade();	
	vector<Turma*> getTurmasAlocadas();
	
	void adicionarTurmaComFamiliaridade(Turma* turma);
	void adicionarDiaPreferivei(int dia);

	void addTurmaAlocada(Turma* turma);
	
	bool verificarCumprimentoTotalCargaHorariaTrabalho();
	void setCargHorariaTrabalho(int valor);
	void imprimir();
private:
	int siape;
	string nome;
	int cargHorariaTrabalho;
	vector<Turma*> turmasComFamiliaridade;
	vector<int> diasPreferiveisTrabalho;
	vector<Turma*> turmasAlocadas;	
	
	int verificarTurmaFamiliar(string componenteCurricular);
};
#endif
