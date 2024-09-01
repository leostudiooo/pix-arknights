#include <functional>
#include <iostream>

void test_fn()
{
	std::cout << "Hello from test_fn" << std::endl;
}

int main()
{
	std::function<void()> fn = test_fn;
	fn();
	return 0;
}