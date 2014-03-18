#include <stdio.h>
#include <stdlib.h>

#define N 42
char *buffer; 

void sprintfcb(char *res,int k){
    res[2] = '\n';
    res[1] = '0' + (k&((1<<3) - 1));
    res[0] = '0' + (k>>3);
}

void main(){
    unsigned int i = 0, j;
    buffer = malloc(sizeof(char) * 1024*3 + 1);
    for(i = 0; i < N; i += 1024) {
	for (j = 0; j < 1024 && i*1024+j < N; j++) { 
	    sprintfcb(&buffer[j*3], rand() % 64);
	}
	buffer[j*3]='\0';
	printf("%s", buffer);
    } 
    free(buffer);
}
