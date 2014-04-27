#include "../../include/Multitask/Task.hpp"

namespace ke
{

Task::Task(void)
    : m_State(ke::Task::State::Uninitialized)
{}

Task::~Task(void)
{}

void Task::initialise(void)
{
    m_State = ke::Task::State::Running;
}

void Task::onSuccess(void)
{}

void Task::onFail(void)
{}

void Task::onAbort(void)
{}

void Task::setSucceed(void)
{
    assert(m_State == State::Running || m_State == State::Paused);
    m_State = State::Succeeded;
}

void Task::setFailed(void)
{
    assert(m_State == State::Running || m_State == State::Paused);
    m_State = State::Failed;
}

void Task::setPaused(void)
{
    if (this->isRunning())
        m_State = State::Paused;
    else
        ke::Debug::printWarning("Task::SetPaused : attempting to pause a task that is not running!");
}

void Task::setUnpaused(void)
{
    if (this->isPaused())
        m_State = State::Running;
    else
        ke::Debug::printWarning("Task::SetUnpaused : attempting to unpause a task that is not paused!");
}

Task::State Task::getState(void) const
{
    return m_State;
}

ke::TaskSPVector & Task::getChildTasks(void)
{
    return m_ChildTasks;
}

bool Task::isAlive(void) const
{
    return ((m_State == State::Running) || (m_State == State::Paused));
}

bool Task::isDead(void) const
{
    return ((m_State == State::Succeeded) || (m_State == State::Failed) || (m_State == State::Aborted));
}

bool Task::isRunning(void) const
{
    return m_State == State::Running;
}

bool Task::isRemoved(void) const
{
    return m_State == State::Removed;
}

bool Task::isPaused(void) const
{
    return m_State == State::Paused;
}

void Task::setState(const Task::State p_NewState)
{
    m_State = p_NewState;
}

}
