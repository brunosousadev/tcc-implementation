#ifndef PROFESSORDTO_H
#define PROFESSORDTO_H


using namespace std;

#include <iostream>


class ProfessorDTO
{
public:
	ProfessorDTO();
	~ProfessorDTO();
	ProfessorDTO(int nSiape, int nCargaHoraria);
	void imprimir();
	int getSiape();
	int getCargaHoraria();
private:
	int siape;
	int cargaHoraria;
};
#endif