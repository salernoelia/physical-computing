#include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>

const char* ssid = "Snibs";      // Replace with your Wi-Fi network name (SSID)
const char* password = "Sunnyvase086";  // Replace with your Wi-Fi password


void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Create a WiFiClient object
    WiFiClient client;

    // Create an HTTPClient object with the WiFiClient
    // HTTPClient http;

    Serial.println("Wifi Connected!");


    // http.begin(client, "https://api.openai.com/v1/engines/davinci/completions");

    // // Add the necessary headers
    // http.addHeader("Content-Type", "application/json");
    // http.addHeader("Authorization", "Bearer " + String(apiKey));

    // // Create the JSON payload with the prompt
    // String jsonPayload = "{\"prompt\":\"Translate 'Hello, World!' to French: \"}";

    // // Send the HTTP POST request
    // int httpResponseCode = http.POST(jsonPayload);

    // if (httpResponseCode > 0) {
    //   String response = http.getString();
    //   Serial.println("HTTP Response Code: " + String(httpResponseCode));
    //   Serial.println("Response: " + response);
    // } else {
    //   Serial.println("Error in HTTP request");
    // }

    // http.end();
  }

  // Wait before making another request
  delay(5000);
}

