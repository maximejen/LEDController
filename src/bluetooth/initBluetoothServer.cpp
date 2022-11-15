//#include <BLEDevice.h>
#include "Arduino.h"
#include "BLE.h"
#include "FastLED.h"

extern uint8_t gCurrentPatternNumber; // Index number of which pattern is current
extern uint8_t gBrightnessLevel;

BLEService ledService(LED_SERVICE_UUID);
BLECharacteristic ledPatternCharacteristic(LED_PATTERN_UUID, BLERead | BLEWrite | BLEWriteWithoutResponse,
										   sizeof(uint8_t));

BLECharacteristic brightnessCharacteristic(BRIGHTNESS_UUID, BLERead | BLEWrite | BLEWriteWithoutResponse,
										   sizeof(uint8_t));

void connectHandler(BLEDevice central) {
	// central connected event handler
	Serial.print("Connected event, central: ");
	Serial.println(central.deviceName());
	// stop the advertisement for the device on Connection of device.
	BLE.setConnectable(false);
}

void disconnectHandler(BLEDevice central) {
	// central disconnected event handler
	Serial.print("Disconnected event, central: ");
	Serial.println(central.deviceName());
	// restart the advertisement for the device on Disconnection of device.
	BLE.setConnectable(true);
}

void onPatternCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
	(void) central;
	Serial.println(characteristic.uuid());
	// central wrote new value to characteristic, update LED
	Serial.print("ledPatternCharacteristic write : ");
	Serial.println(*characteristic.value() % 6);
	gCurrentPatternNumber = *characteristic.value() % 6;
}

void onBrightnessCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
	(void) central;
	uint8_t tmp = 0;
	characteristic.readValue(&tmp, sizeof (uint8_t));
	Serial.println(characteristic.uuid());
	// central wrote new value to characteristic, update LED
	Serial.print("brightnessCharacteristic write : ");
	Serial.print(tmp);
	Serial.print(" (");
	Serial.print(tmp * 100 / 255);
	Serial.println("%)");
	gBrightnessLevel = tmp;
	FastLED.setBrightness(gBrightnessLevel);
}

void initBluetoothServer() {
	if (!BLE.begin()) {
		Serial.println("starting Bluetooth® Low Energy module failed!");

		while (1);
	}
	BLE.setLocalName("(MyESP32)");
	BLE.setDeviceName("LEDController");
	// assign event handlers for connected, disconnected to peripheral
	BLE.setEventHandler(BLEConnected, connectHandler);
	BLE.setEventHandler(BLEDisconnected, disconnectHandler);

	BLE.setAdvertisedService(ledService);

	ledService.addCharacteristic(ledPatternCharacteristic);
	ledPatternCharacteristic.setEventHandler(BLEWritten, onPatternCharacteristicWritten);
	ledPatternCharacteristic.writeValue(gCurrentPatternNumber, sizeof(uint8_t));

	ledService.addCharacteristic(brightnessCharacteristic);
	brightnessCharacteristic.setEventHandler(BLEWritten, onBrightnessCharacteristicWritten);
	brightnessCharacteristic.writeValue(gBrightnessLevel, sizeof(uint8_t));

	BLE.addService(ledService);
	BLE.advertise();
	Serial.println("Bluetooth® device active, waiting for connections...");
}
