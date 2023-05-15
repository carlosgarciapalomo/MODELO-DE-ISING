#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#define N 100

using namespace std;
void CondicionesIniciales (double s[][N]); 
void ConfiguracionOrdenadaPositiva(double s[][N]);
void ConfiguracionOrdenadaNegativa( double s[][N]);
double Energia (int i, int j, double M[][N]);



int main()
{
  int i,j,k; //ESTOS SON LOS CONTADORES QUE UTLIZAREMOS

  int n,m; // (n,m) son las posiciones aleatorias de la red
  double num1,num2; // VARIABLE AUXILIAR PARA ALMACENAR UN NUMERO
  double s[N][N];
  double Probabilidad; //Variable en la que almacenaremos la probabilidad
  double Temperatura; //Vaiable en la que almaceno la temperaturilla
  int h; //Este indice sirve para que solo escribamos pasos de 100 en 100
  srand(time(NULL));
  int config;
  ofstream datos; //FICHERO PARA ALMACENAR LOS DATOS


  //PIDO EL VALOR DE LA TEMPERATURA
  cout <<"Introduzca el valor de la temperatura"<< endl;
  cin>>Temperatura;

  //PEDIMOS LA CONFIGURACION INICIAL
  cout <<"Escriba 1 si quiere los espines a 1, -1 si quiere los espines a -1 y 0 si quiere configuracion inicial aleatoria"<< endl;
  cin>>config;

  //INICIALIZAMOS DE LOS VALORES PARA EL ESPIN DE LA RED CON CONDICIONES DE CONTORNO PERIODICAS

  if(config==0)
CondicionesIniciales (s);
else if(config==1)
ConfiguracionOrdenadaPositiva (s);
else
ConfiguracionOrdenadaNegativa(s);

  // Abrimos el archivo donde escribiremos
    std::ofstream archivo_datos("datos.txt");
    archivo_datos.precision(16); // definir la precisión del archivo de salida

    //ALMACENAMOS LA PRIMERA CONFIGURACION EN UN FICHERO
    for (i= 0; i<N; i++)
    {   
        for(k=0;k<N-1;k++)
        {
          archivo_datos <<s[i][k]<<",";
        }
        archivo_datos<<s[i][N-1]<< std::endl;
    }
    archivo_datos << std::endl<< std::endl;
    h=0;

    //ALGORITMO DE MONTECARLO 
    for (j=0;j<(2000)*(N*N);j++)
    {
      
            //NUMEROS ALEATORIOS (STEP 1)
            n=rand() % N;
            m=rand() % N;

            //EVALUAR PROBABILIDAD (STEP 2)
           num1=exp(-1.0*Energia(n,m,s) /Temperatura);
           if (num1<1) Probabilidad=num1;
           else Probabilidad=1.0;
            
            //GENERACION DEL NUMERO AL AZAR Y COMPROBAR SI QUEDA DENTRO DE LA PROBABILIDAD 
           num2 =(double) rand() / RAND_MAX;
           if (num2<Probabilidad)
           s[n][m]=-1*s[n][m];
        
     //ALMACENO LOS DATOS EN UN FICHERO CADA PASO MONTECARLO
     if(h==N*N)
     {
     for (i= 0; i<N; i++)
    {   
        for(k=0;k<N-1;k++)
        {
          archivo_datos <<s[i][k]<<" ";
        }
        archivo_datos<<s[i][N-1]<< std::endl;
    }
    archivo_datos<< std::endl <<std::endl;
    h=0;
     }
     else {
        h=h+1;
     }

    }
 
  // Cerramos el archivo 
    archivo_datos.close();

  return 0;
}

