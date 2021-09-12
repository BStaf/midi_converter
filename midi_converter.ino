/*
 *******************************************************************************
 * USB-MIDI to Legacy Serial MIDI converter
 * Copyright (C) 2012-2021 Yuuichi Akagawa
 *
 * Idea from LPK25 USB-MIDI to Serial MIDI converter
 *   by Collin Cunningham - makezine.com, narbotic.com
 *
 * This is sample program. Do not expect perfect behavior.
 *******************************************************************************
 */

#include <usbh_midi.h>
#include <usbhub.h>
#include <MIDIUSB.h>

//#ifdef USBCON
//#define _MIDI_SERIAL_PORT Serial1
//#else
#define _MIDI_SERIAL_PORT Serial
//#endif

// Set to 1 if you want to wait for the Serial MIDI transmission to complete.
// For more information, see https://github.com/felis/USB_Host_Shield_2.0/issues/570
#define ENABLE_MIDI_SERIAL_FLUSH 0

//////////////////////////
// MIDI Pin assign
// 2 : GND
// 4 : +5V(Vcc) with 220ohm
// 5 : TX
//////////////////////////

USB Usb;
USBH_MIDI  Midi(&Usb);

void MIDI_poll();

void setup()
{
  //Serial.begin(9600);
  _MIDI_SERIAL_PORT.begin(31250);

  if (Usb.Init() == -1) {
    while (1); //halt
  }//if (Usb.Init() == -1...
  delay( 200 );
}

void loop()
{
  Usb.Task();

  if ( Midi ) {
    MIDI_poll();
  }
  //delay(1ms) if you want
  //delayMicroseconds(1000);
}

// Poll USB MIDI Controler and send to serial MIDI
void MIDI_poll()
{
  char buf[16];
  uint8_t bufMidi[20];
  uint16_t  rcvd;

  if (Midi.RecvData( &rcvd,  bufMidi) == 0 ) {
    //for (int i = 0; i < rcvd; i++) {
 
    _MIDI_SERIAL_PORT.write(bufMidi, rcvd);
    MidiUSB.write(bufMidi, rcvd);
    MidiUSB.flush();
  }
//#if ENABLE_MIDI_SERIAL_FLUSH
  //    _MIDI_SERIAL_PORT.flush();
  //    MidiUSB.write(outBuf, size);
   //   MidiUSB.Flush();
//#endif

}
