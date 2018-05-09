#include "include/playfair.h"


#define _charbit(X) (1 << (X - 'a'))
#define _pos(I,J) ((I)*5 + (J)%5)

//Base idea is to use an 32-bit int as mask to detect which char
// is already on the matrix
std::vector< char > createKM ( const std::string key){
	std::vector< char > mKey(25);
	std::string abc(key + "abcdefghijklmnopqrstuvwxyz");
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

			mKey[_pos(i,j)] = abc[si];
		}
	}
	return mKey;
}

std::string playfair(std::string text, const std::string key, int crypt){
	crypt=crypt+5;//Avoid operator % on negative numbers
	std::ostringstream ret;
	std::vector< char > mKey(createKM(key));
	/*for (int i=0; i<5; ++i){
		for (int j=0; j<5; ++j){
			std::cout << mKey[i*5 + j] << ' ';
		}
		std::cout << std::endl;
	}*/
	unsigned int indexT = 0;
	while(indexT <text.size() ){

		while(text[indexT] < 'a' || text[indexT] > 'z') ++indexT;
		char fst = text[indexT];
		while(text[indexT] < 'a' || text[indexT] > 'z') ++indexT;
		char snd = (++indexT< text.size())?text[indexT]:'x';
		++indexT;
		if (fst == snd){
			if(snd!='x'){
				snd = 'x';
			}else{
				snd='q';
			}
			--indexT;
		}

		int iFst, iSnd;

		for (int i=0; i<25; ++i){
			if(mKey[i] == fst ||
					((fst == 'i' || fst=='j') &&
					 (mKey[i] =='i' || mKey[i]=='j'))){
				iFst=i;
			}
			if(mKey[i] == snd ||
					((snd == 'i' || snd =='j') &&
					 (mKey[i] =='i' || mKey[i]=='j'))){
				iSnd=i;
			}
		}

		char retfst,retsnd;

		if(iFst/5 == iSnd/5){
			retfst= mKey[_pos( iFst/5, (iFst+crypt))];
			retsnd= mKey[_pos( iSnd/5 ,(iSnd+crypt))];
		}else if(iFst%5 == iSnd%5){
			retfst= mKey[_pos( ((iFst/5)+crypt)%5 , (iFst))];
			retsnd= mKey[_pos( ((iSnd/5)+crypt)%5 , (iSnd))];
		}else{
			retfst = mKey[ _pos( iFst/5, iSnd)];
			retsnd = mKey[_pos ( iSnd/5, iFst)];
		}
		ret << retfst << retsnd;
	}
	return ret.str();
}
