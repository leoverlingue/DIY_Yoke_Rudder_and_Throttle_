/*
  Código livre para utilização com o manche caseiro.
  Qualquer modificação e posterior não funcionamento dos componentes é de responsabilidade do usuário.
  Caso deseje modificar, fique atento aos itens já utilizados e aos limites da Biblioteca Joystick disponível para Arduino.
  Não foram utilizados as funcionalidades de manete de aceleração (throttle), acelerador (accelerator) e pedais de leme (rudder).
  Os mesmos foram implementados para testes, porém podem ser utilizados desde que sejam devidamente organizados para uso.
  Em caso de não utilização de algum bloco de código, o mesmo deve ser comentado para que não haja interferências no funcionamento do mesmo.
*/

#include <Joystick.h>

Joystick_ Joystick;

int xAxis_ = 0;
int yAxis_ = 0;
int zAxis_ = 0; 
int RxAxis_ = 0;                    
int RyAxis_ = 0;  
int RzAxis_ = 0;          
//int Throttle_ = 0;
//int Accelerator_ = 0;
//int Rudder_ = 0;

//Botões chave
const int Button_1_F1 = 2;
const int Button_1_F2 = 3;
const int Button_2_F1 = 4;
const int Button_2_F2 = 5;
//Botões freio
const int Button_3 = 6;
const int Button_4 = 7;
//Botão extra
const int Button_5 = 8;       

const bool initAutoSendState = true; 

int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;
int lastButtonState5 = 0;
int lastButtonState6 = 0;
int lastButtonState7 = 0;
int lastButtonState[2][4] = {{0,0,0,0}, {0,0,0,0}};

void setup() {
  pinMode(Button_1_F1,INPUT);
  pinMode(Button_1_F2,INPUT);
  pinMode(Button_2_F1,INPUT);
  pinMode(Button_2_F2,INPUT);
  pinMode(Button_3,INPUT_PULLUP);
  pinMode(Button_4,INPUT_PULLUP);
  pinMode(Button_5,INPUT_PULLUP);
 
  // Initialize Button Pins
  for (int index = 9; index < 13; index++) {
    pinMode(index, INPUT_PULLUP);
  }

  Joystick.begin();
}
   
void loop(){

//Profundor
xAxis_ = analogRead(A0);
xAxis_ = map(xAxis_,0,1023,0,255);
Joystick.setXAxis(xAxis_);

//Aileirons
yAxis_ = analogRead(A1);
yAxis_ = map(yAxis_,0,1023,0,255);
Joystick.setYAxis(yAxis_);

//Compensador
zAxis_ = analogRead(A5);  
zAxis_ = map(zAxis_,0,1023,0,255);
Joystick.setZAxis(zAxis_);  

//Manete motor 1
RxAxis_ = analogRead(A3);
RxAxis_ = map(RxAxis_,0,1023,0,255);
Joystick.setRxAxis(RxAxis_);

//Manete motor 2
RyAxis_ = analogRead(A4);
RyAxis_ = map(RyAxis_,0,1023,0,255);
Joystick.setRyAxis(RyAxis_);

//Pedais leme
RzAxis_ = analogRead(A2);
RzAxis_ = map(RzAxis_,1023,0,255,0);            
Joystick.setRzAxis(RzAxis_);

//Rudder_ = analogRead(A3);
//Rudder_ = map(Rudder_,1023,0,255,0);
//Joystick.setRudder(Rudder_);
  
//Throttle_ = analogRead(A4);
//Throttle_ = map(Throttle_,1023,0,255,0);         
//Joystick.setThrottle(Throttle_);

//Accelerator_ = analogRead(A5);
//Accelerator_ = map(Accelerator_,1023,0,255,0);
//Joystick.setAccelerator(Accelerator_);

int currentButtonState1 = !digitalRead(Button_1_F1);
if (currentButtonState1 != lastButtonState1) {
  Joystick.setButton(0,currentButtonState1);
  lastButtonState1 = currentButtonState1;
}

int currentButtonState2 = !digitalRead(Button_1_F2);
if (currentButtonState2 != lastButtonState2) {
  Joystick.setButton(1,currentButtonState2);
  lastButtonState2 = currentButtonState2;
}

int currentButtonState3 = !digitalRead(Button_2_F1);
if (currentButtonState3 != lastButtonState3) {
  Joystick.setButton(2,currentButtonState3);
  lastButtonState3 = currentButtonState3;
}

int currentButtonState4 = !digitalRead(Button_2_F2);
if (currentButtonState4 != lastButtonState4) {
  Joystick.setButton(3,currentButtonState4);
  lastButtonState4 = currentButtonState4;
}

int currentButtonState5 = !digitalRead(Button_3);
if (currentButtonState5 != lastButtonState5) {
  Joystick.setButton(4,currentButtonState5);
  lastButtonState5 = currentButtonState5;
}

int currentButtonState6 = !digitalRead(Button_4);
if (currentButtonState6 != lastButtonState6) {
  Joystick.setButton(5,currentButtonState6);
  lastButtonState6 = currentButtonState6;
}

int currentButtonState7 = !digitalRead(Button_5);
if (currentButtonState7 != lastButtonState7) {
  Joystick.setButton(6,currentButtonState7);
  lastButtonState7 = currentButtonState7;
}

//hatswitch
bool valueChanged[2] = {false, false};
int currentPin = 9;

// Read pin values
for (int hatSwitch = 0; hatSwitch < 1; hatSwitch++) {
  for (int index = 0; index < 4; index++) {
    int currentButtonState = !digitalRead(currentPin++);
    if (currentButtonState != lastButtonState[hatSwitch][index]) {
      valueChanged[hatSwitch] = true;
      lastButtonState[hatSwitch][index] = currentButtonState;
    }
  }
}

for (int hatSwitch = 0; hatSwitch < 1; hatSwitch++) {
  if (valueChanged[hatSwitch]) {
    if ((lastButtonState[hatSwitch][0] == 0)
    && (lastButtonState[hatSwitch][1] == 0)
    && (lastButtonState[hatSwitch][2] == 0)
    && (lastButtonState[hatSwitch][3] == 0)) {
      Joystick.setHatSwitch(hatSwitch, -1);
    }
    
    else if ((lastButtonState[hatSwitch][0] == 1) 
    && (lastButtonState[hatSwitch][1] == 1)) {
      Joystick.setHatSwitch(hatSwitch, 45);
    }
    else if ((lastButtonState[hatSwitch][1] == 1) 
    && (lastButtonState[hatSwitch][2] == 1)) {
      Joystick.setHatSwitch(hatSwitch, 135);
    }
    else if ((lastButtonState[hatSwitch][2] == 1) 
    && (lastButtonState[hatSwitch][3] == 1)) {
      Joystick.setHatSwitch(hatSwitch, 225);
    }
    else if ((lastButtonState[hatSwitch][3] == 1) 
    && (lastButtonState[hatSwitch][0] == 1)) {
      Joystick.setHatSwitch(hatSwitch, 315);
    }
    
    else if (lastButtonState[hatSwitch][0] == 1) {
      Joystick.setHatSwitch(hatSwitch, 0);
    }
    else if (lastButtonState[hatSwitch][1] == 1) {
      Joystick.setHatSwitch(hatSwitch, 90);
    }
    else if (lastButtonState[hatSwitch][2] == 1) {
      Joystick.setHatSwitch(hatSwitch, 180);
    }
    else if (lastButtonState[hatSwitch][3] == 1) {
      Joystick.setHatSwitch(hatSwitch, 270);
    }  
  } // if the value changed
} // for each hat switch
    
delay (50);
}
