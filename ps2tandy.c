/* 
 * ps2tandy.c
 *
 * PS2 Keyboard on a Tandy 1000A.
 *
 * (c) Scott Baker, https://www.smbaker.com/
 */

// Some of the PS2 code originally based on keyboard.c
//   for NerdKits with ATmega168
//   hevans@nerdkits.com


//#define F_CPU 14745600

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include <util/delay.h>

#include "tandy_scancode_map.h"

//PIN configuration
//PB4          -  Tandy Busy
//PB3          -  Tandy Data
//PB2          -  Tandy CLK
//PB1 (PCINT1) -  PS2 Keyboard CLK
//PB0          -  PS2 Keyboard DATA

#define TANDY_BUSY (1<<PB4)
#define TANDY_DATA (1<<PB3)
#define TANDY_CLK  (1<<PB2)

#define TANDY_CLK_LOW PORTB &= ~TANDY_CLK
#define TANDY_CLK_HIGH PORTB |= TANDY_CLK
#define TANDY_DATA_LOW PORTB &= ~TANDY_DATA
#define TANDY_DATA_HIGH PORTB |= TANDY_DATA

#define PS2_CLK (1<<PB1)
#define PS2_DATA (1<<PB0)

#define PS2_CAPSLOCK_SCANCODE 0x58
#define PS2_NUMLOCK_SCANCODE 0x77
#define PS2_PAUSE_SCANCODE 0x77
#define PS2_BACKSLASH_SCANCODE 0x5D
#define PS2_LSHIFT_SCANCODE 0x12
#define PS2_RSHIFT_SCANCODE 0x59
#define PS2_BACKQUOTE_SCANCODE 0x0E

#define TANDY_KP2_SCANCODE 0x50
#define TANDY_KP4_SCANCODE 0x4B
#define TANDY_KP7_SCANCODE 0x47
#define TANDY_KP8_SCANCODE 0x48
#define TANDY_BREAK_SCANCODE 0x54

#define CAPSLOCK_LEDBIT 0x04
#define NUMLOCK_LEDBIT 0x02

#define LOW 0
#define HIGH 1

volatile uint8_t kbd_data;
volatile uint8_t char_waiting;
volatile uint8_t up_event, down_event;
volatile uint8_t ack_event, nak_event;
volatile uint8_t next_extended, e1flag, up_extended, down_extended;
volatile uint8_t key_state[256];
volatile uint8_t disable_isr;
volatile uint8_t shift_down;
uint8_t started;
uint8_t bit_count;
uint8_t shift;
uint8_t caps_lock;
uint8_t extended;
uint8_t release;
uint8_t capslock;
uint8_t numlock;
uint8_t leds;
uint8_t ps2_argument;
uint8_t ps2_have_argument;

void map_and_send_scancode(uint8_t data, uint8_t extended, uint8_t modifier);

ISR(PCINT0_vect){

  //make sure clock line is low, if not ignore this transition
  if(PINB & (1<<PB1)){
    return;
  }

  if (disable_isr) {
    return;
  }

  //if we have not started, check for start bit on DATA line
  if(!started){
    if ( (PINB & (1<<PB0)) == 0 ) {
      started = 1;
      bit_count = 0;
      kbd_data = 0;
      //printf_P(PSTR("%d"),started);
      return;
    }
  } else if(bit_count < 8) { //we started, read in the new bit
    //put a 1 in the right place of kdb_data if PC2 is high, leave
    //a 0 otherwise
    if(PINB & (1<<PB0)){
      kbd_data |= (1<<bit_count);
    }
    bit_count++;
    return;
  } else if(bit_count == 8){ //pairty bit
    //not implemented
    bit_count++;
    return;
  } else {  //stop bit
    //should check to make sure DATA line is high, what to do if not?
    started = 0;
    bit_count = 0;
  }

  if(kbd_data == 0xF0){ //release code
    release = 1;
    kbd_data = 0;
    return;
  } else if (kbd_data == 0xFA) {
    ack_event = 1;
    return;
  } else if (kbd_data == 0xFE) {
    nak_event = 1;
    return;
  } else if (kbd_data == 0xE0) { //extended code
    next_extended = 1;
    return;
  } else if (kbd_data == 0xE1) { //the other extended code (pause/break)
    e1flag = 1;
    return;
  } else { //not a special character
    if ((e1flag) && (kbd_data!=0x77) && (kbd_data!=0x14)) {
      // E1,14,77,E1,F0,14,F0,77 is the pause sequence.
      // If we see something else, reset the flag.
      e1flag = 0;
    }
    if (release) { //we were in release mode - exit release mode
      if ((kbd_data == PS2_LSHIFT_SCANCODE) || (kbd_data == PS2_RSHIFT_SCANCODE)) {
          shift_down = 0;
      }
      release = 0;
      up_event = kbd_data;
      up_extended = next_extended;
      next_extended = 0;
      key_state[kbd_data] = 0;
    } else {
      if ((kbd_data == PS2_LSHIFT_SCANCODE) || (kbd_data == PS2_RSHIFT_SCANCODE)) {
          shift_down = kbd_data;
      }
      down_event = kbd_data;
      down_extended = next_extended;
      next_extended = 0;
      char_waiting = 1;
      key_state[kbd_data] = 1;
    }
  }
}

