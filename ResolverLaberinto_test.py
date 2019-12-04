from ResolverLaberinto import *

def test_encontrar():
    ejemplosFile = open("encontrarEjemplos.txt","r")
    resultadosFile = open("encontrarResultados.txt","r")
    ejemplos = ejemplosFile.readlines()
    resultados = resultadosFile.readlines()
    ejemplosFile.close()
    resultadosFile.close()
    cantTests = len(ejemplos)
    index = 0
    while(index < cantTests):
        dimension = len(eval(ejemplos[index]))
        assert encontrar(eval(ejemplos[index]),dimension)==eval(resultados[index])
        index += 1
def test_distancia():
    ejemplosFile = open("distanciaEjemplos.txt","r")
    resultadosFile = open("distanciaResultados.txt","r")
    ejemplos = ejemplosFile.readlines()
    resultados = resultadosFile.readlines()
    ejemplosFile.close()
    resultadosFile.close()
    cantTests = len(ejemplos)
    index = 0
    while(index < cantTests):
        ejemplo = eval(ejemplos[index])
        assert distancia(ejemplo[0],ejemplo[1]) == eval(resultados[index])
        index += 1
def test_explorar():
    ejemplosFile = open("explorarEjemplos.txt","r")
    resultadosFile = open("explorarResultados.txt","r")
    ejemplos = ejemplosFile.readlines()
    resultados = resultadosFile.readlines()
    ejemplosFile.close()
    resultadosFile.close()
    cantTests = len(ejemplos)
    index = 0
    while(index < cantTests):
        ejemplo = eval(ejemplos[index])
        assert explorar(ejemplo[0],ejemplo[1],ejemplo[2],ejemplo[3]) == eval(resultados[index])
        index += 1
def test_resolverLaberinto():
    ejemplosFile = open("resolverLaberintoEjemplos.txt","r")
    resultadosFile = open("resolverLaberintoResultados.txt","r")
    ejemplos = ejemplosFile.readlines()
    resultados = resultadosFile.readlines()
    ejemplosFile.close()
    resultadosFile.close()
    cantTests = len(ejemplos)
    index = 0
    while(index < cantTests):
        ejemplo = eval(ejemplos[index])
        assert resolverLaberinto(ejemplo[0],ejemplo[1],ejemplo[2],ejemplo[3]) == eval(resultados[index])
        index += 1
    