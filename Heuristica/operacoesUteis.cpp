#include "operacoesUteis.hpp"


OperacoesUteis::OperacoesUteis(){}

OperacoesUteis::~OperacoesUteis(){}

int OperacoesUteis::quantidade_possivel_quebra_professor_turma(vector<Professor*> professores){
	int total=0;
	for(auto& pro: professores){
		total+= pro->getCargHorariaTrabalho()/2;
	}
	return total;
}

int OperacoesUteis::quantidade_possivel_quebra_professor_dias(vector<Professor*> professores){
	int total =0;
	for(auto& pro: professores){
		for(auto& turma: pro->getTurmasComFamiliaridade()){
			total += turma->getCargaHorariaTotal()/2;
		}
	}
	return total;
}

/*
Para encontrar as observações que deixei no código pesquisa por => [OBSERVAÇÃO]
*/

Solucao OperacoesUteis::construcao_inicial_aleatoria(vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas, bool ordenado, bool ordenado_crescente_ou_decrescente){
	popular_matriz_mapeamento();
	vector<associacaoTurmaProfessor> alocacao_turma_professor;	
	////cout << "INICIO\n";
	if(ordenado){
		alocacao_turma_professor = alocar_turma_professor_ordenado_crescente_ou_decrescente(professores,turmas,ordenado_crescente_ou_decrescente);			
	}else{
		alocacao_turma_professor = alocar_turma_professor_nao_ordenado(professores,turmas);		

	}	
	
	////cout << "INICIOU ALOCAR TURMA_SALA \n";
	vector<associacaoTurmaSala> alocacao_turma_sala = alocar_turma_sala(salas,turmas);	
	////cout << "fim ALOCAR TURMA_SALA \n";
	////cout << "INICIOU ALOCAR slot_turma \n";
	vector<associacaoSlotTurma> alocacao_slot_turma  = alocar_slot_turma(turmas,&alocacao_turma_sala,salas);	
	////cout << "fim ALOCAR slot_turma \n";
	Solucao solucao = Solucao(alocacao_turma_professor,alocacao_slot_turma,alocacao_turma_sala);
		
	//exportarRelacaoProfessor_turma(Dados resultados, int codigo_arquivo, int i, int j, int k)
	ExportarDados ex = ExportarDados();
	//Dados(vector<associacaoTurmaProfessor> associacao_turma_professor, vector<associacaoSlotTurma> associacao_slot_turma, vector<associacaoTurmaSala> associacao_turma_sala)
	/*
	vector<associacaoTurmaProfessor> getAssociacaoTurmaProfessor();

	vector<associacaoSlotTurma>  getAssociacaoSlotTurma();
	vector<associacaoTurmaSala> getAssociacaoTurmaSala();
	*/
	
	////cout << "ALOCOU TUDO\n";
	return solucao;
}	

/*
	O metodo get_componenteCurricular_turmas_sala_id recebe como parametro
	alocacao_turma_sala onde tem todas as relação Turmas com Salas, ou seja, onde cada turma foi 
	alocada em sua sala, partindo disso precisamos pegar todas as alocação de apenas uma respectiva sala
	que será passada no parametro codigo e como retorno tem um vector<string> onde vai ter  todos o componentes Curriculares (id ) da 
	turmas alocadas na sala.
*/

vector<string>  OperacoesUteis::get_componenteCurricular_turmas_sala_id(vector<associacaoTurmaSala>* alocacao_turma_sala, string codigo){
	vector<string> componenteCurriculares;	
	for(auto& turma_sala: (*alocacao_turma_sala)){
		if(turma_sala.codSala ==  codigo)
			componenteCurriculares.push_back(turma_sala.componenteCurricular);
	}
	return componenteCurriculares;
}

vector<string>  OperacoesUteis::get_componenteCurricular_turmas_sala_id_2(vector<associacaoTurmaSala> alocacao_turma_sala, string codigo){
	vector<string> componenteCurriculares;	
	for(auto& turma_sala: alocacao_turma_sala){
		if(turma_sala.codSala ==  codigo)
			componenteCurriculares.push_back(turma_sala.componenteCurricular);
	}
	return componenteCurriculares;
}

/*
 O método abaixo receberá o resultado do metodo get_id_dia_horario_componenteCurricular para retornar um vector<AuxTrocaTurmas> onde tera todos os pares  (dia, horario)
 representando cada id_dia_horario dentro do vetor passado;

AuxTrocaTurmas converter_id_dia_horario_em_dia_horario(int valores);
*/

AuxTrocaTurmas OperacoesUteis::diferenca_com_matriz_aux(int dia, int horario, vector<AuxTrocaTurmas> estaMatriz){

	int tamanho2 = 	estaMatriz.size();
	for (int i = 0; i < tamanho2; ++i)
	{
		if(estaMatriz[i].dia == dia && estaMatriz[i].horario == horario)
			return AuxTrocaTurmas(-1,-1);
	}

	return AuxTrocaTurmas(dia,horario);
}
vector<AuxTrocaTurmas> OperacoesUteis::diferenca_com_matriz(vector<AuxTrocaTurmas> estaMatriz){
	vector<AuxTrocaTurmas> resultado;
	int tamanho =5,horario, dia;	
	AuxTrocaTurmas aux;



	for (horario = 0; horario < (tamanho -1); horario++)
	{
		for (dia = 0; dia < tamanho; dia++)
		{
			aux  = diferenca_com_matriz_aux(dia, horario, estaMatriz);
			if(aux.dia != -1){
				resultado.push_back(aux);
			}
		}
	}	



	return resultado;
}
AuxTrocaTurmas OperacoesUteis::converter_id_dia_horario_em_dia_horario_aux(int valores){
	int tamanho =5,horario, dia;	
	for (horario = 0; horario < (tamanho -1); horario++)
	{
		for (dia = 0; dia < tamanho; dia++)
		{
			if(matrizMapeamento[horario][dia] == valores){
				return AuxTrocaTurmas(dia, horario);
			}
		}
	}		
	return AuxTrocaTurmas(-1, -1);
}

vector<AuxTrocaTurmas> OperacoesUteis::converter_id_dia_horario_em_dia_horario(vector<int> valores){
	vector<AuxTrocaTurmas> resultado;
	AuxTrocaTurmas aux;
	int tamanho = valores.size();

	for(int i=0;i< tamanho; i++)
		aux = converter_id_dia_horario_em_dia_horario_aux(valores[i]);		
	if(aux.dia != -1)
		resultado.push_back(aux);

	return resultado;
}

/*
	O metodo get_id_dia_horario_componenteCurricular recebe o vetor alocacao_slot_turmas e um vetor de string tendo todas as turmas que estão alocada 
	em uma determinada sala já previamente calculado pelo metodo get_componenteCurricular_turmas_sala_id;
	Partindo disso irei capiturar todas os valores do id_dia_horario, ou seja, terei todos os pares de dia e horario dentro de uma determinada sala;	

*/
vector<int> OperacoesUteis::get_id_dia_horario_componenteCurricular2(vector<associacaoSlotTurma> alocacao_slot_turma, string codSala){
	vector<int> resultado;
	
	for(auto& slot_turma: alocacao_slot_turma){
		if( slot_turma.codSala == codSala)
			resultado.push_back(slot_turma.id_dia_horario);
	}	
	return resultado;
}

