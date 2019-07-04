/*
  Basic ESP8266 MQTT example

  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.

  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define left_up 4       //D2
#define left_down 5     //D1
#define middle_up 12    //D6
#define middle_down 15  //D8
#define right_up 2      //D4
#define right_down 13   //D7

// Update these with values suitable for your network.

const char* ssid = "******";
const char* password = "***************";
const char* mqtt_server = "192.168.1.99";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int delayLong = 1100;
int delayShort = 450;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (isTopic(topic, "eg/essen/blinds/links/up")) {
    handleChannel(left_up, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/links/down")) {
    handleChannel(left_down, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/mitte/up")) {
    handleChannel(middle_up, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/mitte/down")) {
    handleChannel(middle_down, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/rechts/up")) {
    handleChannel(right_up, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/rechts/down")) {
    handleChannel(right_down, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/alle/up")) {
    handleChannel(left_up, payload, length);
    delay(delayShort);
    handleChannel(middle_up, payload, length);
    delay(delayShort);
    handleChannel(right_up, payload, length);
  } else if (isTopic(topic, "eg/essen/blinds/alle/down")) {
    handleChannel(left_down, payload, length);
    delay(delayShort);
    handleChannel(middle_down, payload, length);
    delay(delayShort);
    handleChannel(right_down, payload, length);
  }
}

bool isTopic(char* topic, char* reference) {
  return strcmp(topic, reference) == 0;
}

void handleChannel(int channel, byte* payload, unsigned int length) {
  Serial.print("handle channel [");
  Serial.print(channel);
  Serial.print("] => ");
  if (!strncmp((char *)payload, "short", length)) {
    digitalWrite(channel, HIGH);
    delay(delayShort);
    digitalWrite(channel, LOW);
  } else if (!strncmp((char *)payload, "long", length)) {
    digitalWrite(channel, HIGH);
    delay(delayLong);
    digitalWrite(channel, LOW);
  } else {
    Serial.print("unsupported");
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world n" + counter);
      // ... and resubscribe
      client.subscribe("inTopic");

      client.subscribe("eg/essen/blinds/links/up");
      client.subscribe("eg/essen/blinds/links/down");
      client.subscribe("eg/essen/blinds/mitte/up");
      client.subscribe("eg/essen/blinds/mitte/down");
      client.subscribe("eg/essen/blinds/rechts/up");
      client.subscribe("eg/essen/blinds/rechts/down");
      client.subscribe("eg/essen/blinds/alle/up");
      client.subscribe("eg/essen/blinds/alle/down");      

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(left_up, OUTPUT);
  pinMode(left_down, OUTPUT);
  pinMode(middle_up, OUTPUT);
  pinMode(middle_down, OUTPUT);
  pinMode(right_up, OUTPUT);
  pinMode(right_down, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
