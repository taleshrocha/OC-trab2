#include <systemc>

#include "buffer.h"
#include "mymux.h"
#include "arbitro.h"
#include "roteia.h"
#include "myor.h"

SC_MODULE(roteador) {
  sc_in<bool> clk;

  sc_in<FLIT> dataInD1, dataInD2, dataInD3, dataInD4, dataInD5, dataInD6, dataInD7, dataInD8;
  sc_in<FLIT> dataInE1, dataInE2, dataInE3, dataInE4, dataInE5, dataInE6, dataInE7, dataInE8;
  sc_in<FLIT> dataInF1, dataInF2, dataInF3, dataInF4, dataInF5, dataInF6, dataInF7, dataInF8;
  sc_in<FLIT> dataInL1, dataInL2, dataInL3, dataInL4, dataInL5, dataInL6, dataInL7, dataInL8;

  //Para ativar o enable pela testbench para escrita
  sc_in<bool> enableD, enableE, enableF, enableL;

  sc_out<FLIT> dataOutD, dataOutE, dataOutF, dataOutL;

  buffer bD, bE, bL, bF;
  roteia rD, rE, rL, rF;
  arbitro aD, aE, aL, aF;
  mymux mD, mE, mL, mF;
  myor oD, oE, oL, oF;

  sc_signal<bool> oDr, oEr, oLr, oFr;
  sc_signal<FLIT> bDo, bEo, bLo, bFo;
  sc_signal<bool> aDm1, aDm2, aDm3, aEm1, aEm2, aEm3, aLm1, aLm2, aLm3, aFm1, aFm2, aFm3;
  sc_signal<bool> aDe1, aDe2, aDe3, aDe4, aEe1, aEe2, aEe3, aEe4, aLe1, aLe2, aLe3, aLe4, aFe1, aFe2, aFe3, aFe4;
  sc_signal<bool> mDeop, mEeop, mLeop, mFeop;
  sc_signal<bool> rDs, rDl, rDo, rDc, rEn, rEl, rEo, rEc, rLs, rLn, rLo, rLc, rFs, rFl, rFn, rFc;

  sc_signal<bool> rDn, rEs, rLl, rFo; // Inuteis mas necessários para funcionar


  SC_CTOR(roteador)
    : bD("BD"), bE("BE"), bL("BL"), bF("BF"), rD("RD"), rE("RE"), 
    rL("RL"), rF("RF"), aD("AD"), aE("AE"), aL("AL"), aF("AF"), 
    mD("MD"), mE("ME"), mL("ML"), mF("MF"), oD("FD"), 
    oE("FE"), oL("FL"), oF("FF")
  {

    //Associação de entradas de fios
    oD.res(oDr);
    oE.res(oEr);
    oL.res(oLr);
    oF.res(oFr);

    bD.dataOut(bDo);
    bE.dataOut(bEo);
    bL.dataOut(bLo);
    bF.dataOut(bFo);

    aD.muxMude1(aDm1);
    aD.muxMude2(aDm2);
    aD.muxMude3(aDm3);
    aE.muxMude1(aEm1);
    aE.muxMude2(aEm2);
    aE.muxMude3(aEm3);
    aL.muxMude1(aLm1);
    aL.muxMude2(aLm2);
    aL.muxMude3(aLm3);
    aF.muxMude1(aFm1);
    aF.muxMude2(aFm2);
    aF.muxMude3(aFm3);

    aD.env1(aDe1);
    aD.env2(aDe2);
    aD.env3(aDe3);
    aD.env4(aDe4);
    aE.env1(aEe1);
    aE.env2(aEe2);
    aE.env3(aEe3);
    aE.env4(aEe4);
    aL.env1(aLe1);
    aL.env2(aLe2);
    aL.env3(aLe3);
    aL.env4(aLe4);
    aF.env1(aFe1);
    aF.env2(aFe2);
    aF.env3(aFe3);
    aF.env4(aFe4);

    mD.eop(mDeop);
    mE.eop(mEeop);
    mL.eop(mLeop);
    mF.eop(mFeop);

    rD.E(rDs);
    rD.L(rDl);
    rD.F(rDo);
    rE.D(rEn);
    rE.L(rEl);
    rE.F(rEo);
    rL.E(rLs);
    rL.D(rLn);
    rL.F(rLo);
    rF.E(rFs);
    rF.L(rFl);
    rF.D(rFn);

    //Decessários para funcionar
    rD.D(rDn);
    rE.E(rEs);
    rL.L(rLl);
    rF.F(rFo);

    // Direita ----------------------------------------------------------------

    bD.enable(enableD);

    //recebe a sinalização para enviar da porta de saída or associada a ele
    bD.send(oDr); 

    // Recebe flits pelo norte
    bD.dataIn1(dataInD1);
    bD.dataIn2(dataInD2);
    bD.dataIn3(dataInD3);
    bD.dataIn4(dataInD4);
    bD.dataIn5(dataInD5);
    bD.dataIn6(dataInD6);
    bD.dataIn7(dataInD7);
    bD.dataIn8(dataInD8);

    //Recebe flits para saber se é cabeçalho e para onde vai
    rD.dataIn(bDo);
    rD.clk(clk);

    //Recebe o seletor do árbitro norte
    mD.X1(aDm1);
    mD.X2(aDm2);
    mD.X3(aDm3);

    mD.A(bEo);//Recebe flits do buffer sul
    mD.B(bLo);//Recebe flits do buffer leste
    mD.C(bFo);//Recebe flits do buffer oeste
    mD.res(dataOutD);//Eaída dos flits pelo mux norte

    oD.A(aEe1);//Recebe sinal para ler arquivos no buffer norte do árbitro sul
    oD.B(aLe1);//Recebe sinal para ler arquivos no buffer norte do árbitro leste
    oD.C(aFe1);//Recebe sinal para ler arquivos no buffer norte do árbitro oeste

    aD.clk(clk);
    aD.eop(mDeop);//Recebe o fim de pacote pelo mux
    //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
    aD.reqIn1(rEn); //Recebe requisição do sul
    aD.reqIn2(rLn); //Recebe requisição do leste
    aD.reqIn3(rFn); //Recebe requisição do oeste

    // Esquerda ---------------------------------------------------------------

    bE.enable(enableE);
    bE.send(oEr); //recebe a sinaliação para enviar da porta de saída or associada a ele
    //Recebe flits pelo sul
    bE.dataIn1(dataInE1);
    bE.dataIn2(dataInE2);
    bE.dataIn3(dataInE3);
    bE.dataIn4(dataInE4);
    bE.dataIn5(dataInE5);
    bE.dataIn6(dataInE6);
    bE.dataIn7(dataInE7);
    bE.dataIn8(dataInE8);

    rE.dataIn(bEo);//Recebe flits para saber se é cabeçalho e para onde vai
    rE.clk(clk);

    //Recebe o seletor do árbitro sul
    mE.X1(aEm1);
    mE.X2(aEm2);
    mE.X3(aEm3);
    mE.A(bDo);//Recebe flits do buffer norte
    mE.B(bLo);//Recebe flits do buffer leste
    mE.C(bFo);//Recebe flits do buffer oeste
    mE.res(dataOutE);//Eaída dos flits pelo mux sul

    oE.A(aDe1);//Recebe sinal para ler arquivos no buffer sul do árbitro norte
    oE.B(aLe2);//Recebe sinal para ler arquivos no buffer sul do árbitro leste
    oE.C(aFe2);//Recebe sinal para ler arquivos no buffer sul do árbitro oeste

    aE.clk(clk);
    aE.eop(mEeop);//Recebe o fim de pacote pelo mux
    //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
    aE.reqIn1(rDs); //Recebe requisição do norte
    aE.reqIn2(rLs); //Recebe requisição do leste
    aE.reqIn3(rFs); //Recebe requisição do oeste

    // Local ------------------------------------------------------------------

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
    mL.A(bDo);//Recebe flits do buffer norte
    mL.B(bEo);//Recebe flits do buffer sul
    mL.C(bFo);//Recebe flits do buffer oeste
    mL.res(dataOutL);//Eaída dos flits pelo mux leste

    oL.A(aDe2);//Recebe sinal para ler arquivos no buffer leste do árbitro norte
    oL.B(aEe2);//Recebe sinal para ler arquivos no buffer leste do árbitro sul
    oL.C(aFe3);//Recebe sinal para ler arquivos no buffer leste do árbitro oeste

    aL.clk(clk);
    aL.eop(mLeop);//Recebe o fim de pacote pelo mux
    //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
    aL.reqIn1(rDl); //Recebe requisição do norte
    aL.reqIn2(rEl); //Recebe requisição do sul
    aL.reqIn3(rFl); //Recebe requisição do oeste

    // Frente -----------------------------------------------------------------

    bF.enable(enableF);
    bF.send(oFr); //recebe a sinalização para enviar da porta de saída or associada a ele
    //Recebe flits pelo oeste
    bF.dataIn1(dataInF1);
    bF.dataIn2(dataInF2);
    bF.dataIn3(dataInF3);
    bF.dataIn4(dataInF4);
    bF.dataIn5(dataInF5);
    bF.dataIn6(dataInF6);
    bF.dataIn7(dataInF7);
    bF.dataIn8(dataInF8);

    rF.dataIn(bFo);//Recebe flits para saber se é cabeçalho e para onde vai
    rF.clk(clk);

    //Recebe o seletor do árbitro oeste
    mF.X1(aFm1);
    mF.X2(aFm2);
    mF.X3(aFm3);
    mF.A(bDo);//Recebe flits do buffer norte
    mF.B(bEo);//Recebe flits do buffer sul
    mF.C(bLo);//Recebe flits do buffer leste
    mF.res(dataOutF);//Eaída dos flits pelo mux oeste

    oF.A(aDe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro norte
    oF.B(aEe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro sul
    oF.C(aLe3);//Recebe sinal para ler arquivos no buffer oeste do árbitro oeste

    aF.clk(clk);
    aF.eop(mFeop);//Recebe o fim de pacote pelo mux
    //Recebe as requisições das outras portas de entrada pelo fio instanciado como mostrado a seguir:
    aF.reqIn1(rDo); //Recebe requisição do norte
    aF.reqIn2(rEo); //Recebe requisição do sul
    aF.reqIn3(rLo); //Recebe requisição do leste

    bD.clk(clk);
    bE.clk(clk);
    bL.clk(clk);
    bF.clk(clk);

    mD.clk(clk);
    mE.clk(clk);
    mL.clk(clk);
    mF.clk(clk);

    sensitive << clk;
  }
};
