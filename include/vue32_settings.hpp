
// leer settings.json file
boolean settingsRead()
{
    JsonDocument jsonSettings;
    File file = SPIFFS.open("/settings.json", "read");

    if (!file)
    {
        myLog("ERROR", "failed to open settings.json file ");
        // NOTE: llamar a la funcion de reiniciar los valores a fabrica
        settingsReset();
        return false;
    }

    DeserializationError error = deserializeJson(jsonSettings, file);
    file.close();

    if (error)
    {
        myLog("ERROR", "failed to deserialization settings.json file ");
        // NOTE: llamar a la funcion de reiniciar los valores de fabrica
        settingsReset();
        return false;
    }

    // copiar los valores del json a las variables globales
    strlcpy(device_id, jsonSettings["device_id"] | "", sizeof(device_id));
    strlcpy(device_name, jsonSettings["device_name"] | "", sizeof(device_name));
    strlcpy(device_user, jsonSettings["device_user"] | "", sizeof(device_user));
    strlcpy(device_password, jsonSettings["device_password"] | "", sizeof(device_password));

    // wifi STA
    wifi_mode = jsonSettings["wifi"]["wifi_mode"] | false;
    strlcpy(wifi_ssid, jsonSettings["wifi"]["wifi_ssid"] | "", sizeof(wifi_ssid));
    strlcpy(wifi_password, jsonSettings["wifi"]["wifi_password"] | "", sizeof(wifi_password));
    wifi_dhcp = jsonSettings["wifi"]["wifi_dhcp"] | false;
    strlcpy(wifi_IPv4, jsonSettings["wifi"]["wifi_IPv4"] | "", sizeof(wifi_IPv4));
    strlcpy(wifi_gateway, jsonSettings["wifi"]["wifi_gateway"] | "", sizeof(wifi_gateway));
    strlcpy(wifi_subnet, jsonSettings["wifi"]["wifi_subnet"] | "", sizeof(wifi_subnet));
    strlcpy(wifi_dns_primary, jsonSettings["wifi"]["wifi_dns_primary"] | "", sizeof(wifi_dns_primary));
    strlcpy(wifi_dns_secondary, jsonSettings["wifi"]["wifi_dns_secondary"] | "", sizeof(wifi_dns_secondary));

    // wifi AP
    strlcpy(ap_ssid, jsonSettings["wifi"]["ap_ssid"] | "", sizeof(ap_ssid));
    strlcpy(ap_password, jsonSettings["wifi"]["ap_password"] | "", sizeof(ap_password));
    ap_channel = jsonSettings["wifi"]["ap_channel"] | 1;
    ap_visibility = jsonSettings["wifi"]["ap_visibility"] | 0;
    ap_connect = jsonSettings["wifi"]["ap_connect"] | 1;

    // MQTT
    mqtt_enabled = jsonSettings["mqtt"]["mqtt_enabled"] | false;
    strlcpy(mqtt_server, jsonSettings["mqtt"]["mqtt_server"] | "", sizeof(mqtt_server));
    mqtt_port = jsonSettings["mqtt"]["mqtt_port"] | 1883;
    mqtt_retain = jsonSettings["mqtt"]["mqtt_retain"] | false;
    mqtt_qos = jsonSettings["mqtt"]["mqtt_qos"] | 0;
    strlcpy(mqtt_id, jsonSettings["mqtt"]["mqtt_id"] | "", sizeof(mqtt_id));
    strlcpy(mqtt_user, jsonSettings["mqtt"]["mqtt_user"] | "", sizeof(mqtt_user));
    strlcpy(mqtt_password, jsonSettings["mqtt"]["mqtt_password"] | "", sizeof(mqtt_password));
    mqtt_clean_sessions = jsonSettings["mqtt"]["mqtt_clean_sessions"] | false;
    strlcpy(mqtt_sendTopic, jsonSettings["mqtt"]["mqtt_sendTopic"] | "", sizeof(mqtt_sendTopic));
    strlcpy(mqtt_commandTopic, jsonSettings["mqtt"]["mqtt_commandTopic"] | "", sizeof(mqtt_commandTopic));
    strlcpy(mqtt_willTopic, jsonSettings["mqtt"]["mqtt_willTopic"] | "", sizeof(mqtt_willTopic));
    strlcpy(mqtt_willMessage, jsonSettings["mqtt"]["mqtt_willMessage"] | "", sizeof(mqtt_willMessage));
    mqtt_willQoS = jsonSettings["mqtt"]["mqtt_willQoS"] | 0;
    mqtt_willRetain = jsonSettings["mqtt"]["mqtt_willRetain"] | false;
    mqtt_time_send = jsonSettings["mqtt"]["mqtt_time_send"] | false;
    mqtt_time_interval = jsonSettings["mqtt"]["mqtt_time_interval"] | 60;
    mqtt_status_send = jsonSettings["mqtt"]["mqtt_status_send"] | false;

    // relays
    RELAY1_STATUS = jsonSettings["relay"]["RELAY1_STATUS"] | false;
    RELAY2_STATUS = jsonSettings["relay"]["RELAY2_STATUS"] | false;

    // dimmer
    dim = jsonSettings["dimmer"]["dim_value"] | 0;

    // log
    myLog("INFO", "Reading the correct settings");
    return true;
}

