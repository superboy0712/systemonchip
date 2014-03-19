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
#include "testbed.h"
#include "iostream"

// The Bus system
class Bus : public sc_channel, public fifo_write_if<int>
{
public:
	void write(int);// both button and control used the same write entry method. differs by code prefix. . or overload with <templete type>
	sc_port< fifo_write_if<int> > port2control;//access to control's interfaces
	sc_port< Light_if<bool> > port2button[9];// access to button's interfaces

  Bus (sc_module_name name) : sc_channel (name) {}

};
void Bus::write(int code) {
	int i;
	if (code == 0xffff) {
		// turn off all lights
		for(i = 0; i <=9; i++){
			port2button[i]->SetLight(false);
		}
	}

	else if (code >= 9){
			// accessed by control
			port2button[code%9]->SetLight(true);
		}
		else {
			// accessed by button
			port2control->write(code);
		}
}
// top
class top : public sc_module {
public:
  //instances ...
	Button *Button_inst_ptr[];
	Bus Bus_inst;
	Controller Control_inst;
	testbed testbed_inst;

  top (sc_module_name name) : sc_module (name),
						 Bus_inst("Bus_inst"),
						 Control_inst("Control_inst"),
						testbed_inst("testbed_inst")
  { // constructor code
	  //connection
    Bus_inst.port2control(Control_inst);
    Control_inst.writep(Bus_inst);
    int i;
    std::string c = "_0";
    std::string s;
    for(i=0;i<=9;i++,c[1]++){
    	s = "Button" +  c;
    	cout << "Button"<< c << "vs."<< s << endl;
    	Button_inst_ptr[i] = new Button("Button",i);
    	Bus_inst.port2button[i](*(Button_inst_ptr[i]));// Bus_inst's i th port2button connects to i th Button(which Button_inst_ptr[i] points to)
    	Button_inst_ptr[i]->writep(Bus_inst);
    	testbed_inst.port2Button[i](*(Button_inst_ptr[i]));// testbed connect to button

    }
    //delete Button_inst_ptr;
  }
};

int sc_main (int argc , char *argv[])  {
  // instantiate top
	// instantiating top module
	cout << "before top" << endl;
	  top top01("top01");
	  cout << "after top" << endl;
	  // initializing random number generator
	  srand ( time(NULL) );
  // tracing of signals ...put in the testbed

  // sc_start ...
	//  sc_report_handler::set_actions(SC_WARNING, SC_DO_NOTHING);// warnings shut down
  sc_start ();
  
  return 0;
}
