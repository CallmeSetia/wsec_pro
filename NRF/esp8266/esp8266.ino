// MULTITASK -- CONTROLLER
#include <pt.h>
struct pt SerialListener, WifiChecker, HTTP_Sender;
int incomingByte = 0;

// WIFI ESP8266
#include <ESP8266WiFi.h>

const char* SSID     = "polinema_hotspot_2G";
const char* PASSWORD = "";

int statusWifi = 0;
// HTTP
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String PROTOKOL = "http";
String HOST = "projek.bengkelti.com";
String TARGET = "pju";

String URL = PROTOKOL + "://" + HOST + "/" + TARGET + "";
String read1, read2, read3, read4;

// Sofware Serial
#include <SoftwareSerial.h>

#define terima_RX 5
#define terima_TX 4
SoftwareSerial terima(terima_RX, terima_TX); // RX, TX

void setup() {

  Serial.begin(57600); // Baudrate Harus Sama
  terima.begin(9600);

  Serial.println("Begin!");

  PROTOTHREAD_START();
  WIFI_START();

}

void loop() {

  cekStatusWifi(&WifiChecker, 10000);


  // Cek Ada Data Incoming
  if ( Serial.available() > 1 ) {

    String Read =  terima.readString(); //t#33#1.80#3.30
    read1 = parseString(Read, "#", 0);

    if (read1 == "t") {

      read2 = parseString(Read, "#", 1);
      read3 = parseString(Read, "#", 2);
      read4 = parseString(Read, "#", 3);

      int rcwl = read2.toInt();
      float tegangan = read3.toFloat();
      float arus = read4.toFloat();
      float daya = tegangan * arus;
      
      //http://projek.bengkelti.com/pju/dariESP.php?rcwlValue=2&teganganValue=3&dayaValue=2&arusValue=2
      String requestData = URL +  "/dariESP.php?rcwlValue=" + String(rcwl)
                           + "&teganganValue=" + String(tegangan) +
                           +  "&dayaValue=" + String(arus) +
                           +  "&arusValue=" + String(daya) + "";

      // ---
      // Debug
      // ---

      //      Serial.println("RCWL : " + String(rcwl) + " - Tegangan : " + String(tegangan) + " - Arus : " + String(arus) + + " - Daya : " + String(daya) + " - END " );
      //      delay(100);
      
      // ----
      // kirim ke database
      // ----

      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, requestData);
        int httpCode = http.GET();

        if (httpCode > 0) {
          String payload = http.getString();
          Serial.println(payload);
        }
        http.end();
      }
      else {
        konekWifi(SSID, PASSWORD);
      }
    }
  }

  delay(50);
}
