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
class Control : public sc_module
{
public:
  Control (sc_module_name);

private:
  static const int X[9];

};


#endif 	    /* !CONTROL_H_ */
