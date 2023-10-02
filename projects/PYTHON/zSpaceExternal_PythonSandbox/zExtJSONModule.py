import ctypes
from DLLConfigModule import DLLConfig
from zExtUtilsCoreModule import zExtString, zExtStringArray, zExtStringArray2D, zExtIntArray, zExtIntArray2D, zExtIntArray2D, zExtDoubleArray, zExtDoubleArray2D, zExtBoolArray, zExtBoolArray2D
from zExtMeshModule import zExtMesh



DLLFile = DLLConfig.zExternalDLLFile

class zExtJSON(ctypes.Structure):
	_fields_ = [
		("pointer", ctypes.c_void_p),
		("numOfAttributes", ctypes.c_int),
		("attributesNames", ctypes.POINTER(zExtStringArray)),
		("attributesTypes", ctypes.POINTER(zExtStringArray))
		]

#---READ METHODS
ext_json_readJSONAttributeJSON = DLLFile.ext_json_readJSONAttributeJSON
ext_json_readJSONAttributeJSON.restype = ctypes.c_int
ext_json_readJSONAttributeJSON.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtJSON) ]

ext_json_readJSONAttributeInt = DLLFile.ext_json_readJSONAttributeInt
ext_json_readJSONAttributeInt.restype = ctypes.c_int
ext_json_readJSONAttributeInt.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_int ]

ext_json_readJSONAttributeIntArray = DLLFile.ext_json_readJSONAttributeIntArray
ext_json_readJSONAttributeIntArray.restype = ctypes.c_int
ext_json_readJSONAttributeIntArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtIntArray) ]

ext_json_readJSONAttributeIntArray2D = DLLFile.ext_json_readJSONAttributeIntArray2D
ext_json_readJSONAttributeIntArray2D.restype = ctypes.c_int
ext_json_readJSONAttributeIntArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtIntArray2D) ]

ext_json_readJSONAttributeFloat = DLLFile.ext_json_readJSONAttributeFloat
ext_json_readJSONAttributeFloat.restype = ctypes.c_int
ext_json_readJSONAttributeFloat.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_float ]

ext_json_readJSONAttributeFloatArray = DLLFile.ext_json_readJSONAttributeFloatArray
ext_json_readJSONAttributeFloatArray.restype = ctypes.c_int
ext_json_readJSONAttributeFloatArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtFloatArray) ]

ext_json_readJSONAttributeFloatArray2D = DLLFile.ext_json_readJSONAttributeFloatArray2D
ext_json_readJSONAttributeFloatArray2D.restype = ctypes.c_int
ext_json_readJSONAttributeFloatArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtFloatArray2D) ]

ext_json_readJSONAttributeDouble = DLLFile.ext_json_readJSONAttributeDouble
ext_json_readJSONAttributeDouble.restype = ctypes.c_int
ext_json_readJSONAttributeDouble.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_double ]

ext_json_readJSONAttributeDoubleArray = DLLFile.ext_json_readJSONAttributeDoubleArray
ext_json_readJSONAttributeDoubleArray.restype = ctypes.c_int
ext_json_readJSONAttributeDoubleArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtDoubleArray) ]

ext_json_readJSONAttributeDoubleArray2D = DLLFile.ext_json_readJSONAttributeDoubleArray2D
ext_json_readJSONAttributeDoubleArray2D.restype = ctypes.c_int
ext_json_readJSONAttributeDoubleArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtDoubleArray2D) ]

ext_json_readJSONAttributeString = DLLFile.ext_json_readJSONAttributeString
ext_json_readJSONAttributeString.restype = ctypes.c_int
ext_json_readJSONAttributeString.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtString)]

ext_json_readJSONAttributeStringArray = DLLFile.ext_json_readJSONAttributeStringArray
ext_json_readJSONAttributeStringArray.restype = ctypes.c_int
ext_json_readJSONAttributeStringArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtStringArray) ]

ext_json_readJSONAttributeStringArray2D = DLLFile.ext_json_readJSONAttributeStringArray2D
ext_json_readJSONAttributeStringArray2D.restype = ctypes.c_int
ext_json_readJSONAttributeStringArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtStringArray2D) ]

