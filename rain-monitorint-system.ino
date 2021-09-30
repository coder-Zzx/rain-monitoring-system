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
#define DHT11PIN D6

const char *ssid = "rain-monitoring-system";
const char *password = "1373539657";

ESP8266WebServer server(80);

dht11 DHT11;

//获取湿度
float getHumidity()
{
    int chk = DHT11.read(DHT11PIN);
    return (float)DHT11.humidity;
}

//获取温度
float getTemperature()
{
    int chk = DHT11.read(DHT11PIN);
    return (float)DHT11.temperature;
}

//访问对应的内网ip地址会看到的内容
void handle_OnConnect()
{
    int val = digitalRead(RAIN_PIN);

    float h = getHumidity();
    float t = getTemperature();

    server.send(200, "text/html", SendHTML());
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}

void setup()
{
    Serial.begin(9600);
    pinMode(RAIN_PIN, INPUT);

    delay(1000);
    Serial.println();
    Serial.println("Configuring access point...");

    //启动AP热点
    WiFi.begin(ssid, password);

    //显示热点信息
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    //绑定HTTP服务器/目录下所发布的信息，并启动服务
    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    server.begin();

    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();
}

String SendHTML()
{
    int val = digitalRead(RAIN_PIN);
    float T = getTemperature();
    float H = getHumidity();

    String ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head> <meta name=\"viewport\" content=\"width=device-width,  initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
    ptr += "<meta charset=\"UTF-8\">\n";
    ptr += "<title>zzx的雨水监测系统</title>\n";
    ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
    ptr += "body{margin-top: 50px;}\n";
    ptr += "h1 {margin: 50px auto 30px;}\n";
    ptr += " .wd {margin: 50px auto 30px;width: auto;color: #f39c12}\n";
    ptr += " .wd1 {margin: 50px auto 30px;width: auto;color: #3498db}\n";
    ptr += ".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
    ptr += ".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
    ptr += ".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
    ptr += ".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
    ptr += ".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
    ptr += ".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
    ptr += ".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
    ptr += ".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
    ptr += ".data{padding: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";

    ptr += "<div id=\"webpage\">\n";

    ptr += "<h1>室外雨水检测系统</h1>\n";
    ptr += "<div class=\"data\">\n";
    ptr += "<div class=\"side-by-side temperature-icon\">\n";
    ptr += "<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
    ptr += "width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
    ptr += "<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
    ptr += "c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
    ptr += "c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
    ptr += "c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
    ptr += "c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
    ptr += "</svg>\n";
    ptr += "</div>\n";
    ptr += "<div class=\"side-by-side temperature-text\">室外温度：</div>\n";
    ptr += "<div class=\"side-by-side temperature\">";
    ptr += (int)T;
    ptr += "<span class=\"superscript\">°C</span></div>\n";
    ptr += "</div>\n";
    ptr += "<div class=\"data\">\n";
    ptr += "<div class=\"side-by-side humidity-icon\">\n";
    ptr += "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
    ptr += "<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
    ptr += "c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
    ptr += "</svg>\n";
    ptr += "</div>\n";
    ptr += "<div class=\"side-by-side humidity-text\">室外湿度：</div>\n";
    ptr += "<div class=\"side-by-side humidity\">";
    ptr += (int)H;
    ptr += "<span class=\"superscript\">%</span></div>\n";
    ptr += "</div>\n";
    //定义温度变量，并且赋值，用于逻辑判断。
    int wd = T;

    if (wd >= 30)
    {
        ptr += "<div class=\"wd\">Hi~ 宝贝今天天气贼热，注意防暑哦！</div>\n";
    }
    if (29 >= wd && wd > 20)
    {
        ptr += "<div class=\"wd1\">Hi~ 宝贝今天天气不错吆，尽情的玩耍吧！</div>\n";
    }
    if (wd < 10)
    {
        ptr += "<div class=\"side-by-side humidity-text\">Hi~ 宝贝今天天气比较冷，多穿点衣服，小心着凉！</div>\n";
    }
    ptr += "</div>\n";

    ptr += "<h1>是否下雨：";

    if (val)
    {
        ptr +="否";
    }
    else
    {
        ptr +="是";
    }

    ptr += "</h1>\n";
    ptr += "</body>\n";
    ptr += "</html>\n";
    return ptr;
}
