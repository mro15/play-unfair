#include "include/playunfair.h"
#include <fstream>


int main(int argc, char *argv[]){
	if(argc!=3){
		std::cout << "Uso: ./playunfair <file-in> <dicionarion>" << std::endl;
		return 0;
	}
	std::fstream input, output, dict;
	char *inputName, *dictName;
	std::string aux="", key, crip;
	std::ostringstream text, keys;

	inputName = argv[1];
	dictName = argv[2];

	input.open(inputName, std::ifstream::in);
	if(!input.good()){
		std::cout << "Nao foi possivel abrir o arquivo de entrada" << std::endl;
		return 0;
	}

	while(std::getline(input, aux))
		 text << aux;

	crip = text.str();
	parser(crip);
	//std::cout << crip << std::endl;

	dict.open(dictName, std::ifstream::in);
	if(!dict.good()){
		std::cout << "Nao foi possivel abrir o dicionario" << std::endl;
		return 0;
	}

	while(std::getline(dict, aux)){
		keys << aux;
		key = keys.str();
		std::string cypher = playfair(crip, key, DECRYPT);
		if(filter(cypher)==ACCEPTED){
			std::cout << key << ": " << cypher << std::endl;
		}
		keys.str("");
		keys.clear();
	}

	//std::cout << crip << std::endl;
	return 0;
}

void parser(std::string &text){
	text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
}

int filter(std::string text){
	//TODO: if ( 4 primeiras letras sem vogal ||
	//           3 char -('o') -('e') -('a') iguais seguidos ||
	//           6 consoantes ||
	//           7 vogais ||
	//           'q' + !'u' + !vogal ||
	//           ('b'|'c'|'d'|'f'|'h'|'k'|'p'|'q'|'t'|'w'|'y') + !(vogal|'r'|'h'|'l') ||
	//					 ('nh' + vogal || 'ch' + vogal) ||
	//           ultima letras b, c, d (download), f, g, h, k, p (hip hop), q, v (tv), w (show), y
	//          )
	//         { elimina texto: muda pra proxima chave}
	if(filter1(text) == REJECTED)
		return REJECTED;
	else if(filter2(text) == REJECTED)
		return REJECTED;
	else if(filter3(text) == REJECTED)
		return REJECTED;
	else if(filter4(text) == REJECTED)
		return REJECTED;
	else if (filter5(text) == REJECTED)
		return REJECTED;
	else if (filter6(text) == REJECTED)
		return REJECTED;
	else if (filter7(text) == REJECTED)
		return REJECTED;
	else
		return filter8(text);
}

int isVowel(char c){
	int result;
	result = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
	return result;
}

int filter1(std::string text){
	int rej = REJECTED;
	for(int i=0; i<4; ++i){
		if(isVowel(text[i])){
			rej = ACCEPTED;
			break;
		}
	}
	return rej;
}

int filter2(std::string text){
	size_t i, j;
	int rej = ACCEPTED;
	for(i=0; i<text.size()-3; ++i){
		char l = text[i];
		int lim=3, cont=0;
		if (( l=='o') || (l=='e') || (l=='a'))
			continue;
		for(j=i+1; j<i+lim; ++j){
			if(text[j]=='x'){
				++lim;
				continue;
			} else if (text[j] == l){
				++cont;
				continue;
			} else if (text[j] != l){
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

int filter3(std::string text){
	size_t i, j;
	int rej = ACCEPTED;
	for(i=0; i<text.size()-6; ++i){
		int lim = 5, cont = 0;
		char l = text[i];
		if(isVowel(l))
			continue;
		for(j=i+1; j<i+lim; ++j){
			if(text[j]=='x'){
				++lim;
				continue;
			} else if (!isVowel(text[j])){
				++cont;
			} else if(isVowel(text[j])){
				break;
			}
		}
		if(cont==4){
			rej = REJECTED;
			break;
		}
	}
	return rej;
}

int filter4(std::string text){
	size_t i, j;
	int rej = ACCEPTED;
	for(i=0; i<text.size()-7; ++i){
		int lim = 7, cont = 0;
		char l = text[i];
		if(isVowel(l))
			++cont;
		for(j=i+1; j<i+lim; ++j){
			if(text[j]=='x'){
				++lim;
			}else if(isVowel(text[j])){
				++cont;
			}else if(!isVowel(text[j])){
				break;
			}
		}
		if(cont==7){
			rej = REJECTED;
			break;
		}
	}
	return rej;
}

int filter5(std::string text){
	size_t i;
	int rej = ACCEPTED;
	for (i=0; i<text.size()-2; ++i){
		if(text[i]=='q'){
			if(text[i+1]!='u'){
				rej = REJECTED;
				break;
			}else if(!isVowel(text[i+2])){
				rej = REJECTED;
				break;
			}
		}
	}
	return rej;
}

int filter6(std::string text){
	//           ('b'|'c'|'d'|'f'|'h'|'k'|'p'|'q'|'t'|'w'|'y') + !(vogal|'r'|'h'|'l') ||
	size_t i;
	int rej = ACCEPTED;
	for (i=0; i<text.size()-1; ++i){
		if(text[i]=='b' || text[i]=='c' || text[i]=='d' || text[i]=='f' ||
			text[i]=='h' || text[i]=='k' || text[i]=='p' || text[i]=='q' ||
			text[i]=='t' || text[i]=='w' || text[i]=='y'){
			if(!isVowel(text[i+1]) && text[i+1]!='r' && text[i+1]!='h' && text[i+1]!='l' && text[i+1]!='m'){
				rej = REJECTED;
				break;
			}
		}
	}
	return rej;
}

int filter7(std::string text){
	size_t i;
	int rej = ACCEPTED;
	for (i=0; i<text.size()-2; ++i){
		if((text[i]=='n' || text[i]=='c') && text[i+1]=='h'){
			if(!isVowel(text[i+2])){
				rej = REJECTED;
				break;
			}
		}
	}
	return rej;
}

int isF(char c){
	int result = 0;
	result = (c == 'b' || c == 'c' || c == 'd' || c == 'f' || c == 'g' ||
						c == 'h' || c == 'k' || c == 'p' || c == 'q' || c == 'v' ||
						c == 't' || c == 'w' || c == 'y');
	return result;
}

int filter8(std::string text){
	//            ultima letras b, c, d (download), f, g, h, k, p (hip hop), q, v (tv), w (show), y
	size_t i = text.size() -1;
	if (isF(text[i]))
		return REJECTED;
	return ACCEPTED;
}
