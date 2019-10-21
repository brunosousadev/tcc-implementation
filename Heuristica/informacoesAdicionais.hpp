#ifndef informacoesAdicionaisH
#define informacoesAdicionaisH

#include <iostream>
#include <vector>

using namespace std;

class InformacoesAdicionais
{
public:
	InformacoesAdicionais();
	~InformacoesAdicionais();
	
	vector<int> getDiasSemana();
	vector<int> getSlotsHorarios();
	vector<int> getDiasSemanaComMuitoFeriado();

	void addDiaSemana(int dia);
	void addSlotHorario(int horario);
	void addDiaSemanaComMuitoFeriado(int diaF);

private:
	vector<int> slotsHorarios;
	vector<int> diasSemana;
 	vector<int> diasDaSemanaComMuitoFeriado;
};
#endif