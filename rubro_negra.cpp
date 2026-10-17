#include "rubro_negra.h"

using namespace std;

// códigos ANSI para colorir no terminal
#define COR_VERMELHO "\033[1;31m"
#define COR_RESET    "\033[0m"

ArvoreRubroNegra::ArvoreRubroNegra() : totalRotacoes(0), totalRecoloracoes(0) {
  NIL = new NoRN(0, PRETO);
  NIL->esq = NIL;
  NIL->dir = NIL;
  NIL->pai = NIL;
  raiz = NIL;
}

ArvoreRubroNegra::~ArvoreRubroNegra() {
  destruirArvore(raiz);
  delete NIL;
}

void ArvoreRubroNegra::destruirArvore(NoRN* no) {
  if (no != NIL) {
    destruirArvore(no->esq);
    destruirArvore(no->dir);
    delete no;
  }
}

void ArvoreRubroNegra::rotacaoEsquerda(NoRN* x) {
  NoRN* y = x->dir;
  x->dir = y->esq;

  if (y->esq != NIL) {
      y->esq->pai = x;
  }

  y->pai = x->pai;

  if (x->pai == NIL) {
      raiz = y;
  } else if (x == x->pai->esq) {
      x->pai->esq = y;
  } else {
      x->pai->dir = y;
  }

  y->esq = x;
  x->pai = y;

  totalRotacoes++;
}

void ArvoreRubroNegra::rotacaoDireita(NoRN* y) {
  NoRN* x = y->esq;
  y->esq = x->dir;

  if (x->dir != NIL) {
    x->dir->pai = y;
  }

  x->pai = y->pai;

  if (y->pai == NIL) {
    raiz = x;
  } else if (y == y->pai->dir) {
    y->pai->dir = x;
  } else {
    y->pai->esq = x;
  }

  x->dir = y;
  y->pai = x;

  totalRotacoes++;
}

bool ArvoreRubroNegra::inserir(int chave) {
  if (buscar(chave)) {
    return false; 
  }

  NoRN* z = new NoRN(chave, VERMELHO, NIL);
  NoRN* y = NIL;
  NoRN* x = raiz;

  while (x != NIL) {
    y = x;
    if (z->chave < x->chave) {
      x = x->esq;
    } else {
      x = x->dir;
    }
  }

  z->pai = y;

  if (y == NIL) {
    raiz = z;
  } else if (z->chave < y->chave) {
    y->esq = z;
  } else {
    y->dir = z;
  }

  ajustarInsercao(z);
  return true;
}

void ArvoreRubroNegra::ajustarInsercao(NoRN* k) {
  NoRN* tio;
  while (k->pai->cor == VERMELHO) {
    if (k->pai == k->pai->pai->esq) {
      tio = k->pai->pai->dir;

      // o tio eh vermelho -> recoloração
      if (tio->cor == VERMELHO) {
        k->pai->cor = PRETO;
        tio->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        totalRecoloracoes += 3;
        k = k->pai->pai;
      } else {
        // o tio é preto e k é filho direito -> rotação a esquerda
        if (k == k->pai->dir) {
          k = k->pai;
          rotacaoEsquerda(k);
        }
        // o tio eh preto e k eh filho esquerdo -> rotação a direita + recoloração
        k->pai->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        totalRecoloracoes += 2;
        rotacaoDireita(k->pai->pai);
      }
    } else {
        tio = k->pai->pai->esq;

        if (tio->cor == VERMELHO) {
          k->pai->cor = PRETO;
          tio->cor = PRETO;
          k->pai->pai->cor = VERMELHO;
          totalRecoloracoes += 3;
          k = k->pai->pai;
        } else {
          if (k == k->pai->esq) {
            k = k->pai;
            rotacaoDireita(k);
          }
          k->pai->cor = PRETO;
          k->pai->pai->cor = VERMELHO;
          totalRecoloracoes += 2;
          rotacaoEsquerda(k->pai->pai);
        }
    }
    if (k == raiz) break;
  }

  if (raiz->cor != PRETO) {
    raiz->cor = PRETO;
    totalRecoloracoes++;
  }
}

void ArvoreRubroNegra::transplantar(NoRN* u, NoRN* v) {
  if (u->pai == NIL) {
    raiz = v;
  } else if (u == u->pai->esq) {
    u->pai->esq = v;
  } else {
    u->pai->dir = v;
  }
  v->pai = u->pai;
}

NoRN* ArvoreRubroNegra::obterNoMinimo(NoRN* no) {
  while (no->esq != NIL) {
    no = no->esq;
  }
  return no;
}

