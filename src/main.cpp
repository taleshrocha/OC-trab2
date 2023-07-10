#include "systemc.h"
#include <iostream>

#include "testbench.cpp"
#include "modules/roteador.h"
#include "modules/memdetest.h"

int sc_main(int argc, char* argv[]) {
  sc_clock clock("clock", 100, SC_NS, 0.5);

  //Instanciando roteador, componentes de teste e o testbench
  roteador rot("router");
  testbench Tb("testbench");

  //Instanciando fios
  sc_signal<bool> eN, eS, eL, eO, eC;
  sc_signal<bool> dN1[6], dN2[6], dN3[6], dN4[6], dN5[6], dN6[6], dN7[6], dN8[6];
  sc_signal<bool> dS1[6], dS2[6], dS3[6], dS4[6], dS5[6], dS6[6], dS7[6], dS8[6];
  sc_signal<bool> dL1[6], dL2[6], dL3[6], dL4[6], dL5[6], dL6[6], dL7[6], dL8[6];
  sc_signal<bool> dO1[6], dO2[6], dO3[6], dO4[6], dO5[6], dO6[6], dO7[6], dO8[6];
  sc_signal<bool> dC1[6], dC2[6], dC3[6], dC4[6], dC5[6], dC6[6], dC7[6], dC8[6];
  sc_signal<bool> doN[6], doS[6], doL[6], doO[6], doC[6];

  //Conectando fios
  rot.clk(clock);
  Tb.Clk(clock);

  Tb.eN(eN);
  Tb.eS(eS);
  Tb.eL(eL);
  Tb.eO(eO);
  Tb.eC(eC);

  for(short x = 0; x < 6; x++) {

    Tb.dN1[x](dN1[x]);
    Tb.dN2[x](dN2[x]);
    Tb.dN3[x](dN3[x]);
    Tb.dN4[x](dN4[x]);
    Tb.dN5[x](dN5[x]);
    Tb.dN6[x](dN6[x]);
    Tb.dN7[x](dN7[x]);
    Tb.dN8[x](dN8[x]);

    Tb.dS1[x](dS1[x]);
    Tb.dS2[x](dS2[x]);
    Tb.dS3[x](dS3[x]);
    Tb.dS4[x](dS4[x]);
    Tb.dS5[x](dS5[x]);
    Tb.dS6[x](dS6[x]);
    Tb.dS7[x](dS7[x]);
    Tb.dS8[x](dS8[x]);

    Tb.dL1[x](dL1[x]);
    Tb.dL2[x](dL2[x]);
    Tb.dL3[x](dL3[x]);
    Tb.dL4[x](dL4[x]);
    Tb.dL5[x](dL5[x]);
    Tb.dL6[x](dL6[x]);
    Tb.dL7[x](dL7[x]);
    Tb.dL8[x](dL8[x]);

    Tb.dO1[x](dO1[x]);
    Tb.dO2[x](dO2[x]);
    Tb.dO3[x](dO3[x]);
    Tb.dO4[x](dO4[x]);
    Tb.dO5[x](dO5[x]);
    Tb.dO6[x](dO6[x]);
    Tb.dO7[x](dO7[x]);
    Tb.dO8[x](dO8[x]);

    Tb.dC1[x](dC1[x]);
    Tb.dC2[x](dC2[x]);
    Tb.dC3[x](dC3[x]);
    Tb.dC4[x](dC4[x]);
    Tb.dC5[x](dC5[x]);
    Tb.dC6[x](dC6[x]);
    Tb.dC7[x](dC7[x]);
    Tb.dC8[x](dC8[x]);

    rot.dataInN1[x](dN1[x]);
    rot.dataInN2[x](dN2[x]);
    rot.dataInN3[x](dN3[x]);
    rot.dataInN4[x](dN4[x]);
    rot.dataInN5[x](dN5[x]);
    rot.dataInN6[x](dN6[x]);
    rot.dataInN7[x](dN7[x]);
    rot.dataInN8[x](dN8[x]);

    rot.dataInS1[x](dS1[x]);
    rot.dataInS2[x](dS2[x]);
    rot.dataInS3[x](dS3[x]);
    rot.dataInS4[x](dS4[x]);
    rot.dataInS5[x](dS5[x]);
    rot.dataInS6[x](dS6[x]);
    rot.dataInS7[x](dS7[x]);
    rot.dataInS8[x](dS8[x]);

    rot.dataInL1[x](dL1[x]);
    rot.dataInL2[x](dL2[x]);
    rot.dataInL3[x](dL3[x]);
    rot.dataInL4[x](dL4[x]);
    rot.dataInL5[x](dL5[x]);
    rot.dataInL6[x](dL6[x]);
    rot.dataInL7[x](dL7[x]);
    rot.dataInL8[x](dL8[x]);

    rot.dataInO1[x](dO1[x]);
    rot.dataInO2[x](dO2[x]);
    rot.dataInO3[x](dO3[x]);
    rot.dataInO4[x](dO4[x]);
    rot.dataInO5[x](dO5[x]);
    rot.dataInO6[x](dO6[x]);
    rot.dataInO7[x](dO7[x]);
    rot.dataInO8[x](dO8[x]);

    rot.dataInC1[x](dC1[x]);
    rot.dataInC2[x](dC2[x]);
    rot.dataInC3[x](dC3[x]);
    rot.dataInC4[x](dC4[x]);
    rot.dataInC5[x](dC5[x]);
    rot.dataInC6[x](dC6[x]);
    rot.dataInC7[x](dC7[x]);
    rot.dataInC8[x](dC8[x]);

  }

  rot.enableN(eN);
  rot.enableS(eS);
  rot.enableL(eL);
  rot.enableO(eO);
  rot.enableC(eC);

  for(short x = 0; x < 6; x++) {

    rot.dataOutN[x](doN[x]);
    rot.dataOutS[x](doS[x]);
    rot.dataOutL[x](doL[x]);
    rot.dataOutO[x](doO[x]);
    rot.dataOutC[x](doC[x]);

  }

  // Waves --------------------------------------------------------------------

  sc_trace_file *fp;
  fp=sc_create_vcd_trace_file("wave");
  fp->set_time_unit(1, sc_core::SC_NS);

  sc_trace(fp, clock, "clock");

  for(short x = 0; x < 6; x++) {
    sc_trace(fp, rot.dataInN1[x],"router|dataInN1|" + std::to_string(x));
    sc_trace(fp, rot.dataOutS[x],"router|dataOutS|" + std::to_string(x));
  }

  sc_start();

  sc_close_vcd_trace_file(fp);

  return 0;
}
