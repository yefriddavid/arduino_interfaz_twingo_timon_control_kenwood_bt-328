#include <SPI.h>

int pinNegro = 8;
int pinMarron = 10;
int pinRojo = 6;
int pinAzul = 11;            
int pinVerde =7;
int pinAmarillo = 9;

// asignamos variables para almacenar estado de los pines conectados a los cables del mando
int azul;
int verde;
int rojo;
int negro;
int amarillo;
// ruletaSiguiente almacenará la posición que subiría pista desde la posición actual, Anterior la anterior y la ruletaActual, almacenará
// el color del cable que está tocando en el momento actual el codificador rotatorio, junto con el marrón (el común que siempre toca).
int marron, ruletaSiguiente, ruletaAnterior, ruletaActual;
// pulsado almacenará el nº (color) del pin que corresponde al botón pulsado del mando.
// mantiene chequea si hemos soltado o no el botón pulsado. Por ejemplo,
// si se mantiene el botón src, la radio se apagará.
int pulsado,mantiene;

#include "GPIO.h" //library I'm using for very fast digital pin control without needing to do direct port manipulation
GPIO<BOARD::D2> Kenw; //shortening Kenwood to Kenw so there will be less characters in functions


byte KenwoodData; //variable initializer for data that will be sent to Kenwood stereo

//byte CarSWbuttonInput = 0; //initialize variable that will switch through different commands



void setup() 
{
  Kenw.output(); //used with GPIO library for very fast digital pin control without using direct port manipulation
  Kenw = HIGH; //initialize to HIGH, because switching it LOW is for actual communications
  Kenw.input(); //change to input so that pin is floating, so IR remote can still function... turn back to OUTPUT to send a command

  
  //Se inicializan los pines conectados a los cables maestros del mando en modo pull up, es decir,
  //se mantienen en estado HIGH por defecto (mejora la fiabilidad de las señales en caso de ruido eléctrico)
  //se establecen como pines de entrada para leer la posible pulsación del azul, verde o amarillo,
  //que se usarán como pines de salida.
  pinMode(pinMarron, INPUT_PULLUP); // Por defecto los pins de entrada en HIGH (PULLUP)
  pinMode(pinNegro, INPUT_PULLUP);
  pinMode(pinRojo, INPUT_PULLUP);

  pinMode(pinAzul, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);

//inicializamos pines a LOW.
  digitalWrite(pinAzul, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAmarillo, LOW);

  Serial.begin(9600);
  // delay(10000);
  inicializaRuleta();

}


void loop() 
{

  delay(100);
 //delay(250); //introducimos un retardo de 250 ms para resolver ciertos problemas de sincronismo con la ruleta.
            // aún así, en alguna ocasión puntual al avanzar pista retrocede o viceversa.
 rojo = digitalRead(pinRojo); //leemos el estado del pin rojo y pin negro
 negro = digitalRead(pinNegro); //más abajo leemos la ruleta
 
 if (negro == LOW) // se van leyendo los pines maestros para ver si cambian de estado..
  {               
    pulsado = compruebaPinPulsado(pinNegro);
   // Serial.print(pulsado);
    if (pulsado == pinAzul)
    {
      // teclaMute();    // NEGRO + AZUL = MUTE  
      KenwoodOutput(6);
      Serial.println("Mute");
    }
    else if (pulsado == pinVerde)
      {
        //teclaSRCMas(); // NEGRO + VERDE = BOTON SRC+
        KenwoodOutput(3);
        Serial.println("src +");
      }
    else if (pulsado == pinAmarillo)
      {
       // teclaSRCMenos();   // NEGRO + AMARILLO = BOTON SRC-
       KenwoodOutput(4);
       Serial.println("src -");
      }
  
 }
 else if (rojo == LOW)
 {
    // Serial.println("LOW");
  
    pulsado = compruebaPinPulsado(pinRojo);
    if (pulsado == pinAzul)
      {
       //teclaVolMas(); // ROJO + AZUL = BOTON VOL+
         KenwoodOutput(1);
       Serial.println("Volume Up");
       // SPI.transfer(21);
      }
     else if (pulsado == pinVerde)
      {
               Serial.println("burcar emisoras");

        KenwoodOutput(7);
        //teclaSalto();  // ROJO + VERDE = BOTON SALTO CD
      }
      else if (pulsado == pinAmarillo)
      {
       //teclaVolMenos();   //ROJO + AMARILLO = BOTON VOL-
         KenwoodOutput(2); // este se queda
       Serial.println("Volume Down");
      }
 }
  
 //Serial.println(pulsado);
  //pulsado = 0;
  compruebaRuleta();
  
}


void compruebaRuleta()
{
  marron = compruebaPinPulsado(pinMarron);
  if (marron != ruletaActual) //COMPROBAMOS SI HA CAMBIADO EL ESTADO DE LA RULETA (SI SE HA GIRADO)
  {
    delay(10);
    if (marron == ruletaSiguiente) //sube una pista Y REORDENAMOS VARIABLES
    {
       //teclaRuletaMas();
       Serial.println("ruedita abajo");
       ruletaSiguiente = ruletaAnterior;
       ruletaAnterior = ruletaActual;
       ruletaActual = marron; 
    }
    else if (marron == ruletaAnterior) //baja una pista Y REORDENAMOS VARIABLES.
    {
       // teclaRuletaMenos();
       Serial.println("ruedita arriba");
       ruletaAnterior = ruletaSiguiente;
       ruletaSiguiente = ruletaActual;
       ruletaActual = marron; 
    }
  }
}

