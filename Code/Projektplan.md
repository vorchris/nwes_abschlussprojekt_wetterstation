### Projektplan

#### Titel: Wetterstation mit ESP32, LCD-Display und LED-Streifen

#### Ziele
1. **Hauptziele:**
   - Implementierung einer Wetterstation, die Wetterdaten von OpenWeatherMap abruft und diese auf einem LCD-Display anzeigt.
   - Anzeige der lokalen Temperatur und Luftfeuchtigkeit mittels DHT22-Sensor.
   - Steuerung eines LED-Streifens, der die Temperatur farblich und in der Helligkeit visualisiert.
   - Implementierung einer Tastensteuerung zum Wechseln zwischen API-Daten und lokalen Sensordaten sowie zum Ändern der Helligkeit des LED-Streifens.

2. **Zusatzziele:**
   - Erweiterung der Funktionalität um zusätzliche Wetterparameter wie Luftdruck oder Windgeschwindigkeit.
   - Implementierung einer Weboberfläche zur Fernüberwachung der Sensordaten.
   - Speicherung historischer Wetterdaten zur späteren Analyse.

3. **Nicht-Ziele:**
   - Entwicklung einer mobilen App zur Steuerung der Wetterstation.
   - Implementierung von Funktionen für die automatische Kalibrierung der Sensoren.
   - Erweiterung um eine autarke Stromversorgung (Solar).

---

### Arbeitseinteilung für 5 Doppelstunden

#### Doppelstunde 1: Projektvorbereitung und Hardware-Setup
- **Ziel:** Verstehen der Projektanforderungen und Aufbau der Hardware.
- **Aktivitäten:**
  - Besprechung des Projektplans und der Ziele.
  - Zusammenbau der Hardware: ESP32, DHT22, LCD-Display, LED-Streifen, und Taster.
  - Testen der Hardwareverbindungen und Sicherstellen der Funktionalität.

#### Doppelstunde 2: Grundlegende Programmierung und API-Integration
- **Ziel:** Implementierung der Basisfunktionalität zur Datenabfrage von OpenWeatherMap.
- **Aktivitäten:**
  - Einrichtung der Entwicklungsumgebung (Arduino IDE).
  - Schreiben des Codes zur Verbindung mit dem WLAN.
  - Implementierung der Funktion zur Abfrage der Wetterdaten von OpenWeatherMap.
  - Testen und Debuggen der API-Anfragen.

#### Doppelstunde 3: Anzeige der Daten auf dem LCD-Display
- **Ziel:** Darstellung der Wetterdaten und der lokalen Sensordaten auf dem LCD-Display.
- **Aktivitäten:**
  - Programmierung der LCD-Anzeige.
  - Implementierung der Funktionen zur Anzeige der API- und DHT22-Daten.
  - Testen und Debuggen der Anzeige.

#### Doppelstunde 4: Steuerung des LED-Streifens
- **Ziel:** Steuerung des LED-Streifens basierend auf den Temperaturdaten.
- **Aktivitäten:**
  - Programmierung der LED-Farbsteuerung in Abhängigkeit der Temperatur.
  - Implementierung der Helligkeitssteuerung des LED-Streifens.
  - Testen und Debuggen der LED-Funktionen.

#### Doppelstunde 5: Implementierung der Tastensteuerung und Projektabschluss
- **Ziel:** Implementierung der Tastensteuerung und Abschlussarbeiten.
- **Aktivitäten:**
  - Implementierung der Tastensteuerung zum Wechseln der Anzeigemodi und zur Helligkeitssteuerung.
  - Endgültiges Testen und Debuggen des gesamten Systems.
  - Vorbereitung der Projektpräsentation und Erstellung der Dokumentation.
