#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

#include <iostream>
#include <string>
#include <algorithm>

enum Cor { VERMELHO, PRETO };

struct NoRN {
  int chave;
  Cor cor;
  NoRN* esq;
  NoRN* dir;
  NoRN* pai;

  NoRN(int val, Cor c = VERMELHO, NoRN* nulo = nullptr) 
      : chave(val), cor(c), esq(nulo), dir(nulo), pai(nulo) {}
};

class ArvoreRubroNegra {
private:
  NoRN* raiz;
  NoRN* NIL; // sentinela para representar folhas nulas(pretas)

  long long totalRotacoes;
  long long totalRecoloracoes;

  void rotacaoEsquerda(NoRN* x);
  void rotacaoDireita(NoRN* y);
  void ajustarInsercao(NoRN* k);
  void ajustarRemocao(NoRN* x);
  void transplantar(NoRN* u, NoRN* v);
  NoRN* obterNoMinimo(NoRN* no);

  bool buscarRec(NoRN* no, int chave);
  void exibirEmOrdemRec(NoRN* no);
  void visualizarEstruturaRec(NoRN* no, const std::string& prefixo, bool ehEsquerda);
  int calcularAlturaRec(NoRN* no);
  void destruirArvore(NoRN* no);

public:
  ArvoreRubroNegra();
  ~ArvoreRubroNegra();

  bool inserir(int chave);
  bool remover(int chave);
  bool buscar(int chave);
  void exibirEmOrdem();
  void visualizarEstrutura();

  int getAltura();
  long long getRotacoes();
  long long getRecoloracoes();
};

#endif