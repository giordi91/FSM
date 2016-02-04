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
		
		//converting string to number is a messy business, 
		//when you get also a template in the mix, well stuff
		//get hairy. What I eneded up doing is the folloing,
		//I created a generic function that converts to double,
		//in order to try keep max resolution , then we do a static
		//cast on the template type, compiler might get a bit upset
		//based on the type.
		//Now we specialize tho handle basic specific types like int, bool,
		//float.
		template<typename T>
		inline T string_to_number(string& value)
		{
			double double_value= std::stod(args[1]);
			T value = static_cast<T>(double_value);
			return value;
		}
		
		template<> 
		inline bool string_to_number(string& string_value)
		{
			bool value = std::stoi(string_value)==1;
			return value;
		}

		template<> 
		inline int string_to_number(string& string_value)
		{
			int value = std::stoi(string_value);
			return value;
		}
		
		template<> 
		inline float string_to_number(string& string_value)
		{
			float value = std::stof(string_value);
			return value;
		}
	}

}