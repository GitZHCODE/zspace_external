/**
 * \file zSpace_External_C_API_Common.h
 * \brief Common utilities for zSpace External C API
 * \date 2023
 *
 * This file provides common utilities and support functions for the zSpace External C API.
 */

#ifndef ZSPACE_EXTERNAL_C_API_COMMON_H
#define ZSPACE_EXTERNAL_C_API_COMMON_H

#include "../../../cpp/headers/base/zSpace_External_C_API.h"

#include <string>
#include <stdexcept>
#include <memory>

namespace zSpace {

// Thread-local error message storage
extern thread_local std::string g_lastErrorMessage;

// Set the last error message and return a status code (0 for error)
inline int SetError(const std::string& message) {
    g_lastErrorMessage = message;
    return 0;
}

// Template for casting handles to their actual types with error checking
template<typename T>
T* GetPointerFromHandle(void* handle) {
    if (!handle) {
        SetError("Invalid handle: null pointer");
        return nullptr;
    }
    return static_cast<T*>(handle);
}

// RAII wrapper for handle-based objects in the C API implementation
template<typename T>
class HandleScope {
private:
    T* ptr;
    bool owned;

public:
    HandleScope(T* p, bool take_ownership = true) : ptr(p), owned(take_ownership) {}
    
    ~HandleScope() {
        if (owned && ptr) {
            delete ptr;
        }
    }
    
    T* get() const { return ptr; }
    
    T* release() {
        owned = false;
        return ptr;
    }
};

} // namespace zSpace

// Verify that a handle is valid and set error if not
#define VERIFY_HANDLE(type, handle, error_msg) \
    auto* ptr = zSpace::GetPointerFromHandle<type>(handle); \
    if (!ptr) { \
        zSpace::SetError(error_msg); \
        return 0; \
    }

// Try-catch wrapper for C API functions
#define TRY_CATCH_RETURN(code, return_value) \
    try { \
        code \
    } catch (const std::exception& e) { \
        zSpace::SetError(e.what()); \
        return return_value; \
    } catch (...) { \
        zSpace::SetError("Unknown error"); \
        return return_value; \
    }

#endif // ZSPACE_EXTERNAL_C_API_COMMON_H 