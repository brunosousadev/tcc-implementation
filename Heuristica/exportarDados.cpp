#include "exportarDados.hpp"


ExportarDados::ExportarDados(){

}

ExportarDados::~ExportarDados(){

}

bool ExportarDados::exportarBlocos(vector<Bloco*> blocos, int codigo_arquivo, int i, int j, int k){
	int count = blocos.size();
	string pasta = ""+to_string(i)+"_"+to_string(j)+"_"+to_string(k)+"/";
	ofstream f_out;

	for (int b = 0; b < count; b ++){		
		//f_out.open("Saidas/"+to_string(codigo_arquivo)+"_Bloco "+to_string(blocos[i]->getCodeBloco())+ "_.html");
		f_out.open("Saidas/"+pasta+to_string(codigo_arquivo)+"_Bloco "+to_string(blocos[b]->getCodeBloco())+ "_.html");		
		f_out << "<html> <meta charset=\"utf-8\"/> <body>";	
		f_out << exportarBloco(blocos[b]);		
		f_out << "</body> </html>";	
		f_out.close();				
	}
	return true;
}

string ExportarDados::exportarBloco(Bloco *b){
	int i,count = b->getSalas().size();
	string acumulador="";
	acumulador+="<table border=1> <tr bgcolor=#004159> \n";
	acumulador+= "<td align=center><b><font color=white size=4> Bloco " + to_string(b->getCodeBloco()) +" </font></b></td></tr>\n";
	acumulador+="<tr> <td align=left border=0> <table border=1> <tr  color=White> <td ></td>\n";
	for (i = 0; i < count; i++){		
		acumulador+= exportarSala(b->getSalas()[i]);
		acumulador+="<br/><br/>\n";	 
	}	
	return acumulador;
}

bool ExportarDados::exportarSalas(vector<Sala*> salas, int i, int j, int k){
	int s, count = salas.size();
	ofstream f_out;
	string pasta = ""+to_string(i)+"_"+to_string(j)+"_"+to_string(k)+"/";
	for (s = 0; s < count; s++){		
		f_out.open("Saidas/"+pasta+salas[s]->getNomeSala() +" - "+ salas[s]->getCodSala()+".html");
		f_out << "<html> <meta charset=\"utf-8\"/> <body>";	
		f_out << exportarSala(salas[s]);		
		f_out << "</body> </html>";	
		f_out.close();			
	}
	return true;
}

string ExportarDados::exportarSala(Sala* s){
	int i,j,count=5;	
	string acumulador = "";

	acumulador+="<table border=1> <tr bgcolor=#004159> \n";
	acumulador+= "<td align=center><b><font color=white size=4>" + s->getNomeSala() +" - "+s->getCodSala() +" </font></b></td></tr>\n";
	acumulador+="<tr> <td align=left border=0> <table border=1> <tr  color=White> <td ></td>\n";
	acumulador+="<td bgcolor=#65ABC4 width=500 align=center border=0><b><font color=white size=4> Segunda</font></b></td>\n";	
	acumulador+="<td bgcolor=#65ABC4 width=500 align=center border=0><b><font color=white size=4> Terça</font></b></td>\n";
	acumulador+="<td bgcolor=#65ABC4 width=500 align=center border=0><b><font color=white size=4> Quarta</font></b></td>\n";
	acumulador+="<td bgcolor=#65ABC4 width=500 align=center border=0><b><font color=white size=4> Quinta</font></b></td>\n";
	acumulador+="<td bgcolor=#65ABC4 width=500 align=center border=0><b><font color=white size=4> Sexta</font></b></td>\n";
	acumulador+="</tr>\n";

	for (i = 0; i < (count -1); i++){	

		if(i==2){			
			acumulador+="<td height=3 width=5 border=0 align=center bgcolor=\"#000000\"><font size=1 color=white>17h00 - 17h30</font></td>\n";
			acumulador+="<td height=3 width=5 border=0 align=center colspan=\"5\" bgcolor=\"#000000\" ><font size=2 color=white> Jantar </font> </td>\n";
		}

		acumulador+="<tr>\n"; 
		acumulador+="<td bgcolor=\"004159\" width=150 align=center>\n"; 
		acumulador+="<font size=2 color=white> <b><i>"+horario(i)+"</i> </b></font>\n";	
		acumulador+="</td>\n";	
		for (j = 0; j < count; j++){
			if(s->gradeHorario[i][j].status){
				acumulador+="<td width=5 border=0 align=center> "+ s->gradeHorario[i][j].turma->getNomeTurma() +"</br> ["+to_string(s->gradeHorario[i][j].turma->getSiapeProfessor())+"] </br> ["+s->gradeHorario[i][j].turma->getNomeCaracteristicaTurma()+"]</td>\n";	
			}else{
				acumulador+="<td width=5 border=0 align=center>""</td>\n";	
			}		
		}
		acumulador+="</tr>\n";
	}
	acumulador+="</table></td></tr>\n";
	acumulador+= "</table>\n";

	return acumulador;

}

