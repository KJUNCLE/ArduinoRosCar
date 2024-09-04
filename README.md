# ArduinoRosCar

记录一下我遇到的问题和解决方法

1. 安装arduino IDE之后找不到端口 <br>
解决方法: <br>
        ```bash
        sudo dmesg | grep brltty
        ```
查看是否存在驱动占用。如果终端显示：
    ```bash
    [ 7033.078452] usb 1-13: usbfs: interface 0 claimed by ch341 while 'brltty' sets config #1
    ```
    则表示存在占用。<br>
那么我们则需要将占用删除，需要运行：
    ```bash
    sudo apt remove brltty
    ```
    此时重新拔插以下数据线，然后使用如下命令查看<br>
    ```bash
    ls /dev/ttyUSB0 
    /dev/ttyUSB0
    ```
    如果可以在终端中找到usb0，那么就可以在ide中找到端口
https://blog.csdn.net/qq_27865227/article/details/125538516



