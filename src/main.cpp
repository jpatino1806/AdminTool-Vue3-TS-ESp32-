#include <Arduino.h>
#include <EEPROM.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>

// archivos *.hpp (fragmentacion del codigo)
#include <vue32_definitions.hpp>
#include <vue32_functions.hpp>
#include <vue32_settings.hpp>

void setup()
{
    Serial.begin(155200);
    delay(500);
    myLog("INFO", "setup init ...");
    // SPIFFS
    if (!SPIFFS.begin(true))
    {
        myLog("ERROR", "SPIFFS initialization failed");
        while (true)
            ;
    }
    // contador de reinicios
    EEPROM.begin(256);
    EEPROM.get(Restart_Address, device_restart);
    device_restart++;
    // verificar que no exceda 65535
    if (device_restart > 65535)
    {
        device_restart = 0;
        EEPROM.put(Restart_Address, device_restart);
    }
    EEPROM.put(Restart_Address, device_restart);
    EEPROM.commit();
    EEPROM.end();
    String message = "number of reboots: " + String(device_restart);
    myLog("INFO", message.c_str());

    // leer configuraciones del settings.json
    if (!settingsRead())
    {
        // TODO: mandar a llamar la funcion de guardar
        settingsSave();
    }
}

void loop()
{
}
