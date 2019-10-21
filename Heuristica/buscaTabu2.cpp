#include "buscaTabu2.hpp"

BuscaTabu2::BuscaTabu2(){

}

BuscaTabu2::~BuscaTabu2(){

}

BuscaTabu2:: BuscaTabu2(int  maximoIteracoes, int maximoIteracoesSemMelhora, int tamanhoFilaTabu){
	avaliacao = new Avaliacao();
	operacoesUteis = new OperacoesUteis();

	maxIteracoes = maximoIteracoes;
	maxIteracoesSemMelhora= maximoIteracoesSemMelhora;
	tamanhoMaxFila=tamanhoFilaTabu;
	melhorIteracao = 0; 
	contadorMelhoras = 0; 
	contadorRefinamento = 0;   
}

Dados BuscaTabu2::executar(vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas){
	Dados resultado;
	clock_t tempoConstrucaoInicial= clock();	
	Solucao melhorSolucao = operacoesUteis->construcao_inicial_aleatoria(professores, turmas, salas, true, false);


	tempoConstrucaoInicial = clock() - tempoConstrucaoInicial;	
	resultado.tempo_construcao_inicial = (((float)tempoConstrucaoInicial)/CLOCKS_PER_SEC);

	valores_quebraDia_quebraTurma valorMelhorSolucao;
	valorMelhorSolucao =  avaliacao->calcularFO(melhorSolucao.getAssociacaoTurmaProfessor(),melhorSolucao.getAssociacaoSlotTurma(), professores);				
		

	resultado.valorFOConstrucao = valorMelhorSolucao;

	Solucao solucaoAtual = operacoesUteis->copiar_solucao(melhorSolucao);
	solucaoAtual.setIteracaoEncontrada(-1);
	valores_quebraDia_quebraTurma valhorSolucaoAtual= valorMelhorSolucao;

	for (int i = 0; i < maxIteracoes; ++i){		
		//cout << "[Iteração] " <<i<<"\n";
		gerarMelhorVizinho(&solucaoAtual, valhorSolucaoAtual , professores, turmas, salas);	
		
		valhorSolucaoAtual = avaliacao->calcularFO(solucaoAtual.getAssociacaoTurmaProfessor(),solucaoAtual.getAssociacaoSlotTurma(), professores); 

		if((valhorSolucaoAtual.relacaoProfessorTurma + valhorSolucaoAtual.relacaoProfessorDia) < (valorMelhorSolucao.relacaoProfessorTurma + valorMelhorSolucao.relacaoProfessorDia)){
			////cout << "[BuscaTabu]:executar   MELHOROU\n";
			valorMelhorSolucao = valhorSolucaoAtual;
			melhorSolucao = operacoesUteis->copiar_solucao(solucaoAtual);			
			contadorMelhoras++;
			melhorSolucao.setIteracaoEncontrada(i);
			melhorSolucao.setContadorRefinamento(contadorRefinamento);
			//////cout << "melhorSolucao.getIteracaoEncontrada" << melhorSolucao.getIteracaoEncontrada() <<"\n";
			////cout << "MELHOR SOLUCAO: " << i << "\n";
			////cout <<"contadorRefinamento " <<  contadorRefinamento <<"\n";
		}
	}
	
 	Tabu tabuFinal  = procurar_melhor_solucao(melhorSolucao,valorMelhorSolucao);

 	resultado.associacao_turma_professor = tabuFinal.getSolucao().getAssociacaoTurmaProfessor();
 	resultado.associacao_slot_turma =  tabuFinal.getSolucao().getAssociacaoSlotTurma();
 	resultado.associacao_turma_sala =  tabuFinal.getSolucao().getAssociacaoTurmaSala();
	resultado.valorFOFinal =tabuFinal.getValorFO();
	resultado.quantidade_vezes_melhorada = contadorMelhoras;
	resultado.contadorRefinamento = tabuFinal.getSolucao().getContadorRefinamento();	
	resultado.iteracao_encontrada = tabuFinal.getSolucao().getIteracaoEncontrada();


		////cout << "REFINAMENTO final: "<< contadorRefinamento<<"\n";
	return resultado;
}

