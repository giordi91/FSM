#include "FSMFactory.h"
#include <assert.h>
namespace FSM
{
	FSMFactory::FSMFactory()
	{
	}


	FSMFactory::~FSMFactory()
	{
	}

	Condition * FSMFactory::generate_condtition(string data)
	{
		string type = FSM::Serialize::extract_type(data);
		ClassArgs args = FSM::Serialize::extract_args(data);

		auto fun_it = FSM::condition_map.find(type);
		if (fun_it != FSM::condition_map.end())
		{
			auto cond = fun_it->second(&m_dt, args);
			m_conditions.push(std::move(cond));
			auto ptr = m_conditions.top().get();
			return ptr;
		}
		else
		{
			return nullptr;

		}
	}

	Connection * FSMFactory::generate_connection(vector<string>& data)
	{
		//we first extract the connection row, since is expected to be the first
		//one , then an unspecified number of conditions
		string& conn = data[0];
		//we extract the args
		ClassArgs args = Serialize::extract_args(conn);
		assert(args.size() == 2);

		//we grab a pointer to the needed states by the connection,
		//the function will make sure that if they are not found they will
		//be created
		State * source = get_state(args[0]);
		State * destination = get_state(args[1]);

		//now we can pass the arguments to the constructor
		auto con = std::make_unique<Connection>(source, destination);
		//extract the pointer, so we don't need to re-query the map after
		//the smart pointer move
		Connection* p = con.get();

		//now we loop the data and generate all the condition, 
		//we use a counter to skip the first one, I think is better
		//to check the if statement a couple of times rather then 
		//re-allocate a subset, we could do that manually with iterators 
		//aswell
		int counter = 0;
		for (auto condData : data)
		{
			//skillping first iteration
			if (counter == 0)
			{
				counter++;
				continue;
			}

			//builidng the condition
			auto cond = generate_condtition(condData);
			assert(cond != nullptr);
			//adding it to the connection
			con->add_condition(cond);

		}
		//storing the connection and returning the pointer 
		m_connections.push(std::move(con));
		return p;

	}

	State * FSM::FSMFactory::generate_state(string & state_data,
		vector<vector<string>>& conn_data)
	{
		//for now we extract the args only since there is only one state type
		ClassArgs args = Serialize::extract_args(state_data);
		assert(args.size() == 1);

		State * st = get_state(args[0]);
		for (auto conn : conn_data)
		{
			auto newConn = generate_connection(conn);
			st->add_connection(newConn);
		}

		return st;
	}
}