#include <WiFi.h> //ADD B
#include <WebServer.h>

const char *ssid = "**********"; //ETEC
const char *password = "********"; //ETEC123
WebServer server(80);// CONECTAR (80)

const int ledPin = 2; //PORTA =2

void setup()  
{
    Serial.begin(115200); //COMUNICA (VALOR)
    pinMode(ledPin, OUTPUT); //SAIDA

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) //TENTAR INICIAR
    {
        delay(1000); 
        Serial.println("Conectando ao WiFi..."); //INFORMAR 
    }

    Serial.println("Conectado à rede Wi-Fi!"); //OK
    Serial.println(WiFi.localIP()); //IP

    server.on("/", HTTP_GET, []()
              { server.send(200, "text/html", "<html><body><h1>Ligar/Desligar LED</h1><a href=\"/ligar\">Ligar LED</a><br><a href=\"/desligar\">Desligar LED</a></body></html>"); });

    server.on("/ligar", HTTP_GET, []()
              {
    digitalWrite(ledPin, HIGH); //LIGA
    server.send(200, "text/plain", "LED ligado"); }); //OK

    server.on("/desligar", HTTP_GET, []()
              {
    digitalWrite(ledPin, LOW); //LOW
    server.send(200, "text/plain", "LED desligado"); }); //OK

    server.begin(); //GO
    Serial.println("Servidor iniciado"); //OK
}

void loop() //LOOP
{
    server.handleClient();//GERENCIA
}
