// Pin Definitionen
int motorPins[4] = {5, 6, 8, 9};

int triggerPin = 13;
int echoPin = 12;

int rightMotorSpeedPin = 4;
int leftMotorSpeedPin = 7;

int distanceInCm = 0;
int maxSpeed = 0;
int timeForDegree = 0;

// Eine Funktion, die den Ultraschall Sensor des Autos ausliest und in cm ausgibt.
int readUltrasonicDistance(int triggerPin_, int echoPin_)
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Ping Sensor
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);

    // Output von Sensor
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long measured = pulseIn(echoPin, HIGH);
    return (measured / 2) * 0.03432;
}

void stop(int int rMotorPin1_, int rMotorPin2_, int lMotorPin1_, int lMotorPin2_, int rMotorSpeedPin_, int lMotorSpeedPin_)
{
    digitalWrite(rMotorPin1_, LOW);
    digitalWrite(rMotorPin2_, LOW);
    digitalWrite(lMotorPin1_, LOW);
    digitalWrite(lMotorPin2_, LOW);
}

// Eine Funktion, die das Auto für eine vorgegebene Zeit [ms], Geschwindigkeit (0-255) und Richtung (Vorwärts = 'F'; Rückwärts='B') fahren lässt.
void driveForTime(int speed_, int time_, char direction_, int rMotorPin1_, int rMotorPin2_, int lMotorPin1_, int lMotorPin2_, int rMotorSpeedPin_, int lMotorSpeedPin_)
{
    pinMode(rMotorPin1_, OUTPUT);
    pinMode(rMotorPin2_, OUTPUT);
    pinMode(lMotorPin1_, OUTPUT);
    pinMode(lMotorPin2_, OUTPUT);
    pinMode(rMotorSpeedPin_, OUTPUT);
    pinMode(lMotorSpeedPin_, OUTPUT);

    // Geschwindigkeit festlegen
    analogWrite(rMotorSpeedPin_, speed_);
    analogWrite(lMotorSpeedPin_, speed_);

    switch (direction_)
    {
    case 'F':
        // Vorwärts fahren
        digitalWrite(rMotorPin1_, HIGH);
        digitalWrite(rMotorPin2_, LOW);
        digitalWrite(lMotorPin1_, HIGH);
        digitalWrite(lMotorPin2_, LOW);
        delay(time_);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    case 'B':
        // Rückwärts fahren
        digitalWrite(rMotorPin1_, LOW);
        digitalWrite(rMotorPin2_, HIGH);
        digitalWrite(lMotorPin1_, LOW);
        digitalWrite(lMotorPin2_, HIGH);
        delay(time_);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    }
}

// Eine Funktion, die das Auto für eine vorgegebene Strecke [m], Geschwindigkeit (0-255) und Richtung (Vorwärts = 'F'; Rückwärts='B') fahren lässt.
void driveForDistance(int speed_, int distance_, char direction_, int maxSpeed_, int rMotorPin1_, int rMotorPin2_, int lMotorPin1_, int lMotorPin2_, int rMotorSpeedPin_, int lMotorSpeedPin_)
{
    pinMode(rMotorPin1_, OUTPUT);
    pinMode(rMotorPin2_, OUTPUT);
    pinMode(lMotorPin1_, OUTPUT);
    pinMode(lMotorPin2_, OUTPUT);
    pinMode(rMotorSpeedPin_, OUTPUT);
    pinMode(lMotorSpeedPin_, OUTPUT);

    // Geschwindigkeit festlegen
    analogWrite(rMotorSpeedPin_, speed_);
    analogWrite(lMotorSpeedPin_, speed_);

    // Eingegebene Geschwindigkeit und Distanz in Zeit umrechnen
    int x = speed_ / 255;
    int speedOfCar = x * maxSpeed_;
    int time = (distance_ / speedOfCar) * 1000;

    switch (direction_)
    {
    case 'F':
        // Vorwärts fahren
        digitalWrite(rMotorPin1_, HIGH);
        digitalWrite(rMotorPin2_, LOW);
        digitalWrite(lMotorPin1_, HIGH);
        digitalWrite(lMotorPin2_, LOW);
        delay(time);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    case 'B':
        // Rückwärts fahren
        digitalWrite(rMotorPin1_, LOW);
        digitalWrite(rMotorPin2_, HIGH);
        digitalWrite(lMotorPin1_, LOW);
        digitalWrite(lMotorPin2_, HIGH);
        delay(time);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    }
}

// Eine Funktion, die das Auto für eine vorgegebene Gradzahl und Richtung (Rechts = 'R'; Links='L') fahren lässt.
void turnForDegrees(char direction_, int dregree_, int timeForDegree_, int rMotorPin1_, int rMotorPin2_, int lMotorPin1_, int lMotorPin2_, int rMotorSpeedPin_, int lMotorSpeedPin_)
{
    pinMode(rMotorPin1_, OUTPUT);
    pinMode(rMotorPin2_, OUTPUT);
    pinMode(lMotorPin1_, OUTPUT);
    pinMode(lMotorPin2_, OUTPUT);
    pinMode(rMotorSpeedPin_, OUTPUT);
    pinMode(lMotorSpeedPin_, OUTPUT);

    // Geschwindigkeit festlegen (immer 255)
    int speed = 255;
    analogWrite(rMotorSpeedPin_, speed);
    analogWrite(lMotorSpeedPin_, speed);

    // Angegebene Gradzahl in Zeit umrechnen
    int time = dregree_ * timeForDegree_;

    switch (direction_)
    {
    case 'R':
        // Nach rechts fahren
        digitalWrite(rMotorPin1_, HIGH);
        digitalWrite(rMotorPin2_, LOW);
        digitalWrite(lMotorPin1_, HIGH);
        digitalWrite(lMotorPin2_, LOW);
        delay(time);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    case 'L':
        // Nach links fahren
        digitalWrite(rMotorPin1_, LOW);
        digitalWrite(rMotorPin2_, HIGH);
        digitalWrite(lMotorPin1_, LOW);
        digitalWrite(lMotorPin2_, HIGH);
        delay(time);
        stop(rMotorPin1_, rMotorPin2_, lMotorPin1_, lMotorPin2_);
        break;
    }
}

/* 
Aufgaben:
1. 1m*1m Quadrat fahren
2. xm Radius Kreis fahren
3. Slalom fahren
*/

void quadrat(int speed_, int lenght_)
{
    driveForDistance(speed_, lenght_, 'F', maxSpeed, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    turnForDegrees('R', 90, timeForDegree, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    driveForDistance(speed_, lenght_, 'F', maxSpeed, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    turnForDegrees('R', 90, timeForDegree, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    driveForDistance(speed_, lenght_, 'F', maxSpeed, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    turnForDegrees('R', 90, timeForDegree, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    driveForDistance(speed_, lenght_, 'F', maxSpeed, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
    turnForDegrees('R', 90, timeForDegree, motorPins[0], motorPins[1], motorPins[2], motorPins[3], rightMotorSpeedPin, leftMotorSpeedPin);
}

void kreis() {}

void slalom() {}

void setup()
{
}

void loop()
{
}
