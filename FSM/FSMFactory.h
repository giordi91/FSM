#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "Condition.h"
#include "DeSerialize.h"

using FSM::Condition;
using std::unordered_map;
using std::unique_ptr;
using std::string;


namespace FSM
{

	class FSMFactory
	{
	public:
		FSMFactory();
		~FSMFactory();

		Condition* generate_condtition(string data);

	private:

		vector<unique_ptr<Condition>> m_conditions;

	};

}

