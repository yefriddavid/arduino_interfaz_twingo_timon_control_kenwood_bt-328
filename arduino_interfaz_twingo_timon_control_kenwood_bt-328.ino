// #include <SPI.h>

static const uint8_t pinNegro = 4; // 1
static const uint8_t pinMarron = 5; // 3
static const uint8_t pinRojo = 14;
static const uint8_t pinAzul = 13;            
static const uint8_t pinVerde = 15;
static const uint8_t pinAmarillo = 12;

static const uint8_t port = 2;

// asignamos variables para almacenar estado de los pines conectados a los cables del mando
int azul;
int verde;
int rojo;
int negro;
int amarillo;
int marron, ruletaSiguiente, ruletaAnterior, ruletaActual;
int pulsado,mantiene;


//byte KenwoodData; //variable initializer for data that will be sent to Kenwood stereo


static int ZERO = 0;
static int VOL_UP = 1;
static int VOL_DOWN = 2;
static int SKIP_BACKWARD = 3;
static int SKIP_FORWARD = 4;
static int PLAY_PAUSE = 5;
static int MUTE = 6;
static int SOURCE = 7;

const byte KenwoodCommArray[10] = {
  B00000000,  // 0) 00000000 11111111 zero
  B00101000,  // 1) 00101000 11010111 Volume up
  B10101000,  // 2) 10101000 01010111 Volume down
  B11010000,  // 3) 11010000 00101111 Skip forward
  B01010000,  // 4) 01010000 10101111 Skip backward
  B01110000,  // 5) 01110000 10001111 Play/pause
  B01101000,  // 6) 01101000 10010111 Mute
  B11001000 /// 7) 11001000 00110111 Source
};

const String KenwoodCommDescriptionArray[10] = {
  "zero",
  "Volume up",
  "Volume down",
  "Skip forward",
  "Skip backward",
  "Play/pause",
  "Mute",
  "Source"
};



void setup() 
{

  pinMode(pinMarron, INPUT_PULLUP); // Por defecto los pins de entrada en HIGH (PULLUP)
  pinMode(pinNegro, INPUT_PULLUP);
  pinMode(pinRojo, INPUT_PULLUP);

  pinMode(pinAzul, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);
  pinMode(port, OUTPUT);

//inicializamos pines a LOW.
  digitalWrite(pinAzul, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAmarillo, LOW);

  //Serial.begin(9600);
  // delay(10000);
  inicializaRuleta();

}



void loop() 
{
  // SendKenwoodMessage(B00010100);
  // delay(500);
  //SendKenwoodMessage(B00010100);
  //delay(500);
  readButtonActions();
}

