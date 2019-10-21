#include "gerador.hpp"


Gerador::Gerador(){

}

Gerador::~Gerador(){

}

void Gerador::executar(int cenarioSlots, int idArquivo,int novoQuantidadeProfessores, vector<int> novoPorcentagemPerfilProfessor, int novoQuantidadeSalas, int novoAnoPegarFeriado){
	
	quantidadeProfessores = novoQuantidadeProfessores;
	porcentagemPerfilProfessor = novoPorcentagemPerfilProfessor;
	quantidadeSalas = novoQuantidadeSalas;
	anoPegarFeriado = novoAnoPegarFeriado;	
	
	int codeProfessor=10,codeTurma =1,tamanhoPerfil,valorPerfil,tamanho=7,tam;
	

	int tiposPerfis[tamanho]={2,4,6,8,10,12,14};	
	int rastreio[tamanho];	
	vector<qntProfessorXPerfil> quantidadeProfessorPorPerfil = calcularQuantidadeProfessorPorPerfil();
	quantidadeProfessorPorPerfil = verificarQuantidadeProfessor(quantidadeProfessorPorPerfil);
	int tamPerfilPorProfessor = quantidadeProfessorPorPerfil.size();
	Turma* turma = new Turma();	
	
	for (int i = 0; i < tamPerfilPorProfessor; i++){
		
		tamanhoPerfil = quantidadeProfessorPorPerfil[i].quantidade;
		valorPerfil = quantidadeProfessorPorPerfil[i].perfil;

		for (int j = 0; j < tamanhoPerfil; j++){
			Professor* professor  = new Professor();

			gerarQuantidadeTurmasProfessor(valorPerfil,tamanho,tiposPerfis,rastreio);

			professor->setCodeProfessor(codeProfessor);
			professor->setCargaHoraria(valorPerfil);
			codeProfessor+=10;
			
			for (int k = 0; k < tamanho; k++){
				tam = rastreio[k];
				for (int t = 0; t < tam; t++){
					turma->setCodeTurma(codeTurma);
					codeTurma+=1;

					if( tam > 0  && tiposPerfis[k] == 2){						
						turma->setCargarHorariaTeorica(tiposPerfis[k]);
						turma->setCargarHorariaPratica(0);						
					}else if(tam > 0  && tiposPerfis[k] == 6){
						turma->setCargarHorariaTeorica(4);
						turma->setCargarHorariaPratica(2);
					}else{
						turma->setCargarHorariaTeorica(tiposPerfis[k]/2);
						turma->setCargarHorariaPratica(tiposPerfis[k]/2);
					}
					turmas.push_back(turma);
					professor->adicionarTurma(turma);
					turma = new Turma();
				}								
			}
			professores.push_back(professor);
		}
		
	}
	gravarArquivo(cenarioSlots,idArquivo);

}



/*
 Parametros:
 	quantidadeCreditoProfessor  = Representa quantos créditos o professor precisar trabalhar
 	quantidadesTiposCreditos = Representa a quantidade de perfis de creditos ele vai usar
 	tiposCreditos = um vetor que guarda todos os perfis de creditos a serem usados
 	rastreio = um vetor que vai rastrear quais perfis foram escolhidos e a quantidade por perfil
 	
retorno 
		retorna quantidade de turmas
*/

void  Gerador::gerarQuantidadeTurmasProfessor(int quantidadeCreditoProfessor,int quantidadesTiposCreditos, int *tiposCreditos, int *rastreio){
	int aux;	
	for (int i = quantidadesTiposCreditos-1; i>=0; i--){
		aux = 	quantidadeCreditoProfessor/tiposCreditos[i];
		rastreio[i] = aux;
		quantidadeCreditoProfessor -= aux*tiposCreditos[i];		
	}	
}

// Gera números aleatorios
int Gerador::gerarNumeroAleatorio(int min, int max){
	return (min + rand()%max);
}

string Gerador::getSemana(){
	return "1,2,3,4,5";
}

string Gerador::getSlotsHorario(){
	return "1315,1517,171930,192130";
}


string Gerador::getSlotsHorarioManha(){
	return "0810,1012";
}


string Gerador::getSlotsHorarioTarde(){
	return "1315,1517";
}

string Gerador::getCodSalas(int quantidade){
	string resultado = "";
	for (int i = 1; i <=quantidade; i++){
		resultado += to_string(i) +""+getMarcador(4);
	}
	//Remover ultimo caractere da String
	resultado.pop_back();
	return resultado;
}

string Gerador::getMarcador(int op){
	switch(op){
		case 1:
			return "-";
		case 2:
			return "*";
		case 3:
			return ">";
		case 4:
			return ",";
		default:					
			return "";
	}	
}
vector<qntProfessorXPerfil>  Gerador::verificarQuantidadeProfessor(vector<qntProfessorXPerfil> quantidadeProfessorPorPerfil){

	int contador =0;
	int tam = quantidadeProfessorPorPerfil.size();
	int folga = 0;
	int posicao;
	qntProfessorXPerfil aux;
	for (int i = 0; i < tam ; i++){
			contador+= quantidadeProfessorPorPerfil[i].quantidade;			
	}

	folga = quantidadeProfessores - contador;	
	if(folga > 0){
		posicao = procurarPosicaoPerfilZerado(quantidadeProfessorPorPerfil);	
		if(posicao > -1){
			aux.perfil  = quantidadeProfessorPorPerfil[posicao].perfil;			
		}else{
			aux.perfil = quantidadeProfessorPorPerfil[0].perfil;			
		}

		aux.quantidade = folga;
		quantidadeProfessorPorPerfil[posicao] = aux;
	}

	return quantidadeProfessorPorPerfil;
}



