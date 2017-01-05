/*
 * BT Config 
 * 1/5/17
 * Keith Nason
 * 
 *  Use terminal to configure BT module
 *  
 *  Used HC-05 and Arduino Uno
 *  
 *  BT Pins
 *  Tx  - 5
 *  Rx  - 4
 *  Key - 3
 *  
 * 
 */

 
#include <SoftwareSerial.h>
#define key 3
SoftwareSerial BTSerial(4,5); // Rx,Tx

// Settings
int sel = '0';


// Used to set new name, baud rate, password, role

String newName = "New BT Name";
String baud = "9600,0,0";
String pass = "1234";
int role = 0; //1 = master, 0 = slave, normally 0


// Strings for commands
String setName = String("AT+NAME=");
String checkStatus = String("AT");
String checkBaud = String("AT+UART");
String setBaud = String("AT+UART=");
String checkPass = String("AT+PSWD");
String setPass = String("AT+PSWD="); 
String checkName = String("AT+Name");
String checkAdd = String("AT+ADDR");
String checkRole = String("AT+ROLE");
String checkVersion = String("AT+Version");
String factRestore = String("AT+ORGL");
String setRole = String("AT+ROLE=");



void setup() {

//Init serial connections
 Serial.begin(9600);
 BTSerial.begin(9600);

// Set Key High for commands
 pinMode(key, OUTPUT);
 digitalWrite(key, HIGH);
 
// Check connection to module
 sel = '0'; 
 commands();

 delay(500);
 
//Write bt response to monitor
  while (BTSerial.available()) {
  Serial.write(BTSerial.read());
  } 

 
 
//Add blank line then tell options 
 Serial.println();
 selInfo();


  
}
    

void loop() {
 
//Wait for command
 while (!Serial.available());     
 int ComSel = Serial.read();        
 sel = (ComSel);

//Serial.println(sel);

commands();

  //Write bt response to monitor
  while (BTSerial.available()) {
  Serial.write(BTSerial.read());
}



}


void commands(){
  
  
  
switch (sel) {
 
 // Check Status  
  case '0':
   Serial.println("Checking connection");
   BTSerial.println(checkStatus);
   break;

//Check Name
   case '1':
   Serial.println("Checking name");
   BTSerial.println(checkName);
   break;

//Set Name
   case '2':
   Serial.println("Setting name");
   BTSerial.println(setName+newName);
   BTSerial.println(checkName);
   break;
   
//Check Address
   case '3':
   Serial.println("Checking address");
   BTSerial.println(checkAdd);
   break;

//Check Baud
   case '4':
   Serial.println("Checking baud rate");
   BTSerial.println(checkBaud);
   break;

//Set Baud
   case '5':
   Serial.println("Setting baud rate");
   BTSerial.println(setBaud+baud);
   break;

//Check Role
   case '6':
   Serial.println("Checking role");
   BTSerial.println(checkRole);
   break;

//Set Role
   case '7':
   Serial.println("Setting role");
   BTSerial.println(setRole+role);
   break;

//Check Pass
   case '8':
   Serial.println("Checking password");
   BTSerial.println(checkPass);
   break;

//Set Pass
   case '9':
   Serial.println("Setting password");
   BTSerial.println(setPass+pass);
   break;


//Check Version
   case 'V':
   Serial.println("Checking version");
   BTSerial.println(checkVersion);
   break;

//Factory Settings
   case 'R':
   Serial.println("Reseting to factory settings");
   BTSerial.println(factRestore);
   break;


//Repeat Options
   case 'O':
   selInfo();
   break;

//Format Notes
   case 'N':
   Serial.println("Baud is set as - BAUD , 0 , 0");
   Serial.println("Role is set by - 0 = Slave, 1 = Master");
   break;   
   

// Do nothing
  default:
    break;
    
}

delay(1000);

//Write bt response to monitor
  while (BTSerial.available()) {
      Serial.write(BTSerial.read());
    }
}

void selInfo(){

  Serial.println("Select Option, Case Sensitive");
  Serial.println("0 - Check Status");
  Serial.println("1 - Check Name");
  Serial.println("2 - Set Name");
  Serial.println("3 - Check Address");
  Serial.println("4 - Check Baud Rate");
  Serial.println("5 - Set Baud Rate");
  Serial.println("6 - Check Role");
  Serial.println("7 - Set Role");
  Serial.println("8 - Check Password");
  Serial.println("9 - Set Password");
  Serial.println("V - Check Version");
  Serial.println("R - Factory Reset");
  Serial.println("O - Repeat Options");
  Serial.println("N - Formatting Notes");
  Serial.println();
}