void led_init()
{
  // make pb5 an output
  DDRB |= (1<<PB5);
}

void led_on()
{
  PORTB |= (1<<PB5);
}

void led_off()
{
  PORTB &= ~(1<<PB5);
}

uint8_t read_char(){
  while(!char_waiting){
     //wait for a character
  }
  char_waiting = 0;
  return kbd_data;
}

void init_keyboard()
{
  uint8_t i;

  for (i=0; i<255; i++) {
    key_state[i] = 0;
  }

  started = 0;
  kbd_data = 0;
  bit_count = 0;
  next_extended = 0;
  e1flag = 0;
  down_event = 0;
  up_event = 0;
  disable_isr = 0;
  shift_down = 0;
  ps2_have_argument = 0;
  ack_event = 0;
  nak_event = 0;

  //make PB1 input pin
  //DDRB &= ~(1<<PB1);
  //turn on pullup resistor
  PORTB |= (1<<PB1);

  //Enable PIN Change Interrupt 1 - This enables interrupts on pins
  GIMSK |= (1<<PCIE);

  //Set the mask on Pin change interrupt 1 so that only PCINT1 (PB1) triggers
  //the interrupt.
  PCMSK |= (1<<PCINT1);
}

uint8_t wait_for_bit(uint8_t bit, uint8_t highlow, uint16_t ms)
{
    if (highlow != LOW) {
      highlow = bit;
    }

    uint16_t i;
    for (i=0; i<ms*1000; i++) {
      if ((PINB & bit) == highlow) {
        return 1;
      }
      _delay_us(1);
    }
    // timeout
    return 0;
}

uint8_t compute_parity(uint16_t n) 
{ 
    uint8_t parity = 0; 
    while (n) 
    { 
        parity = !parity; 
        n      = n & (n - 1); 
    }         
    return parity; 
} 

void ps2_clk_low()
{
  PORTB &= ~PS2_CLK;
  DDRB |= PS2_CLK;
}

void ps2_clk_release()
{
  // open-collector output; to set high we just release
  DDRB &= ~PS2_CLK;
}

void ps2_data_low()
{
  PORTB &= ~PS2_DATA;
  DDRB |= PS2_DATA;
}

void ps2_data_release()
{
  // open-collector output; to set high we just release
  DDRB &= ~PS2_DATA;
}

uint8_t ps2_send_byte(uint16_t b)
{
    int i;

    wait_for_bit(PS2_CLK, HIGH, 2);

    // bring clock low
    ps2_clk_low();
    // wait 100us
    _delay_us(300);
    // bring data low
    ps2_data_low();
    _delay_us(1);
    // return clock to input state
    ps2_clk_release();

    // wait for keyboard to bring clock low, up to 15ms
    if (!wait_for_bit(PS2_CLK, LOW, 15)) {
      ps2_data_release();
      return 0;
    }

    if (!compute_parity(b)) {
      b |= 0x100;
    }

    // 8 data bits + one parity bit, assume the parity is in bit position 8
    for (i=0; i<9; i++) {
      // set the data bit
      if ((b&1)==1) {
        ps2_data_release();
      } else {
        ps2_data_low();
      }
      // wait for clock to go high
      if (!wait_for_bit(PS2_CLK, HIGH, 2)) {
        ps2_data_release();
        return 0;
      }
      if (!wait_for_bit(PS2_CLK, LOW, 2)) {
        ps2_data_release();
        return 0;
      }
      b = b >> 1;
    }
    
    // return data to inptu state
    ps2_data_release();

    // wait for the ack
    if (!wait_for_bit(PS2_DATA, LOW, 2)) {
      return 0;
    }
    if (!wait_for_bit(PS2_CLK, LOW, 2)) {
      return 0;
    }

    return 1;
}

void ps2_send_command_argument(uint8_t command, uint8_t argument)
{
  disable_isr = 1;
  if (ps2_send_byte(command)) {
      ps2_argument = argument;
      ps2_have_argument = 1;
  }
  disable_isr = 0;
}

void ps2_send_argument(uint8_t arg)
{
  disable_isr = 1;
  ps2_send_byte(ps2_argument);
  disable_isr = 0;
}

void tandy_init()
{
  // make clock and data outputs
  DDRB |= TANDY_CLK;
  DDRB |= TANDY_DATA;
  // default clock state is low
  TANDY_CLK_LOW;
  // default data state is high
  TANDY_DATA_HIGH;
}

