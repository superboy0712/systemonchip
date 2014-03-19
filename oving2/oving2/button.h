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
class Button : public sc_module
{
 public:
  Button (sc_module_name, int);

 private:

};


#endif 	    /* !BUTTON_H_ */
