#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>
#include <queue>
//����ģʽ �ڼ������ʱ��ʹ����õ������� ����ģʽ��û���̰߳�ȫ�����
//����ģʽ���������
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
		std::cout << "����һ������ģʽ�����ĵ���������" << std::endl;
	}
private:
	TaskQueue() = default;

	//��Ҫ�����ʼ��
	static TaskQueue* m_taskqueue;
};
//�����ʼ��
TaskQueue* TaskQueue::m_taskqueue = new TaskQueue();

//-------------------------------------------------------------------------------------------
//����ģʽ �ڵ�һ�ε���getInstance��ʱ��Ŵ�����������
//ʹ��˫�ؼ������+ԭ�ӱ���������̰߳�ȫ����
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
		std::cout << "����һ������ģʽ�����ĵ���������" << std::endl;
	}

private:
	TaskQueue2() = default;
	static std::atomic<TaskQueue2*> m_taskqueue;
	static std::mutex m_mutex;
};
std::atomic<TaskQueue2*> TaskQueue2::m_taskqueue;
std::mutex TaskQueue2::m_mutex;
//----------------------------------------------------------------------------
//���þ�̬�ľֲ��������̰߳�ȫ���� - > ����������֧��c++11
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
		std::cout << "����һ������ģʽ�����ĵ���(�ֲ���̬��������̰߳�ȫ����)������" << std::endl;
	}

private:
	TaskQueue3() = default;

};


//дһ���������,����
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
	// �ж���������Ƿ�Ϊ��
	bool isEmpty()
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		bool flag = m_queue.empty();
		return flag;
	}
	// �������
	void addTask(int node)
	{
		std::lock_guard<std::mutex> locker(m_vecmtx);
		m_queue.push(node);
	}
	// ɾ������
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
	// ȡ��һ������(��ɾ������)
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
	//������������������򵥲��Զ���
	std::queue<int> m_queue;
	//����ȷ�������������̰߳�ȫ
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

	// ������
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

	// ������
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