// ---------- LED PINS ----------

// Layer 1
const int L1_LED1 = 13;
const int L1_LED2 = 14;
const int L1_LED3 = 25;
const int L1_LED4 = 33;

// Layer 2
const int L2_LED1 = 32;
const int L2_LED2 = 18;
const int L2_LED3 = 19;
const int L2_LED4 = 21;

// Layer 3 - BC547 base
const int L3_TRANSISTOR = 23;


// ---------- ULTRASONIC PINS ----------

const int TRIG_PIN = 22;
const int ECHO_PIN = 27;


void setup() {

  // Layer 1
  pinMode(L1_LED1, OUTPUT);
  pinMode(L1_LED2, OUTPUT);
  pinMode(L1_LED3, OUTPUT);
  pinMode(L1_LED4, OUTPUT);

  // Layer 2
  pinMode(L2_LED1, OUTPUT);
  pinMode(L2_LED2, OUTPUT);
  pinMode(L2_LED3, OUTPUT);
  pinMode(L2_LED4, OUTPUT);

  // Layer 3 transistor
  pinMode(L3_TRANSISTOR, OUTPUT);

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);

  // Initially OFF
  allLayersOff();
}


void loop() {

  // ---------- GET DISTANCE ----------

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo
  if (duration == 0) {
    allLayersOff();
    Serial.println("No object");
    delay(100);
    return;
  }

  // Calculate distance in cm
  float distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // ---------- LAYER CONTROL ----------

  if (distance > 100) {

    // Far
    layer1On();
    layer2Off();
    layer3Off();

  }
  else if (distance > 50) {

    // Medium
    layer1On();
    layer2On();
    layer3Off();

  }
  else {

    // Near
    layer1On();
    layer2On();
    layer3On();
  }

  delay(100);
}


// =================================================
// FUNCTIONS
// =================================================

void layer1On() {

  digitalWrite(L1_LED1, HIGH);
  digitalWrite(L1_LED2, HIGH);
  digitalWrite(L1_LED3, HIGH);
  digitalWrite(L1_LED4, HIGH);
}


void layer1Off() {

  digitalWrite(L1_LED1, LOW);
  digitalWrite(L1_LED2, LOW);
  digitalWrite(L1_LED3, LOW);
  digitalWrite(L1_LED4, LOW);
}


void layer2On() {

  digitalWrite(L2_LED1, HIGH);
  digitalWrite(L2_LED2, HIGH);
  digitalWrite(L2_LED3, HIGH);
  digitalWrite(L2_LED4, HIGH);
}


void layer2Off() {

  digitalWrite(L2_LED1, LOW);
  digitalWrite(L2_LED2, LOW);
  digitalWrite(L2_LED3, LOW);
  digitalWrite(L2_LED4, LOW);
}


void layer3On() {

  // Turn ON BC547
  digitalWrite(L3_TRANSISTOR, HIGH);
}


void layer3Off() {

  // Turn OFF BC547
  digitalWrite(L3_TRANSISTOR, LOW);
}


void allLayersOff() {

  layer1Off();
  layer2Off();
  layer3Off();
}
