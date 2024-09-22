#include "IR.h"

#include "BaseFunc.h"
#include "mods.h"

NecDecoder IR;
uint8_t data_pack;

void _comparison()
{
  data_pack = IR.readCommand();
  
  switch (data_pack)
  {
    case 162:           //1
    {
      _filling(base_colors.red);
    } break;

    case 98:            //2
    {
      _filling(base_colors.green);
    } break;

    case 226:           //3
    {
      _filling(base_colors.blue);
    } break;

    case 34:            //4
    {
      _filling(base_colors.cyan);
    } break;

    case 2:             //5
    {
      _filling(base_colors.pink);
    } break;

    case 194:           //6
    {
      _filling(base_colors.orange);
    } break;

    case 224:           //7
    {
      _filling(base_colors.violet);
    } break;

    case 168:           //8
    {
      _filling(base_colors.yellow);
    } break;

    case 144:           //9
    {
      _filling(base_colors.white);
    } break;

    case 152:           //0
    {
    } break;

    case 104:           //*
    {
      _off_on();
    } break;

    case 176:           //#
    {
      // xTaskCreate (_pulse, "effect_selector", 128, NULL, 0, NULL);
    } break;

    case 24:            //🠉
    {
      _change_brightness(true);
    } break;

    case 74:            //🠋
    {
      _change_brightness(false);
    } break;

    case 16:            //🠈
    {
      
    } break;

    case 90:            //🠊
    {
      
    } break;

    case 56:            //OK
    {
      
    } break;
  }
}

void _IRreg()
{
  IR.tick();

  if (IR.available()) 
    _comparison();
}