string ExportarDados::horario(int id){
	switch(id){
		case 0:
		return "13h00 - 15h00";			
		case 1:
		return "15h00 - 17h00";
		case 2:
		return "17h30 - 19h30";
		case 3:
		return "19h30 - 21h30";
		default:
		return "";
	}
}

vector<associacaoSlotTurma> ExportarDados::getTurmasSala(vector<associacaoSlotTurma> associacao_slot_turma, string codSalaPesquisada){
	vector<associacaoSlotTurma>  resultado;
	int qnt = associacao_slot_turma.size();
	for (int i = 0; i < qnt; ++i){
		if(associacao_slot_turma[i].codSala == codSalaPesquisada)
			resultado.push_back(associacao_slot_turma[i]);
	}

	return resultado;
}

int ExportarDados::getIdSala(vector<Sala*> salas, string codSalaP){
	int qntSalas = salas.size();
	for (int i = 0; i < qntSalas; i++){
		if(salas[i]->getCodSala() == codSalaP)
			return i;
	}
	return -1;
}

int ExportarDados::getIdTurma(vector<Turma*> turmas, string componenteCurricularP){
	int qntTurmas  = turmas.size();
	for (int i = 0; i < qntTurmas; i++){
		if(turmas[i]->getComponenteCurricular() == componenteCurricularP){
			return i;
		}
	}
	return -1;
}

void ExportarDados::converter_estrutura_para_salas(vector<Bloco*> blocos, vector<Sala*> salas, vector<Turma*> turmas ,Dados resultado, int codigo_arquivo, int i, int j , int k, int qntProfessores){

	int qntTurmas  = turmas.size();

	vector<string> blocos1 {"1","2","3","4","5"};
	vector<string> blocos2 {"6","7","8","9","10"};

	cout << "blocos: " << blocos.size() <<"\n";

	map<string, vector<associacaoSlotTurma>> sala_com_suas_turmas;	
	vector<associacaoSlotTurma> auxiliar;
	string codSala;
	for(auto& sala: salas){
		codSala = sala->getCodSala();
		auxiliar =  getTurmasSala(resultado.associacao_slot_turma, codSala);
		if(auxiliar.size() > 0) {
			sala_com_suas_turmas.insert(pair<string,vector<associacaoSlotTurma>>(codSala,auxiliar));
		}
	}
	// PREENCHER NA SALA 
	int posicaoSala, posicaoTurma;
	for (map<string, vector<associacaoSlotTurma>>::iterator i = sala_com_suas_turmas.begin(); i != sala_com_suas_turmas.end(); ++i){
		codSala = i->first;
		posicaoSala = getIdSala(salas , codSala);
		if(posicaoSala > -1){
			for(auto& ts:  i->second){
				posicaoTurma = getIdTurma(turmas,ts.componenteCurricular);
				if(posicaoTurma> -1){					
					salas[posicaoSala]->alocarTurma(turmas[posicaoTurma],ts.horario, ts.dia);				
				}
			}
		}
	}


	for(auto& b1: blocos1){
		posicaoSala = getIdSala(salas , b1);
		if(posicaoSala > -1){
			blocos[0]->addSala(salas[posicaoSala]);
		}		
	}

	for(auto& b2: blocos2){
		posicaoSala = getIdSala(salas , b2);
		if(posicaoSala > -1){
			blocos[1]->addSala(salas[posicaoSala]);
		}		
	}

 	exportarBlocos(blocos, codigo_arquivo, i,j,k);
 	exportarRelacaoProfessor_turma(resultado,codigo_arquivo,i,j,k);
 	exportarInformacoesAdicionais(resultado.valorFOConstrucao, resultado.valorFOFinal, resultado.tempo_construcao_inicial, resultado.tempo_total_de_solucao, resultado.quantidade_vezes_melhorada, codigo_arquivo, i, j, k, qntTurmas, qntProfessores, resultado.contadorRefinamento,resultado.iteracao_encontrada,
 			resultado.possivel_quantidade_total_quebra_na_relacao_professor_turma, resultado.possivel_quantidade_total_quebra_na_relacao_professor_dias, resultado.status_da_solucao);
}

