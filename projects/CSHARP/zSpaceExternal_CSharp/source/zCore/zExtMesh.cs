using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtMesh {
        private IntPtr o_mesh; //zObjMesh*
        private int vCount;
        private int fCount;

        public zExtPoint[] getMeshPoints() {
            zExtPointArray mid;
            zNativeMethods.ext_mesh_getMeshPosition(ref this, out mid);
            var items = mid.getItems();
            for (int i = 0; i < items.Length; i++) {
                Console.WriteLine(items[i].x + ", " + items[i].y + ", " +items[i].z);
                //Console.WriteLine(string.Format("{0}, {1}, {2}"), items[i].x, items[i].y, items[i].z);
            }
            return items;
        }
        public System.Drawing.Color[] getMeshColors() {
            zExtColorArray mid;
            zNativeMethods.ext_mesh_getMeshColors(ref this, out mid);
            return mid.getColors();
        }
        public List<int>[] getFaces() {
            zExtIntArray extPCount;
            zExtIntArray extPConnect;
            zNativeMethods.ext_mesh_getMeshPolygonDate(ref this, out extPCount, out extPConnect);


            //List<int> fVerts = new List<int>();

            List<int>[] faces = new List<int>[fCount];


            int polyconnectsCurrentIndex = 0;
            var polyCount = extPCount.getItems();
            var polyConnects = extPConnect.getItems();

            //Console.WriteLine(string.Format("fcount - polyCount {0}-{1} \n", fCount, polyCount.Length));

            for (int i = 0; i < polyCount.Length; i++) {
                int num_faceVerts = polyCount[i];
                //Console.WriteLine("\n face: " + i + "\n");
                faces[i] = new List<int>();
                //fVerts.clear();
                //fVerts.Clear();
                for (int j = 0; j < num_faceVerts; j++) {
                    //fVerts.push_back(polyConnects[polyconnectsCurrentIndex + j]);
                    //fVerts.Add(polyConnects[polyconnectsCurrentIndex + j]);
                    faces[i].Add(polyConnects[polyconnectsCurrentIndex + j]);
                    //Console.Write(polyConnects[polyconnectsCurrentIndex + j] + ", ");
                }

                //addPolygon(fVerts);
                //faces[i] = fVerts;
              
                polyconnectsCurrentIndex += num_faceVerts;

            }

            //foreach (var fff in faces) {
            //    Console.WriteLine("\n face: \n");

            //    foreach (var f2 in fff) {
            //        Console.WriteLine(f2);

            //    }
            //}

            
            return faces;
        }

        //public float[][] getMeshPositions2D() {
        //    float[] pos1D = new float[vCount * 3];
        //    float[] color1D = new float[vCount * 4];
        //    ext_meshUtil_getMeshPosition(this, pos1D, color1D);
        //    return zSpaceUtil.Convert1DtoArray2D(pos1D, 3);
        //}
        //public float[] getMeshPositions1D() {
        //    float[] pos1D = new float[vCount * 3];
        //    Console.WriteLine("countget " + vCount * 3);

        //    float[] color1D = new float[vCount * 4];
        //    ext_meshUtil_getMeshPosition(this, pos1D, color1D);
        //    return pos1D;
        //}
        //public System.Drawing.Color[] getMeshVColors() {
        //    float[] pos1D = new float[vCount * 3];
        //    float[] color1D = new float[vCount * 4];
        //    ext_meshUtil_getMeshPosition(this, pos1D, color1D);
        //    var color = new System.Drawing.Color[vCount];
        //    for (int i = 0; i < vCount; i++) {
        //        int r = (int)zSpaceUtil.Remap(color1D[i * 4 + 0], 0, 1, 0, 255);
        //        int g = (int)zSpaceUtil.Remap(color1D[i * 4 + 1], 0, 1, 0, 255);
        //        int b = (int)zSpaceUtil.Remap(color1D[i * 4 + 2], 0, 1, 0, 255);
        //        int a = (int)zSpaceUtil.Remap(color1D[i * 4 + 3], 0, 1, 0, 255);
        //        color[i] = System.Drawing.Color.FromArgb(a, r, g, b);
        //    }
        //    return color;
        //}

        //public void getMeshPositionsAndColors(out float[][] pos, out System.Drawing.Color[] color) {
        //    float[] pos1D = new float[vCount * 3];
        //    float[] color1D = new float[vCount * 4];
        //    ext_meshUtil_getMeshPosition(this, pos1D, color1D);
        //    pos = zSpaceUtil.Convert1DtoArray2D(pos1D, 3);
        //    color = new System.Drawing.Color[vCount];
        //    for (int i = 0; i < vCount; i++) {
        //        int r = (int)zSpaceUtil.Remap(color1D[i * 4 + 0], 0, 1, 0, 255);
        //        int g = (int)zSpaceUtil.Remap(color1D[i * 4 + 1], 0, 1, 0, 255);
        //        int b = (int)zSpaceUtil.Remap(color1D[i * 4 + 2], 0, 1, 0, 255);
        //        int a = (int)zSpaceUtil.Remap(color1D[i * 4 + 3], 0, 1, 0, 255);
        //        color[i] = System.Drawing.Color.FromArgb(a, r, g, b);
        //    }
        //}

        //public List<int>[] getMeshFaceConnection() {
        //    int[] pCounts = new int[fCount];
        //    ext_meshUtil_getMeshFaceCount(this, pCounts);
        //    int pConnectLength = 0;
        //    foreach (var item in pCounts) {
        //        pConnectLength += item;
        //    }
        //    int[] pConnects = new int[pConnectLength];
        //    ext_meshUtil_getMeshFaceConnect(this, pConnects);
        //    int counter = 0;
        //    var faceConnects = new List<int>[fCount];
        //    for (int i = 0; i < fCount; i++) {
        //        faceConnects[i] = new List<int>();
        //        for (int j = 0; j < pCounts[i]; j++) {
        //            faceConnects[i].Add(counter);
        //            counter++;
        //        }
        //    }
        //    return faceConnects;
        //}

        public int getVCount() {
            return vCount;
        }
        public int getFaceCount() {
            return fCount;
        }



        public void getFaceColors() {

        }

        #region External Methods

        const string path = dllPaths.tsPath;

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_meshUtil_createMeshOBJ(double[] _vertexPositions, int[] _polyCounts, int[] _polyConnects, int numVerts, int numFaces, ref zExtMesh out_mesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_meshUtil_getMeshPosition(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVPostions,
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVColors);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_meshUtil_getMeshFaceCount(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfCounts);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_meshUtil_getMeshFaceConnect(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfConnects);






        #endregion
    }
    #region External methods for array
    static partial class zNativeMethods {
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_mesh_getMeshPosition(ref zExtMesh objMesh, out zExtPointArray pointArray);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_mesh_getMeshColors(ref zExtMesh objMesh, out zExtColorArray colorArray);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_mesh_getMeshPolygonDate(ref zExtMesh objMesh, out zExtIntArray pCount, out zExtIntArray pConnect);
    }
    #endregion
}