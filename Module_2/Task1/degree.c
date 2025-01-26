#include "degree.h"

int degree(int ratio){
	unsigned int tmp = 1;
	for (int i = 0; i < ratio; i++){
		tmp = tmp * N;
	}
	return tmp;
}
