/* -*- mode: c++ -*-
** if.h
** 
** Made by Kjetil Svarstad
**
** All interfaces collected here
*/

#ifndef   	IF_H_
# define   	IF_H_
// Interface for Button to access Bus,and for bus to access Control
template < class T >
class fifo_write_if : public sc_interface {
	public:
	virtual void write (T) = 0;
};
//// Interface for Control to access Bus
//template < class T >
//class control_if : public sc_interface {
//	public:
//	virtual void write(T) = 0;
//};

//// Interface for Control to access Bus
//template < class T >
//class button_if : public sc_interface {
//	public:
//	virtual void write(T) = 0;
//};

// Proxy-interface for Bus to access Button

template < class T >
class Light_if : public sc_interface {
	public:
	virtual void SetLight( T ) = 0;// forget to add "=0", so undefined reference to `Light_if<bool>::SetLight(bool)'
	//collect2: error: ld returned 1 exit status
};
// interface for testbed to access button's push and signal
class Push_if : public sc_interface {
	public:
	virtual void Push(void) = 0;
	virtual bool Checklight(void) = 0;
};

#endif 	    /* !IF_H_ */
