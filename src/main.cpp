#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <Adafruit_MLX90614.h>

#include <webPage.h>

TFT_eSPI tft = TFT_eSPI();

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
WebServer server(80);

const char *ssid = "TTGO";
const char *password = "12345678";

void onIndex()
{
  server.send(200, "text/html", webPage);
}

void onGet()
{
  if (digitalRead(35) == 0 and digitalRead(0) == 0)
  {
    server.send(200, "text/plane", "fizzbuzz");
    tft.drawString("fizzbuzz", 0, 50);
  }
  else if (digitalRead(0) == 0)
  {
    server.send(200, "text/plane", "fizz");
    tft.drawString("fizz", 0, 50);
  }
  else if (digitalRead(35) == 0)
  {
    server.send(200, "text/plane", "buzz");
    tft.drawString("buzz", 0, 50);
  }
  else
  {
    server.send(200, "text/plane", "");
    tft.drawString("", 0, 50);
  }
}

void onGetTemp()
{
  double temp = mlx.readObjectTempC();
  server.send(200, "text/plane", (String)temp);
  tft.drawString("Temperature:", 0, 70);
  tft.drawNumber(temp, 0, 80);
}

void onPost()
{
  server.send(200, "text/plain", "msg sent");
  tft.drawString(server.arg(0), 0, 60);
}

void setup()
{
  pinMode(0, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);

  tft.init();
  tft.fillScreen(TFT_BLACK);

  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  tft.drawString("connect to TTGO", 0, 0);
  tft.drawString("Password:", 0, 10);
  tft.drawString(password, 0, 20);
  tft.drawString("AP IP address:", 0, 30);
  tft.drawString(myIP.toString(), 0, 40);

  server.on("/", onIndex);
  server.on("/get", onGet);
  server.on("/getTemp", onGetTemp);
  server.on("/post", HTTP_POST, onPost);

  mlx.begin();
  server.begin();
}

void loop()
{
  server.handleClient();
}
