#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <dht11.h>

#define D1 5
#define D2 4
#define d3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define RAIN_PIN D7
#define DHT_PIN D6

const char *ssid     = "zzx";
const char *password = "1234567899";

ESP8266WebServer server(80);

dht11 DHT11;

//获取湿度
float getHumidity(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.humidity;
}

//获取温度
float getTemperature(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.temperature;
}

//访问http://192.168.4.1会看到的内容
void handleRoot()
{
    int val = digitalRead(RAIN_PIN);
    String str = R"===(
        <html>
          <head>
            <meta charset="utf-8" http-equiv="Refresh" content="1"/>
            <title>ESP-12E实验</title>
          </head>
          <body>
            <h1>是否下雨:
            )===";

    if (val)
    {
        str += "否";
    }
    else
    {
        str += "是";
    }

    float h = getHumidity();
    float t = getTemperature();

    str += "<br>当前湿度(%):";
    str += String(h);

    str += "<br>当前温度(℃):";
    str += String(t);
    str += "</h1></body></html>";

  server.send(200, "text/html", str);
}

void setup()
{
    Serial.begin(9600);
    pinMode(RAIN_PIN,INPUT);

    delay(1000);
    Serial.println();
    Serial.println("Configuring access point...");

    //启动AP热点
    WiFi.softAP(ssid, password);

    //显示热点信息
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    //绑定HTTP服务器/目录下所发布的信息，并启动服务
    server.on("/", handleRoot);
    server.begin();

    Serial.println("HTTP server started");
    
}

void loop()
{
    server.handleClient();
}
