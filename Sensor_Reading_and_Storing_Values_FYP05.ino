// Variables to store received data
float voltage = 0.0;
float current = 0.0;
float power = 0.0;


// Serial communication parameters
// const int serialBaudRate = 9600;
// HardwareSerial mySerial(2); // Use Serial 2 (RX=Pin 16, TX=Pin 17)


void setup() {
  // Initialize Serial ports
  Serial.begin(9600);    // Debugging via default Serial
  // mySerial.begin(serialBaudRate, SERIAL_8N1, 16, 17); // RX=Pin 16, TX=Pin 17 for ESP32
  //Serial2.begin(baud rate, SERIAL_8N1, RX, TX);
  Serial2.begin(9600, SERIAL_8N1, 4, 2);
  Serial.println("Waiting for data...");
}


void loop() {
  // Check if data is available on Serial2
  if (Serial2.available() > 0) {
    String receivedData = Serial2.readStringUntil('\n'); // Read the data line
    Serial.println("Received: " + receivedData);


    // Parse the voltage, current, and power from the received string
    parseData(receivedData);
   
    // Print the parsed values to the Serial Monitor
    Serial.println("Voltage: " + String(voltage) + " V");
    Serial.println("Current: " + String(current) + " A");
    Serial.println("Power: " + String(power) + " W");
    Serial.println("-------------------------------");
  }


  delay(1000); // Delay to avoid flooding with data
}


// Function to parse data (customize based on your data format)
void parseData(String data) {
  // Example: "Voltage: 230.0 V Current: 10.00 A Power: 2300.00 W"
  int voltageIndex = data.indexOf("Voltage:");
  int currentIndex = data.indexOf("Current:");
  int powerIndex = data.indexOf("Power:");
 
  if (voltageIndex != -1 && currentIndex != -1 && powerIndex != -1) {
    // Extract the voltage value
    voltage = data.substring(voltageIndex + 9, data.indexOf("V", voltageIndex)).toFloat();


    // Extract the current value
    current = data.substring(currentIndex + 8, data.indexOf("A", currentIndex)).toFloat();


    // Extract the power value
    power = data.substring(powerIndex + 6, data.indexOf("W", powerIndex)).toFloat();
  }
}