using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Collections;
using Rhino.Geometry;
using static zSpace.zExtRhinoUtil;

namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtMesh {
        private IntPtr o_mesh; //zObjMesh*
        private int vCount;
        private int fCount;
        
        
        //public zExtMesh() {
        //    o_mesh = IntPtr.Zero;
        //    vCount = 0;
        //    fCount = 0;
        //}
        public zExtMesh(string s) {

            o_mesh = IntPtr.Zero;
            vCount = 0;
            fCount = 0;

            from(s);
        }
        public bool isValid() {
            return !(o_mesh == IntPtr.Zero || vCount == 0);
           
        }
        /// <summary>
        /// Creates a duplicate of the current mesh .
        /// </summary>
        /// <returns>The duplicated mesh.</returns>
        public zExtMesh duplicate() {
            zExtMesh outObject;
            zNativeMethods.ext_mesh_duplicate(in this, out outObject);
            return outObject;
        }

        public zExtPoint[] getMeshPoints() {
            zExtPointArray mid;
           //zExtMesh mesh = this;
            var chk = zNativeMethods.ext_mesh_getVertexPositions(ref this, out mid);
            if (!zStatusCodeUtil.getErrorCheck(chk)) {
                var items = mid.getItems();
                //for (int i = 0; i < items.Length; i++) {
                //    Console.WriteLine(items[i].x + ", " + items[i].y + ", " +items[i].z);
                //    //Console.WriteLine(string.Format("{0}, {1}, {2}"), items[i].x, items[i].y, items[i].z);
                //}
                return items;
            }
            else {
                throw new ArgumentException(string.Format("Failed with error {0}", zStatusCodeUtil.getCodeString(chk)));
            }
            
        }
        public System.Drawing.Color[] getMeshColors() {
            
            zExtColorArray mid;
           //zExtMesh mesh = this;
            zNativeMethods.ext_mesh_getMeshColors(ref this, out mid);
            var colors = mid.getItems();
            return colors;
        }
        public List<int>[] getFaces() {
            zExtIntArray extPCount;
            zExtIntArray extPConnect;
            //zExtMesh mesh = this;
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

        /// <summary>
        /// Get the number of vertices of mesh
        /// </summary>
        /// <returns></returns>
        public int getVCount() {
            return vCount;
        }
        /// <summary>
        /// Get the number of faces of mesh
        /// </summary>
        /// <returns></returns>
        public int getFaceCount() {
            return fCount;
        }

        /// <summary>
        /// Get the 
        /// </summary>
        private void getFaceColors() {

        }

        /// <summary>
        /// Create a mesh from a list of vertices and faces
        /// </summary>
        /// <param name="_vertexPositions"></param>
        /// <param name="_polyCounts"></param>
        /// <param name="_polyConnects"></param>
        /// <returns></returns>
        public zStatusCode createMesh(in zExtPointArray _vertexPositions, in zExtIntArray _polyCounts, in zExtIntArray _polyConnects) {
            ////zExtMesh mesh = this;
            var chk = zNativeMethods.ext_mesh_createFromArrays(in _vertexPositions, in _polyCounts, in _polyConnects, ref this);
            Console.WriteLine(chk);
            Console.WriteLine(vCount);
            //return chk.getErrorCheck();
            return chk;// chk.getErrorCheck();
        }
        /// <summary>
        /// Creat a mesh from a list of vertices, faces and colors
        /// </summary>
        /// <param name="_vertexPositions"></param>
        /// <param name="_polyCounts"></param>
        /// <param name="_polyConnects"></param>
        /// <param name="colors"></param>
        /// <returns></returns>
        public zStatusCode createMesh(in zExtPointArray _vertexPositions, in zExtIntArray _polyCounts, in zExtIntArray _polyConnects, ref System.Drawing.Color[] colors) {
            //zExtMesh mesh = this;
            var chk = zNativeMethods.ext_mesh_createFromArrays(in _vertexPositions, in _polyCounts, in _polyConnects, ref this);
            //Console.WriteLine("\n ext_mesh_createFromArrays " + chk);
            //Console.WriteLine("\n colors.Length " + colors.Length);
            if (colors.Length == this.vCount) {
                var extColors = new zExtColorArray();
                //Console.WriteLine("\n new zExtColorArray ");
                //Console.WriteLine("\n colors.Length " + colors.Length);

                extColors.setColors(ref colors);
                var chk2 = zNativeMethods.ext_mesh_setMeshVertexColors(ref this, extColors);
                //Console.WriteLine("\n ext_mesh_setMeshVertexColors " + chk2);
                //return chk == 1 && chk2 == 1;
                return zStatusCodeUtil.getErrorCheck(chk) && zStatusCodeUtil.getErrorCheck(chk2)? zStatusCode.zSuccess : zStatusCode.zFail;
            }
                return chk;
        }
        /// <summary>
        /// Create a mesh from a file
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public zStatusCode from(string filePath) {
            //zExtMesh mesh = this;
            
            var success = zNativeMethods.ext_mesh_from(filePath, ref this);
            //return (int) success.getCode();
            return success;
        }

        /// <summary>
        /// Create file from mesh
        /// </summary>
        /// <param name="filePath"> The path of the file to be written </param>
        /// <returns> True if the file is written successfully </returns>
        public zStatusCode to(string filePath) {
           //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_to(ref this, filePath);
            return success;
        }

        /// <summary>
        /// Export extMesh to JSON format
        /// </summary>
        /// <param name="json">json object</param>
        /// <returns></returns>
        public zStatusCode to(ref zExtJSON json) {
           //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_toJSON(ref this, ref json);
            return success;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="json"></param>
        /// <returns></returns>
        public zStatusCode from(ref zExtJSON json) {
           //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_fromJSON(ref json, ref this);
            return success;
        }


        public zStatusCode to(ref zExtUSD usd) {
            var success = zNativeMethods.ext_mesh_toUSD(ref this, ref usd);
            return success;
        }
        public zStatusCode from(ref zExtUSD usd) {
            var success = zNativeMethods.ext_mesh_fromUSD(ref usd, ref this);
            return success;
        }
        public bool toTest() {
            try {

                var extPts = this.getMeshPoints();
                var pts = new Point3d[extPts.Length];
                for (int i = 0; i < pts.Length; i++) {
                    pts[i] = PointUtil.toRhinoPoint(extPts[i]);
                }

                var faceConnect = this.getFaces();
                foreach (var fn in faceConnect) {
                    if (fn.Count < 3) continue;
                    else if (fn.Count == 3 || fn.Count == 4) {
                        MeshFace face = fn.Count == 3 ? new MeshFace(fn[0], fn[1], fn[2]) : new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                    }
                    else {
                        var meshFaceIndexList = Enumerable.Range(0, fn.Count - 2).ToList();
                        MeshNgon ngon = MeshNgon.Create(fn, meshFaceIndexList);
                    }
                }

                var colors = this.getMeshColors();
              
                return true;
            }
            catch (Exception) {
                return false;
            }
        }


#if RHINO_CSHARP
        public zStatusCode to(out Mesh mesh) {
            mesh = new Mesh();
            try {
                mesh.Vertices.Clear();
                //Console.WriteLine("extMesh " + extMesh.getVCount());

                var extPts = this.getMeshPoints();
                var pts = new Point3d[extPts.Length];
                for (int i = 0; i < pts.Length; i++) {
                    pts[i] = PointUtil.toRhinoPoint(extPts[i]);
                }
                mesh.Vertices.AddVertices(pts);

                var faceConnect = this.getFaces();
                foreach (var fn in faceConnect) {
                    if (fn.Count < 3) continue;
                    else if (fn.Count == 3 || fn.Count == 4) {
                        MeshFace face = fn.Count == 3 ? new MeshFace(fn[0], fn[1], fn[2]) : new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                        mesh.Faces.AddFace(face);
                    }
                    else {
                        var meshFaceIndexList = Enumerable.Range(0, fn.Count - 2).ToList();
                        MeshNgon ngon = MeshNgon.Create(fn, meshFaceIndexList);
                        mesh.Ngons.AddNgon(ngon);
                    }
                }

                mesh.VertexColors.Clear();
                var colors = this.getMeshColors();
                if (colors.Length == mesh.Vertices.Count) {
                    mesh.VertexColors.AppendColors(colors);
                }

                mesh.RebuildNormals();
                return zStatusCode.zSuccess;
            }
            catch (Exception) {
                return zStatusCode.zThrowError;
            }
        }
        public zStatusCode from(in Mesh rhinoMesh) {
            try {
                this = new zExtMesh();
                zExtPointArray extpts = new zExtPointArray();
                var pts = new zExtPoint[rhinoMesh.Vertices.Count];
                for (int i = 0; i < rhinoMesh.Vertices.Count; i++) {
                    pts[i].x = rhinoMesh.Vertices[i].X;
                    pts[i].y = rhinoMesh.Vertices[i].Y;
                    pts[i].z = rhinoMesh.Vertices[i].Z;
                }
                extpts.setItems(pts);
                List<int> pCountList = new List<int>();
                List<int> pConnectList = new List<int>();
                // all faces and ngons;
                var ngons = rhinoMesh.GetNgonAndFacesEnumerable().ToList();
                for (int i = 0; i < ngons.Count; i++) {
                    pCountList.Add(ngons[i].BoundaryVertexCount);
                    foreach (var p in ngons[i].BoundaryVertexIndexList()) {
                        pConnectList.Add((int)p);
                    }
                }
                zExtIntArray countArray = new zExtIntArray();
                zExtIntArray connectArray = new zExtIntArray();
                countArray.setItems(pCountList.ToArray());
                connectArray.setItems(pConnectList.ToArray());
                var colors = rhinoMesh.VertexColors.ToArray();
                var chk = createMesh(in extpts, in countArray, in connectArray, ref colors);

                return chk;
            }
            catch (Exception) {
               return zStatusCode.zThrowError;
            }
        }

#endif
        /// <summary>
        /// Get the planarity deviation per face for a zExtMesh object.
        /// </summary>
        /// <param name="colorFaces">True if you need to color mesh faces</param>
        /// <param name="tolerance">Planarity tolerance</param>
        /// <param name="planarityDevs">Out array of deviations values</param>
        /// <param name="type">Type of planarity check to calculate. 0 for Quad diagonals method, and 1 for Volume method </param>
        /// <returns> True if the method was run successfully</returns>
        public zStatusCode getPlanarityDeviationPerFace(bool colorFaces, double tolerance, out double[] planarityDevs, int type = 0) {
            zExtDoubleArray devs = new zExtDoubleArray();
            //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_getPlanarityDeviationPerFace(ref this, ref devs, type, colorFaces, tolerance);
            planarityDevs = devs.getItems();
            return success;
        }
        /// <summary>
        /// Get the Gaussian curvature for a zExtMesh object.
        /// </summary>
        /// <param name="gaussianCurvature"> out array to store Gaussian curvature data  </param>
        /// <returns> True if the method was run successfully</returns>
        public zStatusCode getGaussianCurvature(out double[] gaussianCurvature) {
            zExtDoubleArray devs = new zExtDoubleArray();
            //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_getGaussianCurvature(ref this, ref devs);
            gaussianCurvature = devs.getItems();
            return success;
        }

        /// <summary>
        /// Get the face colors of the mesh.
        /// </summary>
        /// <param name="colors"> Out array of face colors </param>
        /// <returns> True if the method was run successfully</returns>
        public zStatusCode getFaceColor(out System.Drawing.Color[] colors) {
            zExtColorArray extColors = new zExtColorArray();
            //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_getMeshColors(ref this, out extColors);
            colors = extColors.getItems();
            return success;
        }
        /// <summary>
        /// Smooths a zExtMesh object using Catmull-Clark subdivision.
        /// </summary>
        /// <param name="level"> The number of times to smoothen the mesh</param>
        /// <param name="fixedCorner"> True to keep the corner fixed</param>
        /// <returns> True if the method was run successfully</returns>
        public zStatusCode smoothMesh(int level, bool smoothCorner, in zExtIntArray fixedVerts = new zExtIntArray(), bool smoothFixedEdges = false) {
            //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_smoothMesh(ref this, level, smoothCorner, fixedVerts, smoothFixedEdges);
            return success;
        }

        public zStatusCode smoothMesh1D(int level, bool smoothCorner, bool flip, in zExtIntArray fixedVerts) {
            //zExtMesh mesh = this;
            var success = zNativeMethods.ext_mesh_smoothMesh1D(ref this, level, smoothCorner, flip, fixedVerts);
            return success;
        }

    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtMeshArray {
        private IntPtr pointer;
        private int arrayCount;

        public zExtMeshArray(zExtMesh[] meshes) {
            pointer = new IntPtr();
            arrayCount = 0;
            //setMeshes(ref meshes);
        }

        public zExtMesh[] getItems() {
            var items = new zExtMesh[arrayCount];
            zNativeMethods.ext_mesh_getMeshsFromMeshArray(ref this, items);
            return items;
        }
        //public void setMeshes(ref zExtMesh[] meshes) {
        //    zNativeMethods.ext_mesh_setMeshsFromArray(ref this, meshes, meshes.Length);
        //}
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtMeshPointerArray {
        private IntPtr pointer;
        private int arrayCount;

        public zExtMeshPointerArray(zExtMesh[] meshes) {
            pointer = new IntPtr();
            arrayCount = 0;
            //setMeshes(ref meshes);
        }

        public zExtMesh[] getItems() {
            var items = new zExtMesh[arrayCount];
            zNativeMethods.ext_mesh_getMeshsFromMeshPointerArray(ref this, items);
            return items;
        }
        public void setMeshes(ref zExtMesh[] meshes) {
            //zNativeMethods.ext_mesh_setMeshsFromPointerArray(ref this, meshes, meshes.Length);
        }
    }


    static partial class zNativeMethods {
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_mesh_createFromRawArrays(double[] _vertexPositions, int[] _polyCounts, int[] _polyConnects, int numVerts, int numFaces, ref zExtMesh out_mesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_duplicate(in zExtMesh inMesh, out zExtMesh outMesh);



        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getVertexPositionsRaw(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVPostions,
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVColors);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshFaceCounts(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfCounts);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshFaceConnect(zExtMesh objMesh,
            [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfConnects);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_from([MarshalAs(UnmanagedType.LPStr)] string filePath, ref zExtMesh outMesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_to(ref zExtMesh extMesh, [MarshalAs(UnmanagedType.LPStr)] string filePath);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_fromJSON(ref zExtJSON json, ref zExtMesh outMesh);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_toJSON(ref zExtMesh extGraph, ref zExtJSON json);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_fromUSD(ref zExtUSD usd, ref zExtMesh outMesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_toUSD(ref zExtMesh extMesh, ref zExtUSD usd);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshFaceCounts(ref zExtMesh objMesh, [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfCounts);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getVertexPositionsRaw(ref zExtMesh objMesh,
           [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVPostions,
           [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outVColors);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshFaceConnect(ref zExtMesh objMesh,
                      [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outfConnects);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshCentre(ref zExtMesh objMesh,
                                 [MarshalAs(UnmanagedType.LPArray), In, Out] float[] outCentre);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshsFromMeshArray(ref zExtMeshArray inArray, [MarshalAs(UnmanagedType.LPArray), In, Out] zExtMesh[] outMeshes);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshsFromMeshPointerArray(ref zExtMeshPointerArray inArray, [MarshalAs(UnmanagedType.LPArray), In, Out] zExtMesh[] outMeshes);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getVertexPositions(ref zExtMesh objMesh, out zExtPointArray extPointArray);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshColors(ref zExtMesh objMesh, out zExtColorArray extPointArray);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getMeshPolygonDate(ref zExtMesh objMesh, out zExtIntArray pCount, out zExtIntArray pConnect);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_smoothMesh(ref zExtMesh objMesh, int level, [MarshalAs(UnmanagedType.Bool)] bool smoothCorner, in zExtIntArray fixedVerts, [MarshalAs(UnmanagedType.Bool)] bool smoothFixedEdges);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_smoothMesh1D(ref zExtMesh objMesh, int level, [MarshalAs(UnmanagedType.Bool)] bool smoothCorner, [MarshalAs(UnmanagedType.Bool)] bool flip, in zExtIntArray fixedVerts);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getPlanarityDeviationPerFace(ref zExtMesh objMesh, ref zExtDoubleArray outPlanarityDevs, int type, [MarshalAs(UnmanagedType.Bool)] bool colorFaces, double tolerance);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getGaussianCurvature(ref zExtMesh objMesh, ref zExtDoubleArray outGaussianCurvature);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_checkPlanarity(ref zExtMesh objMesh, float tolerance, int planarityType, [MarshalAs(UnmanagedType.Bool)] bool colorFaces, ref zExtDoubleArray outDeviations);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_getFaceColor(ref zExtMesh objMesh, ref zExtColorArray extPointArray);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.AsAny)]
        public static extern zExtPoint ext_mesh_meshTest(int num);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_mesh_meshTest2(ref zStatus2 s);

    }

    #region External methods for array
    static partial class zNativeMethods {
        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern zStatusCode ext_mesh_getVertexPositions(ref zExtMesh objMesh, out zExtPointArray pointArray);

        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern zStatusCode ext_mesh_getMeshColors(ref zExtMesh objMesh, out zExtColorArray colorArray);

        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern zStatusCode ext_mesh_getMeshPolygonDate(ref zExtMesh objMesh, out zExtIntArray pCount, out zExtIntArray pConnect);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_createFromArrays(in zExtPointArray _vertexPositions, in zExtIntArray _polyCounts, in zExtIntArray _polyConnects, ref zExtMesh out_mesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_mesh_setMeshVertexColors(ref zExtMesh objMesh, in zExtColorArray colorArray);

        //[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        //internal static extern zStatusCode ext_mesh_checkPlanarity(ref zExtMesh objMesh, float tolerance, int planarityType,
        //    [MarshalAs(UnmanagedType.Bool)] bool colorFaces, 
        //    ref zExtDoubleArray outDeviations);



    }
    #endregion
}