#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "avl.h"
#include "rubro_negra.h"

using namespace std;

void exportarParaCSV(const string& nomeArquivo, const vector<string>& linhasLog) {
  ofstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    cerr << "Erro ao abrir o arquivo para exportacao CSV!\n";
    return;
  }

  arquivo << "Estrutura,Cenario,Quantidade_Elementos,Altura_Final,Rotacoes,Recoloracoes,Tempo_Execucao_ms\n";
  for (const auto& linha : linhasLog) {
    arquivo << linha << "\n";
  }
  
  arquivo.close();
  cout << "\nSUCESSO! Resultados salvos com sucesso em '" << nomeArquivo << "'!\n";
}

template <typename ArvoreTipo>
void menuOperacoes(ArvoreTipo& arvore, const string& nomeArvore) {
  int opcao = 0;
  int chave;

  do {
    cout << "-------------------------------------\n";
    cout << "   OPERAÇÕES: " << nomeArvore << "\n";
    cout << "-------------------------------------\n";
    cout << "1. Inserir elemento\n";
    cout << "2. Remover elemento\n";
    cout << "3. Buscar elemento\n";
    cout << "4. Exibir Percurso Em-Ordem\n";
    cout << "5. Visualizar Estrutura da Arvore (Terminal)\n";
    cout << "6. Exibir Altura e Estatisticas\n";
    cout << "0. Voltar ao Menu Principal\n";
    cout << "Escolha uma opcao: ";
    cin >> opcao;

    switch (opcao) {
      case 1:
        cout << "Digite o valor inteiro para inserir: ";
        cin >> chave;
        if (arvore.inserir(chave)) {
          cout << "Elemento " << chave << " inserido com sucesso\n";
        } else {
          cout << "Aviso: Elemento " << chave << " ja existe na arvore (duplicata recusada)\n";
        }
      break;

      case 2:
        cout << "Digite o valor inteiro para remover: ";
        cin >> chave;
        if (arvore.remover(chave)) {
          cout << "Elemento " << chave << " removido com sucesso\n";
        } else {
          cout << "Erro: Elemento " << chave << " nao encontrado para remocao\n";
        }
      break;

      case 3:
        cout << "Digite o valor para buscar: ";
        cin >> chave;
        if (arvore.buscar(chave)) {
          cout << "Elemento " << chave << " ENCONTRADO na arvore.\n";
        } else {
          cout << "Elemento " << chave << " NAO encontrado na arvore.\n";
        }
      break;

      case 4:
        cout << "\nPercurso Em Ordem: ";
        arvore.exibirEmOrdem();
        cout << "\n";
      break;

      case 5:
        cout << "\n--- Estrutura Hirarquica da Arvore ---\n";
        arvore.visualizarEstrutura();
      break;

      case 6:
        cout << "\nAltura Atual: " << arvore.getAltura() << "\n";
        cout << "Total de Rotacoes: " << arvore.getRotacoes() << "\n";
      break;

      case 0:
        cout << "Retornando ao menu principal\n";
      break;

      default:
        cout << "Opcao invalida, tente novamente\n";
    }
  } while (opcao != 0);
}

void executarBateriaDeTestes() {
  cout << "EXECUTANDO BATERIA DE TESTES AUTOMATICA\n";

  vector<string> logsCSV;
  vector<int> tamanhos = {100, 1000, 5000, 10000};

  for (int n : tamanhos) {
    vector<int> crescente(n), decrescente(n), aleatorio(n);
    for (int i = 0; i < n; i++) {
      crescente[i] = i + 1;
      decrescente[i] = n - i;
      aleatorio[i] = i + 1;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(aleatorio.begin(), aleatorio.end(), std::default_random_engine(seed));

    vector<pair<string, vector<int>>> cenarios = {
      {"Crescente", crescente},
      {"Decrescente", decrescente},
      {"Aleatorio", aleatorio}
    };

    for (const auto& cenario : cenarios) {
      string nomeCenario = cenario.first;
      const auto& dados = cenario.second;

      // teste AVL
      {
        ArvoreAVL avl;
        auto inicio = chrono::high_resolution_clock::now();
        for (int val : dados) avl.inserir(val);
        auto fim = chrono::high_resolution_clock::now();
        double tempo = chrono::duration<double, milli>(fim - inicio).count();

        string log = "AVL," + nomeCenario + "," + to_string(n) + "," +  to_string(avl.getAltura()) + "," + to_string(avl.getRotacoes()) + ",0," + to_string(tempo);
        logsCSV.push_back(log);
      }

      // teste rubro-negra 
      {
        ArvoreRubroNegra rn;
        auto inicio = chrono::high_resolution_clock::now();
        for (int val : dados) rn.inserir(val);
        auto fim = chrono::high_resolution_clock::now();
        double tempo = chrono::duration<double, milli>(fim - inicio).count();

        string log = "Rubro-Negra," + nomeCenario + "," + to_string(n) + "," + to_string(rn.getAltura()) + "," + to_string(rn.getRotacoes()) + "," + to_string(rn.getRecoloracoes()) + "," + to_string(tempo);
        logsCSV.push_back(log);
      }
    }
  }

  exportarParaCSV("resultados_testes.csv", logsCSV);
}

int main() {
  int opcao = 0;

  do {
    cout << "------------------------------------------------------------\n";
    cout << "   AMAZON ENGINEERING CHALLENGE - ARVORES BALANCEADAS\n";
    cout << "------------------------------------------------------------\n";
    cout << "1. Operar Arvore AVL (Manual)\n";
    cout << "2. Operar Arvore Rubro-Negra (Manual)\n";
    cout << "3. Executar Bateria de Testes Automatica (Gerar CSV)\n";
    cout << "0. Sair\n";
    cout << "Escolha uma opcao: ";
    cin >> opcao;

    switch (opcao) {
      case 1: {
        ArvoreAVL avl;
        menuOperacoes(avl, "Arvore AVL");
        break;
      }
      case 2: {
        ArvoreRubroNegra rn;
        menuOperacoes(rn, "Arvore Rubro-Negra");
        break;
      }
      case 3:
        executarBateriaDeTestes();
        break;
      case 0:
        cout << "Encerrando o programa. Ate mais!\n";
        break;
      default:
        cout << "Opcao invalida!\n";
    }
  } while (opcao != 0);

  return 0;
}