#include "main.h"
#include "Metronome.h"
#include "TouchChannel.h"
#include "GlobalControl.h"
#include "Degrees.h"
#include "CAP1208.h"
#include "MIDI.h"
#include "TCA9544A.h"
#include "MCP23017.h"
#include "MCP4922.h"
#include "TLC59116.h"


I2C i2c1(I2C_SDA, I2C_SCL);
I2C i2c3(I2C3_SDA, I2C3_SCL);

Ticker ticker;
Timer timer;
MIDI midi;
Metronome metronome(LOOP_STEP_LED_PIN, LOOP_START_LED_PIN);
InterruptIn extClockInput(EXT_CLOCK_INPUT);

MCP4922 dacA(SPI2_MOSI, SPI2_SCK, DAC_A_CS);
MCP4922 dacB(SPI2_MOSI, SPI2_SCK, DAC_B_CS);

MCP23017 io(&i2c3, MCP23017_DEGREES_ADDR);
TLC59116 ledsA(&i2c3, TLC59116_CHAN_A_ADDR);
TLC59116 ledsB(&i2c3, TLC59116_CHAN_B_ADDR);
TLC59116 ledsC(&i2c3, TLC59116_CHAN_C_ADDR);
TLC59116 ledsD(&i2c3, TLC59116_CHAN_D_ADDR);
TCA9544A i2cMux(&i2c1, TCA9544A_ADDR);

// CAP1208 touchCTRL(&i2c3);
// CAP1208 touchA(&i2c1, &i2cMux, 0);
// CAP1208 touchB(&i2c1, &i2cMux, 1);
// CAP1208 touchC(&i2c1, &i2cMux, 2);
// CAP1208 touchD(&i2c1, &i2cMux, 3);

Degrees degrees(DEGREES_INT, &io);

// TouchChannel channelA(0, GATE_OUT_A, CHAN_INT_A, TOUCH_INT_A, CTRL_LED_A, ADC_A, &touchA, &degrees, &ioA, &midi, &metronome, &dacA, MCP4922::DAC_A);
// TouchChannel channelB(1, GATE_OUT_B, CHAN_INT_B, TOUCH_INT_B, CTRL_LED_B, ADC_B, &touchB, &degrees, &ioB, &midi, &metronome, &dacA, MCP4922::DAC_B);
// TouchChannel channelC(2, GATE_OUT_C, CHAN_INT_C, TOUCH_INT_C, CTRL_LED_C, ADC_C, &touchC, &degrees, &ioC, &midi, &metronome, &dacB, MCP4922::DAC_A);
// TouchChannel channelD(3, GATE_OUT_D, CHAN_INT_D, TOUCH_INT_D, CTRL_LED_D, ADC_D, &touchD, &degrees, &ioD, &midi, &metronome, &dacB, MCP4922::DAC_B);

// GlobalControl globalCTRL(&touchCTRL, TOUCH_INT_CTRL, DISPLAY_DATA, DISPLAY_CLK, DISPLAY_LATCH, ENCODER_CHAN_A, ENCODER_CHAN_B, ENCODER_BTN, &channelA, &channelB, &channelC, &channelD, &metronome);

int newClockTimeStamp;
int lastClockTimeStamp;
int clockPeriod;

void tick() {
  metronome.tick();
  // channelA.tickClock();
  // channelB.tickClock();
  // channelC.tickClock();
  // channelD.tickClock();
}

void extTick() {
  // you need to advance every quarter note when an external clock signal is detected
  // additionally, set the ticker timer to a division of the input pulse duration / PPQN
  // the ticker will handle precise timing between quarter notes, and this interupt will advance each channels step

  lastClockTimeStamp = newClockTimeStamp;
  newClockTimeStamp = timer.read_us();
  clockPeriod = newClockTimeStamp - lastClockTimeStamp;
  metronome.step();
  // channelA.stepClock();
  // channelB.stepClock();
  // channelC.stepClock();
  // channelD.stepClock();

  ticker.attach_us(&tick, clockPeriod / PPQN);  // potentially write this as a flag and update in main loop
}

DigitalOut ctrlLedA(PB_7);
TLC59116 octLeds(&i2c3, TLC59116_OCT_LEDS_ADDR);

int main() {
  
  

  degrees.init();

  ctrlLedA = 1;
  octLeds.initialize();
  octLeds.setLedOutput(0, TLC59116::LedState::ON);
  wait_ms(1000);
  octLeds.setLedOutput(1, TLC59116::LedState::ON);
  wait_ms(1000);
  octLeds.setLedOutput(2, TLC59116::LedState::ON);
  wait_ms(1000);
  octLeds.setLedOutput(3, TLC59116::LedState::ON);
  octLeds.setLedOutput(4, TLC59116::LedState::ON);
  octLeds.setLedOutput(5, TLC59116::LedState::ON);
  octLeds.setLedOutput(6, TLC59116::LedState::ON);
  octLeds.setLedOutput(7, TLC59116::LedState::ON);
  octLeds.setLedOutput(8, TLC59116::LedState::PWM, 100);
  octLeds.setLedOutput(9, TLC59116::LedState::PWM, 20);
  octLeds.setLedOutput(10, TLC59116::LedState::PWM, 255);
  octLeds.setLedOutput(11, TLC59116::LedState::PWM, 50);
  // channelA.init();
  // channelB.init();
  // channelC.init();
  // channelD.init();

  // globalCTRL.init();


  // timer.start();
  // newClockTimeStamp = timer.read_us();
  // metronome.init();

  // ticker.attach_us(&tick, (1000000/2) / PPQN); //approx 120 bpm
  // extClockInput.rise(&extTick);

  while(1) {
    ctrlLedA = 0;
    octLeds.setLedPWM(8, 50);
    wait_ms(1000);
    ctrlLedA = 1;
    octLeds.setLedPWM(8, 100);
    wait_ms(1000);
    

    // degrees.poll();
    // channelA.poll();
    // channelB.poll();
    // channelC.poll();
    // channelD.poll();

    // globalCTRL.poll();
    
  }
}


// NOTE: You may be able to create a seperate "thread" via the Thread api for handling the event loop