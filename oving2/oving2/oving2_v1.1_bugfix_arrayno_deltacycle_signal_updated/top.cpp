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
class Bus : public sc_channel, public Bus4Button_if<int>, public Bus4Control_if<int>
{
public:
	void write(int);// write to Control
	void LightControl(int);
	sc_port< Control4Bus_if<int> > port2control;//access to control's interfaces
	sc_port< Light_if<bool> > port2button[10];// access to button's interfaces,but 10 port!!! 10!!

  Bus (sc_module_name name) : sc_channel (name) {}

};
void Bus::write(int code) {//write to bus
	port2control->write(code);
}

void Bus::LightControl(int code){
	if( code == 0xffff){
		for( int i = 0; i<= 9; i++){
			port2button[i]->SetLight(false);
		}
	} else {
		port2button[code]->SetLight(true);
	}
}
// top
class top : public sc_module {
public:
  //instances ...
	Button *Button_inst_ptr[10];//10!!!!!!
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
    for(i=0;i<=9;i++){//assign different name to the button instances

    	Button_inst_ptr[i] = new Button("Button_inst",i);
    	Bus_inst.port2button[i](*Button_inst_ptr[i]);// Bus_inst's i th port2button connects to i th Button(which Button_inst_ptr[i] points to)
    	Button_inst_ptr[i]->writep(Bus_inst);
    	testbed_inst.port2Button[i](*Button_inst_ptr[i]);// testbed connect to button

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
