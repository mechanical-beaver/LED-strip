#include "mods.h"

#include "IR.h"
#include "BaseFunc.h"


uint8_t fire_random(uint8_t _value, uint8_t _step);
uint8_t minValue(uint8_t value1, uint8_t value2, uint8_t value3 = 0, uint8_t value4 = 0);
uint8_t maxValue(uint8_t value1, uint8_t value2, uint8_t value3);
uint8_t wrapped_distance(uint8_t point, uint8_t rangeStart, uint8_t rangeEnd, uint8_t length);
int8_t triangel_signal(uint16_t T, uint8_t amplitude, uint8_t t);
uint8_t return_pulse(uint8_t value, uint8_t tern);


void _blink(void *pvParameters)
{
  uint8_t lag = 150 / portTICK_PERIOD_MS;
  uint8_t offset = 0;

  for(;;)
  {
    leds[offset] = CRGB(rand() % 255, rand() % 255, rand() % 255);

    offset++;
    offset = offset % NUM_LEDS;
    if (offset == 0)
    {
      FastLED.show();
      vTaskDelay(lag);
    }
  }
  vTaskDelete(NULL);
}

void _fire(void *pvParameters)
{
  uint8_t lag = 100 / portTICK_PERIOD_MS;
  uint8_t offset = 0;
  uint8_t step = 50;
  CRGB color = base_colors.orange;
  for (;;)
  {
    leds[offset] = CRGB(fire_random(color[0], step), fire_random(color[1], step), fire_random(color[2], step));

    offset ++;
    offset = offset % NUM_LEDS; 
    if (offset == 0)
    {
      FastLED.show();
      vTaskDelay(lag);
    }
  }
  vTaskDelete(NULL);
}

void _filling_line(void *pvParameters)
{
  uint8_t lag = 100 / portTICK_PERIOD_MS;
  uint8_t offset = 0;
  bool stage = true;
  CRGB color = base_colors.red;
  for (;;)
  {
    if (stage)
      leds[offset] = color;
    else
      leds[offset] = base_colors.black;
    FastLED.show();
    vTaskDelay(lag);
    offset ++;
    offset = offset % NUM_LEDS;
    if (offset == 0)
      stage = !stage;
  }
  vTaskDelete(NULL);
}


void _snake(void *pvParameters)
{
  uint8_t offset = 0;
  uint8_t length = 15;
  uint8_t lag = 100 / portTICK_PERIOD_MS;
  CRGB color = base_colors.blue;

  for (;;)
  {
    FastLED.clear();
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    {
      uint8_t endSnake = offset;
      uint8_t startSnake = (offset + length - 1) % NUM_LEDS;

      uint8_t dist = wrapped_distance(i, endSnake, startSnake, NUM_LEDS);
      
      if (dist == 0) 
      {
        float gradient = 1 - (startSnake - i >= 0 && startSnake - i <= length - 1 
          ? float(startSnake - i) 
          : float(startSnake - i + NUM_LEDS)) 
          / float(length);
        leds[i] = CRGB(round(color[0] * gradient), round(color[1] * gradient), round(color[2] * gradient));
      }
    }

    FastLED.show();
    vTaskDelay(lag);
    offset++;
    offset = offset % NUM_LEDS;
  }
  vTaskDelete(NULL);
}

void _pulse(void *pvParameters)
{
  uint8_t lag = 100 / portTICK_PERIOD_MS;
  uint8_t offset = 0;
  uint8_t step = 50;
  uint8_t iteration = 0;
  uint16_t period = 4 * lag * step;
  uint16_t current_time = 0;
  CRGB color = base_colors.orange;
  for(;;)
  {
    current_time = lag * iteration;
    uint8_t current_step = triangel_signal(period, step, current_time);

    leds[offset] = CRGB(return_pulse(color[0], current_step), return_pulse(color[1], current_step), return_pulse(color[2], current_step));

    iteration ++;
    iteration = iteration % (4 * step);

    offset ++;
    offset = offset % NUM_LEDS;
    if(offset == 0)
    {
      FastLED.show();
    vTaskDelay(lag);
    }
  }
  vTaskDelete(NULL);
}





uint8_t fire_random(uint8_t _value, uint8_t _step)
{
  if (_value == 0)
    return _value;

  int16_t result;
  if (rand() % 2 == 1)
    result = _value + rand() % _step;
  else
    result = _value - rand() % _step;

  if (result > 255)
    result = 255;
  else if (result < 0)
    result = 0;

  return result;
}

uint8_t minValue(uint8_t value1, uint8_t value2, uint8_t value3, uint8_t value4)
{
  uint8_t result = value1;
  if (result > value2)
    result = value2;

  if (value3 != 0)
    if (result > value3) result = value3;

  if (value4 != 0)
    if (result > value4) result = value4;
  
  return result;
}

uint8_t maxValue(uint8_t value1, uint8_t value2, uint8_t value3)
{
  uint8_t result = value1;
  if (result < value2)
    result = value2;

  if (result < value3)
    result = value3;

  return result;
}

uint8_t wrapped_distance(uint8_t point, uint8_t rangeStart, uint8_t rangeEnd, uint8_t length)
{
  point = point + length % length;
  rangeStart = rangeStart + length % length;
  rangeEnd = rangeEnd + length % length;

  if (rangeStart <= rangeEnd)
  {
    if (point >= rangeStart && point <= rangeEnd)
      return 0.0; 
    else
      return min(abs(point - rangeStart), abs(point - rangeEnd));
  } 

  else
  {
    if (point >= rangeStart || point <= rangeEnd)
      return 0.0; 
    else
      return minValue(abs(point - rangeStart), abs(point - rangeEnd), length - abs(point - rangeStart), length - abs(point - rangeEnd));
  }
}

int8_t triangel_signal(uint16_t T, uint8_t amplitude, uint8_t t)
{
  if (t <= T/4)
    return ((4 * amplitude * t)/T);
  else if (t <= (3 * T)/4)
    return (-(((4 * amplitude)/T) * t)) + 2 * amplitude;
  else
    return ((4 * amplitude * t)/T) - 4 * amplitude;
}

uint8_t return_pulse(uint8_t value, uint8_t tern)
{
  if (value == 0)
    return 0;
  else
  {
    if (value + tern > 255)
      return 255;
    else if (value + tern < 0)
      return 0;
    else
      return value + tern;
  }
}