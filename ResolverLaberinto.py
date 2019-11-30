import subprocess
from math import sqrt

def Encontrar(Laberinto):
    Fila=0
    Columna=0
    Dimension=len(Laberinto)
    Encontrado=0
    while(Fila<Dimension and Encontrado<2):
        while(Columna<Dimension):
            if(Laberinto[Fila][Columna]=="I"):
                Inicio=(Fila,Columna)
                Encontrado+=1
            elif (Laberinto[Fila][Columna]=="X"):
                Final=(Fila,Columna)
                Encontrado+=1
            Columna+=1
        Columna=0
        Fila+=1
    return (Inicio,Final)
"""def Distancia(Posicion,Objetivo):
    return abs(Objetivo[0]-Posicion[0])+abs(Objetivo[1]-Posicion[1])-1
def OrdenarPosiciones(ListaPosiciones,Objetivo):
    MenorDist = Distancia(ListaPosiciones[0],Objetivo)
    MenorPos=0
    i=1
    while(i<len(ListaPosiciones)):
        Dist=Distancia(ListaPosiciones[i],Objetivo)
        if Dist<MenorDist:
            MenorDist=Dist
            Swap=ListaPosiciones[i]
            ListaPosiciones[i]=ListaPosiciones[MenorPos]
            ListaPosiciones[MenorPos]=Swap
            MenorPos=i
        i+=1
    return ListaPosiciones"""
def Explorar(Laberinto,Posicion,Objetivo):
    DicV = [-1,1,0,0]
    DicH = [0,0,1,-1]
    Dimension = len(Laberinto)
    Adyacentes = []
    i=0
    while(i<4):
        X = Posicion[0]+DicH[i]
        Y = Posicion[1]+DicV[i]
        if X>=0 and Y>=0 and X<Dimension and Y<Dimension and Laberinto[X][Y]!="1":
            Adyacentes.append((X,Y))
        i+=1
    return Adyacentes
            
def ResolverLaberinto(Laberinto,Inicio,Objetivo):
    Queue = []
    Queue.append([Inicio])
    Explorados = []
    Solucion = []
    LlegarObjetivo = False
    while(not LlegarObjetivo and Queue!=[]):
        Path = Queue.pop()
        Nodo = Path[-1]
        Vecinos = Explorar(Laberinto,Nodo,Objetivo)
        for Hijo in Vecinos:
            if Hijo not in Explorados:
                NewPath = Path + [Hijo]
                Queue.append(NewPath)
                if Laberinto[Hijo[0]][Hijo[1]]=="X":
                    LlegarObjetivo = True
                    Solucion = NewPath
        Explorados.append(Nodo)
    return Solucion
def ImprimirSolucion(Solucion):
    for Pasos in Solucion:
        print((Pasos[0]+1,Pasos[1]+1))
def main():
    Entrada = open("salida.txt","r")
    Laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
    Entrada.close()
    Salida_Objetivo=Encontrar(Laberinto)
    Recorrido = ResolverLaberinto(Laberinto,Salida_Objetivo[0],Salida_Objetivo[1])
    ImprimirSolucion(Recorrido)
main()