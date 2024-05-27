#include <assert.h>
#include <memory.h>
#include <initializer_list> 
#include <utility>

namespace ADML {

	template <class T>
	class MyVector
	{
	public:

		class iterator
		{
		public:

			iterator(T* p) : _Ptr(p) {}

			T* _Ptr = nullptr;

			bool operator==(const iterator& o)
			{
				return _Ptr == o._Ptr;
			}

			T& operator*()
			{
				return *_Ptr;
			}

			const T& operator*() const
			{
				return *_Ptr;
			}

			iterator operator+(int o)
			{
				return iterator(_Ptr + o); // Pointer math, it increments by the size of the int. Compiler deals with it for you. (_Ptr + 4 bytes)
			}

			const iterator operator+(int o) const
			{
				return iterator(_Ptr + o);
			}
		};

	public:

		MyVector() = default; // initialized below.

		MyVector(const MyVector& other)
		{
			m_Capacity = other.m_Capacity;
			m_Size = other.m_Size;

			m_Memory = new T[m_Capacity];
			memcpy(m_Memory, other.m_Memory, m_Size * sizeof(T));
		}

		MyVector(std::initializer_list<T> iList) noexcept
		{
			m_Size = m_Capacity = iList.size();

			//memcpy(m_Memory, &iList, iList.size() * sizeof(T));

			m_Memory = new T[m_Capacity];

			for (int i = 0; i < m_Size; i++)
			{
				m_Memory[i] = *(iList.begin() + i);
			}

		}

		MyVector(MyVector&& o) noexcept
		{
			m_Memory = o.m_Memory;
			m_Size = o.m_Size;
			m_Capacity = o.m_Capacity;

			o.m_Memory = nullptr;
			o.m_Size = 0;
			o.m_Capacity = 0;
		}

		~MyVector()
		{
			delete[] m_Memory;
		}

		void push_back(T value)
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

		void pop_back()
		{
			m_Size--; // Could be better, but this works for now
		}

		size_t size() const { return m_Size; }
		size_t capacity() { return m_Capacity; }
		size_t capacity() const { return m_Capacity; }
		iterator begin() { return iterator(m_Memory); }
		const iterator begin() const { return iterator(m_Memory); }
		iterator end() { return iterator(m_Memory + m_Size); }

		const T& operator[](size_t index) const // Reference becase it needs to be modifiable
		{
			assert(index < m_Size && "Index out of bounds");
			return m_Memory[index];
		}

		T& operator[](size_t index) // Reference becase it needs to be modifiable
		{
			assert(index < m_Size && "Index out of bounds");
			return m_Memory[index];
		}

		const T& at(size_t index) const
		{
			assert(index < m_Size && "Index out of bounds");
			return m_Memory[index];
		}

		T* m_Memory = nullptr;
		size_t m_Size = 0;
		size_t m_Capacity = 0;





	};
}