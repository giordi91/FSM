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
		
		/**
		@brief getter function for a boolean value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, bool& value);

		/**
		@brief getter function for a int value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, int& value);
		
		/**
		@brief getter function for a float value
		This is a getter function for the given key, if no value is present
		a Staus::Failure is returned
		@param key: the string key for the value
		@param value: a variable reference of the correct type that will be filled
					  with the correct value if found, otherwise untouched
		@returns: Status, wheter the key was found in the container or not
		*/
		Status get_value(const string& name, float& value);

		/**
		@brief setter function for a bool value
		@param key: the string key for the value
		@param value: the value we want to store 
		*/
		inline void set_value(const string& name, bool value) 
		{
			m_bool_storage[name]= value;
		}
		
		/**
		@brief setter function for a int value
		@param key: the string key for the value
		@param value: the value we want to store 
		*/
		inline void set_value(const string& name, int value)
		{
			m_int_storage[name]= value;
		}

		/**
		@brief setter function for a float value
		@param key: the string key for the value
		@param value: the value we want to store 
		*/
		inline void set_value(const string& name, float value)
		{
			m_float_storage[name]= value;
		}
		/**
		@brief: Gets the size of a specific internal container
		@param type: this argument will define which kind of internal container
					 gets picked up for getting the size
		@returns: the size of the wanted internal container
		*/
		size_t size(const DataType type) const ;
		/**
		@brief: Gets the combined size of all the internal container 
		@returns: the combined size of all the containers
		*/
		size_t total_size() const;
	private:
		/* templated inlined getter function 
		 @param container: reference to the wanted container
		 @param name: the key to get
		 @param value: reference to the variable to fill with the value if found
		 @returns : status, whether the key was part of the container or not
		 */
		template<typename T>
		inline Status __get_value(unordered_map<string, T>& container, 
								const string& name, 
								T& value)const;
	private:
		//the bool container
		unordered_map<string, bool> m_bool_storage;
		//the int container
		unordered_map<string, int> m_int_storage;
		//the float container
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

