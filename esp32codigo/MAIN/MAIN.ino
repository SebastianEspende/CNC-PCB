
//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
int lcdColumnas = 16;
int lcdFilas = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumnas, lcdFilas);  

//ENCODER
#include <ClickEncoder.h>
#include <TimerOne.h>

//ENCODER
ClickEncoder *encoder;
volatile int16_t last, value;
int CLK = 8;
int DT = 7;
int SW = 6;
boolean up = false;
boolean down = false;
boolean middle = false;

//SD

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "SD.ino"
#include "WIFI.ino"
#include "LCD.ino"
void setup() {

  Serial.begin(115200);

  while (!Serial) {
    delay(10);
  }

  // SD ////////////////////////////////////////////////////////
  if (!SD.begin()) {
    Serial.println("No se pudo inicializar la tarjeta SD");
    return;
  } else {
    SD.begin();
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No hay tarjeta SD");
    return;
  }

  Serial.print("Tipo de tarjeta: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("DESCONOCIDA");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("TAMAÑO DE SD: %lluMB\n", cardSize);
  
  Serial.printf("Espacio total: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Espacio usado: %lluMB\n", SD.usedBytes() / (1024 * 1024));

  // WIFI ///////////////////////////////////////////////////////////////////////////
  pinMode(btnGPIO, INPUT);
  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int tryDelay = 500;
  int numberOfTries = 20;  while (true) {

    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL: Serial.println("[WiFi] SSID not found"); break;
      case WL_CONNECT_FAILED:
        Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
        return;
        break;
      case WL_CONNECTION_LOST: Serial.println("[WiFi] Connection was lost"); break;
      case WL_SCAN_COMPLETED:  Serial.println("[WiFi] Scan is completed"); break;
      case WL_DISCONNECTED:    Serial.println("[WiFi] WiFi is disconnected"); break;
      case WL_CONNECTED:
        Serial.println("[WiFi] WiFi is connected!");
        Serial.print("[WiFi] IP address: ");
        Serial.println(WiFi.localIP());
        return;
        break;
      default:
        Serial.print("[WiFi] WiFi Status: ");
        Serial.println(WiFi.status());
        break;
    }
    delay(tryDelay);

    if (numberOfTries <= 0) {
      Serial.print("[WiFi] Failed to connect to WiFi!");
      // Use disconnect function to force stop trying to connect
      WiFi.disconnect();
      return;
    } else {
      numberOfTries--;
    }
  }

  //LCD /////////////////////////////////////////////////////////////////////
  renderer.begin();
  menu.setScreen(mainScreen);
}

void loop() {
  // QUE HAY Q HACER:
  // SD Y LCD
  /* SD: HAY QUE ACTIVAR EL WIFI, CONECTARSE AL SERVIDOR Y TRAER LOS NOMBRES DE TODOS LOS ARCHIVOS GUARDADOS. PODER SELECCIONAR UNO Y DESCARGARLO.
   * WIFI: GET DEL SERVIDOR, CONECTARSE AL INTERNET, CONECTARSE A LA API*
   * LCD: MOSTRAR LOS NOMBRES DE LOS ARCHIVOS EN EL SERVIDOR Y GUARDADOS LOCALMENTE EN EL SD, CONTROLAR LOS VENTILADORES, Y ALGO MAS Q NO ME ACUERDO 
   * LAYOUT: 
   * - SD
   *  - ARCHIVOS
   *   - NOMBRES Y PODER SELECCIONARLOS
   * - INFO
   *  - SD ESPACIO Y VARIOS
   *  - COORDENADAS
   * - CONFIG?
    */
  //LCD 
  rotaryInput.observe();
  // WIFI
  btnState = digitalRead(btnGPIO);

  if (btnState == LOW) {
   Serial.println("[WiFi] Disconnecting from WiFi!");
    if (WiFi.disconnect(true, false)) {
      Serial.println("[WiFi] Disconnected from WiFi!");
    }
    delay(1000);
  }
     
}
