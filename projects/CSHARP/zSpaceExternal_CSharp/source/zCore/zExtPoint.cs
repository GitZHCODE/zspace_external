using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtPoint {
        public float x;
        public float y;
        public float z;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtPointArray {
        private IntPtr pointer;
        int arrayCount;

        public zExtPoint[] getItems() {
            var output = new zExtPoint[arrayCount];
            zNativeMethods.ext_point_getItemsFromArray(ref this, output);
            
            return output;
        }
        public int getCount() {
            return arrayCount;
        }
    }

    #region External methods for array
    static partial class zNativeMethods {

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_point_getItemsFromArray(ref zExtPointArray array,
        [MarshalAs(UnmanagedType.LPArray), In, Out] zExtPoint[] outItems);


    }
    #endregion


}
