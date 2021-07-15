// -- FUNCTION -- //
void konekWifi(String _ssid, String _pass) {
   WiFi.begin(SSID, PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(SSID); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(100);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());  
}


// -- MULTITASK CONTROLLER --//
static unsigned int cekStatusWifi(struct pt * pt, int _interval) {
  static unsigned lastTime = 0;

  PT_BEGIN(pt);

  while (1) {

    PT_WAIT_UNTIL(pt, millis() - lastTime > _interval);
    lastTime = millis();
    if ((WiFi.status() != WL_CONNECTED)) {
      statusWifi = 0;
      konekWifi(SSID, PASSWORD); // Start Konek Wifi

    } else {
      if (WiFi.isConnected())
        statusWifi = 1;
    }

  }

  PT_END(pt);
}
