#include "include/playfair.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int main(int argc, char *argv[]){
	if(argc!=3){
		std::cout << "Uso: ./playunfair <file-in> <file-out>" << std::endl;
		return 0;
	}
	std::fstream input, output;
	char *inputName, *outputName;
	std::string aux, key = "cachorro", crip; //a key vai vir do dicionario futuramente
	std::ostringstream text;

	inputName = argv[1];
	outputName = argv[2];
	input.open(inputName, std::ifstream::in);
	if(!input.good()){
		std::cout << "Nao foi possivel abrir o arquivo de entrada" << std::endl;
		return 0;
	}

	while(std::getline(input, aux))
		 text << aux;

	std::cout << text.str() << std::endl;
	//chamar play fair passando string e chave
	crip = playfair(text.str(), key);
	return 0;
}
