import DLLConfig
import ctypes

# Load the DLL file that contains the C++ external methods
DLLFile = DLLConfig.DLLConfig.zExternalDLLFile

class zExtIntArray(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = (ctypes.c_int * self.arrayCount)()
        ext_int_getItemsFromArray(ctypes.byref(self), items)
        return list(items)

    def setItems(self, input):
        input = (ctypes.c_int * len(input))(*input)
        ext_int_setItemsFromArray(ctypes.byref(self), input, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtIntArray2D(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        temp = (zExtIntArray * self.arrayCount)()
        ext_int_getItemsFromArray2D(ctypes.byref(self), temp)
        for i in range(self.arrayCount):
            items.append(temp[i].getItems())
        return items

    def setItems(self, input):
        temp = (zExtIntArray * len(input))()
        for i in range(len(input)):
            temp[i].setItems(input[i])
        ext_int_setItemsFromArray2D(ctypes.byref(self), temp, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtFloatArray(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = (ctypes.c_float * self.arrayCount)()
        ext_float_getItemsFromArray(ctypes.byref(self), items)
        return list(items)

    def setItems(self, input):
        input = (ctypes.c_float * len(input))(*input)
        ext_float_setItemsFromArray(ctypes.byref(self), input, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtFloatArray2D(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        temp = (zExtFloatArray * self.arrayCount)()
        ext_float_getItemsFromArray2D(ctypes.byref(self), temp)
        for i in range(self.arrayCount):
            items.append(temp[i].getItems())
        return items

    def setItems(self, input):
        temp = (zExtFloatArray * len(input))()
        for i in range(len(input)):
            temp[i].setItems(input[i])
        ext_float_setItemsFromArray2D(ctypes.byref(self), temp, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtDoubleArray(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = (ctypes.c_double * self.arrayCount)()
        ext_double_getItemsFromArray(ctypes.byref(self), items)
        return list(items)

    def setItems(self, input):
        input = (ctypes.c_double * len(input))(*input)
        ext_double_setItemsFromArray(ctypes.byref(self), input, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtDoubleArray2D(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        temp = (zExtDoubleArray * self.arrayCount)()
        ext_double_getItemsFromArray2D(ctypes.byref(self), temp)
        for i in range(self.arrayCount):
            items.append(temp[i].getItems())
        return items

    def setItems(self, input):
        temp = (zExtDoubleArray * len(input))()
        for i in range(len(input)):
            temp[i].setItems(input[i])
        ext_double_setItemsFromArray2D(ctypes.byref(self), temp, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtString(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getString(self):
        ch = (ctypes.c_char * self.arrayCount)()
        ext_string_getCharArrayFromExtString(ctypes.byref(self), ch)
        return ctypes.string_at(ch)

    def getArrayCount(self):
        return self.arrayCount


class zExtStringArray(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        for i in range(self.arrayCount):
            length = ext_string_getItemFromArrayCharLength(ctypes.byref(self), i)
            ch = (ctypes.c_char * length)()
            ext_string_getItemFromArrayChar(ctypes.byref(self), i, ch)
            items.append(ctypes.string_at(ch))
        return items

    def setItems(self, input):
        ext_string_setItemsFromArray(ctypes.byref(self), input, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtStringArray2D(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        temp = (zExtStringArray * self.arrayCount)()
        ext_string_getItemsFromArray2D(ctypes.byref(self), temp)
        for i in range(self.arrayCount):
            items.append(temp[i].getItems())
        return items

    def setItems(self, input):
        temp = (zExtStringArray * len(input))()
        for i in range(len(input)):
            temp[i].setItems(input[i])
        ext_string_setItemsFromArray2D(ctypes.byref(self), temp, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtBoolArray(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = (ctypes.c_bool * self.arrayCount)()
        ext_bool_getItemsFromArray(ctypes.byref(self), items)
        return list(items)

    def setItems(self, input):
        input = (ctypes.c_bool * len(input))(*input)
        ext_bool_setItemsFromArray(ctypes.byref(self), input, len(input))

    def getArrayCount(self):
        return self.arrayCount


class zExtBoolArray2D(ctypes.Structure):
    _fields_ = [
        ("pointer", ctypes.c_void_p),
        ("arrayCount", ctypes.c_int)
    ]

    def getItems(self):
        items = []
        temp = (zExtBoolArray * self.arrayCount)()
        ext_bool_getItemsFromArray2D(ctypes.byref(self), temp)
        for i in range(self.arrayCount):
            items.append(temp[i].getItems())
        return items

    def setItems(self, input):
        temp = (zExtBoolArray * len(input))()
        for i in range(len(input)):
            temp[i].setItems(input[i])
        ext_bool_setItemsFromArray2D(ctypes.byref(self), temp, len(input))

    def getArrayCount(self):
        return self.arrayCount


# zExtIntArray
ext_int_getItemsFromArray = DLLFile.ext_int_getItemsFromArray
ext_int_getItemsFromArray.restype = None
ext_int_getItemsFromArray.argtypes = [
    zExtIntArray,
    ctypes.POINTER(ctypes.c_int)
]

# zExtIntArray2D
ext_int_getItemsFromArray2D = DLLFile.ext_int_getItemsFromArray2D
ext_int_getItemsFromArray2D.restype = None
ext_int_getItemsFromArray2D.argtypes = [
    zExtIntArray2D,
    ctypes.POINTER(zExtIntArray)
]

# zExtFloatArray
ext_float_getItemsFromArray = DLLFile.ext_float_getItemsFromArray
ext_float_getItemsFromArray.restype = None
ext_float_getItemsFromArray.argtypes = [
    zExtFloatArray,
    ctypes.POINTER(ctypes.c_float)
]

# zExtFloatArray2D
ext_float_getItemsFromArray2D = DLLFile.ext_float_getItemsFromArray2D
ext_float_getItemsFromArray2D.restype = None
ext_float_getItemsFromArray2D.argtypes = [
    zExtFloatArray2D,
    ctypes.POINTER(zExtFloatArray)
]

# zExtDoubleArray
ext_double_getItemsFromArray = DLLFile.ext_double_getItemsFromArray
ext_double_getItemsFromArray.restype = None
ext_double_getItemsFromArray.argtypes = [
    zExtDoubleArray,
    ctypes.POINTER(ctypes.c_double)
]

# zExtDoubleArray2D
ext_double_getItemsFromArray2D = DLLFile.ext_double_getItemsFromArray2D
ext_double_getItemsFromArray2D.restype = None
ext_double_getItemsFromArray2D.argtypes = [
    zExtDoubleArray2D,
    ctypes.POINTER(zExtDoubleArray)
]

# zExtStringArray
ext_string_getItemsFromArray = DLLFile.ext_string_getItemsFromArray
ext_string_getItemsFromArray.restype = None
ext_string_getItemsFromArray.argtypes = [
    zExtStringArray,
    ctypes.POINTER(zExtString)
]

ext_string_getItemFromArray = DLLFile.ext_string_getItemFromArray
ext_string_getItemFromArray.restype = ctypes.c_char_p
ext_string_getItemFromArray.argtypes = [
    zExtStringArray,
    ctypes.c_int
]

ext_string_getItemFromArrayCharLength = DLLFile.ext_string_getItemFromArrayCharLength
ext_string_getItemFromArrayCharLength.restype = ctypes.c_int
ext_string_getItemFromArrayCharLength.argtypes = [
    zExtStringArray,
    ctypes.c_int
]

ext_string_getItemFromArrayChar = DLLFile.ext_string_getItemFromArrayChar
ext_string_getItemFromArrayChar.restype = None
ext_string_getItemFromArrayChar.argtypes = [
    zExtStringArray,
    ctypes.c_int,
    ctypes.c_char_p
]

ext_string_getCharArrayFromExtString = DLLFile.ext_string_getCharArrayFromExtString
ext_string_getCharArrayFromExtString.restype = ctypes.c_int
ext_string_getCharArrayFromExtString.argtypes = [
    zExtString,
    ctypes.c_char_p
]

# zExtStringArray2D
ext_string_getItemsFromArray2D = DLLFile.ext_string_getItemsFromArray2D
ext_string_getItemsFromArray2D.restype = None
ext_string_getItemsFromArray2D.argtypes = [
    zExtStringArray2D,
    ctypes.POINTER(zExtStringArray)
]

# zExtBoolArray
ext_bool_getItemsFromArray = DLLFile.ext_bool_getItemsFromArray
ext_bool_getItemsFromArray.restype = None
ext_bool_getItemsFromArray.argtypes = [
    zExtBoolArray,
    ctypes.POINTER(ctypes.c_bool)
]

# zExtBoolArray2D
ext_bool_getItemsFromArray2D = DLLFile.ext_bool_getItemsFromArray2D
ext_bool_getItemsFromArray2D.restype = None
ext_bool_getItemsFromArray2D.argtypes = [
    zExtBoolArray2D,
    ctypes.POINTER(zExtBoolArray)
]


