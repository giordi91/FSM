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

		Status get_value(const string& name, bool& value);
		Status get_value(const string& name, int& value);
		Status get_value(const string& name, float& value);
	
		inline void set_value(const string& name, bool value) 
		{
			m_bool_storage.emplace(name, value);
		}
		inline void set_value(const string& name, int value)
		{
			m_int_storage.emplace(name, value);
		}
		inline void set_value(const string& name, float value)
		{
			m_float_storage.emplace(name, value);
		}

		size_t size(const DataType type) const ;
		size_t total_size() const;
	private:
		template<typename T>
		inline Status __get_value(unordered_map<string, T>& container, 
								const string& name, 
								T& value)const;
	private:
		unordered_map<string, bool> m_bool_storage;
		unordered_map<string, int> m_int_storage;
		unordered_map<string, float> m_float_storage;
	};


	template<typename T>
	inline Status DataStorage::__get_value(unordered_map<string, T>& container, 
										 const string & name, 
										 T& value) const
	{

		auto it = container.find(name);
		if (it != container.end())
		{
			value = it->second;
			return Status::Succes;
		}
		return Status::Failure;
	}

}