void  BuscaTabu2::gerarMelhorVizinho(Solucao* solucao,valores_quebraDia_quebraTurma valhorSolucaoAtual, vector<Professor*> professores, vector<Turma*> turmas, vector<Sala*> salas){
	valores_quebraDia_quebraTurma valorSolucaoAntes, valorSolucaoDepois;	
	//valorSolucaoAntes = valhorSolucaoAtual;
	bool flag  = true;	
		
	for(int i=0; i< maxIteracoesSemMelhora; i++){
		// PŔOBLEMA TA AQUI !
		//vizinhanca_professor_turma(solucao, professores);
		vizinhanca_professor_turma2(solucao, professores);
		//vizinhanca_professor_dia(solucao,professores,salas);

		valorSolucaoDepois =  avaliacao->calcularFO((*solucao).getAssociacaoTurmaProfessor(),(*solucao).getAssociacaoSlotTurma(), professores); 
				
		if((valorSolucaoDepois.relacaoProfessorTurma + valorSolucaoDepois.relacaoProfessorDia)  <  (valhorSolucaoAtual.relacaoProfessorTurma + valhorSolucaoAtual.relacaoProfessorDia)){						
			contadorRefinamento++;
			flag  = false;			
			break;
		}		
	}
	

	if(flag){
		//cout <<"ENTROU\n";
		(*solucao).setContadorRefinamento(contadorRefinamento);
		////cout << "REFINAMENTO SETADO: "<< contadorRefinamento<<"\n";
		contadorRefinamento = 0;
		criarTabu(operacoesUteis->copiar_solucao((*solucao)),valorSolucaoDepois);

		/*
			-  perturbação para visitar uma nova vizinhança!
			- Preciso construir uma perturbação em relação a dias coisa simples.
		*/		
		_2IndexDiferente indexDif;
		int maximo = (*solucao).getAssociacaoTurmaProfessor().size();
		indexDif  = operacoesUteis->gerarIndexDiferentes(maximo);		

		(*solucao).swap_entre_turmas(indexDif.index1, indexDif.index2);
		indexDif = operacoesUteis->gerarIndexDiferentes(maximo);		
		(*solucao).swap_entre_turmas(indexDif.index1, indexDif.index2);
		
	}	
}


void BuscaTabu2::criarTabu(Solucao solucao, valores_quebraDia_quebraTurma valhorSolucaol){
	int tamFila  = filaTabu.size();
	if(tamFila <  tamanhoMaxFila){		
		filaTabu.push_back(Tabu(solucao, valhorSolucaol));		
	}
}

