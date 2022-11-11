/*******************************************************************
*
*  DESCRIPTION: Atomic Model Depth Sensor
*
*  AUTHOR: Ronnie Farrell
*
*  Email: ronnie@sce.carleton.ca
*
*  DATE: 22/10/2011
*
*******************************************************************/

#ifndef __DEPTHSENSOR_H
#define __DEPTHSENSOR_H

/** include files **/
#include "atomic.h"     // class Atomic

class DepthSensor : public Atomic
{
public:
	DepthSensor( const string &name = "DepthSensor" );					//Default constructor
	virtual string className() const { return "DepthSensor";}
	~DepthSensor();
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in1;
	const Port &in2;
	Port &out;
	Time prepareTime;
	Time sendTime;
	int depth;		// store the depth
	enum State{
		Idle,		// wait input from Controller
		Pr_Dep,		// prepare to get depth
		Wait,		// wait to receive depth from input
		Send_Con	// send depth to Controller
	};
	State state;
};	// class DepthSensor

#endif   //__DEPTHSENSOR_H
