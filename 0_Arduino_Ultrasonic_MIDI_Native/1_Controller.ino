uint8_t velocity = 100;
#define CH_NUM 1

void loop_controller()
{
  //This sends the control change message including the reading from the ultrasonic
  
  controlChange (0x0B, CH_NUM, velocity);
}

void controlChange(byte channel, byte control, byte value) {
  // First parameter is the event type (0x0B = control change).
  // Second parameter is the event type, combined with the channel.
  // Third parameter is the control number number (0-119).
  // Fourth parameter is the control value (0-127).

  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
