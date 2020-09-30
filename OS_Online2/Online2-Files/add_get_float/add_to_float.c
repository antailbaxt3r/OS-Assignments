#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include "add_to_float.h"

SYSCALL_DEFINE2(add_to_float, char __user*, s, int, len){

	char str[50];
	int ieee[32];	
	int negative,j,base,mantissa,lzeroes,x,a[32],ii,k,temp,start,  end,exp,baseEnd,count,mod,rem,i,finalExp,expBin[8], mantBin[23],after1;
	long ret, p, err;
	
    err = strncpy_from_user(s, str, sizeof(s));
	negative = 0;
    j = 0;
    if(str[0] == '-') {
		negative = 1;
		j = 1;
    }
    base = 0;
    for(; (str[j] != '.' && j < len); j++){
		base *= 10;
		base += str[j] - '0';
    }
    
    mantissa = 0;
    lzeroes = 0;
    j++;
    x = j;
    for(; x < len; x++){
		if(str[x] == '0') {lzeroes++;}
		else {break;}
    }
    for(; j < len; j++){
		mantissa *= 10;
		mantissa += str[j] - '0';
    }
    for(ii = 0; ii < 32; ii++) a[ii] = 0;
    for(k=0;base>0;k++){  
		a[k]=base%2;
		base=base/2;    
    }
    end = k-1;
    start = 0;
    while (start < end){
		temp = a[start];   
		a[start] = a[end];
		a[end] = temp;
		start++;
		end--;
    }
    exp = k-1;
    baseEnd = k-1;
    temp = mantissa;
    count = lzeroes;
    while(temp > 0){
		count++;
		temp /= 10;
    }
    mod = 1;
    while(count > 0){
		mod = mod * 10;
		count--;
    }

    for(; k < 32; k++){
		mantissa = mantissa * 2;
		rem = mantissa / mod;
		a[k] = rem;
		mantissa = mantissa % mod;
		if(mantissa == 0) break;
    }
    
    finalExp = 127 + exp;
    ieee[0] = negative;

    for(i = 0; i < 8; i++) expBin[i] = '0';
    for(i = 7; i >=0; i--){
		expBin[i]=finalExp%2;
		finalExp=finalExp/2;
    }

    for(i = 0; i < 32; i++){
		if(a[i] == 1){
			after1 = i+1;
			break;
		}
    }
    for(i = 0; i < 23; i++){
		mantBin[i] = a[after1 + i];
    }

    for(i = 1; i < 9; i++) ieee[i] = expBin[i-1];
    for(i = 9; i < 32; i++) ieee[i] = mantBin[i-9];
    ret = 0;
    p = 1;
    for(i = 0; i < 32; i++){
		ret = ret + (ieee[i] * p);    
		p *= 2;
    }
    return ret;
}
