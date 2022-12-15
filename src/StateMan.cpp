#include "StateMan.hpp"

Engine::StateMan::StateMan() : m_add(false), m_pop(false), m_replace(false)
{}

Engine::StateMan::~StateMan() {}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd)
{
	m_add = true;
	m_newAddState = std::move(toAdd);
}

void Engine::StateMan::PopCurrent() {m_pop = true;}

void Engine::StateMan::Replace(std::unique_ptr<State> replaceState)
{
	m_replace = true;
	m_newReplaceState = std::move(replaceState);
}

void Engine::StateMan::ProcessStateChange()
{
	if (m_pop)//pop
	{
		if (!m_stateStack.empty()) { m_stateStack.pop(); }
		m_pop = false;
		if (!m_stateStack.empty()) { m_stateStack.top()->Start(); }
	}

	if (m_add)//add
	{
		if (!m_stateStack.empty()) { m_stateStack.top()->Pause(); }
		
		m_stateStack.push(std::move(m_newAddState));
		
		m_stateStack.top()->Init();
		m_stateStack.top()->Start();
		
		m_add = false;
	}

	if (m_replace)//replace
	{
		if (!m_stateStack.empty()) { m_stateStack.pop(); }
		
		m_stateStack.push(std::move(m_newReplaceState));
		
		m_stateStack.top()->Init();
		m_stateStack.top()->Start();
		
		m_replace = false;
	}
}

std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent()
{
	return m_stateStack.top();
}