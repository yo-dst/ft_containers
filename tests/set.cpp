#include "utils.hpp"

template <class T, class C>
void fillSet(std::set<T, C> &mp) {
	mp.insert(16);
	mp.insert(8);
	mp.insert(23);
	mp.insert(7);
	mp.insert(19);
	mp.insert(29);
	mp.insert(41);
	mp.insert(4);
	mp.insert(11);
}

template <class T, class C>
void fillSet(_set<T, C> &mp) {
	mp.insert(16);
	mp.insert(8);
	mp.insert(23);
	mp.insert(7);
	mp.insert(19);
	mp.insert(29);
	mp.insert(41);
	mp.insert(4);
	mp.insert(11);
}

template <class T>
std::vector<int> insert_test_2(std::set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    std::set<int> st2;
    g_start1 = timer();
    st2.insert(st.begin(), st.end());
    g_end1 = timer();
    typename std::set<T>::iterator it2 = st2.begin();
    for (; it2 != st2.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int> insert_test_2(_set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    _set<int> st2;
    g_start2 = timer();
    st2.insert(st.begin(), st.end());
    g_end2 = timer();
    typename _set<T>::iterator it2 = st2.begin();
    for (; it2 != st2.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int>    iterators_test(std::set<T> st) {
    std::vector<int> v;
    std::set<T> stt;
    fillSet(stt);
    for (typename std::set<T>::iterator it = stt.begin(); it != stt.end(); it++) { v.push_back(*it); }
    for (typename std::set<T>::iterator it = --stt.end(); it != stt.begin(); it--) { v.push_back(*it); }
    std::set<int> mp0;
    std::set<int>::iterator ii = mp0.insert(3).first;
    ii++;
    v.push_back(*(--ii));
    for (int i = 0; i < 5; ++i)
        st.insert(i);
    typename std::set<T>::iterator it = st.begin();
    typename std::set<T>::iterator it2 = st.end();
    g_start1 = timer();
    v.push_back(*it);
    it++;
    it++;
    it++;
    it++;
    v.push_back(*it);
    it++;
    it--;
    v.push_back(*it);
    it2--;
    v.push_back(*it2);
    v.push_back(it2 == it);
    v.push_back(*(--it2));
    v.push_back(*(it2--));
    v.push_back(*(it2++));
    v.push_back(*(++it2));
    g_end1 = timer();
    return v;
}

template <class T>
std::vector<int> iterators_test(_set<T> st) {
    std::vector<int> v;
    _set<T> stt;
    fillSet(stt);
    for (typename _set<T>::iterator it = stt.begin(); it != stt.end(); it++) { v.push_back(*it); }
    for (typename _set<T>::iterator it = --stt.end(); it != stt.begin(); it--) { v.push_back(*it); }
    _set<int> mp0;
    _set<int>::iterator ii = mp0.insert(3).first;
    ii++;
    v.push_back(*(--ii));
    for (int i = 0; i < 5; ++i)
        st.insert(i);
    typename _set<T>::iterator it = st.begin();
    typename _set<T>::iterator it2 = st.end();
    g_start2 = timer();
    v.push_back(*it);
    it++;
    it++;
    it++;
    it++;
    v.push_back(*it);
    it++;
    it--;
    v.push_back(*it);
    it2--;
    v.push_back(*it2);
    v.push_back(it2 == it);
    v.push_back(*(--it2));
    v.push_back(*(it2--));
    v.push_back(*(it2++));
    v.push_back(*(++it2));
    g_end2 = timer();
    return v;
}

template <class T>
std::vector<int> erase_test_1(std::set<T> st) {
    std::vector<int> v;
    v.push_back(st.erase(3));
    for (int i = 0; i < 30 * _ratio; ++i)
        st.insert(i);
    typename std::set<T>::iterator it = st.begin();
    v.push_back(*it);
    v.push_back(st.erase(-5));
    v.push_back(st.size());
    v.push_back(st.erase(0));
    v.push_back(st.size());
    typename std::set<T>::iterator it4 = st.begin();
    g_start1 = timer();
    for (; it4 != st.end(); it4 = st.begin())
        st.erase(*it4);
    g_end1 = timer();
    v.push_back(st.erase(30 * _ratio - 1));
    v.push_back(st.size());
    std::set<int> st2;
    for (int i = 0; i < 10 ; ++i)
        st2.insert(i);
    st2.erase(2);
    st2.erase(7);
    typename std::set<T>::iterator it3 = st2.begin();
    for (; it3 != st2.end(); ++it3) {
        v.push_back(*it3);
    }
    return v;
}

template <class T>
std::vector<int> erase_test_1(_set<T> st) {
    std::vector<int> v;
    v.push_back(st.erase(3));
    for (int i = 0; i < 30 * _ratio; ++i)
        st.insert(i);
    typename _set<T>::iterator it = st.begin();
    v.push_back(*it);
    v.push_back(st.erase(-5));
    v.push_back(st.size());
    v.push_back(st.erase(0));
    v.push_back(st.size());
    typename _set<T>::iterator it4 = st.begin();
    g_start2 = timer();
    for (; it4 != st.end(); it4 = st.begin())
        st.erase(*it4);
    g_end2 = timer();
    v.push_back(st.erase(30 * _ratio - 1));
    v.push_back(st.size());
    _set<int> st2;
    for (int i = 0; i < 10 ; ++i)
        st2.insert(i);
    st2.erase(2);
    st2.erase(7);
    typename _set<T>::iterator it3 = st2.begin();
    for (; it3 != st2.end(); ++it3) {
        v.push_back(*it3);
    }
    return v;
}

template <class T>
int run_set_unit_test(std::string test_name, std::vector<int> (func1)(std::set<T>), std::vector<int> (func2)(_set<T>)) {
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::set<int> set;
	_set<int> my_set;

	printElement(test_name);
	res1 = func1(set);
	res2 = func2(my_set);
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

int set_test(void) {
    std::cout << "### SET ###" << std::endl;
    run_set_unit_test<int>("insert", &insert_test_2, &insert_test_2);
    run_set_unit_test<int>("erase", &erase_test_1, &erase_test_1);
    run_set_unit_test<int>("iterator", &iterators_test, &iterators_test);
    return 0;
}
