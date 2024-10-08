#include <iostream>
#include "SimulationManager.h"
int main()
{
    SimulationManager* simulationManager = new SimulationManager();
    simulationManager->InitializeComponents();
	if (!simulationManager->SimulationLoop())
	{
		return false;
	}
}