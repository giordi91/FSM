#include "DataStorage.h"
#include <iostream>

namespace FSM
{
	Status DataStorage::get_value(const string & name, bool & value)
	{
		return __get_value<bool>(m_bool_storage, name, value);
	}
	Status DataStorage::get_value(const string & name, int & value)
	{
		return __get_value<int>(m_int_storage, name, value);
	}
	Status DataStorage::get_value(const string & name, float & value)
	{
		return __get_value<float>(m_float_storage, name, value);
	}
	size_t DataStorage::size(const DataType type) const
	{
		switch (type)
		{
		case DataType::BOOL:
		{
			return m_bool_storage.size();
		}

		case DataType::FLOAT:
		{
			return m_float_storage.size();
		}
		case DataType::INT:
		{
			return m_int_storage.size();
		}
		default:
		{
			return 0;
		}
		}
	}
	size_t DataStorage::total_size() const
	{
		return m_bool_storage.size() +
			m_float_storage.size() +
			m_int_storage.size();
	}
}