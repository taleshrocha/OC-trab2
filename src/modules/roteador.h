#include <systemc>
#include "buffer.h"
#include "mymux.h"
#include "arbitro.h"
#include "roteia.h"
#include "myor.h"

SC_MODULE(roteador) {
    sc_in<bool> dataInN1[6], dataInN2[6], dataInN3[6], dataInN4[6], dataInN5[6], dataInN6[6], dataInN7[6], dataInN8[6]; //Entrada de flits do norte
    sc_in<bool> dataInS1[6], dataInS2[6], dataInS3[6], dataInS4[6], dataInS5[6], dataInS6[6], dataInS7[6], dataInS8[6]; //Entrada de flits do norte
    sc_in<bool> dataInL1[6], dataInL2[6], dataInL3[6], dataInL4[6], dataInL5[6], dataInL6[6], dataInL7[6], dataInL8[6]; //Entrada de flits do norte
    sc_in<bool> dataInO1[6], dataInO2[6], dataInO3[6], dataInO4[6], dataInO5[6], dataInO6[6], dataInO7[6], dataInO8[6]; //Entrada de flits do norte
    sc_in<bool> dataInC1[6], dataInC2[6], dataInC3[6], dataInC4[6], dataInC5[6], dataInC6[6], dataInC7[6], dataInC8[6]; //Entrada de flits do norte
    sc_in<bool> clk; //Clock para funcionamento do roteador
    sc_out<bool> dataOutN[6], dataOutS[6], dataOutL[6], dataOutO[6], dataOutC[6]; //Saida de flits
    buffer bN, bS, bL, bO, bC; //Buffers
    roteia rN, rS, rL, rO, rC; //Roteia
    arbitro aN, aS, aL, aO, aC; //Arbitro
    mymux mN, mS, mL, mO, mC; //Mux's
    myor oN, oS, oL, oO, oC; //Or's
    sc_in<bool> enableN, enableS, enableL, enableO, enableC; //Para ativar o enable pela testbench para escrita
  
    sc_signal<bool> oNr, oSr, oLr, oOr, oCr;
    sc_signal<bool> bNo[6], bSo[6], bLo[6], bOo[6], bCo[6];
    sc_signal<bool> aNm1, aNm2, aNm3, aSm1, aSm2, aSm3, aLm1, aLm2, aLm3, aOm1, aOm2, aOm3, aCm1, aCm2, aCm3;
    sc_signal<bool> aNe1, aNe2, aNe3, aNe4, aSe1, aSe2, aSe3, aSe4, aLe1, aLe2, aLe3, aLe4, aOe1, aOe2, aOe3, aOe4, aCe1, aCe2, aCe3, aCe4;
    sc_signal<bool> mNeop, mSeop, mLeop, mOeop, mCeop;
    sc_signal<bool> rNs, rNl, rNo, rNc, rSn, rSl, rSo, rSc, rLs, rLn, rLo, rLc, rOs, rOl, rOn, rOc, rCs, rCl, rCo, rCn;
    sc_signal<bool> rNn, rSs, rLl, rOo, rCc; //Inuteis mas necessários para funcionar
    
  
    SC_CTOR(roteador): bN("BN"), bS("BS"), bL("BL"), bO("BO"), bC("BC"), rN("RN"), rS("RS"), rL("RL"), rO("RO"), rC("RC"), aN("AN"), aS("AS"), aL("AL"), aO("AO"), aC("AC"), mN("MN"), mS("MS"), mL("ML"), mO("MO"), mC("MC"), oN("ON"), oS("OS"), oL("OL"), oO("OO"), oC("OC") {
      //Associação de entradas de fios
      oN.res(oNr);
      oS.res(oSr);
      oL.res(oLr);
      oO.res(oOr);
      oC.res(oCr);
      
      for(short x = 0; x < 6; x++) {
        bN.dataOut[x](bNo[x]);
        bS.dataOut[x](bSo[x]);
        bL.dataOut[x](bLo[x]);
        bO.dataOut[x](bOo[x]);
        bC.dataOut[x](bCo[x]);
      }
      
      aN.muxMude1(aNm1);
      aN.muxMude2(aNm2);
      aN.muxMude3(aNm3);
      aS.muxMude1(aSm1);
      aS.muxMude2(aSm2);
      aS.muxMude3(aSm3);
      aL.muxMude1(aLm1);
      aL.muxMude2(aLm2);
      aL.muxMude3(aLm3);
      aO.muxMude1(aOm1);
      aO.muxMude2(aOm2);
      aO.muxMude3(aOm3);
      aC.muxMude1(aCm1);
      aC.muxMude2(aCm2);
      aC.muxMude3(aCm3);
      
      aN.env1(aNe1);
      aN.env2(aNe2);
      aN.env3(aNe3);
      aN.env4(aNe4);
      aS.env1(aSe1);
      aS.env2(aSe2);
      aS.env3(aSe3);
      aS.env4(aSe4);
      aL.env1(aLe1);
      aL.env2(aLe2);
      aL.env3(aLe3);
      aL.env4(aLe4);
      aO.env1(aOe1);
      aO.env2(aOe2);
      aO.env3(aOe3);
      aO.env4(aOe4);
      aC.env1(aCe1);
      aC.env2(aCe2);
      aC.env3(aCe3);
      aC.env4(aCe4);
      
      mN.eop(mNeop);
      mS.eop(mSeop);
      mL.eop(mLeop);
      mO.eop(mOeop);
      mC.eop(mCeop);
      
      rN.S(rNs);
      rN.L(rNl);
      rN.O(rNo);
      rN.C(rNc);
      rS.N(rSn);
      rS.L(rSl);
      rS.O(rSo);
      rS.C(rSc);
      rL.S(rLs);
      rL.N(rLn);
      rL.O(rLo);
      rL.C(rLc);
      rO.S(rOs);
      rO.L(rOl);
      rO.N(rOn);
      rO.C(rOc);
      rC.S(rCs);
      rC.L(rCl);
      rC.O(rCo);
      rC.N(rCn);
      
      //Necessários para funcionar
      rN.N(rNn);
      rS.S(rSs);
      rL.L(rLl);
      rO.O(rOo);
      rC.C(rCc);
      
      //Norte
      bN.enable(enableN);
      bN.send(oNr); //recebe a sinalização para enviar da porta de saída or associada a ele
      //Recebe flits pelo norte
      for(short x = 0; x < 6; x++) {
        bN.dataIn1[x](dataInN1[x]);
        bN.dataIn2[x](dataInN2[x]);
        bN.dataIn3[x](dataInN3[x]);
        bN.dataIn4[x](dataInN4[x]);
        bN.dataIn5[x](dataInN5[x]);
        bN.dataIn6[x](dataInN6[x]);
        bN.dataIn7[x](dataInN7[x]);
        bN.dataIn8[x](dataInN8[x]);
      }
      
      for(short x = 0; x < 6; x++) {
        rN.dataIn[x](bNo[x]);//Recebe flits para saber se é cabeçalho e para onde vai
      }
      rN.clk(clk);
      
      //Recebe o seletor do árbitro norte
      mN.X1(aNm1);
      mN.X2(aNm2);
      mN.X3(aNm3);
      for(short x = 0; x < 6; x++) {
        mN.A[x](bSo[x]);//Recebe flits do buffer sul
        mN.B[x](bLo[x]);//Recebe flits do buffer leste
        mN.C[x](bOo[x]);//Recebe flits do buffer oeste
        mN.D[x](bCo[x]);//Recebe flits do buffer central
        mN.res[x](dataOutN[x]);//Saída dos flits pelo mux norte
      }
      
      oN.A(aSe1);//Recebe sinal para ler arquivos no buffer norte do árbitro sul
      oN.B(aLe1);//Recebe sinal para ler arquivos no buffer norte do árbitro leste
      oN.C(aOe1);//Recebe sinal para ler arquivos no buffer norte do árbitro oeste
      oN.D(aCe1);//Recebe sinal para ler arquivos no buffer norte do árbitro central
      
      aN.clk(clk);
      aN.eop(mNeop);//Recebe o fim de pacote pelo mux
      //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
      aN.reqIn1(rSn); //Recebe requisição do sul
      aN.reqIn2(rLn); //Recebe requisição do leste
      aN.reqIn3(rOn); //Recebe requisição do oeste
      aN.reqIn4(rCn); //Recebe requisição do centro
      
      //Sul
      bS.enable(enableS);
      bS.send(oSr); //recebe a sinalização para enviar da porta de saída or associada a ele
      //Recebe flits pelo sul
      for(short x = 0; x < 6; x++) {
        bS.dataIn1[x](dataInS1[x]);
        bS.dataIn2[x](dataInS2[x]);
        bS.dataIn3[x](dataInS3[x]);
        bS.dataIn4[x](dataInS4[x]);
        bS.dataIn5[x](dataInS5[x]);
        bS.dataIn6[x](dataInS6[x]);
        bS.dataIn7[x](dataInS7[x]);
        bS.dataIn8[x](dataInS8[x]);
      }
      
      for(short x = 0; x < 6; x++) {
        rS.dataIn[x](bSo[x]);//Recebe flits para saber se é cabeçalho e para onde vai
      }
      rS.clk(clk);
      
      //Recebe o seletor do árbitro sul
      mS.X1(aSm1);
      mS.X2(aSm2);
      mS.X3(aSm3);
      for(short x = 0; x < 6; x++) {
        mS.A[x](bNo[x]);//Recebe flits do buffer norte
        mS.B[x](bLo[x]);//Recebe flits do buffer leste
        mS.C[x](bOo[x]);//Recebe flits do buffer oeste
        mS.D[x](bCo[x]);//Recebe flits do buffer central
        mS.res[x](dataOutS[x]);//Saída dos flits pelo mux sul
      }
      
      oS.A(aNe1);//Recebe sinal para ler arquivos no buffer sul do árbitro norte
      oS.B(aLe2);//Recebe sinal para ler arquivos no buffer sul do árbitro leste
      oS.C(aOe2);//Recebe sinal para ler arquivos no buffer sul do árbitro oeste
      oS.D(aCe2);//Recebe sinal para ler arquivos no buffer sul do árbitro central
      
      aS.clk(clk);
      aS.eop(mSeop);//Recebe o fim de pacote pelo mux
      //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
      aS.reqIn1(rNs); //Recebe requisição do norte
      aS.reqIn2(rLs); //Recebe requisição do leste
      aS.reqIn3(rOs); //Recebe requisição do oeste
      aS.reqIn4(rCs); //Recebe requisição do centro
      
      //Leste
      bL.enable(enableL);
      bL.send(oLr); //recebe a sinalização para enviar da porta de saída or associada a ele
      //Recebe flits pelo leste
      for(short x = 0; x < 6; x++) {
        bL.dataIn1[x](dataInL1[x]);
        bL.dataIn2[x](dataInL2[x]);
        bL.dataIn3[x](dataInL3[x]);
        bL.dataIn4[x](dataInL4[x]);
        bL.dataIn5[x](dataInL5[x]);
        bL.dataIn6[x](dataInL6[x]);
        bL.dataIn7[x](dataInL7[x]);
        bL.dataIn8[x](dataInL8[x]);
      }
      
      for(short x = 0; x < 6; x++) {
        rL.dataIn[x](bLo[x]);//Recebe flits para saber se é cabeçalho e para onde vai
      }
      rL.clk(clk);
      
      //Recebe o seletor do árbitro leste
      mL.X1(aLm1);
      mL.X2(aLm2);
      mL.X3(aLm3);
      for (short x = 0; x < 6; x++){
        mL.A[x](bNo[x]);//Recebe flits do buffer norte
        mL.B[x](bSo[x]);//Recebe flits do buffer sul
        mL.C[x](bOo[x]);//Recebe flits do buffer oeste
        mL.D[x](bCo[x]);//Recebe flits do buffer central
      	mL.res[x](dataOutL[x]);//Saída dos flits pelo mux leste
      }
      
      oL.A(aNe2);//Recebe sinal para ler arquivos no buffer leste do árbitro norte
      oL.B(aSe2);//Recebe sinal para ler arquivos no buffer leste do árbitro sul
      oL.C(aOe3);//Recebe sinal para ler arquivos no buffer leste do árbitro oeste
      oL.D(aCe3);//Recebe sinal para ler arquivos no buffer leste do árbitro central
      
      aL.clk(clk);
      aL.eop(mLeop);//Recebe o fim de pacote pelo mux
      //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
      aL.reqIn1(rNl); //Recebe requisição do norte
      aL.reqIn2(rSl); //Recebe requisição do sul
      aL.reqIn3(rOl); //Recebe requisição do oeste
      aL.reqIn4(rCl); //Recebe requisição do centro
      
      //Oeste
      bO.enable(enableO);
      bO.send(oOr); //recebe a sinalização para enviar da porta de saída or associada a ele
      //Recebe flits pelo oeste
      for(short x = 0; x < 6; x++) {
        bO.dataIn1[x](dataInO1[x]);
        bO.dataIn2[x](dataInO2[x]);
        bO.dataIn3[x](dataInO3[x]);
        bO.dataIn4[x](dataInO4[x]);
        bO.dataIn5[x](dataInO5[x]);
        bO.dataIn6[x](dataInO6[x]);
        bO.dataIn7[x](dataInO7[x]);
        bO.dataIn8[x](dataInO8[x]);
      }
      
      for(short x = 0; x < 6; x++) {
        rO.dataIn[x](bOo[x]);//Recebe flits para saber se é cabeçalho e para onde vai
      }
      rO.clk(clk);
      
      //Recebe o seletor do árbitro oeste
      mO.X1(aOm1);
      mO.X2(aOm2);
      mO.X3(aOm3);
      for (short x = 0; x < 6; x++){
        mO.A[x](bNo[x]);//Recebe flits do buffer norte
        mO.B[x](bSo[x]);//Recebe flits do buffer sul
        mO.C[x](bLo[x]);//Recebe flits do buffer leste
        mO.D[x](bCo[x]);//Recebe flits do buffer central
        mO.res[x](dataOutO[x]);//Saída dos flits pelo mux oeste
      }
      
      oO.A(aNe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro norte
      oO.B(aSe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro sul
      oO.C(aLe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro oeste
      oO.D(aCe4);//Recebe sinal para ler arquivos no buffer oeste do árbitro central
      
      aO.clk(clk);
      aO.eop(mOeop);//Recebe o fim de pacote pelo mux
      //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
      aO.reqIn1(rNo); //Recebe requisição do norte
      aO.reqIn2(rSo); //Recebe requisição do sul
      aO.reqIn3(rLo); //Recebe requisição do leste
      aO.reqIn4(rCo); //Recebe requisição do centro
      
      //Centro
      bC.enable(enableC);
      bC.send(oCr); //recebe a sinalização para enviar da porta de saída or associada a ele
      //Recebe flits pelo centro
      for(short x = 0; x < 6; x++) {
        bC.dataIn1[x](dataInC1[x]);
        bC.dataIn2[x](dataInC2[x]);
        bC.dataIn3[x](dataInC3[x]);
        bC.dataIn4[x](dataInC4[x]);
        bC.dataIn5[x](dataInC5[x]);
        bC.dataIn6[x](dataInC6[x]);
        bC.dataIn7[x](dataInC7[x]);
        bC.dataIn8[x](dataInC8[x]);
      }
      
      for(short x = 0; x < 6; x++) {
        rC.dataIn[x](bCo[x]);//Recebe flits para saber se é cabeçalho e para onde vai
      }
      rC.clk(clk);
      
      //Recebe o seletor do árbitro central
      mC.X1(aCm1);
      mC.X2(aCm2);
      mC.X3(aCm3);
      for (short x = 0; x < 6; x++){
        mC.A[x](bNo[x]);//Recebe flits do buffer norte
        mC.B[x](bSo[x]);//Recebe flits do buffer sul
        mC.C[x](bLo[x]);//Recebe flits do buffer leste
        mC.D[x](bOo[x]);//Recebe flits do buffer oeste
        mC.res[x](dataOutC[x]);//Saída dos flits pelo mux central
      }
      
      oC.A(aNe4);//Recebe sinal para ler arquivos no buffer central do árbitro norte
      oC.B(aSe4);//Recebe sinal para ler arquivos no buffer central do árbitro sul
      oC.C(aLe4);//Recebe sinal para ler arquivos no buffer central do árbitro leste
      oC.D(aOe4);//Recebe sinal para ler arquivos no buffer central do árbitro oeste
      
      aC.clk(clk);
      aC.eop(mCeop);//Recebe o fim de pacote pelo mux
      //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
      aC.reqIn1(rNc); //Recebe requisição do norte
      aC.reqIn2(rSc); //Recebe requisição do sul
      aC.reqIn3(rLc); //Recebe requisição do leste
      aC.reqIn4(rOc); //Recebe requisição do oeste
     
      bN.clk(clk);
      bS.clk(clk);
      bL.clk(clk);
      bO.clk(clk);
      bC.clk(clk);
      
      mN.clk(clk);
      mS.clk(clk);
      mL.clk(clk);
      mO.clk(clk);
      mC.clk(clk);
      
      //Sensibilidade
      sensitive << clk;
    }
};