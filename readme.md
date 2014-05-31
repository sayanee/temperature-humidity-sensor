#Temperature and Humidity logger

##requirements

1. [Arduino Yun](http://arduino.cc/en/Main/ArduinoBoardYun?from=Products.ArduinoYUN)
1. [Xively](https://xively.com/)
1. [DHT11](http://www.adafruit.com/products/386) basic temperature and humidity sensor
1. [Circuit layout](https://learn.adafruit.com/dht/connecting-to-a-dhtxx-sensor) with an Arduino Yun

##install

1. open Arduino project `YunXivelyTemperature.ino` with the [Arduino IDE that supports Arduino Yun](http://arduino.cc/en/main/software#toc3)
1. make a file `passwords.h` and put in the relevant info as stated in `passwords.sample.h`
1. upload the code to Arduino Yun