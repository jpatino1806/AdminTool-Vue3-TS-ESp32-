
// realizar un log en el puerto serial
void myLog(const char *type, const char *msg)
{
    // type : [ÑDEBUG, INFO, WARN, ERROR]
    Serial.printf("[%s] %s\n", type, msg);
}

// platform
const char *platform()
{
#if defined(ARDUINO_ESP32_DEV)
    return "ESP32";
#endif
}

// HexToStr
String HexToStr(unsigned long h, byte l)
{
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%08lX", h);
    return String(buffer).substring(8 - l);
}

// UniqueID
String UniqueID()
{
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    String id = String(chip, HEX);
    id.toUpperCase();

    while (id.length() < 4)
    {
        id = "0" + id;
    }
    return id;
}

// Device ID unico => ESP32 9B1C5210 0C3D
String DeviceID()
{
    return platform() + HexToStr(ESP.getEfuseMac(), 8) + UniqueID();
}

// extraer numeros
String extractNumbers(const String &e)
{
    String outString;
    for (char c : e)
    {
        if (!isDigit(c))
        {
            outString += c;
        }
    }
    outString.toLowerCase();
    return outString;
}

// crear topicos para MQTT
//  /usuario/+/id/# => /emqx/vue32/ESP329B1C52100C3D/status = true/false
String PathMqttTopic(const String &topic)
{
    return String("/") + mqtt_user + "/vue32/" + mqtt_id + "/" + topic;
}