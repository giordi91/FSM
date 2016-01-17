#include <string>
#include <unordered_map>
#pragma once

using std::string;
using std::unordered_map;
namespace FSM
{
	enum class DataType
	{
		BOOL =0,
		INT,
		FLOAT
	};

	enum class Status
	{
		Succes=0,
		Failure
	};
	
	class DataStorage
	{
	public:
		DataStorage() = default;
		~DataStorage() = default;

		Status get_value(string& name, bool& value);
		Status get_value(string& name, int& value);
		Status get_value(string& name, float& value);
	private:
		unordered_map<string, bool> gm_bool_storage;
		unordered_map<string, int> gm_int_storage;
		unordered_map<string, float> gm_float_storage;
	};


}

