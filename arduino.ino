#include <DHT.h>  //biblioteca
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h> //biblioteca


#define DHTPIN 2          // Pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT22     // Tipo do sensor DHT utilizado

DHT dht(DHTPIN, DHTTYPE); // Instanciando o objeto DHT 

SoftwareSerial bluetooth(10,11); // Inicializa o objeto Bluetooth no pino 10 (RX) e 11 (TX)

#define led1 3
#define led2 4
#define led3 5

String comando;   
bool temperaturaAlta = false;


void setup() {
  Serial.begin(9600);         // Inicializa a comunicação serial
  bluetooth.begin(9600);      // Inicializa a comunicação Bluetooth

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  dht.begin(); // Inicializando o sensor DHT

}

void loop() {
 float temperatura = dht.readTemperature(); // Lendo a temperatura
 

 if (isnan(temperatura)) {  // verifica se é um valor NaN (Not a Number) se for TRUE
    Serial.println("Erro ao ler temperatura!"); // se for TRUE imprime a mensagem
    return;  // encerra a execução se for True
  }


  Serial.print("Temperatura: "); // Imprime "Temperatura: " no monitor serial (sem quebra de linha)
  Serial.print(temperatura);  // Imprime o valor da temperatura  no monitor serial
  Serial.println("°C");  // Imprime o valor da temperatura  no monitor serial, seguido de uma quebra de linha
  delay(2000); // Atraso de 2s entre as leituras

  // Envia os dados de temperatura via Bluetooth adicionei


 // Controle dos LEDs quando a temperatura atinge 31 °C

  if (!temperaturaAlta && temperatura >= 25) {
    temperaturaAlta = true;
    Serial.println("Temperatura atingiu 25 °C");
  }

  if (temperaturaAlta) {
    // Lógica para controle dos LEDs quando a temperatura atinge 31 °C

   comando = "";  // Limpa qualquer comando anteriormente armazenado
  
   if(bluetooth.available()){
     while(bluetooth.available()){         // Verifica se há dados disponíveis para leitura na conexão Bluetooth
      char caracter = bluetooth.read();  // Lê o próximo byte disponível na conexão Bluetooth

      comando += caracter;               // Adiciona o caractere lido à string comando
      delay(10);                         // Aguarda um curto período de tempo para garantir a leitura completa dos dados 10 milisegundos
     }

	   if(comando.indexOf("led1") >= 0){
      digitalWrite(led1, !digitalRead(led1));
      
      }
      
     if(comando.indexOf("led2") >= 0){
      digitalWrite(led2, !digitalRead(led2));
      
      }  

     if(comando.indexOf("led3") >= 0){
      digitalWrite(led3, !digitalRead(led3));
      
      }
	
	   bluetooth.println("{");
	
     if(digitalRead(led1)){
      bluetooth.println("l1on");
     }else{
       bluetooth.println("l1off");
      }

     if(digitalRead(led2)){
      bluetooth.println("l2on");
     }else{
       bluetooth.println("l2off");
      }

     if(digitalRead(led3)){
      bluetooth.println("l3on");
     }else{
       bluetooth.println("l3off");
      }

	   bluetooth.println("}");

  
    }
  }
}