//FUNCION QUE INICIALIZA LA RED 
void CondicionesIniciales ( double s[][N])
{
    int i,j;
    double num; //Variable auxiliar para almacenar números

    //Inicialización de las condiciones de contorno
    for(j=0;j<N;j++)
    {
        num=(double) rand() / (double) RAND_MAX;
        if (num>0.5)
        {
            s[0][j]=1;
            s[N-1][j]=1;
        }

        else
        {
            s[0][j]=-1;
            s[N-1][j]=-1;
        }
    }

    for(i=1;i<N;i++)
    {
        num=(double) rand() / (double) RAND_MAX;
        if (num>0.5)
        {
            s[i][0]=1;
            s[i][N-1]=1;
        }

        else
        {
            s[i][0]=-1;
            s[i][N-1]=-1;
        }
    }

    //inicialización del resto de la red
    for (i=1;i<(N-1);i++)
        for (j=1;j<(N-1);j++)
        {
            num=(double) rand() / (double) RAND_MAX;
            if (num>0.5)
                s[i][j]=1;
            else
                s[i][j]=-1;
        }

    return;
}



//FUNCION QUE INICIALIZA LOS ESPINES A 1
void ConfiguracionOrdenadaPositiva(double s[][N])
{
  
int i,j;
    
    //Inicialización de las condiciones de contorno
    for(j=0;j<N;j++)
    {
        
            s[0][j]=1;
            s[N-1][j]=1;
     
    }

    for(i=1;i<N;i++)
    {
       
            s[i][0]=1;
            s[i][N-1]=1;
    }

    //inicialización del resto de la red
    for (i=1;i<(N-1);i++)
        for (j=1;j<(N-1);j++)
        {
                s[i][j]=1;
        }

    return;

}

//FUNCION QUE INICIALIZA LOS ESPINES A -1
void ConfiguracionOrdenadaNegativa(double s[][N])
{
  
int i,j;

    //Inicialización de las condiciones de contorno
    for(j=0;j<N;j++)
    {
        
            s[0][j]=-1;
            s[N-1][j]=-1;
     
    }

    for(i=1;i<N;i++)
    {
       
            s[i][0]=-1;
            s[i][N-1]=-1;
    }

    //inicialización del resto de la red
    for (i=1;i<(N-1);i++)
        for (j=1;j<(N-1);j++)
        {
                s[i][j]=-1;
        }

    return;

}

double Energia (int i, int j, double M[][N])
{
    double E;
    if ((i != N - 1) && (j != N - 1) && (i != 0) && (j != 0))
        {
            E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[i - 1][j]) + (M[i][j + 1]) + (M[i][j - 1]));
        }
        else
        {
            if ((i == N - 1) && (j != N - 1) && (j != 0))
            {
                E = (2.0) * (M[i][j]) * ((M[0][j]) + (M[i - 1][j]) + (M[i][j + 1]) + (M[i][j - 1]));
            }
            else
            {
                if ((i != N - 1) && (j == N - 1) && (i != 0))
                {
                    E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[i - 1][j]) + (M[i][0]) + (M[i][j - 1]));
                }
                else
                {
                    if ((j != N - 1) && (i == 0) && (j != 0))
                    {
                        E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[N - 1][j]) + (M[i][j + 1]) + (M[i][j - 1]));
                    }
                    else
                    {
                        if ((i != N - 1) && (i != 0) && (j == 0))
                        {
                            E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[i - 1][j]) + (M[i][j + 1]) + (M[i][N - 1]));
                        }
                        else
                        {
                            if ((i == 0) && (j == 0))
                            {
                                E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[N - 1][j]) + (M[i][j + 1]) + (M[i][N - 1]));
                            }
                            else
                            {
                                if ((i == N - 1) && (j == N - 1))
                                {
                                    E = (2.0) * (M[i][j]) * ((M[0][j]) + (M[i - 1][j]) + (M[i][0]) + (M[i][j - 1]));
                                }
                                else
                                {
                                    if ((i == 0) && (j == N - 1))
                                    {
                                        E = (2.0) * (M[i][j]) * ((M[i + 1][j]) + (M[N - 1][j]) + (M[i][0]) + (M[i][j - 1]));
                                    }
                                    else
                                    {
                                        E = (2.0) * (M[i][j]) * ((M[0][j]) + (M[i - 1][j]) + (M[i][j + 1]) + (M[i][N - 1]));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return E;
}
