#include <WiFi.h>

const char* ssid = "TP-Link_AP_4822";     // Nombre de tu red Wi-Fi
const char* password = "IoT23Cloud";  // Contraseña de tu red Wi-Fi

WiFiServer server(80); // Crea un servidor en el puerto 80

void setup() {
    Serial.begin(115200);
    delay(10);
    
    // Conectar a la red Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a la red Wi-Fi...");
    }
    Serial.println("Conexión Wi-Fi establecida.");

    // Imprimir la dirección IP asignada
    Serial.println("Conexión Wi-Fi establecida");
    Serial.print("Dirección IP del ESP32 receptor: ");
    Serial.println(WiFi.localIP());

    // Comenzar el servidor
    server.begin();
}

void loop() {
    // Esperar a que se conecte un cliente
    WiFiClient client = server.available();
if (client.available()) {
                String line = client.readStringUntil('\r');
                if (line.startsWith("Timestamp: ")) {
                    unsigned long timestamp = line.substring(11).toInt();
                    unsigned long receiveTime = millis();
                    unsigned long transmissionTime = receiveTime - timestamp;
                    Serial.print("Tiempo de envío (ms): ");
                    Serial.println(transmissionTime);
                }
            }

       
    }