vector<int> OperacoesUteis::get_id_dia_horario_componenteCurricular(vector<associacaoSlotTurma> alocacao_slot_turma, vector<string> componenteCurriculares){
	vector<int> resultado;

	for(auto& componente: componenteCurriculares){

		for(auto& slot_turma: alocacao_slot_turma){
			if(componente == slot_turma.componenteCurricular)
				resultado.push_back(slot_turma.id_dia_horario);
		}
	}
	return resultado;
}




/*

	RETORNO:
			1 PODE ADICIONAR 
			0 NÃO PODE ADICIONAR NESSE DIA E HORARIO GERE OUTRO;
			-1 NÃO PODE ADICIONAR ALÉM DO MAIS A GRADE DE HORÁRIO DA SALA JÁ ESTÁ LOTADA			
*/

/*
	TEM QUE REVISAR ESSA MERDA !
*/

int OperacoesUteis::verificar_relacao(vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma> alocar_slot_turma, string codigoSala, int id_dia_horario_aux){
	vector<int> relacao_dia_horario;			
	vector<string> componenteCurriculares = get_componenteCurricular_turmas_sala_id(alocacao_turma_sala,codigoSala);
			//////////cout << "tamanho do componenteCurriculares: "<< componenteCurriculares.size()<< "\n";

			/*
				Estou verificando se já existe alguma turma alocada nessa sala;
				[Depois verificar se a melhor abordagem é utilizando o vetor de associação turma_sala pois, posso utilizar o vector<Salas*> salas;]
			*/

	if(componenteCurriculares.size() > 0){

		relacao_dia_horario = get_id_dia_horario_componenteCurricular(alocar_slot_turma,componenteCurriculares);

				//////////cout << "TAMANHO DA relacao_dia_horario: "<< relacao_dia_horario.size() << "\n";

		if(relacao_dia_horario.size() > 0){


				/*
				 	Após isso vou apenas ver se o id_dia_horario_aux está contido no vetor relacao_dia_horario			
				*/

				/*
					Se relacao_dia_horario já tiver 20 item dentro do seu universo é sinla que a grade de horário da sala está preenchida

					se a relação tiver realmente cheia tenho que fazer a realocação dessa turma
				*/
			if(relacao_dia_horario.size() == 0){
					////////cout << "AQUI 1\n";
				return 1;
			}
			if(relacao_dia_horario.size() == 20){
					////////cout << "AQUI 2\n";
				return -1;
			}
			int valor  = verificar_relacao_diaHorario(id_dia_horario_aux,relacao_dia_horario);

			if(valor == 0){
				return 1; 									
			}else{
						//////////cout << "AQUI 1\n";
				return 0;
			}			
		}else{				
			return 1;
		}

	}else{
		return 1;
	}	

}

void OperacoesUteis::troca_turma_de_sala(string codigsalaAntiga, string componenteCurricular, vector<associacaoTurmaSala>* alocacao_turma_sala, vector<Sala*> salas){
	string codigoSalaNova;							
	int idSalaNova;	
	int qntSalas = salas.size();
	do{			
		idSalaNova = getIdSalaGerado(0, qntSalas,false ,salas);
		codigoSalaNova= salas[idSalaNova]->getCodSala();
	}while(codigoSalaNova == codigsalaAntiga);
	int tamanho = (*alocacao_turma_sala).size();
	int id;
	for (int i = 0; i < tamanho; ++i){
		if((*alocacao_turma_sala)[i].componenteCurricular == componenteCurricular){
			id  = i;
			break;
		}						
	}
	(*alocacao_turma_sala)[id].codSala = codigoSalaNova;
}


int OperacoesUteis::getIdSalaGerado(int minimo, int maximo, bool flag, vector<Sala*> salas){
	int idSala = gerar_numero_aleatorio(minimo,maximo);
	if(flag){
		do{
			idSala = gerar_numero_aleatorio(minimo,maximo);								
		}while(salas[idSala]->getTipoSala()!= 0);
		return idSala;
	}

	return 	idSala;							

}

void OperacoesUteis::alocar_turma_sala_aux(vector<associacaoTurmaSala>  *alocar_turma_sala, int quantidadeTurmas, string componenteCurricular, vector<Sala*> salas, bool flag){
	associacaoTurmaSala associacaoTurmaSalaAux;
	int idSala;
	int zero=0;
	int qntSalas = salas.size();
	for (int i = 0; i < quantidadeTurmas; i++){				
		idSala = getIdSalaGerado(zero,qntSalas, flag, salas);
		associacaoTurmaSalaAux.componenteCurricular = componenteCurricular;
		associacaoTurmaSalaAux.codSala = salas[idSala]->getCodSala();
		alocar_turma_sala->push_back(associacaoTurmaSalaAux);	
	}	
}

vector<ProfessorDTO> OperacoesUteis::converter_professor_professorDTO(vector<Professor*> professores){
	vector<ProfessorDTO> resultado;
	int qntProfessor = professores.size();
	for (int p = 0; p < qntProfessor; ++p)
	{
		resultado.push_back(ProfessorDTO(professores[p]->getSiape(), professores[p]->getCargHorariaTrabalho()));
	}
	return resultado;
}

vector<TurmaDTO> OperacoesUteis::converter_turma_turmaDTO(vector<Turma*> turmas){
	vector<TurmaDTO> resultado;
	int qntTurmas = turmas.size();
	for (int i = 0; i < qntTurmas; ++i){		
		//turmas[i]->imprimir();
		resultado.push_back(TurmaDTO(turmas[i]->getComponenteCurricular(),turmas[i]->getCargaHorariaTotal()));
	}
	return resultado;
}

vector<TurmaOrdenacaoAglutinado> OperacoesUteis::converter_turmaDTO_em_turmaOrdenacaoAglutinado(vector<TurmaDTO> turmasTDO){
	int qntTurmasTDO = turmasTDO.size();	
	vector<TurmaOrdenacaoAglutinado> resultado;
	int idTurmaDTO;
	for (int i = 0; i < qntTurmasTDO; ++i){				
		idTurmaDTO = verificar_turmaDTO(resultado, turmasTDO[i].getCarga());
		if( idTurmaDTO > -1){																		
			resultado[idTurmaDTO].adicionarTurmaDTO(TurmaDTO(turmasTDO[i].getComponenteCurricular(),turmasTDO[i].getCarga()));				
		}else{								
			resultado.push_back(TurmaOrdenacaoAglutinado(turmasTDO[i].getCarga(), turmasTDO[i]));				
		}
	}
	return resultado;
}

int OperacoesUteis::verificar_turmaDTO(vector<TurmaOrdenacaoAglutinado> turmaOrdenacaoAglutinado, int valor){		
	int qntTurmaOrdenacaoAglutinado =turmaOrdenacaoAglutinado.size();
	for (int t = 0; t < qntTurmaOrdenacaoAglutinado; t++){				
		if(turmaOrdenacaoAglutinado[t].getValor() == valor) return t;
	}
	return -1;
}

