#include "../../include/Multitask/TaskManager.hpp"
#include "../../include/Multitask/Task.hpp"

namespace ke
{

TaskManager::~TaskManager(void)
{
    this->clear();
}

std::uint32_t TaskManager::updateAllTasks(const ke::Time p_Elapsed)
{
    std::uint32_t success_count = 0, fail_count = 0;
    ke::TaskSPList::iterator tasksp_it(m_TaskSPList.begin());
    while (tasksp_it != m_TaskSPList.end())
    {
        ke::TaskSPtr task_sp(*tasksp_it);

        // get temp it for erase.
        ke::TaskSPList::const_iterator temp_cit(tasksp_it);
        ++tasksp_it;

        // Init if havn't done so.
        if (task_sp->getState() == Task::State::Uninitialized)
            task_sp->initialise();

        // Update if running.
        if (task_sp->getState() == Task::State::Running)
            task_sp->update(p_Elapsed);

        if (task_sp->isDead())
        {
            switch (task_sp->getState())
            {
            case Task::State::Succeeded:
            {
                task_sp->onSuccess();
                // task successfully completed. increment success count.
                ++success_count;

                // add child tasks if there're any.
                for (ke::TaskSPtr new_task_sp : task_sp->getChildTasks())
                {
                    if (new_task_sp)
                        this->add(new_task_sp);
                }
                if (!task_sp->getChildTasks().empty())
                    task_sp->getChildTasks().clear();

                break;
            }

            case Task::State::Failed:
            {
                task_sp->onFail();
                ++fail_count;
                break;
            }

            case Task::State::Aborted:
            {
                task_sp->onAbort();
                ++fail_count;
                break;
            }
            } // end switch
        } // end if
    } // end while (tasksp_it != m_TaskSPList.end())
    return ((success_count << 16) | fail_count); // compress success count in upper 16 bit and fail count in the lower 16 bit. Assume both counts will never exceed 65,535.
}

ke::TaskWPtr TaskManager::add(ke::TaskSPtr p_TaskSP)
{
    m_TaskSPList.push_front(p_TaskSP);
    return TaskWPtr(p_TaskSP);
}

void TaskManager::abortAll(const bool p_Immediately)
{
    ke::TaskSPList::iterator it(m_TaskSPList.begin());
    while (it != m_TaskSPList.end())
    {
        ke::TaskSPList::const_iterator temp_it(it);
        ++it;

        ke::TaskSPtr task_sp(*temp_it);
        if (task_sp->isAlive())
        {
            task_sp->setState(ke::Task::State::Aborted);
            if (p_Immediately)
            {
                task_sp->onAbort();
                m_TaskSPList.erase(temp_it);
            }
        } // end if (task_sp->isAlive())
    } // end whilte
}

void TaskManager::clear(void)
{
    m_TaskSPList.clear();
}

} // KE ns
