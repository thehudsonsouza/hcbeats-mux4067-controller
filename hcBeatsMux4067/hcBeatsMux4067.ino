#include "hcBeatsMux4067.h"

// Definindo o mux 1
Mux output1 (8, 9, 10, 11, 13, true, false);

void setup() {

  Serial.begin(9600);

}

void loop() {

  for (int idx = 0; idx < 10; idx++) {
    for (int idx2 = 0; idx2 < 200; idx2++) {
      output1.writeData(idx, idx2);
      delay(5);
    }
  }
}


