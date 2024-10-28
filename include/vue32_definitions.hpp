
// pinout
#define RELAY1 32  // gpio32 salida relay 1
#define RELAY2 33  // gpio33 salida relay 2
#define WIFILED 26 // gpio26 led wifi verde
#define MQTTLED 27 // gpio27 led mqtt azul
#define DIMMER 25  // gpio25 led dimmer rojo

// version firmware
#define TEXTIFY(A) #A
#define ESCAPEQOUTE(A) TEXTIFY(A)
String device_fw_version = ESCAPEQOUTE(BUILD_TAG);

// hard and manufacture
#define device_hw_version "ADMINESP32 v1 00000000"
#define device_manufacture "JPASSEMBLER"

// zona configuracion dispositivo
char device_id[30];       // id del dispositivo
char Device_name[30];     // nombre del dispositivo
u_int16_t device_restart; // numero de reinicios
char device_user[15];     // usuario para acceso servidor web
char device_password[15]; // pass del usuario servidor web

// zona configuracion wifi modo cliente
int wifi_app = WIFI_AP;      // wifi modo WIFI_AP & WIFI_STA
boolean wifi_mode;           // modo AP false, modo cliente true
char wifi_ssid[63];          // nombre de la red wifi a conectar
char wifi_password[63];      // pass de la red wifi a conectar
boolean wifi_dhcp;           // ip estatica false, ip DHCP true
char wifi_IPv4[16];          // dir ipv4 estatico
char wifi_gateway[16];       // dir ipv4 gateway
char wifi_subnet[16];        // dir ipv4 subred
char wifi_dns_primary[16];   // dir ipv4 dns primario
char wifi_dns_secondary[16]; // dir ipv4 dns secundario

// zona configuracion wifi modo AP
char ap_ssid[63];   //nombre ssid modo AP
char ap_password[63];// pass modo AP minimo 8 NULL
int ap_channel;    // canal AP 1 --13
int ap_visibility; // 0 visible 1 oculto
int ap_connect;    // numero de conexiones en el AP max 8 conexiones ESP32

// zona configuracion MQTT
//-----------------------
boolean mqtt_enabled;
char mwtt_server[39];
int mqtt_port;
boolean mqtt_retain;
int mqtt_qos;
char mqtt_id[30];
char mqtt_user[30];
char mqtt_password[39];
boolean mqtt_clean_sessions;
char mqtt_sendTopic[150];
char mqtt_commandTopic[150];
char mqtt_willTopic[150];
char mqtt_willMessage[63];
int mqtt_willQos;
boolean mqtt_willRetain;
boolean mqtt_time_send;
int mqtt_time_interval;
boolean mqtt_status_send;

// EEPROM
#define Start_Address 0
#define Restart_Address Start_Address + sizeof(int)

// otros
float TemperatureC, temperatureF;

// relays
bool RELAY1_STATUS; //gpio32 estado relay 1
bool RELAY2_STATUS; //gpio33 estado relay 2

// PWM
const int freq = 1000;      //frecuencia de trabajo
const int ledChannel = 0;   //definicion del canal
const int resolution = 8;   // 8 bits 255
int dim;                    //valor del dimer a enviar 

// firmware
size_t content_len;
#define U_PART U_SPIFFS
