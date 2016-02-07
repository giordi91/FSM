#include "FSMFactory.h"
#include <assert.h>
#include <sstream>
#include <fstream>

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
		
		//grabbing the current state
		State * st = get_state(args[0]);
		for (auto conn : conn_data)
		{
			//generating all the condition and appending them to the state
			auto newConn = generate_connection(conn);
			st->add_connection(newConn);
		}

		//return pointer to the generate state
		return st;
	}

	FiniteStateMachine * FSM::FSMFactory::generate_fsm_from_file(string path)
	{
		std::ifstream infile(path);
		if (!infile.is_open())
		{
			std::cout << "error in opening the path" << std::endl;
			return nullptr;
		}

		std::string line;
		string fsm;
		getline(infile, fsm);
		auto f_type = Serialize::extract_type(fsm);
		auto f_name = Serialize::extract_args(fsm);
		assert(f_type.size() != 0);
		assert(f_name.size() == 1);

		//lets build the FSM 
		auto finite_state = std::make_unique<FiniteStateMachine>(f_name[0], &m_dt);
		FiniteStateMachine * ptr = finite_state.get();
		getline(infile, line);
		std::smatch type_match;
		std::regex_search(line, type_match, Serialize::REG_END_CONDITIONS);

		State * st;
		vector<string> connections;
		vector<vector<string>>conditions;
		vector<vector<string>> build_state_data;
		vector<string> conn_sub_data;
		conn_sub_data.clear();
		build_state_data.clear();
		connections.clear();
		conditions.clear();

		while (type_match.size() == 0)
		{
			Serialize::read_connection_from_file(infile, connections, conditions);
			int size = connections.size();
			for (int i = 0; i < size; ++i)
			{
				//building the data in the expected format
				conn_sub_data.push_back(connections[i]);
				int cond_size = conditions[i].size();
				for (int c = 0; c < cond_size; ++c)
				{
					conn_sub_data.push_back(conditions[i][c]);
				}
				build_state_data.push_back(conn_sub_data);
				conn_sub_data.clear();
			}
			
			st = generate_state(line, build_state_data);
			finite_state->add_state(st);
			
			conn_sub_data.clear();
			build_state_data.clear();
			connections.clear();
			conditions.clear();
			getline(infile, line);
			std::regex_search(line, type_match, Serialize::REG_END_STATES);

		}
		
		m_machines[f_name[0]] = std::move(finite_state);
		return ptr;
	}
}