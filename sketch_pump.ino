#include <ModbusRtu.h>

#include <uArmController.h>

#define ID   1      // адрес ведомого

uArmController uarm;

//Задаём ведомому адрес, последовательный порт, выход управления TX
Modbus slave(ID, 0, 0); 
unsigned long tempus;

// массив данных modbus
int8_t state = 0;
uint16_t au16data[11];

void setup() {
  // настраиваем последовательный порт ведомого
  uarm.init();
  slave.begin( 9600 );
  uarm.pumpOff();
  bitWrite( au16data[0], 0, 0);
}

void loop() {
  // обработка сообщений
  state = slave.poll( au16data, 11);  
  // если получили пакет без ошибок - зажигаем светодиод на 50 мс 
  if (state > 4) {
    //modbus coli 16
    if(bitRead( au16data[1], 0 ) == 1){
       uarm.pumpOn();
       bitWrite( au16data[0], 0, 1);                 
    }
    else{
      uarm.pumpOff();
      bitWrite( au16data[0], 0, 0);                 
    }
  }

}
