
#include <Mini-STLIB/DigitalOut.hpp>

vector<DigitalOut*> DigitalOut::all_digital_outs;
map<Pin*, DigitalOut*> DigitalOut::pin_to_digital_out;

DigitalOut::DigitalOut(Pin* pin) : pin(pin) {
	DigitalOut::all_digital_outs.push_back(this);
	DigitalOut::pin_to_digital_out[pin] = this;
	pin->mode = DIGITAL_OUTPUT;
}

void DigitalOut::set_to(DigitalOutState state){
	if(state == HIGH)
		turn_high();
	else
		turn_low();
}

void DigitalOut::turn_high(){
	HAL_GPIO_WritePin(pin->port, pin->pin, GPIO_PIN_SET);
}

void DigitalOut::turn_low(){
	HAL_GPIO_WritePin(pin->port, pin->pin, GPIO_PIN_RESET);
}
