#include "Types.hpp"
#include "../Common/Time.hpp"
#include "../engine_common.hpp"

namespace ke
{


/** \class Task
    \brief Subclass from this class to create meaningful task taht are managed and executed by a task manager.
*/
class Task
{
    friend class TaskManager;

public:
    /** Possible states of a Task. */
    enum class State
    {
        // neither dead nor alive
        Uninitialized,  // created but not running
        Removed,        // removed from the process list but not destoryed; e.g. already running but parented to another process.
        // living Task.
        Running,        // initialized and running
        Paused,         // initialized but not running.
        // dead
        Succeeded,      // completed successfully.
        Failed,         // failed to complete
        Aborted,        // aborted; may not have started.
    };

private:
    ke::Task::State     m_State;
    ke::TaskSPVector    m_ChildTasks;

public:
    Task(void);
    Task(const ke::Task &) = default;
    //Task(const ke::Task &&) = default;
    ke::Task & operator=(const Task &) = default;
    //ke::Task & operator=(const Task &&) = default;
    virtual ~Task(void);

protected:
    /** Called during the very first update. Carry out any task initialisation. */
    virtual void initialise(void);
    /** Run the task, given a delta. */
    virtual void update(const Time p_Delta) = 0;

    /* exit methods. One of the three will be called when a task has "finished". */
    /** Call when task state is 'Succeeded'. */
    virtual void onSuccess(void); // base class do nothing.
    /** Call when task state is 'Failed'. */
    virtual void onFail(void); // base class do nothing.
    /** Call when task state is 'Aborted'. */
    virtual void onAbort(void); // base class do nothing.

public:
    /** Set the task state to \a succeed. */
    void setSucceed(void);
    /** Set the task state to \a failed. */
    void setFailed(void);
    /** Set the task state to \a paused. */
    void setPaused(void);
    /** Set the task state to \a unpaused. */
    void setUnpaused(void);

    Task::State getState(void) const;
    ke::TaskSPVector & getChildTasks(void);

    /** @return true if this task is alive. */
    bool isAlive(void) const;
    /** @return true if this task is dead. */
    bool isDead(void) const;
    /** @return true if this task is running. */
    bool isRunning(void) const;
    /** @return true if this task is removed from the task manager. */
    bool isRemoved(void) const;
    /** @return true if this task is paused. */
    bool isPaused(void) const;

private:
    /** Set the state of the task to ]a p_NewState. */
    void setState(const Task::State p_NewState);

};

}