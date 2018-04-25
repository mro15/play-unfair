#include "include/playfair.h"
#include <fstream>

void parser(std::string &text){
	text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
}

int main(int argc, char *argv[]){
	if(argc!=3){
		std::cout << "Uso: ./playunfair <file-in> <file-out>" << std::endl;
		return 0;
	}
	std::fstream input, output;
	char *inputName, *outputName;
	std::string aux="", key = "cachorro", crip; //a key vai vir do dicionario futuramente
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

	std::cout<<text.str()[2] << std::endl;
	crip = text.str();
	parser(crip);
	std::cout << crip << std::endl;
	crip = playfair(crip, key);
	std::cout << crip << std::endl;
	return 0;
}
