import random

for nb in range (1,11):

    nballs = nb*7
    balls = [0]*(nballs*nballs)

    idBall = 0
    for i in range(nballs):
        for j in range(nballs):
            x = i*10 + 5
            y = j*10 + 5
            raio = random.randint(1,3)
            massa = random.randint(1,5)
            vx = random.uniform(-10,10)
            vy = random.uniform(-10,10)
            balls[i*nballs + j] = [idBall,raio,massa,x,y,vx,vy]
            idBall+=1

    outFile = open("input" + str(nb) + ".txt", 'w')
    outFile.write(str(nballs*10) + " " +str(nballs*10) + " " + str(nballs*nballs) + "\n")
    outFile.write("0.001 1 1\n")
    for i in range(nballs*nballs):
        outFile.write("{0} {1} {2} {3} {4} {5} {6}\n".format(balls[i][0],balls[i][1],balls[i][2],balls[i][3],balls[i][4],balls[i][5],balls[i][6]))
    outFile.close()

