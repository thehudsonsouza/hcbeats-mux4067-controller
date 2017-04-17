/*!
    @file       hcBeatsMux4067.cpp
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
#include "hcBeatsMux4067.h"

/**
    Instancia um Mux setando os pins de controle, pin de entrada e saida e modo de operação
    alanógico ou digital, entrada ou saída
*/
Mux::Mux(int ctrlInputPinA, int ctrlInputPinB, int ctrlInputPinC, int ctrlInputPinD, int inOutPin, bool isAnalog, bool isInput) {

  pinA = ctrlInputPinA;
  pinB = ctrlInputPinB;
  pinC = ctrlInputPinC;
  pinD = ctrlInputPinD;
  iOPin = inOutPin;
  analogMode = isAnalog;
  inputMode = isInput;

  // Inicializando o Mux
  init();

}

/**
   Seta o hardware de acordo com as configurações setadas
*/
void Mux::init() {

  // Setando os pinos de controle
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);

  // Para facilitar a iteração no código
  ctrlPins[0] = pinA;
  ctrlPins[1] = pinB;
  ctrlPins[2] = pinC;
  ctrlPins[3] = pinD;

  // Se entrada digital
  if (analogMode == false && inputMode == true) {
    pinMode(iOPin,  INPUT_PULLUP);
  }

  // Se entrada analógica
  if (analogMode == true && inputMode == true) {
    pinMode(iOPin,  INPUT);
  }

  // Se saída digital ou analógica
  if (inputMode == false) {
    pinMode(iOPin,  OUTPUT);
  }

  // Mapeando as portas
  setChannelMap();
}

/**
   Mapeia as portas do Mux
   de 0 a 15 binário (LSF)
*/
void Mux::setChannelMap() {
  channelMap[0] = B0000;
  channelMap[1] = B1000;
  channelMap[2] = B0100;
  channelMap[3] = B1100;
  channelMap[4] = B0010;
  channelMap[5] = B1010;
  channelMap[6] = B0110;
  channelMap[7] = B1110;
  channelMap[8] = B0001;
  channelMap[9] = B1001;
  channelMap[10] = B0101;
  channelMap[11] = B1101;
  channelMap[12] = B0011;
  channelMap[13] = B1011;
  channelMap[14] = B0111;
  channelMap[15] = B1111;
}

/**
   Faz a seleção do canal de saída através da manipulação
   dos pinos de controle binários.
   Ex.
   Para enviarmos algo ao canal 11 da CMOS, precisamos setar
   os pinos de controle de S0 a S3 (A0 a A3 dependendo do datasheet) respectivamente em High, High, Low, High (1101)
   Ou seja 11 em binário LSF (Representação binária de 11 com 4 bits lendo da esquerda para a direita)
   Dec 11 = Bin 1011
   Dec 11 = Bin LSF 1101
*/
void Mux::setOutputChannel(int channel) {

  // iterando os 4 pinos de controle
  for (int idx = 0; idx < 4; idx++) {
    // Setando o estado do pino de controle de acordo com o bit equivalente
    int val = bitRead(channel, idx);

    digitalWrite(ctrlPins[idx], val);
  }
}

/**
   Escreve um valor digital na porta indicada
*/
void Mux::writeData(int channel, int value) {

  // Setamos o canal de saída
  setOutputChannel(channel);

  // Escrevemos o valor informado

  if (analogMode) {
    analogWrite(iOPin, value);
  }
  else {
    digitalWrite(iOPin, value);
  }

  // Para dar um alivio ao sistema
  delay(1);
}






