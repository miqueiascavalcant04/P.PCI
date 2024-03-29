#include <WiFi.h>
#define sala 15
#define quarto 2
#define cozinha 4


const char* ssid     = "iPhone de Miguel";
const char* password = "miguel123";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);

  pinMode(sala, OUTPUT);
  pinMode(quarto, OUTPUT);
  pinMode(cozinha, OUTPUT);

  delay(10);



  Serial.println();
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  IPAddress ip(192, 168, 2, 162); 
  IPAddress gateway(192, 168, 2, 1); 
  IPAddress subnet(255, 255, 255, 0); 

  WiFi.config(ip, gateway, subnet);

  Serial.println("");
  Serial.println("O Wifi está conectado.");
  Serial.println(" Endereço de IP: ");
  Serial.println(ip);

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();   

  if (client) {                           
    Serial.println("New Client.");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    

         
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html>");
            client.println("<head>");
            client.println("<title> Automação Residencial </title>");
            client.println("<meta charset=\"utf-8\">");
            client.println("<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">");
            client.println("</head>");
            client.println("<body>");
            client.println("<center>");
            client.println("<br>");

            client.println("<a href=\"/SALA\"\"><button>Sala</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/QUARTO\"\"><button>Quarto</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("<a href=\"/COZINHA\"\"><button>Cozinha</button></a>");
            client.println("<br>");
            client.println("<br>");
            client.println("</center>");
            client.println("</body>");
            client.println("</html>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }


        if (currentLine.endsWith("GET /SALA")) {
          digitalWrite(sala, !digitalRead(sala));
        }
        
        if (currentLine.endsWith("GET /QUARTO")) {
          digitalWrite(quarto, !digitalRead(quarto));
        }
        
        if (currentLine.endsWith("GET /COZINHA")) {
          digitalWrite(cozinha, !digitalRead(cozinha));
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
