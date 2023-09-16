#ifndef SECRET
const char ssid[] = "NAME"; // Vul hier je Wi-Fi ssid in (niet belangrijk voor oplevering)
const char pass[] = "PASS"; // Vul hier je Wi-Fi wachtwoord in (niet belangrijk voor oplevering)

const char *MQTT_HOST = "webpage.com";
const int MQTT_PORT = 1883; // Voer hier de MQTT-broker poort in op de aangegeven plek
const char *MQTT_CLIENT_ID = "BOT-007"; // Voer hier je leerlingnummer in op de aangegeven plek
const char *MQTT_USER = "student"; // Vul hier de gebruikersnaam in voor de broker
const char *MQTT_PASS = "welkom01"; // Vul hier het wachtwoord in voor de broker

// Dit is het certificaat dat je nodig hebt. Je hoeft hier op deze plek niks mee te doen
const char *local_root_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
    "-----END CERTIFICATE-----";

#endif
