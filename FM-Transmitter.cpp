#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#include "driver/i2s.h"
#include "driver/periph_ctrl.h"
#include "driver/rtc.h"
#include "soc/rtc.h"

#define SAMPLE_RATE   16000         // frecuencia de muestreo del WAV
#define DEFAULT_FREQ  100.0         // MHz (elige tu frecuencia libre)
#define ANTENNA_PIN   25            // GPIO25 será la antena

File musicFile;

// ------------------------------------------------------------
// Configuración APLL para FM (basado en Alexxdal ESP32FMRadio)
// ------------------------------------------------------------
void setupFM(double freqMHz) {
  // Encender el APLL (Audio PLL)
  rtc_clk_apll_enable(true, 31, 63, 7, 2);

  // Configurar I2S para usar MCLK generado por APLL
  const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = true, // importante: usar APLL
    .tx_desc_auto_clear = true,
    .fixed_mclk = (uint32_t)(freqMHz * 1000000) // frecuencia portadora
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_PIN_NO_CHANGE,
    .ws_io_num = I2S_PIN_NO_CHANGE,
    .data_out_num = ANTENNA_PIN,   // nuestra antena en GPIO25
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

// ------------------------------------------------------------
// Setup
// ------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");

  if (!SPIFFS.begin(true)) {
    Serial.println("Error montando SPIFFS");
    return;
  }

  musicFile = SPIFFS.open("/musica3_8bit.wav", "r");
  if (!musicFile) {
    Serial.println("No se pudo abrir archivo WAV");
    return;
  }

  setupFM(DEFAULT_FREQ);

  Serial.println("Transmisor FM iniciado en 100 MHz.");
}

// ------------------------------------------------------------
// Loop principal
// ------------------------------------------------------------
void loop() {
  if (musicFile.available()) {
    uint8_t sample = musicFile.read();

    // Convertir 8-bit unsigned a 16-bit signed
    int16_t pcm = ((int16_t)sample - 128) << 8;

    size_t bytes_written;
    i2s_write(I2S_NUM_0, &pcm, sizeof(pcm), &bytes_written, portMAX_DELAY);
  } else {
    // Reiniciar archivo para loop
    musicFile.seek(0);
  }
}
