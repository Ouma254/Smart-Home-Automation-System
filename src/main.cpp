#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==================================================
// LCD
// ==================================================

LiquidCrystal_I2C lcd(0x27, 16, 2);


// ==================================================
// PIN DEFINITIONS
// ==================================================

const int PIR_PIN = 2;
const int RELAY_PIN = 3;
const int BUZZER_PIN = 4;


// ==================================================
// MOTION STATE
// ==================================================

bool previousMotion = false;


// ==================================================
// SOUND 1: FUNNY WAH-WAH
// ==================================================

void soundWahWah()
{
    tone(BUZZER_PIN, 900);
    delay(200);

    tone(BUZZER_PIN, 650);
    delay(200);

    tone(BUZZER_PIN, 400);
    delay(600);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 2: DOORBELL
// ==================================================

void soundDoorbell()
{
    tone(BUZZER_PIN, 1000);
    delay(250);

    tone(BUZZER_PIN, 1500);
    delay(500);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 3: CAR HORN
// ==================================================

void soundHorn()
{
    tone(BUZZER_PIN, 400);
    delay(600);

    noTone(BUZZER_PIN);

    delay(100);

    tone(BUZZER_PIN, 400);
    delay(500);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 4: DRAMATIC ENTRANCE
// ==================================================

void soundDrama()
{
    tone(BUZZER_PIN, 250);
    delay(250);

    tone(BUZZER_PIN, 500);
    delay(250);

    tone(BUZZER_PIN, 900);
    delay(200);

    tone(BUZZER_PIN, 1400);
    delay(700);

    tone(BUZZER_PIN, 600);
    delay(200);

    tone(BUZZER_PIN, 1400);
    delay(700);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 5: UH-OH
// ==================================================

void soundUhOh()
{
    tone(BUZZER_PIN, 900);
    delay(200);

    tone(BUZZER_PIN, 700);
    delay(200);

    tone(BUZZER_PIN, 500);
    delay(250);

    tone(BUZZER_PIN, 300);
    delay(600);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 6: POLICE SIREN
// ==================================================

void soundSiren()
{
    for (int i = 0; i <= 5; i++)
    {
        for (int freq = 500; freq <= 1200; freq += 30)
        {
            tone(BUZZER_PIN, freq);
            delay(8);
        }

        for (int freq = 1200; freq >= 500; freq -= 30)
        {
            tone(BUZZER_PIN, freq);
            delay(8);
        }
    }

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 7: CARTOON
// ==================================================

void soundCartoon()
{
    tone(BUZZER_PIN, 400);
    delay(150);

    tone(BUZZER_PIN, 600);
    delay(150);

    tone(BUZZER_PIN, 800);
    delay(150);

    tone(BUZZER_PIN, 1000);
    delay(150);

    tone(BUZZER_PIN, 1400);
    delay(200);

    tone(BUZZER_PIN, 500);
    delay(600);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 8: HUMAN-LIKE LAUGH
// ==================================================

void soundLaugh()
{
    // HA
    tone(BUZZER_PIN, 900);
    delay(120);

    noTone(BUZZER_PIN);
    delay(60);

    // HA
    tone(BUZZER_PIN, 1100);
    delay(120);

    noTone(BUZZER_PIN);
    delay(60);

    // HA
    tone(BUZZER_PIN, 800);
    delay(120);

    noTone(BUZZER_PIN);
    delay(50);

    // HA
    tone(BUZZER_PIN, 1000);
    delay(120);

    noTone(BUZZER_PIN);
    delay(50);

    // HAAAA
    tone(BUZZER_PIN, 700);
    delay(180);

    noTone(BUZZER_PIN);

    delay(100);

    // Final laugh
    tone(BUZZER_PIN, 1200);
    delay(150);

    noTone(BUZZER_PIN);
}


// ==================================================
// SOUND 9: "VOICE OF GOD" / DEEP DIVINE EFFECT
// ==================================================

void soundGod()
{
    // Deep beginning
    tone(BUZZER_PIN, 120);
    delay(700);

    // Rising
    tone(BUZZER_PIN, 180);
    delay(500);

    tone(BUZZER_PIN, 250);
    delay(400);

    tone(BUZZER_PIN, 400);
    delay(300);

    // Powerful final note
    tone(BUZZER_PIN, 600);
    delay(1200);

    noTone(BUZZER_PIN);
}


// ==================================================
// RANDOM SOUND SELECTOR
// ==================================================

void playRandomSound()
{
    int sound = random(0, 9);

    Serial.print("Random sound selected: ");
    Serial.println(sound + 1);

    switch (sound)
    {
        case 0:
            Serial.println("Sound: WAH-WAH");
            soundWahWah();
            break;

        case 1:
            Serial.println("Sound: DOORBELL");
            soundDoorbell();
            break;

        case 2:
            Serial.println("Sound: CAR HORN");
            soundHorn();
            break;

        case 3:
            Serial.println("Sound: DRAMATIC ENTRANCE");
            soundDrama();
            break;

        case 4:
            Serial.println("Sound: UH-OH");
            soundUhOh();
            break;

        case 5:
            Serial.println("Sound: POLICE SIREN");
            soundSiren();
            break;

        case 6:
            Serial.println("Sound: CARTOON");
            soundCartoon();
            break;

        case 7:
            Serial.println("Sound: LAUGH");
            soundLaugh();
            break;

        case 8:
            Serial.println("Sound: GOD EFFECT");
            soundGod();
            break;
    }
}


// ==================================================
// SETUP
// ==================================================

void setup()
{
    // Pin modes
    pinMode(PIR_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // Serial
    Serial.begin(9600);

    // ------------------------------------------------
    // Initial relay state
    //
    // Your tested hardware:
    // HIGH = bulb ON
    // LOW  = bulb OFF
    // ------------------------------------------------

    digitalWrite(RELAY_PIN, LOW);

    // Make sure buzzer is silent
    noTone(BUZZER_PIN);

    // ------------------------------------------------
    // Random seed
    // ------------------------------------------------

    randomSeed(analogRead(A0));

    // ------------------------------------------------
    // LCD initialization
    // ------------------------------------------------

    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("SMART HOME");

    lcd.setCursor(0, 1);
    lcd.print("Starting...");

    delay(3000);

    // ------------------------------------------------
    // Ready screen
    // ------------------------------------------------

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Motion: NO");

    lcd.setCursor(0, 1);
    lcd.print("Relay: OFF");

    Serial.println();
    Serial.println("==============================");
    Serial.println(" SMART HOME SYSTEM READY");
    Serial.println("==============================");
}


// ==================================================
// MAIN LOOP
// ==================================================

void loop()
{
    // Read PIR
    int pirState = digitalRead(PIR_PIN);

    // Determine motion
    bool motionDetected = (pirState == HIGH);


    // =================================================
    // MOTION DETECTED
    // =================================================

    if (motionDetected)
    {
        // Turn bulb ON
        digitalWrite(RELAY_PIN, HIGH);

        // LCD
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Motion: YES");

        lcd.setCursor(0, 1);
        lcd.print("Relay: ON");


        // ------------------------------------------------
        // Play random sound ONLY when motion starts
        // ------------------------------------------------

        if (!previousMotion)
        {
            playRandomSound();
        }
    }


    // =================================================
    // NO MOTION
    // =================================================

    else
    {
        // Turn bulb OFF
        digitalWrite(RELAY_PIN, LOW);

        // Stop buzzer
        noTone(BUZZER_PIN);

        // LCD
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Motion: NO");

        lcd.setCursor(0, 1);
        lcd.print("Relay: OFF");
    }


    // =================================================
    // SAVE CURRENT MOTION STATE
    // =================================================

    previousMotion = motionDetected;


    // =================================================
    // SERIAL MONITOR
    // =================================================

    Serial.print("PIR: ");
    Serial.print(pirState);

    Serial.print(" | Motion: ");
    Serial.print(motionDetected ? "YES" : "NO");

    Serial.print(" | D3: ");
    Serial.print(digitalRead(RELAY_PIN));

    Serial.print(" | Relay: ");
    Serial.println(motionDetected ? "ON" : "OFF");


    // Small delay
    delay(200);
}