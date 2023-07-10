#include <systemc>

SC_MODULE(buffer) {
  sc_in<bool> clk;

  sc_in<FLIT> dataIn1, dataIn2, dataIn3, dataIn4, dataIn5, dataIn6; 

  sc_out<FLIT> dataOut; 

  sc_in<bool> enable;

  sc_in<bool> send; 

  short pos =5; 

  FLIT dados[6] = {"000000", "000000", "000000", "000000", "000000", "000000"};

  void do_buffer() {
    dataOut.write(dados[0]);

    if(send.read()) {
      for(short x = 0; x < pos; x++) {
        dados[x] = dados[(x+1)];
      }

      dados[pos] = false;
      pos = pos - 1;
    }

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