vector<ProfessorDTO> OperacoesUteis::ordenar_professorDTO_crescente_ou_decrescente(vector<Professor*> professores, bool flag){
	vector<ProfessorDTO> professorDTOs = converter_professor_professorDTO(professores);
	if(flag)
			sort(professorDTOs.begin(), professorDTOs.end(), ordenar_professores_crescente); // CRESCENTE 
		else 
			sort(professorDTOs.begin(), professorDTOs.end(), ordenar_professores_decrescente); // DECRESCENTE
		return professorDTOs;

	}

	vector<TurmaOrdenacaoAglutinado> OperacoesUteis::converter_ordenar_turmas(vector<Turma*> turmas){
		vector<TurmaDTO> turmasTDOs = converter_turma_turmaDTO(turmas);	
		sort(turmasTDOs.begin(), turmasTDOs.end(), ordenacao_turmasDTO); 
		vector<TurmaOrdenacaoAglutinado> ordenado = converter_turmaDTO_em_turmaOrdenacaoAglutinado(turmasTDOs);
		return ordenado;
	}
	// Retirei o statis na implementação porque só precisa deixar na declaração da função no .hpp da classe!
	bool OperacoesUteis::ordenar_professores_decrescente(ProfessorDTO& professor1, ProfessorDTO& professor2){
		return professor1.getCargaHoraria() < professor2.getCargaHoraria();
	}

	bool OperacoesUteis::ordenar_professores_crescente(ProfessorDTO& professor1, ProfessorDTO& professor2){
		return professor1.getCargaHoraria() > professor2.getCargaHoraria();
	}

	bool OperacoesUteis::ordenacao_turmasDTO(TurmaDTO& turma1, TurmaDTO& turma2){
		return turma1.getCarga() < turma2.getCarga();
	}

	bool OperacoesUteis::ordencao_salas_turmas(associacaoTurmaSala& a, associacaoTurmaSala& b){
		int valor_a = stoi(a.codSala);
		int valor_b = stoi(b.codSala);
		return valor_a < valor_b;
	}

	void OperacoesUteis::popular_matriz_mapeamento(){
		int tamanho =5,horario, dia, id=1;	
		for (horario = 0; horario < (tamanho -1); horario++)
		{
			for (dia = 0; dia < tamanho; dia++)
			{
				matrizMapeamento[horario][dia] = id++;
			}
		}
	}

	troca_dia_horario  OperacoesUteis::get_dia_horario(int id_dia_horario){
		associacaoSlotTurma resultado ;
		int tamanho =5,horario, dia;	
		for (horario = 0; horario < (tamanho -1); horario++)
		{
			for (dia = 0; dia < tamanho; dia++)
			{
				if(matrizMapeamento[horario][dia]  == id_dia_horario){
				//associacaoSlotTurma(int dia_horario, int dia, int horario)
					return troca_dia_horario(matrizMapeamento[horario][dia], dia, horario);
				}
			}
		}
		return troca_dia_horario(0,0,0);
	}

	int OperacoesUteis::getNumeroMatrizMapeamento(int horario, int dia){
		if(horario < 0 || horario > 4 || dia< 0 || dia > 5) return -1;
		else return matrizMapeamento[horario][dia];
	}


	int OperacoesUteis::gerar_numero_aleatorio(int menor, int maior){
		return rand() % (menor - maior) + menor;
	}


	void OperacoesUteis::ordenar_associacao_turma_sala(vector<associacaoTurmaSala> *associar_turma_sala ){
		sort(associar_turma_sala->begin(), associar_turma_sala->end(), ordencao_salas_turmas); 

	}

	vector<associacaoTurmaProfessor> OperacoesUteis::copiar_associacao_turma_professor(vector<associacaoTurmaProfessor> associacao_turma_professor){
		vector<associacaoTurmaProfessor>  copia;
		int tamanho = copia.size();
		for (int i = 0; i < tamanho; i++){
			copia.push_back(associacaoTurmaProfessor(associacao_turma_professor[i].componenteCurricular, associacao_turma_professor[i].siape));
		}
		return copia;
	}

	vector<associacaoTurmaSala> OperacoesUteis::copiar_associacao_turma_sala(vector<associacaoTurmaSala> associacao_turma_sala){
		vector<associacaoTurmaSala> copia;
		int tamanho = associacao_turma_sala.size();
		for (int i = 0; i < tamanho; i++){
			copia.push_back(associacaoTurmaSala(associacao_turma_sala[i].codSala,associacao_turma_sala[i].componenteCurricular));
		}
		return copia;
	}

	vector<associacaoSlotTurma> OperacoesUteis::copiar_associacao_slot_turma(vector<associacaoSlotTurma> associacao_slot_turma){
		vector<associacaoSlotTurma> copia;
		int tamanho = associacao_slot_turma.size();
		for (int i = 0; i < tamanho; i++){
			copia.push_back(associacaoSlotTurma(associacao_slot_turma[i].id_dia_horario,associacao_slot_turma[i].componenteCurricular, associacao_slot_turma[i].dia, associacao_slot_turma[i].horario, associacao_slot_turma[i].codSala));
		}

		return copia;
	}

  /*
 	Metodo para verificar se uma relação dia_horario já está alocado no universo de alocações de uma sala

    Parametros: dia_horario, vector<int> relações dia_horario da Sala

    retorno: 1 se estíver, 0 caso contrário

*/
	int OperacoesUteis::verificar_relacao_diaHorario(int dia_horario, vector<int> dia_horario_sala){
		if((find(dia_horario_sala.begin(), dia_horario_sala.end(), dia_horario) != dia_horario_sala.end()) == false)
			return 1;
		else return 0;
	/*
	// DEPOIS TROCAR PELA IMPLEMENTAÇÃO DE BAIXO É MAIS ELEGANTE
	for(auto& dia: dia_horario_sala){
		if(dia == dia_horario) 
			return 1;
	}
	
	return 0;
	*/
	}


	vector<associacaoTurmaProfessor> OperacoesUteis::alocar_turma_professor_ordenado_crescente_ou_decrescente(vector<Professor*> professores,vector<Turma*> turmas, bool flag){
		int qntProfessores, posiProfessor, cargaHorariaProfessorTotal, qntTurmaOrdenacaoAglutinado,quantidadeTurmas,valor_da_carga_da_turma;
		vector<associacaoTurmaProfessor> alocacao_turma_professor;	
		vector<TurmaOrdenacaoAglutinado> resultado = converter_ordenar_turmas(turmas); 
		vector<ProfessorDTO> professoresDTO = ordenar_professorDTO_crescente_ou_decrescente(professores, flag);
	//vector<ProfessorDTO> professoresDTO = ordenar_professorDTO(professores);

		qntProfessores = professoresDTO.size();
		qntTurmaOrdenacaoAglutinado = resultado.size();
		associacaoTurmaProfessor objeto;
		TurmaDTO turmaDTOaux;
		int quantidade_turmas_restantes;

	/*
		Primeiro for vai percorrer os professores para pegar o valor da carga de trabalho para usar como valor da moeda;
		Rio branco - Acre 
	*/
		for (posiProfessor= 0; posiProfessor < qntProfessores; posiProfessor++){
			cargaHorariaProfessorTotal = professoresDTO[posiProfessor].getCargaHoraria();
		//////cout << "PROFESSOR [" <<  posiProfessor << "]\n";



			//Algoritmo do troco.


			for (int i = qntTurmaOrdenacaoAglutinado-1; i >=0 ; i--){			
			//resultado[i].imprimir1();			

				quantidade_turmas_restantes = resultado[i].getQuantidade();

				if(quantidade_turmas_restantes > 0){

					valor_da_carga_da_turma = resultado[i].getValor();
					quantidadeTurmas = cargaHorariaProfessorTotal/valor_da_carga_da_turma;			

					//cout << " | QuantidadeTurmas a ser retirada:[ "<< quantidadeTurmas<< " ]\n";
					if(quantidadeTurmas > 0 ){
					/*
					 Removendo a quantidade total da carga horária do professor será 
					 a quantidade de turmas que foram selecionadas multiplicada com 
					 valor que ela tem total de carga (horária teorica e pratica)
					 */

						cargaHorariaProfessorTotal -= quantidadeTurmas*resultado[i].getValor();
					/*
				 	Sabendo a quantidade de turmas que vou ter que selecionar 
					preciso agora remover essa quantidade do valor getQuantidade 
					e escolher aleatoriamente quais turmas vou pegar do vetor vector<turmasDTOs>
					de dentro do objeto TurmaOrdenacaoAglutinado;
					*/
						resultado[i].setQuantidadeMenor(quantidadeTurmas);
					/*
					O for agora vai rodar quantas turmas tem que ser removidas e fazer essa operação já 
					setando siape do professor no objeto turma e setar 
					também o atributo alocado como verdadeiro 
					e pegando essa objeto e setando no conjunto de 
					turmas que o professor tem das turmas alocadas
					*/
						for (int t = 0; t < quantidadeTurmas; ++t){

						//Nessa linha estou pegando a TurmaDTO e removendo o vector dentro da classe
						//turmaOrdenacaoAglutinado

							turmaDTOaux = resultado[i].getTurmaDTO(0);
							if(turmaDTOaux.getCarga() > -1){

								objeto.siape = professoresDTO[posiProfessor].getSiape();
								objeto.componenteCurricular = turmaDTOaux.getComponenteCurricular();						
								alocacao_turma_professor.push_back(objeto);

							}
						}
					}	
				}
			}
		}

		return alocacao_turma_professor;
	}


	vector<associacaoTurmaProfessor> OperacoesUteis::alocar_turma_professor_nao_ordenado(vector<Professor*> professores, vector<Turma*> turmas){
	////////cout << "[INICIO] -alocar_turma_professor\n";
		int qntProfessores, posiProfessor, cargaHorariaProfessorTotal, qntTurmaOrdenacaoAglutinado,quantidadeTurmas,valor_da_carga_da_turma;
		vector<associacaoTurmaProfessor> alocacao_turma_professor;	
		vector<TurmaOrdenacaoAglutinado> resultado = converter_ordenar_turmas(turmas);		


		qntProfessores = professores.size();		
		qntTurmaOrdenacaoAglutinado = resultado.size();

		associacaoTurmaProfessor objeto;
		TurmaDTO turmaDTOaux;
	/*
		Primeiro for vai percorrer os professores para pegar o valor da carga de trabalho para usar como valor da moeda;

	*/ 
		int quantidade_turmas_restantes;
		for (posiProfessor= 0; posiProfessor < qntProfessores; posiProfessor++){
			cargaHorariaProfessorTotal = professores[posiProfessor]->getCargHorariaTrabalho();

		/*
			Algoritmo do troco.
		*/

			for (int i = qntTurmaOrdenacaoAglutinado-1; i >=0 ; i--){

				quantidade_turmas_restantes = resultado[i].getQuantidade();


				if(quantidade_turmas_restantes > 0){
					valor_da_carga_da_turma = resultado[i].getValor();
					quantidadeTurmas = cargaHorariaProfessorTotal/valor_da_carga_da_turma;			

					if(quantidadeTurmas > 0 ){
				/*
					 Removendo a quantidade total da carga horária do professor será 
					 a quantidade de turmas que foram selecionadas multiplicada com 
					  valor que ela tem total de carga (horária teorica e pratica)
				*/
						cargaHorariaProfessorTotal -= quantidadeTurmas*resultado[i].getValor();
				/* Sabendo a quantidade de turmas que vou ter que selecionar 
					preciso agora remover essa quantidade do valor getQuantidade 
					e escolher aleatoriamente quais turmas vou pegar do vetor vector<turmasDTOs>
					de dentro do objeto TurmaOrdenacaoAglutinado;
				*/
						resultado[i].setQuantidadeMenor(quantidadeTurmas);
				/*O for agora vai rodar quantas turmas tem que ser removidas e fazer essa operação já 
					setando siape do professor no objeto turma e setar 
					também o atributo alocado como verdadeiro 
					e pegando essa objeto e setando no conjunto de 
					turmas que o professor tem das turmas alocadas
				*/
						for (int t = 0; t < quantidadeTurmas; ++t){
					/*
						Nessa linha estou pegando a TurmaDTO e removendo o vector dentro da classe
						turmaOrdenacaoAglutinado
					*/						 
							turmaDTOaux = resultado[i].getTurmaDTO(0);
							if(turmaDTOaux.getCarga() > -1){
						/*
							string componenteCurricular;
							int siape;
						*/
								objeto.siape = professores[posiProfessor]->getSiape();
								objeto.componenteCurricular = turmaDTOaux.getComponenteCurricular();						
								alocacao_turma_professor.push_back(objeto);

							}
						}
					}	
				}
				
			}
	} // FIM DO FOR QUE PERCORRE A QUANTIDADE N DE PROFESSORES
	////////cout << "[FIM] -alocar_turma_professor\n";
	return alocacao_turma_professor;

}