void BuscaTabu2::vizinhanca_professor_dia(Solucao* solucao, vector<Professor*> professores, vector<Sala*> salas){	
	Professor * professor;
	int idSalaAntes;
	string codSala;
	vector<string> turmas_sala;			
	int siape_professor;
	AuxTrocaTurmas  troca_1;
	vector<int> id_dia_horario_ocupados_na_sala, id_dia_horario_sala_livre;
	vector<associacaoSlotTurma_indice> turmas_indice;
	vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala;

		/*
		Primeiro passo é pegar os professores com as suas turmas que estão alocadas fora do seu conjunto de dias 
		desejados.
		
		Método ta funcionando corretamente !
		*/
	map<int, vector<associacaoSlotTurma_indice>>  professores_com_turmas_fora_dos_dias  = operacoesUteis->get_professores_fora_dos_dias_preferiveis(professores, (*solucao).getAssociacaoTurmaProfessor(),(*solucao).getAssociacaoSlotTurma());
	/*
	 	Partindo de que existe professores com turmas alocadas em dias que eles não querem 
	 	vamos pegar o primeiro elemento desse map para tentar trabalhar 
	 	as turmas e remanejar para outros dias que resolva a quebra das restrições ProfessorXDia
	*/
	if(professores_com_turmas_fora_dos_dias.size() > 0){
		siape_professor = professores_com_turmas_fora_dos_dias.begin()->first;
		/*
			Como temos as turmas do professor siape_professsor que estão alocadas em dias que não são 
			do agrado dele vamos iterar nessa lista e tentar resolver uma por uma;			
		*/
		turmas_indice = professores_com_turmas_fora_dos_dias.begin()->second;

		if(turmas_indice.size() > 0){
				/*
					Irei percorrer todas essas turmas é vamos tentar alocar primeiramente na mesma sala que a turma está !
					turma_id tem:

						- associacaoSlotTurma  valor;
						- int indice;

					Caso não consigamos vamos tentar alocar em outra sala.
					*/
			for(auto& turma_id: turmas_indice){
				professor = getProfessorSiape(professores,siape_professor);
				if(professor != NULL){// todo cuidado é pouco rs
					idSalaAntes = getIdSaladaTurma((*solucao).getAssociacaoTurmaSala(),turma_id.valor.componenteCurricular, turma_id.valor.codSala);
					/*
						Se a sala existir vamos agora procurar nessa sala se tem uma lacuna dentro do universo de dias desejado pelo professor					
					*/
					if(idSalaAntes > -1){ // chave ok
						codSala  = (*solucao).getAssociacaoTurmaSala()[idSalaAntes].codSala;
						/*
						Tendo codigo da sala, posso pegar todos os id_dia_horario que estão associado a 
						essa sala é depois disso encontrar as lacunas que ainda existe na sala
						*/ 
						// MÉTODO get_id_dia_horario_componenteCurricular2 TA OK
						id_dia_horario_ocupados_na_sala = operacoesUteis->get_id_dia_horario_componenteCurricular2((*solucao).getAssociacaoSlotTurma(), codSala);
						if(id_dia_horario_ocupados_na_sala.size() <  20){ // chave ok
							/*
								O método encontrar_lacunas_na_matriz vai retornar as lacunas vazias que existe 
								dentro da sala! 
								partindo isso agora precisamos converter id_dia_horario para (dia e horario ) que vão ser 
								guardados na variavel lacunas_que_podem_receber_turmas_na_sala
							*/

							id_dia_horario_sala_livre = encontrar_lacunas_na_matriz(id_dia_horario_ocupados_na_sala);

							if(id_dia_horario_sala_livre.size() > 0){// chave ok
								lacunas_que_podem_receber_turmas_na_sala  =  operacoesUteis->converter_id_dia_horario_em_dia_horario(id_dia_horario_sala_livre);	
								if(lacunas_que_podem_receber_turmas_na_sala.size() > 0 ){ // chave ok
									/*
									Apos encontrar as lacunas que podem ser usadas dentro da sala 
									preciso comparar essas lacunas comos dias preferiveis que o professor gosta de trabalhar 
									para encontrar alguma compatibilidade.							
									*/
									troca_1 = 	comparar_vetor_lacuna_dias_desejados(lacunas_que_podem_receber_turmas_na_sala, professor->getDiasPreferiveisTrabalho());

									if(troca_1.dia > -1){ // chave ok
								// EXISTE UMA LACUNA QUE AGRADA O PROFESSOR ENTÃO VAMOS ALOCAR NESSA LACUNA									
										(*solucao).atualizar_relacao_slot_turma(turma_id.indice, troca_1.dia, troca_1.horario,operacoesUteis->getNumeroMatrizMapeamento(troca_1.horario,troca_1.dia) ,turma_id.valor.componenteCurricular, codSala);
									}else{
										procurara_nova_sala(professor->getDiasPreferiveisTrabalho(),turma_id, solucao, codSala,  salas);
										////////cout << "PROCURAR SALA 4\n";
									}		
								}else{
									procurara_nova_sala(professor->getDiasPreferiveisTrabalho(),turma_id, solucao, codSala, salas);
									// VOU ENCIAR PARA ALOCAR EM OUTRA SA
									////////cout << "PROCURAR SALA 3\n";
								}
							}else{
								procurara_nova_sala(professor->getDiasPreferiveisTrabalho(),turma_id, solucao, codSala,  salas);	
								////////cout << "PROCURAR SALA 2\n";
							}

						}else{
							procurara_nova_sala(professor->getDiasPreferiveisTrabalho(),turma_id, solucao, codSala,  salas);
							////////cout << "PROCURAR SALA 1\n";
							// VOU ENCIAR PARA ALOCAR EM OUTRA SALA 
						}
					}else{
						////////cout << "idSalaAntes NÃO EXISTE\n";
					}
				}else{
					////////cout <<"PROFESSOR NULL\n";
				}
			}
		}
	}
}

