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

/** include files **/
#include <math.h>           // fabs( ... )
#include <stdlib.h>
#include "Controller.h"  	// base header
#include "message.h"      	// InternalMessage ....
#include "mainsimu.h"     	// class MainSimulator
#include "strutil.h"        // str2float( ... )

/*******************************************************************
* Function Name: Controller
* Description: constructor
********************************************************************/
Controller::Controller( const std::string &name ) : Atomic( name )
, in1( addInputPort( "in1" ) )
, in2( addInputPort( "in2") )
, out1( addOutputPort( "out1" ) )
, out2( addOutputPort( "out2" ) )
, out3( addOutputPort( "out3" ) )
, processTime (00,00,00,010)
, cmpSetTime (00,00,03,00)
{
	std::string timeProcess( MainSimulator::Instance().getParameter( description(), "processProcessingTime" ) ) ;
	std::string timeCmpSet( MainSimulator::Instance().getParameter( description(), "cmpSetProcessingTime" ) ) ;

	//test
	if (timeProcess !="") processTime = timeProcess;
	if (timeCmpSet !="") cmpSetTime = timeCmpSet;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"processTime="<<processTime<<"\n";
	cout<<"cmpSetTime="<<cmpSetTime<<"\n";
}

/*******************************************************************
* Function Name: Controller::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Controller::initFunction()
{

	this->state = Idle;		// detecting
	this->previous = -1;	// set dummy value
	this->current = -1;		// set dummy value
	return *this ;
}
/*******************************************************************
* Function Name: Controller::externalFunction()
* Description: External Function Controller
********************************************************************/
Model &Controller::externalFunction( const ExternalMessage &msg )
{

	if (state == Idle && msg.port() == in1){
		if (msg.value()==1.0){
			this->state = Process;
			this->holdIn(Atomic::active, processTime);
		}
	}
	else if (state == Wait && msg.port() == in2) {
		if (previous == -1){
			// first time receiving data, set the depth current depth
			this->previous=0;               // we have received data
			this->current=msg.value();      // store the depth from input
			this->state = Cmp_Set;
			this->holdIn(Atomic::active, cmpSetTime);
		} else {
			// update the depths
			this->previous= this->current;  // update previous depth
			this->current=msg.value();		// store the depth from input
			this->state = Cmp_Set;
			this->holdIn(Atomic::active, cmpSetTime);
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: Controller::internalFunction()
* Description: Internal Function Controller
********************************************************************/
Model &Controller::internalFunction( const InternalMessage & )
{
	switch(state){
		case Process:
			this->state = Wait;
			this->passivate();
			break;

		case Cmp_Set:
			if (previous == current){
				// device has hit the ground
				this->state = Idle;
				this->passivate();
			} else {
				// device is still sinking
				this->state = Wait;
				this->passivate();
			}
			break;
	}
	return *this;
}

/*******************************************************************
* Function Name: Controller::outputFunction()
* Description: Output function Controller - writes info about time and events
********************************************************************/
Model &Controller::outputFunction( const InternalMessage &msg )
{
	if (state == Process){
			this->sendOutput( msg.time(), this->out1, 1) ;// activate depth sensor
	}
	else if (state == Cmp_Set){
		if (previous == current){
			// device is at the ground
			this->sendOutput( msg.time(), this->out2, 1) ;// activate inflator
			this->sendOutput( msg.time(), this->out3, current) ;// output final depth
		} else {
			// device is still sinking
			this->sendOutput( msg.time(), this->out1, 1) ;// activate depth sensor
			//this->sendOutput( msg.time(), this->out3, previous) ;// check previous depth
			//this->sendOutput( msg.time(), this->out3, current) ;// check current depth
		}
	}
	return *this ;
}

Controller::~Controller()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
