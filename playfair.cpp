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

			mKey[i*5 + j] = abc[si];
		}
	}
	return mKey;
}

std::string playfair(std::string text, const std::string key){
	std::ostringstream ret;
	std::vector< char > mKey(createKM(key));
	/*for (int i=0; i<5; ++i){
		for (int j=0; j<5; ++j){
			std::cout << mKey[i*5 + j] << ' ';
		}
		std::cout << std::endl;
	}*/
	unsigned int indexT = 0;
	int repetitions=0;
	while(indexT <text.size() ){
		char fst = text[indexT];
		char snd = (++indexT< text.size())?text[indexT]:'x';
		std::cout << fst << " " << snd << std::endl;
		++indexT;
		if (fst == snd){
			if(snd!='x'){
				snd = 'x';
			}else{
				snd='q';
			}
			--indexT;
			++repetitions;
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
			retfst= mKey[_pos( iFst/5, (iFst+1))];
			retsnd= mKey[_pos( iSnd/5 ,(iSnd+1))];
		}else if(iFst%5 == iSnd%5){
			std::cout << iFst << " " << iFst/5 << " " << ((iFst/5)+1)%5  << std::endl;
			retfst= mKey[_pos( ((iFst/5)+1)%5 , (iFst))];
			std::cout << retfst << " " << _pos( ((iFst/5)+1)%5 , (iFst)) << std::endl;
			retsnd= mKey[_pos( ((iSnd/5)+1)%5 , (iSnd))];
		}else{
			retfst = mKey[ _pos( iFst/5, iSnd)];
			retsnd = mKey[_pos ( iSnd/5, iFst)];
		}
		ret << retfst << retsnd;
	}
	std::cout << ret.str() << std::endl;
	//TODO:change
	return ret.str();
}
