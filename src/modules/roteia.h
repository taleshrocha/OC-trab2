#include <systemc>

SC_MODULE(roteia) {
  sc_in<bool> clk;

  sc_in<FLIT> dataIn; 

  sc_out<bool> D, E, L, F;
  
  void do_roteia(){
    FLIT dataInAux = dataIn.read();

    bool req[5] = {false, false, false, false, false};
    
    if(dataInAux[5]) { 
      if(dataInAux[2]) { 
        if(dataInAux[3]) { 
          req[2] = true;
        } else { 
          req[3] = true;
        }
      } else {
        if(dataInAux[0]) { 
          if(dataInAux[1]) { 
          	req[0] = true;
          } else { 
          	req[1] = true;
          }
        } 
      }
    }
    D.write(req[0]);
    E.write(req[1]);
    L.write(req[2]);
    F.write(req[3]);
  }
  
  SC_CTOR(roteia) 
  : clk("clk"), dataIn("dataIn"), D("D"), E("E"), L("L"), F("F") {
    SC_METHOD(do_roteia);
    sensitive << clk;
  }
  
};
