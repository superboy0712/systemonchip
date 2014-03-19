/* -*- mode: c++ -*-
** button.cpp
** 
** Made by Kjetil Svarstad
** 
*/

#include "button.h"

// Functionality for the Button class

// Constructor
SC_HAS_PROCESS(Button);
Button::Button (sc_module_name name, int _id) : sc_module (name),
												button_id (_id)
{
	light.write(false);// Constructor code

	//SC_THREAD(Button_process);

}

//void Button::Button_process(){
//	while(true) {
//
//	}
//}

void Button::SetLight(bool bl) {
	if(bl) {
		light.write(true);
	} else {
		light.write(false);
	}
}

void Button::Push(void) {
	writep->write(button_id);
}

bool Button::Checklight(void){
	return(light.read());
}
