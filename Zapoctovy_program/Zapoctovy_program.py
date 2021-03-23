import random
import numpy as np
import matplotlib.pyplot as plt

class Jedinec:

    def __init__(self,vlastnosti, stavy):
        self.vlastnost =  vlastnosti
        self.stav = stavy
        self.cas = [0]*len(stavy)

        self.bylvinterakci = []
        self.pocetinterakci = []

        self.poloha = self.umisti()
        self.cil = self.umisti()
        self.posuny = (0, 0)
        self.pohyb = False

    def umisti(self):
        a = random.randint(0,rozmer[0])
        b = random.randint(0,rozmer[1])
        return (a,b)

    def hniSe(self,dp):
        if not self.pohyb:
            while self.cil == self.poloha:
                self.cil = (random.randint(0,rozmer[0]),random.randint(0,rozmer[1]))
            x0,y0 = self.poloha[0],self.poloha[1]
            x1,y1 = self.cil[0],self.cil[1]
            dx = np.sqrt(((x1-x0)**2)/((x1-x0)**2+(y1-y0)**2))*dp
            dy = np.sqrt(((y1-y0)**2)/((x1-x0)**2+(y1-y0)**2))*dp
            if x1<x0:
                dx = -dx
            if y1<y0:
                dy = -dy
            self.posuny = (dx,dy)
            self.pohyb = True
        else:
            x0, y0 = self.poloha[0], self.poloha[1]
            x1, y1 = self.cil[0], self.cil[1]
            vzdalenost = np.sqrt((x1-x0)**2+(y1-y0)**2)
            if vzdalenost > dp:
                self.poloha = (self.poloha[0]+self.posuny[0],self.poloha[1]+self.posuny[1])
            else:
                self.poloha = self.cil
                self.pohyb = False

    def vyhodnotPravdepodobnosti(self,pst):
        for i in range(len(pst)):
            p = round(pst[i],2)
            rand = random.randint(1,101)
            if rand <= p*100:
                self.stav[i] = 1-self.stav[i]
                self.cas[i] = 0
                if self.stav[i] == 0:
                    soucet_stavu[i] -= 1
                else:
                    soucet_stavu[i] += 1

    def info(self):
        return "Jedinec: {v}, {s}".format(v= self.vlastnost,s=self.stav)

def nactiVlastnostiJedincu():
    vlastnosti = []
    file = open("Populace_vlastnosti.txt")
    for line in file:
        line = line.strip()
        line = line.split(" ")
        vlastnosti.append([float(x) for x in line])
    return vlastnosti

def nactiStavyJedincu():
    stavy = []
    file = open("Populace_stavy.txt")
    for line in file:
        line = line.strip()
        line = line.split(" ")
        stavy.append([int(x) for x in line])
    return stavy

def vytvorPopulaci(vlastnosti,stavy,n):
    populace = []
    soucet_stavu = [0]*n
    if len(vlastnosti) != len(stavy):
        raise RuntimeError("Matice vlastností a stavů jedinců nemají stejný počet řádků")
        exit(1)
    else:
        for x,y in zip(vlastnosti,stavy):
            populace.append(Jedinec(x,y))
            soucet_stavu = np.add(soucet_stavu,y)
    return populace,soucet_stavu

def nactiJmenaStavu():
    jmena = []
    file = open("Jmena_stavu.txt")
    for line in file:
        line = line.strip()
        jmena.append(line)
    return jmena

def vzdalenost(obj1,obj2):
    x0,y0 = obj1.poloha[0],obj1.poloha[1]
    x1,y1 = obj2.poloha[0],obj2.poloha[1]
    return np.sqrt((x1-x0)**2+(y1-y0)**2)

def zkontrolujVstup(stavy_jedincu,vlastnosti_jedincu,interakce_tab,prechod_tab):
    if (stavy_jedincu == [] or vlastnosti_jedincu == [] or interakce_tab == [] or prechod_tab == []):
        raise RuntimeError("Některý ze vstupů je prázdný")
        exit(1)
    if not (len(stavy_jedincu) == len(vlastnosti_jedincu) and len(vlastnosti_jedincu[0])==len(interakce_tab)==len(prechod_tab)
        and len(interakce_tab[0])==len(prechod_tab[0])):
        raise RuntimeError("Nesedí některý z rozměrů vstupu")
        exit(1)

def interakce(obj1, obj2, it):
    pst1, pst2 = [0]*len(it), [0]*len(it)
    for j in range(len(it)):
        if obj1.stav[j] == 1:
            for k in range(len(it)):
                if pst2[k] < it[j][k](obj1, obj2):
                    pst2[k] = round(it[j][k](obj1, obj2),2)
    for j in range(len(it)):
        if obj2.stav[j] == 1:
            for k in range(len(it)):
                if pst1[k] < it[j][k](obj2, obj1):
                    pst1[k] = round(it[j][k](obj2, obj1),2)
    obj1.vyhodnotPravdepodobnosti(pst1)
    obj2.vyhodnotPravdepodobnosti(pst2)

