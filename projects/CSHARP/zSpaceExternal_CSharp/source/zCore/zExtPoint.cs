using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtPoint2 {
        public float x;
        public float y;
        public float z;

        public zExtPoint2(float xx, float yy, float zz) {
            x = xx;
            y = yy;
            z = zz;
        }
        //public static void testAdd(zExtPoint2 pt1, zExtPoint2 pt2) {
        //    Console.WriteLine(pt2.x + " " + pt1.x);
        //    zNativeMethods.ext_point_testAdd(ref pt1, ref pt2);
        //}
    }

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
            zNativeMethods.ext_point_array_getItems(ref this, output);

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


    [StructLayout(LayoutKind.Sequential)]
    public struct zExtPointArray2D {
        private IntPtr pointer;
        int arrayCount;

        public zExtPointArray2D(zExtPointArray[] input) {
            pointer = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public zExtPointArray[] getItems() {
            var output = new zExtPointArray[arrayCount];
            zNativeMethods.ext_point_array2D_getItems(ref this, output);

            return output;
        }
        public int getCount() {
            return arrayCount;
        }

        public bool setItems(zExtPointArray[] input) {
            int chk = zNativeMethods.ext_point_array2D_setItems(ref this, input, input.Length);
            return chk == 1;
        }
    }


    #region External methods for array
    static partial class zNativeMethods {

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_point_array_getItems(ref zExtPointArray array,
        [MarshalAs(UnmanagedType.LPArray), In, Out] zExtPoint[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_point_setItemsFromArray(ref zExtPointArray array,
        [MarshalAs(UnmanagedType.LPArray), In] zExtPoint[] inItems, int count);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_point_array2D_getItems(ref zExtPointArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtPointArray[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_point_array2D_setItems(ref zExtPointArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtPointArray[] inItems, int count);


    }
    #endregion


}
