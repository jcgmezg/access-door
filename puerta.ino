/* Declaramos las variables */
long distancia;
long tiempo;
void finca();
void fincb();
int i=0;
char c;

void setup(){
Serial.begin(9600);
pinMode(9, OUTPUT);     //Declaramos el pin 9 como salida del pulso ultrasonico trig
pinMode(8, INPUT);      // Declaramos el pin 8 como entrasa (tiempo que tarda en volver) echo
pinMode(12, OUTPUT);    //led
pinMode(3, INPUT);      //peso
pinMode(6, INPUT);      //final de carrera alto
pinMode(7, INPUT);      // final de carrera bajo
pinMode(4, OUTPUT);     //motor1
pinMode(5, OUTPUT);     //motor2
pinMode(10, OUTPUT);     //obstruccion
}

void loop(){
  if (Serial.available());
  {
    int peso, fca, fcb, inter;
    
    i = 0;
    peso = digitalRead(3);
    fca = digitalRead(6);
    fcb = digitalRead(7);
   
      /* Se estabiliza el sensor */
      digitalWrite(9,LOW);
      delayMicroseconds(5);
      /* Se envia el pulso ultrasonico */
      digitalWrite(9, HIGH);
      delayMicroseconds(10);
      /* Mide el tiempo transcurrido entre la salida y la llegada del pulso ultrasonico */
      tiempo=pulseIn(8, HIGH);
      /* Se calcula la distancia on esta formila*/
      distancia= int(0.017*tiempo);
   
      if ((distancia < 15) and (peso == HIGH))
      {  
      //preguntar a RBP si es posible abrir 
      Serial.print("p");   //envia a la rbp p=pregunta
      delay(10); 
      c = Serial.read();
          if (c == '1')
          {
          inter = digitalRead(10);
          finca(fca);
          digitalWrite (4, LOW);
          delay(5000);
          fincb(fcb, inter, fca);
          digitalWrite (5, LOW);
          }
      }
      
}
}
void finca(int fca){
  while ( fca == LOW)
          {
            digitalWrite (4, HIGH);
            digitalWrite (5, LOW); 
            fca = digitalRead(6);
}
}
void fincb(int fcb, int inter, int fca){
  while ( fcb == LOW)
          {
             digitalWrite (4, LOW);
             digitalWrite (5, HIGH);
             fcb = digitalRead(7);
             inter = digitalRead(10);
             if( (inter == HIGH))
             {
                delay(500);
                i ++;
                if (i>2)
                {
                  while ( fca == LOW){
                    digitalWrite (4, HIGH);
                    digitalWrite (5, LOW); 
                    fca = digitalRead(6);
                  }
                  digitalWrite (4, LOW);
                  Serial.print("9");   //mandar senial a la raspberry 
                  break;
                }
                finca(fca);
             }
          }
}
