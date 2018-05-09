#include "include/playunfair.h"
#include <fstream>


int main(int argc, char *argv[]){
	if(argc!=3){
		std::cout << "Uso: ./playunfair <file-in> <key>" << std::endl;
		return 0;
	}
	std::fstream input, keyF;
	char *inputName, *keyName;
	std::string aux="", key, crip;
	std::ostringstream text, keys;

	inputName = argv[1];
	keyName = argv[2];

	input.open(inputName, std::ifstream::in);
	if(!input.good()){
		std::cout << "Nao foi possivel abrir o arquivo de entrada" << std::endl;
		return 0;
	}

	while(std::getline(input, aux))
		 text << aux;

	//TODO: tirar caracteres especiais
	crip = text.str();
	parser(crip);
	//std::cout << crip << std::endl;

	keyF.open(keyName, std::ifstream::in);
	if(!keyF.good()){
		std::cout << "Nao foi possivel abrir o dicionario" << std::endl;
		return 0;
	}

	//TODO: if filter returns accepted print key and text in file
	std::getline(keyF, aux);
	keys << aux;
	key = keys.str();
	crip = playfair(crip, key, CRYPT);
	std::cout << crip << std::endl;
	return 0;
}

void parser(std::string &text){
	text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
}