vector<associacaoTurmaSala> OperacoesUteis::alocar_turma_sala(vector<Sala*> salas, vector<Turma*> turmas){	
	////////cout << "[INICIO] -alocar_turma_sala\n";
	vector<associacaoTurmaSala>  alocar_turma_sala;
	int qntTurmas = turmas.size();	
	int qntTurmasAlocarTeorica,qntTurmasAlocarPratica;
	int caracteristicaTurma;		
	string componenteCurricular;
	associacaoTurmaSala associacaoTurmaSalaAux;

	for (int t = 0; t < qntTurmas; t++){		
		caracteristicaTurma = turmas[t]->getCaracteristicaTurma();
		componenteCurricular = turmas[t]-> getComponenteCurricular();	
		
		switch(caracteristicaTurma){
			case 0: // PURAMENTE TEORICA
				// ALOCANDO A PARTE TEORICA DA DISCIPLINA 
			qntTurmasAlocarTeorica = (turmas[t]->getCreditoTeorico()/2);	
			alocar_turma_sala_aux(&alocar_turma_sala,qntTurmasAlocarTeorica,componenteCurricular,salas, false);
			break;
			case 1:// TEORICA_PRATICA
			// ALOCANDO A PARTE TEORICA DA DISCIPLINA 
			qntTurmasAlocarTeorica = (turmas[t]->getCreditoTeorico()/2);	
			alocar_turma_sala_aux(&alocar_turma_sala,qntTurmasAlocarTeorica,componenteCurricular,salas, false);
			// ALOCANDO A PARTE PRATICA DA DISCIPLINA 
			qntTurmasAlocarPratica = (turmas[t]->getCreditoPratico()/2);				
			alocar_turma_sala_aux(&alocar_turma_sala,qntTurmasAlocarPratica,componenteCurricular,salas, true);
			break;
			case 2:// PURAMENTE PRATICA
			// ALOCANDO A PARTE PRATICA DA DISCIPLINA 
			qntTurmasAlocarPratica = (turmas[t]->getCreditoPratico()/2);
			alocar_turma_sala_aux(&alocar_turma_sala,qntTurmasAlocarTeorica,componenteCurricular,salas, true);
			break;
		}			
	}	
	////////cout << "[FIM] -alocar_turma_sala\n";
	return alocar_turma_sala;	
}



