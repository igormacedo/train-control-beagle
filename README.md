Train Control with threads
==========================

## Building
Requirements:
- CMake >= 3.5.1

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./train_control
```

### Description in Portuguese ###
Questão: controle de 02 trens, para que não haja colisões entre eles.
Loop do Trem1: L1, L2,L3,L4.
Loop do Trem2: L5, L6,L7,L3.

Atividades dos Trens:
- Acender o led correspondente ao seguinte em que o trem está (acender na entrada e apagar na saída).
- Permanecer no seguimento por um tempo inversamente proporcional ao valor da tensão lida no respectivo ADC (ADC1 para o trem1 e ADC2 para o trem2). Evite divisão por ZERO. Use poteciômetros para variar as tensões de entrada dos ADCs.
- Os trens não podem estar no seguimento L3 ao mesmo tempo (utilize uma estratégia de exclusão mútua para resolver este problema).
- Ao pressionar o botão reset, a aplicação é reiniciada. (Este botão está associado a uma entrada digital).

Material necessário:
- 01 placa Beagle Board
- 01 display de 7 seguimentos + 07 resistores (associados a saídas digitais).
- 02 potenciômetros (associados a ADCs)
- 01 botão reset + 01 resistor (associados a uma entrada digital).

Apresentar os resultados em vídeo.
- Demonstre que a solução é livre de colisões (mude a velociade dos trens para exibir isto).
- Apresente uma Rede de Petri para explicar a solução implementada.

## References ##
1. ADC on BeagleBone. <http://beaglebone.cameon.net/home/reading-the-analog-inputs-adc>
2. How to read ADC values in kernel 4.x. <https://askubuntu.com/questions/882433/enable-adc-input-on-beaglebone-with-4-x-kernel>
3. <https://www.teachmemicro.com/beaglebone-black-adc/>
