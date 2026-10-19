# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

> **Projeto de Estruturas de Dados Básicas II — IMD/UFRN**  
> **Autora:** Maria Helena Varela Kizerlla Guanaes  
> **Linguagem:** C++20 | **Ferramentas de Análise:** Python 3 (Pandas,  Numpy e Matplotlib)

---

## 📌 Sobre o Projeto

Este projeto consiste no desenvolvimento e na análise comparativa de desempenho entre duas estruturas de dados auto-balanceadas: **Árvore AVL** e **Árvore Rubro-Negra**. O objetivo é simular o sistema de logística de registro, busca e remoção de encomendas durante o pico de vendas da **Black Friday da Amazon**, avaliando qual estrutura oferece a melhor eficiência teórica e prática.

---

## ⚙️ Funcionalidades Implementadas

O programa conta com uma interface interativa via terminal e um módulo de testes automáticos:

1. **Árvore AVL:**
   - Inserção com rebalanceamento automático por Fator de Balanceamento ($\Delta h \le 1$).
   - Rotações Simples (Esquerda/Direita) e Duplas (Esquerda-Direita/Direita-Esquerda).
   - Contabilização estrita do número total de rotações.
   - Remoção tratando casos com 0, 1 e 2 filhos.

2. **Árvore Rubro-Negra:**
   - Inserção e remoção preservando as propriedades de cores (Nós Vermelhos/Pretos).
   - Balanceamento com Rotações e Recolorações de nós.
   - Contabilização de rotações e recolorações ativas.

3. **Operações Comuns:**
   - **Busca Eficiente:** Localização de chaves em tempo $O(\log N)$.
   - **Percurso Em-Ordem (In-Order):** Exibição das chaves em ordem crescente.
   - **Visualização Hierárquica:** Impressão gráfica da árvore no terminal, exibindo a altura ($h$) para a AVL e cores destacadas em formato ANSI `(V)` e `(P)` para a Rubro-Negra.
   - **Tratamento Defensivo:** Rejeição de chaves duplicadas e alertas para busca/remoção de nós inexistentes.

---

## 🔄 Fluxo de Funcionamento do Projeto

```text
       ┌─────────────────────────────────────────────────────────┐
       │                 Compilação via Makefile                 │
       └────────────────────────────┬────────────────────────────┘
                                    │
                                    ▼
       ┌─────────────────────────────────────────────────────────┐
       │             Executável (./amazon_challenge)             │
       └────────────────────────────┬────────────────────────────┘
                                    │
                   ┌────────────────┴────────────────┐
                   ▼                                 ▼
   [ Modo 1 & 2: Teste Interativo ]    [ Modo 3: Bateria Automática ]
   ├── Inserção / Remoção / Busca      ├── Cenários (100 a 10.000 nós)
   ├── Impressão In-Order              ├── Casos: Crescente, Decrescente, Aleatório
   └── Visualização Estrutural         └── Coleta: Altura, Rotações, Recolorações
                   │                                 │
                   └────────────────┬────────────────┘
                                    │
                                    ▼
       ┌─────────────────────────────────────────────────────────┐
       │             Exportação de Resultados (.csv)             │
       └────────────────────────────┬────────────────────────────┘
                                    │
                                    ▼
       ┌─────────────────────────────────────────────────────────┐
       │          Geração de Gráficos (gerar_graficos.py)        │
       └────────────────────────────┬────────────────────────────┘
```
## 🛠️ Como Compilar e Executar
### Pré-requisitos
  - Compilador g++ com suporte a C++20.
  - Make utilitário.
  - Python 3.8+ (para a geração de gráficos).

Para compilar e executar o projeto, utilize o **Makefile** incluído:

```bash
# Compilar o projeto
make

# Executar o programa
make run

# Limpar arquivos compilados
make clean
```

## 📊 Como gerar os gráficos
Para gerar os gráficos comparativos a partir do arquivo resultados_testes.csv gerado pela opção 3 do menu do C++:

1. Crie e ative um ambiente virtual Python:
```bash
python -m venv .venv

# no linux/macOS:
source .venv/bin/activate
```

2. Instale as dependências exigidas (pandas, matplotlib, numpy):

```bash
pip install -r requirements.txt
```

3. Execute o script de geração de gráficos:

```bash
python gerar_graficos.py
```