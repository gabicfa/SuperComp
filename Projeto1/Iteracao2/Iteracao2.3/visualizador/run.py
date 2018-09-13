import os

from subprocess import PIPE, run

def out(command):
    result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
    return result.stdout

os.system("cmake .")  
os.system("make") 

f= open("out.txt","w+")

t_omp = []
t_simd= []
t_seq =[]

if(os.environ['GUI'] == '2'): 
    print("Escrevendo arquivo de saida...")
    for i in range (1,11):
            comando = "./visualizadorOMP < Inputs/input" + str(i) + ".txt"
            tempo = out(comando)
            print("omp input" + str(i) + "->tempo=" + tempo)
            t_omp.append(tempo)

            comando = "./visualizadorSIMD < Inputs/input" + str(i) + ".txt"
            tempo = out(comando)
            print("simd input" + str(i) + "->tempo=" + tempo)
            t_simd.append(tempo)

            comando = "./visualizadorSEQ < Inputs/input" + str(i) + ".txt"
            tempo = out(comando)
            print("seq input" + str(i) + "->tempo=" + tempo)
            t_seq.append(tempo)

    f.write("t_omp=[")
    for i in range (0,10):
        if(i!=9):
            f.write(t_omp[i] + ',')
        else:
            f.write(t_omp[i])
    f.write("]"+ '\n')

    f.write("t_simd=[")
    for i in range (0,10):
        if(i!=9):
            f.write(t_simd[i] + ',')
        else:
            f.write(t_simd[i])
    f.write("]"+ '\n')

    f.write("t_seq=[")
    for i in range (0,10):
        if(i!=9):
            f.write(t_seq[i] + ',')
        else:
            f.write(t_seq[i])
    f.write("]"+ '\n')