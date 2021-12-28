class Photoresister {

    int pin = A3;
    int sensorThres = 400;
    int analogSensor;

  public:
    Photoresister(int none) {
      pinMode(pin, INPUT);
    }
    
    int lightValue() {
      analogSensor = analogRead(pin);
      return analogSensor;
    }
};
