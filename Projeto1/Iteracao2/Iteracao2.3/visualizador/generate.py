import random

balls = [0]*(100*100)
# print(balls)
k = 0
for i in range(100):
    for j in range(100):
        x = i*100 + 5
        y = j*100 + 5
        radius = random.randint(1,3)
        mass = random.randint(1,10)
        vx = random.uniform(-10,10)
        vy = random.uniform(-10,10)
        balls[i*100 + j] = [k,radius,mass,x,y,vx,vy]
        k+=1
for i in range(100*100):
    print("{0} {1} {2} {3} {4} {5} {6}".format(balls[i][0],balls[i][1],balls[i][2],balls[i][3],balls[i][4],balls[i][5],balls[i][6]))