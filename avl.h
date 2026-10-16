#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <algorithm>
#include <string>

// estrutura do nós da Árvore AVL
struct NoAVL {
  int chave;
  int altura;
  NoAVL* esq;
  NoAVL* dir;

  NoAVL(int val) : chave(val), altura(1), esq(nullptr), dir(nullptr) {}
};

class ArvoreAVL {
private:
  NoAVL* raiz;
  long long totalRotacoes; // contador de rotacões

  int obtermAltura(NoAVL* no);
  int obterFatorBalanceamento(NoAVL* no);
  void atualizarAltura(NoAVL* no);

  NoAVL* rotacaoDireita(NoAVL* y);
  NoAVL* rotacaoEsquerda(NoAVL* x);

  NoAVL* inserirRec(NoAVL* no, int chave, bool& inserido);
  NoAVL* removerRec(NoAVL* no, int chave, bool& removido);
  NoAVL* obterNoMinimo(NoAVL* no);
  bool buscarRec(NoAVL* no, int chave);
  
  void exibirEmOrdemRec(NoAVL* no);
  void visualizarEstruturaRec(NoAVL* no, const std::string& prefixo, bool ehEsquerda);
  void destruirArvore(NoAVL* no);

public:
  ArvoreAVL();
  ~ArvoreAVL();

  bool inserir(int chave);
  bool remover(int chave);
  bool buscar(int chave);
  void exibirEmOrdem();
  void visualizarEstrutura();

  int getAltura();
  long long getRotacoes();
};

#endif 