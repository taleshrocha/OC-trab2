//Decide de onde vem o pacote, recebendo o fdp do buffer atual, tal qual a requisição de qual buffer vai ser enviado pelo roteia, dado a requisição, ele se mantém com o mux naquele caminho(buffer) até receber o fdp(1)(diretamente do buffer, fio unico do bit), prosseguindo com o round-robin ao receber-lo

//Dividido em duas partes:
//Parte operativa: buffer circular do round-robin(que recebe dos 4 roteia(controle de saída dos buffers) requisições para uso do árbitro e guarda elas no buffer na posição indicada)
//Parte de controle: recebe um bit de término de pacote do multiplexador para prosseguir com execução dos próximos valores no buffer round-robin enviando-o para prosseguir e recebe do round-robin um bit mandando-o parar quando o bit naquela posição for 1(requisitado envio naquela porta) e envia para o buffer determinado o "send" para poder receber os pacotes dele, além de mudar os 3 bits de 1xx para 0xx indicando o novo xx(caminho do multiplexador) para receber

#include "systemc.h"
#include <utility>
#include <iostream>
#include "circbuffer.h"

SC_MODULE(arbitro) {
  sc_in<bool> clk; //Clock para funcionamento do árbitro
  sc_in<bool> eop; //Bit que o árbitro recebe do buffer para checar caso haja algum pacote passando por ele, sendo ele o fdp para terminar o envio do pacote
  sc_in<bool> reqIn1, reqIn2, reqIn3; //Requisições do algoritmo de roteamento, colocadas no buffer circular
  sc_in<bool> envArq; //Serve para indicar quando está ativo/recebendo arquivos pela saída que gerencia
  sc_in<short> posMux; //Serve para guiar o árbitro para setar o muxMud para a posição correta e dar ao buffer certo o sinal de ler pacote
  sc_out<bool> env1, env2, env3, env4; //Bit que avisa quando ativar a leitura do buffer para os buffers
  sc_out<bool> muxMude1, muxMude2, muxMude3; //Indica ao mux qual caminho deve ser usado para desvio de pacote, também podendo usar o caminho "vazio" para que o mux não receba/desvie acidentalmente pacote algum para sua saída associada
  sc_out<bool> avn; //Manda avançar para a próxima posição  

  circbuffer cb;//Buffer circular(Parte operativa do árbitro)

  sc_signal<short> pM;
  sc_signal<bool> av, eA;

  void do_arbitro() {

    if(envArq.read() == 1) { //Se houver requisições para enviar um pacote
      cout<<"tem que ler agora!!! na pos: "<<posMux.read()<<endl;
      avn.write(0); //Desative o avanço
      if(posMux.read() == 0) {//Envie para o ligado a primeira posição
        env1.write(true);
        muxMude1.write(false);
        muxMude2.write(false);
        muxMude3.write(false);
      } else if(posMux.read() == 1) {//Envie para o ligado a segunda posição
        env2.write(true);
        muxMude1.write(false);
        muxMude2.write(false);
        muxMude3.write(true);
      } else if(posMux.read() == 2) {//Envie para o ligado a terceira posição
        env3.write(true);
        muxMude1.write(false);
        muxMude2.write(true);
        muxMude3.write(false);
      } else if(posMux.read() == 3) {//Envie para o ligado a quarta posição
        env4.write(true);
        muxMude1.write(false);
        muxMude2.write(true);
        muxMude3.write(true);
      }
    } else { //Se não
      avn.write(1); //Avance
      env1.write(false);
      env2.write(false);
      env3.write(false);
      env4.write(false);
      muxMude1.write(true);
      muxMude2.write(false);
      muxMude3.write(false);
    }

    if(eop.read()) {//Chega no final de um pacote
      cout<<"reativa o avn"<<endl;
      avn.write(true); //Reativa o avançador de pacote
    }
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
