#ifndef SALA_H
#define SALA_H

#include "turma.hpp"
#include "tiposEstruturas.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
/*
struct Grade{ 
	int status; 
	Turma* turma; 
};

struct AuxTrocaTurmas{ 
	int horario, dia;
};
*/

class Sala
{
public:
	Sala();
	Sala(string cod, int tipo);
	Sala(string cod, int nTipo, int nQuantidadeDeTurmasAlocada, int nAlocadaBloco, Grade NgradeHorario[4][5]);
	~Sala();

	void setCodSala(string  cod);
	void setTipoSala(int tipo);
	void setAlocadaBloco(int value);
	void imprimirGradeHorario();
	void imprirSituacaoLacuna(int horario, int dia);

	int  getTipoSala(); 
	int getAlocadaBloco();
	int getQuantidadeDeTurmasAlocada();
	int verificarDisponibilidadeHorarioDia(int horario, int dia);
	int verificarSalaComportarTurma(int qntCreditos);	
	int getCapacidadeTotalDaGrade();

	bool trocarTurmasDeAlocacoes(string componenteCurricular1, string componenteCurricular2);
	bool alocarTurma(Turma *turma, int horario, int dia);
	bool removerTurma(int horario, int dia);
	bool verificarGradeCheia();


	string getNomeSala();
	string getCodSala();

	AuxTrocaTurmas procurarLacuna();
	AuxTrocaTurmas procurarLacunaDia(int dia);
		
	AuxTrocaTurmas procurarTurmaIJ(string componenteCurricular);
	AuxTrocaTurmas procurarTurma(string componenteCurricular);	
	Turma* getTurma(int horario, int dia);

	
	// 4 HORÁRIOS X 5 DIAS DA SEMANA 
	Grade gradeHorario[4][5];
	
		
	vector<int> diasDaTurmaAlocada(string componenteCurricular);	
	
	
	
private:
	string codSala;
	// SALA = 1 ; LABORATORIO = 0
	int tipoSala;
	int quantidadeDeTurmasAlocada;		
	int alocadaBloco;		
	int capacidadeTotalDaGrade = 20;
};
#endif
