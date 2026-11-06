#pragma once

#include <iostream>

#define SPP_LOG_DEBUG(msg) std::cout << "[" << __func__ << "] DEBUG: " << msg << "\n"   
#define SPP_LOG_ERROR(msg) std::cout << "[" << __func__ << "] ERROR: " << msg << "\n"
#define SPP_THROW_ERROR(msg) throw std::runtime_error(std::string("[" + std::string(__func__) + "] ERROR: " + msg))