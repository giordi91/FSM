#pragma once
#include "Serialize.h"
#include <unordered_map>
#include <string>
#include "Condition.h"
using std::regex;

namespace FSM
{
	namespace Serialize
	{ 
		///regex expression used to extract type of object from the string
		const string TYPE_EXTRACTOR = OPEN_TAG + " *([a-zA-Z]+?[<>a-zA-Z>]*) *" +TYPE_SEP ;  
		///regex expression used to extract args block from the string
		const string ARGS_EXTRACTOR = TYPE_SEP + " *([a-zA-Z0-9 ,\\.]+) *" +CLOSE_TAG;  
		///regex expression used to extract arguments one by one
		const string SINGLE_ARG_EXTRACTOR = "([a-zA-Z0-9\\.]+)";  
	
		//regex objects
		///regex object to extrac the type
		const regex REG_TYPE_EXTRACTOR = regex(TYPE_EXTRACTOR);
		///regex object to extract arguments block
		const regex REG_ARGS_EXTRACTOR = regex(ARGS_EXTRACTOR);
		///regex object to extract single arguments
		const regex REG_SINGLE_ARG_EXTRACTOR = regex(SINGLE_ARG_EXTRACTOR);
		///regex object used to find end connections tag
		const regex REG_END_CONNECTION = regex(CONNECTIONS_TAG);
		///regex object used to find end conditions tag
		const regex REG_END_CONDITIONS= regex(CONDITIONS_TAG);
		///regex object used to find end states tag
		const regex REG_END_STATES= regex(STATES_TAG);

		/*
		@brief this function extract the type from a string 
		@param data: the string to parse
		@retunrs: the matched type or empty string
		*/
		string extract_type( const string& data);

		/*
		@brief this functoin extract the args from a string
		@param data: the string to parse
		@returns : array of strings, the matched args 
		*/
		ClassArgs extract_args(const string& data);

		/*
		@brief reads a block of conditions from the file
		This function will pick up the stream object from the 
		point where it is, supposely at beginning of conditions,
		it will keep advancing the file until wont find a closing
		condition tag for conditions. Meanwhile it will keep track
		of the found condition and store them to return them.
		@param file: the stram we are working on
		@param data: the datastructure to fill, each entry is a full
					 unparsed condition string
		*/
		void read_conditions_from_file( std::ifstream& file, 
										std::vector<string>& data);
		
		/*
		@brief reads a block of connections from the file
		This function will pick up the stream object from the 
		point where it is, supposely at beginning of a connection,
		it will keep advancing the file until wont find a closing
		connection tag for conditions. Meanwhile it will keep track
		of the found conditions and connections and store them to return them.
		@param file: the stram we are working on
		@param connection_data: the data structure to fill with the
					connection data, each line is a full and unparsed
					connection string
		@param condition_data: the data structure to fill, each entry is 
					 an array of full unparsed condition strings
		*/
		void read_connection_from_file(std::ifstream& file, 
			vector<string>& connection_data,
			vector<vector<string>>& condition_data);
	}

}