void BuscaTabu2::procurara_nova_sala(vector<int> diasDesejados, associacaoSlotTurma_indice turma_id, Solucao* solucao, string codSala, vector<Sala*> salas){
	vector<string> turmas_sala;	
	vector<int>  id_dia_horario_ocupados_na_sala, id_dia_horario_sala_livre;
	int conseguiu_trocar  = 1,idSala;
	string codSalaPesquisada;
	AuxTrocaTurmas  troca;
	vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala;
		/*
			conseguiu_trocar = 
								- 1 conseguiu trocar 
								- 0 não conseguiu trocar
	*/
	for(auto& sala : salas){
		codSalaPesquisada = sala->getCodSala();
		if(codSalaPesquisada != codSala){
			/*
				Como já tenho todos os id_dia_horario que estão ocupados dentro da sala codSalaPesquisada agora posso 
				descobrir quais lacunas estão livres para assim pesquisar se dentro dessas lacunas existe uma lacuna 
				que agrade o professor dos diasDesejados.
			*/

			id_dia_horario_ocupados_na_sala = get_id_dia_horario_dentro_de_uma_sala((*solucao).getAssociacaoSlotTurma(),codSalaPesquisada);
			if(id_dia_horario_ocupados_na_sala.size() <  20){
					/*
						O método encontrar_lacunas_na_matriz vai retornar as lacunas vazias que existe 
						dentro da sala! 
						partindo isso agora precisamos converter id_dia_horario para (dia e horario ) que vão ser 
						guardados na variavel lacunas_que_podem_receber_turmas_na_sala
					*/

				id_dia_horario_sala_livre = encontrar_lacunas_na_matriz(id_dia_horario_ocupados_na_sala);
				
				if(id_dia_horario_sala_livre.size() > 0){
					//imprimir(id_dia_horario_sala_livre);
					 /*
						PRECISO TESTAR ESSE MÉTODO CONVERTER_ID_DIA_HORARIO_EM_DIA_HORARIO PORQUE TA RETORNANDO MUITO VAZIO ESTRANHO DADO
						QUE id_dia_horario_sala_livre TEM É MAIOR QUE ZERO!
					 */

					lacunas_que_podem_receber_turmas_na_sala =  operacoesUteis->converter_id_dia_horario_em_dia_horario(id_dia_horario_sala_livre);	
					imprimir2(lacunas_que_podem_receber_turmas_na_sala);

					if(lacunas_que_podem_receber_turmas_na_sala.size() > 0){
					/*
								Apos encontrar as lacunas que podem ser usadas dentro da sala 
								preciso comparar essas lacunas comos dias preferiveis que o professor gosta de trabalhar 
								para encontrar alguma compatibilidade.							
				*/
						troca =comparar_vetor_lacuna_dias_desejados(lacunas_que_podem_receber_turmas_na_sala, diasDesejados);
						if(troca.dia > -1 ){							
							(*solucao).atualizar_relacao_slot_turma(turma_id.indice, troca.dia, troca.horario,operacoesUteis->getNumeroMatrizMapeamento(troca.horario,troca.dia) ,turma_id.valor.componenteCurricular, codSalaPesquisada);
							idSala = getIdSaladaTurma((*solucao).getAssociacaoTurmaSala(),turma_id.valor.componenteCurricular, codSala);
							(*solucao).remover_relacao_turma_sala(idSala);							
							(*solucao).adicionar_nova_relacao_turma_sala(codSalaPesquisada,  turma_id.valor.componenteCurricular);	
							conseguiu_trocar = 1;
							////////cout << "TROCO.DIA> 1\n";
							break;
						}else{
							////////cout << "[procurara_nova_sala] NAS LACUNAS LIVRES NÃO TEM UMA QUE AGRADE O PROFESSOR\n";
						}
					}else{

						////////cout << "[procurara_nova_sala] lacunas_que_podem_receber_turmas_na_sala VAZIO\n";	
					}					
				}else{
						////////cout << "[procurara_nova_sala] NÃO TEM LACUNAS QUE PODE RECEBER A TURAMA\n";
				}				
			}else{
				////////cout << "[procurara_nova_sala] SALA LOCATADA\n";
			}
		}
	}
}

