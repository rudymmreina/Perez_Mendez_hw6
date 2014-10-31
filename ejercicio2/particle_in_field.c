#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define w_0c -8.619E11 /*Unidades de la aceleracion w_0 es la frecuencia natural del sistema ( w_0=-qB/m=-2873.65  [1/s]) y
c la velocidad de la luz (c=3*10**8 [m/s]), por lo que w_0c=-8.619E11m/s**2 y define las unidades naturales de la aceleración*/
#define h 0.0001

double func_prime_r(double t,double *r,double v);
double func_prime_v(int i,double *r,double *v);
double RungeKuttaFourthOrderStep(double *r, double *v, double t_old);
double norma_vector(double A,double B, double C);

int main(int argc, char **argv){

  int n_points, i;
  double  alpha, v_0, E;
  double *v,*r,  *t;
  double pi=3.14159;


  r = malloc(3 * sizeof(float));
  v = malloc(3 * sizeof(float));
  t = malloc(2 * sizeof(double));


  //se define el intervalo de integracion y los puntos
  double min_t=0.0;
  double max_t=100.0;
  n_points=((max_t-min_t)/h)+1;

  //condiciones iniciales
  E=atof(argv[1]); //[MeV]
  alpha=atoi(argv[2]);//[°]
  double m=938; //[Mev/c**2]
  v_0=sqrt(1-(1/pow(((E/m)+1),2)));//[c]


  //condiciones iniciales
  double v_0x;
  double v_0y;
  double v_0z;
  double x_0;
  double y_0;
  double z_0;

  v_0x=0;//[c]
  v_0y=v_0*sin(alpha*pi/180);//[c]
  v_0z=v_0*cos(alpha*pi/180);//[c]
  x_0=2;//[R_t]
  y_0=0;//[R_t]
  z_0=0;//[R_t]

  //iniciando las matrices

  t[0] = min_t;
  r[0] = x_0;//[R_t]
  v[0] = v_0x;//[c]
  r[1] = y_0;//[R_t]
  v[1] = v_0y;//[c]
  r[2] = z_0;//[R_t]
  v[2] = v_0z;//[c]

  FILE *file;

  char filename[64];
  sprintf (filename, "trayectoria_%d_%d.dat", atoi(argv[1]), atoi(argv[2]));

  file=fopen(filename, "w");

  fprintf(file, "%f \t %f \t %f \t %f \n", t[0],  r[0], r[1],r[2] );

  for( i=1;i<n_points;i++){

    t[1] = RungeKuttaFourthOrderStep(r,v,t[0]);
    t[0]=t[1];

    fprintf(file, "%f \t %f \t %f \t %f \n", t[0],  r[0], r[1],r[2] );
  }


  return 0;
}


//definiendo las ecuaciones

double func_prime_r(double t,double *r,double v){
  return v;
}

double norma_vector(double A,double B, double C){
  return sqrt(pow(A,2)+pow(B,2)+pow(C,2));
}
double func_prime_v(int i, double *r, double *v){

  double vx,vy,vz,x,y,z;
  double gamma,Br,By,Bz;
  double s, u;
  double a[3];
//todas las posiciones estan en unidades del radio de la tierra
//todas las velocidad estan en unidades de la velocidad de la luz
//definiendo las coordenadas del vector posicion y velocidad
  x=r[0];
  y=r[1];
  z=r[3];

  vx=v[0];
  vy=v[1];
  vz=v[2];
//definiendo la norma del vector posicion

  s=norma_vector(x,y,z);
  u=norma_vector(vx,vy,vz);
//calculando el campo magnético adimensional

  Br=(3*x*z)/(pow(s,5));
  By=(3*y*z)/(pow(s,5));
  Bz=(2*pow(z,2)-pow(x,2)-pow(y,2))/(pow(s,5));
/*calculando la aceleracion vectorial y adimensional es decir...se encuentra en unidades de [w_0 c]
definida inicialmente
*/
  gamma=1/(sqrt(1-pow(u,2)));;

  a[0]=(vy*Bz-vz*By)/gamma;
  a[1]=(vz*Br-vx*Bz)/gamma;
  a[2]=(vx*By-vy*Br)/gamma;


  return a[i];
}

