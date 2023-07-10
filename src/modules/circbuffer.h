//Guarda os flits para envio do pacote, deverá ter espaço para 8 flits onde só guarda os pacotes quando ativado (enable) e envia pacotes quando recebe o sinal (send)
#include "systemc.h"
#include <utility>
#include <iostream>

SC_MODULE(circbuffer) {
  sc_in<bool> clk;
  sc_in<bool> advance; //Receba do árbitro o comando para avançar para a próxima posição no buffer circular
  sc_in<bool> reqIn1, reqIn2, reqIn3; //requisições dos "roteia" instanciados das 4 direções
  sc_out<bool> reqOut; //Avisa para o árbitro se há uma requisição nessa posição atual
  sc_out<short> posOut; //Valor do ponteiro/posição atual para uso do árbitro
  
  
  bool reqs[4] = {false, false, false, false}; //Guarda as requisições dos algoritmos de roteiamento, inicialmente sem requisições
  short pont = 0;
  
  void do_circbuffer() {
    
    if(advance.read()) {
      //Avança o ponteiro para a próxima posição
      if(pont == 3) {
        pont = 0;
      } else {
        pont = pont + 1;
      }
    
      //Lê as requisições dos algoritmos de roteamento atuais
      reqs[0] = reqIn1.read();
      reqs[1] = reqIn2.read();
      reqs[2] = reqIn3.read();
    }
    
    //Envia a posição
    posOut.write(pont);
    reqOut.write(reqs[pont]);
  }
  
  SC_CTOR(circbuffer) 
  : advance("adv"), reqIn1("rI1"), reqIn2("rI2"), reqIn3("rI3"), 
    reqOut("rO"), posOut("pO") {
    SC_METHOD(do_circbuffer);
    sensitive << clk.pos();
  }
};
