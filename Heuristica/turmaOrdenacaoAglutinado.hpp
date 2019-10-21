#ifndef TurmaOrdenacaoAglutinado_H
#define TurmaOrdenacaoAglutinado_H

#include "turmaDTO.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class TurmaOrdenacaoAglutinado
{
public:
	TurmaOrdenacaoAglutinado();
	~TurmaOrdenacaoAglutinado();
	TurmaOrdenacaoAglutinado(int nValor, TurmaDTO turma);
	vector<TurmaDTO> getTurmasDTOs();
	int getQuantidade();
	int getValor();
	
	void imprimir1();
	void imprimir2();

	void setTurmasDTOs(vector<TurmaDTO> turmas);
	void adicionarTurmaDTO(TurmaDTO turma);
	void setQuantidade(int nQuantidade);
	void setValor(int nValor);	
	void setQuantidadeMenor(int menos);	
	TurmaDTO getTurmaDTO(int id);	
private:
	vector<TurmaDTO> turmasDTOs;
	int quantidade;
	int valor;
};
#endif