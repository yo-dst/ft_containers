#include "utils.hpp"

template <class T, class V, class C>
void fillMap(std::map<T, V, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}

template <class T, class V, class C>
void fillMap(_map<T, V, C> &mp) {
	mp.insert(_make_pair(16, 3));
	mp.insert(_make_pair(8, 3));
	mp.insert(_make_pair(23, 3));
	mp.insert(_make_pair(7, 3));
	mp.insert(_make_pair(19, 3));
	mp.insert(_make_pair(29, 3));
	mp.insert(_make_pair(41, 3));
	mp.insert(_make_pair(4, 3));
	mp.insert(_make_pair(11, 3));
}

template <class T, class V>
std::vector<int> insert_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::pair<std::map<int, int>::iterator , bool> pair = mp.insert(std::make_pair(7, 7));
    std::map<int, int>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second);
    mp.insert(std::make_pair(9, 9));
    std::pair<std::map<int, int>::iterator , bool> pair2 = mp.insert(std::make_pair(9, 9));
    std::map<int, int>::iterator it2 = pair.first;
    v.push_back(it2->first);
    v.push_back(it2->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second);
    g_start1 = timer();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    g_end1 = timer();
    typename std::map<T, V>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    v.push_back(mp.size());
    return v;
}

template <class T, class V>
std::vector<int> insert_test(_map<T, V> mp) {
    std::vector<int> v;
    _pair<_map<int, int>::iterator , bool> pair = mp.insert(_make_pair(7, 7));
    _map<int, int>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second);
    mp.insert(_make_pair(9, 9));
    _pair<_map<int, int>::iterator , bool> pair2 = mp.insert(_make_pair(9, 9));
    _map<int, int>::iterator it2 = pair.first;
    v.push_back(it2->first);
    v.push_back(it2->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second);
    g_start2 = timer();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    g_end2 = timer();
    typename _map<T, V>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    v.push_back(mp.size());
    return v;
}

template <class T, class V>
std::vector<int> erase_test_1(std::map<T, V> mp) {
    std::vector<int> v;
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    typename std::map<T, V>::iterator it4 = mp.begin();
    g_start1 = timer();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
    g_end1 = timer();
    v.push_back(mp.erase(30 * _ratio - 1));
    v.push_back(mp.size());
    std::map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    typename std::map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> erase_test_1(_map<T, V> mp) {
    std::vector<int> v;
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    typename _map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    typename _map<T, V>::iterator it4 = mp.begin();
    g_start2 = timer();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
    g_end2 = timer();
    v.push_back(mp.erase(30 * _ratio - 1));
    v.push_back(mp.size());
    _map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    typename _map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

template <class T, class V>
std::vector<int>    iterators_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::map<T, V> mpp;
    fillMap(mpp);
    for (typename std::map<T, V>::iterator it = mpp.begin(); it != mpp.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mpp.end(); it != mpp.begin(); it--) { v.push_back(it->first); }
    std::map<int, int> mp0;
    std::map<int, int>::iterator ii = mp0.insert(std::make_pair(3, 3)).first;
    ii++;
    v.push_back((--ii)->first);
    for (int i = 0, j = 10; i < 5; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator it = mp.begin();
    typename std::map<T, V>::iterator it2 = mp.end();
    g_start1 = timer();
    v.push_back(it->first);
    it++;
    it++;
    it++;
    it++;
    v.push_back(it->first);
    it++;
    it--;
    v.push_back(it->first);
    it2--;
    v.push_back(it2->first);
    v.push_back(it2 == it);
    v.push_back((--it2)->first);
    v.push_back((it2--)->first);
    v.push_back((it2++)->first);
    v.push_back((++it2)->first);
    g_end1 = timer();
    return v;
}

template <class T, class V>
std::vector<int> iterators_test(_map<T, V> mp) {
    std::vector<int> v;
    _map<T, V> mpp;
    fillMap(mpp);
    for (typename _map<T, V>::iterator it = mpp.begin(); it != mpp.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mpp.end(); it != mpp.begin(); it--) { v.push_back(it->first); }
    _map<int, int> mp0;
    _map<int, int>::iterator ii = mp0.insert(_make_pair(3, 3)).first;
    ii++;
    v.push_back((--ii)->first);
    for (int i = 0, j = 10; i < 5; ++i, ++j)
        mp.insert(_make_pair(i, j));
    typename _map<T, V>::iterator it = mp.begin();
    typename _map<T, V>::iterator it2 = mp.end();
    g_start2 = timer();
    v.push_back(it->first);
    it++;
    it++;
    it++;
    it++;
    v.push_back(it->first);
    it++;
    it--;
    v.push_back(it->first);
    it2--;
    v.push_back(it2->first);
    v.push_back(it2 == it);
    v.push_back((--it2)->first);
    v.push_back((it2--)->first);
    v.push_back((it2++)->first);
    v.push_back((++it2)->first);
    g_end2 = timer();
    return v;
}

template <class T, class V>
std::vector<int> find_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = -75 * _ratio, j = 0; i < 75 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    g_start1 = timer();
    typename std::map<T, V>::iterator it = mp.find(34 * _ratio);
    g_end1 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-34 * _ratio);
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-75 * _ratio);
    if (it == mp.end())
        v.push_back(1);
    return v;
}

template <class T, class V>
std::vector<int> find_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = -75 * _ratio, j = 0; i < 75 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    g_start2 = timer();
    typename _map<T, V>::iterator it = mp.find(34 * _ratio);
    g_end2 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-34 * _ratio);
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-75 * _ratio);
    if (it == mp.end())
        v.push_back(1);
    return v;
}

template <class T, class V>
int run_map_unit_test(std::string test_name, std::vector<int> (func1)(std::map<T, V>), std::vector<int> (func2)(_map<T, V>)) {
	time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::map<int, int> map;
	_map<int, int> my_map;

	printElement(test_name);
	res1 = func1(map);
	res2 = func2(my_map);
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

	return (0);
}

int map_test(void) {
    std::cout << "### MAP ###" << std::endl;
    run_map_unit_test<int, int>("insert", &insert_test, &insert_test);
    run_map_unit_test<int, int>("erase", &erase_test_1, &erase_test_1);
    run_map_unit_test<int, int>("iterator", &iterators_test, &iterators_test);
    run_map_unit_test<int, int>("find", &find_test, &find_test);
    return 0;
}