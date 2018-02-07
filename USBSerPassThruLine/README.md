# USB Serial to USB Pass Through

USBSerPassThruLine receives keyboard and mouse events from the serial port and
send them out the USB port.

In the first draft, without changing the core USB files, the USB keyboard did
not work when the computer is in the BIOS. Some older versions of Windows also
did not accept the Arduino USB keyboard. This is caused by the Arduino USB
descriptors. The default descriptors expose a USB CDC ACM serial port as well
as the HID device for keyboard. This confuses older versions of Windows and
BIOS.

The changes to the core files remove the USB CDC ACM serial port so the Arduino
looks like a plain old USB keyboard.

One directory must be moved before compiling the sketch. Move the HID
directory/folder to sketchbook/libraries. This version will override the
default HID library.

The core files are from Arduino IDE version 1.8.5. They may not be compatible
with any other version.
