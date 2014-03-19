/* -*- mode: c++ -*-
** control.h
** 
** Made by Kjetil Svarstad
** 
*/

#ifndef   	CONTROL_H_
# define   	CONTROL_H_

#include <systemc.h>

#include "if.h"

//  Our beloved control class (changes required)
class Controller : public sc_module, public Control4Bus_if <int>
{
public:
	sc_port< Bus4Control_if<int> > writep;
	Controller (sc_module_name);
	void write(int);
	void Control_process(void);

private:
  static const int X[9];// Secrete code
  //sc_fifo<int> sc_fifo_inst;// restore the current correct button ID. pointer to an array which stores the button id

};


#endif 	    /* !CONTROL_H_ */
