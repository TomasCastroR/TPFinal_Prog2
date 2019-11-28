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
void Swapear(int *Matriz[],int Pos,int Dimension,int Tamano,int CantSwapeados){
    int Swap;
    Swap=Matriz[(Tamano-1-CantSwapeados)/Dimension][(Tamano-1-CantSwapeados)%Dimension];
    Matriz[(Tamano-1-CantSwapeados)/Dimension][(Tamano-1-CantSwapeados)%Dimension]=Matriz[Pos/Dimension][Pos%Dimension];
    Matriz[Pos/Dimension][Pos%Dimension]=Swap;
}
void ObstaculosRandom (FILE *Archivo,int *Laberinto[],int CantObsRandom,int Dimension){
    int Tamano=Dimension*Dimension,Pos=0;
    int **PosLibres=(int**)malloc(sizeof(int*)*Dimension);
    for(int i=0;i<Dimension;++i){
        PosLibres[i]=malloc(sizeof(int)*Dimension);
    }
    //printf("SE ROMPE ACA 6?\n");
    for(int i=0;i<Dimension;i++){
        //printf("SE ROMPE ACA %di?\n",i);
        for(int j=0;j<Dimension;j++){
            //printf("SE ROMPE ACA %dj?\n",j);
            //printf("%c???\n",Laberinto[i][j]);
            //printf("%c/%d ",Laberinto[i][j],Laberinto[i][j] == '0');
            if(Laberinto[i][j] == '0'){
                //printf("SE ROMPE ACA %dAAAA?\n",j);
                PosLibres[i][j]=Pos;
            }
            else PosLibres[i][j]=-1;
            Pos++;
        }
        //printf("\n");
    }
    /*printf("MATRIZ INICIAL\n");
    for(int i=0;i<Dimension;i++){
        for(int j=0;j<Dimension;j++){
            printf("%d ",PosLibres[i][j]);
        }
        printf("\n");
    }*/
    //printf("SE ROMPE ACA 7?\n");
    srand(time(NULL));
    int i=0,Random,Ocupadas=0,Posicion;
    while(i<CantObsRandom){
        Random = rand()%(Tamano-(i+Ocupadas));
        //printf("%d -- %d -- (%d,%d) -- %d\n",i,Random,(Random/Dimension)+1,(Random%Dimension)+1,Tamano-(i+Ocupadas));
        if(PosLibres[Random/Dimension][Random%Dimension]!=-1){
            Posicion=PosLibres[Random/Dimension][Random%Dimension];
            Laberinto[Posicion/Dimension][Posicion%Dimension]='1';
            Swapear(PosLibres,Random,Dimension,Tamano,(i+Ocupadas));
            i++;
        }
        else{
            Swapear(PosLibres,Random,Dimension,Tamano,(i+Ocupadas));
            Ocupadas++;
        }
    }
    /*printf("MATRIZ SWAPEADO\n");
    for(int i=0;i<Dimension;i++){
        for(int j=0;j<Dimension;j++){
            printf("%d ",PosLibres[i][j]);
        }
        printf("\n");
    }*/
    //printf("SE ROMPE ACA 8?\n");
    free(PosLibres);
}
int LayoutLab (FILE *Archivo,int *Laberinto[],int Dimension){
    int Validez=1,CantObsFijos=0,Fila,Columna,ObsRandom,LargoBuffer=100;
    char buffer[LargoBuffer],Caracter;

    fgets(buffer,100,Archivo);
    Caracter=fgetc(Archivo);
    while(Caracter == '('&&Validez==1){
        fscanf(Archivo,"%d,%d)\n",&Fila,&Columna);
        if(Verificar(Fila,Columna,Dimension,Laberinto)){
            Laberinto[Fila-1][Columna-1]='1';
            CantObsFijos++;
            Caracter=fgetc(Archivo);
        }
        else Validez=0;
    }
    fgets(buffer,100,Archivo);
    fscanf(Archivo,"%d\n",&ObsRandom);
    if(ObsRandom>((Dimension*Dimension)-CantObsFijos-2))Validez=0;
    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    if(Verificar(Fila,Columna,Dimension,Laberinto)){
        Laberinto[Fila-1][Columna-1]='I';}
    else Validez=0;

    fgets(buffer,100,Archivo);
    fscanf(Archivo,"(%d,%d)\n",&Fila,&Columna);
    if(Verificar(Fila,Columna,Dimension,Laberinto)){
        Laberinto[Fila-1][Columna-1]='X';}
    else Validez=0;
    fclose(Archivo);
    if(Validez)ObstaculosRandom(Archivo,Laberinto,ObsRandom,Dimension);
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
    if(LayoutLab(Entrada,Laberinto,Dimension)){
        Escritura(Laberinto,Dimension,Argumentos[2]);
        LiberarMemoria(Laberinto,Dimension);
    }
    else{
        printf("La entrada no es valida");
        LiberarMemoria(Laberinto,Dimension);
    }

    
    return 0;
}