#include "avl.h"

using namespace std;

ArvoreAVL::ArvoreAVL() : raiz(nullptr), totalRotacoes(0) {}

ArvoreAVL::~ArvoreAVL() {
  destruirArvore(raiz);
}

void ArvoreAVL::destruirArvore(NoAVL* no) {
  if (no != nullptr) {
    destruirArvore(no->esq);
    destruirArvore(no->dir);
    delete no;
  }
}

int ArvoreAVL::obtermAltura(NoAVL* no) {
  return (no == nullptr) ? 0 : no->altura;
}

int ArvoreAVL::obterFatorBalanceamento(NoAVL* no) {
  return (no == nullptr) ? 0 : obtermAltura(no->esq) - obtermAltura(no->dir);
}

void ArvoreAVL::atualizarAltura(NoAVL* no) {
  if (no != nullptr) {
    no->altura = 1 + max(obtermAltura(no->esq), obtermAltura(no->dir));
  }
}

// rotação simples a direita
NoAVL* ArvoreAVL::rotacaoDireita(NoAVL* y) {
  NoAVL* x = y->esq;
  NoAVL* T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  atualizarAltura(y);
  atualizarAltura(x);

  totalRotacoes++;
  return x;
}

// rotação simples a esquerda
NoAVL* ArvoreAVL::rotacaoEsquerda(NoAVL* x) {
  NoAVL* y = x->dir;
  NoAVL* T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  atualizarAltura(x);
  atualizarAltura(y);

  totalRotacoes++;
  return y;
}

// inserção com rebalanceamento
bool ArvoreAVL::inserir(int chave) {
  bool inserido = false;
  raiz = inserirRec(raiz, chave, inserido);
  return inserido;
}

NoAVL* ArvoreAVL::inserirRec(NoAVL* no, int chave, bool& inserido) {
  if (no == nullptr) {
    inserido = true;
    return new NoAVL(chave);
  }

  if (chave < no->chave) {
    no->esq = inserirRec(no->esq, chave, inserido);
  } else if (chave > no->chave) {
    no->dir = inserirRec(no->dir, chave, inserido);
  } else {
    // se achou chave duplicada 
    inserido = false;
    return no;
  }

  atualizarAltura(no);
  int fb = obterFatorBalanceamento(no);

  // casos de desbalanceamento:

  // esquerda-esquerda
  if (fb > 1 && chave < no->esq->chave) {
    return rotacaoDireita(no);
  }

  // direita-direita
  if (fb < -1 && chave > no->dir->chave) {
    return rotacaoEsquerda(no);
  }

  // esquerda-direita
  if (fb > 1 && chave > no->esq->chave) {
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
  }

  // direita-esquerda
  if (fb < -1 && chave < no->dir->chave) {
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
  }

  return no;
}

NoAVL* ArvoreAVL::obterNoMinimo(NoAVL* no) {
  NoAVL* atual = no;

  while (atual->esq != nullptr) {
    atual = atual->esq;
  }
  
  return atual;
}

// remoção com rebalanceamento
bool ArvoreAVL::remover(int chave) {
  bool removido = false;
  raiz = removerRec(raiz, chave, removido);
  return removido;
}

NoAVL* ArvoreAVL::removerRec(NoAVL* no, int chave, bool& removido) {
  if (no == nullptr) {
    removido = false;
    return nullptr;
  }

  if (chave < no->chave) {
    no->esq = removerRec(no->esq, chave, removido);
  } else if (chave > no->chave) {
    no->dir = removerRec(no->dir, chave, removido);
  } else {
    removido = true;

    if ((no->esq == nullptr) || (no->dir == nullptr)) {
      NoAVL* temp = no->esq ? no->esq : no->dir;

      if (temp == nullptr) {
        temp = no;
        no = nullptr;
      } else {
        *no = *temp;
      }

      delete temp;
    } else {
      NoAVL* temp = obterNoMinimo(no->dir);
      no->chave = temp->chave;
      no->dir = removerRec(no->dir, temp->chave, removido);
    }
  }

  if (no == nullptr) return nullptr;

  atualizarAltura(no);
  int fb = obterFatorBalanceamento(no);

  // rebalanceamento após remoção

  // esquerda-esquerda
  if (fb > 1 && obterFatorBalanceamento(no->esq) >= 0) {
    return rotacaoDireita(no);
  }

  // esquerda-direita
  if (fb > 1 && obterFatorBalanceamento(no->esq) < 0) {
    no->esq = rotacaoEsquerda(no->esq);
    return rotacaoDireita(no);
  }

  // direita-direita
  if (fb < -1 && obterFatorBalanceamento(no->dir) <= 0) {
    return rotacaoEsquerda(no);
  }

  // direita-esquerda
  if (fb < -1 && obterFatorBalanceamento(no->dir) > 0) {
    no->dir = rotacaoDireita(no->dir);
    return rotacaoEsquerda(no);
  }

  return no;
}

bool ArvoreAVL::buscar(int chave) {
  return buscarRec(raiz, chave);
}

bool ArvoreAVL::buscarRec(NoAVL* no, int chave) {
  if (no == nullptr) return false;
  if (chave == no->chave) return true;
  if (chave < no->chave) return buscarRec(no->esq, chave);
  return buscarRec(no->dir, chave);
}

void ArvoreAVL::exibirEmOrdem() {
  exibirEmOrdemRec(raiz);
}

void ArvoreAVL::exibirEmOrdemRec(NoAVL* no) {
  if (no != nullptr) {
    exibirEmOrdemRec(no->esq);
    cout << no->chave << " ";
    exibirEmOrdemRec(no->dir);
  }
}

void ArvoreAVL::visualizarEstrutura() {
  if (raiz == nullptr) {
    cout << "[Arvore Vazia]\n";
    return;
  }

  visualizarEstruturaRec(raiz, "", false);
}

void ArvoreAVL::visualizarEstruturaRec(NoAVL* no, const string& prefixo, bool ehEsquerda) {
  if (no != nullptr) {
    cout << prefixo;
    cout << (ehEsquerda ? "├──" : "└──");
    cout << "[" << no->chave << "] (h=" << no->altura << ")\n";

    visualizarEstruturaRec(no->esq, prefixo + (ehEsquerda ? "│   " : "    "), true);
    visualizarEstruturaRec(no->dir, prefixo + (ehEsquerda ? "│   " : "    "), false);
  }
}

int ArvoreAVL::getAltura() {
  return obtermAltura(raiz);
}

long long ArvoreAVL::getRotacoes() {
  return totalRotacoes;
}