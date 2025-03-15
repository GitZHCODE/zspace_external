/**
 * \file zSpace_External_C_API_Common.cpp
 * \brief Implementation of common C API functions
 * \date 2023
 */

#include "../../../cpp/headers/base/zSpace_External_C_API.h"
#include "../../../cpp/headers/base/zSpace_External_C_API_Common.h"

// Thread-local error message storage
namespace zSpace {
    thread_local std::string g_lastErrorMessage;
}

extern "C" {

ZSPACE_EXTERNAL_API const char* zext_get_last_error() {
    return zSpace::g_lastErrorMessage.c_str();
}

} // extern "C" 