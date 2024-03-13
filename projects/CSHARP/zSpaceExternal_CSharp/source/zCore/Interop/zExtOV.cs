using System;
using System.Runtime.InteropServices;

namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtUSD {
        public IntPtr pointer;


    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtOmniClient {
        public IntPtr pointer;

        public int startOmniverse(string path) {
            int success = zNativeMethods.ext_omni_startOmniverse(ref this, path);
            return success;
        }
        public bool shutdownOmniverse() {
            int success = zNativeMethods.ext_omni_shutdownOmniverse(ref this);
            return success == 1;
        }

    }

    static partial class zNativeMethods {

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_omni_startOmniverse(ref zExtOmniClient extOmni, 
            [MarshalAs(UnmanagedType.LPStr)] string filePath);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_omni_shutdownOmniverse(ref zExtOmniClient extOmni);
    }
}