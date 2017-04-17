/*!
    @file       hcBeatsMux4067.h
    Project     HC-Beats Surface Controller
    @brief      Controlador para CMOS 4067
    @author     Hudson C. Souza
    @date       14/04/2017
    @license    MIT - Copyright (c) 2017 Hudson C. Souza

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/
#ifndef hcBeatsMux4067_h
#define hcBeatsMux4067_h

#include <Arduino.h>

class Mux
{

  private:
    int pinA;
    int pinB;
    int pinC;
    int pinD;
    int iOPin;
    int ctrlPins[4];
    bool analogMode;
    bool inputMode;
    byte channelMap[16];
    
  public:
    Mux(int ctrlInputPinA, int ctrlInputPinB, int ctrlInputPinC, int ctrlInputPinD, int inOutPin, bool isAnalog, bool isInput);

  private:
    void init();
    void setChannelMap();
    
  public:
    void setOutputChannel(int channel);
    void writeData(int port, int value);
    int readDigitalData(int port);
};

#endif