double RungeKuttaFourthOrderStep(double *r, double *v, double t_old){

//definiendo las matrices de las cuatro pendientes
  double k_1_prime1[3],k_1_prime2[3],k_2_prime1[3], k_2_prime2[3], k_3_prime1[3], k_3_prime2[3], k_4_prime1[3], k_4_prime2[3];
//definiendo las matrices de las posiciones intermedios
  double r_1[3],r_2[3],r_3[3];
//defieniendo las matrices de  las velocidade intermedias
  double v_1[3], v_2[3], v_3[3];
//definiendo las matrices de las pendientes promedio
  double average_k_1[3], average_k_2[3];
  //definiendo los tiempos intermedios
  double t1,t2,t3;
  //definiendo los vectors de posicion y velocidadnuevos
  double t_new, r_new[3], v_new[3];



  k_1_prime1[0] = func_prime_r(t_old,r, v[0]);
  k_1_prime2[0] = func_prime_v(0,r, v);

  k_1_prime1[1] = func_prime_r(t_old,r, v[1]);
  k_1_prime2[1] = func_prime_v(1,r, v);

  k_1_prime1[2] = func_prime_r(t_old,r, v[2]);
  k_1_prime2[2] = func_prime_v(2,r, v);

  //first step
  t1 = t_old+ (h/2.0);

  r_1[0] = r[0] + (h/2.0) * k_1_prime1[0];
  v_1[0] = v[0] + (h/2.0) * k_1_prime2[0];

  r_1[1] = r[1] + (h/2.0) * k_1_prime1[1];
  v_1[1] = v[1] + (h/2.0) * k_1_prime2[1];

  r_1[2] = r[2] + (h/2.0) * k_1_prime1[2];
  v_1[2] = v[2] + (h/2.0) * k_1_prime2[2];

  k_2_prime1[0] = func_prime_r(t1, r_1, v_1[0]);
  k_2_prime2[0] = func_prime_v(0, r_1, v_1);


  k_2_prime1[1] = func_prime_r(t1, r_1, v_1[1]);
  k_2_prime2[1] = func_prime_v(1, r_1, v_1);


  k_2_prime1[2] = func_prime_r(t1, r_1, v_1[2]);
  k_2_prime2[2] = func_prime_v(2, r_1, v_1);


  //"second step"
  t2 = t_old + (h/2.0);

  r_2[0] = r[0] + (h/2.0) * k_2_prime1[0];
  v_2[0] = v[0] + (h/2.0) * k_2_prime2[0];

  r_2[1] = r[1] + (h/2.0) * k_2_prime1[1]; //
  v_2[1] = v[1] + (h/2.0) * k_2_prime2[1];

  r_2[2] = r[2] + (h/2.0) * k_2_prime1[2];
  v_2[2] = v[2] + (h/2.0) * k_2_prime2[2];

  k_3_prime1[0] = func_prime_r(t2, r_2, v_2[0]);
  k_3_prime2[0] = func_prime_v(0, r_2, v_2);


  k_3_prime1[1] = func_prime_r(t2, r_2, v_2[1]);
  k_3_prime2[1] = func_prime_v(1, r_2, v_2);


  k_3_prime1[2] = func_prime_r(t2, r_2, v_2[2]);
  k_3_prime2[2] = func_prime_v(2, r_2, v_2);  //Falta organizar v_2



    //"third step"
  t3 = t_old + h;

  r_3[0] = r[0] + h * k_3_prime1[0];
  v_3[0] = v[0] + h * k_3_prime2[0];

  r_3[1] = r[1] + h * k_3_prime1[1];
  v_3[1] = v[1] + h * k_3_prime2[1];

  r_3[2] = r[2] + h * k_3_prime1[2];
  v_3[2] = v[2] + h * k_3_prime2[2];

  k_4_prime1[0] = func_prime_r(t3, r_3, v_3[0]);
  k_4_prime2[0] = func_prime_v(0, r_3, v_3);


  k_4_prime1[1] = func_prime_r(t3, r_3, v_3[1]);
  k_4_prime2[1] = func_prime_v(1, r_3, v_3);


  k_4_prime1[2] = func_prime_r(t3, r_3, v_3[2]);
  k_4_prime2[2] = func_prime_v(2, r_3, v_3);



  // "fourth step"
  average_k_1[0] = (1.0/6.0)*(k_1_prime1[0] + 2.0*k_2_prime1[0] + 2.0*k_3_prime1[0] + k_4_prime1[0]);
  average_k_2[0] = (1.0/6.0)*(k_1_prime2[0] + 2.0*k_2_prime2[0] + 2.0*k_3_prime2[0] + k_4_prime2[0]);

  average_k_1[1] = (1.0/6.0)*(k_1_prime1[1] + 2.0*k_2_prime1[1] + 2.0*k_3_prime1[1] + k_4_prime1[1]);
  average_k_2[1] = (1.0/6.0)*(k_1_prime2[1] + 2.0*k_2_prime2[1] + 2.0*k_3_prime2[1] + k_4_prime2[1]);

  average_k_1[2] = (1.0/6.0)*(k_1_prime1[2] + 2.0*k_2_prime1[2] + 2.0*k_3_prime1[2] + k_4_prime1[2]);
  average_k_2[2] = (1.0/6.0)*(k_1_prime2[2] + 2.0*k_2_prime2[2] + 2.0*k_3_prime2[2] + k_4_prime2[2]);


  //Las nuevas variables
  t_new = t_old + h;

  r[0]=r[0] + h * average_k_1[0];
  v[0]=v[0] + h * average_k_2[0];

  r[1]=r[1] + h * average_k_1[1];
  v[1]=v[1] + h * average_k_2[1];

  r[2]=r[2] + h * average_k_1[2];
  v[2]=v[2] + h * average_k_2[2];



  return t_new;
}