void ExportarDados::exportarInformacoesAdicionais(valores_quebraDia_quebraTurma valorFOInicial, valores_quebraDia_quebraTurma valorFOFinal,float tempo_construcao_inicial, float tempo_total_de_solucao,int quantidade_vezes_melhorada, int codigo_arquivo, int i, int j , int k, int qntTurmas, int qntProfessores, int contadorRefinamento, int iteracao_encontrada, int possivel_quantidade_total_quebra_na_relacao_professor_turma, int possivel_quantidade_total_quebra_na_relacao_professor_dias,  bool status){
	/*
	// QUANTIAS VEZES EU REFINEI 
	int contadorRefinamento;
	// QUAL ITERAÇÃO ENCONTREI 
	int iteracao_encontrada;
	*/
	string acumulador = "";
	acumulador+="<table border=1>\n";
	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>Tempo de Construção Inicial </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(tempo_construcao_inicial)+"</td>\n";
  	acumulador+="</tr>\n";

  	unsigned int relacaoProfessorTurmaInicial = valorFOInicial.relacaoProfessorTurma;
	unsigned int relacaoProfessorDiaInicial = valorFOInicial.relacaoProfessorDia;

	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Na Construção ] Função Objetivo Total </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorTurmaInicial+relacaoProfessorDiaInicial)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Na Construção ] Relação Professor x Turma </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorTurmaInicial)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Na Construção ] Relação Professor x Dias </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorDiaInicial)+"</td>\n";
  	acumulador+="</tr>\n";
 




  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>Tempo de Construção Final  </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(tempo_total_de_solucao)+"</td>\n";
  	acumulador+="</tr>\n";

	unsigned int relacaoProfessorTurmaFinal = valorFOFinal.relacaoProfessorTurma;
	unsigned int relacaoProfessorDiaFinal = valorFOFinal.relacaoProfessorDia;

	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Final  ] Função Objetivo Total </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorTurmaFinal+relacaoProfessorDiaFinal)+"</td>\n";
  	acumulador+="</tr>\n";


  	 acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Final ] Relação Professor x Turma </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorTurmaFinal)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Final ] Relação Professor x Dias </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(relacaoProfessorDiaFinal)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantas Vezes Melhorei a FO </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(quantidade_vezes_melhorada)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantidades de Turmas </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(qntTurmas)+"</td>\n";
  	acumulador+="</tr>\n";


  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantidades de professores </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(qntProfessores)+"</td>\n";
  	acumulador+="</tr>\n";


  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantidades foi feito refinamento </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(contadorRefinamento)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Iteração encontrada a melhor solucação </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(iteracao_encontrada)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantidade de possíveis quebras professor x Turma </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(possivel_quantidade_total_quebra_na_relacao_professor_turma)+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantidade de possíveis quebras professor x Dias </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(possivel_quantidade_total_quebra_na_relacao_professor_dias)+"</td>\n";
  	acumulador+="</tr>\n";


  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Situação da alocação </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
	if(status)
    	acumulador+="<td align=center>Viável</td>\n";
	else
		acumulador+="<td align=center>Inviável</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="</table>\n"; 
    ofstream f_out;
    string pasta = ""+to_string(i)+"_"+to_string(j)+"_"+to_string(k)+"/";
    f_out.open("Saidas/"+pasta+to_string(codigo_arquivo)+"_informacoesFinais_.html");
    f_out << "<html> <meta charset=\"utf-8\"/> <body>";	    
	f_out << acumulador;
	f_out << "</body> </html>";	

}