void readButtonActions(){
  delay(150);
 // delay(250); 
 rojo = digitalRead(pinRojo);
 negro = digitalRead(pinNegro);
 //pinMode(port, OUTPUT);

   
 if (negro == LOW) // se van leyendo los pines maestros para ver si cambian de estado..
  {               
      //Serial.println("negro");

    pulsado = compruebaPinPulsado(pinNegro);
   // Serial.print(pulsado);
    if (pulsado == pinAzul)
    {
      // teclaMute();    // NEGRO + AZUL = MUTE  
      SendKenwoodMessage(MUTE);
      //Serial.println("Mute");
    }
    else if (pulsado == pinVerde)
      {
        //teclaSRCMas(); // NEGRO + VERDE = BOTON SRC+
        SendKenwoodMessage(SKIP_FORWARD);
        //Serial.println("src +");
      }
    else if (pulsado == pinAmarillo)
      {
       // teclaSRCMenos();   // NEGRO + AMARILLO = BOTON SRC-
       SendKenwoodMessage(SKIP_BACKWARD);
       //Serial.println("src -");
      }
  
 }
 else if (rojo == LOW)
 {
        //Serial.println("rojo");

    pulsado = compruebaPinPulsado(pinRojo);
    if (pulsado == pinAzul)
      {
       //teclaVolMas(); // ROJO + AZUL = BOTON VOL+
         SendKenwoodMessage(VOL_UP);
       // Serial.println("Volume Up");
       // SPI.transfer(21);
      }
     else if (pulsado == pinVerde)
      {
          //     Serial.println("burcar emisoras");

        SendKenwoodMessage(SOURCE);
        //teclaSalto();  // ROJO + VERDE = BOTON SALTO CD
      }
      else if (pulsado == pinAmarillo)
      {
       //teclaVolMenos();   //ROJO + AMARILLO = BOTON VOL-
         SendKenwoodMessage(VOL_DOWN); // este se queda
       // Serial.println("Volume Down");
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
       // Serial.println("ruedita abajo");
       SendKenwoodMessage(4);
       ruletaSiguiente = ruletaAnterior;
       ruletaAnterior = ruletaActual;
       ruletaActual = marron; 
    }
    else if (marron == ruletaAnterior) //baja una pista Y REORDENAMOS VARIABLES.
    {
       // teclaRuletaMenos();
       // Serial.println("ruedita arriba");
       SendKenwoodMessage(3);
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


























byte KenwoodData; //variable initializer for data that will be sent to Kenwood stereo

byte CarSWbuttonInput = 0; //initialize variable that will switch through different commands

/*
void setup() {
  pinMode(port, OUTPUT);
  //pinMode(led2, OUTPUT);
}


void loop() {
  
SendKenwoodMessage(1);
  delay(500);
SendKenwoodMessage(2);
  delay(500);
}
*/




void SendKenwoodMessage(int messageId) {
CarSWbuttonInput = messageId;
  PrepareKenwoodMessage(); // B10101000 down B00010100: up
  //PrepareKenwoodMessage();
  //Serial.println(KenwoodCommDescriptionArray[messageId]);
}

void PrepareKenwoodMessage() {
      const byte KenwoodAddress = B10111001;            
    

      const byte KenwoodCommArray[10] = {
        B00000000,  // 0) 00000000 11111111 zero
        B00010100,  // 1) 00101000 11010111 Volume up
        B00010101,  // 2) 10101000 01010111 Volume down
        B00001011,  // 3) 11010000 00101111 Skip forward
        B00001010,  // 4) 01010000 10101111 Skip backward
        B00001110,  // 5) 01110000 10001111 Play/pause
        B00010110,  // 6) 01101000 10010111 Mute
        B00010011}; // 7) 11001000 00110111 Source

  byte KenwoodCommand; //variable initializer for which command is chosen
  switch (CarSWbuttonInput) {
    case 0:    /*do nothing currently*/   Serial.println("No Button");   break;
    case 1:    KenwoodCommand = KenwoodCommArray[1]; Serial.println("Volume Up");   break;   //Volume up
    case 2:    KenwoodCommand = KenwoodCommArray[2]; Serial.println("Volume Down");   break;   //Volume down
    case 3:    KenwoodCommand = KenwoodCommArray[3]; Serial.println("Skip Forward");   break;   //Skip Forward
    case 4:    KenwoodCommand = KenwoodCommArray[4]; Serial.println("Skip Backward");   break;   //Skip Backward
    case 5:    KenwoodCommand = KenwoodCommArray[5]; Serial.println("Play/Pause");   break;   //1-6 button - Play/Pause
    case 6:    KenwoodCommand = KenwoodCommArray[6]; Serial.println("Mute");   break;   //Mute
    case 7:    KenwoodCommand = KenwoodCommArray[7]; Serial.println("Source");   break;   //Source
  }

    digitalWrite(port, LOW);     delayMicroseconds(9000); //turn ON for 9ms for Start
    digitalWrite(port, HIGH);    delayMicroseconds(4500); //turn OFF for 4.5ms for Start

    KenwoodData = KenwoodAddress;
  SendKenwoodBinary();  // Send Device Address
  KenwoodData = KenwoodCommand;
  SendKenwoodBinary();
  


    digitalWrite(port, LOW);     delayMicroseconds(562); // prender para finalizar
    digitalWrite(port, HIGH);    // apagar para finalizar
  
}

/*****************************************************************************/
void SendKenwoodBinary() {
  byte bit; //variable that flips through bits

  for (byte i=1; i<=2; i++) {
    if (i == 2) {   KenwoodData = ~KenwoodData;   } //also send inverted data
    
    for (byte X = 0; X <= 7; X++) {
      bit = bitRead(KenwoodData, X); //bitRead starts with LSB (least significant bit), meaning it reads right-most bit moving leftward
      if (bit == 0) {
        digitalWrite(port, LOW);     delayMicroseconds(562);  //keep ON for 562.5us
        digitalWrite(port, HIGH);    delayMicroseconds(562);  //keep OFF for 562.5us
      }
      else {  //(bit == 1)
        digitalWrite(port, LOW);     delayMicroseconds(562);  //keep ON for 562.5us
        digitalWrite(port, HIGH);    delayMicroseconds(1687); //keep OFF for 1687.5us
      }
    }
  }
}
