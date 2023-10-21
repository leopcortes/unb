/************************************************************
* Projeto Irrigador Automatico
* Leonardo Pereira e Marcos Milhomem
* UnB 2021.1 - Projeto Transversal em Redes de Comunicação
*************************************************************/

const int PINO_SENSOR = A0; //Pino (analogico) conectado ao sensor
const int PINO_RELE = 2; //Pino conectado ao rele

//Variaveis que armazenam as leituras do sensor
int leitura_sensor = 0;
int leitura_anterior = 0;

//Variaveis que armazenam os valores da sensibilidade do sensor
const int VALOR_MAXIMO = 632; //Solo seco
const int VALOR_MINIMO = 314; //Solo umido

//Pocentagens a serem alteradas de acordo com a necessidade de cada planta
const int CONCENTRACAO_MAXIMA = 50;
const int CONCENTRACAO_MINIMA = 30;

void setup() {
  pinMode(PINO_SENSOR, INPUT); //Define o pino conectado ao sensor como uma entrada do sistema
  pinMode(PINO_RELE, OUTPUT); //Define o pino conectado ao rele como uma saida do sistema

  digitalWrite(PINO_RELE, LOW); //Inicia o pino conectado ao rele com nivel logico baixo

  pinMode(8, OUTPUT); //led verde
  pinMode(9, OUTPUT); //led amarelo
  pinMode(10, OUTPUT); //led vermelho

  Serial.begin(9600);
}

void loop() {
  leitura_sensor = analogRead(PINO_SENSOR); //Leitura do sensor
  leitura_sensor = map(leitura_sensor, VALOR_MINIMO, VALOR_MAXIMO, 100, 0); //Conversao do valor lido para um valor entre 0 e 100%
  Serial.print(analogRead(PINO_SENSOR)); //Impressao no monitor serial
  Serial.print('\n');

  //Verifica se a leitura esta abaixo da concentracao minima desejada
  if(leitura_sensor < CONCENTRACAO_MINIMA){ //Se sim (seco)
    digitalWrite(8, LOW); //Verde desligado
    digitalWrite(10, HIGH); //Vermelho ligado
  }else if(leitura_sensor > CONCENTRACAO_MAXIMA){ //Caso contrario (umido)
    digitalWrite(8, HIGH); //Verde ligado
    digitalWrite(10, LOW); //Vermelho desligado
  }

  if(leitura_sensor && !leitura_anterior){ //Se estiver seco
    delay(5000); //Aguarda 5 segundos para comecar a irrigacao
    digitalWrite(9, HIGH); //Amarelo ligado
    digitalWrite(10, LOW); //Vermelho desligado

    while(digitalRead(PINO_SENSOR)){ //Loop para liberar agua ate ficar umido
      digitalWrite(PINO_RELE, HIGH); //Acionamos o rele por 2 segundos
      delay(2000);
      digitalWrite(PINO_RELE, LOW); //Desligamos o rele

      delay(5000); //Espera 5 segundos para fazer nova leitura
    }
    digitalWrite(9, LOW); //Amarelo desligado
  }
  leitura_anterior = leitura_sensor;
}
