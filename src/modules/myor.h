#include <systemc>

SC_MODULE(myor) {
  sc_in<bool> A, B, C;
  sc_out<bool> res;
  
  void do_myor(){
    res.write(A.read() || B.read() || C.read());
  }
  
  SC_CTOR(myor): A("A"), B("B"), C("C"), res("res") {
    SC_METHOD(do_myor);
    sensitive << A << B << C;
  }
  
};
