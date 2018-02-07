/*
MIT License

Copyright (c) 2018 gdsports625@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

/*
 * Receive ASCII text from Serial1 and convert to USB HID report.
 * Send HID report out USB interface.
 *
 */

#include <Keyboard.h>

#if 0
/* Arduino Zero */
#define SERDEBUG  Serial1
#define USBEvent  Serial
#endif

#if 1
/* Trinket M0 or 32u4 */
//#define SERDEBUG  Serial
#define USBEvent  Serial1
#endif

char aLine[81];
uint8_t aLine_count = 0;

void setup()
{
#ifdef SERDEBUG
  SERDEBUG.begin(115200);
#endif
  USBEvent.begin(115200);
  aLine_count = 0;
}

uint8_t params2bin(char *buf, uint8_t *outbuf, uint8_t outbuf_len)
{
  char *p;
  uint8_t outbuf_count = 0;

  memset(outbuf, 0, outbuf_len);
  p = strtok(buf, ",");
  while (p != NULL && outbuf_count < outbuf_len) {
    *outbuf++ = strtoul(p, NULL, 10);
    outbuf_count++;
    p = strtok(NULL, ",");
  }
  return outbuf_count;
}

void loop()
{
#ifdef SERDEBUG
  if (SERDEBUG.available() > 0) {
    char c = SERDEBUG.read();
    USBEvent.write(c);
  }
#endif

  if (USBEvent.available() > 0) {
    char c = USBEvent.read();
#ifdef SERDEBUG
    SERDEBUG.print("c 0x"); SERDEBUG.println(c, HEX);
#endif
    if (c == '\n' || aLine_count >= sizeof(aLine)) {
      aLine[aLine_count] = '\0';
#ifdef SERDEBUG
      SERDEBUG.println(aLine);
#endif
      char command = aLine[0];
      uint8_t rawdata[8];
      uint8_t raw_len = params2bin(aLine+2, rawdata, sizeof(rawdata));
      aLine_count = 0;
      if (raw_len > 0) {
        switch (command) {
          // Keyboard HID report
          case 'K':
          case 'k':
            if (raw_len != 8) break;
            HID().SendReport(2, rawdata, sizeof(KeyReport));
            break;
            // Mouse HID report
          case 'M':
          case 'm':
            if (raw_len != 4) break;
            HID().SendReport(1, rawdata, 4);
            break;
            // Joystick????
          case 'J':
          case 'j':
            break;
          default:
            break;
        }
      }
    }
    else {
      aLine[aLine_count++] = c;
    }
  }
}
