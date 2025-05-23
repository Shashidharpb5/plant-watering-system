// Automatic Plant Watering System
// This code checks the moisture level of a plant every hour.
// If the level is below 30%, it runs a water pump for 90 seconds.
// Original code by Louise Lundblad and Hanna Hermansson (Group 41)

const int sensor_pin = A0;         // Analog pin for moisture sensor
const int led_pin = 13;            // Built-in LED pin
const int water_pump = A4;         // Digital pin for water pump relay
const int sensor_power = 12;       // Digital pin to power the sensor

int moisture = 0;
int moisture1 = 0;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(water_pump, OUTPUT);
  pinMode(sensor_power, OUTPUT);

  Serial.begin(9600);              // Start serial communication
}

void loop() {
  // Wait for 1 hour (3600000 milliseconds)
  delay(3600000);

  moisture = 0;

  // Take 5 readings and average them
  for (int i = 0; i < 5; i++) {
    digitalWrite(sensor_power, HIGH);
    delay(100); // Allow sensor to stabilize
    moisture += analogRead(sensor_pin);
    digitalWrite(sensor_power, LOW);
    delay(100); // Wait before next reading
  }

  moisture = moisture / 5; // Average the readings

  // Map sensor value to percentage (adjust range based on your sensor)
  moisture1 = map(moisture, 135, 105, 0, 100);

  Serial.print("Moisture: ");
  Serial.print(moisture1);
  Serial.println("%");

  if (moisture1 <= 30) {
    digitalWrite(led_pin, HIGH);
    digitalWrite(water_pump, HIGH);
    delay(90000); // Run pump for 90 seconds
    digitalWrite(led_pin, LOW);
    digitalWrite(water_pump, LOW);
  } else {
    digitalWrite(led_pin, LOW);
    digitalWrite(water_pump, LOW);
  }
}
