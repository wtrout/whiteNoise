/*
Uses a 16-bit Fibonaci LFSR to generate pseudo-random noise: x^16 + x^14 + x^13 + x^11 + 1 (convention seems to count from one).
Coloring is applied similarly to the Voss-McCartney pink noise concept except only one LFSR is used to reduce overhead.
Eight output pins are used and sample the LFSR but at staggered, binary weighted intervals (somewhat like grey code).

The LFSR only uses the top byte for feedback so it is copied to an 8bit temporary value. The register is then
shifted by one. The XOR feedback is pre-computed into a lookup table so that the upper byte used as an index
returns the value to add to the bottom of the LFSR. To stagger the bit toggles, a bit value table is used to
select only the desired bit to update from the lfsr which is XORed into the GPIO output register.

The counter uses another GPIO output register (PORTB) to measure performance with a logic analyzer. I think
the loop runs 36 clock cycles on the 328p as I read 222 kHz on pin 8.
*/



const uint8_t lookup[] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0};
const uint8_t update[] = {4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,16,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,1,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,16,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,32,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,16,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,1,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,16,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,2,4,128,4,8,4,128,4,64,4,128,4,8,4,128,4,32};
uint16_t lfsr;
uint8_t upper;


void setup(){
    lfsr = random(1,255);
    DDRD = 0xFF;
    pinMode(8, OUTPUT);
}


void loop(){
    // 36 cycles
    memcpy((void*)&upper, (void*)&lfsr+1, 1);
    lfsr <<= 1;
    lfsr += lookup[upper];
    PORTD ^= (lfsr & update[PORTB++]);

    // Replace PORTB with a uint8_t var; just for testing

}