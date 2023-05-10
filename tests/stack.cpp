#include "utils.hpp"

template <class T>
std::vector<int> pop_test(std::stack<T> stk) {
	std::vector<int> v;
	for (int i = 0; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start1 = timer();
	while (stk.size() > 0)
		stk.pop();
	g_end1 = timer();
	v.push_back(stk.size());
	return v;
}

template <class T>
std::vector<int> pop_test(_stack<T> stk) {
	std::vector<int> v;
	for (int i = 0; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start2 = timer();
	while (stk.size() > 0)
		stk.pop();
	g_end2 = timer();
	v.push_back(stk.size());
	return v;
}

template <class T>
std::vector<int> size_test(std::stack<T> stk) {
	std::vector<int> v;
	g_start1 = timer();
	for (int i = 0; i < 800 * _ratio; ++i)
		stk.push(i);
	g_end1 = timer();
	v.push_back(stk.size());
	return v;
}

template <class T>
std::vector<int> size_test(_stack<T> stk) {
	std::vector<int> v;
	g_start2 = timer();
	for (int i = 0; i < 800 * _ratio; ++i)
		stk.push(i);
	g_end2 = timer();
	v.push_back(stk.size());
	return v;
}

template <class T>
std::vector<int> top_test(std::stack<T> stk) {
	std::vector<int> v;
	for (int i = 0; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start1 = timer();
	v.push_back(stk.top());
	g_end1 = timer();
	stk.pop();
	v.push_back(stk.top());
	stk.push(7);
	v.push_back(stk.top());
	return v;
}

template <class T>
std::vector<int> top_test(_stack<T> stk) {
	std::vector<int> v;
	for (int i = 0; i < 200 * _ratio; ++i)
		stk.push(i);
	g_start2 = timer();
	v.push_back(stk.top());
	g_end2 = timer();
	stk.pop();
	v.push_back(stk.top());
	stk.push(7);
	v.push_back(stk.top());
	return v;
}

template <class T>
int run_stack_unit_test(std::string test_name, std::vector<int> (func1)(std::stack<T>), std::vector<int> (func2)(_stack<T>)) {
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::stack<int> stack;
	_stack<int> my_stack;

	printElement(test_name);
	res1 = func1(stack);
	res2 = func2(my_stack);
	if (res1 == res2) {
	    printElement("OK");
	}
	else {
	    printElement("FAILED");
	}
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	std::cout << std::endl;

	return 0;
}

int stack_test(void) {
    std::cout << "### STACK ###" << std::endl;
    run_stack_unit_test<int>("pop", &pop_test, &pop_test);
    run_stack_unit_test<int>("push", &size_test, &size_test);
    run_stack_unit_test<int>("top", &top_test, &top_test);
    return 0;
}
