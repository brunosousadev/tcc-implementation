#ifndef importarDadosH
#define importarDadosH

#include "bloco.hpp"
#include "professor.hpp"
#include "informacoesAdicionais.hpp"
#include "turma.hpp"
#include "sala.hpp"

#include <stdlib.h>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cfloat>
#include <cstdlib>
#include <math.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;


class ImportarDados
{
public:
	ImportarDados();
	~ImportarDados();	
	bool executar(int id_file);
	

	vector<Bloco*> 			getBlocos();
	vector<Professor*> 		getProfessores();
	vector<Turma*> 			getTurmas();
	InformacoesAdicionais 	getInformacoesAdicionais();
	vector<Sala*>			getSalas();

private:

	char* formatarDado(const char *separator, string line);
	Turma* getTurma(string componente);

	bool verificarLinha(string markupCharacter, string linha);
	string removerMarcador(string linha);
	
	vector<string> tokenizacaoString(string linha,bool op);
	vector<Sala*> getSalasBloco(vector<string> codigos);
	
	bool carregarBlocos();
	void adicionarTurmasProfessor(int siape, Turma* turma);
	void adicionarDiasPrefeirveisProfessor(int siape, int dia);
	void adicionarCargaHorariaProfessor(int siape, int horaTrabalho);
	
	int getIdSala(string codigo);

	
	int getCodigo(string linha, const char* separator);
	
	vector<Bloco*> 			blocos;  
	vector<Professor*> 		professores; 
	vector<Turma*> 			turmas;
	InformacoesAdicionais 	informacoesAdicionais;
	vector<Sala*> 			salas;
   
    string line,EMPTY="",firstStopMarker="-",secondStopMarker="*",thirdStopMarker=">";
};
#endif

