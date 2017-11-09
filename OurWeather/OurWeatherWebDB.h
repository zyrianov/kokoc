//
// OurWeatherWebDB Interface
//
// K0KOC, November 2017
//
//


int sendOurWeatherData()
{


  WiFiClient client;

  const char* host = "ourweather.k0koc.com";

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return 1;
  }

  String myURL;
  // = "/updateweather.asp?ID=K0KOC&PASSWORD=u*1=now&EnglishOrMetric=0&AirQualitySensor=0&ESP8266HeapSize=32800&OurWeatherTime=11/06/2017 20:41:20&FullDataString=14.50,58.90,22.30,101938.00,100.29,6.00,0.00,315.00,1.00,1.20,6.00,0.00,0.00,45.00,315.00,0,11/06/2017 20:41:20,,0,-1,0.00,0.00,0.00,0.00,0.00,0.00,4.13,34.40,0.00,0.00,0.00,21.20,V:0,WXLMG&FirmwareVersion=023&IndoorTemperature=22.30&BarometricPressure=101938.00&Altitude=100.29&outdoortemperature=14.50&outdoorhumidity=59.10&currentwindspeed=8.46&currentwinddir=180&software=OurWeather";


  myURL = "/updateweather.asp?";
  myURL += "ID=" + OurWeatherID;
  myURL += "&PASSWORD=" + OurWeather_StationKey;
  myURL += "&dateutc=now";

  // now weather station variables

  myURL += "&EnglishOrMetric=" + String(EnglishOrMetric);
  myURL += "&AirQualitySensor=" + String(AirQualitySensor);
  myURL += "&ESP8266HeapSize=" + String(ESP8266HeapSize);
  myURL += "&OurWeatherTime=" + String(OurWeatherTime);
  myURL += "&FullDataString=" + String(FullDataString);

  myURL += "&FirmwareVersion=" + String(FirmwareVersion);
  myURL += "&IndoorTemperature=" + String(IndoorTemperature);
  myURL += "&BarometricPressure=" + String(BarometricPressure);
  myURL += "&Altitude=" + String(Altitude);
  myURL += "&outdoortemperature=" + String(AM2315_Temperature);
  myURL += "&outdoorhumidity=" + String(AM2315_Humidity);

  myURL += "&currentwindspeed=" + String(currentWindSpeed);
  myURL += "&currentwindgust=" + String(currentWindGust);
  myURL += "&currentwinddir=" + String(currentWindDirection);

  myURL += "&RainTotal=" + String(RainTotal);
  myURL += "&WindSpeedMin=" + String(WindSpeedMin);
  myURL += "&WindSpeedMax=" + String(WindSpeedMax);
  myURL += "&WindGustMin=" + String(WindGustMin);
  myURL += "&WindGustMax=" + String(WindGustMax);
  myURL += "&WindDirectionMin=" + String(WindDirectionMin);
  myURL += "&WindDirectionMax=" + String(WindDirectionMax);
 
  myURL += "&id=" + String(id);
  myURL += "&name=" + String(name);
  myURL += "&software=" + String(software);
  // myURL += "&software=OurWeather";
  // myURL += "&connected=" + String(connected);




  Serial.print("Requesting URL: ");
  Serial.println(myURL);

  // This will send the request to the server
  client.print(String("GET ") + myURL + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

String OWResult;

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    OWResult = line;
    yield();
  }
  Serial.print("OWResult=");
  Serial.println(OWResult);

  if (OWResult.indexOf("success") != -1)
  {
     Serial.println("OW Successful Write");
     return 1;
  }
  else
  {
    Serial.println("OW NOT Successful Write");
  }
  client.stop();
  return 0;




}

