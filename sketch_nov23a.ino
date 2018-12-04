//
#define NOTE_FS3 2702
#define NOTE_G3  2551
#define NOTE_C4  1908
#define NOTE_E4  1515
#define NOTE_FS4 1351
#define NOTE_G4  1275
#define NOTE_A4  1136

int melody[] = {NOTE_C4, NOTE_E4, NOTE_FS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_G3, NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3};// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2,4,4,8,2,4,4,4,8,8,8,4
};


void setup() {

 /*TCCR0A |= (1 << WGM01); 
 TCCR0A |= (1 << COM0B0); 
 TCCR0B |= (1 << CS00); 
 OCR0A = 9; */
 
 TCCR1B = (1 << WGM12); 
 TCCR1A = (1 << COM1A0); 
 TCCR1B |= (1 << CS10); 
 OCR1A = 4 ;

 //DDRB |= (1 << PB1);
}

void transmitBeep(uint16_t wavelength, uint32_t duration) {
 
 for(int elapsed = 0; elapsed < duration; elapsed += wavelength){

 for (int i = 0; i < wavelength; i++){
 delayMicroseconds(1);
 }
 DDRB ^= (1 <<PB1);
 
 }
 
}

void loop() {
   // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 12; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    transmitBeep( melody[thisNote], noteDuration*1000);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);

}
}

