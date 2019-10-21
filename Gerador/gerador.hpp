#ifndef GERADORH
#define GERADORH

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "turma.hpp"
#include "professor.hpp"

using namespace std;

struct qntProfessorXPerfil{
	int quantidade;
	int perfil;
};
class Gerador
{
public:
	void executar(int cenarioSlots, int idArquivo,int novoQuantidadeProfessores, vector<int> novoPorcentagemPerfilProfessor, int novoQuantidadeSalas, int novoAnoPegarFeriado);
	Gerador();
	/*
	porcentagemPerfilProfessor sempre vai ter a porcentagem dos perfil seguindo a ordem crescente
			
		Exemplo:  		10%			20 %   ... até completar 100%
					2 Creditos | 4 Creditos ... 
	*/	
	~Gerador();


	string getSemana(); 
	string getSlotsHorario(); 
	string getSlotsHorarioManha(); 
	string getSlotsHorarioTarde(); 
	string getMarcador(int op); 
	string getCodSalas(int quantidade); 
	void   gerarQuantidadeTurmasProfessor(int quantidadeCreditoProfessor,int quantidadesTiposCreditos, int *tiposCreditos, int *rastreio);	

	vector<qntProfessorXPerfil> calcularQuantidadeProfessorPorPerfil(); 
	vector<Turma*> getTurmas();
	vector<Professor*>  getProfessores();

private:
	vector<qntProfessorXPerfil>  verificarQuantidadeProfessor(vector<qntProfessorXPerfil> quantidadeProfessorPorPerfil);
	int procurarPosicaoPerfilZerado(vector<qntProfessorXPerfil> quantidadeProfessorPorPerfil);

	int    gerarNumeroAleatorio(int min, int max);
	string transfomarVectorString(vector<int> valores);
	void   gravarArquivo(int cenarioSlots,int idArquivo);
	void   gravarAquivosHeuristica();
	string linhaCodigosProfessor();
	string linhaCodigoTurma();
	string linhasAssociandoProfessorTurmas();
	string gerarDiasPreferiveisProfessores();
	string linhasAssociandoProfessorCargaHoraria();

	int quantidadeProfessores;
	vector<int> porcentagemPerfilProfessor;
	int quantidadeSalas;
	int anoPegarFeriado;
	vector<Turma*> turmas;
	vector<Professor*> professores;
	vector<qntProfessorXPerfil> quantidadeProfessoresPorPerfil;

};
#endif