void BuscaTabu2::vizinhanca_professor_turma2(Solucao* solucao, vector<Professor*> professores){
	map<int, vector<turma_id>> professores_turmas_nao_desejadas = operacoesUteis->get_professores_com_turmas_fora_das_preferiveis_com_posicao_no_vetor_de_relacoes(professores,(*solucao).getAssociacaoTurmaProfessor());
	/* Vamos sempre trabalhar pegando o primeiro da lista do map para trabalhar a vizinhança desse professor */
	int siape,idSala;	
	Professor* professorDonoTurma;
	vector<turma_id> turmas_nao_desejadas_professor1;
	if(professores_turmas_nao_desejadas.size() > 0){
	
		//funciona ok
		siape = professores_turmas_nao_desejadas.begin()->first;
		//funciona ok
		turmas_nao_desejadas_professor1 = professores_turmas_nao_desejadas.begin()->second;
		/*
			Agora vou percorrer toda as turmas que estão com esse professor que não são deles
			partindo disso preciso encontrar quem é o professor que é dono dessa turma!
		*/
		for(auto& troca_professor_1 : turmas_nao_desejadas_professor1){
			
			professorDonoTurma = getProfessor(professores,troca_professor_1.componenteCurricular);
			if(professorDonoTurma != NULL){
				////cout << "swap_entre_professores_turma\n";
				(*solucao).swap_entre_professores_turma(troca_professor_1, professorDonoTurma->getSiape());
			}
		}
	}
}

void BuscaTabu2::vizinhanca_professor_turma(Solucao* solucao, vector<Professor*> professores){
	
	map<int, vector<turma_id>> professores_turmas_nao_desejadas = operacoesUteis->get_professores_com_turmas_fora_das_preferiveis_com_posicao_no_vetor_de_relacoes(professores,(*solucao).getAssociacaoTurmaProfessor());

	/* Vamos sempre trabalhar pegando o primeiro da lista do map para trabalhar a vizinhança desse professor */
	int siape,idSala;

	Professor* professorDonoTurma;
	vector<turma_id> turmas_nao_desejadas_professor1;
	vector<turma_id> turmas_nao_desejadas_professor2;
	turma_id troca_professor_2;
	if(professores_turmas_nao_desejadas.size() > 0){

		//funciona ok
		siape = professores_turmas_nao_desejadas.begin()->first;
		//funciona ok
		turmas_nao_desejadas_professor1 = professores_turmas_nao_desejadas.begin()->second;
		/*
			Agora vou percorrer toda as turmas que estão com esse professor que não são deles
			partindo disso preciso encontrar quem é o professor que é dono dessa turma!
		*/
		for(auto& troca_professor_1 : turmas_nao_desejadas_professor1){
			//funciona ok
			professorDonoTurma = getProfessor(professores,troca_professor_1.componenteCurricular);

			if(professorDonoTurma != NULL){
				/*
				Vamos verificar se o professor que é dono da turma está dentro do map que contem os 
				professores com lista de turmas que ele não deseja trabalhar.
				*/
				if(verificar_professor_na_lista_dos__com_turmas_indesejadas(professores_turmas_nao_desejadas,professorDonoTurma->getSiape())){				
					turmas_nao_desejadas_professor2 = professores_turmas_nao_desejadas[professorDonoTurma->getSiape()];
					/*
						Como tenho a lista de turmas não desejadas do professorVerificado e do professor que quer a turma 
						troca_professor_1 então vamos verificar se  dentro das preferiveis pelo professorVerificado está
						na lista indesejada pelo professor que quer a turma troca_professor_1 caso não tenha eu escolho qualquer
						turma lá dentro e faço a troca.
					*/
					//troca_professor_2= verificar_compatibilidade_entre_listas_indesejadas(turmas_nao_desejadas_professor2,getTurmasComFamiliaridadeProfessor(professores, siape));
					troca_professor_2 = verificar_compatibilidade_entre_listas_indesejadas2(turmas_nao_desejadas_professor2,getTurmasComFamiliaridadeProfessor(professores, siape));

					if(troca_professor_2.idPosicao > -1){ // SINAL QUE NÃO CONTEM FAMILIARIDADE !
						(*solucao).swap_entre_turmas_professores(troca_professor_1,troca_professor_2);	
					}else{
						(*solucao).swap_entre_professores_turma(troca_professor_1, professorDonoTurma->getSiape());
					}					
					////////////cout << "ENTROU AQUI BRUNO\n";
				}else{
					//////////cout << "AQUIIII\n";
					//////////////cout << "vou ter que procurar em toda no vector<associacaoTurmaProfessor> !!creio eu pela logica isso não sera necessário\n";
				}
			}else{
				//////////cout << "AQUI\n";
			}
		}
	}else{
		//////////cout << "AQUI 22\n";
	}
}

