#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace Engine
{
	class WorkerThread
	{
	public:
		WorkerThread();
		~WorkerThread();

		void ExitThread();

		void AddToQueue(std::function<void()> callback);

	private:
		void Process();

		std::atomic<bool> m_processingFlag{ true };
		std::thread m_thread;
		std::queue<std::function<void()>> m_queue;
		std::mutex m_mutex;
		std::condition_variable m_cv;
	};
}

