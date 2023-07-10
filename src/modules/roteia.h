//Requisita ao árbitro a saida do pacote pela porta necessária, checando ao requisitar a porta para ser enviada
//Façamos o Xdir/Ydir do seguinte modo:
//Xdir |  0  | 1
//     | Oes | Les
//Ydir |  0  | 1
//     | Sul | Nor
//Sem estado
//Verifica se é um flit de cabeçalho, e se é, calcula a rota mandando para o arbitro

#include "systemc.h"
#include <iostream>
#include <bitset>

SC_MODULE(roteia) {
  sc_in<bool> clk;

  //Recebe o flit pra verificar se cabeçalho
  sc_in<FLIT> dataIn; 

   //Manda a requisição necessária para o arbitro correto
  sc_out<bool> L, O, N, S, C;
  
  void do_roteia(){
    FLIT dataInAux = dataIn.read();

    //Para guardar o local que vai obter a requisição
    bool req[5] = {false, false, false, false, false};
    
    if(dataInAux[5]) { //Se for um cabeçalho, ou seja, idp = 1
      if(dataInAux[2]) { //Se 3º bit, Xval = 1, então vamos mandar para algum lugar: L/O
        if(dataInAux[3]) { //Se 4º bit, Xdir = 1, requisitemos o Leste
          req[2] = true;
        } else { //Se não, requisitemos o Oeste
          req[3] = true;
        }
      } else {//Xval = 0
        if(dataInAux[0]) { //Se 1º bit, Yval = 1, então vamos mandar para algum lugar: N/S
          if(dataInAux[1]) { //Se 2º bit, Ydir = 1, requisitemos o Norte
          	req[0] = true;
          } else { //Se não, requisitemos o Sul
          	req[1] = true;
          }
        } else { //Yval = 0, então encontramos o roteador destino, envie para a porta local/central
          req[4] = true;
        }
      }
    }
    N.write(req[0]);
    S.write(req[1]);
    L.write(req[2]);
    O.write(req[3]);
    C.write(req[4]);
  }
  
  SC_CTOR(roteia) 
  : clk("clk"), dataIn("dataIn"), L("L"), O("O"), N("N"), S("S"), C("C")
  {
    SC_METHOD(do_roteia);
    sensitive << clk;
  }
  
};
