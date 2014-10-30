//Codigo para el 1er punto de la tarea 6 de metodos computacionales 2014-2.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//Runge Kutta 4to Orden
#define h 0.01
#define A 30.0
#define B 1.0
#define C 30.0
#define D 1.0

// Este codigo fue modificado del codigo para RungeKuttaFourthOrderStep creado por forero (github) para ipython.
// link: http://nbviewer.ipython.org/github/forero/ComputationalMethods/blob/master/notes/SecondOrder_ODE.ipynb


double func1(double xa, double ya_1, double  ya_2); //func_prime_1
double func2(double xb, double yb_1, double  yb_2); //func_prime_2
double * RungeKutta4os(double  xc_old, double yc1_old, double  yc2_old);

int main(int argc, char **argv){ 
	
	

	if(argc<3){
		printf("We need at least 2 arguments beside the name of the executable!\n EXIT!\n");
		exit(1);
	} //tomado del tutorial de c
	
	double *lista;
	lista = malloc(3*sizeof(double));

	// Aqui se define un valor con el cual se haran los pasos o saltos
	double  minimo_t = 0.0; // valor minimo de tiempo	
	double  maximo_t = 1.0; // valor maximo de tiempo
	double  n_points; // variable que define el numero de punto en el intervalo t minimo a t maximo
	n_points = (maximo_t - minimo_t)/ h;
	n_points = (int)(n_points);
	
	double  equis[(int)(n_points)];
	double  ye[(int)(n_points)];
	double  te[(int)(n_points)];
	
	
	te[0]   = minimo_t ; 
	equis[0] = atof(argv[1]);
	ye[0] =  atof(argv[2]);
	

	
	
	

	
	
	FILE *in;
	
	

	
	int i;
	char filename[100]="poblaciones_x0_y0.dat";
    sprintf(filename, "poblaciones_%d_%d.dat", atoi(argv[1]),atoi(argv[2]));
	printf("Writing to file: %s\n", filename);
	/*opens the file, writes, closes the file*/
	in = fopen(filename,"w");
	
	if(!in){
		
		printf("problems opening the file %s\n", filename);
		exit(1);
	
	}

	

	
	//Generando los t,x,y
	
	for(i=1; i < (n_points) ; i++){
		
		lista = RungeKutta4os(te[i-1],equis[i-1],ye[i-1]);
		te[i]=lista[0];
		equis[i]=lista[1];
		ye[i] = lista[2];

	}
	
	
	
	for(i=0; i < (int)(n_points) ; i++){
		fprintf(in, "%f %f %f\n", te[i], equis[i], ye[i]);
	}
	
	fclose(in);
	
	
	
	
	
	
	return 0;

}



double  func1(double xa, double  ya_1, double  ya_2){
	double  Ya_1,Ya_2,respuestaa;

	Ya_1 = ya_1;
	Ya_2 = ya_2;
	respuestaa = A*Ya_1 - B*Ya_1*Ya_2;
	return respuestaa;
	
}

double  func2(double  xb, double  yb_1, double yb_2){
	double  Yb_1, Yb_2,respuestab;

	Yb_1 = yb_1;
	Yb_2 = yb_2;
	respuestab = -C*Yb_2 + D*Yb_1*Yb_2;
	return respuestab;
	
}


double * RungeKutta4os(double  xc_old, double  yc1_old, double yc2_old){
	// espaciamiento
	
    double  k_1_prime1, k_1_prime2;
    double  x1, y1_1, y2_1; //first step variable definition
   
    
    double k_2_prime1, k_2_prime2;
    double  x2,y1_2, y2_2; // second step variable definition
    
    double  k_3_prime1, k_3_prime2;
    double x3,y1_3, y2_3; // third step variable definition
    
    double  k_4_prime1, k_4_prime2;
    double  average_k_1 , average_k_2 ;// fourth step variable definition
    
    double  x_new,y_1_new, y_2_new ;
    
    // obtengo los varoles de k_1_prime 1 y 2 pasandole un puntero a las funciones definidas anteriormente
    k_1_prime1 = func1(xc_old, yc1_old, yc2_old);
    k_1_prime2 = func2(xc_old, yc1_old, yc2_old);
    
    
    //first step
    x1 = (xc_old) + (h/2.0);
    y1_1 = (yc1_old) + ((h/2.0) * k_1_prime1);
    y2_1 = (yc2_old) + ((h/2.0) * k_1_prime2);
    
    k_2_prime1 = func1(x1, y1_1, y2_1);
    k_2_prime2 = func2(x1, y1_1, y2_1);
    
    //second step
    x2 = xc_old + (h/2.0);
    y1_2 = yc1_old + ((h/2.0) * k_2_prime1);
    y2_2 = yc2_old + ((h/2.0) * k_2_prime2);
    
    k_3_prime1 = func1(x2, y1_2, y2_2);
    k_3_prime2 = func2(x2, y1_2, y2_2);
    
    
    //third step
    x3 = xc_old + (h);
    y1_3 = yc1_old + (h * k_3_prime1);
    y2_3 = yc2_old + (h * k_3_prime2);
    
    k_4_prime1 = func1(x3, y1_3, y2_3);
    k_4_prime2 = func2(x3, y1_3, y2_3);
    
    //fourth step
    
    average_k_1 = (k_1_prime1 + (2.0*k_2_prime1) + (2.0*k_3_prime1) + k_4_prime1)/6.0;
    average_k_2 = (k_1_prime2 + (2.0*k_2_prime2) + (2.0*k_3_prime2) + k_4_prime2)/6.0;
    
    x_new = xc_old + (h);
    y_1_new = yc1_old + (h*average_k_1);
    y_2_new= yc2_old + (h*average_k_2);
    
    // return x_new, y_1_new, y_2_new ---> esta sintaxis no funciona en c por lo cual hay que redefinir las variables punteros que entraron
    
    double *array;
    
    array = malloc(3*sizeof(double));
    array[0] = x_new;
   
    array[1] = y_1_new ;
    array[2] = y_2_new;
    
    return array;

}

