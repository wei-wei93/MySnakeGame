#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
	class StateMan
	{
	private:
		std::stack<std::unique_ptr<State>> m_stateStack;
		std::unique_ptr<State> m_newAddState;
		std::unique_ptr<State> m_newReplaceState;

		bool m_add;
		bool m_pop;
		bool m_replace;
		
	public:
		StateMan();
		~StateMan();

		void Add(std::unique_ptr<State> toAdd);
		void PopCurrent();
		void Replace(std::unique_ptr<State> replaceState);
		void ProcessStateChange();
		std::unique_ptr<State>& GetCurrent();
	};
}


