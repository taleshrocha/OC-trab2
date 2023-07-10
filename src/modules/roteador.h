#include <systemc>

#include "buffer.h"
#include "mymux.h"
#include "arbitro.h"
#include "roteia.h"
#include "myor.h"

SC_MODULE(roteador) {
  sc_in<bool> clk;

  sc_in<FLIT> dataInN1, dataInN2, dataInN3, dataInN4, dataInN5, dataInN6, dataInN7, dataInN8;
  sc_in<FLIT> dataInS1, dataInS2, dataInS3, dataInS4, dataInS5, dataInS6, dataInS7, dataInS8;
  sc_in<FLIT> dataInL1, dataInL2, dataInL3, dataInL4, dataInL5, dataInL6, dataInL7, dataInL8;
  sc_in<FLIT> dataInO1, dataInO2, dataInO3, dataInO4, dataInO5, dataInO6, dataInO7, dataInO8;
  sc_in<FLIT> dataInC1, dataInC2, dataInC3, dataInC4, dataInC5, dataInC6, dataInC7, dataInC8;

  //Para ativar o enable pela testbench para escrita
  sc_in<bool> enableN, enableS, enableL, enableO, enableC; 

  sc_out<FLIT> dataOutN, dataOutS, dataOutL, dataOutO, dataOutC;

  buffer bN, bS, bL, bO, bC;
  roteia rN, rS, rL, rO, rC;
  arbitro aN, aS, aL, aO, aC;
  mymux mN, mS, mL, mO, mC;
  myor oN, oS, oL, oO, oC;

  sc_signal<bool> oNr, oSr, oLr, oOr, oCr;
  sc_signal<FLIT> bNo, bSo, bLo, bOo, bCo;
  sc_signal<bool> aNm1, aNm2, aNm3, aSm1, aSm2, aSm3, aLm1, aLm2, aLm3, aOm1, aOm2, aOm3, aCm1, aCm2, aCm3;
  sc_signal<bool> aNe1, aNe2, aNe3, aNe4, aSe1, aSe2, aSe3, aSe4, aLe1, aLe2, aLe3, aLe4, aOe1, aOe2, aOe3, aOe4, aCe1, aCe2, aCe3, aCe4;
  sc_signal<bool> mNeop, mSeop, mLeop, mOeop, mCeop;
  sc_signal<bool> rNs, rNl, rNo, rNc, rSn, rSl, rSo, rSc, rLs, rLn, rLo, rLc, rOs, rOl, rOn, rOc, rCs, rCl, rCo, rCn;

  sc_signal<bool> rNn, rSs, rLl, rOo, rCc; // Inuteis mas necessários para funcionar


  SC_CTOR(roteador)
    : bN("BN"), bS("BS"), bL("BL"), bO("BO"), bC("BC"), rN("RN"), rS("RS"), 
    rL("RL"), rO("RO"), rC("RC"), aN("AN"), aS("AS"), aL("AL"), aO("AO"), 
    aC("AC"), mN("MN"), mS("MS"), mL("ML"), mO("MO"), mC("MC"), oN("ON"), 
    oS("OS"), oL("OL"), oO("OO"), oC("OC") 
  {

    //Associação de entradas de fios
    oN.res(oNr);
    oS.res(oSr);
    oL.res(oLr);
    oO.res(oOr);
    oC.res(oCr);

    bN.dataOut(bNo);
    bS.dataOut(bSo);
    bL.dataOut(bLo);
    bO.dataOut(bOo);
    bC.dataOut(bCo);

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

    // Norte ------------------------------------------------------------------
    bN.enable(enableN);

    //recebe a sinalização para enviar da porta de saída or associada a ele
    bN.send(oNr); 

    // Recebe flits pelo norte
    bN.dataIn1(dataInN1);
    bN.dataIn2(dataInN2);
    bN.dataIn3(dataInN3);
    bN.dataIn4(dataInN4);
    bN.dataIn5(dataInN5);
    bN.dataIn6(dataInN6);
    bN.dataIn7(dataInN7);
    bN.dataIn8(dataInN8);

    //Recebe flits para saber se é cabeçalho e para onde vai
    rN.dataIn(bNo);
    rN.clk(clk);

    //Recebe o seletor do árbitro norte
    mN.X1(aNm1);
    mN.X2(aNm2);
    mN.X3(aNm3);

    mN.A(bSo);//Recebe flits do buffer sul
    mN.B(bLo);//Recebe flits do buffer leste
    mN.C(bOo);//Recebe flits do buffer oeste
    mN.D(bCo);//Recebe flits do buffer central
    mN.res(dataOutN);//Saída dos flits pelo mux norte

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
    bS.send(oSr); //recebe a sinaliação para enviar da porta de saída or associada a ele
    //Recebe flits pelo sul
    bS.dataIn1(dataInS1);
    bS.dataIn2(dataInS2);
    bS.dataIn3(dataInS3);
    bS.dataIn4(dataInS4);
    bS.dataIn5(dataInS5);
    bS.dataIn6(dataInS6);
    bS.dataIn7(dataInS7);
    bS.dataIn8(dataInS8);

    rS.dataIn(bSo);//Recebe flits para saber se é cabeçalho e para onde vai
    rS.clk(clk);

    //Recebe o seletor do árbitro sul
    mS.X1(aSm1);
    mS.X2(aSm2);
    mS.X3(aSm3);
    mS.A(bNo);//Recebe flits do buffer norte
    mS.B(bLo);//Recebe flits do buffer leste
    mS.C(bOo);//Recebe flits do buffer oeste
    mS.D(bCo);//Recebe flits do buffer central
    mS.res(dataOutS);//Saída dos flits pelo mux sul

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
    bL.dataIn1(dataInL1);
    bL.dataIn2(dataInL2);
    bL.dataIn3(dataInL3);
    bL.dataIn4(dataInL4);
    bL.dataIn5(dataInL5);
    bL.dataIn6(dataInL6);
    bL.dataIn7(dataInL7);
    bL.dataIn8(dataInL8);

    rL.dataIn(bLo);//Recebe flits para saber se é cabeçalho e para onde vai
    rL.clk(clk);

    //Recebe o seletor do árbitro leste
    mL.X1(aLm1);
    mL.X2(aLm2);
    mL.X3(aLm3);
    mL.A(bNo);//Recebe flits do buffer norte
    mL.B(bSo);//Recebe flits do buffer sul
    mL.C(bOo);//Recebe flits do buffer oeste
    mL.D(bCo);//Recebe flits do buffer central
    mL.res(dataOutL);//Saída dos flits pelo mux leste

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
    bO.dataIn1(dataInO1);
    bO.dataIn2(dataInO2);
    bO.dataIn3(dataInO3);
    bO.dataIn4(dataInO4);
    bO.dataIn5(dataInO5);
    bO.dataIn6(dataInO6);
    bO.dataIn7(dataInO7);
    bO.dataIn8(dataInO8);

    rO.dataIn(bOo);//Recebe flits para saber se é cabeçalho e para onde vai
    rO.clk(clk);

    //Recebe o seletor do árbitro oeste
    mO.X1(aOm1);
    mO.X2(aOm2);
    mO.X3(aOm3);
    mO.A(bNo);//Recebe flits do buffer norte
    mO.B(bSo);//Recebe flits do buffer sul
    mO.C(bLo);//Recebe flits do buffer leste
    mO.D(bCo);//Recebe flits do buffer central
    mO.res(dataOutO);//Saída dos flits pelo mux oeste

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
    bC.dataIn1(dataInC1);
    bC.dataIn2(dataInC2);
    bC.dataIn3(dataInC3);
    bC.dataIn4(dataInC4);
    bC.dataIn5(dataInC5);
    bC.dataIn6(dataInC6);
    bC.dataIn7(dataInC7);
    bC.dataIn8(dataInC8);

    rC.dataIn(bCo);//Recebe flits para saber se é cabeçalho e para onde vai
    rC.clk(clk);

    //Recebe o seletor do árbitro central
    mC.X1(aCm1);
    mC.X2(aCm2);
    mC.X3(aCm3);
    mC.A(bNo);//Recebe flits do buffer norte
    mC.B(bSo);//Recebe flits do buffer sul
    mC.C(bLo);//Recebe flits do buffer leste
    mC.D(bOo);//Recebe flits do buffer oeste
    mC.res(dataOutC);//Saída dos flits pelo mux central

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

    sensitive << clk;
  }
};
