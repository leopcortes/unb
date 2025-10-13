
import requests
import time
from pathlib import Path

# URL do manifesto (use 127.0.0.1 em vez de localhost para evitar erros de permissão)
MANIFEST_URL = "http://127.0.0.1:5000/manifest.mpd"

def baixar_manifesto(url: str = MANIFEST_URL) -> dict:
    """
    Função 1: Fazer uma requisição GET ao manifesto
    - Obter o JSON com as representações de vídeo
    - Retornar o dicionário com as informações do manifesto
    """
    resp = requests.get(url, timeout=10)
    resp.raise_for_status()
    return resp.json()

def medir_largura_de_banda(url_segmento_teste: str) -> float:
    """
    Função 2: Medir a largura de banda
    - Baixar um segmento pequeno (ex: 360p)
    - Medir o tempo da transferência
    - Calcular a largura de banda em Mbps: (tamanho_bytes * 8) / (tempo * 1_000_000)
    - Retornar a largura de banda medida (float, em Mbps)
    """
    t0 = time.time()
    resp = requests.get(url_segmento_teste, timeout=60, stream=True)
    resp.raise_for_status()

    tamanho_bytes = 0
    for chunk in resp.iter_content(chunk_size=64 * 1024):
        if not chunk:
            continue
        tamanho_bytes += len(chunk)
    dt = max(time.time() - t0, 1e-6)  # evita divisão por zero

    largura_mbps = (tamanho_bytes * 8) / (dt * 1_000_000)  # Mbps
    return largura_mbps

def selecionar_qualidade(manifesto: dict, largura_banda_mbps: float) -> dict:
    """
    Função 3: Escolher a melhor representação
    - Percorrer as representações disponíveis no manifesto
    - Comparar a largura de banda exigida por cada uma com a medida
    - Retornar a melhor representação suportada
    Regras:
      * Assume 'bandwidth' em kbps no manifesto; converte para Mbps para comparar.
      * Usa margem de segurança de 15% (fator 0.85).
      * Se nenhuma caber, escolhe a de menor taxa.
    """
    reps = manifesto.get("video", {}).get("representations", [])
    if not reps:
        raise ValueError("Manifesto sem representações.")

    reps_sorted = sorted(reps, key=lambda r: r.get("bandwidth", 0))  # crescente (kbps)
    fator_safety = 0.85
    escolhida = reps_sorted[0]  # default: menor

    for rep in reps_sorted:
        req_mbps = (rep.get("bandwidth", 0) or 0) / 1000.0  # kbps -> Mbps
        if req_mbps <= largura_banda_mbps * fator_safety:
            escolhida = rep

    return escolhida

def baixar_video(representacao: dict, destino: Path | str | None = None) -> Path:
    """
    Função 4: Baixar o segmento de vídeo escolhido
    - Fazer uma requisição GET para a URL da representação escolhida
    - Salvar o conteúdo em um arquivo local (ex: video_720p.mp4)
    """
    if not representacao or "url" not in representacao:
        raise ValueError("Representação inválida para download.")

    url = representacao["url"]
    vid_id = representacao.get("id", "desconhecido")
    out = Path(destino) if destino else Path(f"video_{vid_id}.mp4")

    resp = requests.get(url, timeout=120, stream=True)
    resp.raise_for_status()
    with open(out, "wb") as f:
        for chunk in resp.iter_content(chunk_size=128 * 1024):
            if chunk:
                f.write(chunk)
    return out

def escolher_url_teste(manifesto: dict) -> str:
    """
    Seleciona a URL de teste de menor banda (ex.: 360p).
    Se não achar '360p', pega a menor 'bandwidth' disponível.
    """
    reps = manifesto.get("video", {}).get("representations", [])
    if not reps:
        raise ValueError("Manifesto sem representações para teste.")
    # tenta achar 360p
    for rep in reps:
        if rep.get("id") == "360p" and "url" in rep:
            return rep["url"]
    # senão, pega a de menor banda
    rep_min = min(reps, key=lambda r: r.get("bandwidth", float("inf")))
    return rep_min["url"]

def main():
    print("== Cliente DASH Adaptativo ==")
    print(f"Manifesto: {MANIFEST_URL}")
    # 1) Baixar manifesto
    manifesto = baixar_manifesto(MANIFEST_URL)
    reps = manifesto.get("video", {}).get("representations", [])
    print("Representações disponíveis (id, bandwidth kbps, url):")
    for rep in reps:
        print(f" - {rep.get('id')} | {rep.get('bandwidth')} kbps | {rep.get('url')}")

    # 2) Medir largura de banda usando menor representação (ex: 360p)
    url_teste = escolher_url_teste(manifesto)
    print(f"\nMedindo largura de banda com segmento de teste: {url_teste}")
    largura_mbps = medir_largura_de_banda(url_teste)
    print(f"Largura de banda medida: {largura_mbps:.3f} Mbps")

    # 3) Selecionar melhor qualidade suportada
    rep_escolhida = selecionar_qualidade(manifesto, largura_mbps)
    req_mbps = (rep_escolhida.get("bandwidth", 0) or 0) / 1000.0
    print(f"\nMelhor representação suportada: {rep_escolhida.get('id')} "
          f"({rep_escolhida.get('bandwidth')} kbps ~ {req_mbps:.3f} Mbps)")

    # 4) Baixar o segmento escolhido
    caminho = baixar_video(rep_escolhida)
    print(f"Segmento salvo em: {caminho.resolve()}")

    # 5) Resumo final
    print("\nResumo:")
    print(f" - BW medida: {largura_mbps:.3f} Mbps")
    print(f" - Escolhida: {rep_escolhida.get('id')} ({req_mbps:.3f} Mbps)")
    print(f" - Arquivo:   {caminho.name}")

if __name__ == '__main__':
    main()
