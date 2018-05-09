#include "include/playunfair.h"
#include <fstream>


int main(int argc, char *argv[]){
	if(argc!=4){
		std::cout << "Uso: ./playunfair <file-in> <file-out> <dicionarion>" << std::endl;
		return 0;
	}
	std::fstream input, output, dict;
	char *inputName, *outputName, *dictName;
	std::string aux="", key, crip; //a key vai vir do dicionario futuramente
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

	//TODO: tirar caracteres especiais
	std::cout<<text.str()[2] << std::endl;
	crip = text.str();
	parser(crip);
	//std::cout << crip << std::endl;

	dict.open(dictName, std::ifstream::in);
	if(!dict.good()){
		std::cout << "Nao foi possivel abrir o dicionario" << std::endl;
		return 0;
	}

	//TODO: if filter returns accepted print key and text in file
	while(std::getline(dict, aux)){
		keys << aux;
		key = keys.str();
		crip = playfair(crip, key, DECRYPT);
		std::cout << crip << std::endl;
		std::cout << key << std::endl;
		keys.str("");
		keys.clear();
		filter(crip, key); //chamar filtro para cada key
	}

	//crip = playfair(crip, key, DECRYPT);
	//std::cout << crip << std::endl;
	return 0;
}

void parser(std::string &text){
	text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
}

int filter(std::string text, const std::string key){
	//TODO: if ( 4 primeiras letras sem vogal ||
	//           3 char -('o') iguais seguidos ||
	//           5 consoantes ||
	//           7 vogais ||
	//           'q' + !'u' ||
	//           ('c'|'d'|'f'|'h'|'k'|'p'|'q'|'w'|'y') + !(vogal|'r'|'h')
	//
	//          )
	//         { elimina texto: muda pra proxima chave}

	return ACCEPTED;
}
