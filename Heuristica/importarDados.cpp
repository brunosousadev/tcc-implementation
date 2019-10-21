#include "importarDados.hpp"

ImportarDados::ImportarDados(){

}
ImportarDados::~ImportarDados(){

}

bool  ImportarDados::executar(int id_file){
	
	string line,EMPTY="",firstStopMarker="-",secondStopMarker="*",thirdStopMarker=">";
	char *p;
	int i=0, codigo;
	string componeteCurricular;	
	const char *separator=",";	
	Turma* turma;
    int count_line =0,size=10;  
    ifstream myfile(string("Entradas/"+to_string(id_file)+".txt")); // ifstream = padrão ios:in
    if (myfile.is_open()){
		while(!myfile.eof()){
			getline(myfile,line); 
			switch (count_line){
				  case 0:   // Capiturando os SIAPE dos professores.      OK [ TESTADO ESTRUTURA]                              
                    //cout << "[switch]=[Capiturando os SIAPE dos professores.]" << "\n";  
                    p = formatarDado(separator,line);
                    while(p!=0){                        
                    	professores.push_back(new Professor(strtol(p,NULL, size),"Professor"));                    	
                    	p = strtok(NULL,separator);                     
                    }                     
                    break; 
                    case 1:// CAPITURANDO OS NUMEROS DE CADA TURMA  
                     p = formatarDado(separator,line);
                     while(p!=0){                     	                     
                     	turmas.push_back(new Turma(p,"turma "+to_string(strtol(p,NULL, size))));
                     	p = strtok(NULL,separator);                     	
                 	}
                    break; 
                    case 2:// CAPITURANDO A CARGA HORÁRIA PRATICA DA TURMA  
                    i =0;
                    p = formatarDado(separator,line);
                     while(p!=0){
                     	turmas[i++]->setCreditoPratico(strtol(p,NULL, size));
                     	p = strtok(NULL,separator);                     	
                 	}
                    break;                   
                    case 3:// CAPITURANDO A CARGA HORÁRIA TEORICO DA TURMA  
                    i=0;
                    p = formatarDado(separator,line);
                     while(p!=0){
                     	turmas[i++]->setCreditoTeorico(strtol(p,NULL, size));
                     	p = strtok(NULL,separator);                     	
                 	}
                    break;  
                    case 4: // CONJUNTO DE DIAS DA SEMANA
                    p = formatarDado(separator,line);
                    while(p!=0){
                    	informacoesAdicionais.addDiaSemana(strtol(p,NULL, size));
						p = strtok(NULL,separator);      
                    }
                    break;      
                    case 5: //Representa os dias que são feriados 
					p = formatarDado(separator,line);
                    while(p!=0){
                    	informacoesAdicionais.addDiaSemanaComMuitoFeriado(strtol(p,NULL, size));
						p = strtok(NULL,separator);      
                    }
                    break; 
                    case 6: // Slots de horário
                    p = formatarDado(separator,line);
                    while(p!=0){
                    	informacoesAdicionais.addSlotHorario(strtol(p,NULL, size));
						p = strtok(NULL,separator);      
                    }
                    break; 
                    case 7://Salas de aulas  OK [ TESTADO ESTRUTURA] 
                    //Sala(string cod, int tipo);
                    p = formatarDado(separator,line);

                    while(p!=0){
                    	i = strtol(p,NULL, size);
                    	if(i == 5 || i == 10)	
                    		salas.push_back(new Sala(p,1));
                    	else 
                    		salas.push_back(new Sala(p,0));
						p = strtok(NULL,separator);      
                    }
                    break;         
			}// SWITCH     
			// Conjunto de turmas que o professor p tem familiaridade 
			if(verificarLinha(firstStopMarker,line)){
				line = removerMarcador(line); // REMOVENDO O SIMBOLO DA LINHA  
				// VERIFICAR SE TEM CODIGO DA TURMA 
				 if(line != EMPTY){
				 	codigo  = getCodigo(line, separator);

				 	line = removerMarcador(line); // REMOVENDO O SIMBOLO DA LINHA  
				 	line = removerMarcador(line); // REMOVENDO O SIMBOLO DA LINHA  
				 	line = removerMarcador(line); // REMOVENDO O SIMBOLO DA LINHA  

				 	p = formatarDado(separator,line);
				 	while(p!=0){
				 		componeteCurricular = p;                            
				 		turma = getTurma(componeteCurricular);
				 		if(turma != NULL){
				 			adicionarTurmasProfessor(codigo,turma);
				 		}
				 		p = strtok(NULL,separator); 
				 	}
				 }
			}
			//dias preferível
               // VERIFICANDO SE NA LINHA TEM *
			if(verificarLinha(secondStopMarker,line)){                
				line = removerMarcador(line);                
				if(line != EMPTY){ 
					codigo  = getCodigo(line, separator);
					line = removerMarcador(line);
                    line = removerMarcador(line);
                    line = removerMarcador(line);
                     p = formatarDado(separator,line);
                    while(p!=0){                        
                    	adicionarDiasPrefeirveisProfessor(codigo, strtol(p,NULL, size));
                    	p = strtok(NULL,separator);
                    }
				}
			}
			// CAPITURAR A CARGA HORÁRIA DE CADA PROFESSOR
                // VERIFICANDO SE NA LINHA TEM >  
			if(verificarLinha(thirdStopMarker, line)){
				line = removerMarcador(line);
				if(line != EMPTY){ 
					codigo  = getCodigo(line, separator);

					line = removerMarcador(line);
                    line = removerMarcador(line);
                    line = removerMarcador(line); 
                    p = formatarDado(separator,line);
                        while(p!=0){
                        adicionarCargaHorariaProfessor(codigo, strtol(p,NULL, size));
                         p = strtok(NULL,separator);   
                        }
				}
			}
			 count_line++;
		}
    }else{
        return false;
    } 

    return carregarBlocos();
}

