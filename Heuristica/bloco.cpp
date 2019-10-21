#include "bloco.hpp"

Bloco::Bloco(int code, vector<Sala*> sala){
    codeBloco = code;
    salas = sala;
}
Bloco::Bloco(){

}

Bloco::~Bloco(){

}


Bloco::Bloco(int code){
	codeBloco = code;
}
vector<Sala*> Bloco::getSalas(){
    return salas;
}

int Bloco::getCodeBloco(){
    return codeBloco;
}

void Bloco::setCodeBloco(int code){
    codeBloco = code;
}

void Bloco::addSala(Sala *sala){
	sala->setAlocadaBloco(1);
    salas.push_back(sala);
}


int Bloco::procurarSala(string codSala){
	int s, count = salas.size();
	for (s = 0; s < count; s++){
		if(salas[s]->getCodSala()== codSala) 
			return s;		
	}
	return -1;
}