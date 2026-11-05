"""
Servidor Flask que le o estado do semaforo de 3 vias via porta serial
do Arduino e expoe uma visualizacao web em http://localhost:8080
"""
import threading
import time

import serial
from flask import Flask, jsonify, render_template

SERIAL_PORT = "COM3"
BAUD_RATE = 9600

app = Flask(__name__)

estado_lock = threading.Lock()
estado_atual = {"V1": "VERMELHO", "V2": "VERMELHO", "V3": "VERMELHO"}


def parse_linha(linha):
    # Formato esperado: STATUS,V1:VERDE,V2:VERMELHO,V3:VERMELHO
    partes = linha.strip().split(",")
    if not partes or partes[0] != "STATUS":
        return None
    novo_estado = {}
    for parte in partes[1:]:
        if ":" not in parte:
            continue
        chave, valor = parte.split(":", 1)
        novo_estado[chave] = valor
    if {"V1", "V2", "V3"} <= novo_estado.keys():
        return novo_estado
    return None


def ler_serial_loop():
    global estado_atual
    while True:
        try:
            with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
                print(f"Conectado em {SERIAL_PORT} @ {BAUD_RATE}")
                while True:
                    linha = ser.readline().decode("utf-8", errors="ignore")
                    if not linha:
                        continue
                    novo_estado = parse_linha(linha)
                    if novo_estado:
                        with estado_lock:
                            estado_atual = novo_estado
        except serial.SerialException as exc:
            print(f"Erro na porta serial ({SERIAL_PORT}): {exc}. Tentando novamente em 3s...")
            time.sleep(3)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/status")
def status():
    with estado_lock:
        return jsonify(estado_atual)


if __name__ == "__main__":
    thread = threading.Thread(target=ler_serial_loop, daemon=True)
    thread.start()
    app.run(host="0.0.0.0", port=8080)
