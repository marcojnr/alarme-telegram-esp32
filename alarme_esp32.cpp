#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Dados do WiFi
#define WIFI_SSID "PHSOUZA"
#define WIFI_PASSWORD "123456787"
// Telegram BOT Token (Botfather)
#define BOT_TOKEN "7052144896:AAE_O6dJc7Aof1OjQkG9DZNhDBpbYznfhF4"

// Use @myidbot (IDBot) para saber qual o seu ID
#define CHAT_ID "5756955138"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

#define Sensor 4

bool portaAnterior = false;

void setup() {

  pinMode(Sensor, INPUT);
  Serial.begin(115200);
  Serial.println();


  //conexão da rede:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot iniciou", ""); //envia mensagem dizendo que iniciou o BOT
}

void loop() {

  bool portaAtual = digitalRead(Sensor);

  if (portaAtual != portaAnterior) {
    if (portaAtual == LOW) {
      Serial.println("Porta Aberta");
      bot.sendMessage(CHAT_ID, "Porta Aberta", "");
    } else {
      Serial.println("Porta Fechada");
      bot.sendMessage(CHAT_ID, "Porta Fechada", "");
    }
    portaAnterior = portaAtual;
    delay(1000); // Delay para evitar múltiplos envios devido a vibração ou instabilidade do sensor
  }

}