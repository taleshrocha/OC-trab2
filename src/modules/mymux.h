//Cuida do chaveamento dependendo da resposta do árbitro, um mux com 4 entradas de um flit(6 bits)

#include "systemc.h"

SC_MODULE(mymux) {
  sc_in<bool> clk;
  sc_in<FLIT> A, B, C;
  sc_in<bool> X1, X2, X3;
  sc_out<FLIT> res;
  sc_out<bool> eop;

  bool eopS;

  void do_mymux() {
    FLIT aValue = A.read();
    FLIT bValue = B.read();
    FLIT cValue = C.read();

    if (X1.read() == false) { // Estou recebendo flit
      if (X3.read() == false) {
        if (X2.read() == false) {
          eopS = (bool) aValue[4];
          res.write(aValue);
        } else {
          eopS = (bool) cValue[4];
          res.write(cValue);
        }
      } else {
        if (X2.read() == false) {
          eopS = (bool) bValue[4];
          res.write(bValue);
        } 
        //else {
        //  eopS = (bool) dValue[4];
        //  res.write(dValue);
        //}
      }
    } else { // Não estou recebendo flit
      eopS = false;
      res.write("000000"); // Set default value when not receiving from any channel
    }

    eop.write(eopS);
  }

  SC_CTOR(mymux) {
    SC_METHOD(do_mymux);
    sensitive << clk; // Sensitive to the clock
  }
};
