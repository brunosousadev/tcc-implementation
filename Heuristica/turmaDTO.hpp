#ifndef TURMADTO_H
#define TURMADTO_H

using namespace std;

#include <iostream>
#include <string>



class TurmaDTO
{
public:
	TurmaDTO();
	~TurmaDTO();
	TurmaDTO(int valor);
	TurmaDTO(string componente, int valor);	
	string getComponenteCurricular();
	int getCarga();		
	void imprimir();
private:
	string componenteCurricular;
	int carga;
};
#endif
