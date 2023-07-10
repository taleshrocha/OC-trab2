#include <systemc>

SC_MODULE(circbuffer) {
  sc_in<bool> clk;
  sc_in<bool> advance;
  sc_in<bool> reqIn1, reqIn2, reqIn3;
  sc_out<bool> reqOut;
  sc_out<short> posOut;
  
  
  bool reqs[4] = {false, false, false, false};
  short pont = 0;
  
  void do_circbuffer() {
    
    if(advance.read()) {
      if(pont == 3) {
        pont = 0;
      } else {
        pont = pont + 1;
      }
    
      reqs[0] = reqIn1.read();
      reqs[1] = reqIn2.read();
      reqs[2] = reqIn3.read();
    }
    
    posOut.write(pont);
    reqOut.write(reqs[pont]);
  }
  
  SC_CTOR(circbuffer) 
  : advance("adv"), reqIn1("rI1"), reqIn2("rI2"), reqIn3("rI3"), 
    reqOut("rO"), posOut("pO") {
    SC_METHOD(do_circbuffer);
    sensitive << clk.pos();
  }
};
