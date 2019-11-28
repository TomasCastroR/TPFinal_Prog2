import subprocess

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
def ResolverLaberinto(Inicio,Final):
    
def main():
    Entrada = open("salida.txt","r")
    Laberinto =list(map(lambda linea:list(linea.strip()),Entrada.readlines()))
    Entrada.close()
    Salida_Objetivo=Encontrar(Laberinto)
    ResolverLaberinto(Salida_Objetivo[0],Salida_Objetivo[1])
main()