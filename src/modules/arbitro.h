#include <systemc>
#include "circbuffer.h"

SC_MODULE(arbitro) {
  sc_in<bool> clk;
  sc_in<bool> eop;
  sc_in<bool> reqIn1, reqIn2, reqIn3;
  sc_in<bool> envArq;
  sc_in<short> posMux;

  sc_out<bool> env1, env2, env3, env4;
  sc_out<bool> muxMude1, muxMude2, muxMude3;
  sc_out<bool> avn;

  circbuffer cb;

  sc_signal<short> pM;
  sc_signal<bool> av, eA;

  void do_arbitro() {

    if(envArq.read() == 1) {
      avn.write(0);
      if(posMux.read() == 0) {
        env1.write(true);
        muxMude1.write(false);
        muxMude2.write(false);
        muxMude3.write(false);
      } else if(posMux.read() == 1) {
        env2.write(true);
        muxMude1.write(false);
        muxMude2.write(false);
        muxMude3.write(true);
      } else if(posMux.read() == 2) {
        env3.write(true);
        muxMude1.write(false);
        muxMude2.write(true);
        muxMude3.write(false);
      } else if(posMux.read() == 3) {
        env4.write(true);
        muxMude1.write(false);
        muxMude2.write(true);
        muxMude3.write(true);
      }
    } else {
      avn.write(1);
      env1.write(false);
      env2.write(false);
      env3.write(false);
      env4.write(false);
      muxMude1.write(true);
      muxMude2.write(false);
      muxMude3.write(false);
    }

    if(eop.read())
      avn.write(true);
  }

  SC_CTOR(arbitro)
    : clk("clk"), eop("eop"),
    reqIn1("reqIn1"), reqIn2("reqIn2"), reqIn3("reqIn3"),
    envArq("envArq"), posMux("posMux"), 
    env1("env1"), env2("env2"), env3("env3"), env4("env4"),
    muxMude1("muxMude1"), muxMude2("muxMude2"), muxMude3("muxMude3"), avn("avn"),
    cb("cb") {

    avn(av);

    cb.advance(av);
    cb.reqIn1(reqIn1);
    cb.reqIn2(reqIn2);
    cb.reqIn3(reqIn3);
    cb.reqOut(eA);
    cb.posOut(pM);
    cb.clk(clk);

    envArq(eA);
    posMux(pM);

    SC_METHOD(do_arbitro);

    sensitive << clk;
  }
};
