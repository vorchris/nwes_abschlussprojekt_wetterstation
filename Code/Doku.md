### setup()
Die `setup`-Funktion wird einmal beim Start des ESP32 ausgeführt und initialisiert die verschiedenen Komponenten:
- Initialisiert die serielle Kommunikation für Debugging-Zwecke.
- Initialisiert den DHT22-Sensor zur Messung von Temperatur und Luftfeuchtigkeit.
- Initialisiert den LED-Streifen und setzt die anfängliche Helligkeit.
- Initialisiert das LCD-Display.
- Konfiguriert die Taster als Eingänge mit Pullup-Widerständen.
- Verbindet sich mit dem WLAN und gibt den Verbindungsstatus aus.
- Ruft die initialen Wetterdaten von OpenWeatherMap ab und zeigt diese an.

### loop()
Die `loop`-Funktion wird kontinuierlich ausgeführt und verarbeitet die Button-Eingaben sowie das periodische Abrufen der Wetterdaten:
- Liest die Zustände der beiden Taster ein.
- Überprüft, ob Taster 1 gedrückt wurde, um zwischen der Anzeige der API-Daten und den lokalen Sensordaten umzuschalten.
- Überprüft, ob Taster 2 gedrückt wurde, um die Helligkeit des LED-Streifens in voreingestellten Schritten zu ändern.
- Aktualisiert die Anzeige auf dem LCD-Display basierend auf dem aktuellen Modus.
- Ruft periodisch (alle 60 Sekunden) die Wetterdaten von OpenWeatherMap ab und aktualisiert die Anzeige, wenn der API-Modus aktiv ist.

### fetchWeatherData()
Diese Funktion ruft die Wetterdaten von OpenWeatherMap ab und verarbeitet die JSON-Antwort:
- Überprüft, ob das WLAN verbunden ist.
- Führt eine HTTP-GET-Anfrage an die OpenWeatherMap API durch.
- Parst die JSON-Antwort, um die Temperatur, Luftfeuchtigkeit und Wetterbeschreibung zu extrahieren.
- Aktualisiert die LED-Streifenfarbe basierend auf der abgerufenen Temperatur.

### displayWeatherData()
Diese Funktion zeigt die Wetterdaten von der API auf dem LCD-Display an:
- Löscht das LCD-Display.
- Zeigt die Wetterbeschreibung und die Temperatur von OpenWeatherMap an.

### displayLocalData()
Diese Funktion zeigt die lokalen Sensordaten vom DHT22 auf dem LCD-Display an:
- Liest die Temperatur und Luftfeuchtigkeit vom DHT22-Sensor.
- Überprüft, ob die Sensorwerte gültig sind.
- Zeigt die lokalen Temperatur- und Feuchtigkeitswerte auf dem LCD-Display an.
- Zeigt eine Fehlermeldung an, wenn das Lesen der Sensorwerte fehlschlägt.

### setLEDColor()
Diese Funktion steuert die Farbe des LED-Streifens basierend auf der Temperatur:
- Setzt die Farbe des LED-Streifens auf Blau, wenn die Temperatur unter 0°C liegt.
- Setzt die Farbe des LED-Streifens auf Rot, wenn die Temperatur über 30°C liegt.
- Setzt eine Mischfarbe aus Blau und Rot basierend auf der Temperatur im Bereich 0-30°C.
- Aktualisiert die Farbe aller LEDs im Streifen.
