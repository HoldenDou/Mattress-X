import processing.serial.*;
Serial myPort;
PrintWriter output;

void setup() {
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  output = createWriter("totalScores.txt");
  //output.println("Hello");
  printArray(Serial.list());
}

void draw() {
  //output.println("Hello");
  if ( myPort.available() > 0) 
  {  // If data is available,
    String totalScore = myPort.readStringUntil('\n');
    if(totalScore != null) {
      output.print(totalScore);
    }
  }
  
  if ( myPort.available() > 0) 
  {  // If data is available,
    
    String turnCount = myPort.readStringUntil('\n');
    if(turnCount != null) {
      
      output.print(turnCount);
    }
  } 
}

void mousePressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}