#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//Runge Kutta 4to Orden




float func_prime_1(float x, float y_1, float y_2,float a, float b, float c, float d);
float func_prime_2(float x, float y_1, float y_2,float a, float b, float c, float d);

float RungeKuttaFourthOrderStep(float x_old, float y1_old, float y2_old);

int main(void){ 
	
	float A = 30.0;
	float B = 1.0;
	float C = 30.0;
	float D = 1.0;

	float espacio = 0.01;
	float minimo_x = 0.0;
	float maximo_x = 6.0;
	float n_points = 0.0;
	n_points = (maximo_x - minimo_x)/espacio;
	




}



float func_prime_1(float x, float y_1, float y_2,float a, float b, float c, float d){
	
	float X, Y_1, Y_2,respuesta, A,B,C,D;
	A = a ;
	B = b ; 
	C = c ;
	D = d ;
	X = x;
	Y_1 = y_1;
	Y_2 = y_2;
	respuesta = A*Y_1 - B*Y_1*Y_2;
	return respuesta;
	
}

float func_prime_2(float x, float y_1, float y_2,float a, float b, float c, float d){
	
	float X, Y_1, Y_2,respuesta, A,B,C,D;
	A = a ;
	B = b ; 
	C = c ;
	D = d ;
	X = x;
	Y_1 = y_1;
	Y_2 = y_2;
	respuesta = C*Y_2 + D*Y_1*Y_2;
	return respuesta;
	
}


float RungeKuttaFourthOrderStep(float x_old, float y1_old, float y2_old){
    
    float X_old, Y1_old ,Y2_old ;
    
    X_old = x_old ; 
    Y1_old = y1_old ; 
    Y2_old = y2_old ; 	
    
    k_1_prime1 = func_prime_1(x_old,y1_old, y2_old)
    k_1_prime2 = func_prime_2(x_old,y1_old, y2_old)
    
    //first step
    x1 = x_old+ (h/2.0)
    y1_1 = y1_old + (h/2.0) * k_1_prime1
    y2_1 = y2_old + (h/2.0) * k_1_prime2
    k_2_prime1 = func_prime_1(x1, y1_1, y2_1)
    k_2_prime2 = func_prime_2(x1, y1_1, y2_1)
    
	//second step
    x2 = x_old + (h/2.0)
    y1_2 = y1_old + (h/2.0) * k_2_prime1
    y2_2 = y2_old + (h/2.0) * k_2_prime2
    k_3_prime1 = func_prime_1(x2, y1_2, y2_2)
    k_3_prime2 = func_prime_2(x2, y1_2, y2_2)
    
    
    //third
    x3 = x_old + h
    y1_3 = y1_old + h * k_3_prime1
    y2_3 = y2_old + h * k_3_prime2
    k_4_prime1 = func_prime_1(x3, y1_3, y2_3)
    k_4_prime2 = func_prime_2(x3, y1_3, y2_3)
    
    //fourth step
    average_k_1 = (1.0/6.0)*(k_1_prime1 + 2.0*k_2_prime1 + 2.0*k_3_prime1 + k_4_prime1)
    average_k_2 = (1.0/6.0)*(k_1_prime2 + 2.0*k_2_prime2 + 2.0*k_3_prime2 + k_4_prime2)
    
    x_new = x_old + h
    y_1_new = y1_old + h * average_k_1
    y_2_new= y2_old + h * average_k_2
    
    
    return X_new, Y_1_new, Y_2_new;


}
