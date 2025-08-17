#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include "fm_transmitter.h"   // Librería ESP32-FM-Transmitter

FMTransmitter fm;  // Objeto transmisor
File musicFile;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Montar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("❌ Error montando SPIFFS");
    return;
  }
  Serial.println("✅ SPIFFS montado correctamente");

  // Abrir archivo WAV convertido (8-bit PCM, 22050 Hz mono recomendado)
  musicFile = SPIFFS.open("/musica3_8bit.wav", "r");
  if (!musicFile) {
    Serial.println("❌ No se pudo abrir musica3_8bit.wav");
    return;
  }
  Serial.println("✅ Archivo musica3_8bit.wav abierto");

  // Inicializar transmisor en frecuencia 100 MHz usando GPIO25
  fm.begin(100.0, 25);
  Serial.println("📡 Transmisor iniciado en 100.0 MHz (GPIO25 como antena)");
}

void loop() {
  if (!musicFile) {
    return; // Si no hay archivo, salir
  }

  uint8_t buffer[512];

  // Leer y transmitir en bloques
  if (musicFile.available()) {
    int n = musicFile.read(buffer, sizeof(buffer));
    fm.write(buffer, n);
  } else {
    // Si terminó el archivo, reiniciar desde el principio
    Serial.println("🔁 Reiniciando archivo...");
    musicFile.seek(0); // Volver al inicio del archivo
  }
}
