#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InicializarLab (int *Laberinto[],int Dimension){
    for(int i=0; i<Dimension;++i){
        for(int j=0;j<Dimension;++j){
            Laberinto[i][j]='0';
        }
    }
}
void LiberarMemoria (int *Array[],int Dimension){
    for(int i=0;i<Dimension;++i){
        free(Array[i]);
    }
    free(Array);
}
void ObstaculosRandom (FILE *Archivo,int *Laberinto[],int CantObsRandom,int Dimension){
    int FilaRandom,ColumnaRandom;

    srand(time(NULL));
    for(int i=0;i<CantObsRandom;++i){
        FilaRandom = rand()%Dimension;
        ColumnaRandom = rand()%Dimension;

        while(Laberinto[FilaRandom][ColumnaRandom]!='0'){
            FilaRandom = rand()%Dimension;
            ColumnaRandom = rand()%Dimension;
        }

        Laberinto[FilaRandom][ColumnaRandom]='1';
    }
}
void LayoutLab (FILE *Archivo,int *Laberinto[],int Dimension){
    char buffer[100],Caracter;
    int Fila,Columna,ObsRandom;

    fgets(buffer,100,Archivo);
    Caracter=fgetc(Archivo);
    while(Caracter == '('){
        fscanf(Archivo,"%d,%d)\n",&Fila,&Columna);
        Laberinto[Fila-1][Columna-1]='1';
        Caracter=fgetc(Archivo);
    }
    fgets(buffer,100,Archivo);
    fscanf(Archivo,"%d\n",&ObsRandom);

    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    Laberinto[Fila-1][Columna-1]='I';

    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    Laberinto[Fila-1][Columna-1]='X';

    ObstaculosRandom(Archivo,Laberinto,ObsRandom,Dimension);
}
void Escritura (int *Laberinto[],int Dimension){
    FILE *ArchivoSalida = fopen("Laberinto.txt","w");

    for(int i=0;i<Dimension;++i){
        for(int j=0;j<Dimension;++j){
            fputc(Laberinto[i][j],ArchivoSalida);
        }
        fputc('\n',ArchivoSalida);
    }
    fclose(ArchivoSalida);
}
int main (){
    FILE *Entrada = fopen("ejemplo.txt","r");
    char buffer[20];
    int Dimension;

    fgets(buffer,20,Entrada);
    fscanf(Entrada,"%d",&Dimension);
    fgetc(Entrada);
    int **Laberinto=(int**)malloc(sizeof(int*)*Dimension);
    for(int i=0;i<Dimension;++i){
        Laberinto[i]=malloc(sizeof(int)*Dimension);
    }

    InicializarLab(Laberinto,Dimension);
    LayoutLab(Entrada,Laberinto,Dimension);
    fclose(Entrada);

    Escritura(Laberinto,Dimension);
    LiberarMemoria(Laberinto,Dimension);
}