# Panduan Penggunaan

1. CLONE REPOSITORY
2. MAIN FILE ADA DI => esp8266.ino 
3. KONFIGURASI WIFI

        const char* SSID     = "polinema_hotspot_2G";
        const char* PASSWORD = "";

4. KONFIGURASI HTTP CLIENT 

        String PROTOKOL = "http"; // HTTP atau HTTPS
        String HOST = "192.168.137.1"; // HOST bisa IP bisa Domain
        String TARGET = "pju"; // Target Folder
        
        String URL = PROTOKOL + "://" + HOST + "/" + TARGET + "";


# Version Change Log

- Version 1.2.0 => Auto Send When Parsed Data
- Verison 1.1.0 => Auto Connect Wifi While Disconnected
- Version 1.0.1 => Multitask Enable using Protothread
- Version 1.0.0 => String Parser 
