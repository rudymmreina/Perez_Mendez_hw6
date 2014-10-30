#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//Runge Kutta 4to Orden




float func_prime_1(float xa, float ya_1, float ya_2,float aa, float ba, float ca, float da);
float func_prime_2(float xb, float yb_1, float yb_2,float ab, float bb, float cb, float db);

float RungeKuttaFourthOrderStep(float xc_old, float yc1_old, float yc2_old,float ac, float bc, float cc, float dc);

int main(int argc, char **argv){ 
	
	float A = 30.0;
	float B = 1.0;
	float C = 30.0;
	float D = 1.0;

	if(argc<3){
		printf("We need at least 2 arguments beside the name of the executable!\n EXIT!\n");
		exit(1);
	}


	float espacio = 0.01;
	float minimo_t = 0.0;
	float maximo_t = 1.0;
	float n_points;
	n_points = (maximo_t - minimo_t)/espacio;
	float equis[(int)(n_points)];
	float ye[(int)(n_points)];
	float te[(int)(n_points)];
	int i;
	te[0]   = minimo_t ; 
	equis[0] = atoi(argv[1]);
	ye[0] =  atoi(argv[2]);
	
	float variable = 0.0;
	int contador = 1;
	int contador1 = 0;
	int j;
	
	for( j =0; j < (int)(n_points);j++){
		
		te[j] = te[j] + 0.01*j;
		
	} 
	while(contador< (int)(n_points)){
		
		te[contador], equis[contador], ye[contador] = RungeKuttaFourthOrderStep(te[contador-1],equis[contador-1],ye[contador-1],A,B,C,D);
		variable = variable + espacio;
		contador = contador +1;
	
	}
	
	
	FILE *in;
	
	

	
	
	char filename[100]="poblaciones_x0_y0.dat";
    sprintf(filename, "poblaciones_%d_%d.dat", atoi(argv[1]),atoi(argv[2]));
	printf("Writing to file: %s\n", filename);
	/*opens the file, writes, closes the file*/
	in = fopen(filename,"w");
	
	if(!in){
		
		printf("problems opening the file %s\n", filename);
		exit(1);
	
	}
	
	for(i=0; i < (int)(n_points) ; i++){
		fprintf(in, "%f %f %f\n", te[i], equis[i], ye[i]);
	}
	
	fclose(in);
	
	
	
	
	
	
	return 0;

}



float func_prime_1(float xa, float ya_1, float ya_2,float aa, float ba, float ca, float da){
	
	float Xa, Ya_1, Ya_2,respuestaa;
	Xa = xa;
	Ya_1 = ya_1;
	Ya_2 = ya_2;
	respuestaa = Aa*Ya_1 - Ba*Ya_1*Ya_2;
	return respuestaa;
	
}

float func_prime_2(float xb, float yb_1, float yb_2,float ab, float bb, float cb, float db){
	
	float Xb, Yb_1, Yb_2,respuestab;
	Xb = xb;
	Yb_1 = yb_1;
	Yb_2 = yb_2;
	respuestab = C*Yb_2 + D*Yb_1*Yb_2;
	return respuestab;
	
}


float RungeKuttaFourthOrderStep(float xc_old, float yc1_old, float yc2_old,float ac, float bc, float cc, float dc){
    
    float Xc_old ;
    float Yc1_old ;
    float Yc2_old ;
    float Ac1;
    float Bc;
    float  Cc ;
    float Dc;
    float kc_1_prime1;
    float kc_1_prime2;
    float kc_2_prime1;
    float kc_2_prime2 ;
    float kc_3_prime1 ;
    float kc_3_prime2 ;
    float acverage_k_1 ;
    float acverage_k_2 ;
    float kc_4_prime1;
    float kc_4_prime2;
    float xc_new;
    float yc_1_new;
    float Yc_2_new;
    float yc_2_new;
    float Xc_new, Yc_1_new ;
    float xc1, xc2, xc3 ,hc , yc1_1, yc2_1, yc1_2, yc2_2, yc1_3, yc2_3; 
    Ac1 = ac;
    Bc = bc;
    Cc = cc;
    Dc = dc;
    Xc_old = xc_old ; 
    Yc1_old = yc1_old ; 
    Yc2_old = yc2_old ; 	
    float h = 0.01;
    kc_1_prime1 = func_prime_1(xc_old,yc1_old, yc2_old,Ac1, Bc, Cc, Dc);
    kc_1_prime2 = func_prime_2(xc_old,yc1_old, yc2_old,Ac1, Bc, Cc, Dc);
    
    //first step
    xc1 = xc_old+ (h/2.0) ;
    yc1_1 = yc1_old + (h/2.0) * kc_1_prime1 ;
    yc2_1 = yc2_old + (h/2.0) * kc_1_prime2 ;
    kc_2_prime1 = func_prime_1(xc1, yc1_1, yc2_1,Ac1, Bc, Cc, Dc) ;
    kc_2_prime2 = func_prime_2(xc1, yc1_1, yc2_1,Ac1, Bc, Cc, Dc) ;
    
	//second step
    xc2 = xc_old + (h/2.0) ;
    yc1_2 = yc1_old + (h/2.0) * kc_2_prime1 ;
    yc2_2 = yc2_old + (h/2.0) * kc_2_prime2 ;
    kc_3_prime1 = func_prime_1(xc2, yc1_2, yc2_2,Ac1, Bc, Cc, Dc) ;
    kc_3_prime2 = func_prime_2(xc2, yc1_2, yc2_2,Ac1, Bc, Cc, Dc) ;
    
    
    //third
    xc3 = xc_old + h ;
    yc1_3 = yc1_old + h * kc_3_prime1 ;
    yc2_3 = yc2_old + h * kc_3_prime2 ;
    kc_4_prime1 = func_prime_1(xc3, yc1_3, yc2_3,Ac1, Bc, Cc, Dc) ;
    kc_4_prime2 = func_prime_2(xc3, yc1_3, yc2_3,Ac1, Bc, Cc, Dc) ; 
    
    //fourth step
    acverage_k_1 = (1.0/6.0)*(kc_1_prime1 + 2.0*kc_2_prime1 + 2.0*kc_3_prime1 + kc_4_prime1) ; 
    acverage_k_2 = (1.0/6.0)*(kc_1_prime2 + 2.0*kc_2_prime2 + 2.0*kc_3_prime2 + kc_4_prime2) ;
    
    Xc_new = xc_old + h ;
    Yc_1_new = yc1_old + h * acverage_k_1 ; 
    Yc_2_new= yc2_old + h * acverage_k_2 ;
    
    
    return Xc_new, Yc_1_new, Yc_2_new;


}
