#include <dht.h>
dht DHT;

class TempAndHum {
    int pin = 2;
#define DHT11_PIN pin
  public:
    TempAndHum(int pin) {
      //error if not
    }
    double temp() {
      double chk = DHT.read11(DHT11_PIN);
      double needed = DHT.humidity;
      return (DHT.temperature);
    }
    int humidity() {
      return (DHT.humidity);
    }
};
