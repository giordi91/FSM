// ConsoleApplication2.cpp : main project file.

#include "stdafx.h"
#include "State.h"
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
using namespace System;


namespace FSMWrapper
{
	public ref class StateWrapper
	{
	private:
		FSM::State * _state;
	public:
		StateWrapper()
		{
			_state = new FSM::GenericState("Fuffa");
		};

		~StateWrapper()
		{
			delete _state;
			_state = nullptr;
		}

		String^ get_name()
		{
			return msclr::interop::marshal_as<String^>(_state->get_name());
		}

		int getInt()
		{
			return 10;
		}

	};

}
int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	FSMWrapper::StateWrapper s;
	//std::cout << s.get_name() << std::endl;;
	system("pause");
    return 0;
}
