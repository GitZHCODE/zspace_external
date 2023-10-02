
from DLLConfigModule import DLLConfig
import ctypes

# Load the DLL file that contains the C++ external methods
DLLFile = DLLConfig.zExternalDLLFile

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


ext_int_setItemsFromArray = DLLFile.ext_int_setItemsFromArray
ext_int_setItemsFromArray.restype = None
ext_int_setItemsFromArray.argtypes = [
    zExtIntArray,
    ctypes.POINTER(ctypes.c_int), 
    ctypes.c_int
]

# zExtIntArray2D
ext_int_getItemsFromArray2D = DLLFile.ext_int_getItemsFromArray2D
ext_int_getItemsFromArray2D.restype = None
ext_int_getItemsFromArray2D.argtypes = [
    zExtIntArray2D,
    ctypes.POINTER(zExtIntArray)
]


ext_int_setItemsFromArray2D = DLLFile.ext_int_setItemsFromArray2D
ext_int_setItemsFromArray2D.restype = None
ext_int_setItemsFromArray2D.argtypes = [
    zExtIntArray2D,
    ctypes.POINTER(zExtIntArray),
     ctypes.c_int
]

# zExtFloatArray
ext_float_getItemsFromArray = DLLFile.ext_float_getItemsFromArray
ext_float_getItemsFromArray.restype = None
ext_float_getItemsFromArray.argtypes = [
    zExtFloatArray,
    ctypes.POINTER(ctypes.c_float)
]


ext_float_setItemsFromArray = DLLFile.ext_float_setItemsFromArray
ext_float_setItemsFromArray.restype = None
ext_float_setItemsFromArray.argtypes = [
    zExtFloatArray,
    ctypes.POINTER(ctypes.c_float),
    ctypes.c_int
]

# zExtFloatArray2D
ext_float_getItemsFromArray2D = DLLFile.ext_float_getItemsFromArray2D
ext_float_getItemsFromArray2D.restype = None
ext_float_getItemsFromArray2D.argtypes = [
    zExtFloatArray2D,
    ctypes.POINTER(zExtFloatArray)
]


ext_float_setItemsFromArray2D = DLLFile.ext_float_setItemsFromArray2D
ext_float_setItemsFromArray2D.restype = None
ext_float_setItemsFromArray2D.argtypes = [
    zExtFloatArray2D,
    ctypes.POINTER(zExtFloatArray),
    ctypes.c_int
]

# zExtDoubleArray
ext_double_getItemsFromArray = DLLFile.ext_double_getItemsFromArray
ext_double_getItemsFromArray.restype = None
ext_double_getItemsFromArray.argtypes = [
    zExtDoubleArray,
    ctypes.POINTER(ctypes.c_double)
]

ext_double_setItemsFromArray = DLLFile.ext_double_setItemsFromArray
ext_double_setItemsFromArray.restype = None
ext_double_setItemsFromArray.argtypes = [
    zExtDoubleArray,
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int
]

# zExtDoubleArray2D
ext_double_getItemsFromArray2D = DLLFile.ext_double_getItemsFromArray2D
ext_double_getItemsFromArray2D.restype = None
ext_double_getItemsFromArray2D.argtypes = [
    zExtDoubleArray2D,
    ctypes.POINTER(zExtDoubleArray)
]


ext_double_setItemsFromArray2D = DLLFile.ext_double_setItemsFromArray2D
ext_double_setItemsFromArray2D.restype = None
ext_double_setItemsFromArray2D.argtypes = [
    zExtDoubleArray2D,
    ctypes.POINTER(zExtDoubleArray),
    ctypes.c_int
]


# zExtString
ext_string_getCharArrayFromExtString = DLLFile.ext_string_getCharArrayFromExtString
ext_string_getCharArrayFromExtString.restype = ctypes.c_int
ext_string_getCharArrayFromExtString.argtypes = [
    zExtString,
    ctypes.c_char_p
]

ext_string_setExtStringFromCharArray = DLLFile.ext_string_setExtStringFromCharArray
ext_string_setExtStringFromCharArray.restype = ctypes.c_int
ext_string_setExtStringFromCharArray.argtypes = [
    zExtString,
    ctypes.c_char_p,
    ctypes.c_int
]


# zExtStringArray
ext_string_getItemsFromArray = DLLFile.ext_string_getItemsFromArray
ext_string_getItemsFromArray.restype = None
ext_string_getItemsFromArray.argtypes = [
    zExtStringArray,
    ctypes.POINTER(zExtString)
]
ext_string_setItemsFromArray = DLLFile.ext_string_setItemsFromArray
ext_string_setItemsFromArray.restype = None

ext_string_setItemsFromArray.argtypes = [
    zExtStringArray,
    ctypes.POINTER(zExtString),
    ctypes.c_int
]


ext_string_getCharArrayFromExtString = DLLFile.ext_string_getCharArrayFromExtString
ext_string_getCharArrayFromExtString.restype = ctypes.c_int
ext_string_getCharArrayFromExtString.argtypes = [
    zExtStringArray,
    ctypes.c_char_p
]


# zExtStringArray2D
ext_string_getItemsFromArray2D = DLLFile.ext_string_getItemsFromArray2D
ext_string_getItemsFromArray2D.restype = None
ext_string_getItemsFromArray2D.argtypes = [
    zExtStringArray2D,
    ctypes.POINTER(zExtStringArray)
]


ext_string_setItemsFromArray2D = DLLFile.ext_string_setItemsFromArray2D
ext_string_setItemsFromArray2D.restype = None
ext_string_setItemsFromArray2D.argtypes = [
    zExtStringArray2D,
    ctypes.POINTER(zExtStringArray),
    ctypes.c_int

]


# zExtBoolArray
ext_bool_getItemsFromArray = DLLFile.ext_bool_getItemsFromArray
ext_bool_getItemsFromArray.restype = None
ext_bool_getItemsFromArray.argtypes = [
    zExtBoolArray,
    ctypes.POINTER(ctypes.c_bool)
]


ext_bool_setItemsFromArray = DLLFile.ext_bool_setItemsFromArray
ext_bool_setItemsFromArray.restype = None
ext_bool_setItemsFromArray.argtypes = [
    zExtBoolArray,
    ctypes.POINTER(ctypes.c_bool),
     ctypes.c_int
]

# zExtBoolArray2D
ext_bool_getItemsFromArray2D = DLLFile.ext_bool_getItemsFromArray2D
ext_bool_getItemsFromArray2D.restype = None
ext_bool_getItemsFromArray2D.argtypes = [
    zExtBoolArray2D,
    ctypes.POINTER(zExtBoolArray)
]


ext_bool_setItemsFromArray2D = DLLFile.ext_bool_setItemsFromArray2D
ext_bool_setItemsFromArray2D.restype = None
ext_bool_setItemsFromArray2D.argtypes = [
    zExtBoolArray2D,
    ctypes.POINTER(zExtBoolArray),
    ctypes.c_int

]

