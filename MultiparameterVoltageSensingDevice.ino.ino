// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL873aSK-z"
#define BLYNK_DEVICE_NAME "MULTIPARAMETER VOLTAGE SENSING DEVICE"
#define BLYNK_AUTH_TOKEN "CqbCjamxV35uHfayr02WDDWgKbCmfKPp"
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D1,D2);
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define button1 D5
#define button2 D6
#define button3 D7
boolean buttons1=true;

Multiparameter Voltage Sensing Device

Department of Electronics and Communication Engineering,AJCE
boolean buttons2=true;
boolean buttons3=true;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "12345678";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void senddata()
{
// You can send any value at any time.
// Please don't send more that 10 values per second.
buttons1=digitalRead(button1);
buttons2=digitalRead(button2);
buttons3=digitalRead(button3);
if(buttons1==0)
{
float voltage = pzem.voltage();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("voltage : ");
lcd.setCursor(10,0);
lcd.print(voltage);
lcd.print("V");
double current = pzem.current();
lcd.setCursor(0,1);
lcd.print("current : ");
lcd.setCursor(6,1);
lcd.setCursor(10,1);
lcd.print(current);
lcd.print("A");
delay(3000);
}
if(buttons2==0)
{
float power = pzem.power();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("power : ");
lcd.setCursor(8,0);
lcd.print(power);
lcd.print("W");
float energy = pzem.energy();
lcd.setCursor(0,1);
lcd.print("energy : ");
//lcd.setCursor(10,1);
lcd.print(energy);
lcd.print("kWh");
delay(3000);
}
if(buttons3==0)
{
float frequency = pzem.frequency();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("frequency : ");
lcd.setCursor(12,0);
lcd.print(frequency);
lcd.print("Hz");
float pf = pzem.pf();
lcd.setCursor(0,1);
lcd.print("pf : ");
lcd.setCursor(8,0);
lcd.print(pf);
delay(3000);
}
float voltage = pzem.voltage();
Blynk.virtualWrite(V0,voltage);
Serial.print("Voltage: ");
Serial.print(voltage);
Serial.println("V");
lcd.setCursor(0,0);
lcd.print("voltage : ");
lcd.setCursor(10,0);
lcd.print(voltage);
lcd.print("V");
delay(500);
lcd.clear();
double current = pzem.current();
Blynk.virtualWrite(V1,current);
Serial.print("Current: ");
Serial.print(current);
Serial.println("A");
lcd.setCursor(0,0);
lcd.print("current : ");
lcd.setCursor(10,0);
lcd.print(current); lcd.print("A");
delay(500);
lcd.clear();
float power = pzem.power();
Blynk.virtualWrite(V2,power);
Serial.print("Power: ");
Serial.print(power);
Serial.println("W");
lcd.setCursor(0,0);
lcd.print("power : ");
lcd.print(power);
lcd.print("W");
delay(500);
lcd.clear();
float energy = pzem.energy();
Blynk.virtualWrite(V3,energy);
Serial.print("Energy: ");
Serial.print(energy,3);
Serial.println("kWh");
lcd.setCursor(0,0);
lcd.print("energy : ");
//lcd.setCursor(1,0);
lcd.print(energy);
lcd.print("kWh");
delay(500);
lcd.clear();
float frequency = pzem.frequency();
Blynk.virtualWrite(V4,frequency);
Serial.print("Frequency: ");
Serial.print(frequency, 1);
Serial.println("Hz");
lcd.setCursor(0,0);
lcd.print("frequency : ");
lcd.setCursor(12,0);
lcd.print(frequency);
lcd.print("Hz");
delay(500);
lcd.clear();
float pf = pzem.pf();
Blynk.virtualWrite(V5,pf);
Serial.print("PF: ");
Serial.println(pf);
lcd.setCursor(0,0);
lcd.print("pf : ");
lcd.setCursor(6,0);
lcd.print(pf);
delay(500);
lcd.clear();

}

void setup()
{
// Debug console Serial.begin(115200);
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);
Wire.begin(D4, D3); //sda,scl
lcd.begin();
lcd.home();
lcd.setCursor(2,0);
lcd.print("SMART ENERGY");
lcd.setCursor(5,1);
lcd.print("METER");
Blynk.begin(auth, ssid, pass);
timer.setInterval(3000L, senddata);
lcd.clear();
// You can also specify server:
//Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
// Setup a function to be called every second
}

void loop()
{
Blynk.run();
timer.run(); // Initiates BlynkTimer
}

For Tariff Calculation Code

# Import required libraries
import blynklib

# Blynk authentication token
BLYNK_AUTH = 'your_blynk_auth_token'

# Create Blynk instance
blynk = blynklib.Blynk(BLYNK_AUTH)

# Device variables
power_consumption = 100 # Power consumption of the device in watts
usage_duration = 4 # Usage duration in hours
electricity_rate = 0.12 # Electricity rate per kilowatt-hour

# Calculate bill function
def calculate_bill():
energy_consumed = (power_consumption / 1000) * usage_duration # Energy consumed in
kilowatt-hours
bill_amount = energy_consumed * electricity_rate # Total bill amount
return bill_amount

# Blynk virtual pin handler
@blynk.handle_event('write V1')
def write_virtual_pin_handler(pin, value):
# Retrieve values from Blynk app
power_consumption = int(blynk.virtual_write(1))
usage_duration = int(blynk.virtual_write(2))
electricity_rate = float(blynk.virtual_write(3))

# Calculate bill
bill_amount = calculate_bill()

# Display bill amount on Blynk app
blynk.virtual_write(4, bill_amount)

# Start Blynk connection
blynk.run()

