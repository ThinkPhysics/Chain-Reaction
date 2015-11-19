// Helper functions for the Think Physics Chain Reaction workshop
// Jonathan Sanderson, Northumbria University
// Intitial version: 0.1 2015-11-19

// Blink an LED on ledPin1 (default is pin 13, so also blinks onboard LED)
void blink(int time) {
	digitalWrite(ledPin1, HIGH);
	delay(time);
	digitalWrite(ledPin1, LOW);
	delay(time);
}

int updateSensors() {
	int sensorReading; // Declare the variable we're about to use
	
	// Cascade through possible inputs, pulling data off the relevant sensor pin
	if ( input == "LDR" ) {
		sensorReading = analogRead(ldrAnalogPin);
		sensorReading = map(sensorReading, 100, 800, 0, 180);
	} else if ( input == "FSR" ) {
		sensorReading = analogRead(fsrAnalogPin);
		sensorReading = map(sensorReading, 0, 1023, 0, 180);
	} else if ( input == "FLEX" ) {
		sensorReading = analogRead(flexAnalogPin);
		sensorReading = map(sensorReading, 720, 850, 0, 180);
	} else if ( input == "DISTANCE" ) {
		sensorReading = analogRead(distanceAnalogPin);
		sensorReading = map(sensorReading, 0, 1023, 0, 180);
	} else if ( input == "POTENTIOMETER" ) {
		sensorReading = analogRead(potentiometerAnalogPin);
		sensorReading = map(sensorReading, 0, 1023, 0, 180);
	} else if ( input == "TILT" ) {
		sensorReading = (digitalRead(tiltDigitalPin)) * 180; // Horrid kludge!
	} else if ( input == "HALL" ) {
		sensorReading = (digitalRead(hallDigitalPin)) * 180; // Kludging again!
	} else if ( input == "LOAD" ) {
		sensorReading = analogRead(loadAnalogPin);
		sensorReading = map(sensorReading, 900, 1023, 0, 180); // range here is tricky; full load is 50kg!
	}	else {
		sensorReading = 88; // If all you see in the serial window is this, we fell through the cascade above
	}
	
	// Make extra certain we're not returning anything except an int between 0 and 180
	sensorReading = constrain(sensorReading, 0, 180);
	
	return sensorReading;
}

// Hiding setup down here to 
// setup connects all the bits and makes sure they're working. Ignore this and skip to loop() !
void setup() {
	Serial.begin(9600);           	// establish a serial connection for debugging
	pinMode(ledPin1, OUTPUT);     	// set up the LED
	pinMode(tiltDigitalPin, INPUT);	// configure for tilt sensor input
	pinMode(relayPin1, OUTPUT);
	myServo1.attach(servoPin1);   	// set up the servo
	myServo1.write(angleRest);
	contServo1.attach(servoPinCont);// set up the continuous-rotation servo
	contServo1.write(contServoStop);// set to zero rotation
	delay(200);                   	// wait for servo to move into position
}