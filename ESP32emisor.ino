#include <WiFi.h>

const char* ssid = "TP-Link_AP_4822";      // Nombre de tu red Wi-Fi
const char* password = "IoT23Cloud";  // Contraseña de tu red Wi-Fi
const char* host = "148.213.39.150";       // Dirección IP del receptor ESP32
int port = 80;

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

}

void loop() {
    // Crear una conexión TCP al receptor
    WiFiClient client;
    if (client.connect(host, port)) {
        Serial.println("Conexión al receptor establecida.");

        // Generar una marca de tiempo
        unsigned long timestamp = millis();

        // Enviar la marca de tiempo al receptor
        client.print("Timestamp: ");
        client.println(timestamp);
        client.println();


        // Enviar datos al receptor
        String datosAEnviar = "Hola mundo";
        client.println(datosAEnviar);
        client.println();

        // Esperar una confirmación del receptor
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.print(c); // Mostrar lo que llega desde el receptor
            }
        }

        // Cerrar la conexión
        client.stop();
        Serial.println("Conexión al receptor cerrada.");
        

    } else {
        Serial.println("Error al conectar al receptor.");
    }

    // Esperar un breve tiempo antes de enviar más datos
    delay(3000); // Esperar 5 segundos antes de enviar más datos
}