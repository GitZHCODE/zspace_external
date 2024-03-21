from enum import Enum
import ctypes

# Define the enumeration for zStatusCode
class zStatusCode(Enum):
    zFail = 0
    zSuccess = 1
    zMemAllocSuccess = 2
    zMemNotAllocError = 3
    zThrowError = 4
    zInvalidParameter = 5
    zPathNotFound = 6
    zRunning = 7
    zSkip = 8

# Define the zStatus structure
class zStatus(ctypes.Structure):
    _fields_ = [
        ("statusCode", ctypes.c_int),
        ("errorMessage", ctypes.c_char_p)
    ]

    def __init__(self, code, error=None):
        self.statusCode = code.value
        if error:
            self.errorMessage = ctypes.c_char_p(error.encode())
        else:
            self.errorMessage = None

    def getErrorCheck(self):
        return ext_status_getErrorCheck(self)

    def clearError(self):
        if self.errorMessage:
            self.errorMessage = None

# Define function prototypes
ext_status_operator_equal = DLLFile.ext_status_operator_equal
ext_status_operator_equal.restype = ctypes.c_bool
ext_status_operator_equal.argtypes = [
    zStatus,
    zStatus
]

ext_status_operator_equalCode = DLLFile.ext_status_operator_equalCode
ext_status_operator_equalCode.restype = ctypes.c_bool
ext_status_operator_equalCode.argtypes = [
    zStatus,
    ctypes.c_int
]

ext_status_getErrorCheck = DLLFile.ext_status_getErrorCheck
ext_status_getErrorCheck.restype = ctypes.c_bool
ext_status_getErrorCheck.argtypes = [
    zStatus
]

# Usage:
# status = zStatus(zStatusCode.zSuccess)
# print(ext_status_getErrorCheck(status))
# status = zStatus(zStatusCode.zFail, "Error message")
# print(ext_status_getErrorCheck(status))
