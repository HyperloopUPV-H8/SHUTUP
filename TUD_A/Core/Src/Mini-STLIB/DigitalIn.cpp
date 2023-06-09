
#include <Mini-STLIB/DigitalIn.hpp>

vector<DigitalIn*> DigitalIn::all_digital_ins;
map<Pin*, DigitalIn*> DigitalIn::pin_to_digital_in;

DigitalIn::DigitalIn(Pin* pin) : pin(pin) {
	DigitalIn::all_digital_ins.push_back(this);
	DigitalIn::pin_to_digital_in[pin] = this;
	pin->mode = DIGITAL_INPUT;
}

DigitalIn::DigitalInState DigitalIn::get_value(){
	GPIO_PinState hal_state = HAL_GPIO_ReadPin(pin->port, pin->pin);
	if(hal_state == GPIO_PIN_SET)
		state = DigitalIn::HIGH;
	else
		state = DigitalIn::LOW;
	return state;
}