def prechod(jedinec, prechod):
    novystav = jedinec.stav.copy()
    for i in range(len(prechod)):
        if jedinec.stav[i]==1:
            for j in range(len(prechod)):
                if prechod[i][j](jedinec) == -1:
                    if jedinec.stav[j] == novystav[j]:
                        novystav[j] = 1-novystav[j]
                        jedinec.cas[j] = 0
                        if novystav[j] == 0:
                            soucet_stavu[j] -= 1
                        else:
                            soucet_stavu[j] += 1
                elif jedinec.cas[i] >= prechod[i][j](jedinec)*den and prechod[i][j](jedinec) !=0:
                    if jedinec.stav[j] == novystav[j]:
                        novystav[j] = 1 - novystav[j]
                        jedinec.cas[j] = 0
                        if novystav[j] == 0:
                            soucet_stavu[j] -= 1
                        else:
                            soucet_stavu[j] += 1
    jedinec.stav = novystav

def vykresliGraf(data,maxT,nazvystavu):
    x = np.arange(0,maxT,1)
    fig, axs = plt.subplots()
    for y,name in zip(data,nazvystavu):
        plt.plot(x,y, label = name)
    axs.grid(True, linestyle="-.")
    axs.set(xlim=(0,maxT-1),ylim=(-1,np.max(data)+1))
    axs.set_xlabel("Počet dní")
    axs.set_ylabel("Počet jedinců ve stavu")
    axs.set_title("Vývoj počtu jedinců ve stavu v závislosti na čase")
    plt.legend()
    plt.show()

"""
Následující blok obsahuje:
1- rozmer (šířka a výška) simuláční plochy
2- počet iterací za den
3- počet dní v simulaci
4- vzdálenost na kterou dojde k interakci
5- posun jedince za iteraci (spočítáno tak, aby jedinec za jeden den přešel vzdálenost odpovídající jedné úhlopříčce)
6- počet možných iterací dvou jedinců za den
"""
rozmer = (50,50)
den = 10
maxT = 150
int_vzdalenost = 0.75
dp = np.sqrt(rozmer[0]**2+rozmer[1]**2)/(den*4)
pocet_interakci = 1

jmena_stavu = nactiJmenaStavu()
interakce_tab = []
prechod_tab = []

pravdepodobnost_nakazeni = 0.10
inkubacni_doba = 10
doba_leceni = 14 + inkubacni_doba

interakce_tab = [[lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0],
          [lambda j1,j2: 0,lambda j1,j2: j1.stav[3]*pravdepodobnost_nakazeni*j2.stav[0],lambda j1,j2: 0,lambda j1,j2: 0],
                 [lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0],
                 [lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0,lambda j1,j2: 0]]

prechod_tab = [[lambda j: 0,lambda j: 0,lambda j: 0,lambda j: 0],
               [lambda j:-j.stav[0],lambda j: doba_leceni/j.vlastnost[0],
                lambda j: inkubacni_doba*(1-j.stav[2]),lambda j:(inkubacni_doba+1)*j.vlastnost[3]*j.stav[3]],
                [lambda j: 0,lambda j: 0,lambda j: j.stav[1]*(doba_leceni/j.vlastnost[0]-inkubacni_doba),lambda j: 0],
               [lambda j: 0,lambda j: 0,lambda j: 0,lambda j: 0]]

zkontrolujVstup(nactiStavyJedincu(),nactiVlastnostiJedincu(),interakce_tab,prechod_tab)

populace,soucet_stavu = vytvorPopulaci(nactiVlastnostiJedincu(),nactiStavyJedincu(),len(jmena_stavu))

data = []

for i in range(maxT):
    data.append(soucet_stavu.copy())
    for jedinec in populace:
        jedinec.bylvinterakci = []
        jedinec.pocetinterakci = []
    for j in range(den):
        for k in range(len(populace)):
            jed1 = populace[k]
            for l in range(k+1,len(populace)):
                jed2 = populace[l]
                if vzdalenost(jed1, jed2) <= int_vzdalenost:
                    if jed2 in jed1.bylvinterakci and jed1 in jed1.bylvinterakci:
                        a, b = jed1.bylvinterakci.index(jed2), jed2.bylvinterakci.index(jed1)
                        if jed1.pocetinterakci[a] <= pocet_interakci and jed2.pocetinterakci[b] <= pocet_interakci:
                            interakce(jed1, jed2, interakce_tab)
                            jed1.pocetinterakci[a] += 1
                            jed2.pocetinterakci[b] += 1
                    else:
                        interakce(jed1, jed2, interakce_tab)
                        jed1.bylvinterakci.append(jed2)
                        jed1.pocetinterakci.append(0)
                        jed1.pocetinterakci[-1] += 1
                        jed2.bylvinterakci.append(jed1)
                        jed2.pocetinterakci.append(0)
                        jed2.pocetinterakci[-1] += 1
            jed1.hniSe(dp)
            prechod(jed1, prechod_tab)
            jed1.cas = np.add(jed1.cas, [1] * len(jed1.cas))

    if soucet_stavu[1] == 0:
        print("Počet nakažených je 0. Ukončuji program v čase "+str(i+1))
        maxT = i+1
        break

data.append(soucet_stavu.copy())
vykresliGraf(np.array(data).T,maxT+1,jmena_stavu)
"""
Poznámky:
1- počet interakcí mezi libovolnými dvěma jedinci je omezen na určité číslo za den
2- grafy ukazují počet stavů jak na začátku simulace, tak na jejím konci
3- může se stát, že počet nakažených klesne na 0, v tom případě program ukončíme a vykreslíme dosavadní průběh
"""