bool BuscaTabu2::verificar_professor_na_lista_dos__com_turmas_indesejadas(map<int, vector<turma_id>> professores_turmas_nao_desejadas, int siape){
	for (map<int, vector<turma_id>>::iterator i = professores_turmas_nao_desejadas.begin(); i != professores_turmas_nao_desejadas.end(); ++i){
		if(i->first == siape)
			return true;
	}
	return false;
}

Professor* BuscaTabu2::getProfessor(vector<Professor*> professores, string componente){
	for(auto& profe : professores){
		for(auto& turma: profe->getTurmasComFamiliaridade()){
			if(turma->getComponenteCurricular() == componente){
				return profe;
			}	
		}
	}
	return NULL;
}

turma_id BuscaTabu2::verificar_compatibilidade_entre_listas_indesejadas2(vector<turma_id> turmas_nao_desejadas_professor2, vector<Turma*> turmas_desejadas_professor1){

	for(auto& turma : turmas_desejadas_professor1){
		for(auto& id_componente: turmas_nao_desejadas_professor2){
			if(turma->getComponenteCurricular()  == id_componente.componenteCurricular )
				return id_componente;
		}
	}
	return turma_id(-1, "");
}

turma_id BuscaTabu2::verificar_compatibilidade_entre_listas_indesejadas(vector<turma_id> turmas_nao_desejadas_professor2, vector<Turma*> turmas_desejadas_professor1){	
	
	for(auto& turma : turmas_desejadas_professor1){
		for(auto& id_componente: turmas_nao_desejadas_professor2){
			if(turma->getComponenteCurricular()  == id_componente.componenteCurricular )
				return id_componente;
		}
	}

	int inicio =0;
	int final  = turmas_nao_desejadas_professor2.size();
	int id = operacoesUteis->gerar_numero_aleatorio(inicio, final);
	return turmas_nao_desejadas_professor2[id];
}

vector<Turma*> BuscaTabu2::getTurmasComFamiliaridadeProfessor(vector<Professor*> professores, int siape){
	vector<Turma*> vazia;
	for(auto& professor: professores){
		if(professor->getSiape() == siape)
			return professor->getTurmasComFamiliaridade();
	}
	return vazia;
}

/*
	Irá retornar 0 se tiver e 1 se não pertencer ao conjunto
*/