int Gerador::procurarPosicaoPerfilZerado(vector<qntProfessorXPerfil> quantidadeProfessorPorPerfil){	
	int tam  = quantidadeProfessorPorPerfil.size();	
	for (int i = 0; i < tam; i++)
		if(quantidadeProfessorPorPerfil[i].quantidade == 0)			
			return i;	

	return -1;	
	
}

vector<qntProfessorXPerfil> Gerador::calcularQuantidadeProfessorPorPerfil(){

	vector<qntProfessorXPerfil>  resultado;
	int qntPerfis = porcentagemPerfilProfessor.size();
	qntProfessorXPerfil aux;
	int auxQuantidadeProfessores = quantidadeProfessores;
	int credito = 2;
	for (int i = 0; i < qntPerfis; i++){
			aux.perfil = credito;
			aux.quantidade = ((auxQuantidadeProfessores * porcentagemPerfilProfessor[i])/ 100);			
			credito+=2;
			resultado.push_back(aux);
	}
	return resultado;
}


vector<Turma*> Gerador::getTurmas(){
	return  turmas;
}

vector<Professor*>  Gerador::getProfessores(){
	return professores;
}


string Gerador::linhaCodigosProfessor(){
	int tam = professores.size();
	string resultado = "";
	for (int i = 0; i < tam; i++){		
		resultado+= to_string(professores[i]->getCodeProfessor()) +""+ getMarcador(4);
	}
	resultado.pop_back();
	return resultado;
}


string Gerador::linhaCodigoTurma(){
	int tam = turmas.size();
	string codigo="";
	string pratica="";
	string teorica ="";

	for (int i = 0; i < tam; i++){
		codigo += to_string(turmas[i]->getCodeTurma())+""+ getMarcador(4);
		teorica += to_string(turmas[i]->getCargarHorariaTeorica())+""+ getMarcador(4);
		pratica += to_string(turmas[i]->getCargarHorariaPratica())+""+ getMarcador(4);
	}

	codigo.pop_back();
	teorica.pop_back();
	pratica.pop_back();

	codigo  = codigo + "\n" + pratica+"\n"+ teorica;

	return codigo;
}


string Gerador::linhasAssociandoProfessorTurmas(){
	string resultado="";
	string acumulador="";
	int tam = professores.size();
	int tam2;

	for (int i = 0; i < tam; i++){
		acumulador+=getMarcador(1) + ""+to_string(professores[i]->getCodeProfessor())+""+getMarcador(4);		
		tam2 = professores[i]->getTurmas().size();
		for (int j = 0; j < tam2; j++){

			acumulador+=to_string(professores[i]->getTurmas()[j]->getCodeTurma())+""+getMarcador(4);	
		}
		acumulador.pop_back();

		resultado+=acumulador+"\n";
		acumulador="";
	}
	return resultado;
}

string Gerador::linhasAssociandoProfessorCargaHoraria(){
	string resultado="";	
	string acumulador = "";
	int tam = professores.size();
	for (int i = 0; i < tam; i++){
		acumulador+=getMarcador(3)+""+to_string(professores[i]->getCodeProfessor())+""+getMarcador(4)+""+to_string(professores[i]->getCargaHoraria());
		resultado+=acumulador+"\n";
		acumulador="";
	}
	return resultado;
}

string Gerador::gerarDiasPreferiveisProfessores(){
	int min=2, max=3;
	int min2=1, max2=5;
	int tam = professores.size();
	int quantidadeDias;
	string acumulador="";
	string resultado ="";
	int dia;
	vector<int> auxDias;
	for (int i = 0; i < tam; i++){
		quantidadeDias = gerarNumeroAleatorio(min,max);
		for (int j = 0; j < quantidadeDias; j++){
			dia = gerarNumeroAleatorio(min2,max2);
			 if((find(auxDias.begin(), auxDias.end(), dia) != auxDias.end()) == false)			 
				auxDias.push_back(dia);			
		}
		acumulador+=+""+getMarcador(2)+""+to_string(professores[i]->getCodeProfessor())+""+getMarcador(4)+""+transfomarVectorString(auxDias);
		auxDias.clear();
		resultado+=acumulador + "\n";
		acumulador="";
	}
	return resultado;
}
string  Gerador::transfomarVectorString(vector<int> valores){
	string resultado = "";
	int tam = valores.size();
	for (int i = 0; i < tam; i++){
		resultado+=to_string(valores[i])+""+getMarcador(4);
	}
	resultado.pop_back();
	return resultado;
}

void Gerador::gravarArquivo(int cenarioSlots, int idArquivo){
	ofstream arq;
	arq.open("Entradas/"+to_string(idArquivo)+".txt", ios::out);
	arq << linhaCodigosProfessor()<< "\n";
	arq << linhaCodigoTurma()<< "\n";
	arq << getSemana() << "\n";
	arq << gerarNumeroAleatorio(1,5) << "\n";
	switch(cenarioSlots){
		case 1:
		arq << getSlotsHorario()<< "\n";
		break;
		case 2:
		arq << getSlotsHorarioManha() << getMarcador(4) <<getSlotsHorario()<< "\n";
		break;
		case 3:
		arq << "1012,"<< getSlotsHorario()<< "\n";
		break;
	}
	arq << getCodSalas(quantidadeSalas)<< "\n";
	arq << linhasAssociandoProfessorTurmas();	
	arq << gerarDiasPreferiveisProfessores();
	arq << linhasAssociandoProfessorCargaHoraria();
	arq.close();
}


void Gerador::gravarAquivosHeuristica(){
	
}