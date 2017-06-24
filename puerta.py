import serial
import time
import push

arduino = serial.Serial('/dev/ttyUSB1', 9600) #ttyUSB0 para arduino nano , ttyACMo para arduino uno
arduino.open

txt = ''
print("........Bienvenido.......\n")
print("Configuracion:\n")

access = int(raw_input("El perrito tendra acceso a la puerta de la cocina?  0=NO, 1=SI ")) #acceso

print("........Configuracion completa.......\n")
if access == 1:
      print("El perrito tiene acceso a la cocina \n")
if access == 0:
      print("El perrito NO tiene acceso a la cocina \n")

while True:
      time.sleep(0.1)
      while arduino.inWaiting() > 0:
            txt = arduino.read(1)
            print txt
            if txt == "p":
                  if access == 1:
                        arduino.write("1")
                  else:
                        arduino.write("0")
            elif txt == "9":
                  push.sendNotification("8969e7c6b9d30c765ab2dea18fbed44a244a880d", "access-door", "Puerta bloqueada :( ")
            txt = ''
arduino.close() #Finalizamos la comunicacion
