#include <LiquidCrystal.h>

/**
 * CONSTANTS PIN FIRST NUMBER
 */
const byte PIN_OPERATION = 14;

/**
 * CONSTANTS PIN FIRST NUMBER
 */
const byte PIN_FIRST_NUM_1 = 10;
const byte PIN_FIRST_NUM_2 = 11;
const byte PIN_FIRST_NUM_3 = 12;
const byte PIN_FIRST_NUM_4 = 13;

/**
 * CONSTANTS PIN SECOND NUMBER
 */
const byte PIN_SECOND_NUM_1 = 6;
const byte PIN_SECOND_NUM_2 = 7;
const byte PIN_SECOND_NUM_3 = 8;
const byte PIN_SECOND_NUM_4 = 9;

/**
 * CONSTANTS PIN DISPLAY
 */
const byte DISPLAY_RS = 0;
const byte DISPLAY_ENABLE = 1;
const byte DISPLAY_D4 = 5;
const byte DISPLAY_D5 = 4;
const byte DISPLAY_D6 = 3;
const byte DISPLAY_D7 = 2;

/**
 * Initialize a instance LiquidCrystal.
 */
LiquidCrystal lcd(
  DISPLAY_RS,
  DISPLAY_ENABLE,
  DISPLAY_D4,
  DISPLAY_D5,
  DISPLAY_D6,
  DISPLAY_D7
);

int valorAUm, valorADois, valorATres, valorAQuatro;
int valorBUm, valorBDois, valorBTres, valorBQuatro;

int operation, operationBefore = -1, resultBefore = 0;

/**
 * Returns the operation output result.
 *
 * @param int valueA
 * @param int valueB
 * @param int residual
 * return bool
 */
bool operationOutput(int valueA, int valueB, int residual)
{
  return (valueA && !valueB && !residual) || (!valueA && !valueB && residual) || (valueA && valueB && residual) || (!valueA && valueB && !residual);
}

/**
 * Returns the remainder of the operation.
 *
 * @param int valueA
 * @param int valueB
 * @param int residual
 * @param int operation
 * return bool
 */
bool residualOperation(int valueA, int valueB, int residual, int operation)
{
  return (valueB && residual) || (!operation && valueA && valueB) || (!operation && valueA && residual) || (operation && !valueA && valueB) || (operation && !valueA && residual);
}

/**
 * Convert result values(valueA, valueB, valueC, valueD, operation) to decimal.
 *
 * @param int valueA
 * @param int valueB
 * @param int valueC
 * @param int valueD
 * @param int operation
 * return int
 */
int convertToDecimal(int valueA, int valueB, int valueC, int valueD, int operation) 
{
  return (valueA * 1) + (valueB * 2) + (valueC * 4) + (valueD * 8) + (operation * 16);
}

/**
 * Initialize a pin mode.
 */
void setup() 
{
  pinMode(PIN_OPERATION, INPUT);
  
  pinMode(PIN_FIRST_NUM_1, INPUT);
  pinMode(PIN_FIRST_NUM_2, INPUT);
  pinMode(PIN_FIRST_NUM_3, INPUT);
  pinMode(PIN_FIRST_NUM_4, INPUT);
  
  pinMode(PIN_SECOND_NUM_1, INPUT);
  pinMode(PIN_SECOND_NUM_2, INPUT);
  pinMode(PIN_SECOND_NUM_3, INPUT);
  pinMode(PIN_SECOND_NUM_4, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  delay(2000);
  lcd.clear();
}

/**
 * System Loop.
 */
void loop() 
{
  operation = digitalRead(PIN_OPERATION);
  
  valorAUm = digitalRead(PIN_FIRST_NUM_1);
  valorADois = digitalRead(PIN_FIRST_NUM_2);
  valorATres = digitalRead(PIN_FIRST_NUM_3);
  valorAQuatro = digitalRead(PIN_FIRST_NUM_4);
  
  valorBUm = digitalRead(PIN_SECOND_NUM_1);
  valorBDois = digitalRead(PIN_SECOND_NUM_2);
  valorBTres = digitalRead(PIN_SECOND_NUM_3);
  valorBQuatro = digitalRead(PIN_SECOND_NUM_4);

  int output1 = operationOutput(valorAUm, valorBUm, 0);
  int residual = residualOperation(valorAUm, valorBUm, 0, operation);
    
  int output2 = operationOutput(valorADois, valorBDois, residual);
  	  residual = residualOperation(valorADois, valorBDois, residual, operation);
  
  int output3 = operationOutput(valorATres, valorBTres, residual);
  	  residual = residualOperation(valorATres, valorBTres, residual, operation);
  
  int output4 = operationOutput(valorAQuatro, valorBQuatro, residual);
  	  residual = residualOperation(valorAQuatro, valorBQuatro, residual, operation);

  int resultA = convertToDecimal(valorAUm, valorADois, valorATres, valorAQuatro, 0);
  int resultB = convertToDecimal(valorBUm, valorBDois, valorBTres, valorBQuatro, 0);
  
  int result = convertToDecimal(output1, output2, output3, output4, residual);

  if (operation != operationBefore || result != resultBefore) {
    lcd.clear();
    resultBefore = result;
    operationBefore = operation;
  }
  
  lcd.setCursor(0, 0);
  lcd.print(resultA);

  if(operation == 1) {
    lcd.print(" - ");

  	if(resultA < resultB) {
  		result -= 32;
    }
  } else {
  	lcd.print(" + ");
  }

  lcd.print(resultB);

  lcd.setCursor(2, 1);
  lcd.print(result);
  
  delay(10);
}