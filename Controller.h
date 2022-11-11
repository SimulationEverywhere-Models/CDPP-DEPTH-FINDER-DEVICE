/*******************************************************************
*
*  DESCRIPTION: Atomic Model Controller
*
*  AUTHOR: Ronnie Farrell
*
*  Email: ronnie@sce.carleton.ca
*
*  DATE: 22/10/2011
*
*******************************************************************/

#ifndef __CONTROLLER_H
#define __CONTROLLER_H

/** include files **/
#include "atomic.h"     // class Atomic

class Controller : public Atomic
{
public:
	Controller( const string &name = "Controller" );					//Default constructor
	virtual string className() const { return "Controller";}
	~Controller();
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in1;
	const Port &in2;
	Port &out1;
	Port &out2;
	Port &out3;
	Time processTime;
	Time cmpSetTime;
	int previous;	// the previous depth (ft)
	int current;    // the current depth (ft)
	enum State{
		Idle,		// wait for input to activate
		Process,	// controller is on
		Wait,		// wait to receive depth from DepthSensor
		Cmp_Set		// set or compare depth
	};
	State state;
};	// class Controller

#endif   //__CONTROLLER_H
