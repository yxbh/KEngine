#pragma once

// std includes
#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <cstdint>
#include <condition_variable>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// VC12 does not have constexpr.
#if defined(_WIN32) || defined(_WIN64)
    #define constexpr
#endif

// pointer macro
#define SPtr std::shared_ptr
#define WPtr std::weak_ptr
#define UPtr std::unique_ptr