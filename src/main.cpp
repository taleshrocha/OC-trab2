#include <systemc>
#include <iostream>

#include "definitions.hpp"
#include "testbench.cpp"
#include "modules/roteador.h"
#include "modules/memdetest.h"

int sc_main(int argc, char* argv[]) {
  sc_clock clock("clock", 100, SC_NS, 0.5);

  //Instanciando roteador, componentes de teste e o testbench
  roteador rot("roteador");
  testbench Tb("testbench");

  //Instanciando fios
  sc_signal<bool> eN, eS, eL, eO, eC;

  sc_signal<FLIT> dN1, dN2, dN3, dN4, dN5, dN6, dN7, dN8;
  sc_signal<FLIT> dS1, dS2, dS3, dS4, dS5, dS6, dS7, dS8;
  sc_signal<FLIT> dL1, dL2, dL3, dL4, dL5, dL6, dL7, dL8;
  sc_signal<FLIT> dO1, dO2, dO3, dO4, dO5, dO6, dO7, dO8;
  sc_signal<FLIT> dC1, dC2, dC3, dC4, dC5, dC6, dC7, dC8;

  sc_signal<FLIT> doN, doS, doL, doO, doC;

  //Conectando fios
  rot.clk(clock);
  Tb.Clk(clock);

  Tb.eN(eN);
  Tb.eS(eS);
  Tb.eL(eL);
  Tb.eO(eO);
  Tb.eC(eC);

  Tb.dN1(dN1);
  Tb.dN2(dN2);
  Tb.dN3(dN3);
  Tb.dN4(dN4);
  Tb.dN5(dN5);
  Tb.dN6(dN6);
  Tb.dN7(dN7);
  Tb.dN8(dN8);

  Tb.dS1(dS1);
  Tb.dS2(dS2);
  Tb.dS3(dS3);
  Tb.dS4(dS4);
  Tb.dS5(dS5);
  Tb.dS6(dS6);
  Tb.dS7(dS7);
  Tb.dS8(dS8);

  Tb.dL1(dL1);
  Tb.dL2(dL2);
  Tb.dL3(dL3);
  Tb.dL4(dL4);
  Tb.dL5(dL5);
  Tb.dL6(dL6);
  Tb.dL7(dL7);
  Tb.dL8(dL8);

  Tb.dO1(dO1);
  Tb.dO2(dO2);
  Tb.dO3(dO3);
  Tb.dO4(dO4);
  Tb.dO5(dO5);
  Tb.dO6(dO6);
  Tb.dO7(dO7);
  Tb.dO8(dO8);

  Tb.dC1(dC1);
  Tb.dC2(dC2);
  Tb.dC3(dC3);
  Tb.dC4(dC4);
  Tb.dC5(dC5);
  Tb.dC6(dC6);
  Tb.dC7(dC7);
  Tb.dC8(dC8);

  rot.dataInN1(dN1);
  rot.dataInN2(dN2);
  rot.dataInN3(dN3);
  rot.dataInN4(dN4);
  rot.dataInN5(dN5);
  rot.dataInN6(dN6);
  rot.dataInN7(dN7);
  rot.dataInN8(dN8);

  rot.dataInS1(dS1);
  rot.dataInS2(dS2);
  rot.dataInS3(dS3);
  rot.dataInS4(dS4);
  rot.dataInS5(dS5);
  rot.dataInS6(dS6);
  rot.dataInS7(dS7);
  rot.dataInS8(dS8);

  rot.dataInL1(dL1);
  rot.dataInL2(dL2);
  rot.dataInL3(dL3);
  rot.dataInL4(dL4);
  rot.dataInL5(dL5);
  rot.dataInL6(dL6);
  rot.dataInL7(dL7);
  rot.dataInL8(dL8);

  rot.dataInO1(dO1);
  rot.dataInO2(dO2);
  rot.dataInO3(dO3);
  rot.dataInO4(dO4);
  rot.dataInO5(dO5);
  rot.dataInO6(dO6);
  rot.dataInO7(dO7);
  rot.dataInO8(dO8);

  rot.dataInC1(dC1);
  rot.dataInC2(dC2);
  rot.dataInC3(dC3);
  rot.dataInC4(dC4);
  rot.dataInC5(dC5);
  rot.dataInC6(dC6);
  rot.dataInC7(dC7);
  rot.dataInC8(dC8);

  rot.enableN(eN);
  rot.enableS(eS);
  rot.enableL(eL);
  rot.enableO(eO);
  rot.enableC(eC);

  rot.dataOutN(doN);
  rot.dataOutS(doS);
  rot.dataOutL(doL);
  rot.dataOutO(doO);
  rot.dataOutC(doC);

  // Waves --------------------------------------------------------------------

  sc_trace_file *fp;
  fp=sc_create_vcd_trace_file("wave");
  fp->set_time_unit(1, sc_core::SC_NS);

  sc_trace(fp, clock, "clock");

  sc_trace(fp, rot.dataInN1,"router|dataInN1");
  sc_trace(fp, rot.dataOutN,"router|dataOutN");
  sc_trace(fp, rot.dataInS1,"router|dataInS1");
  sc_trace(fp, rot.dataOutS,"router|dataOutS");

  sc_start();

  sc_close_vcd_trace_file(fp);

  return 0;
}
