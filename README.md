
# 📡 ESP32 FM Transmitter (SPIFFS + WAV Player)

This project turns an **ESP32 DevKit v1** into a **DIY FM Transmitter** 🎶📻.
It loads a `.wav` file from **SPIFFS** and broadcasts it on the FM band (default: **100.0 MHz**).

⚠️ **Disclaimer**: FM transmission may be restricted by law in your country. Use this project **only for educational purposes** and in compliance with local regulations.

---

## ✨ Features

* Plays **8-bit mono WAV audio** from SPIFFS
* Broadcasts on any FM frequency (default **100.0 MHz**)
* Simple antenna using **GPIO25** + jumper/resistor
* Loops music file automatically 🎵
* Debug messages in **Serial Monitor (115200 baud)**

---

## 🛠️ Requirements

### Hardware

* ESP32 DevKit v1
* Jumper wire (as antenna, or \~20–75 cm wire)
* Optional: 1kΩ resistor in series with antenna

### Software

* [Arduino IDE](https://www.arduino.cc/en/software)
* ESP32 board support installed
* [ESP32 FM Transmitter Library](https://github.com/karawin/ESP32-FM-Transmitter)
* SPIFFS Upload Tool for Arduino IDE

---

## 📂 File Structure

```
ESP32-FM-Transmitter/
│── src/
│    └── main.ino         # Arduino sketch (transmitter code)
│── data/
│    └── musica3_8bit.wav # WAV file (8-bit PCM, mono, 22050Hz)
│── README.md             # This file
```

---

## 🚀 How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/ESP32-FM-Transmitter.git
   cd ESP32-FM-Transmitter
   ```

2. Open `main.ino` in Arduino IDE.

3. Upload `musica3_8bit.wav` to SPIFFS:

   * Place your WAV file in the `/data/` folder.
   * Use **ESP32 Sketch Data Upload** tool.

4. Flash the sketch to your ESP32.

5. Connect a **jumper wire to GPIO25** as antenna.

6. Open **Serial Monitor** (115200 baud) to see status messages.

7. Tune an FM radio to **100.0 MHz** and enjoy 🎶

---

## 📡 Antenna Notes

* A simple jumper wire works as a basic antenna.
* For better range: use a **20–75 cm wire** tuned with a small capacitor.
* GPIO25 is the antenna pin.

---

## 📜 License

This project is released under the **MIT License**.
See [LICENSE](LICENSE) for details.

---

👉 Would you like me to make it in **Spanish** too so you can have a bilingual README, or do you prefer to keep it only in English?
