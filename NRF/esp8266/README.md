# Panduan Penggunaan

1. CLONE REPOSITORY
2. MAIN FILE ADA DI => esp8266.ino 
3. KONFIGURASI WIFI

        const char* SSID     = "polinema_hotspot_2G";
        const char* PASSWORD = "";

4. KONFIGURASI HTTP CLIENT (=) OTW MASIH DI HOSTING

        String PROTOKOL = "http";
        String HOST = "192.168.137.1";
        String TARGET = "pju";
        
        String URL = PROTOKOL + "://" + HOST + "/" + TARGET + "";


# Version Change Log

- Version 1.0.1 => Multitask Enable using Protothread
- Version 1.0.0 => String Parser 
