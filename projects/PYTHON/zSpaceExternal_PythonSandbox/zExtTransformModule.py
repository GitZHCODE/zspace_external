import ctypes
from typing import List
#from pxr import Gf
from DLLConfigModule import DLLConfig

DLLFile = DLLConfig.zExternalDLLFile

class 
(ctypes.Structure):
    _fields_ = [
        ('_transform', ctypes.c_void_p),
        ('matrix', ctypes.c_float * 4 * 4)
    ]
    def __init__(self):
        ext_transform_initPointer(self)
        self.readonly = True

    def updateTransformFromFloatArray(self,values):
        my_array = (ctypes.c_float * 16)(*values)
        ext_transform_updateFromValues(ctypes.byref(self), my_array)

    def updateTransformFromListOfLists(self, values):
        ee_transformValues = (ctypes.c_float * 16)()
        for i in range(4):
            for j in range(4):
                ee_transformValues[i*4+j] = values[i][j]
        ext_transform_updateFromValues(ctypes.byref(self), ee_transformValues)

    def updateTransformFrom2dArray(self, values):
        ee_transformValues = (ctypes.c_float * 16)()        
        for i in range(4):
            for j in range(4):
                ee_transformValues[i*4+j] = values[i][j]
        ext_transform_updateFromValues(ctypes.byref(self), ee_transformValues)
 
    
    #def getGfMatrix(self):
    #    return Gf.Matrix4d(self.matrix[0][0],self.matrix[1][0],self.matrix[2][0],self.matrix[3][0],
    #                       self.matrix[0][1],self.matrix[1][1],self.matrix[2][1],self.matrix[3][1],
    #                       self.matrix[0][2],self.matrix[1][2],self.matrix[2][2],self.matrix[3][2],
    #                       self.matrix[0][3],self.matrix[1][3],self.matrix[2][3],self.matrix[3][3])
    
    #def getGfMatrixTransformed(self):
    #    return Gf.Matrix4d(self.matrix[0][0],self.matrix[0][1],self.matrix[0][2],self.matrix[0][3],
    #                       self.matrix[1][0],self.matrix[1][1],self.matrix[1][2],self.matrix[1][3],
    #                       self.matrix[2][0],self.matrix[2][1],self.matrix[2][2],self.matrix[2][3],
    #                       self.matrix[3][0],self.matrix[3][1],self.matrix[3][2],self.matrix[3][3])
            
    def setMatrix(self, value):
            self.updateTransformFrom2dArray(value)

    def getMatrix(self):
        return self.matrix

    matrix = property(getMatrix, setMatrix)

    @matrix.setter
    def matrix(self, value):
        self.updateTransformFrom2dArray(self.matrix)    

    matrix = property(getMatrix, setMatrix)

# Define the function prototypes with ctypes function annotations
ext_transform_createNew = DLLFile.ext_transform_createNew
ext_transform_createNew.restype = None
ext_transform_createNew.argtypes = [
    ctypes.POINTER(zExtTransform),
    ]    

ext_transform_createNewFromArray = DLLFile.ext_transform_createNewFromArray
ext_transform_createNewFromArray.restype = None
ext_transform_createNewFromArray.argtypes = [
    ctypes.POINTER(ctypes.c_float),
    ctypes.POINTER(zExtTransform),
    ]    

ext_transform_updateFromValues = DLLFile.ext_transform_updateFromValues
ext_transform_updateFromValues.restype = None
ext_transform_updateFromValues.argtypes = [
    ctypes.POINTER(zExtTransform),
    ctypes.POINTER(ctypes.c_float),
    ]  