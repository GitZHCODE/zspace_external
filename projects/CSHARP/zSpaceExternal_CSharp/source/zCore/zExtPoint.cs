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

        public zExtPoint(float x, float y, float z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtPointArray {
        private IntPtr pointer;
        int arrayCount;

        public zExtPointArray(zExtPoint[] input) {
            pointer = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public zExtPoint[] getItems() {
            var output = new zExtPoint[arrayCount];
            zNativeMethods.ext_point_getItemsFromArray(ref this, output);
            
            return output;
        }
        public int getCount() {
            return arrayCount;
        }

        public bool setItems(zExtPoint[] input) {
            int chk = zNativeMethods.ext_point_setItemsFromArray(ref this, input, input.Length);
            return chk == 1;
        }
    }

    #region External methods for array
    static partial class zNativeMethods {

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_point_getItemsFromArray(ref zExtPointArray array,
        [MarshalAs(UnmanagedType.LPArray), In, Out] zExtPoint[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_point_setItemsFromArray(ref zExtPointArray array,
        [MarshalAs(UnmanagedType.LPArray), In] zExtPoint[] inItems, int count);


    }
    #endregion


}
