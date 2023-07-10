#include "definitions.hpp"
#include "systemc.h"

SC_MODULE(testbench) {
    sc_in<bool> Clk;
    sc_out<bool> dN1[6], dN2[6], dN3[6], dN4[6], dN5[6], dN6[6], dN7[6], dN8[6];
    sc_out<bool> dS1[6], dS2[6], dS3[6], dS4[6], dS5[6], dS6[6], dS7[6], dS8[6];
    sc_out<bool> dL1[6], dL2[6], dL3[6], dL4[6], dL5[6], dL6[6], dL7[6], dL8[6];
    sc_out<bool> dO1[6], dO2[6], dO3[6], dO4[6], dO5[6], dO6[6], dO7[6], dO8[6];
    sc_out<bool> dC1[6], dC2[6], dC3[6], dC4[6], dC5[6], dC6[6], dC7[6], dC8[6];
    sc_out<bool> eN, eS, eL, eO, eC;

    void TbGen() {
        //pacote (8 flits) para o sul
        bool vdn[8][6] = {{true, false, false, false, false, true}, {true, true, false, false, false, false}, {false, false, true, true, false, false}, {true, false, true, false, false, false}, {false, true, false, true, false, false}, {false, false, true, false, false, false}, {false, false, false, true, false, false}, {false, false, false, false, true, false}};

        //Envio dos dados
        for(short x = 0; x < 6; x++) {
            //Norte
            dN1[x].write(vdn[0][x]);
            dN2[x].write(vdn[1][x]);
            dN3[x].write(vdn[2][x]);
            dN4[x].write(vdn[3][x]);
            dN5[x].write(vdn[4][x]);
            dN6[x].write(vdn[5][x]);
            dN7[x].write(vdn[6][x]);
            dN8[x].write(vdn[7][x]);
        }

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
