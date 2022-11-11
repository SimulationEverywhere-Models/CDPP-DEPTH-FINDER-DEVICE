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

#ifndef __INFLATOR_H
#define __INFLATOR_H

/** include files **/
#include "atomic.h"     // class Atomic

class Inflator : public Atomic
{
public:
	Inflator( const string &name = "Inflator" );					//Default constructor
	virtual string className() const { return "Inflator";}
	~Inflator();

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	Port &out;
	Time inflateTime;
	enum State{
		Idle,		// wait input from Controller
		In_Bag		// inflate bag
	};
	State state;
};	// class Inflator

#endif   //__INFLATOR_H
