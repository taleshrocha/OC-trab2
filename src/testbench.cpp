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
        //Dados para serem gravados nos buffers
        bool vdn[8][6] = {{true, false, false, false, false, true}, {true, true, false, false, false, false}, {false, false, true, true, false, false}, {true, false, true, false, false, false}, {false, true, false, true, false, false}, {false, false, true, false, false, false}, {false, false, false, true, false, false}, {false, false, false, false, true, false}};//pacote (8 flits) para o sul
        bool vds[8][6] = {{false, false, false, false, false, true}, {true, false, false, false, false, false}, {false, true, false, false, false, false}, {false, false, false, false, true, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}};//pac(4) flits p/ centro
        bool vdl[8][6] = {{false, false, false, false, false, true}, {true, true, true, true, false, false}, {true, true, true, false, false, false}, {true, true, false, false, false, false}, {true, false, false, false, false, false}, {false, false, false, true, false, false}, {false, false, true, true, false, false}, {false, false, false, false, true, false}}; //pac(8) flits p/ centro
        bool vdo[8][6] = {{false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}};
        bool vdc[8][6] = {{false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}, {false, false, false, false, false, false}};
      
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


          //Sul
          dS1[x].write(vds[0][x]);
          dS2[x].write(vds[1][x]);
          dS3[x].write(vds[2][x]);
          dS4[x].write(vds[3][x]);
          dS5[x].write(vds[4][x]);
          dS6[x].write(vds[5][x]);
          dS7[x].write(vds[6][x]);
          dS8[x].write(vds[7][x]);

          //Leste
          dL1[x].write(vdl[0][x]);
          dL2[x].write(vdl[1][x]);
          dL3[x].write(vdl[2][x]);
          dL4[x].write(vdl[3][x]);
          dL5[x].write(vdl[4][x]);
          dL6[x].write(vdl[5][x]);
          dL7[x].write(vdl[6][x]);
          dL8[x].write(vdl[7][x]);

          //Oeste
          dO1[x].write(vdo[0][x]);
          dO2[x].write(vdo[1][x]);
          dO3[x].write(vdo[2][x]);
          dO4[x].write(vdo[3][x]);
          dO5[x].write(vdo[4][x]);
          dO6[x].write(vdo[5][x]);
          dO7[x].write(vdo[6][x]);
          dO8[x].write(vdo[7][x]);

          //Centro
          dC1[x].write(vdc[0][x]);
          dC2[x].write(vdc[1][x]);
          dC3[x].write(vdc[2][x]);
          dC4[x].write(vdc[3][x]);
          dC5[x].write(vdc[4][x]);
          dC6[x].write(vdc[5][x]);
          dC7[x].write(vdc[6][x]);
          dC8[x].write(vdc[7][x]);
          
        }
      
        //Ativadores da gravação dos dados nos buffers
        eN.write(true);
        eS.write(true);
        eL.write(true);
        eO.write(true);
        eC.write(true);

        wait(1, SC_NS); //Espere por 1 nano segundo para gravar os dados nos buffers

        //Desativando gravação dos buffers
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
