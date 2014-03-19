/* -*- mode: c++ -*-
** control.cpp
** 
** Made by Kjetil Svarstad
** 
*/

#include "control.h"

const int Controller::X[9] = {3,8,1,2,9,5,7,6,4};

// Functionality for the Control class

// Constructor
SC_HAS_PROCESS(Controller);
Controller::Controller (sc_module_name name) : sc_module (name)
{ // Constructor code
	//SC_THREAD(Control_process);
}

void Controller::write(int id)
{
	//sc_fifo_inst.write(id);
	int id_temp = id;
	static int i = 0;//restores the current i th try with previous i-1 times successful push
			if (i > 9) i = 0; //
			if(X[i]==id_temp){
				writep->write(id_temp+0xff);// light on the id button, add offset 0xff represents sent from controller
				i ++;// i th try matches, move to next one.
			} else {
				writep->write(0xffff); // 0xffff code reserved. means all light off.
				i = 0;// i th try fails, from beginning.
			}

}
////
//void Controller::Control_process(void){
//
//}
