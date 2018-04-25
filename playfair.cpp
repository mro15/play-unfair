#include "include/playfair.h"


#define _charbit(X) (1 << (X - 'a'))

//Base idea is to use an 32-bit int as mask to detect which char
// is already on the matrix
std::vector< char > createKM ( const std::string key){
	std::vector< char > mKey(25);
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

			mKey[i*5 + j] = abc[si];
		}
	}
	return mKey;
}

std::string playfair(std::string text, const std::string key){
	std::ostringstream ret;
	std::vector< char > mKey(createKM(key));
	for (int i=0; i<5; ++i){
		for (int j=0; j<5; ++j){
			std::cout << mKey[i*5 + j] << ' ';
		}
		std::cout << std::endl;
	}

	int indexT = -1;
	char fst = text[++indexT];
	char snd = text[++indexT];
	if (fst == snd && snd != 'x'){
		snd = 'x';
		--indexT;
	}

	int iFst, iSnd;

	for (int i=0; i<25; ++i){
		if(mKey[i] == fst){
			iFst=i;
		}
		if(mKey[i] == snd){
			iSnd=i;
		}
	}
	char retfst,retsnd;
	retfst = mKey[iFst/5 + iSnd%5]

	//TODO:change
	return text;
}
