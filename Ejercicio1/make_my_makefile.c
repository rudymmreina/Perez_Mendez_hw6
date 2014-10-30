// Code for automatically writing the makefile.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	FILE *in;
	int i;
	int var;
	int test;
	int numero;
	numero = 31;
	char filename[100]="makefile";
	printf("Writing to file: %s\n", filename);
	/*opens the file, writes, closes the file*/
	in = fopen(filename,"w");
	if(!in){
		printf("problems opening the file %s\n", filename);
		exit(1);
	}
	fprintf(in,"all:");
	
	for(i=1;i<31;i++){
		
		fprintf	(in,"poblaciones_%d_20.pdf ", i);
	}
	
	fprintf(in,"\n");
	
	for(i=1;i<31;i++){
	
		fprintf	(in,"poblaciones_%d_20.pdf: poblaciones_%d_20.dat\n	python plot_poblaciones.py $^\npoblaciones_%d_20.dat :  runge_kutta.x plot_poblaciones.py \n	./runge_kutta.x %d 20\n", i,i,i,i );
	}
	
	fprintf(in,"\n");
	fprintf(in,"\nclean:\n	rm -f *.pdf\n	rm -f *.dat");
	fclose(in);
}
