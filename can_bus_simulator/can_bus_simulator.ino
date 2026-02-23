/*
 *   CAN Bus simulator by Igor Ramos
 *   
 *   commands: ? = help, 0 = stop sim, 1 = start sim (default on)
 *
 *   Sample output:
 *   
 *  CAN BUS simulator at 115200
 *   @0xB,8,488A2988405C2C87
 *   @0xB,8,A73492A393BA7B27
 *   @0xA,8,3449672D6558197B
 *   @0xB,8,D4D59B0D719EBDC3
 *   @0xA,8,DD1AD04865E04912
 *
 */
 
 const String ver  = "CAN BUS simulator at 115200";
const String help  = "Help = 0=stop, 1=go";
String payload = "Debug: ";
String canid = "0";
int run = '1';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(ver);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250);
  
  if(run == '1'){
    canid = String(10+random(0,2), HEX) ;
    payload = "";
    for (char i=0; i<16 ; i++){
      payload += String(random(15), HEX);
    }
    canid.toUpperCase();
    payload.toUpperCase();
    Serial.println("@0x" + canid + ",8," +  payload );
    //Serial.println("@0x0,11223344AABBCCDD");
  }


   while (Serial.available() > 0) {
       handleSerial(Serial.read());
   }

}

void handleSerial(int buf){
         Serial.print("[DEBUG] Serial Received: ");
         Serial.println(buf, DEC);
         if (buf == '?'){
            Serial.println(help);
         }
         else if (buf == '1'){
           Serial.println("start simulator");
           run = '1';
         }
         else if (buf == '0'){
          Serial.println("stop simulator");
          run = '0';
         }
         else if (buf == 10){
            //ignore enter
            delay(1);     
         }
         else{
            Serial.print("cmd not supported: ");
            Serial.println(buf, DEC);
         }
         delay(250);
  }

