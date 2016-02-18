#pragma once
#include <vector>
using std::vector;
using std::string;



namespace FSM
{
	class Connection;
	class  State
	{
	public:
		/**
		@bief constructor
		@param name: string represeting the name
		*/
		__declspec(dllexport)
		State(string name) :m_name(name) {}

		/**
		@brief adds a connection to the state
		@param conn: pointer to the connection we wish to add
		*/
		__declspec(dllexport)
		inline void add_connection(Connection * conn)
		{
			m_connections.push_back(conn);
		};
		~State() = default;

		/**
		@brief evaluates wheter there is need for a transition
		This function is going to evaluate all the connecitions and
		if one evaluate to true will return that a pointer to the next
		state. The order in which connections are added gives precedence.
		@returns : returns a pointer to the next state, if none of the
		connections evaluate to true will return a pointer to itself
		*/
		__declspec(dllexport)
		virtual State * transition() = 0;

		/**
		@brief Getter method for the state name
		@returns a const ref to the name
		*/
		__declspec(dllexport)
		inline const string& get_name()const
		{
			return m_name;
		}

		virtual const string serialize() const = 0;
		
		__declspec(dllexport)
		inline const void  set_name(string& name)
		{
			m_name = name;
		}

	protected:
		//storagfe for the connection pointers
		vector<Connection*> m_connections;
		//the state name
		string m_name;
	};

	class GenericState: public State 
	{
	public:
		GenericState(string name) : State(name) {}
		/**
		@brief evaluates wheter there is need for a transition
		This function is going to evaluate all the connecitions and
		if one evaluate to true will return that a pointer to the next
		state. The order in which connections are added gives precedence.
		@returns : returns a pointer to the next state, if none of the
		connections evaluate to true will return a pointer to itself
		*/
		__declspec(dllexport)
		virtual State * transition() override;

		__declspec(dllexport)
		virtual const string serialize() const override;

	private:
		static const string m_class_name;

	};
}

