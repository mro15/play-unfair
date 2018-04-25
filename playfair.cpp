#include "include/playfair.h"


#define _charbit(X) (1 << (X - 'a'))


std::vector< std::vector<char> > createKM ( const std::string key){
	std::vector< std::vector<char> > mKey(5, std::vector<char>(5));
	std::string abc(key + "abcdefghijklmnopqrstuvxwyz");
	int mask =0;
	//mask with 32 bits for the 25 letter alfabet
	int si=0;
	for(int i=0; i<5;  ++i){
		for(int j=0; j<5; ++j){
			while( (_charbit(abc[si]) & mask)!=0 )
				++si;
			mask = mask | _charbit(abc[si]);

			if (abc[si] == 'i' || abc[si] == 'j'){
				mask = mask | (_charbit('j') | _charbit('i'));
			}

			mKey[i][j] = abc[si];
		}
	}
	return mKey;
}

std::string playfair(std::string text, const std::string key){
	std::vector< std::vector <char> > mKey(createKM(key));
	for (int i=0; i<5; ++i){
		for (int j=0; j<5; ++j){
			std::cout << mKey[i][j] << ' ';
		}
		std::cout << std::endl;
	}


	//TODO:change
	return text;
}
