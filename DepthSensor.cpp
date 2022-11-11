/*******************************************************************
*
*  DESCRIPTION: Atomic Model DepthSensor
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
#include "DepthSensor.h"  	// base header
#include "message.h"      	// InternalMessage ....
#include "mainsimu.h"     	// class MainSimulator
#include "strutil.h"        // str2float( ... )

/*******************************************************************
* Function Name: DepthSensor
* Description: constructor
********************************************************************/
DepthSensor::DepthSensor( const std::string &name ) : Atomic( name )
, in1( addInputPort( "in1" ) )
, in2( addInputPort( "in2" ) )
, out( addOutputPort( "out" ) )
, prepareTime (00,00,00,010)
, sendTime (00,00,00,010)
{
	std::string timePrepare( MainSimulator::Instance().getParameter( description(), "prepareProcessingTime" ) ) ;
	std::string timeSend( MainSimulator::Instance().getParameter( description(), "sendProcessingTime" ) ) ;

	//test
	if (timePrepare !="") prepareTime = timePrepare;
	if (timeSend !="") sendTime = timeSend;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"prepareTime="<<prepareTime<<"\n";
	cout<<"sendTime="<<sendTime<<"\n";
}

/*******************************************************************
* Function Name: DepthSensor::initFunction()
* Description: Initialization Function
********************************************************************/
Model &DepthSensor::initFunction()
{

	this->state = Idle;		// detecting
	this->depth = -1;		// set dummy depth
	return *this ;
}
/*******************************************************************
* Function Name: DepthSensor::externalFunction()
* Description: External Function DepthSensor
********************************************************************/
Model &DepthSensor::externalFunction( const ExternalMessage &msg )
{

	if (state == Idle && msg.port() == in1){
		if (msg.value()==1.0){
			this->state = Pr_Dep;
			this->holdIn(Atomic::active, prepareTime);
		}
	}
	else if (state == Wait && msg.port() == in2){
		this->depth=msg.value();      // store the depth from input
		this->state = Send_Con;
		this->holdIn(Atomic::active, sendTime);
	}
	return *this;
}

/*******************************************************************
* Function Name: DepthSensor::internalFunction()
* Description: Internal Function DepthSensor
********************************************************************/
Model &DepthSensor::internalFunction( const InternalMessage & )
{
	switch(state){
		case Pr_Dep:
			this->state = Wait;
			this->passivate();
			break;

		case Send_Con:
			this->state = Idle;
			this->passivate();
			break;
	}
	return *this;
}

/*******************************************************************
* Function Name: DepthSensor::outputFunction()
* Description: Output function DepthSensor - writes info about time and events
********************************************************************/
Model &DepthSensor::outputFunction( const InternalMessage &msg )
{
	if (state == Send_Con){
			this->sendOutput( msg.time(), this->out, depth) ;// output depth
	}
	return *this ;
}

DepthSensor::~DepthSensor()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