vector<Bloco*> 			ImportarDados::getBlocos(){
	return blocos;
}

vector<Professor*> 		ImportarDados::getProfessores(){
	return professores;
}

vector<Turma*> 			ImportarDados::getTurmas(){
	return turmas;
}

InformacoesAdicionais 	ImportarDados::getInformacoesAdicionais(){
	return informacoesAdicionais;
}

vector<Sala*>			ImportarDados::getSalas(){
	return salas;
}


char* ImportarDados::formatarDado(const char *separator, string line){
	char *cstrLine;
	cstrLine = new char[line.length()+1];        
	strcpy(cstrLine,line.c_str());    
    return strtok (cstrLine,separator); // split do c++            
}

bool ImportarDados::verificarLinha(string markupCharacter, string linha){
	if (linha.find(markupCharacter) != string::npos)  return true;
    else return false;
}

string ImportarDados::removerMarcador(string linha){
	return linha.replace(0,1,"");
}

int ImportarDados::getCodigo(string linha, const char* separator){
	char* p = formatarDado(separator, linha);
	return strtol(p,NULL, 10); 
}

Turma* ImportarDados::getTurma(string componente){
	int qntTurmas  = turmas.size();
	for (int i = 0; i < qntTurmas; ++i){
		if(turmas[i]->getComponenteCurricular() == componente){
			return turmas[i];
		}		
	}
	return NULL;
}

void ImportarDados::adicionarTurmasProfessor(int siape, Turma* turma){
	for(auto& professor : professores){
		if(professor->getSiape() == siape){
			professor->adicionarTurmaComFamiliaridade(turma);
		}
	}
}

void ImportarDados::adicionarDiasPrefeirveisProfessor(int siape, int dia){
	for(auto& professor : professores){
		if(professor->getSiape() == siape){            
			professor->adicionarDiaPreferivei(dia);
		}
	}
}

void ImportarDados::adicionarCargaHorariaProfessor(int siape, int horaTrabalho){
	for(auto& professor : professores){
		if(professor->getSiape() == siape){
			professor->setCargHorariaTrabalho(horaTrabalho);
		}
	}
}

bool ImportarDados::carregarBlocos(){
    //cout << "[CARREGANDO OS BLOCOS]" <<endl;
    string line, marcador="-";
    vector<string> valores;
    vector<Sala*> salasAux;
    int id;
    ifstream meuArquivo ("Entradas/blocos.txt",ios::in);
    if (meuArquivo.is_open()){ 
        while(!meuArquivo.eof()){                   
                getline(meuArquivo,line);
                valores = tokenizacaoString(line,true);
                if(verificarLinha(marcador,valores[1])){
                   salasAux = getSalasBloco(tokenizacaoString(valores[1],false));
                }else{
                   id = getIdSala(valores[1]);
                   if(id > -1){                    
                    salasAux.push_back(salas[id]);
                   }
                }                    
                blocos.push_back(new Bloco(atoi(valores[0].c_str()),salasAux));           
        }
         meuArquivo.close();
    }else{
        return false;
    }
    return true;
 }    
  

  int ImportarDados::getIdSala(string codigo){
    int i, count = salas.size();   
    for( i = 0; i < count; i++){        
        if(salas[i]->getCodSala() == codigo)
            return i;
    }
    return -1;    
}

vector<string> ImportarDados::tokenizacaoString(string linha,bool op){    
    istringstream tokenizer { linha };
    string token;    
    vector<string> tokens;    
    if (op){
        while (getline(tokenizer, token, ','))
            tokens.push_back(token);
    }else{
        while (getline(tokenizer, token, '-'))
            tokens.push_back(token);
    }      
    return tokens;
}


vector<Sala*> ImportarDados::getSalasBloco(vector<string> codigos){
    vector<Sala*> resultado;
    int count = codigos.size(), id,i;
    
    for(i = 0; i < count; i++){    
        id = getIdSala(codigos[i]);
        if(id >-1){
            resultado.push_back(salas[id])
;        }
    }
    return resultado;
}