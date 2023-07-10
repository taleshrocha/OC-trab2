//Guarda os flits para envio do pacote, deverá ter espaço para 8 flits onde só guarda os pacotes quando ativado (enable) e envia pacotes quando recebe o sinal (send)
#include "systemc.h"
#include <utility>
#include <iostream>
#include <string>

SC_MODULE(buffer) {
  sc_in<bool> clk;
  sc_in<bool> enable; //Receba dos componentes de teste/outros roteadores
  sc_in<bool> send; //Envie/Leia flit(do pacote) (do árbitro) ou não(do mesmo)
  sc_in<bool> dataIn1[6], dataIn2[6], dataIn3[6], dataIn4[6], dataIn5[6], dataIn6[6], dataIn7[6], dataIn8[6]; //Flits do pacote para o buffer receber, setado manualmente durante o teste
  sc_out<bool> dataOut[6]; //Dados para o buffer enviar
  
  short pos = 7; //Serve para indicar o número de posições já ocupadas, não usado em teste, desde que terá já instanciado os dados nos buffers
  bool dados[8][6] = {{false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}};
    
  void do_buffer() {
    cout<<"buffer atual ";
    for(short x = 0; x < 6; x++) {
        dataOut[x].write(dados[0][x]);
        cout << dados[0][x];
    }
    cout<<endl;
    
    if(send.read()) {
      //Envia o flit do pacote pra saída e apaga o flit enviado, avançando a fila
      for(short x = 0; x < pos; x++) {
        for(short y = 0; y < 6; y++) {
          dados[x][y] = dados[(x+1)][y];
        }
      }
      
      for(short x = 0; x < 6; x++) {
        dados[pos][x] = false;
      }
      pos = pos - 1;
    }
    if(enable.read()){ //Lê todos os pacotes para instânciar o buffer
      cout<<"leia algo"<<endl;
      for(short x = 0; x < 6; x++) {
        dados[0][x] = dataIn1[x].read();
        dados[1][x] = dataIn2[x].read();
        dados[2][x] = dataIn3[x].read();
        dados[3][x] = dataIn4[x].read();
        dados[4][x] = dataIn5[x].read();
        dados[5][x] = dataIn6[x].read();
        dados[6][x] = dataIn7[x].read();
        dados[7][x] = dataIn8[x].read();
      }
      /*
      //Teste (lendo certo)
      for(short y = 0; y < 8; y++) {
        for(short x = 0; x < 6; x++) {
          cout<< dados[y][x];
        }
        cout<<endl;
      }*/
    }
  }
  
  SC_CTOR(buffer) {
    SC_METHOD(do_buffer);
    sensitive << clk;
  }
};