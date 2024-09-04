// #include <Servo.h> // 引入Servo库
// #include "MsTimer2.h"

#include "PS2X_lib.h"  //for v1.6
#include "Emakefun_MotorDriver.h"
#include "math.h"

// 初始化PS2手柄
PS2X ps2x;
// 设置PS2手柄引脚
#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

// 获取电机控制器的地址？？
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver(0x60);

// 初始化Emakefun_MotorDriver 舵机
Emakefun_Servo *mServo8 = mMotorDriver.getServo(8);

// 初始化直流电机
Emakefun_DCMotor *DCMotor_1 = mMotorDriver.getMotor(M1);
Emakefun_DCMotor *DCMotor_2 = mMotorDriver.getMotor(M2);


// Servo myservo; // 创建一个Servo对象来控制舵机

void setup() {

  Serial.begin(9600); // 初始化串口通信
  // 初始化PS2手柄
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  ps2x.read_gamepad();
  mMotorDriver.begin(50);


  // myservo.attach(9); // 将舵机信号线连接到数字引脚9
}

void loop() {
  // 读取手柄数据
    ps2x.read_gamepad();
    
    // 读取左摇杆X轴，用于控制舵机的角度
    int joyX = ps2x.Analog(PSS_LX);
    int joyY = ps2x.Analog(PSS_RY);
    
    // 映射摇杆的值到舵机的角度（0-180度）
    int servoAngle = map(joyX, 0, 255, 0, 180);
    int dcSpeed = map(joyY, 0, 255, -255, 255);

    // 设置舵机角度
    mServo8->writeServo(servoAngle);
    if (dcSpeed >= 0)
    {
      DCMotor_1->setSpeed(dcSpeed);
      DCMotor_1->run(FORWARD);
      DCMotor_2->setSpeed(dcSpeed);
      DCMotor_2->run(FORWARD);
    }
    else 
    {
      DCMotor_1->setSpeed(abs(dcSpeed));
      DCMotor_1->run(BACKWARD);
      DCMotor_2->setSpeed(abs(dcSpeed));
      DCMotor_2->run(BACKWARD);
    }

    //设置延时
    delay(10);
}