int OperacoesUteis::verificar_lacuna_na_sala2(string codigoSala, int id_dia_horario_aux , vector<associacaoSlotTurma> alocar_slot_turma){
	for(auto& ts: alocar_slot_turma){
		if(ts.codSala == codigoSala && ts.id_dia_horario == id_dia_horario_aux)
			return 0;
	}
	return 1;	

}


/*
Método vai percorre todo o veotor de alocação slot turma e verificar se vai encontrar uma relação codSala + id_dia_horario_aux se tiver porque aquela 
	lacuna já está cheia na sala.

			1 PODE ADICIONAR 
			0 NÃO PODE ADICIONAR NESSE DIA E HORARIO GERE OUTRO;
			-1 NÃO PODE ADICIONAR ALÉM DO MAIS A GRADE DE HORÁRIO DA SALA JÁ ESTÁ LOTADA			

	string codSala;
	int id_dia_horario;
	int dia, horario;
	string componenteCurricular;



*/

int OperacoesUteis::verificar_lacuna_na_sala( vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma> alocar_slot_turma, string codigoSala, int id_dia_horario_aux){	
	vector<string> relacao = get_componenteCurricular_turmas_sala_id(alocacao_turma_sala, codigoSala);
	if(relacao.size() ==  20)
		return -1;

	for(auto& ts: alocar_slot_turma){
		if(ts.codSala == codigoSala && ts.id_dia_horario == id_dia_horario_aux)
			return 0;
	}

	return 1;
}

