#ifndef TABU_H
#define TABU_H

#include "solucao.hpp"
#include "tiposEstruturas.hpp"

class Tabu
{
public:
	Tabu();
	~Tabu();

	Tabu(Solucao s, valores_quebraDia_quebraTurma fo);

	Solucao getSolucao(); 
	valores_quebraDia_quebraTurma  getValorFO();
	
	void setSolucao(Solucao s);
	void setValorFO(valores_quebraDia_quebraTurma fo);
	
private:
	Solucao solucao;
	valores_quebraDia_quebraTurma valorFO;
	
};
#endif