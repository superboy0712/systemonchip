/* -*- mode: c++ -*-
** button.h
** 
** Made by Kjetil Svarstad
** 
*/

#ifndef   	BUTTON_H_
# define   	BUTTON_H_

#include <systemc.h>
#include "if.h"


//  Our beloved button class (changes are required)

class Button: public sc_module, public Light_if<bool>, public Push_if{

public:
	//to access Bus
	sc_port< Bus4Button_if<int> > writep;
  Button (sc_module_name, int);

  void Push(void);//method for simulate "push"
  bool Checklight(void);// returns the light status
  void Button_process();// why should basic thread functions declaration be placed in public? how to hide them.
  void SetLight ( bool bl );

 private:
  int button_id;
  sc_signal<bool> light;//represents the on/off status

};


#endif 	    /* !BUTTON_H_ */
