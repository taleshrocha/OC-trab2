#include "definitions.hpp"
#include "systemc.h"

SC_MODULE(testbench) {
    sc_in<bool> Clk;

    sc_out<FLIT> dD1, dD2, dD3, dD4, dD5, dD6, dD7, dD8;
    sc_out<FLIT> dE1, dE2, dE3, dE4, dE5, dE6, dE7, dE8;
    sc_out<FLIT> dL1, dL2, dL3, dL4, dL5, dL6, dL7, dL8;
    sc_out<FLIT> dF1, dF2, dF3, dF4, dF5, dF6, dF7, dF8;
    sc_out<bool> eD, eE, eL, eF;

    void TbGen() {

        //pacote (8 flits) para o sul
        FLIT vdn[8] = {"100001", "110000", "001100", "101000", "010100", 
            "001000", "000100", "000010"};

        //Envio dos dados
        //Dorte
        dD1.write(vdn[0]);
        dD2.write(vdn[1]);
        dD3.write(vdn[2]);
        dD4.write(vdn[3]);
        dD5.write(vdn[4]);
        dD6.write(vdn[5]);
        dD7.write(vdn[6]);
        dD8.write(vdn[7]);

        eD.write(true);
        eE.write(true);
        eL.write(true);
        eF.write(true);

        wait(1);

        eD.write(false);
        eE.write(false);
        eL.write(false);
        eF.write(false);

        wait(15);

        sc_stop();
    }

    SC_CTOR(testbench): eE("eE"), eL("eL"), eF("eF") {
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};
