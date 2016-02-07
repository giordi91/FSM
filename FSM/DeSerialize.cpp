#include "DeSerialize.h"
#include <sstream>
#include <fstream>
namespace FSM
{
	namespace Serialize
	{
		
		string extract_type(string& data)
		{
			std::smatch type_match;
			std::regex_search(data, type_match, REG_TYPE_EXTRACTOR);
			if (type_match.size() != 2)
			{
				return string();
			}
			else
			{
				return type_match[1];
			}
		}

		ClassArgs extract_args(string & data)
		{
			
			//first pass in extracting args only full string
			std::smatch type_match;
			std::regex_search(data, type_match, REG_ARGS_EXTRACTOR);
			
			//second pass we find all the matches for single argumenets
			std::smatch type_match2;
			string data2 = type_match[1];
			auto it = std::sregex_iterator(data2.begin(), data2.end(), REG_SINGLE_ARG_EXTRACTOR);
			auto end = std::sregex_iterator();

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
			string line;
			std::getline(file, line);
			std::smatch type_match;
			std::regex_search(line, type_match, REG_END_CONDITIONS);

			while (type_match.size() == 0)
			{
				data.push_back(line);
				std::getline(file, line);
				std::regex_search(line, type_match, REG_END_CONDITIONS);
			}
		}
		void read_connection_from_file(std::ifstream & file, vector<string>& connection_data,
											 vector<vector<string>>& condition_data)
		{
			string line;
			std::getline(file, line);
			std::smatch type_match;
			std::regex_search(line, type_match, REG_END_CONNECTION);
			
			int counter = 1;
			vector<string> cond_sub_data;
			condition_data.clear();
			while (type_match.size() == 0)
			{
				//pushing back conneciton line
				connection_data.push_back(line);
				read_conditions_from_file(file, cond_sub_data);
				condition_data.push_back(cond_sub_data);
				cond_sub_data.clear();
				std::getline(file, line);
				std::regex_search(line, type_match, REG_END_CONNECTION);
			}
		}
	}
}