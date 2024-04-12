using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtIntArray {
        private IntPtr pointer; 
        private int arrayCount;

        public zExtIntArray(int[] input) {
            pointer = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public int[] getItems() {
            int[] items = new int[arrayCount];
            zNativeMethods.ext_int_array_getItems(ref this, items);
            return items;
        }

        public void setItems(int[] input) {
            zNativeMethods.ext_int_array_setItems(ref this, input, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }
    
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtIntArray2D {
        private IntPtr pointer;
        private int arrayCount;

        public int[][] getItems() {
            var output = new int[arrayCount][];
            var mid = new zExtIntArray[arrayCount];
            zNativeMethods.ext_int_array2D_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getItems();                
            }
            return output;
        }
        public void setItems(int[][] input) {
            var mid = new zExtIntArray[input.Length];
            for (int i = 0; i < input.Length; i++) {
                mid[i].setItems(input[i]);
            }
            zNativeMethods.ext_int_array2D_setItems(ref this, mid, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtFloatArray {
        private IntPtr pointer;
        private int arrayCount;

        public zExtFloatArray(float[] input) {
            pointer = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }
        public float[] getItems() {
            float[] items = new float[arrayCount];
            zNativeMethods.ext_float_array_getItems(ref this, items);
            return items;
        }

        public void setItems(float[] input) {
            zNativeMethods.ext_float_setItemsFromArray(ref this, input, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtFloatArray2D {
        private IntPtr pointer;
        private int arrayCount;

        public float[][] getItems() {
            var output = new float[arrayCount][];
            var mid = new zExtFloatArray[arrayCount];
            zNativeMethods.ext_float_array2D_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getItems();
            }
            return output;
        }
        public void setItems(float[][] input) {
            var mid = new zExtFloatArray[input.Length];
            for (int i = 0; i < input.Length; i++) {
                mid[i].setItems(input[i]);
            }
            zNativeMethods.ext_float_array2D_setItems(ref this, mid, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct zExtDoubleArray {
        private IntPtr pointer;
        private int arrayCount;


        public double[] getItems() {
            double[] items = new double[arrayCount];
            zNativeMethods.ext_double_array_getItems(ref this, items);
            return items;
        }

        public void setItems(double[] input) {
            zNativeMethods.ext_double_setItemsFromArray(ref this, input, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtDoubleArray2D {
        private IntPtr pointer;
        private int arrayCount;

        public double[][] getItems() {
            var output = new double[arrayCount][];
            var mid = new zExtDoubleArray[arrayCount];
            zNativeMethods.ext_double_array2D_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getItems();
            }
            return output;
        }
        public void setItems(double[][] input) {
            var mid = new zExtDoubleArray[input.Length];
            for (int i = 0; i < input.Length; i++) {
                mid[i].setItems(input[i]);
            }
            zNativeMethods.ext_double_array2D_setItems(ref this, mid, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtString {
        private IntPtr pointer;
        private int arrayCount;

        public string getString() {
            char[] c = new char[arrayCount];
            //string s = new string(c);

            //Console.WriteLine(arrayCount);
            zNativeMethods.ext_string_getCharArrayFromExtString(ref this, c);
            //int chk = 
                //zNativeMethods.ext_string_getCharArrayFromExtString(ref this, ch);
            //Console.WriteLine(chk);
            //Console.WriteLine(s);

            return new string(c);
        }

        public void setString(string input) {
            char[] c = new char[input.Length];

            //zNativeMethods.ext_string_setExtStringFromCharArray(ref this, c, c.Length);
            zNativeMethods.ext_string_setExtStringFromCharArray(ref this, input, c.Length);


        }
    }
    
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtStringArray {
        //[MarshalAs(UnmanagedType.AnsiBStr)]

        private IntPtr pointer;
        private int arrayCount;


        public string[] getItems() {
            //string[] items = new string[arrayCount];
            var output = new string[arrayCount];
            var mid = new zExtString[arrayCount];
            zNativeMethods.ext_string_array_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getString();
            }
            //for (int i = 0; i < arrayCount; i++) {
            //    //Console.WriteLine(i);
            //    //items[i] = zNativeMethods.ext_string_getItemFromArray(ref this, i);
            //    int length = zNativeMethods.ext_string_getItemFromArrayCharLength(ref this, i);
            //   // Console.WriteLine("c# char array length " + length);
            //    char[] c = new char[length];
            //    zNativeMethods.ext_string_getItemFromArrayChar(ref this, i, c);
            //    items[i] = new string(c);
            //}
            //zNativeMethods.ext_string_array_getItems(ref this, items);
            return output;
        }

        public void setItems(string[] input) {
            zExtString[] mid = new zExtString[input.Length];
            for (int i = 0; i < input.Length; i++) {

                mid[i] = new zExtString();
                mid[i].setString(input[i]);
            }
            //Console.WriteLine("array 1 + " + input.Length);
            
            zNativeMethods.ext_string_setItemsFromArray(ref this, mid, input.Length);
            //Console.WriteLine("array 2");

        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtStringArray2D {
        private IntPtr pointer;
        private int arrayCount;

        public string[][] getItems() {
            var output = new string[arrayCount][];
            var mid = new zExtStringArray[arrayCount];
            zNativeMethods.ext_string_array2D_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getItems();
            }
            return output;
        }
        public void setItems(string[][] input) {
            var mid = new zExtStringArray[input.Length];
            for (int i = 0; i < input.Length; i++) {
                mid[i].setItems(input[i]);
            }
            zNativeMethods.ext_string_array2D_setItems(ref this, mid, mid.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct zExtBoolArray {
        private IntPtr pointer;
        private int arrayCount;


        public bool[] getItems() {
            bool[] items = new bool[arrayCount];
            zNativeMethods.ext_bool_array_getItems(ref this, items);
            return items;
        }

        public void setItems(bool[] input) {
            zNativeMethods.ext_bool_setItemsFromArray(ref this, input, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtBoolArray2D {
        private IntPtr pointer;
        private int arrayCount;

        public bool[][] getItems() {
            var output = new bool[arrayCount][];
            var mid = new zExtBoolArray[arrayCount];
            zNativeMethods.ext_bool_array2D_getItems(ref this, mid);
            for (int i = 0; i < arrayCount; i++) {
                output[i] = mid[i].getItems();
            }
            return output;
        }
        public void setItems(bool[][] input) {
            var mid = new zExtBoolArray[input.Length];
            for (int i = 0; i < input.Length; i++) {
                mid[i].setItems(input[i]);
            }
            zNativeMethods.ext_bool_array2D_setItems(ref this, mid, input.Length);
        }

        public int getArrayCount() { return arrayCount; }
    }



    #region External methods for array
    static partial  class zNativeMethods {

        #region Int Array 1D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_int_array_getItems(ref zExtIntArray array,
        [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outItems);
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_int_array_setItems(ref zExtIntArray array,
        [MarshalAs(UnmanagedType.LPArray), In] int[] outItems, int count);
        #endregion
        #region Int Array 2D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_int_array2D_getItems(ref zExtIntArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtIntArray[] outItems); 
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_int_array2D_setItems(ref zExtIntArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtIntArray[] outItems, int count);
        #endregion
        #region Float Array 1D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_float_array_getItems(ref zExtFloatArray array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_float_setItemsFromArray(ref zExtFloatArray array,
            [MarshalAs(UnmanagedType.LPArray), In] float[] outItems, int count);
        #endregion
        #region Float Array 2D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_float_array2D_getItems(ref zExtFloatArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtFloatArray[] outItems);  

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_float_array2D_setItems(ref zExtFloatArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtFloatArray[] outItems, int count);
        #endregion
        #region Double Array 1D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_double_array_getItems(ref zExtDoubleArray array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] double[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_double_setItemsFromArray(ref zExtDoubleArray array,
            [MarshalAs(UnmanagedType.LPArray), In] double[] outItems, int count);
        #endregion
        #region Double Array 2D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_double_array2D_getItems(ref zExtDoubleArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtDoubleArray[] outItems);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_double_array2D_setItems(ref zExtDoubleArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtDoubleArray[] outItems, int count);
        #endregion
        #region String
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_string_getCharArrayFromExtString(ref zExtString extString,
            [MarshalAs(UnmanagedType.LPArray), In, Out] char[] outString
           );
        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //public static extern int ext_string_setExtStringFromCharArray(ref zExtString extString,
        //    [MarshalAs(UnmanagedType.LPArray), In] char[] inString, int charCount);
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_string_setExtStringFromCharArray(ref zExtString extString,
            [MarshalAs(UnmanagedType.LPStr), In] string inString, int charCount);
        #endregion
        #region String Array 1D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_string_array_getItems(ref zExtStringArray array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtString[] outItems);
        //[MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr .LPWStr), In, Out] string[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_string_setItemsFromArray(ref zExtStringArray array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtString[] inItems, int count);
            //[MarshalAs(UnmanagedType.LPArray), In] string[] inItems, int count);
        #endregion
        #region String Array 2D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_string_array2D_getItems(ref zExtStringArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtStringArray[] outItems);
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_string_array2D_setItems(ref zExtStringArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtStringArray[] outItems, int count);
        #endregion
        #region Bool Array 1D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_bool_array_getItems(ref zExtBoolArray array,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1), In, Out] bool[] outItems);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_bool_setItemsFromArray(ref zExtBoolArray array,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1), In] bool[] outItems, int count);
        #endregion
        #region Bool Array 2D
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_bool_array2D_getItems(ref zExtBoolArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtBoolArray[] outItems);
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_bool_array2D_setItems(ref zExtBoolArray2D array,
            [MarshalAs(UnmanagedType.LPArray), In] zExtBoolArray[] outItems, int count);
        #endregion




        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //[return: MarshalAs(UnmanagedType.LPStr)]
        //public static extern string ext_string_getItemFromArray(ref zExtStringArray array, int index);

        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //public static extern int ext_string_getItemFromArrayCharLength(ref zExtStringArray array, int index);
        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //public static extern void ext_string_getItemFromArrayChar(ref zExtStringArray array, int index,
        //    [MarshalAs(UnmanagedType.LPArray), In, Out] char[] item
        //   );

    }
    #endregion

    
}
