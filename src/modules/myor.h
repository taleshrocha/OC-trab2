//Serve para ativar o "send" do buffer necessário, entrando os 4 outros árbitros e saindo para ativar a leitura do buffer para a saída necessária do roteador

#include "systemc.h"
#include <iostream>
#include <bitset>

SC_MODULE(myor) {
  sc_in<bool> A, B, C, D;
  sc_out<bool> res;
  
  void do_myor(){
    res.write(A.read() || B.read() || C.read() || D.read());
  }
  
  SC_CTOR(myor): A("A"), B("B"), C("C"), D("D"), res("res") {
    SC_METHOD(do_myor);
    sensitive << A << B << C << D;
  }
  
};