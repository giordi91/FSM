#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

using std::string;
namespace FSM
{
	namespace Serialize
	{
		const string TYPE_SEP = " ### ";
		const string ARGS_SEP = " , ";
		const string OPEN_TAG = "<< ";
		const string CLOSE_TAG = " >>";
		const size_t FLOAT_PRECISION = 5;
		const string CONNECTIONS_TAG = "<<< CONNECTIONS >>>";

		template<typename T>
		inline string number_to_string(T number)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(FLOAT_PRECISION) << number;
			return stream.str();
		}
	}

}