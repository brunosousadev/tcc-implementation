#ifndef TURMAH
#define TURMAH

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Turma
{
public:
	Turma();
	~Turma();
	int getCodeTurma();
	int getCargarHorariaTeorica();
	int getCargarHorariaPratica();

	void setCodeTurma(int code);
	void setCargarHorariaTeorica(int cargarT);
	void setCargarHorariaPratica(int cargarP);

private:
	int codeTurma;
	int cargarHorariaTeorica;
	int cargarHorariaPratica;
};
#endif