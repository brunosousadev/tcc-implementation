#ifndef TURMA_H
#define TURMA_H

#include <iostream>
#include <string>


using namespace std;

enum  TipoTurma {OBRIGATORIA, OPTATIVA}; //OBRIGATORIA = 1; OPTATIVA=0
enum  CaracteristicaTurma{TEORICA, TEORICA_PRATICA, PRATICA};

class Turma
{
public: 
	Turma();
	~Turma();
	Turma(string nome);
	Turma(string componentC, string nome);

	Turma(string componentC, int creditoT, int creditoP, string nome, int tipoT);
	Turma(string componentC, int creditoT, int creditoP, string nome, int tipoT, int siape);
	Turma(string componentC, int creditoT, int creditoP, string nome, TipoTurma tipoT,int siapeP, int nAlocada);
	string getComponenteCurricular();
	int getCreditoTeorico();
	int getCreditoPratico();
	string getNomeTurma();
	TipoTurma getTipo();
	int getSiapeProfessor();
	int getAlocada();
	CaracteristicaTurma getCaracteristicaTurma();
	string getNomeCaracteristicaTurma();
	void setComponenteCurricular(string componente);
	void setCreditoTeorico(int creditoT);
	void setCreditoPratico(int creditoP);
	void setNomeTurma(string nome);
	void setTipo(TipoTurma tipoT);
	void setSiapeProfessor(int siape);
	void setAlocada(int valor);
	void imprimir();
	int getCargaHorariaTotal();	
private:

	void setCaracteristicaTurma(int teorica, int pratica);

	string componenteCurricular;
	int creditoTeorico;
	int creditoPratico;
	string nomeTurma;
	TipoTurma tipo;
	// Quando está -1 é porque não tem professor alocado para essa turma
	int siapeProfessor;
	// 1 alocado 0 não alocado
	int alocada;
		/*
	0 - TEORICA
	1 - TEORICA_PRATICA
	2 - PRATICA
	*/	
	CaracteristicaTurma caracteristica;	

};

#endif
