#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <regex>
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
		const string CONDITIONS_TAG =  "<<< CONDITIONS >>>";
		const string CONNECTIONS_TAG = "<<< CONNECTIONS >>>";
		const string STATES_TAG = "<<< STATES >>>";

		
		template<typename T>
		inline string number_to_string(T number)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(FLOAT_PRECISION) << number;
			return stream.str();
		}


			
	}

}