/**
 * CONSTANTS PIN
 */
const byte PIN_A = 12;
const byte PIN_B = 11;
const byte PIN_C = 10;
const byte PIN_D = 9;

/**
 * SEGMENTS PIN
 */
const byte SEGMENT_A = 7;
const byte SEGMENT_B = 8;
const byte SEGMENT_C = 4;
const byte SEGMENT_D = 3;
const byte SEGMENT_E = 2;
const byte SEGMENT_F = 6;
const byte SEGMENT_G = 5;

/**
 * Initialize a pin mode.
 */
void setup() 
{  
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_C, INPUT);
  pinMode(PIN_D, INPUT);
  
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);
  Serial.begin(9600);
}

/**
 * On Segment A.
 */
void onA(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool a = (pinB && pinC) || (!pinA && pinC && pinD) || (!pinA && pinB && pinD) || (pinA && !pinC && !pinD) || (pinA && !pinB && !pinC) || (!pinB && !pinD);
  Serial.println( a );
  digitalWrite(SEGMENT_A, a);
}

/**
 * On Segment B.
 */
void onB(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool b = (!pinA && !pinB) || (!pinA && !pinC && !pinD) || (!pinA && pinC && pinD) || (pinA && !pinC && pinD) || (!pinB && !pinD);
  Serial.println( b );
  digitalWrite(SEGMENT_B, b);
}

/**
 * On Segment C.
 */
void onC(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool c = (!pinA && pinD) || (!pinA && pinB || pinA && !pinB) || (!pinB && !pinC) || (pinA && !pinC && pinD);
  Serial.println( c );
  digitalWrite(SEGMENT_C, c);
}

/**
 * On Segment D.
 */
void onD(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool d = (!pinA && !pinB && !pinD) || (!pinB && pinC && pinD) || (pinB && !pinC && pinD) || (pinB && pinC && !pinD) || (pinA && !pinC && !pinD);
  Serial.println( d );
  digitalWrite(SEGMENT_D, d);
}

/**
 * On Segment E.
 */
void onE(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool e = (!pinB && !pinD) || (pinA && pinB) || (pinA && pinC) || (pinC && !pinD);
  Serial.println( e );
  digitalWrite(SEGMENT_E, e);
}

/**
 * On Segment F.
 */
void onF(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool f = (!pinC && !pinD) || (!pinA && pinB && !pinC) || (pinA && !pinB) || (pinA && pinC)  || (pinB && pinC && !pinD);
  Serial.println( f );
  digitalWrite(SEGMENT_F, f);
}

/**
 * On Segment G.
 */
void onG(byte pinA, byte pinB, byte pinC, byte pinD)
{
  bool g = (!pinA && !pinB && pinC) || (!pinA && pinB && !pinD) || (pinB && !pinC && pinD) || (pinA && pinB && pinC)  || (pinA && !pinB);
  Serial.println( g );
  digitalWrite(SEGMENT_G, g);
}

/**
 * System Loop.
 */
void loop() 
{
  byte pinA = digitalRead(PIN_A);
  byte pinB = digitalRead(PIN_B);
  byte pinC = digitalRead(PIN_C);
  byte pinD = digitalRead(PIN_D);

  onA(pinA, pinB, pinC, pinD);
  onB(pinA, pinB, pinC, pinD);
  onC(pinA, pinB, pinC, pinD);
  onD(pinA, pinB, pinC, pinD);
  onE(pinA, pinB, pinC, pinD);
  onF(pinA, pinB, pinC, pinD);
  onG(pinA, pinB, pinC, pinD);
  
  delay(500);
}

/*byte seven_seg_digits[16][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 },  // = Digito 9
                                 { 1,1,1,0,1,1,1 },  // = Digito A
                                 { 0,0,1,1,1,1,1 },  // = Digito B
                                 { 1,0,0,1,1,1,0 },  // = Digito C
                                 { 0,1,1,1,1,0,1 },  // = Digito D
                                 { 1,0,0,1,1,1,1 },  // = Digito E
                                 { 1,0,0,0,1,1,1 }   // = Digito F
                                 };

void setup() 
{  
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino 9 do Arduino ligado ao segmento PONTO
  writePonto(0);  // Inicia com o ponto desligado
}

void writePonto(byte dot)   //Funcao que aciona o ponto no display
{  
  digitalWrite(9, dot);
}

void sevenSegWrite(byte digit)  //Funcao que aciona o display
{
  byte pin = 2;
  //Percorre o array ligando os segmentos correspondentes ao digito
  for (byte segCount = 0; segCount < 7; ++segCount)  
  { 
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
    writePonto(1);  //Liga o ponto
    delay(100);   //Aguarda 100 milisegundos
    writePonto(0);  //Desliga o ponto
}

void loop() 
{
  //Contador de 0 a 15, ligando os segmentos correspondentes
  //0 a 9 = liga os segmentos correspondentes aos numeros
  //10 a 15 = Forma as letras A,B,C,D,E,F
  for (byte count = 0; count < 16; count++)
  {
     delay(500);
     sevenSegWrite(count);
  }
  delay(4000);
}*/