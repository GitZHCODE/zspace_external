import ctypes
import DLLConfigModule
import zExtTransformModule
import zExtPointModule
import zExtUtilsCoreModule
import zExtColorModule
import zStatusModule

from zExtTransformModule import zExtTransform
from DLLConfigModule import DLLConfig
from zStatusModule import zStatus
from zExtPointModule import zExtPoint, zExtPointArray
from zExtColorModule import zExtColor, zExtColorArray
from zExtUtilsCoreModule import zExtIntArray, zExtIntArray2D
from zExtUtilsCoreModule import zExtFloatArray, zExtFloatArray2D
from zExtUtilsCoreModule import zExtBoolArray, zExtBoolArray2D



DLLFile = DLLConfig.zExternalDLLFile

if not DLLFile:
    print("Failed to load the library")
else:
    print("Library loaded successfully")
    
    
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

ext_meshUtil_createMeshOBJFromArray = DLLFile.ext_mesh_createFromArrays
ext_meshUtil_createMeshOBJFromArray.restype = zStatus
ext_meshUtil_createMeshOBJFromArray.argtypes = [ctypes.POINTER(zExtPointArray), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtMesh)]

ext_meshUtil_setMeshVertexColors = DLLFile.ext_meshUtil_setMeshVertexColors
ext_meshUtil_setMeshVertexColors.restype = zStatus
ext_meshUtil_setMeshVertexColors.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtColorArray)]


ext_mesh_from = DLLFile.ext_mesh_from
ext_mesh_from.restype = zStatus
ext_mesh_from.argtypes = [
    ctypes.c_char_p,
    zExtMesh
]

ext_mesh_to = DLLFile.ext_mesh_to
ext_mesh_to.restype = zStatus
ext_mesh_to.argtypes = [
    zExtMesh,
    ctypes.c_char_p
]

ext_mesh_fromJSON = DLLFile.ext_mesh_fromJSON
ext_mesh_fromJSON.restype = zStatus
ext_mesh_fromJSON.argtypes = [
    zExtJSON,
    zExtMesh
]

ext_mesh_toJSON = DLLFile.ext_mesh_toJSON
ext_mesh_toJSON.restype = zStatus
ext_mesh_toJSON.argtypes = [
    zExtMesh,
    zExtJSON
]

# Define functions for USD interop if ZSPACE_USD_INTEROP is defined

ext_mesh_fromUSD = DLLFile.ext_mesh_fromUSD
ext_mesh_fromUSD.restype = zStatus
ext_mesh_fromUSD.argtypes = [
    zExtUSD,
    zExtMesh
]

ext_mesh_toUSD = DLLFile.ext_mesh_toUSD
ext_mesh_toUSD.restype = zStatus
ext_mesh_toUSD.argtypes = [
    zExtMesh,
    zExtUSD
]

#---GET METHODS
ext_meshUtil_getMeshFaceCount = DLLFile.ext_meshUtil_getMeshFaceCount
ext_meshUtil_getMeshFaceCount.restype = zStatus
ext_meshUtil_getMeshFaceCount.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_int)]

ext_meshUtil_getVertexPositionsRaw = DLLFile.ext_meshUtil_getVertexPositionsRaw
ext_meshUtil_getVertexPositionsRaw.restype = ctypes.c_int
ext_meshUtil_getVertexPositionsRaw.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float)]

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

ext_meshUtil_getVertexPositions = DLLFile.ext_meshUtil_getVertexPositions
ext_meshUtil_getVertexPositions.restype = ctypes.c_int
ext_meshUtil_getVertexPositions.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtPointArray)]

ext_meshUtil_getMeshColors = DLLFile.ext_meshUtil_getMeshColors
ext_meshUtil_getMeshColors.restype = ctypes.c_int
ext_meshUtil_getMeshColors.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtColorArray)]

ext_meshUtil_getMeshPolygonDate = DLLFile.ext_meshUtil_getMeshPolygonDate
ext_meshUtil_getMeshPolygonDate.restype = ctypes.c_int
ext_meshUtil_getMeshPolygonDate.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtIntArray), ctypes.POINTER(zExtIntArray)]

#---SET METHODS
ext_meshUtil_smoothMesh = DLLFile.ext_meshUtil_smoothMesh

ext_meshUtil_smoothMesh.restype = ctypes.c_int
ext_meshUtil_smoothMesh.argtypes = [ctypes.POINTER(zExtMesh), ctypes.c_int, ctypes.c_bool]

ext_meshUtil_getPlanarityDeviationPerFace = DLLFile.ext_meshUtil_getPlanarityDeviationPerFace
ext_meshUtil_getPlanarityDeviationPerFace.restype = ctypes.c_int
ext_meshUtil_getPlanarityDeviationPerFace.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtDoubleArray), ctypes.c_int, ctypes.c_bool, ctypes.c_double]
#ext_meshUtil_getPlanarityDeviationPerFace.argtypes[-1].value = 0.05
#ext_meshUtil_getPlanarityDeviationPerFace.argtypes[-2].value = False

ext_meshUtil_getGaussianCurvature = DLLFile.ext_meshUtil_getGaussianCurvature
ext_meshUtil_getGaussianCurvature.restype = ctypes.c_int
ext_meshUtil_getGaussianCurvature.argtypes = [ctypes.POINTER(zExtMesh), ctypes.POINTER(zExtDoubleArray)]


