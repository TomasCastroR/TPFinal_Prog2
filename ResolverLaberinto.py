import subprocess
def ImprimirSolucion(Solucion):
    if(Solucion!=[]):
        for Pasos in Solucion:
            print(Pasos)
    else:
        print("Este laberinto no tiene solucion") 
        response = subprocess.run(["./a.exe","Entrada.txt"])
def Encontrar(Laberinto):
    Fila=0
    Columna=0
    Dimension=len(Laberinto)
    while(Fila<Dimension):
        while(Columna<Dimension):
            if(Laberinto[Fila][Columna]=="I"):
                Inicio=(Fila,Columna)
            elif (Laberinto[Fila][Columna]=="X"):
                Final=(Fila,Columna)
            Columna+=1
        Columna=0
        Fila+=1
    return (Inicio,Final)
def ResolverLaberinto(Laberinto,Inicio,Final):
    Visitados = [[False]*len(Laberinto)]*len(Laberinto)
    Camino = [Inicio]
    Visitados[Inicio[0]][Inicio[1]] = True
    LlegarObjetivo = False
    while(not LlegarObjetivo and Camino!=[]):
    

    return Camino

def main():
    Entrada = open("salida.txt","r")
    Laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
    Entrada.close()
    Salida_Objetivo=Encontrar(Laberinto)
    Recorrido = ResolverLaberinto(Laberinto,Salida_Objetivo[0],Salida_Objetivo[1])
    ImprimirSolucion(Recorrido)
main()