"""
===============================
Cliente DASH (A ser desenvolvido pelos alunos)
===============================

Objetivo:
Implementar um cliente DASH que:

1. Baixe o manifesto do servidor
2. Liste as representações disponíveis
3. Meça a largura de banda atual da rede
4. Escolha a melhor qualidade de vídeo com base na largura de banda
5. Baixe o segmento de vídeo da qualidade escolhida
6. Mostre os dados coletados e salve o segmento localmente

💡 Dica: Utilize Wireshark para capturar os pacotes da execução e observar:
   - A requisição ao manifesto
   - O segmento de vídeo baixado
   - O tempo da transferência para calcular a largura de banda

"""

# Exemplo de biblioteca útil:
import requests
import time
import os

# URL do manifesto (use 127.0.0.1 em vez de localhost para evitar erros de permissão)
MANIFEST_URL = "http://127.0.0.1:5000/manifest.mpd"
SEGMENTO_TESTE_URL = "http://127.0.0.1:5000/video/360p"

def baixar_manifesto():
    """
    Função 1: Fazer uma requisição GET ao manifesto
    - Obter o JSON com as representações de vídeo
    - Retornar o dicionário com as informações do manifesto
    """
    
    print(f"\n[1] Baixando manifesto de {MANIFEST_URL}")
    resposta = requests.get(MANIFEST_URL)
    resposta.raise_for_status()
    manifesto = resposta.json()

    print("Representacoes disponiveis:")
    for rep in manifesto["video"]["representations"]:
        print(f"  - {rep['id']}: {rep['bandwidth']} kbps")

    return manifesto

def medir_largura_de_banda(url_segmento_teste):
    """
    Função 2: Medir a largura de banda
    - Baixar um segmento pequeno (ex: 360p)
    - Medir o tempo da transferência
    - Calcular a largura de banda em Mbps: (tamanho_bytes * 8) / (tempo * 1_000_000)
    - Retornar a largura de banda medida
    """
    
    print(f"\n[2] Medindo largura de banda com {url_segmento_teste}")
    inicio = time.time()
    resposta = requests.get(url_segmento_teste)
    resposta.raise_for_status()
    fim = time.time()

    tempo = fim - inicio
    tamanho_bytes = len(resposta.content)
    largura_banda_mbps = (tamanho_bytes * 8) / (tempo * 1_000_000) if tempo > 0 else 0

    print(f"Tamanho baixado: {tamanho_bytes} bytes")
    print(f"Tempo de transferencia: {tempo:.4f} s")
    print(f"Largura de banda medida: {largura_banda_mbps:.4f} Mbps")

    return largura_banda_mbps

def selecionar_qualidade(manifesto, largura_banda_mbps):
    """
    Função 3: Escolher a melhor representação
    - Percorrer as representações disponíveis no manifesto
    - Comparar a largura de banda exigida por cada uma com a medida
    - Retornar a melhor representação suportada
    """
    
    print(f"\n[3] Selecionando qualidade para {largura_banda_mbps:.4f} Mbps")
    largura_banda_kbps = largura_banda_mbps * 1000

    representacoes = sorted(
        manifesto["video"]["representations"],
        key=lambda r: r["bandwidth"]
    )

    escolhida = representacoes[0]
    for rep in representacoes:
        if rep["bandwidth"] <= largura_banda_kbps:
            escolhida = rep
        else:
            break

    print(f"Qualidade selecionada: {escolhida['id']} ({escolhida['bandwidth']} kbps)")
    return escolhida

def baixar_video(representacao):
    """
    Função 4: Baixar o segmento de vídeo escolhido
    - Fazer uma requisição GET para a URL da representação escolhida
    - Salvar o conteúdo em um arquivo local (ex: video_720p.mp4)
    """
    url = representacao["url"]
    nome_arquivo = f"video_{representacao['id']}.mp4"
    print(f"\n[4] Baixando segmento de {url}")

    inicio = time.time()
    resposta = requests.get(url)
    resposta.raise_for_status()
    tempo = time.time() - inicio

    with open(nome_arquivo, "wb") as f:
        f.write(resposta.content)

    print(f"Arquivo salvo: {os.path.abspath(nome_arquivo)}")
    print(f"Tamanho: {len(resposta.content)} bytes")
    print(f"Tempo de download: {tempo:.4f} s")

    return nome_arquivo

def main():
    """
     Função principal:
    - Chamar as funções na ordem correta
    - Exibir os dados na tela
    - Salvar o vídeo com a qualidade selecionada
    """
    
    print("=" * 50)
    print("  CLIENTE DASH ADAPTATIVO")
    print("=" * 50)

    try:
        manifesto = baixar_manifesto()
        largura_banda = medir_largura_de_banda(SEGMENTO_TESTE_URL)
        representacao = selecionar_qualidade(manifesto, largura_banda)
        arquivo = baixar_video(representacao)

        print("\n" + "=" * 50)
        print("  RESUMO")
        print("=" * 50)
        print(f"Largura de banda medida: {largura_banda:.4f} Mbps")
        print(f"Qualidade escolhida:     {representacao['id']}")
        print(f"Bandwidth exigido:       {representacao['bandwidth']} kbps")
        print(f"Arquivo salvo:           {arquivo}")

    except requests.exceptions.ConnectionError:
        print("\nERRO: Nao foi possivel conectar ao servidor.")
        print("Verifique se o server.py esta rodando em 127.0.0.1:5000")
    except Exception as e:
        print(f"\nERRO inesperado: {e}")

if __name__ == '__main__':
    main()

