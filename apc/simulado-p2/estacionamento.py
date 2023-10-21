def converterTempo(ti, tf):
    tempo_ti = (int(ti[:2]) * 60) + int(ti[3:])
    tempo_tf = (int(tf[:2]) * 60) + int(tf[3:])
    tempo = tempo_tf - tempo_ti
    return tempo

def calcularCobranca(registro):
    tempo = converterTempo(registro[1], registro[2])
    if registro[3] == "estacionamento 1":
        preco = tempo * 0.10
    elif registro[3] == "estacionamento 2":
        preco = tempo * 0.15
    else:
        return
            
    print(f"Carro com a placa: {registro[0]}, parado no {registro[3]}, deve pagar {preco} reais")

carro10 = ("PBX6480", "12:25", "14:30", "estacionamento 1")
carro11 = ("PBX6480", "12:25", "14:30", "estacionamento 2")
carro20 = ("ABC1234", "18:40", "20:05", "estacionamento 1")
carro21 = ("ABC1234", "18:40", "20:05", "estacionamento 2")

calcularCobranca(carro10)
calcularCobranca(carro11)
calcularCobranca(carro20)
calcularCobranca(carro21)