import random

file = open("Populace_vlastnosti.txt","w+")

for i in range(300):
    file.write("{a} {b} {c} {d}\n".format(a = random.randint(50,100)/100,b = random.randint(0,100)/100, c= random.randint(33,100)/100, d = random.randint(0,1)))

file = open("Populace_stavy.txt","w+")
file.write("0 1 0 1\n")
file.write("0 1 0 1\n")
file.write("0 1 0 1\n")
for i in range(297):
    file.write("1 0 0 1\n")