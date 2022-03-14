# Eletrônica do mecanismo de ejeção em um foguete de garrafa PET
O projeto abaixo tem por objetivo construir um sistema eletrônico e autônomo capaz de realizar  o acionamente de um sistema de ejeção de paraquedas para um foguete de garrafa PET com o intuito de futuramente ser possível testarmos novos paraquedas a fim de evitar gastos e problemas de deslocamente, visto que o teste do paraquedas demanda locais altos e abertos.

O código do programa se encontra no arquivo **teste_bmp180.ino** e pode ser aberto na interface do arduino para visualização e edição.

Os testes com as saídas do programas estão na pasta **Valores_de_Teste** neste mesmo repositório.

## Componentes do projeto (parte eletrônica)
Para ser construído a parte eletrônica, usamos os componentes abaixo:

- Arduino Nano;
- Micro Servo 9g SG90;
- BMP180 (Foi usado esse sensor devido não termos encontrado o BMP280);
- Jumpers macho-fêmea (bmp180 -> arduino);
- Jumpers macho-macho (servo -> arduino).

### Imagens dos componentes
![Arduino Nano](https://github.com/paivaneto8190/Eletronica_PET_PRD/blob/main/teste_bmp180/Imagens_componentes/arduino_nano.png?raw=true)
![BMP180](https://github.com/paivaneto8190/Eletronica_PET_PRD/blob/main/teste_bmp180/Imagens_componentes/bmp180_novo.png?raw=true)
![Micro Servo 9g SG90](https://github.com/paivaneto8190/Eletronica_PET_PRD/blob/main/teste_bmp180/Imagens_componentes/servo.png?raw=true)

Acima temos as imagens do Arduino Nano, do BMP180 e do Micro Servo 9g SG90, respectivamente.

### Conexões
Abaixo, uma imagem com uma imagem mostrando a conexão de cada componente na placa:
![Conexoes placa](https://github.com/paivaneto8190/Eletronica_PET_PRD/blob/main/teste_bmp180/Imagens_componentes/conexao.png?raw=true)

### Carregamente e execução do programa
Para executar o programa no arduíno nano, deve ser seguir as seguintes instruções na IDE do Arduino:
- Ferramentas >> Placa >> Arduino Nano

Escolhendo a porta USB:
- Ferramentas >> Porta (selecionar a porta USB para carregar o programa.)

Depois, selecionamos o processados da placa e o modo de boot:
- Ferramentas >> Processador >> ATmega328P (Old Bootloader).

Após isso, basta carregar o programa para a placa via USB.

## Problemas encontrados
Os problemas corrigidos estarão marcados com um "x".
- [x] Atuação do servo (movimento de ir e voltar a origem)
- [x] Travamento do programa durante a execução
- [ ] Oscilação do servo durante a execução (provavelmente é um problema físico)

Além do citado acima, foram colocada algums condições de teste no programa para acompanhamento via serial, como por exemplo uma condição de teste do servo ainda no setup do arduino:
```Arduino
//Condição de teste do servo
  servo.write(60);
  delay(200);
  servo.write(142);
  delay(200);
  servo.write(60);
```
Também coloquei uma condição de teste para verificar em quais momentos o código detecta a variação de altura para acionar o servo de modo a facilitar a visualização no monitor serial devido o grande número de dados (pode retirar depois):

  ```Arduino 
  Serial.println("CONT AUMENTOU")
  ```

Até o momento apenas essas funcionabilidades foram implementadas, mas em caso de sugestões de melhorias, podem clicar [aqui](mailto:paiva.neto.067@ufrn.edu.br) para escrever sugestões e até mesmo upar o código em arquivo .ZIP com uma descrição das mudanças.
