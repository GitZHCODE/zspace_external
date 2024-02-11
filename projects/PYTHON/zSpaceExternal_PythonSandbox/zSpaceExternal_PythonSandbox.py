import ctypes
import DLLConfigModule as DLLConfig
import sys
import importlib
import zExtColorModule
import zExtMeshModule
from zExtMeshModule import zExtMesh
import zExtUtilsCoreModule
import os


from zExtColorModule import zExtColor

#DLLFile = ctypes.CDLL("C:/Users/Keerti.Manney/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/zSpace_External.dll")
DLLFile = DLLConfig.DLLConfig;
print("\n Running Python")
filepath = r"C:\Users\heba.eiz\source\repos\GitZHCODE\zspace_alice\ALICE_PLATFORM\x64\Release\EXE\data\cube-2.obj"
#ext_meshUtil_createMeshFromFile = DLLFile.ext_meshUtil_createMeshFromFile
print(os.path.exists(filepath)) 
myMesh = zExtMesh()
print(f'extPointer before: {myMesh.extPointer}')
zExtMeshModule.ext_meshUtil_createMeshFromFile(filepath.encode('utf-8'), ctypes.byref(myMesh))
print(f'extPointer after: {myMesh.extPointer}')
print("\n opened a mesh")
max_faces = 100  
outfCounts = myMesh.fCount
#result = zExtMeshModule.ext_meshUtil_getMeshFaceCount(myMesh, outfCounts)
print(f'Result: {outfCounts}')
#ext_meshUtil_getMeshFaceCount = zExtMeshModule.ext_meshUtil_getMeshFaceCount(myMesh, ctypes.byref(numberOfFaces))
#if result == 1:  # Function succeeded
#    # Print the count of vertices for the first face
#else:
#    print("meshPointer is null or some other error occurred")



#devs = zExtUtilsCoreModule.zExtDoubleArray ()

#c = 0.05

#ext_meshUtil_smoothMesh = DLLFile.ext_meshUtil_smoothMesh
#ext_meshUtil_smoothMesh (myMesh,3,True)