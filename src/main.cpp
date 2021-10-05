#include <Arduino.h>
#include <BleKeyboard.h>
// This library is for using BLE HID with your ESP32
// 
// This is not availble on the library manager so
// needs to be installed from Github
// https://github.com/T-vK/ESP32-BLE-Keyboard

#include <Keypad.h>
// This library is for interfacing with the 4x4 Matrix
// 
// Can be installed from the library manager, search for "keypad"
// and install the one by Mark Stanley and Alexander Brevig
// https://playground.arduino.cc/Code/Keypad/



// the library will return the character inside this array
// when the appropriate button is pressed.


const byte ROWS = 5; //four rows
const byte COLS = 16; //four columns

byte rowPins[ROWS] = {23, 19, 18, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 21, 32, 33 }; //connect to the column pinouts of the keypad


char keys[ROWS][COLS] = {
  {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', KEY_BACKSPACE, '+'},
  {KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\', KEY_DELETE},
  {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', "'"[0], KEY_RETURN, KEY_PAGE_UP},
  {KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_RIGHT_SHIFT, KEY_UP_ARROW, KEY_PAGE_DOWN},
  {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_RIGHT_CTRL, '#', '$', KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW},
};


// Creating instances of a keypad for matrix and BleKeyboard for keyboard
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
BleKeyboard bleKeyboard("BLE_Switcheroonie", "BLough", 100);

void setup() {
  Serial.begin(9600);
  bleKeyboard.begin();
}

// This will hold down all the following buttons.
/* void sendMacroCommand(uint8_t key) {
  bleKeyboard.press(KEY_LEFT_CTRL);
  bleKeyboard.press(KEY_LEFT_SHIFT);
  bleKeyboard.press(KEY_LEFT_ALT);
  bleKeyboard.press(key);
}  */

void loop() {
  char key = keypad.getKey();

  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
  if (bleKeyboard.isConnected() && key) {
    Serial.println(key);
    bleKeyboard.press(key);
    /* switch (key) {
      case 'C':
        sendMacroCommand('c');
        break;
      case 'D':
        sendMacroCommand('d');
        break; 
    }*/

    delay(10);
    bleKeyboard.releaseAll(); // this releases the buttons
  }
}
