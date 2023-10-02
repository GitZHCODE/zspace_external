import ctypes
import os
usdFolderPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/ov";

os.add_dll_directory(usdFolderPath)
class DLLConfig:
    zExternalDLLFile = ctypes.CDLL("C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/zSpace_External.dll")

