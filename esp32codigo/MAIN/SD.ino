
#include "FS.h"
#include "SD.h"
#include "SPI.h"

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("No se pudo abrir la ruta");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("No es una ruta valida");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  ARCHIVO: ");
      Serial.print(file.name());
      Serial.print("  TAMAÑO: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}


void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Leyendo archivo: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("No se pudo abrir el archivo");
    return;
  }

  Serial.print("Leyendo el archivo: %s /n", file.name());
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}
