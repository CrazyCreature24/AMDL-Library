#include <assert.h>
#include <memory.h>
#include <initializer_list> 
#include <utility>
#include <queue>
#include "MyVector.hpp"
#include "MyQueue.hpp"


// natstepfilter // Helps for preventing stepping into useless functions

void MyVectorTests();

void MyQueueTests();

using namespace ADML;


int main()
{
	//MyVectorTests();

	MyQueueTests();

}

void MyVectorTests()
{
	MyVector<int> numbers;
	assert(numbers.size() == 0);
	assert(numbers.capacity() == 0);

	MyVector<int>::iterator it = numbers.begin();
	assert(it == numbers.end());

	int bp = 1;

	numbers.push_back(10);
	assert(numbers.size() == 1);
	assert(numbers[0] == 10);
	numbers[0] = 12;
	assert(numbers[0] == 12);

	assert(numbers.at(0) == 12);
	assert(*(numbers.begin()) == 12);
	assert(numbers.capacity() == 1);

	numbers.push_back(20);
	assert(numbers.size() == 2);
	assert(numbers[1] == 20);
	assert(numbers.at(0) == 12);
	assert(numbers.at(1) == 20);
	assert(*(numbers.begin()) == 12);
	*(numbers.begin()) = 12;
	assert(*(numbers.begin() + 1) == 20);
	assert(numbers.capacity() == 2);

	const MyVector<int> b(numbers);
	assert(b.size() == 2);
	assert(b[0] == 12);
	//b[0] = 12;
	assert(b[1] == 20);
	assert(b.at(0) == 12);
	assert(b.at(1) == 20);
	assert(*(b.begin()) == 12);
	// *(b.begin()) = 12; Should be illegal, no modifying const
	assert(*(b.begin() + 1) == 20);
	assert(b.capacity() == 2);

	numbers.pop_back();
	assert(numbers.size() == 1);
	assert(numbers[0] == 12);
	assert(numbers.at(0) == 12);
	assert(*(numbers.begin()) == 12);
	assert(numbers.capacity() == 2);


	MyVector<int> c({ 5, 15 });
	assert(c.size() == 2);

	MyVector<int> d = c; // This works
	//d = c; // This needs a new assignment operator overload
	assert(d.size() == 2);

	MyVector<int> e = { 5, 15 };
	assert(e.size() == 2);

	MyVector<int> f(std::move(c));
	assert(c.size() == 0);
	c.push_back(1);
	assert(f.size() == 2);
}

void MyQueueTests()
{
	ADML::MyQueue<int> a;
	assert(a.size() == 0);
	a.push(2);
	assert(a.size() == 1);
	assert(a.empty() == false);
	a.push(5);
	a.push(8);
	assert(a.size() == 3);
	assert(a.front() == 2);
	assert(a.back() == 8);
	assert(a.pop() == 2);
	assert(a.size() == 2);
	


}
