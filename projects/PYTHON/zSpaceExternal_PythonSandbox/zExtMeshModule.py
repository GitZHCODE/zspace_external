import ctypes

import zExtTransformModule
import DLLConfigModule
import zExtTransformModule
import zExtPointModule
import zExtUtilsCoreModule
import zExtColorModule

#from zExtTransformModule import zExtTransform
from DLLConfigModule import DLLConfig
from zExtPointModule import zExtPoint, zExtPointArray
from zExtColorModule import zExtColor, zExtColorArray
from zExtUtilsCoreModule import zExtIntArray, zExtIntArray2D
from zExtUtilsCoreModule import zExtFloatArray, zExtFloatArray2D
from zExtUtilsCoreModule import zExtBoolArray, zExtBoolArray2D


DLLFile = DLLConfig.zExternalDLLFile

class zExtMesh(ctypes.Structure):
	_fields_ = [
		("extPointer", ctypes.c_void_p),
		("vCount", ctypes.c_int),
		("fCount", ctypes.c_int),		
		]

class zExtMeshArray(ctypes.Structure):
	_fields_ = [
		("pointer", ctypes.c_void_p),
		("arrayCount", ctypes.c_int),
		]

class zExtMeshPointerArray(ctypes.Structure):[
		("pointer", ctypes.c_void_p),
		("arrayCount", ctypes.c_int),
		]


#---CREATE METHODS
ext_meshUtil_createMeshOBJFromRawArray = DLLFile.ext_meshUtil_createMeshOBJFromRawArray
ext_meshUtil_createMeshOBJFromRawArray.restype = None
ext_meshUtil_createMeshOBJFromRawArray.argtypes = [ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int, ctypes.POINTER(zExtMesh)]

ext_meshUtil_createMeshOBJFromArray = DLLFile.ext_meshUtil_createMeshOBJFromArray
ext_meshUtil_createMeshOBJFromArray.restype = ctypes.c_int
ext_meshUtil_createMeshOBJFromArray.argtypes = [ctypes.POINTER(zExtPointArray), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtMesh)]

ext_meshUtil_setMeshVertexColors = DLLFile.ext_meshUtil_setMeshVertexColors
ext_meshUtil_setMeshVertexColors.restype = ctypes.c_int
ext_meshUtil_setMeshVertexColors.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtColorArray)]

ext_meshUtil_createMeshOBJFromFile = DLLFile.ext_meshUtil_createMeshOBJFromFile
ext_meshUtil_createMeshOBJFromFile.restype = None
ext_meshUtil_createMeshOBJFromFile.argtypes = [ctypes.c_char_p, ctypes.POINTER(zExtMesh)]

ext_meshUtil_exportToJson = DLLFile.ext_meshUtil_exportToJson
ext_meshUtil_exportToJson.restype = None
ext_meshUtil_exportToJson.argtypes = [ctypes.POINTER(zExtMesh), ctypes.c_char_p]

#---GET METHODS
ext_meshUtil_getMeshFaceCount = DLLFile.ext_meshUtil_getMeshFaceCount
ext_meshUtil_getMeshFaceCount.restype = ctypes.c_int
ext_meshUtil_getMeshFaceCount.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_int)]

ext_meshUtil_getMeshPositionRaw = DLLFile.ext_meshUtil_getMeshPositionRaw
ext_meshUtil_getMeshPositionRaw.restype = ctypes.c_int
ext_meshUtil_getMeshPositionRaw.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]

ext_meshUtil_getMeshFaceConnect = DLLFile.ext_meshUtil_getMeshFaceConnect
ext_meshUtil_getMeshFaceConnect.restype = ctypes.c_int
ext_meshUtil_getMeshFaceConnect.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_int)]

ext_meshUtil_getMeshCentre = DLLFile.ext_meshUtil_getMeshCentre
ext_meshUtil_getMeshCentre.restype = ctypes.c_int
ext_meshUtil_getMeshCentre.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_float)]

ext_meshUtil_getMeshsFromMeshArray = DLLFile.ext_meshUtil_getMeshsFromMeshArray
ext_meshUtil_getMeshsFromMeshArray.restype = ctypes.c_int
ext_meshUtil_getMeshsFromMeshArray.argtypes = [ctypes.POINTER(zExtMeshArray), ctypes.POINTER(zExtMesh)]

ext_meshUtil_getMeshsFromMeshPointerArray = DLLFile.ext_meshUtil_getMeshsFromMeshPointerArray
ext_meshUtil_getMeshsFromMeshPointerArray.restype = ctypes.c_int
ext_meshUtil_getMeshsFromMeshPointerArray.argtypes = [ctypes.POINTER(zExtMeshPointerArray), ctypes.POINTER(zExtMesh)]

ext_meshUtil_getMeshPosition = DLLFile.ext_meshUtil_getMeshPosition
ext_meshUtil_getMeshPosition.restype = ctypes.c_int
ext_meshUtil_getMeshPosition.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtPointArray)]

ext_meshUtil_getMeshColors = DLLFile.ext_meshUtil_getMeshColors
ext_meshUtil_getMeshColors.restype = ctypes.c_int
ext_meshUtil_getMeshColors.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtColorArray)]

ext_meshUtil_getMeshPolygonDate = DLLFile.ext_meshUtil_getMeshPolygonDate
ext_meshUtil_getMeshPolygonDate.restype = ctypes.c_int
ext_meshUtil_getMeshPolygonDate.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtIntArray)]

#---SET METHODS
ext_meshUtil_catmullclark = DLLFile.ext_meshUtil_catmullclark
ext_meshUtil_catmullclark = ctypes.c_int
ext_meshUtil_catmullclark = [ctypes.POINTER(zExtMesh), ctypes.c_int, ctypes.c_bool]