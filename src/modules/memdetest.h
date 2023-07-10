//Serve para testar
#include "systemc.h"
#include <utility>
#include <iostream>

SC_MODULE(memdetest) {
  sc_in<bool> clk;
  sc_in<bool> dataIn[6]; //Flits recebidos do roteador
  
  bool recebe = false;
  short pos = 0; //Para guardar os dados nos espaços disponíveis
  bool dados[16][6] = {{false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}};
    
  void do_memdetest() {
    if(dataIn[4]) {
      recebe = false;
    }
    
    if(dataIn[5]) {
      recebe = true;
    }
    
    if(recebe) {
      cout<<"guarda arq?"<<endl;
      for(short x = 0; x < 6; x++) {
        cout<<dataIn[x].read();
        dados[pos][x] = dataIn[x].read();
      }
      pos = pos + 1;
      cout<<endl;
    }
  }
  
  SC_CTOR(memdetest) {
    SC_METHOD(do_memdetest);
    sensitive << clk;
  }
};