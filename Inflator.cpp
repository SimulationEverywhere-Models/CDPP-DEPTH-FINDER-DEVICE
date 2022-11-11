/*******************************************************************
*
*  DESCRIPTION: Atomic Model Inflator
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
#include "Inflator.h"  		// base header
#include "message.h"      	// InternalMessage ....
#include "mainsimu.h"     	// class MainSimulator
#include "strutil.h"        // str2float( ... )

/*******************************************************************
* Function Name: Inflator
* Description: constructor
********************************************************************/
Inflator::Inflator( const std::string &name ) : Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, inflateTime (00,00,02,00)
{
	std::string timeInflate( MainSimulator::Instance().getParameter( description(), "inflateProcessingTime" ) ) ;
//test
	if (timeInflate !="") inflateTime = timeInflate;

	//MainSimulator::Instance().Spin_Motor_Clockwise(30);

	cout<<"inflateTime="<<inflateTime<<"\n";
}

/*******************************************************************
* Function Name: Inflator::initFunction()
* Description: Initialization Function
********************************************************************/
Model &Inflator::initFunction()
{

	this->state = Idle;		// detecting
	return *this ;
}
/*******************************************************************
* Function Name: Inflator::externalFunction()
* Description: External Function Inflator
********************************************************************/
Model &Inflator::externalFunction( const ExternalMessage &msg )
{

	if (state == Idle && msg.port() == in && msg.value()==1.0)
	{
		this->state = In_Bag;
		this->holdIn(Atomic::active, inflateTime);
	}
	return *this;
}

/*******************************************************************
* Function Name: Inflator::internalFunction()
* Description: Internal Function Inflator
********************************************************************/
Model &Inflator::internalFunction( const InternalMessage & )
{
	if(state == In_Bag){
		this->state = Idle;
		this->passivate();
	}

	return *this;
}

/*******************************************************************
* Function Name: Inflator::outputFunction()
* Description: Output function Inflator - writes info about time and events
********************************************************************/
Model &Inflator::outputFunction( const InternalMessage &msg )
{
	if (state == In_Bag){
		this->sendOutput( msg.time(), this->out, 1) ;//something founded
	}
	return *this ;
}

Inflator::~Inflator()
{
	//MainSimulator::Instance().Spin_Motor_Stop();
}
