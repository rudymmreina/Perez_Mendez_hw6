#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define w_0c -8.619E11
#define h 0.001

double funcx_prime_1(float g, double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double funcx_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double funcy_prime_1(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double funcy_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double funcz_prime_1(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double funcz_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2);
double * RungeKuttaSecondOrderStep(float g,double t_old,double x_1_old,double x_2_old,double y_1_old,double y_2_old,double z_1_old,double z_2_old);
int main(int argc, char **argv){


  double min_t=0.0;
  double max_t=100.0;
  int n_points;

  // la constante w_0 es la frecuencia natural del problema que es qB/m

  //se define el intervalo de integracion y los puntos

  n_points=((max_t-min_t)/h);
  printf("n: %d \n",n_points);

  //se inicializan las matrices
  double t[n_points];
  double x_1[n_points];
  double x_2[n_points];
  double y_1[n_points];
  double y_2[n_points];
  double z_1[n_points];
  double z_2[n_points];

  //energía y angulo

  double E;
  double alpha;
  double m=938; //[Mev/c**2]
  double v_0;
  double gamma;
  E=atof(argv[1]); //[MeV]
  alpha=atoi(argv[2]);//[°]

  v_0=sqrt(1-(1/pow(((E/m)+1),2)));//[c]
  gamma=1/(sqrt(1-pow(v_0,2)));

  //condiciones iniciales
  double v_0x;
  double v_0y;
  double v_0z;
  double x_0;
  double y_0;
  double z_0;
  double pi=3.14159;
  v_0x=0;//[c]
  v_0y=v_0*sin(alpha*pi/180);//[c]
  v_0z=v_0*cos(alpha*pi/180);//[c]
  x_0=2;//[R_t]
  y_0=0;//[R_t]
  z_0=0;//[R_t]

  printf("gamma %lf m/s \n", gamma);

  //usando las condiciones iniciales
  t[0] = min_t;
  x_1[0] = x_0;
  x_2[0] = v_0x;
  y_1[0] = y_0;
  y_2[0] = v_0y;
  z_1[0] = z_0;
  z_2[0] = v_0z;

//solucionando las ecuACIONES DIFERENCIALES
  int i;
  double *lista;

  for(i=1;i<n_points;i++){
    lista=RungeKuttaSecondOrderStep(gamma,t[i-1],x_1[i-1],x_2[i-1],y_1[i-1],y_2[i-1],z_1[i-1],z_2[i-1]);
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
    fprintf(in, "%lf %lf %lf %lf\n", t[k],x_1[k],y_1[k],z_1[k]);
  }

  fclose(in);


 return 0;
}
/*definiendo las ecuaciones diferenciales a resolver
x_1=x x_2=v_x
y_1=y y_2=v_y
z_1=z z_2=v_z
g=gamma
todas las posiciones estan en unidades del radio de la tierra R_T
las velocidades en unidades de la velocidad de la tierra c
la aceleración en unidades de la frecuencia natural del sistema w_o=-qB_o/m=-2873.65 Y LA VELOCIDAD DE LA LUZ  [w_0 c]

*/
double funcx_prime_1(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return x_2;
}


double funcx_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return (w_0c/g)*((y_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2))))-(3.0*z_2*y_1*z_1))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


double funcy_prime_1(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return y_2;
}


double funcy_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return (w_0c/g)*((3.0*x_1*z_1*z_2)-(x_2*((2.0*pow(z_1,2))-(pow(x_1,2))-(pow(y_1,2)))))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


double funcz_prime_1(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return z_2;
}



double funcz_prime_2(float g,double t,double x_1,double x_2,double y_1,double y_2,double z_1,double z_2){
  return (w_0c/g)*3.0*((y_1*z_1*x_2)-(x_1*z_1*y_2))/pow((pow(x_1,2)+pow(y_1,2)+pow(z_1,2)),2.5);
}


double * RungeKuttaSecondOrderStep(float g,double t_old,double x_1_old,double x_2_old,double y_1_old,double y_2_old,double z_1_old,double z_2_old){
    //get the first derivatives
    double x_prime_1;
    double x_prime_2;
    double y_prime_1;
    double y_prime_2;
    double z_prime_1;
    double z_prime_2;
    double t_middle;
    double x_1_middle;
    double x_2_middle;
    double y_1_middle;
    double y_2_middle;
    double z_1_middle;
    double z_2_middle;
    double x_middle_prime_1;
    double x_middle_prime_2;
    double y_middle_prime_1;
    double y_middle_prime_2;
    double z_middle_prime_1;
    double z_middle_prime_2;
    double t_new;
    double x_1_new;
    double x_2_new;
    double y_1_new;
    double y_2_new;
    double z_1_new;
    double z_2_new;





    x_prime_1 = funcx_prime_1(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    x_prime_2 = funcx_prime_2(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    y_prime_1 = funcy_prime_1(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    y_prime_2 = funcy_prime_2(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    z_prime_1 = funcz_prime_1(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);
    z_prime_2 = funcz_prime_2(g,t_old,x_1_old,x_2_old,y_1_old, y_2_old,z_1_old,z_2_old);

    //from this estimation move to the middle point
    t_middle = t_old+ (h/2.0);
    x_1_middle = y_1_old + (h/2.0) * x_prime_1;
    x_2_middle = y_2_old + (h/2.0) * x_prime_2;
    y_1_middle = y_1_old + (h/2.0) * y_prime_1;
    y_2_middle = y_2_old + (h/2.0) * y_prime_2;
    z_1_middle = y_1_old + (h/2.0) * z_prime_1;
    z_2_middle = y_2_old + (h/2.0) * z_prime_2;

    //compute the derivatives at the middle point
    x_middle_prime_1 = funcx_prime_1(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    x_middle_prime_2 = funcx_prime_2(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    y_middle_prime_1 = funcy_prime_1(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    y_middle_prime_2 = funcy_prime_2(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    z_middle_prime_1 = funcz_prime_1(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);
    z_middle_prime_2 = funcz_prime_2(g,t_middle,x_1_middle,x_2_middle,y_1_middle, y_2_middle,z_1_middle,z_2_middle);

    t_new = t_old + h;
    x_1_new = y_1_old + h * x_middle_prime_1;
    x_2_new= y_2_old + h * x_middle_prime_2;
    y_1_new = y_1_old + h * y_middle_prime_1;
    y_2_new= y_2_old + h * y_middle_prime_2;
    z_1_new = y_1_old + h * z_middle_prime_1;
    z_2_new= y_2_old + h * z_middle_prime_2;

    double *array;
    array = malloc(10 * sizeof(double));

    array[0]=t_new;
    array[1]=x_1_new;
    array[2]=x_2_new;
    array[3]=y_1_new;
    array[4]=y_2_new;
    array[5]=z_1_new;
    array[6]=z_2_new;

    return array;
}