vector<associacaoSlotTurma>  OperacoesUteis::alocar_slot_turma(vector<Turma*> turmas, vector<associacaoTurmaSala>* alocacao_turma_sala, vector<Sala*> salas){
	////cout <<"TRABALHANDO\n";
	//////cout << "[INICIO] -alocar_slot_turma\n";
	vector<associacaoSlotTurma> alocar_slot_turma;	
	vector<associacaoTurmaSala> turmas_nao_alocadas;
	int dia, horario;
	int zero=0;
	int total = 5;
	bool flag= true;	
	string codigoSala,componenteCurricular;
	//vector<string> componenteCurriculares;
	int contador=0;
	int id_dia_horario_aux;

	for(auto& turma_sala: *(alocacao_turma_sala)){
		codigoSala = turma_sala.codSala;
		////cout << "ALOCANDO TURMA: "<< codigoSala << "\n";
		/*
			Vou pegar turma_sala : Após isso vou ter que gerar um dia e horário aleatorio;
		*/
		
		componenteCurricular  = turma_sala.componenteCurricular;
		////////cout << "TENTANDO ALOCAR codSala: "<< codigoSala << " componenteCurricular: "<< componenteCurricular << "\n";

		flag= true;

		contador = 0;
		while(flag){						
			contador++;
			/*
			[OBSERVAÇÃO] - PRECISO PENSAR EM ALGUMA 
			*/			
			horario  = gerar_numero_aleatorio(zero, total-1);
			dia =  gerar_numero_aleatorio(zero, total);	
			//////////cout << "HORÁRIO: "<< horario << " dia: "<<  dia << "\n";
			id_dia_horario_aux = getNumeroMatrizMapeamento(horario, dia);
			//////////cout << "id_dia_horario_aux:"<<id_dia_horario_aux<<"\n";
			/*
				Apos gerar aleatóriamente o valor de dia e horário
				preciso verificar se na sala que estou alocado existe 
				essa disponibilidade se não eu irei gerar novamente um novo 
				número de horario e dia.				
				
				- Para pegar os dias que tem alocação para uma determinada sala 
				eu irei pegar o codigo da sala e varrer o vetor 
			*/
			/*
				ERRO PROVAVELMENTE ESTÁ NO MÉTODO VERIFICAR_RELACAO;
			*/

			//int resultado_verificacao_relacao = verificar_relacao(alocacao_turma_sala, alocar_slot_turma,codigoSala,id_dia_horario_aux);
			int resultado_verificacao_relacao = verificar_lacuna_na_sala(alocacao_turma_sala, alocar_slot_turma,codigoSala,id_dia_horario_aux);

			////////////cout << "resultado_verificacao_relacao: "<<resultado_verificacao_relacao<<"\n";
			if(resultado_verificacao_relacao ==  1){
				//////cout << "resultado_verificacao_relacao ==1 \n";
				flag = false;				
				alocar_slot_turma.push_back(associacaoSlotTurma(id_dia_horario_aux,componenteCurricular, dia, horario,codigoSala));
			}
			if(resultado_verificacao_relacao == -1){
				//-1 NÃO PODE ADICIONAR ALÉM DO MAIS A GRADE DE HORÁRIO DA SALA JÁ ESTÁ LOTADA													
				//////////cout << "-1 NÃO PODE ADICIONAR ALÉM DO MAIS A GRADE DE HORÁRIO DA SALA JÁ ESTÁ LOTADA\n";
				//////cout << "resultado_verificacao_relacao == -1\n";
				troca_turma_de_sala(codigoSala, componenteCurricular, alocacao_turma_sala, salas);						
			}			

			if (resultado_verificacao_relacao == 0){
				//////cout << "resultado_verificacao_relacao == 0\n";
				flag = true;				
			}

			if(contador== 600){
				//cout << "ENTROU\n"	;
				turmas_nao_alocadas.push_back(turma_sala);
				flag = false;
				/*
				[OBSERVAÇÃO] - ATRIBUI FLAG = FALSE; 
				 E ADICIONA A TURMA EM UMA LISTA SEGUNDARIA PARA 
				 QUANDO TERMINAR ANTES DE RETORNAR MANDA PARA UM MÉTODO 
				 E VERIFICAR SE ESSA  LISTA TA VAZIA SE TIVER OK, PASSA
				 SE NÃO EU TENTO ALOCAR NO PRIMEIRO MELHOR 
				 	- Como as turmas são associadas a salas antes de alocarem dia e horario tem que verificar dentro da sala se não tiver lacuna 
				 	procura na próxima 
				*/
			}


			}// FIM DO WHILE
			////cout << "alocou TURMA: "<< codigoSala << "\n";
		}	
		if(turmas_nao_alocadas.size() > 0)
			alocar_turmas_nao_alocadas(alocacao_turma_sala,&alocar_slot_turma, turmas_nao_alocadas, salas);

	////////cout << "[FIM] -alocar_slot_turma\n";
		return alocar_slot_turma;

	}

	int OperacoesUteis::procura_lacuna_na_grade_horario_da_sala(vector<int>  id_dias_horarios){
		if(id_dias_horarios.size() == 20) 
			return -1;
		for(int i=1; i<=20; i++){		
			if((find(id_dias_horarios.begin(), id_dias_horarios.end(), i) != id_dias_horarios.end()) == false){
				return i;
			}
		}
		return -1;
	}

	void OperacoesUteis::alocar_turmas_nao_alocadas(vector<associacaoTurmaSala>* alocacao_turma_sala, vector<associacaoSlotTurma>* alocar_slot_turma, vector<associacaoTurmaSala> turmas_nao_alocadas, vector<Sala*> salas){				
		vector<string> turmas_sala; 
		vector<int>  id_dias_horarios;

		bool flag ;
		int tamanho = (*alocacao_turma_sala).size();
		int id;
		int verificador;
		string codigoSalaAtual, codigoSalaNova;

		int qntSalas  = salas.size();
		int idSala;
		if(turmas_nao_alocadas.size()){
			for(auto& turma: turmas_nao_alocadas){
				flag = true;
				codigoSalaAtual = turma.codSala;
				codigoSalaNova = codigoSalaAtual;

				do{
					turmas_sala = get_componenteCurricular_turmas_sala_id(alocacao_turma_sala, codigoSalaNova);
					id_dias_horarios = get_id_dia_horario_componenteCurricular((*alocar_slot_turma),turmas_sala);
					verificador = procura_lacuna_na_grade_horario_da_sala(id_dias_horarios);
					if(verificador > -1){
						if(codigoSalaNova != codigoSalaAtual){

							for (int i = 0; i < tamanho; ++i){
								if((*alocacao_turma_sala)[i].componenteCurricular == turma.componenteCurricular){
									id  = i;
									break;
								}						
							}
							(*alocacao_turma_sala)[id].codSala = codigoSalaNova;					
						}
							/*
								Adicionar no alocar_slot_turma a turma 
							*/ 
						troca_dia_horario troca  = get_dia_horario(verificador);		
					//associacaoSlotTurma(int dia_horario, string componente, int dia, int horario)			
						(*alocar_slot_turma).push_back(associacaoSlotTurma(troca.id_dia_horario,turma.componenteCurricular, troca.dia, troca.horario, codigoSalaNova));
						flag = false;
					}else{ 
					/*
						QUANDO NA SALA QUE A TURMA ESTÁ TA CHEIA PRECISAMOS ENCONTRAR OUTRA 
						IMPORTANTE FRIZAR QUE O NOVO CODIGO DA SALA PRECISA SER DIFERENTE DA SALA ANTIGA
					*/ 
						do{
							idSala = gerar_numero_aleatorio(0,qntSalas);	
							codigoSalaNova  = salas[idSala]->getCodSala();
						}while(codigoSalaNova == codigoSalaAtual);										

					}
				}while(flag);

			}
		}
	}
	vector<string> OperacoesUteis::get_turmas_professor(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		vector<string> resultado;
		for(auto& turma_professor : alocacao_turma_professor){
			if(turma_professor.siape == siape)
				resultado.push_back(turma_professor.componenteCurricular);
		}
		return resultado;
	}






	vector<troca_dia_horario> OperacoesUteis::get_id_dia_horario(vector<string> componenteCurriculares, vector<associacaoSlotTurma> alocacao_slot_turma){
		vector<troca_dia_horario> resultado ;
		int qntComponenteCurriculares = componenteCurriculares.size();
		string componente;
		for (int c= 0; c < qntComponenteCurriculares; c++){
			componente = componenteCurriculares[c];
			for(auto& slot_turma: alocacao_slot_turma){
				if(slot_turma.componenteCurricular == componente){				
					resultado.push_back(troca_dia_horario(slot_turma.id_dia_horario, slot_turma.dia, slot_turma.horario));
				}
			}		
		}
		return resultado;
	}



	map<string, int> OperacoesUteis::get_carga_horaria_total_turmas(vector<Turma*> turmas){
		map<string, int> resultado;
		for(auto& turma : turmas){
			resultado.insert(pair<string, int>(turma->getComponenteCurricular(), turma->getCargaHorariaTotal()));
		}
		return resultado;
	}
/*
	Irá verificar se todos os professores tiveram cumpridas suas cargas horárias;
	retorna uma lista dos siape dos professores que ainda não estão alocados com sua totalidade de carga horária

*/
	int OperacoesUteis::calcular_valor_carga_horaria(map<string, int> turma_carga_horaria_total, vector<string> componenteCurricular){
		int total=0;
		for(auto& componente: componenteCurricular){		
			total  += turma_carga_horaria_total.find(componente)->second;
		}
		return total;
	}

