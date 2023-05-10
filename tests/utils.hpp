#ifndef UTILS_HPP
#define UTILS_HPP

#include <ctime>
#include <sys/time.h>
#include <iomanip>
#include "../vector.hpp"
#include <vector>
#include <iostream>
#include <list>
#include <unistd.h>
#include <map>
#include "../map.hpp"
#include <set>
#include "../set.hpp"
#include <stack>
#include "../stack.hpp"

#define _vector ft::vector
#define _map ft::map
#define _stack ft::stack
#define _set ft::set
#define _pair ft::pair
#define _make_pair ft::make_pair

static time_t g_start1;
static time_t g_end1;
static time_t g_start2;
static time_t g_end2;

static int _ratio = 10000;

static const std::string GREEN = "\x1B[1;32m";
static const std::string REDD = "\x1B[1;31m";
static const std::string YELLOW = "\x1B[1;33m";
static const std::string WHITE = "\x1B[1;39m";
static const std::string RESET = "\033[0m";

static time_t timer(void) {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

static void printElement(std::string t) {
	if (t == "OK")
	    t = GREEN + t + RESET;
	else if (t == "FAILED")
		t = REDD + t + RESET;
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}

#endif