#define CHANNEL_NUM 0

int noteCount = 0;
int playThisNote = 0;

#define NUM_NOTES 4
const byte notePitches[NUM_NOTES] = {60, 50, 52, 53};

#define NOTE_LENGTH 30
#define NOTE_BREAK 10

void loop_notes()
{
  //Simply loops the note sequence
  if (noteCount>NOTE_LENGTH+NOTE_BREAK)
  {
    noteCount = 0;
    playThisNote++;
    if(playThisNote==4) playThisNote=0;
  }
  
  if (noteCount==0){
    noteOn(CHANNEL_NUM, notePitches[playThisNote], 127);    
  }
  else if (noteCount==NOTE_LENGTH)
  {
    noteOff(CHANNEL_NUM, notePitches[playThisNote], 0);
  }
  
  noteCount++;
}

void noteOn(byte channel, byte pitch, byte velocity) {
  //Play an on note
  
  // First parameter is the event type (0x09 = note on, 0x08 = note off).
  // Second parameter is note-on/note-off, combined with the channel.
  // Channel can be anything between 0-15. Typically reported to the user as 1-16.
  // Third parameter is the note number (48 = middle C).
  // Fourth parameter is the velocity (64 = normal, 127 = fastest).

  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);

  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  //Play an off note
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);

  MidiUSB.flush();
}
