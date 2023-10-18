// Initialize a flag to track BLE connection status.
let bleConnected = false;

// Define the UUID for the Bluetooth service.
const serviceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";

// Create an array to store Bluetooth characteristics.
let myCharacteristics = [];

// Initialize the LED state to 'off'.
let ledState = 0;

// Initialize variables to store IMU (Inertial Measurement Unit) data.
let ax = 0.0;
let ay = 0.0;
let az = 0.0;

// Setup function runs once at the beginning.
function setup() {
	// Create a 3D canvas with WebGL rendering.
	createCanvas(400, 400, WEBGL);

	// Create a 'Connect' button and set its click event handler.
	const connectButton = createButton('Connect');
	connectButton.mousePressed(connectToBle);
	connectButton.position(20, 20);

	// Create an 'LED Switch' button and set its click event handler.
	const LEDSButton = createButton('LED Switch');
	LEDSButton.mousePressed(switchLED);
	LEDSButton.position(20, 40);
}

// Draw function continuously renders the 3D scene.
function draw() {
	background(100); // Set background color.

	// Apply 3D transformations based on IMU data.
	rotateX(ax);
	rotateY(ay);
	rotateZ(az);

	// Draw a 3D box.
	box(200, 200);
}

// Function to toggle the state of an LED when the 'LED Switch' button is clicked.
function switchLED() {
	if (bleConnected) {
		ledState = 1 - ledState; // Toggle LED state between 0 and 1.
		writeToCharacteristic(myCharacteristics[0], ledState); // Write the state to the first characteristic.
	}
}

// Function to initiate a connection to a BLE device when the 'Connect' button is clicked.
function connectToBle() {
	log('Requesting Bluetooth Device...');
	navigator.bluetooth.requestDevice({
		filters: [{
			services: [serviceUuid]
		}]
	})
	.then(device => {
		console.log('Connecting to GATT Server...');
		return device.gatt.connect();
	})
	.then(server => {
		console.log('Getting Service...');
		return server.getPrimaryService(serviceUuid);
	})
	.then(service => {
		bleConnected = true;
		console.log('Getting all Characteristics...');
		return service.getCharacteristics();
	})
	.then(characteristics => {
		for (const c in characteristics) {
			myCharacteristics.push(characteristics[c]);
			console.log('Getting all Notifications started');
			
			// Start receiving notifications and set up an event listener.
			characteristics[c].startNotifications().then(_ => {
				characteristics[c].addEventListener('characteristicvaluechanged', handleNotifications);
			});
			
			console.log(`${c}: ${characteristics[c]}`);
		}
	})
	.catch(error => {
		console.log('error: ' + error);
	});
}

// Function to write a value to a Bluetooth characteristic.
function writeToCharacteristic(characteristic, value) {
	let bufferToSend = Int8Array.of(value);
	characteristic.writeValueWithResponse(bufferToSend)
	.then(_ => {
		// Log success when the value is written.
		// console.log('> Characteristic changed to: ' + bufferToSend);
	})
	.catch(error => {
		log('Argh! ' + error); // Log an error if writing fails.
	});
}

// Function to handle notifications received from the Bluetooth device.
function handleNotifications(event) {
	let value = event.target.value;
	let x = value.getFloat32(0, true); // Get the first 4 bytes as a float.
	let y = value.getFloat32(4, true); // Get the next 4 bytes as a float.
	let z = value.getFloat32(8, true); // Get the next 4 bytes as a float.

	// Update IMU data with the received values.
	ax += x * 0.02;
	ay += y * 0.02;
	az += z * 0.02;
}
