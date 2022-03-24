    #include<dk_StepperWDR.h>
    #include <Servo.h>
    Servo myservo;
    dk_StepperWDR Dstep;
    #define SPversion "5.5.0"
    const int dk_maxmotor=5;
    void initial() {    // Reset ค่าต่างๆ                 
        Dstep.dk_currentPosX = 0;   // now position X of endpoint absolutely ตำแหน่ง ปัจจุบัน ของ X
        Dstep.dk_currentPosY = 0;   // now position Y of endpoint absolutely ตำแหน่ง ปัจจุบัน ของ Y
        Dstep.dk_currentTheta = 0;   // absolute pen angle ตำแหน่ง ปัจจุบัน ของ องศา มองตามการเคลื่อนของปากกา
       for (int ii=0; ii<(dk_maxmotor-1); ii++) {  // clear all data of step drive
         Dstep.dk_stepcarry[ii] = 0.0;
         Dstep.dk_stepvalue[ii] = 0.0;
         Dstep.dk_positionmm[ii]= 0.0;
       }
    }
    void D_mechanicalSetup() {   // กำหนดขนา ของกลไก
       Dstep.dk_wheelDistant = 150.0;   // 150.0   ระยะระหว่าง 2 ล้อ mm
       Dstep.dk_wheelXYdia = 63.0;     // เส้นผ่าศุนย์กลาง ล้อ mm
       Dstep.dk_wheelZdia = 20;        // เส้นผ่าศูนย์กลาง ล้อ แกน Z (ยังไม่ทำ 650128)
       Dstep.dk_SPRmotXY = 400;    // Step per Revolution MotXY ( ตั้งจากตัว Stepping Drive driver เช่น fullstep 1:1 =200, 1:2 halfstep=400)
       Dstep.dk_SPRmotZ = 1600;     // Step per Revolution MotZ ( ตั้งจากตัว Stepping Drive driver)
       Dstep.dk_gearRatioXY = 3.75;    // 3.75 อัตราทดเกียร์/pulley เช่น ทด ลง 60:16 = 3.75 
       Dstep.dk_gearRatioZ = 1;     //  อัตราทดเกียร์/pulley ของแกน Z (ยังไม่ทำ)
       Dstep.dk_LinearResmm = 0.01;  // Max error in mm   // การกำหนดค่า ต่ำสุดของระยะทาง ที่ใช้ได้
       Dstep.dk_AngleResdeg = 0.01;  // Max error in degree  // การกำหนดค่า ต่ำสุดของมุมอาศา ที่ใช้ได้
    }
    void setup() {    
        myservo.attach(9);       
    // กลับทิศมอเตอร์ ตรงนี้ ดูจาก การใช้งานจริง
    //  Dstep.dk_reversedir(0);   // Reverse direction of motor 0 (must be check the mechanics)
        Dstep.dk_reversedir(1);     // Reverse direction of motor 1 (must be check the mechanics)
    //  Dstep.dk_reversedir(2);    // 
        initial();
        D_mechanicalSetup();
        Dstep.dk_pitchXYmm = Dstep.dk_wheelXYdia*Dstep.dk_Pi/(Dstep.dk_SPRmotXY*Dstep.dk_gearRatioXY);  //mm
        Dstep.dk_pitchZmm  = Dstep.dk_wheelZdia*Dstep.dk_Pi/(Dstep.dk_SPRmotZ*Dstep.dk_gearRatioZ);     //mm
        Serial.begin(9600);    // set serial monitor 
        Serial.print(" dk_pitchXYmm = ");   Serial.println(Dstep.dk_pitchXYmm,5);
        Serial.print(" dk_pitchZmm = ");    Serial.println(Dstep.dk_pitchZmm,5);
        Serial.print("Dstep.dk_reversedir(0) = ");    Serial.println(Dstep.dk_MDIRCW[0]);
        Serial.print(" Dstep.dk_reversedir(1)=");    Serial.println(Dstep.dk_MDIRCW[1]);
    
        Dstep.dk_configStepmot(0,2,3); // set (mot_Number, clk, dir)  port for 2 motor on XY
        Dstep.dk_configStepmot(1,4,5); // set (mot_Number, clk, dir) port for 2 motor on XY
        Dstep.dk_configStepmot(2,7,6); // set (mot_Number, clk, dir) port for Z Axis
        Dstep.dk_configMech(0,Dstep.dk_SPRmotXY*Dstep.dk_gearRatioXY,Dstep.dk_pitchXYmm); // mot_number,SPR,pitch : steps/rev set at 1/2 step =400s/rev, pitch 
        Dstep.dk_configMech(1,Dstep.dk_SPRmotXY*Dstep.dk_gearRatioXY,Dstep.dk_pitchXYmm);  // mot_Number,SPR,Pitch 
        Dstep.dk_configMech(2,Dstep.dk_SPRmotZ*Dstep.dk_gearRatioZ,Dstep.dk_pitchZmm);  // mot_Number,SPR,Pitch 
    }
    void dk_delay(uint32_t dk_delay) {      // dk_delay can use 32 bit microisecond without error
        Dstep.dk_delayus(dk_delay);
    }
    void wait3sec() {
       Serial.println(" Wait for 3 seconds ");  delay(1000);
       Serial.println(" . . . . 2 ");      delay(1000);
       Serial.println(" . . . . 1 ");      delay(1000);
       Serial.println(" . . . . . ");
    }
    void printInfo() {
       Serial.println(" Infomation ");
       Serial.print(" 1. Curr X = ");  Serial.println(Dstep.dk_currentPosX,8);
       Serial.print(" 2. Curr Y = ");  Serial.println(Dstep.dk_currentPosY),8;
       Serial.print(" 3. Curr Angle = "); Serial.println(Dstep.dk_currentTheta,8);
    }
    void dk_wait() {
      while (1) {} 
    }
    void loop() {
       Serial.println(" +++++++++++++++++++++++ ");
       Serial.println("+   dk_StepperWDR 5.5.0");
       Serial.println("+   dk_StepperWDR v.1.4");
       Serial.println(" ++++++++++++++++++++++ ");
       wait3sec();
    // ============
    myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(-6,-12, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(-13,-5, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(2,-11, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(-4,1, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(-2,8, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(-8,4, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(-8,12, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(-8,4, 500);
Dstep.dk_WDRgotoXYA(-4,1, 500);
Dstep.dk_WDRgotoXYA(-13,-5, 500);
Dstep.dk_WDRgotoXYA(-12,-12, 500);
Dstep.dk_WDRgotoXYA(-4,-15, 500);
Dstep.dk_WDRgotoXYA(-6,-12, 500);
Dstep.dk_WDRgotoXYA(2,-11, 500);
Dstep.dk_WDRgotoXYA(7,0, 500);
Dstep.dk_WDRgotoXYA(11,4, 500);
Dstep.dk_WDRgotoXYA(12,12, 500);
Dstep.dk_WDRgotoXYA(5,8, 500);
Dstep.dk_WDRgotoXYA(-2,8, 500);
Dstep.dk_WDRgotoXYA(-8,12, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(5,8, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(11,4, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(7,0, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(2,-3, 500);
Dstep.dk_WDRgotoXYA(-4,1, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(2,-11, 500);
myservo.write(120);  delay(15);
Dstep.dk_WDRgotoXYA(2,-3, 500);
myservo.write(60);  delay(15);
Dstep.dk_WDRgotoXYA(-20,-20, 500);
myservo.write(120);  delay(15);
        myservo.write(40); delay(15);
        Serial.println(" ******* E N D *********** ");
        delay(2000);
        while(1){}
      }
      