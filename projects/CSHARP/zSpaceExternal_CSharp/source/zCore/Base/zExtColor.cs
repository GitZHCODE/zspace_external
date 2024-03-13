using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {
    
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtColor {
        //private IntPtr pointer;
        float R; ///< red component
		float G; ///< green component
		float B; ///< blue component
		float A; ///< alpha component
		float H; ///< hue component
        float S; ///< saturation component
        float V; ///< value component

        public zExtColor(System.Drawing.Color color) {
            //this.delete pointer; 
            //pointer = new IntPtr();
            //Console.WriteLine(string.Format("\n zExtColor color {0} {1} {2}", color.R, color.G, color.B));

            this.R = color.R / 255f;
            this.G = color.G / 255f;
            this.B = color.B / 255f;
            this.A = color.A / 255f;
            this.H = 0;
            this.S = 0;
            this.V = 0;
            zNativeMethods.ext_color_computeHSV(ref this);

            //zNativeMethods.ext_color_createRGB(R, G, B, A, out this);
            //zNativeMethods.ext_color_createRGB(R, G, B, A, out this);
            //Console.WriteLine(string.Format("\n zExtColor {0} {1} {2}", R, G, B));

            
        }
        public zExtColor(float r=0, float g=0, float b=0, float a=1) {
            //this.delete pointer; 
            //pointer = new IntPtr();
            this.R = r;
            this.G = g;
            this.B = b;
            this.A = a;
            this.H = 0;
            this.S = 0;
            this.V = 0;

            zNativeMethods.ext_color_computeHSV(ref this);

            //zNativeMethods.ext_color_createRGB(R, G, B, A, out this);
        }
        public zExtColor(int r = 0, int g = 0, int b = 0, int a = 255) {
            //this.delete pointer; 
            //pointer = new IntPtr();
            this.R = r / 255f;
            this.G = g / 255f;
            this.B = b / 255f;
            this.A = a / 255f;
            this.H = 0;
            this.S = 0;
            this.V = 0;
            zNativeMethods.ext_color_computeHSV(ref this);
            //zNativeMethods.ext_color_createRGB(R, G, B, A, out this);
        }



        public System.Drawing.Color getColor() {

            System.Drawing.Color color = System.Drawing.Color.FromArgb((int)(A * 255), (int)(R * 255), (int)(G * 255), (int)(B * 255));
            return color;
        }
        public void setColor(System.Drawing.Color color) {
            //Console.WriteLine(string.Format("\n zExtColor setcolor {0} {1} {2}", color.R, color.G, color.B));

            this.R = color.R / 255f;
            this.G = color.G / 255f;
            this.B = color.B / 255f;
            this.A = color.A / 255f;

            zNativeMethods.ext_color_computeHSV(ref this);
        }
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtColorArray {
        private IntPtr pointer;
        private int arrayCount;

        public zExtColorArray(System.Drawing.Color[] colors) {
            pointer = new IntPtr();
            arrayCount = 0;
            setColors(ref colors);
        }

        public zExtColor[] getItemsExt() {
            var items = new zExtColor[arrayCount];
            zNativeMethods.ext_color_array_getItems(this, items);
            return items;
        }        
        
        public System.Drawing.Color[] getItems() {
            var items = new zExtColor[arrayCount];
            var colors = new System.Drawing.Color[arrayCount];
            zNativeMethods.ext_color_array_getItems(this, items);

            for (int i = 0; i < arrayCount; i++) {
                colors[i] = items[i].getColor();
            }
            return colors;
        }
        public void setColors(ref System.Drawing.Color[] colors) {
            var items = new zExtColor[colors.Length];
            for (int i = 0; i < colors.Length; i++) {
                items[i] = new zExtColor(colors[i]);

            }
            zNativeMethods.ext_color_setItemsFromArray(ref this, items, items.Length);           
        }

        public int getArrayCount() { return arrayCount; }
    }
    static partial class zNativeMethods {
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_color_createRGB(float r, float g, float b, float a, out zExtColor extColor);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_color_array_getItems(zExtColorArray array,
        [MarshalAs(UnmanagedType.LPArray), In, Out] zExtColor[] outItems);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_color_setItemsFromArray(ref zExtColorArray array,
        [MarshalAs(UnmanagedType.LPArray), In] zExtColor[] inItems, int count);

        //		ZSPACE_EXTERNAL int ext_color_computeHSV(zExtColor& extColor);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_color_computeRGB(ref zExtColor extColor);


        //		ZSPACE_EXTERNAL int ext_color_computeRGB(zExtColor& extColor);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_color_computeHSV(ref zExtColor extColor);

    }


}