/*
[OBSERVAÇÃO] revisar essa função !
*/
	vector<int> OperacoesUteis::verificar_professor_cumprir_carga_trabalho(vector<Turma*> turmas, vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		int cargaHorariaProfessorTotal;
		vector<int> resultado;
		map<int, vector<string>> turmas_por_professor  = get_turmas_pro_professor(professores,alocacao_turma_professor);
		map<string, int> turma_carga_horaria_total = get_carga_horaria_total_turmas(turmas);
		int siape;

		for(auto& professor: professores){
			cargaHorariaProfessorTotal = professor->getCargHorariaTrabalho();
			siape = professor->getSiape();

			if( cargaHorariaProfessorTotal != calcular_valor_carga_horaria(turma_carga_horaria_total,turmas_por_professor.find(siape)->second)){
				resultado.push_back(siape);
			}
		}
		return resultado;
	}

	map<int, vector<Turma*>> OperacoesUteis::get_turmas_preferiveis_por_professor(vector<Professor*> professores){
		map<int, vector<Turma*>> resultado;
		for(auto& professor: professores){
			resultado.insert(pair<int, vector<Turma*>>(professor->getSiape(), professor->getTurmasComFamiliaridade()));
		}
		return resultado;
	}







	bool OperacoesUteis::verificar_alocacao_turma(string componenteCurricular,vector<associacaoTurmaProfessor> alocacao_turma_professor){
		for(auto& associacao : alocacao_turma_professor){
			if(associacao.componenteCurricular == componenteCurricular)
				return true;
		}
		return  false;	
	}

	map<string,int> OperacoesUteis::get_turmas_nao_alocadas_professor(vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<Turma*> turmas){
		map<string,int> resultado;
		for(auto& turma: turmas){
			if(!verificar_alocacao_turma(turma->getComponenteCurricular(),alocacao_turma_professor)){
				resultado.insert(pair<string,int>(turma->getComponenteCurricular(), turma->getCargaHorariaTotal()));
			}
		}
		return resultado;
	}
	// está com erro também 
	vector<associacaoSlotTurma_indice> OperacoesUteis::get_associacao_turma_id_horario(int siape, vector<Professor*> professores, vector<string> componentesCurriulares, vector<associacaoSlotTurma> alocacao_slot_turma){
		vector<associacaoSlotTurma_indice> resultado;
		vector<int> dias;
		int dia_horario;
		int tamanho  = alocacao_slot_turma.size();
		dias = get_dias_preferiveis_professor(siape, professores);

		for(auto& componente: componentesCurriulares){

			for(int i =0 ; i< tamanho ; i++){
				if(componente == alocacao_slot_turma[i].componenteCurricular){
					dia_horario = alocacao_slot_turma[i].dia;	

					if(verificar_relacao_diaHorario(dia_horario,dias)==0){
						resultado.push_back(associacaoSlotTurma_indice(alocacao_slot_turma[i],i));					
					}
					
				}
			}
		}
		return resultado;
	}

	vector<int> OperacoesUteis::get_dias_preferiveis_professor(int siape, vector<Professor*> professores){
		vector<int>  vazio;
		for(auto& pro: professores){
			if(pro->getSiape()  == siape)
				return pro->getDiasPreferiveisTrabalho();
		}
		return vazio;
	}

	

	Solucao OperacoesUteis::copiar_solucao(Solucao s){	

		vector<associacaoTurmaProfessor> novo_associacao_turma_professor;
		vector<associacaoSlotTurma> novo_associacao_slot_turma;
		vector<associacaoTurmaSala> novo_associacao_turma_sala;	

		for(auto& turma_professor: s.getAssociacaoTurmaProfessor()){
			novo_associacao_turma_professor.push_back(associacaoTurmaProfessor(turma_professor.componenteCurricular, turma_professor.siape));
		}

		for(auto& turma_sala: s.getAssociacaoTurmaSala()){
			novo_associacao_turma_sala.push_back(associacaoTurmaSala(turma_sala.codSala, turma_sala.componenteCurricular));
		}	

		for(auto& turma_slot: s.getAssociacaoSlotTurma()){
			novo_associacao_slot_turma.push_back(associacaoSlotTurma(turma_slot.id_dia_horario,turma_slot.componenteCurricular, turma_slot.dia, turma_slot.horario,turma_slot.codSala));
		}
			Solucao solucaoCopiada = Solucao(novo_associacao_turma_professor,novo_associacao_slot_turma,novo_associacao_turma_sala);			
			solucaoCopiada.setIteracaoEncontrada(s.getIteracaoEncontrada());
			solucaoCopiada.setContadorRefinamento(s.getContadorRefinamento());
		return  solucaoCopiada;	
	}


	vector<string> OperacoesUteis::get_diferenca_turmas_preferiveis_alocadas(vector<Turma*> turmas, vector<string> componenteCurricular){
		vector<string> componentes;
		bool flag;

		for(auto& componente : componenteCurricular){
			flag = true;
			for(auto* turma: turmas){
				if(componente == turma->getComponenteCurricular()){
					flag = false;
					break;
				}
			}
			if(flag){
				componentes.push_back(componente);
			}
		}
		return componentes;
	}




	


	vector<turma_id> OperacoesUteis::get_diferenca_turmas_preferiveis_alocadas_com_posicao_no_vetor_de_relacoes(vector<Turma*> turmas, vector<turma_id>   alocadas_para_professor){
		bool flag;
		vector<turma_id> resultado;
		for(auto& alocadas: alocadas_para_professor){
			flag = true;
			for(auto* turma: turmas){

				if(alocadas.componenteCurricular == turma->getComponenteCurricular()){
					flag = false;
					break;
				}
			}
			if(flag){
				resultado.push_back(alocadas);
			}
		}
		return resultado;
	}



/*
	Método tera finalidade de verificar quem o professor pegou é quem não está dentro da lista de preferiveis dele
	retornar um map com key : siape | value : vetor de componentes curriculares
*/
	map<int, vector<string>> OperacoesUteis::get_professres_com_turmas_fora_das_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		vector<string> diferenca_turmas_preferiveis_alocadas;
		map<int, vector<string>> resultado;

		map<int, vector<string>> turmas_por_professor  = get_turmas_pro_professor(professores,alocacao_turma_professor);

		map<int, vector<Turma*>> professor_com_suas_tumas_com_familiaridade = get_turmas_preferiveis_por_professor(professores);

		int siape_professor;    
		for(map<int, vector<string>>::iterator it= turmas_por_professor.begin(); it!= turmas_por_professor.end(); ++it){
			siape_professor = it->first;    	
			diferenca_turmas_preferiveis_alocadas = get_diferenca_turmas_preferiveis_alocadas(professor_com_suas_tumas_com_familiaridade.find(siape_professor)->second, it->second);
			if(diferenca_turmas_preferiveis_alocadas.size() > 0){
				resultado.insert(pair<int, vector<string>>(siape_professor,diferenca_turmas_preferiveis_alocadas));
			}
		}
		return resultado;
	}


	map<int, vector<turma_id>> OperacoesUteis::get_professores_com_turmas_fora_das_preferiveis_com_posicao_no_vetor_de_relacoes(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		map<int, vector<turma_id>> resultado;
		vector<turma_id> diferenca_turmas_preferiveis_alocadas;

		map<int, vector<turma_id>>	turmas_por_professor = get_turmas_professor_com_posicao_no_vetor_de_relacoes(professores, alocacao_turma_professor);

		map<int, vector<Turma*>> professor_com_suas_tumas_com_familiaridade = get_turmas_preferiveis_por_professor(professores);
		int siape_professor;    
		for (map<int, vector<turma_id>>::iterator it= turmas_por_professor.begin(); it!= turmas_por_professor.end(); ++it){
			siape_professor =  it->first; 
			diferenca_turmas_preferiveis_alocadas = get_diferenca_turmas_preferiveis_alocadas_com_posicao_no_vetor_de_relacoes(professor_com_suas_tumas_com_familiaridade.find(siape_professor)->second, it->second);
			if(diferenca_turmas_preferiveis_alocadas.size() > 0){ 				
				resultado.insert(pair<int,vector<turma_id>>(siape_professor, diferenca_turmas_preferiveis_alocadas));				
			}
		}
		return resultado;
	}

/*
	método pega todas as turmas que estão associada a um professor com siape igual ao do parametro dentro do vetor alocacao_turma_professor de relações 
	retorna um vetor com par de componente curricular mais posicao dentro do vetor de alocacao_turma_professor;
*/
	vector<turma_id> OperacoesUteis::get_turmas_professor_com_posicao_no_vetor_de_relacoes_aux(int siape, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		vector<turma_id> resultado;
		int tamanho = alocacao_turma_professor.size();
		for (int i = 0; i < tamanho; i++){
			if(alocacao_turma_professor[i].siape == siape){
				resultado.push_back(turma_id(i,alocacao_turma_professor[i].componenteCurricular));
			}
		}
		return resultado;
	}
