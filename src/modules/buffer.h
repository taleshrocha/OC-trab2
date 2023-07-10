//Guarda os flits para envio do pacote, deverá ter espaço para 8 flits onde só guarda os pacotes quando ativado (enable) e envia pacotes quando recebe o sinal (send)
#include "systemc.h"
#include <utility>
#include <iostream>
#include <string>

SC_MODULE(buffer) {
  sc_in<bool> clk;

  //Flits do pacote para o buffer receber, setado manualmente durante o teste
  sc_in<FLIT> dataIn1, dataIn2, dataIn3, dataIn4, dataIn5, dataIn6; 

  //Dados para o buffer enviar
  sc_out<FLIT> dataOut; 

  //Recebe dos componentes de teste/outros roteadores
  sc_in<bool> enable;

  //Envie/Leia flit(do pacote) (do árbitro) ou não(do mesmo)
  sc_in<bool> send; 

  //Serve para indicar o número de posições já ocupadas, não usado em teste,
  //desde que terá já instanciado os dados nos buffers
  short pos =5; 

  FLIT dados[6] = {"000000", "000000", "000000", "000000", "000000", "000000"};

  void do_buffer() {
    dataOut.write(dados[0]);

    if(send.read()) {
      //Envia o flit do pacote pra saída e apaga o flit enviado, avançando a fila
      for(short x = 0; x < pos; x++) {
        dados[x] = dados[(x+1)];
      }

      dados[pos] = false;
      pos = pos - 1;
    }

    //Lê todos os pacotes para instânciar o buffer
    if(enable.read()){ 
      dados[0] = dataIn1.read();
      dados[1] = dataIn2.read();
      dados[2] = dataIn3.read();
      dados[3] = dataIn4.read();
      dados[4] = dataIn5.read();
      dados[5] = dataIn6.read();
    }
  }

  SC_CTOR(buffer) {
    SC_METHOD(do_buffer);
    sensitive << clk;
  }
};
