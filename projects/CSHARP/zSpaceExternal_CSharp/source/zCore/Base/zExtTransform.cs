using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtTransform {
        private IntPtr pointer;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] row0;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] row1;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] row2;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] row3;

        public zExtTransform(float[] row0, float[] row1, float[] row2, float[] row3) {
            pointer = new IntPtr();
            this.row0 = row0;
            this.row1 = row1;
            this.row2 = row2;
            this.row3 = row3;

            initPointer();

        }

        public void initPointer() {
            zNativeMethods.ext_transform_initPointer(ref this);
        }

    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtTransformArray {
        private IntPtr pointer;
        int arrayCount;

        public zExtTransformArray(zExtTransform[] input) {
            pointer = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public zExtTransform[] getItems() {
            var output = new zExtTransform[arrayCount];
            zNativeMethods.ext_transform_array_getItems(ref this, output);

            return output;
        }
        public int getCount() {
            return arrayCount;
        }

        public void setItems(zExtTransform[] input) {
            arrayCount = input.Length;
            zNativeMethods.ext_transform_setItemsInArray(ref this, input);
        }
    }

    #region External methods
    static partial class zNativeMethods {
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_transform_array_getItems(ref zExtTransformArray array, [MarshalAs(UnmanagedType.LPArray), In, Out] zExtTransform[] output);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_transform_setItemsInArray(ref zExtTransformArray array, [In] zExtTransform[] input);

        //	ZSPACE_EXTERNAL_INLINE void ext_transform_initPointer(zExtTransform& outTransform)
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_transform_initPointer(ref zExtTransform refTransform);




    }
    #endregion

}
