//Cuida do chaveamento dependendo da resposta do árbitro, um mux com 4 entradas de um flit(6 bits)

#include "systemc.h"
#include <iostream>
#include <bitset>

SC_MODULE(mymux) {
  sc_in<bool> clk;
  sc_in<bool> A[6], B[6], C[6], D[6];
  sc_in<bool> X1, X2, X3;
  sc_out<bool> res[6];
  sc_out<bool> eop;
  
  bool eopS; //Fio para redirecionar eop, devido a complicações com o systemC
  
  void do_mymux(){
    if(X1.read() == false) {//Estou recebendo flit
      if(X3.read() == false) {
        if(X2.read() == false) {
          eopS = A[4].read();
          for(short x = 0; x < 6; x++) {
            res[x].write(A[x].read());
          }
        } else {
          eopS = C[4].read();
          for(short x = 0; x < 6; x++) {
            res[x].write(C[x].read());
          }
        }
      } else {
        if(X2.read() == false) {
          eopS = B[4].read();
          for(short x = 0; x < 6; x++) {
            res[x].write(B[x].read());
          }
        } else {
          eopS = D[4].read();
          for(short x = 0; x < 6; x++) {
            res[x].write(D[x].read());
          }
        }
      }
    } else { //Não estou recebendo flit
      eopS = false;
      for(short x = 0; x < 6; x++) {
        res[x].write(false); //Se não tiver recebendo de nenhum canal
      }
    }
    
    eop.write(eopS);
  }
  
  SC_CTOR(mymux) {
    SC_METHOD(do_mymux);
    sensitive << clk;//Sensivel ao clock
  }
  
};