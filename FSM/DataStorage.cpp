#include "DataStorage.h"

namespace FSM
{
	Status DataStorage::get_value(string & name, bool & value)
	{
#ifdef DEBUG
		std::cout << "debug mode" << std::endl;
#endif 
		return Status();
	}
	Status DataStorage::get_value(string & name, int & value)
	{
		return Status();
	}
	Status DataStorage::get_value(string & name, float & value)
	{
		return Status();
	}
}