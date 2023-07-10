#include "definitions.hpp"
#include "systemc.h"

SC_MODULE(testbench) {
    sc_in<bool> Clk;

    sc_out<FLIT> dN1, dN2, dN3, dN4, dN5, dN6, dN7, dN8;
    sc_out<FLIT> dS1, dS2, dS3, dS4, dS5, dS6, dS7, dS8;
    sc_out<FLIT> dL1, dL2, dL3, dL4, dL5, dL6, dL7, dL8;
    sc_out<FLIT> dO1, dO2, dO3, dO4, dO5, dO6, dO7, dO8;
    sc_out<FLIT> dC1, dC2, dC3, dC4, dC5, dC6, dC7, dC8;
    sc_out<bool> eN, eS, eL, eO, eC;

    void TbGen() {

        //pacote (8 flits) para o sul
        FLIT vdn[8] = {"100001", "110000", "001100", "101000", "010100", 
            "001000", "000100", "000010"};

        //Envio dos dados
        //Norte
        dN1.write(vdn[0]);
        dN2.write(vdn[1]);
        dN3.write(vdn[2]);
        dN4.write(vdn[3]);
        dN5.write(vdn[4]);
        dN6.write(vdn[5]);
        dN7.write(vdn[6]);
        dN8.write(vdn[7]);

        eN.write(true);
        eS.write(true);
        eL.write(true);
        eO.write(true);
        eC.write(true);

        wait(1);

        eN.write(false);
        eS.write(false);
        eL.write(false);
        eO.write(false);
        eC.write(false);

        wait(15);

        sc_stop();
    }

    SC_CTOR(testbench): eS("eS"), eL("eL"), eO("eO"), eC("eC"){
        SC_THREAD(TbGen);
        sensitive << Clk.pos();
    }
};
