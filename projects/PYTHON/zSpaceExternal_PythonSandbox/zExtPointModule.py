import ctypes

from DLLConfigModule import DLLConfig

DLLFile = DLLConfig.zExternalDLLFile

class zExtPoint(ctypes.Structure):
	_fields_ = [
		("x", ctypes.c_float),
		("y", ctypes.c_float),
		("z", ctypes.c_float),
		]

class zExtPointArray(ctypes.Structure):
	_fields_ = [
		("pointer", ctypes.c_void_p),
		("arrayCount", ctypes.c_int),
		]

#---GET METHODS

ext_point_getItemsFromArray = DLLFile.ext_point_getItemsFromArray
ext_point_getItemsFromArray.restype = None
ext_point_getItemsFromArray.argtypes = [ctypes.POINTER(zExtPointArray), ctypes.POINTER(zExtPoint)]

#---SET METHODS

ext_point_getItemsFromArray = DLLFile.ext_point_getItemsFromArray
ext_point_getItemsFromArray.restype = ctypes.c_int
ext_point_getItemsFromArray.argtypes = [ctypes.POINTER(zExtPointArray),ctypes.POINTER(zExtPoint), ctypes.c_int]



