// Semaforo sincronizado de 3 vias - Arduino Uno/Nano
// Apenas uma via fica verde por vez; entre trocas ha uma fase de
// "tudo vermelho" (clareamento) para evitar cruzamento de fluxos.
// Estado e enviado por Serial a cada troca de fase para o servidor Python.

const int PIN_VERDE[3]    = {13, 9, 5};
const int PIN_AMARELO[3]  = {12, 8, 4};
const int PIN_VERMELHO[3] = {11, 7, 3};

const unsigned long TEMPO_VERDE    = 5000;
const unsigned long TEMPO_AMARELO  = 2000;
const unsigned long TEMPO_CLAREAR  = 1000; // tudo vermelho antes de trocar

enum Fase { VERDE, AMARELO, CLAREANDO };

int viaAtiva = 0;      // qual via esta no ciclo verde/amarelo
Fase faseAtual = VERDE;
unsigned long inicioFase = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(PIN_VERDE[i], OUTPUT);
    pinMode(PIN_AMARELO[i], OUTPUT);
    pinMode(PIN_VERMELHO[i], OUTPUT);
  }
  Serial.begin(9600);
  inicioFase = millis();
  aplicarEstado();
  enviarStatus();
}

void loop() {
  unsigned long agora = millis();
  unsigned long duracaoFase = (faseAtual == VERDE) ? TEMPO_VERDE
                              : (faseAtual == AMARELO) ? TEMPO_AMARELO
                              : TEMPO_CLAREAR;

  if (agora - inicioFase >= duracaoFase) {
    avancarFase();
    inicioFase = agora;
    aplicarEstado();
    enviarStatus();
  }
}

void avancarFase() {
  if (faseAtual == VERDE) {
    faseAtual = AMARELO;
  } else if (faseAtual == AMARELO) {
    faseAtual = CLAREANDO;
  } else { // CLAREANDO -> proxima via entra no verde
    viaAtiva = (viaAtiva + 1) % 3;
    faseAtual = VERDE;
  }
}

// Liga/desliga os LEDs de acordo com viaAtiva + faseAtual
void aplicarEstado() {
  for (int i = 0; i < 3; i++) {
    bool verde = false, amarelo = false, vermelho = true;

    if (i == viaAtiva) {
      if (faseAtual == VERDE) {
        verde = true; vermelho = false;
      } else if (faseAtual == AMARELO) {
        amarelo = true; vermelho = false;
      }
      // CLAREANDO: fica vermelho (default), igual as outras vias
    }

    digitalWrite(PIN_VERDE[i], verde ? HIGH : LOW);
    digitalWrite(PIN_AMARELO[i], amarelo ? HIGH : LOW);
    digitalWrite(PIN_VERMELHO[i], vermelho ? HIGH : LOW);
  }
}

const char* nomeEstado(int via) {
  if (via == viaAtiva) {
    if (faseAtual == VERDE) return "VERDE";
    if (faseAtual == AMARELO) return "AMARELO";
  }
  return "VERMELHO";
}

// Envia: STATUS,V1:VERDE,V2:VERMELHO,V3:VERMELHO
void enviarStatus() {
  Serial.print("STATUS,V1:");
  Serial.print(nomeEstado(0));
  Serial.print(",V2:");
  Serial.print(nomeEstado(1));
  Serial.print(",V3:");
  Serial.println(nomeEstado(2));
}
