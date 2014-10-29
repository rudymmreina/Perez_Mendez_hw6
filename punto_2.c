#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define w_0 -5276460.0
#define h 1

float funcx_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float funcx_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float funcy_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float funcy_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float funcz_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float funcz_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2);
float * RungeKuttaSecondOrderStep(float t_old,float x_1_old,float x_2_old,float y_1_old,float y_2_old,float z_1_old,float z_2_old);
int main(int argc, char **argv){


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

  v_0=sqrt(1-(1/pow(((E/m)+1),2)));//[c]

  //condiciones iniciales
  float v_0x;
  float v_0y;
  float v_0z;
  float x_0;
  float y_0;
  float z_0;
  float pi=3.14159;
  v_0x=0;//[c]
  v_0y=v_0*sin(alpha*pi/180);//[c]
  v_0z=v_0*cos(alpha*pi/180);//[c]
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


  int i;
  float *lista;

  for(i=1;i<n_points;i++){
    lista=RungeKuttaSecondOrderStep(t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
    t[i] = lista[0];
    x_1[i] = lista[1];
    x_2[i] = lista[2];
    y_1[i] = lista[3];
    y_2[i] = lista[4];
    z_1[i] = lista[5];
    z_2[i] = lista[6];
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

float funcx_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return x_2;
}


float funcx_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*((y_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2))))-(3.0*z_2*y_1*z_1))*sqrt(1-(pow(x_2,2)+pow(y_2,2)+pow(z_2,2)))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


float funcy_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return y_2;
}


float funcy_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*((3.0*x_1*z_1*z_2)-(x_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2)))))*sqrt(1-((pow(x_2,2)+pow(y_2,2)+pow(z_2,2))))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


float funcz_prime_1(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return z_2;
}



float funcz_prime_2(float t,float x_1,float x_2,float y_1,float y_2,float z_1,float z_2){
  return w_0*3.0*((y_1*z_1*x_2)-(x_1*z_1*y_2))*sqrt(1-((pow(x_2,2)+pow(y_2,2)+pow(z_2,2))))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


float * RungeKuttaSecondOrderStep(float t_old,float x_1_old,float x_2_old,float y_1_old,float y_2_old,float z_1_old,float z_2_old){
    //get the first derivatives
    float x_prime_1;
    float x_prime_2;
    float y_prime_1;
    float y_prime_2;
    float z_prime_1;
    float z_prime_2;
    float t_middle;
    float x_1_middle;
    float x_2_middle;
    float y_1_middle;
    float y_2_middle;
    float z_1_middle;
    float z_2_middle;
    float x_middle_prime_1;
    float x_middle_prime_2;
    float y_middle_prime_1;
    float y_middle_prime_2;
    float z_middle_prime_1;
    float z_middle_prime_2;
    float t_new;
    float x_1_new;
    float x_2_new;
    float y_1_new;
    float y_2_new;
    float z_1_new;
    float z_2_new;





    x_prime_1 = funcx_prime_1(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    x_prime_2 = funcx_prime_2(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    y_prime_1 = funcy_prime_1(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    y_prime_2 = funcy_prime_2(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    z_prime_1 = funcz_prime_1(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    z_prime_2 = funcz_prime_2(t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);

    //from this estimation move to the middle point
    t_middle = t_old+ (h/2.0);
    x_1_middle = y_1_old + (h/2.0) * x_prime_1;
    x_2_middle = y_2_old + (h/2.0) * x_prime_2;
    y_1_middle = y_1_old + (h/2.0) * y_prime_1;
    y_2_middle = y_2_old + (h/2.0) * y_prime_2;
    z_1_middle = y_1_old + (h/2.0) * z_prime_1;
    z_2_middle = y_2_old + (h/2.0) * z_prime_2;

    //compute the derivatives at the middle point
    x_middle_prime_1 = funcx_prime_1(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    x_middle_prime_2 = funcx_prime_2(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    y_middle_prime_1 = funcy_prime_1(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    y_middle_prime_2 = funcy_prime_2(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    z_middle_prime_1 = funcz_prime_1(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    z_middle_prime_2 = funcz_prime_2(t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);

    t_new = t_old + h;
    x_1_new = y_1_old + h * x_middle_prime_1;
    x_2_new= y_2_old + h * x_middle_prime_2;
    y_1_new = y_1_old + h * y_middle_prime_1;
    y_2_new= y_2_old + h * y_middle_prime_2;
    z_1_new = y_1_old + h * z_middle_prime_1;
    z_2_new= y_2_old + h * z_middle_prime_2;

    float *array;
    array = malloc(10 * sizeof(float));

    array[0]=t_new;
    array[1]=x_1_new;
    array[2]=x_2_new;
    array[3]=y_1_new;
    array[4]=y_2_new;
    array[5]=z_1_new;
    array[6]=z_2_new;

    return array;
}
