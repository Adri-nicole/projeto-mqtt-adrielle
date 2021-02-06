
#include <PubSubClient.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <SPI.h>

//Define o endereço MAC que será utilizado
byte mac[] = {0xC8, 0x45, 0x17, 0xDF, 0x5D,0x67};
bool mensagem;
int pino2 =2;
bool estado_sensor;
//Inicia o cliente Ethernet
EthernetClient client;
PubSubClient mqttClient(client);

void setup() {
    
     pinMode (pino2,INPUT_PULLUP);
     Serial.begin(9600);
    
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);
    
    Serial.begin(9600);
    //Definição de IP e porta TCP do Broker MQTT
    mqttClient.setServer("3.87.59.89",1883);
    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());
    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());
    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());
  
}
void loop() {
    estado_sensor = digitalRead(pino2);

 mqttClient.connect ("adriellenicole");
if (estado_sensor == 0){
mensagem = mqttClient.publish("adriellenicole", "O Rack esta Fechado.");
Serial.print("O estado do sensor e: ");
Serial.println(estado_sensor);
delay(500);
delay (500);


}else {
    mensagem = mqttClient.publish("adriellenicole", "O Rack esta Aberto");
    Serial.print("O estado do sensor e: ");
    Serial.println(estado_sensor);
    delay(500);
  
}
  mqttClient.loop();
 
  delay(500);
    
    
}