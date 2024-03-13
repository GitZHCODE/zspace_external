using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace
{
    public static class dllPaths {
        //private const string solutionDir = Properties.Settings.Default.SolutionDir;
        //public const string tsPath = "../../cpp/compiled/zSpace_External.dll";
        //public const string tsPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/cpp/compiled/dll/zSpace_External.dll";



        public const string tsPath = "zSpace_External.dll";
        //public const string tsPath = "zspace/zSpace_External.dll";
        //public const string tsPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/zspace/zSpace_External.dll";



    }
    public static partial class zNativeMethods {
        const string path = dllPaths.tsPath;

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool SetDllDirectory(string lpPathName);
    }
}
