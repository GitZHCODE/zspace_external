
import DLLConfig
import ctypes

# Load the DLL file that contains the C++ external methods
DLLFile = DLLConfig.DLLConfig.zExternalDLLFile

class zExtMesh(ctypes.Structure):
    _fields_ = [
        ("extPointer", ctypes.c_void_p),
        ("vCount", ctypes.c_int),
        ("fCount", ctypes.c_int)
    ]

DLLFile.ext_meshUtil_createMeshOBJFromArray.argtypes = [
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_int),
    ctypes.POINTER(ctypes.c_int),
    ctypes.c_int,
    ctypes.c_int,
    ctypes.POINTER(zExtMesh)
]

DLLFile.ext_meshUtil_createMeshOBJFromFile.argtypes = [
    ctypes.c_char_p,
    ctypes.POINTER(zExtMesh)
]

DLLFile.ext_meshUtil_exportToJson.argtypes = [
    zExtMesh,
    ctypes.c_char_p
]

DLLFile.ext_meshUtil_getMeshFaceCount.argtypes = [
    zExtMesh,
    ctypes.POINTER(ctypes.c_int)
]

DLLFile.ext_meshUtil_getMeshPosition.argtypes = [
    zExtMesh,
    ctypes.POINTER(ctypes.c_float),
    ctypes.POINTER(ctypes.c_float)
]

DLLFile.ext_meshUtil_getMeshFaceConnect.argtypes = [
    zExtMesh,
    ctypes.POINTER(ctypes.c_int)
]

DLLFile.ext_meshUtil_getMeshCentre.argtypes = [
    zExtMesh,
    ctypes.POINTER(ctypes.c_float)
]

DLLFile.ext_meshUtil_getMeshsFromMeshArray.argtypes = [
    zExtMeshArray,
    ctypes.POINTER(zExtMesh)
]

DLLFile.ext_meshUtil_getMeshsFromMeshPointerArray.argtypes = [
    zExtMeshPointerArray,
    ctypes.POINTER(zExtMesh)
]

DLLFile.ext_mesh_getMeshPosition.argtypes = [
    zExtMesh,
    zExtPointArray
]

DLLFile.ext_mesh_getMeshColors.argtypes = [
    zExtMesh,
    zExtColorArray
]

DLLFile.ext_mesh_getMeshPolygonDate.argtypes = [
    zExtMesh,
    zExtIntArray,
    zExtIntArray
]

DLLFile.ext_mesh_catmullclark.argtypes = [
    zExtMesh,
    ctypes.c_int,
    ctypes.c_bool
]






