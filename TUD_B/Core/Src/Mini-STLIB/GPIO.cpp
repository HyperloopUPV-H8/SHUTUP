
#include <Mini-STLIB/GPIO.hpp>

vector<GPIO*> GPIO::all_gpio;
map<Pin*, GPIO*> GPIO::pin_to_gpio;

GPIO::GPIO(Pin* pin) : pin(pin) {
	GPIO::all_gpio.push_back(this);
	GPIO::pin_to_gpio[pin] = this;
	pin->mode = GPIO_PIN;
}

void GPIO::write(GPIOState state) {
	if(mode == GPIO_NONE) {
		mode = GPIO_OUT;
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct			= {0};
		GPIO_InitStruct.Pin 	= pin->pin;
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull	= GPIO_NOPULL;
		GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(pin->port, &GPIO_InitStruct);
	}

	if(mode == GPIO_OUT){
		if(state == HIGH)
			HAL_GPIO_WritePin(pin->port, pin->pin, GPIO_PIN_SET);
		if(state == LOW)
			HAL_GPIO_WritePin(pin->port, pin->pin, GPIO_PIN_RESET);
	}
}

GPIO::GPIOState GPIO::get_value(){
	if(mode == GPIO_NONE) {
		mode = GPIO_IN;
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct			= {0};
		GPIO_InitStruct.Pin 	= pin->pin;
		GPIO_InitStruct.Mode	= GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull	= GPIO_PULLDOWN;
		HAL_GPIO_Init(pin->port, &GPIO_InitStruct);
	}

	if(mode == GPIO_IN){
		GPIO_PinState hal_state = HAL_GPIO_ReadPin(pin->port, pin->pin);
		if(hal_state == GPIO_PIN_SET){
			state = GPIOState::HIGH;
			value = 1.0;
		}else{
			state = GPIOState::LOW;
			value = 0.0;
		}return state;
	}

	return GPIOState::LOW;
}