void inicializaRuleta()  //LEEMOS EL ESTADO INICIAL DE LA RULETA AL ENCENDER LA RADIO.
                          //Y ESTABLECEMOS LOS COLORES QUE SERÁN LA SIGUIENTE O LA ANTERIOR PISTA (Y EL ACTUAL)
  {
    ruletaActual = compruebaPinPulsado(pinMarron);
    if (ruletaActual == pinVerde)
    {
    ruletaSiguiente = pinAzul;
    ruletaAnterior = pinAmarillo;
    }
    else if (ruletaActual == pinAzul)
    {
    ruletaSiguiente = pinAmarillo;
    ruletaAnterior = pinVerde;
    }
    else if (ruletaActual == pinAmarillo)
    {
    ruletaAnterior=pinAzul;
    ruletaSiguiente=pinVerde;
    }
  }




int compruebaPinPulsado(int pinBuscado)
{
  digitalWrite(pinAzul, HIGH);
  if (digitalRead(pinBuscado) == HIGH)
    {
      pulsado = pinAzul;
    }
  digitalWrite(pinAzul, LOW);
  digitalWrite(pinVerde, HIGH);
  if (digitalRead(pinBuscado) == HIGH)
    {
      pulsado = pinVerde;
    }

  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAmarillo, HIGH);
  if (digitalRead(pinBuscado) == HIGH)
   {
    pulsado = pinAmarillo;
   }
   digitalWrite(pinAmarillo, LOW);
   return pulsado;
 }


void KenwoodOutput(int outputValue) {
  
      const byte KenwoodAddress = B10111001;
      const byte KenwoodCommArray[10] = {
        B00000000,  // 0) 00000000 11111111 zero
        B00010100,  // 1) 00101000 11010111 Volume up
        B00010101,  // 2) 10101000 01010111 Volume down
        B00001011,  // 3) 11010000 00101111 Skip forward
        B00001010,  // 4) 01010000 10101111 Skip backward
        B00001110,  // 5) 01110000 10001111 Play/pause
        B00010110,  // 6) 01101000 10010111 Mute
        B00010011 /// 7) 11001000 00110111 Source
      };
   //*4)End with 562.5us ON        */

  byte KenwoodCommand; //variable initializer for which command is chosen
  switch (outputValue) {
    case 0:    /*do nothing currently*/   Serial.println("No Button");   break;
    case 1:    KenwoodCommand = KenwoodCommArray[1]; break;   //Volume up
    case 2:    KenwoodCommand = KenwoodCommArray[2]; break;   //Volume down
    case 3:    KenwoodCommand = KenwoodCommArray[3]; break;   //Skip Forward
    case 4:    KenwoodCommand = KenwoodCommArray[4]; break;   //Skip Backward
    case 5:    KenwoodCommand = KenwoodCommArray[5]; break;   //1-6 button - Play/Pause
    case 6:    KenwoodCommand = KenwoodCommArray[6]; break;   //Mute
    case 7:    KenwoodCommand = KenwoodCommArray[7]; break;   //Source
    
    /*case 0:       Serial.println("No Button");   break; //do nothing currently
    case 1:    KenwoodCommand = KenwoodCommArray[1]; Serial.println("Volume Up");   break;   //Volume up
    case 2:    KenwoodCommand = KenwoodCommArray[2]; Serial.println("Volume Down");   break;   //Volume down
    case 3:    KenwoodCommand = KenwoodCommArray[3]; Serial.println("Skip Forward");   break;   //Skip Forward
    case 4:    KenwoodCommand = KenwoodCommArray[4]; Serial.println("Skip Backward");   break;   //Skip Backward
    case 5:    KenwoodCommand = KenwoodCommArray[5]; Serial.println("Play/Pause");   break;   //1-6 button - Play/Pause
    case 6:    KenwoodCommand = KenwoodCommArray[6]; Serial.println("Mute");   break;   //Mute
    case 7:    KenwoodCommand = KenwoodCommArray[7]; Serial.println("Source");   break;   //Source
    */
  }

//Sending data to Kenwood starts here:
  Kenw.output(); //need to turn pin to output
//  delay(15); //delay to give time for setting output pin type
  
  //Start signal:
    Kenw = LOW;     delayMicroseconds(9000); //turn ON for 9ms for Start
    Kenw = HIGH;    delayMicroseconds(4500); //turn OFF for 4.5ms for Start
  
  //Address code data:
    KenwoodData = KenwoodAddress;
    KenwoodCommanding();
  //Command code data:
    KenwoodData = KenwoodCommand;
    KenwoodCommanding();

  //End signal:
    Kenw = LOW;     delayMicroseconds(562); //turn ON for 562.5us for End
    Kenw = HIGH; //turn OFF to conclude transmission
  Kenw.input(); //turn pin back to INPUT to make it floating
}


/*****************************************************************************/
void KenwoodCommanding() {
  byte bit; //variable that flips through bits

  for (byte i=1; i<=2; i++) {
    if (i == 2) {   KenwoodData = ~KenwoodData;   } //also send inverted data
    
    for (byte X = 0; X <= 7; X++) {
      bit = bitRead(KenwoodData, X); //bitRead starts with LSB (least significant bit), meaning it reads right-most bit moving leftward
      if (bit == 0) {
        Kenw = LOW;     delayMicroseconds(562);  //keep ON for 562.5us
        Kenw = HIGH;    delayMicroseconds(562);  //keep OFF for 562.5us
      }
      else {  //(bit == 1)
        Kenw = LOW;     delayMicroseconds(562);  //keep ON for 562.5us
        Kenw = HIGH;    delayMicroseconds(1687); //keep OFF for 1687.5us
      }
    }
  }
}
