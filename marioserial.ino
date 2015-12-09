/*  Marioserial: use this to copy paste level codes from a pc to a wii u
 *   It emulates a USB keyboard on the wiiu, while communicating to a pc with ttl serial
 *   The pc sends messages of the form "1234567890123456!" (16 characters followed by exclamation mark)
 *   If it's the right length, we send it as keyboard input over usb
 *   Then we echo them back over serial with messages about whether we sent it on or not (for debug)
 *   
*/

#include <HID-Project.h>

void setup() {
  // start serial port at 9600 bps:
  Serial1.begin(9600);

  // set up keyboard emulation
  pinMode(13, OUTPUT);
  BootKeyboard.begin();
}

void loop() {
  while (1) {
    if ( Serial1.available()) {
       String msg = Serial1.readStringUntil('!');
       Serial1.println("\"" + msg + "\"");
       if (msg.length() == 16) {
         Serial1.println("sending code");
         BootKeyboard.print(msg);         
       } else {
         Serial1.println("invalid code length (expected 16)");
       }
    }
    delay(50);
  }
 
}