void ExportarDados::exportarRelacaoProfessor_turma(Dados resultados, int codigo_arquivo, int i, int j, int k){
	//vector<associacaoTurmaProfessor> associacao_turma_professor

	string pasta = ""+to_string(i)+"_"+to_string(j)+"_"+to_string(k)+"/";
	string nome_arquivo  = "Saidas/"+pasta+to_string(codigo_arquivo)+"relacao_professor_turma.txt";
	string nome_arquivo2 = "Saidas/"+pasta+to_string(codigo_arquivo)+"relacao_turma_sala.txt";
	string nome_arquivo3 = "Saidas/"+pasta+to_string(codigo_arquivo)+"relacao_turma_slot.txt";
	ofstream f_out;
	f_out.open(nome_arquivo);
	for(auto& turma_professor: resultados.associacao_turma_professor){
		f_out << turma_professor.siape<<","<<turma_professor.componenteCurricular<<"\n";
	}		
	f_out.close();

	ofstream f_out2;
	f_out2.open(nome_arquivo2);
	for(auto& turma_sala: resultados.associacao_turma_sala){
		f_out2<< turma_sala.codSala <<","<< turma_sala.componenteCurricular<<"\n";
	}
	f_out2.close();

	ofstream f_out3;
	f_out3.open(nome_arquivo3);
	for(auto& tuma_slot:resultados.associacao_slot_turma){
		f_out3 << tuma_slot.codSala <<","<<tuma_slot.id_dia_horario << "," <<tuma_slot.dia << ","<<tuma_slot.horario <<","<<tuma_slot.componenteCurricular<<"\n";
	}
	f_out3.close();

}



	/*
	//cout << "1 - [converter_estrutura_manipulacao_para_estrutura_para_exportar]\n";
	OperacoesUteis* op= new OperacoesUteis();
	vector<Bloco*>  resultado = copiarBloco(blocos);		
	//cout << "2 - [converter_estrutura_manipulacao_para_estrutura_para_exportar]\n";
	vector<Sala*> salasAux = copiarConteudoSalas(salas);
	//cout << "3 - [converter_estrutura_manipulacao_para_estrutura_para_exportar]\n";
	// ATÉ ESSA LINHA TA OK
	map<string, vector<associacaoSlotTurma>> turmas_por_sala = organizar_as_turmas_por_sala(salas, dados.associacao_slot_turma);
	cout << "4 - [converter_estrutura_manipulacao_para_estrutura_para_exportar]\n";
	int idSala;
	Turma * turmaAux;
	string componenteCurricular;
	for (map<string, vector<associacaoSlotTurma>>::iterator i = turmas_por_sala.begin(); i != turmas_por_sala.end(); ++i){
		idSala = getIdSala(salasAux, i->first);
		cout << "MAP: " <<  i->first << "\n";
	
		cout << "TAMANHO: "<< i->second.size() <<"\n"; // erro ta aqui
		for(auto& tur: i->second){

			cout << "Antes [getTurma] "<<tur.componenteCurricular<< " \n";
			turmaAux = getTurma(tur.componenteCurricular, turmas);
			cout << "depois [getTurma]\n";

			if(turmaAux != NULL){
				salasAux[idSala]->alocarTurma(copiarConteudoTurma(turmaAux,getSiapeProfessorAlocadoTurma(dados.associacao_turma_professor,tur.componenteCurricular)), tur.horario, tur.dia);
			}
		}
	}
	
	//cout << "5 - [converter_estrutura_manipulacao_para_estrutura_para_exportar]\n";

	map<int, vector<string>> professores_turmas  =  op->get_turmas_pro_professor(professores, dados.associacao_turma_professor);
	int idProfessor;

	for (map<int, vector<string>>::iterator i = professores_turmas.begin(); i != professores_turmas.end(); ++i){
		idProfessor = getIdProfessor(professores, i->first);
		if(idProfessor > -1){
			for(auto& t: i->second)
				professores[idProfessor]->addTurmaAlocada(getTurma(t,turmas));
		}
	}

	delete(op);
	*/