ext_json_readJSONAttributeBool = DLLFile.ext_json_readJSONAttributeBool
ext_json_readJSONAttributeBool.restype = ctypes.c_int
ext_json_readJSONAttributeBool.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_bool]

ext_json_readJSONAttributeBoolArray = DLLFile.ext_json_readJSONAttributeBoolArray
ext_json_readJSONAttributeBoolArray.restype = ctypes.c_int
ext_json_readJSONAttributeBoolArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtBoolArray) ]

ext_json_readJSONAttributeBoolArray2D = DLLFile.ext_json_readJSONAttributeBoolArray2D
ext_json_readJSONAttributeBoolArray2D.restype = ctypes.c_int
ext_json_readJSONAttributeBoolArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtBoolArray2D) ]


#---WRITE METHODS

ext_json_writeJSONAttributeInt = DLLFile.ext_json_writeJSONAttributeInt
ext_json_writeJSONAttributeInt.restype = ctypes.c_int
ext_json_writeJSONAttributeInt.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_int, ctypes.c_bool ]
ext_json_writeJSONAttributeInt.argtypes[-1].value = True 

ext_json_writeJSONAttributeIntArray = DLLFile.ext_json_writeJSONAttributeIntArray
ext_json_writeJSONAttributeIntArray.restype = ctypes.c_int
ext_json_writeJSONAttributeIntArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtIntArray), ctypes.c_bool ]
ext_json_writeJSONAttributeIntArray.argtypes[-1].value = True 

ext_json_writeJSONAttributeIntArray2D = DLLFile.ext_json_writeJSONAttributeIntArray2D
ext_json_writeJSONAttributeIntArray2D.restype = ctypes.c_int
ext_json_writeJSONAttributeIntArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtIntArray2D), ctypes.c_bool ]
ext_json_writeJSONAttributeIntArray2D.argtypes[-1].value = True 

ext_json_writeJSONAttributeFloat = DLLFile.ext_json_writeJSONAttributeFloat
ext_json_writeJSONAttributeFloat.restype = ctypes.c_int
ext_json_writeJSONAttributeFloat.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_float, ctypes.c_bool ]
ext_json_writeJSONAttributeFloat.argtypes[-1].value = True 

ext_json_writeJSONAttributeFloatArray = DLLFile.ext_json_writeJSONAttributeFloatArray
ext_json_writeJSONAttributeFloatArray.restype = ctypes.c_int
ext_json_writeJSONAttributeFloatArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtFloatArray), ctypes.c_bool ]
ext_json_writeJSONAttributeFloatArray.argtypes[-1].value = True 

ext_json_writeJSONAttributeFloatArray2D = DLLFile.ext_json_writeJSONAttributeFloatArray2D
ext_json_writeJSONAttributeFloatArray2D.restype = ctypes.c_int
ext_json_writeJSONAttributeFloatArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtFloatArray2D), ctypes.c_bool ]
ext_json_writeJSONAttributeFloatArray2D.argtypes[-1].value = True 

ext_json_writeJSONAttributeDouble = DLLFile.ext_json_writeJSONAttributeDouble
ext_json_writeJSONAttributeDouble.restype = ctypes.c_int
ext_json_writeJSONAttributeDouble.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_double, ctypes.c_bool ]
ext_json_writeJSONAttributeDouble.argtypes[-1].value = True 

ext_json_writeJSONAttributeDoubleArray = DLLFile.ext_json_writeJSONAttributeDoubleArray
ext_json_writeJSONAttributeDoubleArray.restype = ctypes.c_int
ext_json_writeJSONAttributeDoubleArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtDoubleArray), ctypes.c_bool ]
ext_json_writeJSONAttributeDoubleArray.argtypes[-1].value = True 

ext_json_writeJSONAttributeDoubleArray2D = DLLFile.ext_json_writeJSONAttributeDoubleArray2D
ext_json_writeJSONAttributeDoubleArray2D.restype = ctypes.c_int
ext_json_writeJSONAttributeDoubleArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtDoubleArray2D), ctypes.c_bool ]
ext_json_writeJSONAttributeDoubleArray2D.argtypes[-1].value = True 

ext_json_writeJSONAttributeString = DLLFile.ext_json_writeJSONAttributeString
ext_json_writeJSONAttributeString.restype = ctypes.c_int
ext_json_writeJSONAttributeString.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtString), ctypes.c_bool]
ext_json_writeJSONAttributeString.argtypes[-1].value = True 

