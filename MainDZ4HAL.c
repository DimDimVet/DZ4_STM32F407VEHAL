#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common

// LED2 PA6 31pin соотв. GPIO port mode register (GPIOx_MODER) 12-13 битам
// LED3 PA7 32pin соотв. GPIO port mode register (GPIOx_MODER) 14-15 битам

//ищем GPIO_Init stm32f4xx_hal_gpio.с, находим, требуется структура с настройками
//по логике идем в файл GPIO (stm32f4xx_hal_gpio.h) ищем по признаку TypeDef или гугл "HAL GPIO"
//и созаем экземляр 
	GPIO_InitTypeDef LED2;
	GPIO_InitTypeDef LED3;

void initClk(void);
void initGPIO(void);

int main(void)
{
initClk();
initGPIO();

while(1)
	{
	//в файле stm32f4xx_hal_gpio.h находим вариант IO operation functions
	HAL_GPIO_WritePin(GPIOA,LED2.Pin,GPIO_PIN_SET);
	HAL_GPIO_TogglePin(GPIOA,LED3.Pin);
	for (int i = 0; i < 900000; i++) {};
	HAL_GPIO_WritePin(GPIOA,LED2.Pin,GPIO_PIN_RESET);
	for (int i = 0; i < 900000; i++) {};
	}

}


void initClk()
{
//по логике идем в файл RCC ищем по признаку RCC_GPIOA или гугл "HAL RCC"
__HAL_RCC_GPIOA_CLK_ENABLE();
}


void initGPIO()
{
//по составу структуры заполняем, по сути 4 региста (GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR and GPIOx_PUPDR)
LED2.Pin=GPIO_PIN_6;//находим в stm32f4xx_hal_gpio.h вариант
LED2.Mode=GPIO_MODE_OUTPUT_PP;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом
LED2.Pull=GPIO_PULLDOWN;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом
LED2.Speed=GPIO_SPEED_FREQ_LOW;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом;
//ищем GPIO_Init, укажем порт и укажем на структуру
HAL_GPIO_Init(GPIOA, &LED2);

LED3.Pin=GPIO_PIN_7;//находим в stm32f4xx_hal_gpio.h вариант
LED3.Mode=GPIO_MODE_OUTPUT_PP;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом
LED3.Pull=GPIO_PULLDOWN;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом
LED3.Speed=GPIO_SPEED_FREQ_LOW;//stm32f4xx_hal_gpio.h находим ссылку enum с вариантом;
HAL_GPIO_Init(GPIOA, &LED3);

}