// resetear los valores a fabrica

void settingsReset()
{

    // copiar los valores del json a las variables globales
    strlcpy(device_id, DeviceID().c_str(), sizeof(device_id));
    strlcpy(device_name, extractNumbers(DeviceID()).c_str(), sizeof(device_name));
    strlcpy(device_user, "admin", sizeof(device_user));
    strlcpy(device_password, "admin", sizeof(device_password));

    // wifi STA
    wifi_mode = true; // true = STA, false = AP
    strlcpy(wifi_ssid, "MOVISTAR FIBRA", sizeof(wifi_ssid));
    strlcpy(wifi_password, "Jepy#180613#", sizeof(wifi_password));
    wifi_dhcp = false;
    strlcpy(wifi_IPv4, "192.168.30.160", sizeof(wifi_IPv4));
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_gateway, "192.168.30.1", sizeof(wifi_gateway));
    strlcpy(wifi_dns_primary, "8.8.8.8", sizeof(wifi_dns_primary));
    strlcpy(wifi_dns_secondary, "4.4.4.4", sizeof(wifi_dns_secondary));

    // wifi AP
    strlcpy(ap_ssid, DeviceID().c_str(), sizeof(ap_ssid));
    strlcpy(ap_password, "adminserver32", sizeof(ap_password));
    ap_channel = 9;
    ap_visibility = false;
    ap_connect = 2;

    // MQTT
    mqtt_enabled = true;
    strlcpy(mqtt_server, "192.168.1.40", sizeof(mqtt_server));
    mqtt_port = 1885;
    mqtt_retain = false;
    mqtt_qos = 0;
    strlcpy(mqtt_id, DeviceID().c_str(), sizeof(mqtt_id));
    strlcpy(mqtt_user, "root", sizeof(mqtt_user));
    strlcpy(mqtt_password, "Password123*", sizeof(mqtt_password));
    mqtt_clean_sessions = true;
    strlcpy(mqtt_commandTopic, PathMqttTopic("command").c_str(), sizeof(mqtt_commandTopic));
    strlcpy(mqtt_sendTopic, PathMqttTopic("device").c_str(), sizeof(mqtt_sendTopic));
    strlcpy(mqtt_willTopic, PathMqttTopic("status").c_str(), sizeof(mqtt_willTopic));
    strlcpy(mqtt_willMessage, "{\"connected\": false}", sizeof(mqtt_willMessage));
    mqtt_willQoS = 0;
    mqtt_willRetain = false;
    mqtt_time_send = true;
    mqtt_time_interval = 60000; // 60 sec
    mqtt_status_send = true;

    // relays
    RELAY1_STATUS = false;
    RELAY2_STATUS = false;

    // dimmer
    dim = 0;

    // log
    myLog("INFO", "all values ​​were reset to default");
}

// guardar configuraciones en el json
boolean settingsSave()
{
}