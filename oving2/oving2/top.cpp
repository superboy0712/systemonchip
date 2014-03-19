/* -*- mode: c++ -*-
**
** topp.cpp
**
** top level instatiations and simulation control
** 
** Made by Kjetil Svarstad
** 
*/


#include <systemc.h>

#include "if.h"
#include "button.h"
#include "control.h"

// The Bus system
class Bus : public sc_channel
{
public:
  Bus (sc_module_name name) : sc_channel (name) {}

};

class top : public sc_module {
public:
  //instances ...

  top (sc_module_name name) : sc_module (name)
  { // constructor code
    
  }
};

int sc_main (int argc , char *argv[])  {
  // instantiate top

  // tracing of signals ...

  // sc_start ...

  sc_start ();
  
  return 0;
}
