// MULTITASK -- CONTROLLER
#include <pt.h>
struct pt SerialListener, WifiChecker, HTTP_Sender;
int incomingByte = 0;

// WIFI ESP8266
#include <ESP8266WiFi.h>

const char* SSID     = "AndroidAPF642";
const char* PASSWORD = "ydnerkusuma098";

int statusWifi = 0;

// HTTP
// A 5rx - D2tx, 6tx - D1rx
// N

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String PROTOKOL = "http";
String HOST = "projek.bengkelti.com";
String TARGET = "pju";

String URL = PROTOKOL + "://" + HOST + "/" + TARGET + "";
uint8_t x = 0;
String read1, read2, read3, read4, read5, read6;

// Sofware Serial
#include <SoftwareSerial.h>

#define terima_RX 5
#define terima_TX 4
SoftwareSerial terima(terima_RX, terima_TX); // RX, TX

void setup() {

  Serial.begin(57600); // Baudrate Harus Sama
  terima.begin(115200);

  Serial.println("Begin!");

  PROTOTHREAD_START();
  WIFI_START();
}

void loop() {

  cekStatusWifi(&WifiChecker, 10000);
  //  x++;
  //  Serial.println("TEST" + String(x));


  if ( Serial.available() > 1 ) {
    String Read =  Serial.readString(); //t#33#1.80#3.30
    read1 = parseString(Read, "#", 0);

    if (read1 == "t") {

      read2 = parseString(Read, "#", 1);
      read3 = parseString(Read, "#", 2);
      read4 = parseString(Read, "#", 3);

      Serial.print("READ SERIAL : " + String(read2.toInt())) ;
    }

  }

  // Cek Ada Data Incoming
  if ( terima.available() > 1 ) {
    //    Serial.println("1");

    //    String terimaData = terima.readString();
    //    Serial.println(terimaData);
    //
    //    String Read =  terima.readString(); //t#33#1.80#3.30
    String Read =  terima.readString(); //t#33#1.80#3.30
    read1 = parseString(Read, "#", 0);
    Serial.println ("RECEIVE DATA : " + String(Read) );
    if (read1 == "t") {

      read2 = parseString(Read, "#", 1);
      read3 = parseString(Read, "#", 2);
      read4 = parseString(Read, "#", 3);
      read5 = parseString(Read, "#", 4);
      read6 = parseString(Read, "#", 5);

      int rcwl = read2.toInt();

      float teganganPV = read3.toFloat();
      float teganganBeban = read4.toFloat();

      float arusPV = read5.toFloat();
      float arusBeban = read6.toFloat();

      // http://projek.bengkelti.com/pju/dariESP.php?rcwlValue=24&teganganValue=2&dayaValue=4&arusValue=3&arusBeban=4&teganganBeban=5

      String requestData = URL +  "/dariESP.php?rcwlValue=" + String(rcwl)
                           + "&teganganValue=" + String(teganganPV) +
                           +  "&dayaValue=" + String(arusPV * teganganPV ) +
                           +  "&arusValue=" + String(arusPV) +
                           +  "&arusBeban=" + String(arusBeban) +
                           +  "&teganganBeban=" + String(teganganBeban) + "";

      // ---
      // Debug
      // ---

      // Serial.println("RCWL : " + String(rcwl) + " - Tegangan : " + String(tegangan) + " - Arus : " + String(arus) + + " - Daya : " + String(daya) + " - END " );
      // delay(100);

      // ----
      // kirim ke database
      // ----

      if (WiFi.status() == WL_CONNECTED) {

        Serial.println("SEND");
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
