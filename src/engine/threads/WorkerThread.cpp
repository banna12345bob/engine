#include "WorkerThread.h"

namespace Engine
{
	WorkerThread::WorkerThread()
	{
		m_thread = std::thread(&WorkerThread::Process, this);
	}

	WorkerThread::~WorkerThread()
	{
		ExitThread();
	}

	void WorkerThread::Process()
	{
		while (m_processingFlag)
		{
			// Check for work to be done
			std::function<void()> func;
			{
				std::unique_lock lk(m_mutex);	// Automatically unlocks after leaving scope.
				while (m_queue.empty())
				{
					// Unlocks the lock (so that AddToQueue can still run in case we missed the notification. As in, something was added to queue after checking if empty but before wating.
					// After being awakened, re-locks the lock.
					m_cv.wait(lk);
				}

				func = m_queue.front();
				m_queue.pop();
			}

			// Do the work without needing access to the queue. (The mutex is unlocked at this point, so AddToQueue can be used safely.)
			func();
		}
	}

	void WorkerThread::AddToQueue(std::function<void()> callback)
	{
		std::unique_lock lk(m_mutex);
		m_queue.push(callback);
		lk.unlock();		// Not exactly sure why this is necessary, but apparently it is.
		m_cv.notify_one();
	}

	void WorkerThread::ExitThread()
	{
		m_processingFlag = false;
		if (m_thread.joinable()) {
			std::function<void()> func = [this] {
				std::lock_guard lk(m_mutex);
				// DO NOTHING: just here to make sure the thread properly closes
			};

			// idk why but the worker thread only closes when one final function is added
			AddToQueue(func);

			m_thread.join();
		}
	}

}