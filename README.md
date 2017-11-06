Train Control with threads
========================
This project was developed as part of a university (UFRN) course and demonstrates functionalities of a mutex while dealing with threads. It uses a A Bleaglebone Black (BBB) that receives analog input through its ADC to control the simulated speed which two trains run along a circular rail. There is only one intersection between both rails and the trains should not be on the same section at the same time.

![BeagleBone](http://beagleboard.org/static/images/cape-headers.png)

## Getting started ##
### Connecting to the Bleaglebone Black ###
On a Linux system
1. Connect your BeagleBone to your computer by using a Mini USB cable.
2. Open the terminal and type `ifconfig`. You should see a network adapter that has one of the following ips `192.168.7.1` or `192.168.6.1`
3. Then the BeagleBone itself will have the ip `192.168.6.2` or `192.168.7.2`
4. Then connect via ssh with the command `ssh debian@192.168.7.2`, use sudo and/or change the ip if necessary. Make sure you're connecting with the correct username in ssh

#### Share internet connection over the USB ####
Reference: <https://elementztechblog.wordpress.com/2014/12/22/sharing-internet-using-network-over-usb-in-beaglebone-black/>

On the BeagleBone Board, run (mind the correct ip address, it could be either `192.168.6.#` or `192.168.7.#`)
```
ifconfig usb0 192.168.6.2
route add default gw 192.168.6.1
```

On the PC host, run (ATTENTION: change the `wlan0` to yout internet interface and `eth0` to the network adapter of the BeagleBone. And mind the ip address as well)
```
sudo su
ifconfig eth0 192.168.6.1
iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
iptables --append FORWARD --in-interface eth0 -j ACCEPT
echo 1 > /proc/sys/net/ipv4/ip_forward
```
## Enable ADC read in Kernel 4.x ##

With root provileges, run
```
sh -c "echo 'BB-ADC' > /sys/devices/platform/bone_capemgr/slots"
```

And to read from analog port, run
```
cat "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
```
in `in_voltage0_raw` change 0 to the number of the ADC, from 0 to 6.

See references to make this permanent on reboot
## Enable LCD Display on Beagle ##

If you want to display the result on a LCD display, first follow the steps in README of <https://github.com/gorskima/hd44780-i2c> to compile and add kernel module of LCD I2C display (see the usage below, copied and modified from gorskima).

#### Usage ####
1. In the train-control-beagle folder, run `insmod ../hd44780-i2c/hd44780.ko` to add the kernel module
2. Let the I2C adapter know that there's a new device attached: `echo hd44780 0x27 > /sys/class/i2c-adapter/i2c-2/new_device`. You may need to replace the device's I2C address and adapter path with proper values. For example, consider changing the `i2c-1` to `i2c-2`, if you get `bash: /sys/class/i2c-adapter/i2c-1/new_device: No such file or directory`
3. At this point a new device should appear (`/dev/lcd0`) and you should be able to write to it
4. For more information, see the github repository of the hd44780 driver.

Disable cursor blink and cursos display
```
echo "0" > /sys/class/hd44780/lcd-2/cursor_blink
echo "0" > /sys/class/hd44780/lcd-2/cursor_display
```


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
