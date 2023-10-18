/* jshint esversion: 8 */
let msg;
let serialOptions = { baudRate: 9600 };
let serial;
var sendData = true;
var sendButton;
var connect = false;
let isConnected = false;

let m;
console.log(m);

let timeBetweenDataSend = 50; //500ms
let lastDataSensTime = 0;




function setup() {
 
  createCanvas(400,400);
  background(50);
  gui = createGui("");
  gui.addGlobals('connect');

  // sendButton = createButton("OFF");
  //   sendButton.position(20, 100);
  //   sendButton.size(400, 100);
  // sendButton.style("font-family", "Comic Sans MS");
  // sendButton.style("font-size", "40px");
  // sendButton.mousePressed(serialWriteNumberData);

  // Setup Web Serial using serial.js
  serial = new Serial();
  serial.on(SerialEvents.CONNECTION_OPENED, onSerialConnectionOpened);
  serial.on(SerialEvents.CONNECTION_CLOSED, onSerialConnectionClosed);
  serial.on(SerialEvents.DATA_RECEIVED, onSerialDataReceived);
  serial.on(SerialEvents.ERROR_OCCURRED, onSerialErrorOccurred);
  // Add <p> element to provide messages. This is optional.
  msg = createP("");

  
  
}


function draw() {
  m = map(mouseX, 0, 400, 0, 255);
  mConstr = constrain(m, 0, 255)

  // serialWriteNumberData()

  if (connect && !isConnected) {
    connectPort();
    isConnected = true;
  } else if (!connect && isConnected) {
    closePort();
    isConnected = false;
  }



  
  // Check if connect button is pressed and the connection is not established
  if (connect && isConnected) {
    let currentSendTime = millis() - lastDataSensTime;

    if (currentSendTime > timeBetweenDataSend) {
      serialWriteNumberData();
      lastDataSensTime = millis();
    }
    
    
  }

}

async function connectPort() {
  if (!serial.isOpen()) {
    await serial.connectAndOpen(null, serialOptions);
  } else {
    serial.autoConnectAndOpenPreviouslyApprovedPort(serialOptions);
  }
}

async function closePort() {
  if (serial.isOpen()) {
    await serial.close();
  }
}

 function onSerialErrorOccurred(eventSender, error) {
  console.log("onSerialErrorOccurred", error);
  msg.html(error);
}

function onSerialConnectionOpened(eventSender) {
  console.log("onSerialConnectionOpened");
  msg.html("Serial connection opened successfully");
}


function onSerialConnectionClosed(eventSender) {
  console.log("onSerialConnectionClosed");
  msg.html("onSerialConnectionClosed");
}

function onSerialDataReceived(eventSender, newData) {
  console.log("onSerialDataReceived", newData);
  msg.html("onSerialDataReceived: " + newData);
}
 

// send data to serial port
async function serialWriteNumberData(){
  serial.writeLine(mConstr);
  
}

