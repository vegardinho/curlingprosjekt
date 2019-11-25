import serial #bibliotek som gjør at vi kan bruke USB-inngangen som seriell port
from firebase import firebase #bibliotek som gjør at vi kan sende data til firebase-databsen
firebase = firebase.FirebaseApplication('https://etellerannet.com/') #link til prosjektet i firebase-databasen


data = {}
ser = serial.Serial('/dev/ttyACM0', 9600) #serial port USB er koblet til, baudrate
ser.flushInput() #rengjør "input buffer"
liste = [0,0,0] #inneholder verdiene for akselerasjon, gyroskop og konduktans-sensoren
ant = 20 # midlertidig grense for hvor mange ganger det skal sendes data til databsen
x = 0

while ant > 0:
    #Serial leser en verdi om gangen, og vi har tre verdier for hver oppdatering
    #lagrer de tre verdiene i 'liste' og bruker dem til å oppdatere dictionaryen
    for x in range(3):
        inputValue = ser.read(1)  #leser verdien som kommer på serial-inngangen
        valueOut = ord(inputValue) #bruker ord() siden den verien som blir sendt ikke er en int
        liste[x] = valueOut

    data['aks'] = liste[0]
    data['gyro'] = liste[1]
    data['cond'] = liste[2]

    #print(data)

    result = firebase.post('/data', data) #sender dataen til firebase-databasen
    ant -= 1 #trekker fra en hver loop, slik at vi til slutt stopper å sende data

