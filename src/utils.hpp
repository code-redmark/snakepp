#pragma once

#include <iostream>

#define LOG_DEBUG(msg) std::cout << "[" << __func__ << "] DEBUG" << msg << "\n"   
#define LOG_ERROR(msg) std::cout << "[" << __func__ << "] ERROR" << msg << "\n"
