#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Servo.h>

Adafruit_BMP085 bmp180;

Servo servo;

float altura = 0.0, alt1 = 0.0, alt2 = 0.0, alt3 = 0.0;
float media_alt = 0.0;
float alt_anterior = 0.0, maior_alt = 0.0;

int cont = 0;

bool condicao = false;

#define pinServo 9

void setup() {
  Serial.begin(9600);
  if(!bmp180.begin()) 
  {
    Serial.println("Sensor nao encontrado !!");
    while(1){}
  }
  servo.attach(pinServo);

  //Condição de teste do servo (pode retirar depois)
  servo.write(60);
  delay(200);
  servo.write(142);
  delay(200);
  servo.write(60);
}

void loop() {
  Serial.print("Altitude : ");
  Serial.print(bmp180.readAltitude());
  Serial.println(" m");
  
  servo.write(60);

  coleta(); 
  delay(500);



  condicao = altimetro(altura, alt1, alt2, alt3);

  if(condicao == true)
  {
    servo.write(142);
    Serial.print("DEU CERTO");
    delay(300); //Condicao para ver o porque o servo nao estar funcionando corretamente
  }
  Serial.println("");
}

// Coleta das altitudes
void coleta()
{
  altura = bmp180.readAltitude();

  delay(500);
  alt1 = bmp180.readAltitude();
  delay(100);
  alt2 = bmp180.readAltitude();
  delay(100);
  alt3 = bmp180.readAltitude();
}

bool altimetro(float altura, float alt1, float alt2, float alt3)
{
  alt_anterior = altura;
  if(altura >= 10.0)
  {
    
    // Medias das altitudes
    media_alt = (alt1 + alt2 + alt3)/3;


    // Checa se a media das altitudes eh maior que a altitude coletada
    if(media_alt > alt_anterior)
    {
      maior_alt = media_alt;
    }


    // Incrementa quando a maior altitude eh maior que a media 
    if(maior_alt > media_alt)
    {
      cont++;
    }

    Serial.print("MAIOR altura = ");
    Serial.println(maior_alt);
    delay(100);


    if(cont == 3)
    {
      cont = 0;
      return true;
    }
  }
  return false;
}