bool ArvoreRubroNegra::remover(int chave) {
  NoRN* z = raiz;

  while (z != NIL) {
    if (z->chave == chave) break;
    if (chave < z->chave) z = z->esq;
    else z = z->dir;
  }

  if (z == NIL) return false;

  NoRN* y = z;
  NoRN* x;
  Cor corOriginalDeY = y->cor;

  if (z->esq == NIL) {
    x = z->dir;
    transplantar(z, z->dir);

  } else if (z->dir == NIL) {
    x = z->esq;
    transplantar(z, z->esq);

  } else {
    y = obterNoMinimo(z->dir);
    corOriginalDeY = y->cor;
    x = y->dir;

    if (y->pai == z) {
        x->pai = y;
    } else {
        transplantar(y, y->dir);
        y->dir = z->dir;
        y->dir->pai = y;
    }

    transplantar(z, y);
    y->esq = z->esq;
    y->esq->pai = y;
    y->cor = z->cor;
  }

  delete z;

  if (corOriginalDeY == PRETO) {
    ajustarRemocao(x);
  }

  return true;
}

void ArvoreRubroNegra::ajustarRemocao(NoRN* x) {
  while (x != raiz && x->cor == PRETO) {
    if (x == x->pai->esq) {
      NoRN* w = x->pai->dir;

      if (w->cor == VERMELHO) {
        w->cor = PRETO;
        x->pai->cor = VERMELHO;
        totalRecoloracoes += 2;
        rotacaoEsquerda(x->pai);
        w = x->pai->dir;
      }

      if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
        w->cor = VERMELHO;
        totalRecoloracoes++;
        x = x->pai;

      } else {
        if (w->dir->cor == PRETO) {
          w->esq->cor = PRETO;
          w->cor = VERMELHO;
          totalRecoloracoes += 2;
          rotacaoDireita(w);
          w = x->pai->dir;
        }

        w->cor = x->pai->cor;
        x->pai->cor = PRETO;
        w->dir->cor = PRETO;
        totalRecoloracoes += 3;
        rotacaoEsquerda(x->pai);
        x = raiz;
      }
    } else {
      NoRN* w = x->pai->esq;

      if (w->cor == VERMELHO) {
        w->cor = PRETO;
        x->pai->cor = VERMELHO;
        totalRecoloracoes += 2;
        rotacaoDireita(x->pai);
        w = x->pai->esq;
      }

      if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
        w->cor = VERMELHO;
        totalRecoloracoes++;
        x = x->pai;
      } else {
        if (w->esq->cor == PRETO) {
          w->dir->cor = PRETO;
          w->cor = VERMELHO;
          totalRecoloracoes += 2;
          rotacaoEsquerda(w);
          w = x->pai->esq;
        }

        w->cor = x->pai->cor;
        x->pai->cor = PRETO;
        w->esq->cor = PRETO;
        totalRecoloracoes += 3;
        rotacaoDireita(x->pai);
        x = raiz;
      }
    }
  }

  if (x->cor != PRETO) {
    x->cor = PRETO;
    totalRecoloracoes++;
  }
}

bool ArvoreRubroNegra::buscar(int chave) {
  return buscarRec(raiz, chave);
}

bool ArvoreRubroNegra::buscarRec(NoRN* no, int chave) {
  if (no == NIL) return false;
  if (chave == no->chave) return true;
  if (chave < no->chave) return buscarRec(no->esq, chave);
  return buscarRec(no->dir, chave);
}

void ArvoreRubroNegra::exibirEmOrdem() {
  exibirEmOrdemRec(raiz);
}

void ArvoreRubroNegra::exibirEmOrdemRec(NoRN* no) {
  if (no != NIL) {
    exibirEmOrdemRec(no->esq);
    cout << no->chave << " ";
    exibirEmOrdemRec(no->dir);
  }
}

void ArvoreRubroNegra::visualizarEstrutura() {
  if (raiz == NIL) {
    cout << "[Arvore Vazia]\n";
    return;
  }
  visualizarEstruturaRec(raiz, "", false);
}

void ArvoreRubroNegra::visualizarEstruturaRec(NoRN* no, const string& prefixo, bool ehEsquerda) {
  if (no != NIL) {
    cout << prefixo;
    cout << (ehEsquerda ? "├──" : "└──");

    if (no->cor == VERMELHO) {
      cout << COR_VERMELHO << "[" << no->chave << "] (V)" << COR_RESET << "\n";
    } else {
      cout << "[" << no->chave << "] (P)\n";
    }

    visualizarEstruturaRec(no->esq, prefixo + (ehEsquerda ? "│   " : "    "), true);
    visualizarEstruturaRec(no->dir, prefixo + (ehEsquerda ? "│   " : "    "), false);
  }
}

int ArvoreRubroNegra::getAltura() {
  return calcularAlturaRec(raiz);
}

int ArvoreRubroNegra::calcularAlturaRec(NoRN* no) {
  if (no == NIL) return 0;
  return 1 + max(calcularAlturaRec(no->esq), calcularAlturaRec(no->dir));
}

long long ArvoreRubroNegra::getRotacoes() {
  return totalRotacoes;
}

long long ArvoreRubroNegra::getRecoloracoes() {
  return totalRecoloracoes;
}