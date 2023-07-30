/* 				Twingo Stering Wheel Audio Stereo Contro For Keenwood 					*/
/*------------------+---------------+-------------------+-----------------------+---------------+-----------------------+*/
/*================= | Code Variable |	    Pin		|     Arnes Color 	|   Board Pin 	| 	Control Color	|*/
/*------------------+---------------+-------------------+-----------------------+---------------+-----------------------+*/
static const uint8_t pinVerde 	 = 	4; 	// 	| 	Green		| 	D2 	|	Green 		|
static const uint8_t pinMarron 	 = 	2; 	// 	| 	White 		|	D4 	|	Brown 		|
static const uint8_t pinAmarillo = 	15; 	// 	| 	Yellow		|	D8 	|	Yellow 		|
static const uint8_t pinAzul 	 = 	12; 	// 	| 	Blue		|	D6 	|	Light Blue 	|
static const uint8_t pinNegro 	 = 	13; 	//	| 	White/Brown 	|	D7 	|	Black		|
static const uint8_t pinRojo 	 = 	14; 	// 	| 	White/Orange 	|	D5 	|	Red 		|
/*------------------------------------------------------+---------------+---------------+-------------------------------+*/

static const uint8_t stereoOutput = 5; // output -> yellow D1

int azul;
int verde;
int rojo;
int negro;
int amarillo;
int marron, ruletaSiguiente, ruletaAnterior, ruletaActual;
int pulsado, mantiene;

static int ZERO = 0;
static int VOL_UP = 1;
static int VOL_DOWN = 2;
static int SKIP_BACKWARD = 3;
static int SKIP_FORWARD = 4;
static int PLAY_PAUSE = 5;
static int MUTE = 6;
static int SOURCE = 7;

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

  // Por defecto los pins de entrada en HIGH (PULLUP)
  pinMode(pinMarron, INPUT_PULLUP); 	// for wheel
  pinMode(pinNegro, INPUT_PULLUP); 	// for buttons
  pinMode(pinRojo, INPUT_PULLUP); 	// for buttons

  pinMode(pinAzul, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);

  pinMode(stereoOutput, OUTPUT); // For send kenwood commands

  //inicializamos pines a LOW.
  digitalWrite(pinAzul, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAmarillo, LOW);

  // Serial.begin(9600);
  // delay(10000);
  inicializaRuleta();

}



void loop()
{
  readButtonActions();
}

void readButtonActions() {
  // delay(200);
  delay(250);
  rojo = digitalRead(pinRojo);
  negro = digitalRead(pinNegro);

  if (negro == LOW) // se van leyendo los pines maestros para ver si cambian de estado..
  {
    Serial.println("Black:");
    pulsado = compruebaPinPulsado(pinNegro);
    if (pulsado == pinAzul)
    {
      SendKenwoodMessage(MUTE);
    }
    else if (pulsado == pinVerde)
    {
      SendKenwoodMessage(SKIP_BACKWARD);
    }
    else if (pulsado == pinAmarillo)
    {
      SendKenwoodMessage(SKIP_FORWARD);
    }

  }
  else if (rojo == LOW)
  {
    Serial.println("Red:");
    pulsado = compruebaPinPulsado(pinRojo);
    if (pulsado == pinAzul)
    {
      SendKenwoodMessage(VOL_UP);
    }
    else if (pulsado == pinVerde)
    {
      SendKenwoodMessage(SOURCE);
    }
    else if (pulsado == pinAmarillo)
    {
      SendKenwoodMessage(VOL_DOWN);
    }
  }
  
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
      SendKenwoodMessage(SKIP_FORWARD);
      ruletaSiguiente = ruletaAnterior;
      ruletaAnterior = ruletaActual;
      ruletaActual = marron;
    }
    else if (marron == ruletaAnterior) //baja una pista Y REORDENAMOS VARIABLES.
    {
      SendKenwoodMessage(SKIP_BACKWARD);
      
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
    ruletaAnterior = pinAzul;
    ruletaSiguiente = pinVerde;
  }
}

int compruebaPinPulsado(int pinBuscado)
{
  
  digitalWrite(pinAzul, HIGH);
  if (digitalRead(pinBuscado) == HIGH)
  {
    pulsado = pinAzul;
    digitalWrite(pinAzul, LOW);
    return pulsado;
  }
  
  digitalWrite(pinAzul, LOW);
  digitalWrite(pinVerde, HIGH);
  if (digitalRead(pinBuscado) == HIGH)
  {
    pulsado = pinVerde;
    digitalWrite(pinVerde, LOW);
    return pulsado;
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
int before_millis;

void SendKenwoodMessage(int messageId) {
  CarSWbuttonInput = messageId;
  PrepareKenwoodMessage();
  Serial.println(KenwoodCommDescriptionArray[messageId]);

  int diff = millis() - before_millis;
  //Serial.println(diff);

  //Serial.println(before_millis);


  before_millis = millis();
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
    B00010011
  }; // 7) 11001000 00110111 Source

  byte KenwoodCommand;
  switch (CarSWbuttonInput) {
    case 0:    break; /*do nothing currently*/
    case 1:    KenwoodCommand = KenwoodCommArray[1]; break;   //Volume up
    case 2:    KenwoodCommand = KenwoodCommArray[2]; break;   //Volume down
    case 3:    KenwoodCommand = KenwoodCommArray[3]; break;   //Skip Forward
    case 4:    KenwoodCommand = KenwoodCommArray[4]; break;   //Skip Backward
    case 5:    KenwoodCommand = KenwoodCommArray[5]; break;   //1-6 button - Play/Pause
    case 6:    KenwoodCommand = KenwoodCommArray[6]; break;   //Mute
    case 7:    KenwoodCommand = KenwoodCommArray[7]; break;   //Source
  }

  digitalWrite(stereoOutput, LOW);     delayMicroseconds(9000); //turn ON for 9ms for Start
  digitalWrite(stereoOutput, HIGH);    delayMicroseconds(4500); //turn OFF for 4.5ms for Start

  KenwoodData = KenwoodAddress;
  SendKenwoodBinary();  // Send Device Address
  KenwoodData = KenwoodCommand;
  SendKenwoodBinary();

  digitalWrite(stereoOutput, LOW);     delayMicroseconds(562); // prender para finalizar
  digitalWrite(stereoOutput, HIGH);    // apagar para finalizar

}

/*****************************************************************************/
void SendKenwoodBinary() {
  byte bit;

  for (byte i = 1; i <= 2; i++) {
    if (i == 2) {
      KenwoodData = ~KenwoodData;
    }

    for (byte X = 0; X <= 7; X++) {
      bit = bitRead(KenwoodData, X); //bitRead starts with LSB (least significant bit), meaning it reads right-most bit moving leftward
      if (bit == 0) {
        digitalWrite(stereoOutput, LOW);     delayMicroseconds(562);  //keep ON for 562.5us
        digitalWrite(stereoOutput, HIGH);    delayMicroseconds(562);  //keep OFF for 562.5us
      }
      else {  //(bit == 1)
        digitalWrite(stereoOutput, LOW);     delayMicroseconds(562);  //keep ON for 562.5us
        digitalWrite(stereoOutput, HIGH);    delayMicroseconds(1687); //keep OFF for 1687.5us
      }
    }
  }
}
