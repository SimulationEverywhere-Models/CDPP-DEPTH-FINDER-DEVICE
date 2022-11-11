/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Ronnie Farrell
*
*  EMAIL: ronnie@sce.carleton.ca
*
*
*  DATE: 22/10/2011
*
*******************************************************************/

#include <modeladm.h>
#include <mainsimu.h>

/* New libraries are copied after this line */
#include "Inflator.h"
#include "DepthSensor.h"
#include "Controller.h"


void MainSimulator::registerNewAtomics()
{

//New models are registered after this line
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Inflator>() , "Inflator" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<DepthSensor>() , "DepthSensor" ) ;
SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Controller>() , "Controller" ) ;

}
