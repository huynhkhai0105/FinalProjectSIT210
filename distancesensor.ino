// Pin Definitions

double in;
bool warning;
long duration;

int timerRedLED = D4;
int timerLED = D2;
int buzzer = D3;
int triggerPin = D6;
int echoPin = D7;

void setup() 
{
    pinMode(buzzer, OUTPUT);
    pinMode(timerRedLED, OUTPUT);
    pinMode(timerLED, OUTPUT);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() 
{
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    in = (duration/2)/74;
    delay(200);
    // check if there is a breakout
    if (in > 10){
        Particle.publish("Nothing_Happened", String(warning));
        warning = false;   
        Serial.println("Nothing Happened");
        digitalWrite(buzzer, LOW);
        digitalWrite(timerLED, LOW);
    }
    
    else if (in >= 10 && in <=20) {
        Particle.publish("People_Approaching", String(warning));
        warning = false;   
        Serial.println("People_Approaching");
        digitalWrite(buzzer, LOW);
        digitalWrite(timerLED, HIGH);
    }
    
    else if (in < 10){
        Particle.publish("Outside", String(warning));
        warning = true;   
        Serial.println("Outside");
        digitalWrite(buzzer, HIGH);
        digitalWrite(timerLED, HIGH);
    }
    delay(1000);
}
