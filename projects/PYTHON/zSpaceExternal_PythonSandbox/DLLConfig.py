import ctypes
import os

usdFolderPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/ov";

# Specify the path to the "usd" folder
usd_folder = os.path.abspath(usdFolderPath)

# Modify the PATH environment variable to include the "usd" folder
os.environ['PATH'] = usd_folder + os.pathsep + os.environ['PATH']

# Specify the path to the directory containing the DLL and its dependencies
dll_directory = r'C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release'

# Modify the PATH environment variable to include the DLL directory
os.environ['PATH'] = dll_directory + os.pathsep + os.environ['PATH']

class DLLConfig:
    zExternalDLLFile = ctypes.CDLL("C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/cpp/compiled/dll/zSpace_External.dll")