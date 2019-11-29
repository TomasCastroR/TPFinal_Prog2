#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LargoBuffer 100 
char DeterminarInicializacion(FILE *Archivo){
    char buffer[LargoBuffer];
    int Dimension,ObsFijos=0,ObsRandom;
    fscanf(Archivo,"%s\n%d\n",buffer,&Dimension);
    fgets(buffer,LargoBuffer,Archivo);
    while(fgetc(Archivo)=='('){
        fgets(buffer,LargoBuffer,Archivo);
        ObsFijos++;
    }
    fgets(buffer,LargoBuffer,Archivo);
    fscanf(Archivo,"%d\n",&ObsRandom);
    return (ObsRandom>(((Dimension*Dimension)-ObsFijos)/2));
}
void InicializarLab (char *Laberinto[],int Dimension,int Condicion){
    char Caracter = Condicion +'0';
    for(int i=0;i<Dimension;++i){
        Laberinto[i]=malloc(sizeof(int)*Dimension+1);
        Laberinto[0][i]= Caracter;
    }
    Laberinto[0][Dimension]='\0';
    for(int i=1; i<Dimension;++i){
        strcpy(Laberinto[i],Laberinto[0]);
}
}
void LiberarMemoria (char *Array[],int Dimension){
    for(int i=0;i<Dimension;++i){
        free(Array[i]);
    }
    free(Array);
}

int Verificar(int PosX, int PosY,int Dimension, char *Laberinto[],char Letra){
    return (PosX>0 && PosY>0)&&(PosX<=Dimension&&PosY<=Dimension)&&(Laberinto[PosX-1][PosY-1]==Letra);
}
void ObstaculosRandom(char *Laberinto[],int CantObsRandom,int CantObsFijos,int Dimension,int Condicion){
    int FilaRandom,ColumnaRandom;
    char PosLibre = Condicion +'0';
    srand(time(NULL));
    if(Condicion){
        int CaminosPuestos=0,CaminosAPoner=((Dimension*Dimension)-CantObsFijos-2)-CantObsRandom;
        while(CaminosPuestos<CaminosAPoner){
            FilaRandom = rand()%Dimension;
            ColumnaRandom = rand()%Dimension;
            while(Laberinto[FilaRandom][ColumnaRandom]!= PosLibre){
                FilaRandom = rand()%Dimension;
                ColumnaRandom = rand()%Dimension;
            }
            Laberinto[FilaRandom][ColumnaRandom]= '0';
            CaminosPuestos++;
        }
    }
    else{
        int ObsRandomPuestos=0;
        while(ObsRandomPuestos<CantObsRandom){
            FilaRandom = rand()%Dimension;
            ColumnaRandom = rand()%Dimension;
            while(Laberinto[FilaRandom][ColumnaRandom]!= PosLibre){
                FilaRandom = rand()%Dimension;
                ColumnaRandom = rand()%Dimension;
            }
            Laberinto[FilaRandom][ColumnaRandom]= '1';
            ObsRandomPuestos++;

        }
    }
}
int LayoutLab (FILE *Archivo,char *Laberinto[],int Dimension,int Condicion){
    int Validez=1,CantObsFijos=0,Fila,Columna,ObsRandom;
    char Caracter = Condicion +'0',Pared = Condicion + '1',buffer[LargoBuffer];
    fgets(buffer,100,Archivo);
    while(fgetc(Archivo) == '('&&Validez==1){
        fscanf(Archivo,"%d,%d)\n",&Fila,&Columna);
        if(Verificar(Fila,Columna,Dimension,Laberinto,Caracter)){
            Laberinto[Fila-1][Columna-1]= Pared;
            CantObsFijos++;
        }
        else Validez=0;
    }
    if (Validez){
        fgets(buffer,100,Archivo);
        fscanf(Archivo,"%d\n",&ObsRandom);
        if(ObsRandom>((Dimension*Dimension)-CantObsFijos-2))Validez=0;
        if (Validez){
            fgets(buffer,100,Archivo);
            fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
            if(Verificar(Fila,Columna,Dimension,Laberinto,Caracter)){
            Laberinto[Fila-1][Columna-1]='I';}
            else Validez=0;
            if(Validez){
                fgets(buffer,100,Archivo);
                fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
                if(Verificar(Fila,Columna,Dimension,Laberinto,Caracter)){
                Laberinto[Fila-1][Columna-1]='X';}
                else Validez=0;
                if(Validez)ObstaculosRandom(Laberinto,ObsRandom,CantObsFijos,Dimension,Condicion);
            }
        }
    }
    fclose(Archivo);
    return Validez;
}
void Escritura (char *Laberinto[],int Dimension,char NombreSalida[],int Condicion){
    FILE *ArchivoSalida = fopen(NombreSalida,"w");
    if(Condicion){
        for(int i=0;i<Dimension;i++){
            for(int j=0;j<Dimension;j++){
                if(Laberinto[i][j]=='2'){
                    Laberinto[i][j]='1';
                }
            }
        }
        for(int i=0;i<Dimension;++i){
            fprintf(ArchivoSalida,"%s\n",Laberinto[i]);
        }
    }
    else{
        for(int i=0;i<Dimension;++i){
            fprintf(ArchivoSalida,"%s\n",Laberinto[i]);
        }
    }
    fclose(ArchivoSalida);
}
int main (int Argc,char *Argumentos[]){
    FILE *Entrada = fopen(Argumentos[1],"r");
    int Condicion;
    Condicion = DeterminarInicializacion(Entrada);
    rewind(Entrada);
    int Dimension;
    char buffer[LargoBuffer];

    fgets(buffer,LargoBuffer,Entrada);
    fscanf(Entrada,"%d\n",&Dimension);
    char **Laberinto=(char**)malloc(sizeof(char*)*Dimension);
    InicializarLab(Laberinto,Dimension,Condicion);
    if(LayoutLab(Entrada,Laberinto,Dimension,Condicion)){
        Escritura(Laberinto,Dimension,Argumentos[2],Condicion);
        LiberarMemoria(Laberinto,Dimension);
    }
    else{
        printf("La entrada no es valida\n");
        LiberarMemoria(Laberinto,Dimension);
    }

    return 0;
}
