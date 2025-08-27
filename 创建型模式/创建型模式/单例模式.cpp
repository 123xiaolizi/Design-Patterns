#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>
#include <queue>
//饿汉模式 在加载类的时候就创建好单例对象 饿汉模式是没有线程安全问题的
//单例模式的任务队列
class TaskQueue
{
public:
	TaskQueue(const TaskQueue&) = delete;
	TaskQueue& operator=(const TaskQueue&) = delete;
	static TaskQueue* getInstance()
	{
		return m_taskqueue;
	}
	void print()
	{
		std::cout << "这是一个饿汉模式创建的单例。。。" << std::endl;
	}
private:
	TaskQueue() = default;

	//需要类外初始化
	static TaskQueue* m_taskqueue;
};
//类外初始化
TaskQueue* TaskQueue::m_taskqueue = new TaskQueue();

//-------------------------------------------------------------------------------------------
//懒汉模式 在第一次调用getInstance的时候才创建单例对象
//使用双重检查锁定+原子变量来解决线程安全问题
class TaskQueue2
{
public:
	TaskQueue2(const TaskQueue2&) = delete;
	TaskQueue2& operator=(const TaskQueue2&) = delete;
	static TaskQueue2* getInstance()
	{
		TaskQueue2* task = m_taskqueue.load();
		if (task == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			task = m_taskqueue.load();
			if (task == nullptr)
			{
				task = new TaskQueue2();
				m_taskqueue.store(task);
			}
		}

		return task;
	}
	void print()
	{
		std::cout << "这是一个懒汉模式创建的单例。。。" << std::endl;
	}

private:
	TaskQueue2() = default;
	static std::atomic<TaskQueue2*> m_taskqueue;
	static std::mutex m_mutex;
};
std::atomic<TaskQueue2*> TaskQueue2::m_taskqueue;
std::mutex TaskQueue2::m_mutex;
//----------------------------------------------------------------------------
//利用静态的局部对象解决线程安全问题 - > 编译器必须支持c++11
class TaskQueue3
{
public:
	TaskQueue3(const TaskQueue3&) = delete;
	TaskQueue3& operator=(const TaskQueue3&) = delete;
	static TaskQueue3* getInstance()
	{
		static TaskQueue3 task;
		return &task;
	}
	void print()
	{
		std::cout << "这是一个懒汉模式创建的单例(局部静态变量解决线程安全问题)。。。" << std::endl;
	}

private:
	TaskQueue3() = default;

};


//写一个任务队列,测试
class TaskQueue4
{
public:
	TaskQueue4(const TaskQueue4&) = delete;
	TaskQueue4& operator=(const TaskQueue4&) = delete;
	static TaskQueue4* getInstance()
	{
		TaskQueue4* task = m_taskqueue.load();
		if (task == nullptr)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			task = m_taskqueue.load();
			if (task == nullptr)
			{
				task = new TaskQueue4();
				m_taskqueue.store(task);
			}
		}

		return task;
	}
	// 判断任务队列是否为空
	bool isEmpty()
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		bool flag = m_queue.empty();
		return flag;
	}
	// 添加任务
	void addTask(int node)
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		m_queue.push(node);
	}
	// 删除任务
	bool popTask()
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		if (m_queue.empty())
		{
			return false;
		}
		m_queue.pop();
		return true;
	}
	// 取出一个任务(不删除任务)
	int takeTask()
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		if (m_queue.empty())
		{
			return -1;
		}
		int data = m_queue.front();
		return data;
	}

private:
	TaskQueue4() = default;
	static std::atomic<TaskQueue4*> m_taskqueue;
	static std::mutex m_mutex;
	//存放任务的容器，这里简单测试而已
	std::queue<int> m_queue;
	//用于确保对容器操作线程安全
	std::mutex m_vecmtx;
};
std::atomic<TaskQueue4*> TaskQueue4::m_taskqueue;
std::mutex TaskQueue4::m_mutex;

#if 0
int main(char* argc, char** argv)
{
	TaskQueue::getInstance()->print();
	TaskQueue2* task2 = TaskQueue2::getInstance();
	task2->print();
	TaskQueue3::getInstance()->print();


	TaskQueue4* taskQ = TaskQueue4::getInstance();

	// 生产者
	std::thread t1([=]()
		{
			for (int i = 0; i < 10; ++i)
			{
				taskQ->addTask(i + 100);
				std::cout << "+++ push data: " << i + 100 << ", threadID: " <<
					std::this_thread::get_id() << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		});

	// 消费者
	std::thread t2([=]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			while (!taskQ->isEmpty())
			{
				int num = taskQ->takeTask();
				std::cout << "+++ take data: " << num << ", threadID: " <<
					std::this_thread::get_id() << std::endl;
				taskQ->popTask();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});

	t1.join();
	t2.join();
	return 0;
}

#endif