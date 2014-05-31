#include <Process.h>
#include "DHT.h"
#include "passwords.h"

#define DHTTYPE DHT11
#define DHTPIN 2

const unsigned long postingInterval = 10000;  //delay between updates to xively.com
unsigned long lastRequest = 0;      // when you last made a request
String dataString = "";
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // start serial port:
  Bridge.begin();
  Serial.begin(9600);

  dht.begin();

  // while(!Serial);    // wait for Network Serial to open
  Serial.println("Xively client");

  // Do a first update immediately
  updateData();
  sendData();
  lastRequest = millis();
}

void loop() {
  // get a timestamp so you can calculate reading and sending intervals:
  long now = millis();

  // if the sending interval has passed since your
  // last connection, then connect again and send data:
  if (now - lastRequest >= postingInterval) {
    updateData();
    sendData();
    lastRequest = now;
  }

}

void updateData() {
  // convert the readings to a String to send it:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    dataString = "Temperature,";
    dataString += t;
    // add pressure:
    dataString += "\nHumidity,";
    dataString += h;

    Serial.println(dataString);
  }
}

// this method makes a HTTP connection to the server:
void sendData() {
  // form the string for the API header parameter:
  String apiString = "X-ApiKey: ";
  apiString += APIKEY;

  // form the string for the URL parameter:
  String url = "https://api.xively.com/v2/feeds/";
  url += FEEDID;
  url += ".csv";

  // Send the HTTP PUT request

  // Is better to declare the Process here, so when the
  // sendData function finishes the resources are immediately
  // released. Declaring it global works too, BTW.
  Process xively;
  Serial.print("\n\nSending data... ");
  xively.begin("curl");
  xively.addParameter("-k");
  xively.addParameter("--request");
  xively.addParameter("PUT");
  xively.addParameter("--data");
  xively.addParameter(dataString);
  xively.addParameter("--header");
  xively.addParameter(apiString);
  xively.addParameter(url);
  digitalWrite(13, HIGH);
  xively.run();
  Serial.println("done!");
  digitalWrite(13, LOW);

  // If there's incoming data from the net connection,
  // send it out the Serial:
  while (xively.available()>0) {
    char c = xively.read();
    Serial.write(c);
    Serial.print("incoming data");
  }

}
