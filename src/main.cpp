#include <systemc>
#include <iostream>

#include "definitions.hpp"
#include "testbench.cpp"
#include "modules/roteador.h"

int sc_main(int argc, char* argv[]) {
  sc_clock clock("clock", 100, SC_NS, 0.5);

  //Instanciando roteador, componentes de teste e o testbench
  roteador rot("roteador");
  testbench Tb("testbench");

  //Instanciando fios
  sc_signal<bool> eD, eE, eL, eF;

  sc_signal<FLIT> dD1, dD2, dD3, dD4, dD5, dD6, dD7, dD8;
  sc_signal<FLIT> dE1, dE2, dE3, dE4, dE5, dE6, dE7, dE8;
  sc_signal<FLIT> dL1, dL2, dL3, dL4, dL5, dL6, dL7, dL8;
  sc_signal<FLIT> dF1, dF2, dF3, dF4, dF5, dF6, dF7, dF8;

  sc_signal<FLIT> doD, doE, doL, doF;

  //Conectando fios
  rot.clk(clock);
  Tb.Clk(clock);

  Tb.eD(eD);
  Tb.eE(eE);
  Tb.eL(eL);
  Tb.eF(eF);

  Tb.dD1(dD1);
  Tb.dD2(dD2);
  Tb.dD3(dD3);
  Tb.dD4(dD4);
  Tb.dD5(dD5);
  Tb.dD6(dD6);
  Tb.dD7(dD7);
  Tb.dD8(dD8);

  Tb.dE1(dE1);
  Tb.dE2(dE2);
  Tb.dE3(dE3);
  Tb.dE4(dE4);
  Tb.dE5(dE5);
  Tb.dE6(dE6);
  Tb.dE7(dE7);
  Tb.dE8(dE8);

  Tb.dL1(dL1);
  Tb.dL2(dL2);
  Tb.dL3(dL3);
  Tb.dL4(dL4);
  Tb.dL5(dL5);
  Tb.dL6(dL6);
  Tb.dL7(dL7);
  Tb.dL8(dL8);

  Tb.dF1(dF1);
  Tb.dF2(dF2);
  Tb.dF3(dF3);
  Tb.dF4(dF4);
  Tb.dF5(dF5);
  Tb.dF6(dF6);
  Tb.dF7(dF7);
  Tb.dF8(dF8);

  rot.dataInD1(dD1);
  rot.dataInD2(dD2);
  rot.dataInD3(dD3);
  rot.dataInD4(dD4);
  rot.dataInD5(dD5);
  rot.dataInD6(dD6);
  rot.dataInD7(dD7);
  rot.dataInD8(dD8);

  rot.dataInE1(dE1);
  rot.dataInE2(dE2);
  rot.dataInE3(dE3);
  rot.dataInE4(dE4);
  rot.dataInE5(dE5);
  rot.dataInE6(dE6);
  rot.dataInE7(dE7);
  rot.dataInE8(dE8);

  rot.dataInL1(dL1);
  rot.dataInL2(dL2);
  rot.dataInL3(dL3);
  rot.dataInL4(dL4);
  rot.dataInL5(dL5);
  rot.dataInL6(dL6);
  rot.dataInL7(dL7);
  rot.dataInL8(dL8);

  rot.dataInF1(dF1);
  rot.dataInF2(dF2);
  rot.dataInF3(dF3);
  rot.dataInF4(dF4);
  rot.dataInF5(dF5);
  rot.dataInF6(dF6);
  rot.dataInF7(dF7);
  rot.dataInF8(dF8);

  rot.enableD(eD);
  rot.enableE(eE);
  rot.enableL(eL);
  rot.enableF(eF);

  rot.dataOutD(doD);
  rot.dataOutE(doE);
  rot.dataOutL(doL);
  rot.dataOutF(doF);

  // Waves --------------------------------------------------------------------

  sc_trace_file *fp;
  fp=sc_create_vcd_trace_file("wave");
  fp->set_time_unit(1, sc_core::SC_NS);

  sc_trace(fp, clock, "clock");

  sc_trace(fp, rot.dataInD1,"router|dataInD1");
  sc_trace(fp, rot.dataOutD,"router|dataOutD");
  sc_trace(fp, rot.dataInE1,"router|dataInE1");
  sc_trace(fp, rot.dataOutE,"router|dataOutE");

  sc_start();

  sc_close_vcd_trace_file(fp);

  return 0;
}
