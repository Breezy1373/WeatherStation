#include <DHT.h>
#include <OneWire.h>
#include <Adafruit_BMP280.h> //CHECK #define BMP280_ADDRESS mine works with (0x76)
#include <ESP8266WiFi.h>
#define DHTPIN 1        //GPIO1 (Tx)
#define DHTTYPE  DHT11
#define ONE_WIRE_BUS 3  // GPIO3=Rx
const char* ssid        = "Dog Food II"; //YOUR WIFI SSID
const char* password    = "Silentd3$"; //YOUR WIFIPASS
const char* host        = "api.thingspeak.com";
const char* writeAPIKey = "asd"; //YOUR APIKEY
//DHT11 stuff
float temperature_buiten;
float temperature_buiten2;
DHT dht(DHTPIN, DHTTYPE, 15);
//BMP280
Adafruit_BMP280 bmp;
void setup()
  {
    Serial.begin(115200);
    delay(500); 
    Serial.println("Starting setup");
    //I2C stuff
//    Wire.pins(0, 2);
//    Wire.begin(0, 2);
//    //DHT1
//    dht.begin();
//    //BMP280
//    if (!bmp.begin())
//      {
//         Serial.println("No BMP280");
//         //while (1) {}
//      }
    //Connect to WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.println("In Wifi loop");
        Serial.println(WiFi.status());
      }
    Serial.println(WiFi.macAddress());
  }
void loop()
  {
    //DHT11
//    float humidity    = dht.readHumidity();
//    float temperature = dht.readTemperature();
//    if (isnan(humidity) || isnan(temperature))
//      {
//        return;
//      }
    //BMP280
//      String t = String(bmp.readTemperature());
//      String p = String(bmp.readPressure());
//    //TCP CONNECTION
//    WiFiClient client;
//    const int httpPort = 80;
//    if (!client.connect(host, httpPort))
//      {
//        return;
//      }
//    String url = "/update?key=";
//    url += writeAPIKey;
//    url += "&field1=";
//    url += String(temperature); //DHT11 CELSIUS
//    url += "&field2=";
//    url += String(humidity); //DHT11 RELATIVE HUMIDITY
//    url +="&field3=";
//    url +=String(bmp.readTemperature()); //BMP280 CELSIUS
//    url +="&field4=";
//    url +=String(bmp.readPressure()/100); //BMP280 MILLIBAR
//    url +="&field5=";
//    url +=String(bmp.readAltitude(1013.25)); //BMP280 METER
//    url +="&field6=";
//    url +=String((temperature+bmp.readTemperature())/2); //DHT11 + BMP280 AVERAGE CELSIUS
//    url += "\r\n";
//    // Send request to the server
//    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                 "Host: " + host + "\r\n" +
//                 "Connection: close\r\n\r\n");
    delay(1000);
}
