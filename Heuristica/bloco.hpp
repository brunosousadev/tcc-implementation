#ifndef BLOCO_H
#define BLOCO_H

#include "sala.hpp"

#include <iostream>
#include <vector>

using namespace std;


class Bloco
{
public:
	Bloco();
	Bloco(int code, vector<Sala*> sala);
	Bloco(int code);
	~Bloco();
	vector<Sala*> getSalas();
	int getCodeBloco();
	void setCodeBloco(int code);
	void addSala(Sala* sala);
	int procurarSala(string codSala);
private:
		vector<Sala*> salas;
		int codeBloco;	
};
#endif

