#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Largo del buffer donde almacena la informacion innecesaria
#define LARGO_BUFFER 100 
/*determinarInicializacion: FILE -> Bool
Recibe un archivo con el formato de entrada, si la cantidad de obstaculos random es mayor
a la mitad de casillas disponibles devuelve 1, sino 0*/
int determinarInicializacion(FILE *archivo){
    char buffer[LARGO_BUFFER];
    int dimension,ObsFijos=0,obsRandom;
    fscanf(archivo,"%s\n%d\n",buffer,&dimension);
    fgets(buffer,LARGO_BUFFER,archivo);
    while(fgetc(archivo)=='('){
        fgets(buffer,LARGO_BUFFER,archivo);
        ObsFijos++;
    }
    fgets(buffer,LARGO_BUFFER,archivo);
    fscanf(archivo,"%d\n",&obsRandom);
    return (obsRandom>(((dimension*dimension)-ObsFijos-2)/2));
}
/*inicializarLaberinto: char** int int
Recibe un laberinto, su dimension y la condicion de seteo.
Si la condicion es 1, inicializa todas las casillas en '1'.Sino, en '0'*/
void inicializarLaberinto (char **laberinto,int dimension,int condicion){
    char caminoLibre = condicion +'0';
    for(int i=0;i<dimension;++i){
        laberinto[i]=malloc(sizeof(int)*dimension+1);
        laberinto[0][i]= caminoLibre;
    }
    laberinto[0][dimension]='\0';
    for(int i=1; i<dimension;++i){
        strcpy(laberinto[i],laberinto[0]);
}
}
/*inicializarLaberinto: char** int
Recibe una matriz char y su tamaño, libera todos los espacios de memoria
que aputan cada posicion de la matriz, luego la matriz*/
void liberarMemoria (char *array[],int dimension){
    for(int i=0;i<dimension;++i){
        free(array[i]);
    }
    free(array);
}
/*verificar: int int int char** char -> bool
Recibe una numero de fila, un numero de columna, un laberinto, su tamaño y un caracter que representa espacio libre
devuelve 1 si la posicion esta dentro del laberinto y no es una posicion ya ocupada*/
int verificar(int posX, int posY,int dimension, char *laberinto[],char caracter){
    return (posX>0 && posY>0)&&(posX<=dimension&&posY<=dimension)&&(laberinto[posX-1][posY-1]==caracter);
}
void obstaculosRandom(char **laberinto,int cantObsRandom,int cantObsFijos,int dimension,int condicion,char randomSeed){
    int filaRandom,columnaRandom;
    char posLibre = condicion +'0';
    srand((int)randomSeed);
    if(condicion){
        int caminosPuestos=0,caminos_a_poner=((dimension*dimension)-cantObsFijos-2)-cantObsRandom;
        while(caminosPuestos<caminos_a_poner){
            filaRandom = rand()%dimension;
            columnaRandom = rand()%dimension;
            while(laberinto[filaRandom][columnaRandom]!= posLibre){
                filaRandom = rand()%dimension;
                columnaRandom = rand()%dimension;
            }
            laberinto[filaRandom][columnaRandom]= '0';
            caminosPuestos++;
        }
    }
    else{
        int obsRandomPuestos=0;
        while(obsRandomPuestos<cantObsRandom){
            filaRandom = rand()%dimension;
            columnaRandom = rand()%dimension;
            while(laberinto[filaRandom][columnaRandom]!= posLibre){
                filaRandom = rand()%dimension;
                columnaRandom = rand()%dimension;
            }
            laberinto[filaRandom][columnaRandom]= '1';
            obsRandomPuestos++;

        }
    }
}
int layoutLaberinto (FILE *archivo,char **laberinto,int dimension,int condicion,char randomSeed){
    int validez=1,cantObsFijos=0,fila,columna,obsRandom;
    char caminoLibre = condicion +'0',pared = condicion + '1',buffer[LARGO_BUFFER];

    fgets(buffer,LARGO_BUFFER,archivo);
    while(fgetc(archivo) == '('&&validez==1){
        fscanf(archivo,"%d,%d)\n",&fila,&columna);
        if(verificar(fila,columna,dimension,laberinto,caminoLibre)){
            laberinto[fila-1][columna-1]= pared;
            cantObsFijos++;
        }
        else validez=0;
    }
    if (validez){
        fgets(buffer,LARGO_BUFFER,archivo);
        fscanf(archivo,"%d\n",&obsRandom);
        if(obsRandom>((dimension*dimension)-cantObsFijos-2))validez=0;
        if (validez){
            fgets(buffer,LARGO_BUFFER,archivo);
            fscanf(archivo,"(%d,%d)\n",&fila,&columna);
            if(verificar(fila,columna,dimension,laberinto,caminoLibre)){
                laberinto[fila-1][columna-1]='I';
                }
            else validez=0;
            if(validez){
                fgets(buffer,LARGO_BUFFER,archivo);
                fscanf(archivo,"(%d,%d)\n",&fila,&columna);
                if(verificar(fila,columna,dimension,laberinto,caminoLibre)){
                laberinto[fila-1][columna-1]='X';}
                else validez=0;
                if(validez){
                    obstaculosRandom(laberinto,obsRandom,cantObsFijos,dimension,condicion,randomSeed);
                    int Transformados=0;
                    if(condicion){
                        for(int i=0;i<dimension&&Transformados<cantObsFijos;i++){
                            for(int j=0;j<dimension&&Transformados<cantObsFijos;j++){
                            if(laberinto[i][j]=='2'){
                                laberinto[i][j]='1';
                                Transformados++;}
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(archivo);
    return validez;
}
void escritura (char **laberinto,int dimension,char fileSalida[]){
    FILE *archivoSalida = fopen(fileSalida,"w");
    for(int i=0;i<dimension;++i){
        fprintf(archivoSalida,"%s\n",laberinto[i]);
    }
    fclose(archivoSalida);
}
int main (int Argc,char **argumentos){
    FILE *Entrada = fopen(argumentos[1],"r");
    int condicion;
    condicion = determinarInicializacion(Entrada);
    rewind(Entrada);
    int dimension;
    char buffer[LARGO_BUFFER];

    fgets(buffer,LARGO_BUFFER,Entrada);
    fscanf(Entrada,"%d\n",&dimension);
    char **laberinto=(char**)malloc(sizeof(char*)*dimension);
    inicializarLaberinto(laberinto,dimension,condicion);
    if(layoutLaberinto(Entrada,laberinto,dimension,condicion,argumentos[3])){
        escritura(laberinto,dimension,argumentos[2]);
        liberarMemoria(laberinto,dimension);
    }
    else{
        printf("La entrada no es valida\n");
        liberarMemoria(laberinto,dimension);
    }

    return 0;
}
