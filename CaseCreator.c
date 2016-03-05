#include<stdio.h>
#include<stdlib.h>


#define NUM_UPBOUND 10001

#define DATATYPE 2
//1 for same order
//2 for reverse order
//3 for random order
int main(int argc,char *argv[]){
	int num[NUM_UPBOUND] = {};
	int t, j, i;
	srand((unsigned int)time(0) );
	
	int Nsize = rand() % 9900  + 1000;

	printf("%d\n", Nsize);
	if(DATATYPE == 1){
		for(i = 0; i < Nsize; i++){
			printf("%d ", i);
		}
		for(i = 0; i < Nsize; i++){
			printf("%d ", i);
		}
	}else if(DATATYPE == 2){
		for(i = 0; i < Nsize; i++){
			printf("%d ", i);
		}
		for(i = 0; i < Nsize; i++){
			printf("%d ", Nsize - i - 1);
		}
	}else if(DATATYPE == 3){
		for(i = 1; i <= Nsize; i++){
			t = rand() % Nsize;
			for(j = t; num[j]; j = j < Nsize - 1 ? j+1 : 0){	
			}
			num[j] = i;
			
		}
		for(i = 0; i < Nsize; i++){
			printf("%d ", num[i]);	
		}
		printf("\n\n\n");
		for(i = 0; i < Nsize; i++){
			t = rand() % Nsize;
			for(j = t; !num[j]; j = j < Nsize - 1 ? j + 1 : 0){	 
			}
			printf("%d ", num[j]);
			num[j] = 0;
		}
	}
}



