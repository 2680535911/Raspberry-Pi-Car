import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)

TRIG = 5
ECHO = 6
IN1 = 20
IN2 = 21
IN3 = 19
IN4 = 26
ENA = 16
ENB = 13

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)
GPIO.setup(ENA, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(IN1, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN2, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(ENB, GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(IN3, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(IN4, GPIO.OUT, initial=GPIO.LOW)

pwm_ENA = GPIO.PWM(ENA, 2000)
pwm_ENB = GPIO.PWM(ENB, 2000)
pwm_ENA.start(0)
pwm_ENB.start(0)

def voltage_set(signal):
    IN1 = 20
    IN2 = 21
    IN3 = 19
    IN4 = 26
    GPIO.output(IN1, signal[0])
    GPIO.output(IN2, signal[1])
    GPIO.output(IN3, signal[2])
    GPIO.output(IN4, signal[3])
    pass


def flexible_run(rate, delay_time=None):
    signal = [GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH]
    voltage_set(signal)
    pwm_ENA.ChangeDutyCycle(int((1 - rate[0]) * rate[1] / 2 + rate[2]))
    pwm_ENB.ChangeDutyCycle(int((1 + rate[0]) * rate[1] / 2 + rate[2]))
    if delay_time is not None:
        time.sleep(delay_time)
    else:
        pass
    brake()


def forward(speed, delay_time=None):
    signal = [GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH]
    voltage_set(signal)
    pwm_ENA.ChangeDutyCycle(speed)
    pwm_ENB.ChangeDutyCycle(speed)
    if delay_time is not None:
        time.sleep(delay_time)
    else:
        pass
    brake()

def left(speed, delay_time=None):
    signal = [GPIO.LOW, GPIO.LOW, GPIO.LOW, GPIO.HIGH]
    voltage_set(signal)
    pwm_ENA.ChangeDutyCycle(0)
    pwm_ENB.ChangeDutyCycle(speed)
    if delay_time is not None:
        time.sleep(delay_time)
    else:
        pass
    brake()


def right(speed, delay_time=None):
    signal = [GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.LOW]
    voltage_set(signal)
    pwm_ENA.ChangeDutyCycle(speed)
    pwm_ENB.ChangeDutyCycle(0)
    if delay_time is not None:
        time.sleep(delay_time)
    else:
        pass
    brake()

def brake(speed=100, delay_time=None):
    signal = [GPIO.LOW, GPIO.LOW, GPIO.LOW, GPIO.LOW]
    voltage_set(signal)
    pwm_ENA.ChangeDutyCycle(speed)
    pwm_ENB.ChangeDutyCycle(speed)
    if delay_time is not None:
        time.sleep(delay_time)
    else:
        pass


def Distance_Ultrasound():
    emitTime = 0
    while emitTime == 0:
        GPIO.output(TRIG, GPIO.LOW)
        time.sleep(0.000002)
        GPIO.output(TRIG, GPIO.HIGH)
        time.sleep(0.00001)
        GPIO.output(TRIG, GPIO.LOW)
        while GPIO.input(ECHO) == 0:
            emitTime = time.time()
        while GPIO.input(ECHO) == 1:
            acceptTime = time.time()
        totalTime = acceptTime - emitTime
        distanceReturn = totalTime * 340 / 2 * 100
    return distanceReturn

def Obstacle_Avoidance():
    while True:
        dis= Distance_Ultrasound()
        print("距离 ",dis,"cm")
        if dis<30 :
            while dis<30:
                dis=Distance_Ultrasound()
                print("距离 ",dis,"cm")
            left(20,delay_time=1)
            forward(20,delay_time=1)
        time.sleep(0.5)

print("超声波避障系统运行中，按Ctrl+C退出...")
try:
    Forward()
    Obstacle_Avoidance()
except KeyboardInterrupt:
    pass
