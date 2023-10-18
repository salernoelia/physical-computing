let bleConnected = false;
const serviceUuid = "c2575d0e-959f-489e-a917-f5778e802eba";
let myCharacteristics = [];
let ledState = 0;
//IMU data 
let ax = 0.0;
let ay = 0.0;
let az = 0.0;

function setup() {
	createCanvas(400, 400, WEBGL);
	// Create a 'Connect' button
	const connectButton = createButton('Connect')
	connectButton.mousePressed(connectToBle);
	connectButton.position(20, 20);
	// led button
	const LEDSButton = createButton('LED Switch')
	LEDSButton.mousePressed(switchLED);
	LEDSButton.position(20, 40);
}

function draw() {
	background(100);
	normalMaterial();
	rotateX(ax);
	rotateY(ay);
	rotateZ(az);
	box(200, 200);
}


function switchLED() {
	if (bleConnected) {
		ledState = 1 - ledState; // toggle value between 0 and 1
		writeToCharacteristic(myCharacteristics[0], ledState) // write to first Characteristic
	}
}

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

function writeToCharacteristic(characteristic, value) {
	let bufferToSend = Int8Array.of(value);
	characteristic.writeValueWithResponse(bufferToSend)
		.then(_ => {
			//		console.log('> Characteristic changed to: ' + bufferToSend);
		})
		.catch(error => {
			log('Argh! ' + error);
		});
}

function handleNotifications(event) {
	let value = event.target.value;
	let x = value.getFloat32(0, true); // get the first 4 bytes 
	let y = value.getFloat32(4, true); // the next first 4 bytes
	let z = value.getFloat32(8, true); // the next first 4 bytes
	ax += x * 0.02 
	ay += y * 0.02; 
	az += z * 0.02; 
}