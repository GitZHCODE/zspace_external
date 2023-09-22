import ctypes
from .dll_module import DLLConfig

DLLFile = DLLConfig.zExternalDLLFile

class zExtColor(ctypes.Structure):
	_fields_ = [
		("r", ctypes.c_float),
		("g", ctypes.c_float),
		("b", ctypes.c_float),
		("a", ctypes.c_float)
		]

class zExtColorArray(ctypes.Structure):
    _fields_ = [
        ("zColorArray", ctypes.c_void_p),
		("arrayCount", ctypes.c_int)
		]

       
#---CREATE METHODS
ext_color_createRGB = DLLfile.ext_color_createRGB
ext_color_createRGB.restype = None
ext_color_createRGB.argtypes = [ctypes.c_float,ctypes.c_float,ctypes.c_float,ctypes.c_float,ctypes.POINTER(zExtColor)]

#---GET METHODS
ext_color_getItemsFromArray = DLLfile.ext_color_getItemsFromArray
ext_color_getItemsFromArray = None
ext_color_getItemsFromArray = [ctypes.POINTER(zExtColorArray),ctypes.POINTER(zExtColor)]

#---SET METHODS
ext_color_setItemsFromArray = DLLfile.ext_color_setItemsFromArray
ext_color_setItemsFromArray = None
ext_color_setItemsFromArray = [ctypes.POINTER(zExtColorArray),ctypes.POINTER(zExtColor),ctypes.c_int]