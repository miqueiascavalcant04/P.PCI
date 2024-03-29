#include <WiFi.h>

const char* ssid     = "iPhone de Miguel";
const char* password = "miguel123";

WiFiServer server(80);

const int ledPin1 = 15;  // Pino do primeiro LED
const int ledPin2 = 2;  // Pino do segundo LED
const int ledPin3 = 4;  // Pino do terceiro LED

void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);  // Configura os pinos dos LEDs como saída
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Espera por clientes

  if (client) {                             // Se um cliente se conectou,
    Serial.println("Novo Cliente.");           // Imprime uma mensagem no monitor serial
    String currentLine = "";                // Cria uma string para armazenar os dados do cliente
    while (client.connected()) {            // Loop enquanto o cliente estiver conectado
      if (client.available()) {             // Se há dados para ler do cliente
        char c = client.read();             // Lê um byte

        if (c == '\n') {                    // Se o byte lido for uma quebra de linha
          if (currentLine.length() == 0) {  // Se a linha atual estiver vazia, indica que o pedido HTTP terminou
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Clique <a href=\"/H1\">aqui</a> para ligar o LED VERDE.<br>");
            client.print("Clique <a href=\"/L1\">aqui</a> para desligar o LED VERDE.<br>");
            client.print("Clique <a href=\"/H2\">aqui</a> para ligar o LED VERMELHO.<br>");
            client.print("Clique <a href=\"/L2\">aqui</a> para desligar o LED VERMELHO.<br>");
            client.print("Clique <a href=\"/H3\">aqui</a> para ligar o LED AMARELO.<br>");
            client.print("Clique <a href=\"/L3\">aqui</a> para desligar o LED AMARELO.<br>");
            client.println();
            
            break;
          } else {    // Se não estiver vazia, limpa a linha atual para ler o próximo pedido HTTP
            currentLine = "";
          }
        } else if (c != '\r') {  // Se o byte não for um retorno de carro, adiciona-o à linha atual
          currentLine += c;
        }

        // Verifica se o pedido do cliente foi "GET /H" ou "GET /L":
        if (currentLine.endsWith("GET /H1")) {
          digitalWrite(ledPin1, HIGH);               // GET /H liga o LED

        }
        if (currentLine.endsWith("GET /H2")) {
              // GET /H liga o LED
          digitalWrite(ledPin2, HIGH);

        }
        if (currentLine.endsWith("GET /H3")) {               // GET /H liga o LED

          digitalWrite(ledPin3, HIGH);
        }
        if (currentLine.endsWith("GET /L1")) {
          digitalWrite(ledPin1, LOW);                // GET /L desliga o LED

        }
        
        if (currentLine.endsWith("GET /L2")) {
           // GET /L desliga o LED
          digitalWrite(ledPin2, LOW);

        }
        
        if (currentLine.endsWith("GET /L3")) {

          digitalWrite(ledPin3, LOW);
        }
      }
    }
    // Fecha a conexão com o cliente
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}