/*

bool ExportarDados::exportarDadosSolucao2(Dados resultado, int codigo_arquivo, vector<Bloco*> blocos, vector<Sala*> salas, vector<Turma*> turmas){
	//cout << "[INICIO ] EXPORTANDO SOLUÇÃO \n";

	return true;

}
	
bool ExportarDados::exportarDadosSolucao(Tabu* informacoesFinais, float tempoDeExecucao, int codigo_arquivo){
	//cout << "[INICIO ] EXPORTANDO SOLUÇÃO \n";
	
    exportarBlocos(informacoesFinais->getSolucao(),codigo_arquivo);
  
  	string acumulador = "";
	acumulador+="<table border=1>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>Tempo de Execução</th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(tempoDeExecucao)+"</td>\n";
  	acumulador+="</tr>\n";

  	//ValoresFO valoresFinal  = informacoesFinais->getTabuFinal()->getValorFuncaoObjetivo();

  	ValoresFO valoresConstrucao = informacoesFinais->getValorFuncaoObjetivoContrucao();

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Na Construção ] Função Objetivo Total </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(valoresConstrucao.getTotal())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Na Construção ] Relação Professor x Turma </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(valoresConstrucao.getAcumuladorPenalidadeProfessorTurma())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4>[ Na Construção ] Relação Professor x Dias </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(valoresConstrucao.getAcumuladorPenalidadeProfessorDias())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Solução Final ] Função Objetivo Total </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(valoresFinal.getTotal())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Solução Final ] Relação Professor x Turma </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    //acumulador+="<td align=center>"+to_string(informacoesFinais->getAcumuladorPenalidadeProfessorTurmaTabuFinal())+"</td>\n";
    acumulador+="<td align=center>"+to_string(valoresFinal.getAcumuladorPenalidadeProfessorTurma())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> [ Solução Final ] Relação Professor x Dias </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    //acumulador+="<td align=center>"+to_string(informacoesFinais->getAcumuladorPenalidadeProfessorDiasTabuFinal())+"</td>\n";
    acumulador+="<td align=center>"+to_string(valoresFinal.getAcumuladorPenalidadeProfessorDias())+"</td>\n";
  	acumulador+="</tr>\n";
  	
  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Iteração que encontrou a FO </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(informacoesFinais->getTabuFinal()->getIteracao())+"</td>\n";
  	acumulador+="</tr>\n";

  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantas Vezes Melhorei a FO </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(informacoesFinais->getQuantasVezesMelhoreiFO())+"</td>\n";
  	acumulador+="</tr>\n";


  	acumulador+="<tr bgcolor=#004159>\n";
    acumulador+="<th align=center><b><font color=white size=4> Quantas Vezes Melhorei Dentro da Procura de Vizinhança </th>\n";
  	acumulador+="</tr>\n";
	acumulador+="<tr>\n"; 
    acumulador+="<td align=center>"+to_string(informacoesFinais->getContadorMelhorasDentroDaProcuraVizinhanca())+"</td>\n";
  	acumulador+="</tr>\n";

	acumulador+="</table>\n";
	
    ofstream f_out;


    f_out.open("Saidas/"+to_string(codigo_arquivo)+"_informacoesFinais_.html");
    f_out << "<html> <meta charset=\"utf-8\"/> <body>";	    
	f_out << acumulador;
	f_out << "</body> </html>";	


	//cout << "[FIM] EXPORTANDO SOLUÇÃO \n";

    return true;

}
*/