#include <assert.h>
#include <memory.h>


namespace ADML {

	template <class T>
	class MyQueue
	{
	public:

		MyQueue() = default;

		MyQueue(const MyQueue& other)
		{
			m_Capacity = other.m_Capacity;
			m_Size = other.m_Size;
			m_Memory = new T[m_Capacity];
			memcpy(m_Memory, other.m_Memory, m_Size * sizeof(T));
		}

		// This adds an element to the back of the Queue
		void push(T value)
		{
			if (m_Size == m_Capacity)
			{
				m_Capacity = (m_Capacity + 1) + (size_t)(m_Capacity * 0.3f);
				T* newAddress = new T[m_Capacity];
				memcpy(newAddress, m_Memory, m_Size * sizeof(T));
				delete[] m_Memory;
				m_Memory = newAddress;
			}

			m_Memory[m_Size] = value;
			m_Size++;
		}

		// This returns the Size
		size_t size() { return m_Size; }

		// This returns if the Queue is empty
		bool empty() { return m_Size == 0; }

		// This returns the next element in the Queue
		T& front() 
		{ 
			assert(m_Size > 0 && "There is no valid memory to access");
			return m_Memory[0];
		}
		
		// This returns the last element in the Queue
		T& back() 
		{ 
			assert(m_Size > 0 && "There is no valid memory to access");
			return m_Memory[m_Size - 1];
		}

		// This returns the next element in the Queue, while also removing it from the Queue
		T pop()
		{
			assert(m_Size > 0 && "There is no valid memory to access");
			T temp = m_Memory[0];
			m_Memory = m_Memory + 1;
			m_Size--;
			return temp;
		}

		T* m_Memory = nullptr;
		size_t m_Size = 0;
		size_t m_Capacity = 0;



	};
}