int BuscaTabu2::verificar_se_pertence(int  id_dia_horario, vector<int> id_dia_horario_sala){
	if((find(id_dia_horario_sala.begin(), id_dia_horario_sala.end(), id_dia_horario) != id_dia_horario_sala.end()) == false)
		return 1;
	else return 0;
}


vector<int> BuscaTabu2::encontrar_lacunas_na_matriz(vector<int> id_dias_horarios_sala){
	vector<int> resultado;
	for (int i= 1; i <=20; ++i){
		if(verificar_se_pertence(i, id_dias_horarios_sala) == 1){
			resultado.push_back(i);
		}
	}
	return resultado;
}

Professor* BuscaTabu2::getProfessorSiape(vector<Professor*> professores, int siape){
	for(auto& profe : professores){
		if(profe->getSiape() == siape)
			return profe;
	}
	return NULL;
}



int BuscaTabu2::getIdSaladaTurma(vector<associacaoTurmaSala> associacao_turma_sala, string componente, string codSala){
	int tamanho = associacao_turma_sala.size();	
	for (int i = 0; i < tamanho; i++){
		if(associacao_turma_sala[i].componenteCurricular == componente && associacao_turma_sala[i].codSala == codSala)
			return i;
	}
	return -1;
}

int BuscaTabu2::getIdSaladaTurma2(vector<associacaoTurmaSala> associacao_turma_sala, string componente){
	int tamanho = associacao_turma_sala.size();	
	for (int i = 0; i < tamanho; i++){
		if(associacao_turma_sala[i].componenteCurricular == componente)
			return i;
	}
	return -1;
}

AuxTrocaTurmas BuscaTabu2::comparar_vetor_lacuna_dias_desejados(vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala, vector<int> diasDesejados){
	for(auto& dia: diasDesejados){
		for(auto& lacuna: lacunas_que_podem_receber_turmas_na_sala){
			if(lacuna.dia  == dia) 
				return lacuna;
		}
	}
	return AuxTrocaTurmas(-1,-1);
}

/*
	Método vai receber o vetor com as associações entre turma e slot e retornara os id_dia_horario de todas as turmas que estão 
dentro de uma determina sala.

*/
vector<int> BuscaTabu2::get_id_dia_horario_dentro_de_uma_sala(vector<associacaoSlotTurma> alocacao_turma_slot, string codSalaPesquisada){
	vector<int> resultado;
	for(auto& turma_slot: alocacao_turma_slot){
		if(turma_slot.codSala == codSalaPesquisada){
			resultado.push_back(turma_slot.id_dia_horario);
		}
	}

	return resultado;
}

void BuscaTabu2::imprimir(vector<int> id_dia_horario_sala_livre){
	for(auto& d : id_dia_horario_sala_livre){
		//////////cout << " [" << d << "] ";
	}
}

void BuscaTabu2::imprimir2(vector<AuxTrocaTurmas> lacunas_que_podem_receber_turmas_na_sala){
	//////////cout << "\nimprimir2: \n";
	for(auto& p : lacunas_que_podem_receber_turmas_na_sala){
		//////////cout << " (Dia: " << p.dia << ","<< p.horario << ")";
	}
}



Tabu BuscaTabu2::procurar_melhor_solucao(Solucao solucao, valores_quebraDia_quebraTurma valorMelhorSolucao){
	int tam = filaTabu.size();
	int posiMelhorSolucao = -1;
	for (int i = 0; i < tam; ++i){
		if(( filaTabu[i].getValorFO().relacaoProfessorTurma +   filaTabu[i].getValorFO().relacaoProfessorDia )  
			<  
			(valorMelhorSolucao.relacaoProfessorTurma + valorMelhorSolucao.relacaoProfessorDia)){
			valorMelhorSolucao = filaTabu[i].getValorFO();
			posiMelhorSolucao = i;
		}
	}

	if(posiMelhorSolucao == -1){
		return Tabu(solucao,valorMelhorSolucao);
	}else{
		return filaTabu[posiMelhorSolucao];
	}
}
