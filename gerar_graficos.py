import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# com base no csv que foi criado na main vai gerar um grafico que mostra a altura das arvores e o custo de rebalanceamento (rotações e recolorações) de cada uma
def gerar_graficos_analise():
  caminho_csv = 'resultados_testes.csv'
  
  try:
    df = pd.read_csv(caminho_csv)
  except FileNotFoundError:
    print(f"Erro: O arquivo '{caminho_csv}' não foi encontrado. Execute a bateria de testes em C++ primeiro.")
    return

  plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')
  fig, axes = plt.subplots(1, 2, figsize=(14, 5))

  # grafico que compara a altura das arvores
  df_aleatorio = df[df['Cenario'] == 'Aleatorio']
  
  for estrutura, grupo in df_aleatorio.groupby('Estrutura'):
    is_avl = (estrutura == 'AVL')
    axes[0].plot(
      grupo['Quantidade_Elementos'], 
      grupo['Altura_Final'], 
      marker='o' if is_avl else 's', 
      linewidth=4 if is_avl else 2, 
      linestyle='-' if is_avl else '--',
      alpha=0.75,
      label=f'Árvore {estrutura}'
    )

  axes[0].set_title('Comparação de Altura Final (Cenário Aleatório)', fontsize=12, fontweight='bold')
  axes[0].set_xlabel('Quantidade de Elementos (N)', fontsize=10)
  axes[0].set_ylabel('Altura Final da Árvore', fontsize=10)
  axes[0].legend()
  axes[0].grid(True, linestyle='--', alpha=0.7)

  # grafico que compara a qntd de rotações e recolorações
  df_10k = df[(df['Quantidade_Elementos'] == 10000) & (df['Cenario'] == 'Aleatorio')]
  
  estruturas = df_10k['Estrutura']
  rotacoes = df_10k['Rotacoes']
  recoloracoes = df_10k['Recoloracoes']

  x = np.arange(len(estruturas))
  largura = 0.35

  axes[1].bar(x - largura/2, rotacoes, largura, label='Rotações', color='#1f77b4')
  axes[1].bar(x + largura/2, recoloracoes, largura, label='Recolorações', color='#ff7f0e')

  axes[1].set_title('Custo de Rebalanceamento (N = 10.000, Aleatório)', fontsize=12, fontweight='bold')
  axes[1].set_xticks(x)
  axes[1].set_xticklabels(estruturas)
  axes[1].set_ylabel('Quantidade de Operações', fontsize=10)
  axes[1].legend()
  axes[1].grid(True, linestyle='--', alpha=0.7)

  plt.tight_layout()
  caminho_imagem = 'graficos_comparativos_amazon.png'
  plt.savefig(caminho_imagem, dpi=300)
  print(f"[SUCESSO] Gráficos gerados e salvos em '{caminho_imagem}'!")
  plt.show()

if __name__ == "__main__":
  gerar_graficos_analise()