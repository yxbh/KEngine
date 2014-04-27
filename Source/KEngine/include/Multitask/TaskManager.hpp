#pragma once
#include "../engine_common.hpp"
#include "../Utility/NonCopyable.hpp"
#include "Types.hpp"
#include "../Common/Time.hpp"

namespace ke
{

/** \class TaskManager
*/
class TaskManager
    : public ke::NonCopyable
{
private:
    ke::TaskSPList  m_TaskSPList;

public:
    TaskManager(void) = default;
    ~TaskManager(void);

    /** Update all tasks with elapsed time and return the number of succeed tasks and the number of failed & aborted tasks. */
    std::uint32_t updateAllTasks(const ke::Time p_Elapsed);
    /** Add task to the task manager and return a weak pointer to the given task. */
    ke::TaskWPtr add(ke::TaskSPtr p_TaskSP);
    /** Abort and remove all tasks*/
    void abortAll(const bool p_Immediately = true);
    /** Get the number of task the task manager is currently managing. */
    unsigned getTaskCount(void) const;

private:
    /** Empty the internal task list. */
    void clear(void);

};

} // KE ns
