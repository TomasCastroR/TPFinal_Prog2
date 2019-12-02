import subprocess
from math import sqrt
import random

def encontrar(laberinto,dimension):
    fila = 0
    columna = 0
    encontrado = 0
    while(fila<dimension and encontrado<2):
        while(columna<dimension and encontrado<2):
            if(laberinto[fila][columna]=="I"):
                inicio = (fila,columna)
                encontrado +=1
            if(laberinto[fila][columna]=="X"):
                final = (fila,columna)
                encontrado +=1
            columna+=1
        columna = 0
        fila+=1
    return (inicio,final)
def distancia(nodo,objetivo):
    return sqrt(pow(objetivo[0]-nodo[0],2)+pow(objetivo[1]-nodo[1],2))
def ordenarPorDistancia(listaNodos,objetivo):
    listaDistancia = []
    listaOrdenada = []
    for nodo in listaNodos:
        Dist = distancia(nodo,objetivo)
        listaDistancia.append((nodo[0],nodo[1],Dist))
    listaOrdenada.sort(key=lambda tupla: tupla[2])
    for nodo in listaDistancia:
        listaOrdenada.append((nodo[0],nodo[1]))
    return listaOrdenada

def explorar(laberinto,nodo,objetivo,dimension):
    DicV = [1,0,-1,0]
    DicH = [0,1,0,-1]
    Adyacentes = []
    i=0
    while(i<4):
        X = nodo[0] + DicV[i]
        Y = nodo[1] + DicH[i]
        if X>=0 and Y>=0 and X<dimension and Y<dimension and laberinto[X][Y]!="1":
            Adyacentes.append((X,Y))
        i+=1
    Adyacentes = ordenarPorDistancia(Adyacentes,objetivo)
    return Adyacentes
            
def resolverLaberinto(laberinto,inicio,objetivo,dimension):
    Queue = []
    Queue.append([inicio])
    Solucion = []
    llegarObjetivo = False
    while(not llegarObjetivo and Queue!=[]):
        print(Queue)
        path = Queue.pop()
        nodo = path[-1]
        if laberinto[nodo[0]][nodo[1]]!=-1:
            laberinto[nodo[0]][nodo[1]]=-1
            vecinos = explorar(laberinto,nodo,objetivo,dimension)
            for nodoVecino in vecinos:
                if laberinto[nodoVecino[0]][nodoVecino[1]]!=-1:
                    newPath = path + [nodoVecino]
                    Queue.append(newPath)
                    if laberinto[nodoVecino[0]][nodoVecino[1]]=="X":
                        llegarObjetivo = True
                        Solucion = newPath
    return Solucion               
def imprimirSolucion(Solucion,intentos):
    for pasos in Solucion:
        print((pasos[0]+1,pasos[1]+1))
def main():
    randomSeed = random.randint(0,100000)
    ejecutar = subprocess.run(["./a.exe","entrada.txt","salida.txt",str(randomSeed)])
    Entrada = open(ejecutar.args[2],"r")
    laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
    Entrada.close()
    dimension = len(laberinto)
    inicio_fin = encontrar(laberinto,dimension)
    recorrido = resolverLaberinto(laberinto,inicio_fin[0],inicio_fin[1],dimension)
    intentos = 0
    """while(recorrido == []):
        randomSeed = random.randint(0,100000)
        ejecutar = subprocess.run(["./a.exe","entrada.txt","salida.txt",str(randomSeed)])
        Entrada = open(ejecutar.args[2],"r")
        laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
        Entrada.close()
        recorrido = resolverLaberinto(laberinto,salida,dimension)
        intentos +=1"""
    imprimirSolucion(recorrido,intentos)
main()