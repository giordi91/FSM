#include "DeSerialize.h"
#include <sstream>
#include <fstream>
namespace FSM
{
	namespace Serialize
	{
		
		string extract_type(const string& data)
		{
			//create a string match and parse the string
			std::smatch type_match;
			std::regex_search(data, type_match, REG_TYPE_EXTRACTOR);
			//for some reason we have to expect two result, the first one 
			//will be the full string
			if (type_match.size() != 2)
			{
				return string();
			}
			else
			{
				return type_match[1];
			}
		}

		ClassArgs extract_args(const string & data)
		{
			
			//first pass in extracting args only full string
			std::smatch type_match;
			std::regex_search(data, type_match, REG_ARGS_EXTRACTOR);
			
			//second pass we find all the matches for single argumenets
			std::smatch type_match2;
			string data2 = type_match[1];
			auto it = std::sregex_iterator(data2.begin(), data2.end(), REG_SINGLE_ARG_EXTRACTOR);
			auto end = std::sregex_iterator();
			
			//here we extract the single arguments and push it in the data structure,
			//then return it
			ClassArgs args;
			while (it != end)
			{
				args.push_back(it->str());
				++it;
			}

			return args;
		}

		void read_conditions_from_file(std::ifstream & file, 
										std::vector<string>& data)
		{
			//here we start by reading the first line, which is expected to be 
			//a condition, we might want to do some extra check to verify thats actually
			//true
			string line;
			std::getline(file, line);
			std::smatch type_match;
			std::regex_search(line, type_match, REG_END_CONDITIONS);
			
			//if in the line we just parsed we did not fine the end conditions
			//tag we keep parsing
			while (type_match.size() == 0)
			{
				//we push the data
				data.push_back(line);
				//evaluate next line
				std::getline(file, line);
				std::regex_search(line, type_match, REG_END_CONDITIONS);
			}
		}

		void read_connection_from_file(std::ifstream & file, vector<string>& connection_data,
											 vector<vector<string>>& condition_data)
		{
			//the operation here is similar for the condition extraction but 
			//we check for a connection end tag
			string line;
			std::getline(file, line);
			std::smatch type_match;
			std::regex_search(line, type_match, REG_END_CONNECTION);
			
			//we declare the subdata for the condition
			vector<string> cond_sub_data;
			condition_data.clear();
			while (type_match.size() == 0)
			{
				//pushing back conneciton line
				connection_data.push_back(line);
				//since we have a connection we need then to parse the conditions,
				//we call the appropiate function to do that
				read_conditions_from_file(file, cond_sub_data);
				//we push the condition data
				condition_data.push_back(cond_sub_data);
				//we clear the temporary datastruct
				cond_sub_data.clear();
				//we read next line and validate is not and end line
				std::getline(file, line);
				std::regex_search(line, type_match, REG_END_CONNECTION);
			}
		}
	}
}