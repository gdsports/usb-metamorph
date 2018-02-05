# The USB Metamorph Project

Imagine plugging a USB keyboard into a small box then plugging
the small box into a computer. Pressing keys on the keyboard produces
MIDI CC messages.

Image plugging  a USB keyboard into a small box then plugging the
small box into two computers. Pressing keys on the keyboard sends
keystrokes to both computers.

The USB metamorph project explores connecting one ore more USB
controllers, host and device, in useful ways. The Adafruit
Trinket M0 makes it cheap and easy to experiment with multiple USB
controllers. The interconnection will use UART for simplicity but SPI
and I2C interfaces are available on the Trinket M0. The SAMD21 native
USB port is USB On-The-Go (OTG) which means it supports host and
device modes. To use USB host mode, all that is needed is a simple
cable.

The [Arduino USB host documentation](https://www.arduino.cc/en/Reference/USBHost)
refers to Arduino Due with no mention of the Zero/M0 SAMD21 boards. However,
the USB host examples for Due work on Trinket M0. The Arduino USB Host is
limited to USB keyboard, mouse, and ADK at the moment.

The Trinket M0 is very different from the much older Trinket. The
older Trinket does not have USB host capability.

The other Arduino USB host feature is based on the MAX3421E chip that
many more drivers for other USB devices but is more complex. This type
of USB host is not used in this project.

The Trinket M0 is based on the Atmel SAMD21 chip so other boards based
on the same chip probably have the same USB Host features but only the
Trinket M0 has been tested.

Examples of SAMD21 boards usable with the Arduino IDE.

* Arduino Zero, Arduino M0, and Arduino M0 Pro
* Arduino MKR series
* SparkFun SAMD21 mini breakout
* Adafruit Feather M0 series, Trinket M0

## USB Host Requirements

### USB OTG to USB host cable

The following cables are two examples. Similar cables are available from a
large number of vendors.

* https://www.sparkfun.com/products/14276
* https://www.adafruit.com/product/1099

This cable is required to plug in a keyboard or mouse. When this cable
is used, serial console output no longer available.

### USB serial cable

For serial console output, a USB serial cable is highly recommended.  Make sure
the cable uses 3.3V logic levels and 5V USB power out. The following cables are
two examples. Similar cables are available from a large number of vendors.

* https://www.adafruit.com/product/954
* https://www.sparkfun.com/products/12977

Plug this into the Trinket M0 UART Tx and Rx for serial console. This
cable can also be used to power the Trinket M0 and the keyboard or mouse.
Connect the 5V output from the cable to the Trinket M0 USB pin. And
connect ground to ground.

### Run the KeyboardController example

Upload and run the example.
Unplug the Trinket M0 from the PC.
Plug in the OTG USB host cable to the Trinket M0.
Plug in the USB keyboard to the OTG USB host cable.
Connect the USB serial cable to the PC. This will power up the Trinket
M0 and the USB keyboard.
Typing on the keyboard should produce output on the serial console.

NOTE: When the Trinket M0 is running in USB host mode, be sure to double click
the reset button when you want to upload a new sketch.


## Keyboad Pass Through

![Photo of USB keyboard pass through](https://github.com/gdsports/usb-metamorph/blob/master/images/usbkbdpassthru.jpg)

### Dataflow

USB keyboard > OTG to host cable > SAMD > UART Tx > UART Rx > 32u4 > USB > computer

### Hardware

USB keyboard or numeric keypad
USB OTG to host cable
SAMD mini board such as Adafruit Trinket M0
32u4 3.3V mini board such as SparkFun Pro Micro or Adafruit Itsy Bitsy
Proto board, hookup wire, solder, etc.

```
32u4        SAMD
====        ====
GND ------- GND
USB 5V ---- USB 5V
TX -------- RX
RX -------- TX
```

### Software

#### SAMD USB host source code

The USB host sketch is named KeyboardHm0 which stands for Keyboard Host for M0.
This program receives USB keyboard events from the USB OTG port in host mode
and sends them out a UART port.

#### 32u4 USB device/gadget source code

The USB device sketch is named USBSerPassThruLine. This program receives USB
keyboard events from a UART port and sends them out the 32u4 USB device/gadget
port.

### Variations

#### Keyboard Remapper

Swapping keys could be done on the SAMD since it has lots of memory for code
and data compared to the 32u4.

Example 1: Swap Windows and ALT keys.

Example 2: Swap Caps Lock and Ctrl.

Example 3: Dvorak key mapping.

#### Keyboard Cloner

![Photo of USB keyboard cloner](https://github.com/gdsports/usb-metamorph/blob/master/images/usbkbdcloner.jpg)

A simple variation of the pass through is to send the keyboard events to more
than one 32u4 at the same time.

```
32u4 A      SAMD    32u4 B  32u4 C  32u4 ...
======      ====    ======  ======  ========
GND ------- GND --- GND --- GND --- GND
USB 5V ---- USB 5V
TX -------- RX
RX -------- TX ---- RX ---- RX ---- RX
```

## USB Keyboard to MIDI Button Controller

TBD, maybe

## IP KVM

TBD, maybe

