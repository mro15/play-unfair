#include "include/playunfair.h"
#include <fstream>


int main(int argc, char *argv[]){
	if(argc!=4){
		std::cout << "Uso: ./playunfair <file-in> <file-out> <dicionarion>" << std::endl;
		return 0;
	}
	std::fstream input, output, dict;
	char *inputName, *outputName, *dictName;
	std::string aux="", key, crip;
	std::ostringstream text, keys;

	inputName = argv[1];
	outputName = argv[2];
	dictName = argv[3];

	input.open(inputName, std::ifstream::in);
	if(!input.good()){
		std::cout << "Nao foi possivel abrir o arquivo de entrada" << std::endl;
		return 0;
	}

	while(std::getline(input, aux))
		 text << aux;

	crip = text.str();
	parser(crip);

	dict.open(dictName, std::ifstream::in);
	if(!dict.good()){
		std::cout << "Nao foi possivel abrir o dicionario" << std::endl;
		return 0;
	}

	while(std::getline(dict, aux)){
		keys << aux;
		key = keys.str();
		crip = playfair(crip, key, DECRYPT);
		if(filter(crip)==ACCEPTED){
			std::cout << crip << std::endl;
			std::cout << key << std::endl;
		}
		keys.str("");
		keys.clear();
	}

	std::cout << crip << std::endl;
	return 0;
}

void parser(std::string &text){
	text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
}

int filter(std::string text){
	//TODO: if ( 4 primeiras letras sem vogal ||
	//           3 char -('o') iguais seguidos ||
	//           5 consoantes ||
	//           7 vogais ||
	//           'q' + !'u' ||
	//           ('c'|'d'|'f'|'h'|'k'|'p'|'q'|'w'|'y') + !(vogal|'r'|'h')
	//
	//          )
	//         { elimina texto: muda pra proxima chave}
	int i, j, rej = REJECTED;
	for(int i=0; i<4; ++i){
		if(text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' ||
			 text[i] == 'u'){
			rej = ACCEPTED;
			break;
		}
	}
	for(i=0; i<text.size()-3; ++i){
		char l = text[i];
		int lim=3, cont=0;
		if ( l=='o')
			continue;
		for(j=i+1; j<i+lim; ++j){
			if(text[j]=='x'){
				++lim;
				continue;
			} else if (text[j] == l){
				++cont;
				continue;
			} if (text[j] != l){
				break;
			}
		}
		if(cont == 2 ) {
			rej = REJECTED;
			break;
		}
	}

	return rej;
}
