#pragma once

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace FSM
{
	/**
	Simple enum defining the kind of data type supported by the storage
	*/
	enum class DataType
	{
		BOOL =0,
		INT,
		FLOAT
	};
	
	/*
	Enum defining statuses returned
	*/
	enum class Status
	{
		Succes=0,
		Failure
	};
	/**
	@brief This class wraps a container around different types, data can be accessed with
	string key
	*/	
	class DataStorage
	{
	public:
		/** constructor */
		DataStorage() = default;
		/** destructor */
		~DataStorage() = default;
		
		/*
		@brief getter function for a boolean value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, bool& value);

		/*
		@brief getter function for a int value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, int& value);
		
		/*
		@brief getter function for a float value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, float& value);



		/*
		@brief setter function for a bool value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
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

