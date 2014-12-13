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
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    #define constexpr
    #define __func__ __FUNCTION__
#endif

// pointer macro
#define Sptr std::shared_ptr
#define Wptr std::weak_ptr
#define Uptr std::unique_ptr
