#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <esp_system.h>

#define LED_COUNT 4
#define BUTTON_PIN 15

const gpio_num_t led_pins[LED_COUNT]={
  GPIO_NUM_2, GPIO_NUM_3, GPIO_NUM_4, GPIO_NUM_5
};

int app_main(){
  
  for(int i=0; i<LED_COUNT; i++){
    gpio_pad_select_gpio(led_pins[i]);
    gpio_set_direction(led_pins[i], GPIO_MODE_OUTPUT);
  }
  
  gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
  gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);



  uint32_t count=0; 
  while(1){
    if(gpio_get_level(BUTTON_PIN) == 0){
      for( int i=0; i<LED_COUNT; i++){
        gpio_set_level(led_pins[i],(count & (1<<i)) ? 1 : 0);

      }
      count = (count +1) % 16;
      vTaskDelay(500/ portTICK_PERIOD_MS);
      
    }
 
 }
}
