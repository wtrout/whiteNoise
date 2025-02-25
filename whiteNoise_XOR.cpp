

uint16_t lfsr;

//uint8_t update[] = {0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,7};
const uint8_t update[] = {2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,1,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,6,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,1,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,4,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,1,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,6,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,1,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,3,2,0,2,5,2,0,2,7,2,0,2,5,2,0,2,4};
const uint8_t lookup[] = {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0};
const uint8_t bits[] = {1,2,4,8,16,32,64,128};

uint8_t state;

inline void shift() __attribute__((always_inline));
inline void updateBit() __attribute__((always_inline));

void shift(){
    lfsr ^= lfsr >> 7;
    lfsr ^= lfsr << 9;
    lfsr ^= lfsr >> 13;
}

void updateBit(uint8_t i){
    state ^= (lfsr & bits[i]);
    PORTD = state;
}

void setup(){
    lfsr = random(0,255);
    state = lfsr;
    DDRD = 0xFF;
    //pinMode(8, OUTPUT);
}


void loop(){
    static uint8_t c = 0;
    shift();
    updateBit(update[c]);
    //PORTB = (c&0x01);
    c++;

}