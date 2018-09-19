import sys
import os

from subprocess import PIPE, run

def out(command):
    result = run(command, stdout=PIPE, stderr=PIPE, universal_newlines=True, shell=True)
    return result.stdout
 
f= open(sys.argv[1] + ".txt","w+")

t_omp = []
t_seq =[]

print("Escrevendo arquivo de saida...")
for i in range (1,5):
        comando = "./exefs" + " ../" + str(sys.argv[2]) + str(i)
        tempo = out(comando)
        print("omp " + str(i) + "->tempo=" + tempo)
        t_omp.append(tempo)

        comando = "./exsomp" + " ../" + str(sys.argv[2]) + str(i)
        tempo = out(comando)
        print("seq " + str(i) + "->tempo=" + tempo)
        t_seq.append(tempo)

f.write("t_omp=[")
for i in range (0,4):
    if(i!=3):
        f.write(t_omp[i] + ',')
    else:
        f.write(t_omp[i])
f.write("]"+ '\n')

f.write("t_seq=[")
for i in range (0,4):
    if(i!=3):
        f.write(t_seq[i] + ',')
    else:
        f.write(t_seq[i])
f.write("]"+ '\n')