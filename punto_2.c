#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define w_0 5276460.0

float x_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float x_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float y_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float y_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float z_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float z_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);

int main(int argc, char **argv){

  float h=1;
  float min_t=0.0;
  float max_t=100.0;
  int n_points;
  // la constante w_0 es la frecuencia natural del problema que es qB/m

  //se define el intervalo de integracion y los puntos

  n_points=(max_t-min_t/h);

  //se inicializan las matrices
  float t[n_points];
  double x_1[n_points];
  double x_2[n_points];
  double y_1[n_points];
  double y_2[n_points];
  double z_1[n_points];
  double z_2[n_points];


  //energía y angulo

  float E;
  float alpha;
  float m=0.5109;
  float v_0;
  E=atof(argv[1]); //[MeV]
  alpha=atoi(argv[2]);//[°]

  v_0=sqrt(2.0*E/m)*3*pow(10,8);//[m/s]

  //condiciones iniciales
  float v_0x;
  float v_0y;
  float v_0z;
  float x_0;
  float y_0;
  float z_0;
  float pi=3.14159;
  v_0x=0;//[m/s]
  v_0y=v_0*sin(alpha*pi/180);//[m/s]
  v_0z=v_0*cos(alpha*pi/180);//[m/s]
  x_0=2;//[R_t]
  y_0=0;//[R_t]
  z_0=0;//[R_t]

  printf("La frecuencia natural del sistema es %f 1/s \nLa velocidad del electron es %f m/s \n",w_0, v_0);

  //usando las condiciones iniciales
  t[0] = min_t;
  x_1[0] = x_0;
  x_2[0] = v_0x;
  y_1[0] = y_0;
  y_2[0] = v_0y;
  z_1[0] = z_0;
  z_2[0] = v_0z;


  //generando el primer paso
  t[1] = min_t + h;
  x_1[1] = y_1[0] + h*x_prime_1(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);
  x_2[1] = y_2[0] + h*x_prime_2(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);
  y_1[1] = y_1[0] + h*y_prime_1(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);
  y_2[1] = y_2[0] + h*y_prime_2(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);
  z_1[1] = z_1[0] + h*z_prime_1(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);
  z_2[1] = z_2[0] + h*z_prime_2(t[0],x_1[0],x_2[0],y_1[0],y_2[0],z_1[0],z_2[0]);

  //generando los demás
  int i;
  for(i=2;i<n_points;i++){
    t[i] = t[i-1] + h;
    x_1[i] = x_1[i-2] + 2 * h *x_prime_1(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    x_2[i] = y_2[i-2] + 2 * h *x_prime_2(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    y_1[i] = y_1[i-2] + 2 * h *y_prime_1(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    y_2[i] = y_2[i-2] + 2 * h *y_prime_2(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    z_1[i] = z_1[i-2] + 2 * h *z_prime_1(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    z_2[i] = y_2[i-2] + 2 * h *z_prime_2(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
  }

  //generando un archivo

  char nombre[50]="trayectoria_";
  char energia_s[50];
  char alpha_s[5];
  char rayita[5]="_";
  char extension[10]=".dat";
  int k;


  strcpy(energia_s,argv[1]);
  strcpy(alpha_s,argv[2]);
  strcat(nombre,energia_s);
  strcat(nombre,rayita);
  strcat(nombre,alpha_s);
  strcat(nombre,extension);
  FILE *in;

  printf("nombre del archivo es : %s\n",nombre);

  in = fopen(nombre,"w");
  if(!in){
    printf("problems opening the file %s\n", nombre);
    exit(1);
  }

  for(k=0;k<n_points;k++){
    fprintf(in, "%f %f %f %f\n", t[k],x_1[k],y_1[k],z_1[k]);
  }

  fclose(in);

 return 0;
}

float x_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return x_2;
}


float x_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*((y_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2))))-(3.0*z_2*y_1*z_1))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


float y_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return y_2;
}


float y_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*((3.0*x_1*z_1*z_2)-(x_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2)))))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


float z_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return z_2;
}


float z_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*3.0*((y_1*z_1*x_2)-(x_1*z_1*y_2))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}
