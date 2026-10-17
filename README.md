# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

## 🔄 Fluxo de Funcionamento do Projeto

O projeto foi estruturado de forma modular para permitir tanto o teste interativo individual quanto a execução automática de baterias de testes em grande escala para análise de desempenho.

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
                                    │
                                    ▼
       ┌─────────────────────────────────────────────────────────┐
       │         Apresentação Técnica & Relatório (PDF)          │
       └─────────────────────────────────────────────────────────┘
```

## 🛠️ Como Compilar e Executar

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
Para gerar o gráficos a partir do csv, crie uma venv a partir do comando:

```bash
python -m venv .venv
```

Ative o ambiente virtual, se for linux utilize o seguinte comando:
```bash
source venv/bin/activate
```

Instale os requisitos do projeto:

```bash
pip install -r requirements.txt
```

Para gerar o gráfico utilize o comando:

```bash
python gerar_graficos.py
```