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

DLLFile = ctypes.CDLL("C:/Users/Keerti.Manney/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/zSpace_External.dll")
print("\n Running Python")
filepath = r"C:\Users\Keerti.Manney\source\repos\GitZHCODE\zspace_alice\ALICE_PLATFORM\x64\Release\EXE\data\TestData\alicetest3.obj"
#ext_meshUtil_createMeshOBJFromFile = DLLFile.ext_meshUtil_createMeshOBJFromFile
print(os.path.exists(filepath)) 
myMesh = zExtMesh()
print(f'extPointer before: {myMesh.extPointer}')
zExtMeshModule.ext_meshUtil_createMeshOBJFromFile(filepath.encode('utf-8'), ctypes.byref(myMesh))
print(f'extPointer after: {myMesh.extPointer}')
print("\n opened a mesh")
max_faces = 100  
outfCounts = (ctypes.c_int * max_faces)()
result = zExtMeshModule.ext_meshUtil_getMeshFaceCount(myMesh, outfCounts)
print(f'Result: {result}')
print(outfCounts[0]) 
#ext_meshUtil_getMeshFaceCount = zExtMeshModule.ext_meshUtil_getMeshFaceCount(myMesh, ctypes.byref(numberOfFaces))
#if result == 1:  # Function succeeded
#    # Print the count of vertices for the first face
#else:
#    print("meshPointer is null or some other error occurred")



#devs = zExtUtilsCoreModule.zExtDoubleArray ()

#c = 0.05

#ext_meshUtil_catmullclark = DLLFile.ext_meshUtil_catmullclark
#ext_meshUtil_catmullclark (myMesh,3,True)

