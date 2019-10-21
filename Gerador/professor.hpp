#ifndef PROFESSORH
#define PROFESSORH

#include <iostream>
#include <string>
#include <vector>

#include "turma.hpp"
using namespace std;
class Professor
{
public:
	Professor();
	Professor(int code);
	~Professor();
	int getCodeProfessor();
	vector<int> getDiasPreferiveis();
	int getCargaHoraria();
	vector<Turma*> getTurmas();

	void setCodeProfessor(int code);
	void adicionarDiaPreferivel(int dia);
	void setCargaHoraria(int cargar);
	void adicionarTurma(Turma* novaTurma);
	


	
private:
	int codeProfessor;
	vector<int> diasPreferiveis;
	int cargaHoraria;
	vector<Turma*> turmas;
};

#endif