ext_json_writeJSONAttributeStringArray = DLLFile.ext_json_writeJSONAttributeStringArray
ext_json_writeJSONAttributeStringArray.restype = ctypes.c_int
ext_json_writeJSONAttributeStringArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtStringArray), ctypes.c_bool ]
ext_json_writeJSONAttributeStringArray.argtypes[-1].value = True 

ext_json_writeJSONAttributeStringArray2D = DLLFile.ext_json_writeJSONAttributeStringArray2D
ext_json_writeJSONAttributeStringArray2D.restype = ctypes.c_int
ext_json_writeJSONAttributeStringArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtStringArray2D), ctypes.c_bool ]
ext_json_writeJSONAttributeStringArray2D.argtypes[-1].value = True 

ext_json_writeJSONAttributeBool = DLLFile.ext_json_writeJSONAttributeBool
ext_json_writeJSONAttributeBool.restype = ctypes.c_int
ext_json_writeJSONAttributeBool.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.c_bool, ctypes.c_bool]
ext_json_writeJSONAttributeBool.argtypes[-1].value = True 

ext_json_writeJSONAttributeBoolArray = DLLFile.ext_json_writeJSONAttributeBoolArray
ext_json_writeJSONAttributeBoolArray.restype = ctypes.c_int
ext_json_writeJSONAttributeBoolArray.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtBoolArray), ctypes.c_bool ]
ext_json_writeJSONAttributeBoolArray.argtypes[-1].value = True 

ext_json_writeJSONAttributeBoolArray2D = DLLFile.ext_json_writeJSONAttributeBoolArray2D
ext_json_writeJSONAttributeBoolArray2D.restype = ctypes.c_int
ext_json_writeJSONAttributeBoolArray2D.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtBoolArray2D), ctypes.c_bool ]
ext_json_writeJSONAttributeBoolArray2D.argtypes[-1].value = True 

ext_json_writeJSONAttributeJSON = DLLFile.ext_json_writeJSONAttributeJSON
ext_json_writeJSONAttributeJSON.restype = ctypes.c_int
ext_json_writeJSONAttributeJSON.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p, ctypes.POINTER(zExtJSON), ctypes.c_bool ]
ext_json_writeJSONAttributeJSON.argtypes[-1].value = True 

#---CREATE METHODS
ext_json_createJson = DLLFile.ext_json_createJson
ext_json_createJson.restype = None
ext_json_createJson.argtypes = [ctypes.POINTER(zExtJSON) ]

ext_json_createJsonDeepCopy = DLLFile.ext_json_createJsonDeepCopy
ext_json_createJsonDeepCopy.restype = None
ext_json_createJsonDeepCopy.argtypes = [ctypes.POINTER(zExtJSON), ctypes.POINTER(zExtJSON)]

#---READ 
ext_json_readJsonFile = DLLFile.ext_json_readJsonFile
ext_json_readJsonFile.restype = ctypes.c_int
ext_json_readJsonFile.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p]

#---GET METHODS
ext_json_getMeshFromJson = DLLFile.ext_json_getMeshFromJson
ext_json_getMeshFromJson.restype = ctypes.c_int
ext_json_getMeshFromJson.argtypes = [ctypes.POINTER(zExtJSON), ctypes.POINTER(zExtMesh)]

ext_json_getMeshFromJsonPath = DLLFile.ext_json_getMeshFromJsonPath
ext_json_getMeshFromJsonPath.restype = ctypes.c_int
ext_json_getMeshFromJsonPath.argtypes = [ctypes.c_char_p, ctypes.POINTER(zExtMesh) ]

#---SET METHODS
ext_json_setMeshToJson = DLLFile.ext_json_setMeshToJson
ext_json_setMeshToJson.restype = ctypes.c_int
ext_json_setMeshToJson.argtypes = [ctypes.POINTER(zExtJSON), ctypes.POINTER(zExtMesh)]

#---EXPORT
ext_json_exportFile = DLLFile.ext_json_exportFile
ext_json_exportFile.restype = ctypes.c_int
ext_json_exportFile.argtypes = [ctypes.POINTER(zExtJSON), ctypes.c_char_p]
