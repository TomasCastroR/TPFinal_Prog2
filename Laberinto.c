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
int Verificar(int PosX, int PosY,int Dimension, int *Laberinto[]){
    return (PosX>0 && PosY>0)&&(PosX<=Dimension&&PosY<=Dimension)&&(Laberinto[PosX-1][PosY-1]=='0');
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
int LayoutLab (FILE *Archivo,int *Laberinto[],int Dimension){
    int Validez=1,Fila,Columna,ObsRandom,LargoBuffer=100;
    char buffer[LargoBuffer],Caracter;

    fgets(buffer,100,Archivo);
    Caracter=fgetc(Archivo);
    while(Caracter == '('&&Validez==1){
        fscanf(Archivo,"%d,%d)\n",&Fila,&Columna);
        if(Verificar(Fila,Columna,Dimension,Laberinto)==1){
            Laberinto[Fila-1][Columna-1]='1';
            Caracter=fgetc(Archivo);
        }
        else Validez=0;
    }
    fgets(buffer,100,Archivo);
    fscanf(Archivo,"%d\n",&ObsRandom);
    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    if(Verificar(Fila,Columna,Dimension,Laberinto)==1){
        Laberinto[Fila-1][Columna-1]='I';}
    else Validez=0;

    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    if(Verificar(Fila,Columna,Dimension,Laberinto)==1){
        Laberinto[Fila-1][Columna-1]='X';}
    else Validez=0;
    if(Validez==1)ObstaculosRandom(Archivo,Laberinto,ObsRandom,Dimension);
    return Validez;
}
void Escritura (int *Laberinto[],int Dimension,char NombreSalida[]){
    FILE *ArchivoSalida = fopen(NombreSalida,"w");

    for(int i=0;i<Dimension;++i){
        for(int j=0;j<Dimension;++j){
            fputc(Laberinto[i][j],ArchivoSalida);
        }
        fputc('\n',ArchivoSalida);
    }
    fclose(ArchivoSalida);
}
int main (int Argc,char *Argumentos[]){
    FILE *Entrada = fopen(Argumentos[1],"r");
    int Dimension,LargoBuffer=20;
    char buffer[LargoBuffer];

    fgets(buffer,20,Entrada);
    fscanf(Entrada,"%d\n",&Dimension);
    int **Laberinto=(int**)malloc(sizeof(int*)*Dimension);
    for(int i=0;i<Dimension;++i){
        Laberinto[i]=malloc(sizeof(int)*Dimension);
    }

    InicializarLab(Laberinto,Dimension);
    if(LayoutLab(Entrada,Laberinto,Dimension)==1){
        fclose(Entrada);
        Escritura(Laberinto,Dimension,Argumentos[2]);
        LiberarMemoria(Laberinto,Dimension);
    }
    else{
        printf("La entrada no es valida");
        LiberarMemoria(Laberinto,Dimension);
    }

    
    return 0;
}