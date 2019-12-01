import subprocess
from math import sqrt

def Encontrar(Laberinto,Dimension):
    Fila=0
    Columna=0
    Encontrado=0
    while(Fila<Dimension and Encontrado<2):
        while(Columna<Dimension and Encontrado<2):
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
def Explorar(Laberinto,Posicion,Dimension):
    DicV = [1,0,-1,0]
    DicH = [0,1,0,-1]
    Adyacentes = []
    i=0
    while(i<4):
        X = Posicion[0]+DicV[i]
        Y = Posicion[1]+DicH[i]
        if X>=0 and Y>=0 and X<Dimension and Y<Dimension and Laberinto[X][Y]!="1":
            Adyacentes.append((X,Y))
        i+=1
    return Adyacentes
            
def ResolverLaberinto(Laberinto,Inicio,Dimension):
    Queue = []
    Queue.append([Inicio])
    Solucion = []
    LlegarObjetivo = False
    while(not LlegarObjetivo and Queue!=[]):
        Path = Queue.pop(0)
        Nodo = Path[-1]
        if Laberinto[Nodo[0]][Nodo[1]]!=-1:
            Vecinos = Explorar(Laberinto,Nodo,Dimension)
            for Hijo in Vecinos:
                if Laberinto[Hijo[0]][Hijo[1]]!=-1:
                    NewPath = Path + [Hijo]
                    Queue.append(NewPath)
                    if Laberinto[Hijo[0]][Hijo[1]]=="X":
                        LlegarObjetivo = True
                        Solucion = NewPath
        Laberinto[Nodo[0]][Nodo[1]]=-1
    return Solucion
def ImprimirSolucion(Solucion):
    for Pasos in Solucion:
        print((Pasos[0]+1,Pasos[1]+1))
def main():
    Entrada = open("salida.txt","r")
    Laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
    Entrada.close()
    Dimension = len(Laberinto)
    Salida_Objetivo=Encontrar(Laberinto,Dimension)
    Recorrido = ResolverLaberinto(Laberinto,Salida_Objetivo[0],Dimension)
    """while(Recorrido == []):
        response = subprocess.run(["./a.out","salida.txt"])
        Salida_Objetivo=Encontrar(Laberinto)
        Recorrido = ResolverLaberinto(Laberinto,Salida_Objetivo[0])"""
    ImprimirSolucion(Recorrido)
main()