/*
	método pega todas as turmas que fora atribuidas ao professores e coloca em map sendo o value = a componenteCurricular da turma e id da posição no vetor alocacao_turma_professor
*/
	map<int, vector<turma_id>> OperacoesUteis::get_turmas_professor_com_posicao_no_vetor_de_relacoes(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		map<int, vector<turma_id>> resultado;
		int siape;		
		for(auto& pro: professores){
			siape =pro->getSiape();
			resultado.insert(pair<int,vector<turma_id>>(siape,get_turmas_professor_com_posicao_no_vetor_de_relacoes_aux(siape,alocacao_turma_professor)));
		}

		return resultado;
	}
	_2IndexDiferente OperacoesUteis::gerarIndexDiferentes(int maximo){
		int zero = 0;
		int index2, index1;
		
		do{
			index1  = gerar_numero_aleatorio(zero, maximo);
			index2  = gerar_numero_aleatorio(zero, maximo);

		}while(index1 == index2);


		return _2IndexDiferente(index1,index2);
	}

	map<int, vector<string>> OperacoesUteis::get_turmas_pro_professor(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor){
		map<int, vector<string>> resultado;
		int siape;
		for(auto& pro: professores){
			siape =pro->getSiape();
			resultado.insert(pair<int, vector<string>>(siape,get_turmas_professor(siape,alocacao_turma_professor)));
		}
		return resultado;
	}


	// ESTÁ COM ERRO ELE ESTÁ RETORNANDO É OS PROFESSORES QUE ESTÃO ALOCADOS COM TURMAS DENTRO DOS SEUS DIAS PREFEIRVEIS 
	map<int, vector<associacaoSlotTurma_indice>> OperacoesUteis::get_professores_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma){	
		map<int, vector<associacaoSlotTurma_indice>> resultado;
		vector<associacaoSlotTurma_indice> aux;

		map<int, vector<string>> turmas_professores =  get_turmas_pro_professor(professores, alocacao_turma_professor);

		for (map<int, vector<string>>::iterator i = turmas_professores.begin(); i != turmas_professores.end(); ++i){
			
			aux = get_associacao_turma_id_horario(i->first,professores,i->second,alocacao_slot_turma);			
			if(aux.size() > 0){
				resultado.insert(pair<int,vector<associacaoSlotTurma_indice>>(i->first,aux));
			}
			aux.clear();



		}	
		return resultado;
	}


	map<int, vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot>> OperacoesUteis::get_professores_com_turmas_alocadas_fora_dos_dias_preferiveis(vector<Professor*> professores, vector<associacaoTurmaProfessor> alocacao_turma_professor, vector<associacaoSlotTurma> alocacao_slot_turma, vector<associacaoTurmaSala> associacao_turma_sala){
		map<int, vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot>> resultado;

		map<int, vector<string>> professores_com_suas_turmas_alocadas =  get_turmas_pro_professor(professores, alocacao_turma_professor);

		map<int, vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor>>  professores_com_suas_turmas_alocadas_com_posicao_da_sala;
		/*
			O for abaixo vai guardar o siape do professor com a lista das turmas que foram alocadas para ele com a posição que ela está alcoada no vetor de relação turma_sala !
		*/
		for(auto& pro: professores_com_suas_turmas_alocadas){
			professores_com_suas_turmas_alocadas_com_posicao_da_sala.insert(pair<int,vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor>>(pro.first, get_turmas_nas_salas(pro.second,associacao_turma_sala)));
		}

		/*
			Agora precisamos percorrer o map do for anterior para vasculhar dentro da sala em qual lacuna dia e horario ela está associada dentro do vetor de associação turma slot 

		*/
		for (map<int, vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor>>::iterator it = professores_com_suas_turmas_alocadas_com_posicao_da_sala.begin(); it != professores_com_suas_turmas_alocadas_com_posicao_da_sala.end(); ++it){
			resultado.insert(pair<int,vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot>>(it->first, get_slot_das_turmas_do_professor_que_esta_fora_do_seu_dias_preferiveis(it->second, get_dias_preferiveis_professor(it->first, professores),alocacao_slot_turma)));
		}

		return resultado;
	}


	vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot> OperacoesUteis::get_slot_das_turmas_do_professor_que_esta_fora_do_seu_dias_preferiveis(vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor> turma_sala_posicao, vector<int> diaspreferiveisDoProfessor, vector<associacaoSlotTurma> alocacao_slot_turma){
		vector<associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot> resultado;

		/*
		 Atributos na variavel tur_sa_po:		 
			- string codSala;
			- string componenteCurricular;		
			- int posicao_no_vetor_de_relacao_turma_sala;
			
		Atributos da variável associacaoSlotTurma:		
			- int id_dia_horario;
			- int dia, horario;
			- string componenteCurricular;

		*/

		int tamanho = alocacao_slot_turma.size();

		for(auto&  tur_sa_po :turma_sala_posicao){
			for (int i = 0; i < tamanho; ++i){
				if(alocacao_slot_turma[i].componenteCurricular  == tur_sa_po.componenteCurricular){
					//verificar_relacao_diaHorario(int dia_horario, vector<int> dia_horario_sala)
					if(verificar_relacao_diaHorario(alocacao_slot_turma[i].dia,diaspreferiveisDoProfessor) == 0){
						/*Só vamos adicionar os dados das turmas que foram associado ao professor ṕorém estão associada a um slot que é um dia que não está dentro do grupo de dais desejados pelo professor*/
						//associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot(int posicao_no_vetor_de_relacao_turma_sala,int id_dia_horario,int dia, int horario,string componenteCurricular,int posicao_no_vetor_de_relacao_turma_slot)
						resultado.push_back(associacaoSlotTurma_com_posicao_tanto_do_vetor_turma_sala_como_turma_slot(tur_sa_po.posicao_no_vetor_de_relacao_turma_sala,alocacao_slot_turma[i].id_dia_horario,alocacao_slot_turma[i].dia,alocacao_slot_turma[i].horario,alocacao_slot_turma[i].componenteCurricular,i));
					}
				}
			}
		}
		return resultado;
	}


	vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor> OperacoesUteis::get_turmas_nas_salas(vector<string> componenteCurriculares, vector<associacaoTurmaSala> associacao_turma_sala){
		vector<associacaoTurmaSala_com_posicao_no_respectivo_vetor> resultado;
		int tamanho = associacao_turma_sala.size();
		for(auto& componente : componenteCurriculares){

			for (int i = 0; i < tamanho; i++)
			{
				if(componente == associacao_turma_sala[i].componenteCurricular){
					resultado.push_back(associacaoTurmaSala_com_posicao_no_respectivo_vetor(associacao_turma_sala[i].codSala, associacao_turma_sala[i].componenteCurricular, i));
				}
			}	
		}
		return resultado;
	}

