#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>

#define ID_ADDRESS 7
#define BAUDRATE_ADDRESS 8
#define ID_MOTOR 1

DynamixelDevice motor(ID_MOTOR);
uint8_t status = 0;
uint8_t idReaded = 0;
uint8_t baudrateReaded = 0;

void setup() {
  DxlMaster.begin(57600);
  Serial.begin(9600);
  status = motor.init();
  Serial.println(String("Motor inti: ") + status);

/*  
  uint8_t len;
  len = 1;
  
  uint8_t *data = new uint8_t[len];

  status = DxlMaster.read(2, ID_ADDRESS, len, data);
  Serial.println(String("ID status: ") + status);
  printData(data, len);

  for(uint8_t i=0; i<len; ++i)
  {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.print("\n\r");

  delete data;
*/

  printData(ID_MOTOR, 7, "ID", 1);
  motor.write(64, 0);
  delay(50);  

  printData(ID_MOTOR, 11, "Operating Mode BEFORE", 1);
  motor.write(11, 3);
  delay(50);
  printData(ID_MOTOR, 11, "Operating Mode AFTER", 1);
  motor.write(64, 1);
  delay(50);  
  printData(ID_MOTOR, 64, "Torque Enable", 1);
  printData(ID_MOTOR, 65, "LED", 1);
  motor.write(112, uint32_t(32));
  delay(50);  
  printData(ID_MOTOR, 112, "Profile Velocity", 4);
  motor.write(116, uint32_t(2048));
  delay(50);  
  printData(ID_MOTOR, 116, "Goal Position", 4);
  //baudrateReaded = motor.read(BAUDRATE_ADDRESS);
  //Serial.println(String("Baud rate: ") + idReaded);
}

void loop() {
  motor.write(65, 0);
  delay(300);
  motor.write(65, 1);
  delay(300);
  
}

//void printData(const uint8_t *data, uint8_t length)
void printData(uint8_t idDevice, uint8_t address, String typeRegister, uint8_t length)
{
  uint8_t *data = new uint8_t[length];

  status = DxlMaster.read(idDevice, address, length, data);
  Serial.println(String("Status ") + typeRegister + ": " + status);
  for(uint8_t i=0; i<length; ++i)
  {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.print("\n\r");
}
