#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "stringToFloat.h"

float getFloat(char * str, int len){
	for(int i = 0; i < len; i++){
		if(isalpha(str[i])) return 100001;
	}
	int x = to_float(str, len);
	float* f = (float *)&x;
	float ret = *(f);
	if (ret > 100000) {return 100002;}
	else if (ret < 0.01 && ret > -0.01) {return 100003;}
	else if (ret < -100000) {return 100004;}
	else return ret;
}
