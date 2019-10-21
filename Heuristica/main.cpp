#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <ctime>
#include <time.h> 
#include <string>
#include <fstream>
#include <cstdlib>

#include "importarDados.hpp"
#include "professorDTO.hpp"
#include "solucao.hpp"
#include "tiposEstruturas.hpp"
#include "operacoesUteis.hpp"
#include "turmaDTO.hpp"
#include "avaliacao.hpp"
#include "buscaTabu2.hpp"
#include "exportarDados.hpp"

using namespace std;

int main(int argc, char const *argv[]){


	if(argc < 4){
		cout<<"[ ATENÇÃO ] FALTA ARGUMENTOS\n";
		return 0;
	}

	srand((unsigned)time(0)); 
		
	ImportarDados* importarDados;
	ExportarDados* exportarDados;
	BuscaTabu2 * buscaTabu2;
	OperacoesUteis* operacoesUteis;
	clock_t tempoConstrucaoFinal;
	int qntProfessores;
	
		importarDados =  new ImportarDados();			
		if(importarDados->executar(atoi(argv[1]))){

			exportarDados = new ExportarDados();
			operacoesUteis = new OperacoesUteis();

			cout << "[ INICIO ] INSTÂANCIA GERANDO:\n " << atoi(argv[1]) << "\n";			
			buscaTabu2 = new  BuscaTabu2(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));			
			tempoConstrucaoFinal= clock();				
			Dados resultado = buscaTabu2->executar(importarDados->getProfessores(), importarDados->getTurmas(), importarDados->getSalas());
			tempoConstrucaoFinal = clock() - tempoConstrucaoFinal;	
			resultado.tempo_total_de_solucao = (((float)tempoConstrucaoFinal)/CLOCKS_PER_SEC);
			qntProfessores = importarDados->getProfessores().size();
			resultado.possivel_quantidade_total_quebra_na_relacao_professor_turma = operacoesUteis->quantidade_possivel_quebra_professor_turma(importarDados->getProfessores());
			resultado.possivel_quantidade_total_quebra_na_relacao_professor_dias = operacoesUteis->quantidade_possivel_quebra_professor_dias(importarDados->getProfessores());																				
			
			vector<int> professores_sem_cumprir_carga_horaria = operacoesUteis->verificar_professor_cumprir_carga_trabalho(importarDados->getTurmas(), importarDados->getProfessores(), resultado.associacao_turma_professor);
			map<string,int> turmas_sem_ser_alocadas =operacoesUteis->get_turmas_nao_alocadas_professor(resultado.associacao_turma_professor,importarDados->getTurmas());
						

			if(professores_sem_cumprir_carga_horaria.size() == 0 && turmas_sem_ser_alocadas.size() == 0){
				resultado.status_da_solucao =  true;	
			}else{
				resultado.status_da_solucao =  false;
			}
			
			exportarDados->converter_estrutura_para_salas(importarDados->getBlocos(), importarDados->getSalas(),importarDados->getTurmas(), resultado,atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[4]), qntProfessores); 
			cout << "[fim ] INSTÂANCIA GERANDO:\n " << atoi(argv[1]) << "\n";

		}else{
			cout << "NÃO TA ABRINDO\n";
		}
		
		delete(importarDados);
		delete(exportarDados);
		delete(buscaTabu2);
		delete(operacoesUteis);
	
	return 0;
}