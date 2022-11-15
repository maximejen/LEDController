/*
** BLE.h
**
** Made by Maxime JENNY
*/

#ifndef BLE_H_
# define BLE_H_

#include <Arduino.h>
#include <ArduinoBLE.h>

// LED Service
# define LED_SERVICE_UUID    "98294635-40dd-4094-a095-3464082ea944"
# define LED_PATTERN_UUID    "98294635-40dd-4094-a095-d866ad327621"
# define BRIGHTNESS_UUID     "98294635-40dd-4094-a095-0242ac120002"
# define FPS_UUID     		"98294635-40dd-4094-a095-0242ac120003"

void initBluetoothServer();

#endif /* BLE_H_ */