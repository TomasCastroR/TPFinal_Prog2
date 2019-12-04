import subprocess
from math import sqrt
import random
""" Diseño de datos:
    Representaremos un laberinto como una lista de listas (una matriz) donde cada lista representa
    una fila y la posicion en esa lista, la columna. Lo que se encuentra en cada casilla del laberinto se representa 
    a traves de un caracter string.

    Para representar la ubicacion, posicion, coordenadas de una casilla o nodo del laberinto usaremos una dupla (int,int)
    donde el primer elemento representa la fila - 1 y el segundo la columna - 1. Aunque luego, la impresion de la solucion
    las coordenas de los nodos seran a partir que la primer ubicacion es el (1,1)
    
    El programa comienza generando un numero random que sera la seedrand para el programa en C, luego ejecuta el archivo
    compilado de C pasando como argumenos el archivo de entrada, el nombre del texto de salida y la seedrand."""
    
# encontrar: List[List[string]] int -> Tupla(Tupla(int))
# Recibe un laberinto y su tamaño, devolve en forma de tupla las tuplas con las coordenadas
# de la salida y el objetivo respectivamente
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

# distancia: Tupla(int) Tupla(int) -> int
# Dado un nodo del laberinto y la posicion del objetivo, devuelve la distancia entre ellos
def distancia(nodo,objetivo):
    return sqrt((objetivo[0]-nodo[0])**2 + (objetivo[1]-nodo[1])**2)

# ordenarPorDistancia: List(Tupla(int)) Tupla(int)
# Dada una lista de nodos y la posicion del objetivo, ordena la lista en base a la distancia
# al objetivo de cada nodo de mayor a menor
def ordenarPorDistancia(listaNodos,objetivo):
    listaDistancia = []
    for nodo in listaNodos:
        Dist = distancia(nodo,objetivo)
        listaDistancia.append((nodo[0],nodo[1],Dist))

    listaNodos.clear()
    listaDistancia.sort(key=lambda tupla: tupla[2],reverse=True)
    for nodo in listaDistancia:
        listaNodos.append((nodo[0],nodo[1]))

# explorar: List(List(string)) Tupla(int) Tupla(int) int -> List(Tupla(int))
# Dado un laberinto, las coordenadas nodo del mismo, las coordenadas del objetivo y el tamaño del laberinto,
# devuelve una lista con los nodos adyacentes que no sean una pared al nodo de entrada ordenados
# por la distancia al objetivo
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
    ordenarPorDistancia(Adyacentes,objetivo)
    return Adyacentes

# resolverLaberinto: List(List(string)) Tupla(int) Tupla(int) int -> List(Tupla(int))
# Recibe un laberinto, las coordenadas de la salida y del inicio, y la dimension,
# devuelve una lista de coordenadas en secuencia que representan una solucion del laberinto
def resolverLaberinto(laberinto,inicio,objetivo,dimension):
    Stack = []
    Stack.append([inicio])
    Solucion = []
    llegarObjetivo = False
    while(not llegarObjetivo and Stack!=[]):
        path = Stack.pop(-1)
        nodo = path[-1]
        if laberinto[nodo[0]][nodo[1]]!="-1":
            laberinto[nodo[0]][nodo[1]]="-1"
            vecinos = explorar(laberinto,nodo,objetivo,dimension)
            for nodoVecino in vecinos:
                if laberinto[nodoVecino[0]][nodoVecino[1]]!="-1":
                    newPath = path + [nodoVecino]
                    Stack.append(newPath)
                    if laberinto[nodoVecino[0]][nodoVecino[1]]=="X":
                        llegarObjetivo = True
                        Solucion = newPath
    return Solucion

# imprimirSolucion: List(Tupla(int))
# Recibe una solucion del laberinto, imprime la secuencia de coordenadas en pantalla
def imprimirSolucion(Solucion,archivoSolucion,intentos):
    salida = open(archivoSolucion,"w")
    for pasos in Solucion:
        salida.write("({0},{1})\n".format(pasos[0]+1,pasos[1]+1))
    print(intentos)

def main():
    archivoEntradaC = "entrada.txt"
    archivoLaberinto = "salida.txt"
    archivoSalida = "solucion.txt"
    randomSeed = random.randint(0,10000000)
    ejecutar = subprocess.run(["./a.exe",archivoEntradaC,archivoLaberinto,str(randomSeed)])
    #Pregunta si se genero la salida, en caso que sea False significa que la entrada no era valida
    if(ejecutar.returncode == 0): 
        Entrada = open(ejecutar.args[2],"r")
        laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
        Entrada.close()
        dimension = len(laberinto)
        inicio_fin = encontrar(laberinto,dimension)
        recorrido = resolverLaberinto(laberinto,inicio_fin[0],inicio_fin[1],dimension)
        intentos = 0
        while(recorrido == []):
            randomSeed = random.randint(0,10000000)
            ejecutar = subprocess.run(["./a.exe",archivoEntradaC,archivoLaberinto,str(randomSeed)])
            Entrada = open(ejecutar.args[2],"r")
            laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
            Entrada.close()
            recorrido = resolverLaberinto(laberinto,inicio_fin[0],inicio_fin[1],dimension)
            intentos +=1
        imprimirSolucion(recorrido,archivoSalida,intentos)
main()