void tandy_send(uint8_t data)
{
  int i;

  // wait for non-busy state
  while ((PORTB && TANDY_BUSY)==0) {
    // do nothing
  }

  led_on();

  for (i=0; i<8; i++) {
    if (data&1) {
      TANDY_DATA_HIGH;
    } else {
      TANDY_DATA_LOW;
    }
    // based on timing at https://www.lo-tech.co.uk/w/images/a/a5/Tandy-1000-Keyboard-Protocol-Sample.png
    _delay_us(5);
    TANDY_CLK_HIGH;
    _delay_us(8);
    TANDY_DATA_HIGH;
    _delay_us(4.5);
    TANDY_CLK_LOW;
    _delay_us(9.5);
    data = data >> 1;
  }

  TANDY_DATA_LOW;
  _delay_us(5);
  TANDY_DATA_HIGH;
  // give some time for the LED to be visible
  _delay_ms(1);

  led_off();
}

void tandy_send_without_shift(uint8_t data)
{
    uint8_t need_shift, need_unshift;
    uint8_t wrong, shift_to_use;

    // Note: Assumes the user only uses one shift key at a time.
    //    If the user messes with both shift keys, could get
    //    confused.
    
    need_shift = 0;
    need_unshift = 0;
    wrong = (shift_down != 0);
    if (numlock) {
        wrong = !wrong;
    }
    shift_to_use = shift_down;
    if (shift_to_use == 0) {
      shift_to_use = PS2_LSHIFT_SCANCODE;
    }
    if (wrong) {
        if (shift_down != 0) {
            // break the shift
            map_and_send_scancode(shift_to_use, 0, 0x80);
            need_shift = 1;
        } else {
            // make the shift
            map_and_send_scancode(shift_to_use, 0, 0);
            need_unshift = 1;          
        }
    }
      
    tandy_send(data);
    
    if (need_shift) {
        // restore the shift by making it
        map_and_send_scancode(shift_to_use, 0, 0);
    } else if (need_unshift) {
        // restore the shift by breaking it
        map_and_send_scancode(shift_to_use, 0, 0x80);
    }
}

void map_and_send_scancode(uint8_t data, uint8_t extended, uint8_t modifier)
{
    uint8_t scancode;

    if (data == PS2_BACKSLASH_SCANCODE) {
      if (shift_down==0) {
          tandy_send_without_shift(TANDY_KP7_SCANCODE | modifier);  // KP7 or backslash
      } else {
          tandy_send_without_shift(TANDY_KP4_SCANCODE | modifier);  // KP4 or vertical bar
      }
      return;
    }

    if (data == PS2_BACKQUOTE_SCANCODE) {
      if (shift_down==0) {
          tandy_send_without_shift(TANDY_KP2_SCANCODE | modifier);  // KP2 or backquote
      } else {
          tandy_send_without_shift(TANDY_KP8_SCANCODE | modifier);  // KP8 or tilde
      }
      return;
    }

    if (extended!=0) {
        scancode = pgm_read_byte(&(extcode_map[data]));
    } else {
        scancode = pgm_read_byte(&(scancode_map[data]));
    }

    if (scancode!=0) {
        tandy_send(scancode | modifier);
    }
}

void handle_toggle(uint8_t state, uint8_t scancode, uint8_t ledbit)
{
  if (state) {
    // send the make
    map_and_send_scancode(scancode, 0, 0);
    // update the leds
    leds = leds | ledbit;
    ps2_send_command_argument(0xED, leds);
  } else {
    // send the break
    map_and_send_scancode(scancode, 0, 0x80);
    // update the leds
    leds = leds & (~ledbit);
    ps2_send_command_argument(0xED, leds);
  }
}

int main() {
  init_keyboard();

  tandy_init();

  led_init();

  //enable interrupts
  sei();

  up_event = 0;
  down_event = 0;
  leds = 0;

  while(1) {
    if (up_event != 0) {
        if ((e1flag) && (up_event == PS2_PAUSE_SCANCODE)) {
            e1flag = 0;
            tandy_send(TANDY_BREAK_SCANCODE | 0x80);
        } else if (up_event == PS2_CAPSLOCK_SCANCODE) {
            capslock = !capslock;
            handle_toggle(capslock, up_event, CAPSLOCK_LEDBIT);
        } else if (up_event == PS2_NUMLOCK_SCANCODE) {
            numlock = !numlock;
            handle_toggle(numlock, up_event, NUMLOCK_LEDBIT);
        } else {
            map_and_send_scancode(up_event, up_extended, 0x80);
        }
        up_event = 0;
    }
    if (down_event != 0) {
        if ((e1flag) && (down_event == PS2_PAUSE_SCANCODE)) {
            e1flag = 0;
            tandy_send(TANDY_BREAK_SCANCODE);
        } else if ((down_event == PS2_CAPSLOCK_SCANCODE) || (down_event == PS2_NUMLOCK_SCANCODE)) {
            // ignore; we'll handle it on the up event
        } else {
            map_and_send_scancode(down_event, down_extended, 0);
        }
        down_event = 0;
    }
    if (ack_event != 0) {
      if (ps2_have_argument) {
        ps2_send_argument(ps2_argument);
        ps2_have_argument = 0;
      }
      ack_event = 0;
    }
    if (nak_event != 0) {
        ps2_have_argument = 0;
        nak_event = 0;
    }
  }

  return 0;
}
