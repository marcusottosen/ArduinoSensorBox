// (Wire is a standard library included with Arduino.):
#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;


//Pins: sda: A4   -   scl: A5
//SKAL HAVE 3.3V!!!!!
class BaroAndTemp {

    char status;
    double T, P, p0, a;

  public:
    BaroAndTemp(int arduinoGiverIkkeMening) {
      //just bc
    }
    void initBaro() {
      pressure.begin();
    }
    double tempValue() {
      // Start a temperature measurement:
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = pressure.startTemperature();
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed temperature measurement:
        // Note that the measurement is stored in the variable T.
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getTemperature(T);
        if (status != 0)
        {
          return T;
        }
        else return 0;
      }
      else return 0;
    }
    double baroValue() {
      // Start a temperature measurement:
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = pressure.startTemperature();
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);
        status = pressure.getTemperature(T);
        if (status != 0)
        {
          // Start a pressure measurement:
          status = pressure.startPressure(3);
          if (status != 0)
          {
            // Wait for the measurement to complete:
            delay(status);

            status = pressure.getPressure(P, T);
            if (status != 0)
            {
              return P; //mb
            }
            else return 0;
          }
          else return 0;
        }
        else return 0;
      }
      else return 0;
    }
};
