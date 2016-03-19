#include <ExampleLib.h>

ExampleLib ch_inst(13);

void setup()
{
}

void loop()
{
  ch_inst.on(); 
  delay(3000);
  ch_inst.off(); 
  delay(3000);
  ch_inst.blink(1000); 
}
