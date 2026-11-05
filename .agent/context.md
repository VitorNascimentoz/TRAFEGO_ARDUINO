int verde1 = 13;
int amarelo1 = 12;
int vermelho1 = 11;

int verde2 = 9;
int amarelo2 = 8;
int vermelho2 = 7;

int verde3 = 5;
int amarelo3 = 4;
int vermelho3 = 3;

void setup() {
  pinMode(verde1, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(vermelho1, OUTPUT);
  
  pinMode(verde2, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(vermelho2, OUTPUT);
}

/*void loop1(){
  digitalWrite(verde1, HIGH) && digitalWrite(vermelho2, HIGH);
  delay(5000); 
  digitalWrite(verde1, LOW)&& digitalWrite(amarelo1,HIGH)
  delay(2000) 
  digitalWrite(vermelho2, LOW);;  
}

void loop2(){
  digitalWrite(amarelo1, HIGH) && digitalWrite(verde2, HIGH);
  
}*/

void loop() { 
  // Verde: pode passar
  digitalWrite(amarelo1, LOW);
  digitalWrite(amarelo2, LOW);
  digitalWrite(vermelho1, LOW); 
  digitalWrite(verde1, HIGH);
  digitalWrite(vermelho2, HIGH);
  delay(5000);              // 5 segundos
  digitalWrite(verde1, LOW);
  digitalWrite(vermelho2, HIGH);
  digitalWrite(amarelo1, HIGH);
  delay(3000);
  digitalWrite(amarelo1, LOW);
  digitalWrite(vermelho2, HIGH);
  digitalWrite(vermelho1, HIGH);
  delay(4000);
  digitalWrite(amarelo1, LOW);
  digitalWrite(vermelho2, LOW);
  digitalWrite(vermelho1, HIGH);
  digitalWrite(verde2, HIGH);
  delay(5000);
  digitalWrite(verde2, LOW);
  digitalWrite(verde1, LOW);
  digitalWrite(amarelo2, HIGH);
  digitalWrite(vermelho2, LOW);
  digitalWrite(vermelho1, HIGH);
  delay(3000);
  digitalWrite(amarelo2, LOW);
  digitalWrite(vermelho1, HIGH);
  digitalWrite(vermelho2, HIGH);
  digitalWrite(verde1, LOW);
  delay(4000);

}