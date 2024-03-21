using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;
using Rhino.Geometry;
using static zSpace.zExtRhinoUtil;


//write me in c# external zExtGraph defined in c++ zExtGraph.h

namespace zSpace {
    [StructLayout(LayoutKind.Sequential)]
    public struct zExtGraph {
        private IntPtr _ptr;
        private int vCount;
        private int eCount;
        private zExtPointArray vPositions;
        private zExtColorArray vColors;
        private zExtIntArray ePair;
        private zExtColorArray eColors;

        /// <summary>
        /// Initializes a new instance of the zExtGraph class with vertex positions, vertex colors, edge pairs, and edge colors.
        /// </summary>
        /// <param name="vPositions">An array of vertex positions.</param>
        /// <param name="vColors">An array of vertex colors.</param>
        /// <param name="ePairs">An array of edge pairs.</param>
        /// <param name="eColors">An array of edge colors.</param>
        public zExtGraph(zExtPoint[] vPositions, Color[] vColors, int[] ePairs, Color[] eColors) {
            _ptr = new IntPtr();
            this.vCount = vPositions.Length;
            this.eCount = ePairs.Length;
            this.vPositions = new zExtPointArray(vPositions);
            this.vColors = new zExtColorArray(vColors);
            this.ePair = new zExtIntArray(ePairs);
            this.eColors = new zExtColorArray(eColors);
            zNativeMethods.ext_graph_updateGraph(ref this);
        }

        /// <summary>
        /// Initializes a new instance of the zExtGraph class with vertex positions and edge pairs.
        /// </summary>
        /// <param name="vPositions">An array of vertex positions.</param>
        /// <param name="ePairs">An array of edge pairs.</param>
        /// 
        public zExtGraph(zExtPoint[] vPositions, int[] ePairs, Color[] eColors = null) {
            _ptr = new IntPtr();
            this.vCount = vPositions.Length;
            this.eCount = ePairs.Length;
            this.vPositions = new zExtPointArray(vPositions);
            this.ePair = new zExtIntArray(ePairs);
            //this.eColors = eColors==null? new zExtColorArray(): new zExtColorArray(eColors);
            Console.WriteLine(string.Format("\n \n zExtGraphcolors is null {0} \n \n", eColors == null));
            this.eColors = eColors==null? new zExtColorArray(): new zExtColorArray(eColors);

            this.vColors = new zExtColorArray();
            //Console.WriteLine(string.Format("\n \n zExtGraph before ext_graph_updateGraph to {0} {1} \n \n", vPositions.Length, this.eColors.getItems()[0]));
            zNativeMethods.ext_graph_updateGraph(ref this);
        }

        ///// <summary>
        ///// Initializes a new instance of the zExtGraph class with vertex positions and edge pairs.
        ///// </summary>
        ///// <param name="vPositions">An array of vertex positions.</param>
        ///// <param name="ePairs">An array of edge pairs.</param>
        //public zExtGraph(zExtPoint[] vPositions, int[] ePairs) {
        //    _ptr = new IntPtr();
        //    this.vCount = vPositions.Length;
        //    this.eCount = ePairs.Length;
        //    this.vPositions = new zExtPointArray(vPositions);
        //    this.vColors = new zExtColorArray();
        //    this.ePair = new zExtIntArray(ePairs);
        //    this.eColors = new zExtColorArray();
        //    zNativeMethods.ext_graph_updateGraph(ref this);
        //}

        /// <summary>
        /// Initializes a new instance of the zExtGraph class with vertex positions and edge pairs.
        /// </summary>
        /// <param name="vPositions">An array of vertex positions.</param>
        /// <param name="ePairs">An instance of zExtIntArray representing edge pairs.</param>
        public zExtGraph(zExtPoint[] vPositions, zExtIntArray ePairs) {
            _ptr = new IntPtr();
            this.vCount = vPositions.Length;
            this.eCount = ePairs.getArrayCount();
            this.vPositions = new zExtPointArray(vPositions);
            this.vColors = new zExtColorArray();
            this.ePair = ePairs;
            this.eColors = new zExtColorArray();
            zNativeMethods.ext_graph_updateGraph(ref this);
        }

        public zExtGraph(zExtPoint[] vPositions, int[] ePairs) {
            _ptr = new IntPtr();
            this.vCount = vPositions.Length;
            this.eCount = ePairs.Length;
            this.vPositions = new zExtPointArray(vPositions);
            this.vColors = new zExtColorArray();
            this.ePair = new zExtIntArray(ePairs);

            this.eColors = new zExtColorArray();
            zNativeMethods.ext_graph_updateGraph(ref this);
        }

        /// <summary>
        /// Initializes a new instance of the zExtGraph class from a file specified by its path.
        /// </summary>
        /// <param name="path">The path of the file to be read.</param>
        public zExtGraph(string path) {
            this._ptr = new IntPtr();
            this.vCount = 0;
            this.eCount = 0;
            this.vPositions = new zExtPointArray();
            this.vColors = new zExtColorArray();
            this.ePair = new zExtIntArray();
            this.eColors = new zExtColorArray();
            zNativeMethods.ext_graph_from(path, ref this);
        }



#if RHINO_CSHARP
        public zExtGraph(Line[] lines, System.Drawing.Color[] eColors = null) {
            this._ptr = new IntPtr();
            this.vCount = 0;
            this.eCount = 0;
            this.vPositions = new zExtPointArray();
            this.vColors = new zExtColorArray();
            this.ePair = new zExtIntArray();
            this.eColors = new zExtColorArray();
            try {

                List<Point3d> vrts = new List<Point3d>();
                var edges = new int[lines.Length * 2];
                double tolerance = 0.0000001;
                for (int i = 0; i < lines.Length; i++) {
                    Point3d start = lines[i].From;
                    Point3d end = lines[i].To;
                    int startId = -1; int endId = -1;


                    for (int j = 0; j < vrts.Count; j++) {

                        Point3d p1 = vrts[j];
                        Point3d p2 = start;
                        bool chk = Math.Abs(p1.X - p2.X) < tolerance && Math.Abs(p1.Y - p2.Y) < tolerance && Math.Abs(p1.Z - p2.Z) < tolerance;

                        if (chk) {
                            startId = j;
                            break;
                        }
                    }
                    if (startId == -1) {
                        vrts.Add(start);
                        startId = vrts.Count - 1;
                    }

                    for (int k = 0; k < vrts.Count; k++) {
                        Point3d p1 = vrts[k];
                        Point3d p2 = end;
                        bool chk = Math.Abs(p1.X - p2.X) < tolerance && Math.Abs(p1.Y - p2.Y) < tolerance && Math.Abs(p1.Z - p2.Z) < tolerance;

                        if (chk) {
                            endId = k;
                            break;
                        }
                    }
                    if (endId == -1) {
                        vrts.Add(end);
                        endId = vrts.Count - 1;
                    }
                    edges[i * 2] = startId;
                    edges[i * 2 + 1] = endId;
                }
                Console.WriteLine(string.Format("\n zExtGraph to {0} {1}", vrts.Count, edges.Length));
                var extPts = PointUtil.toExtPoint(vrts.ToArray());
                //var extEdges = new zExtIntArray();
                //extEdges.setItems(edges);
                this = new zExtGraph(extPts, edges, eColors);
                //zNativeMethods.ext_graph_updateGraph(ref this);
            }
            catch (Exception) {
                Console.WriteLine("\n zExtGraph to exception");
                //throw;
            }

        }
#endif

        /// <summary>
        /// Creates a duplicate of the current mesh .
        /// </summary>
        /// <returns>The duplicated mesh.</returns>
        public zExtGraph duplicate() {
            zExtGraph outObject;
            zNativeMethods.ext_graph_duplicate(in this, out outObject);
            return outObject;
        }


        /// <summary>
        /// Gets the count of vertices in the graph.
        /// </summary>
        /// <returns>The count of vertices in the graph.</returns>
        public int getVertexCount() {
            return vCount;
        }
        
        /// <summary>
        /// Gets the count of edges in the graph.
        /// </summary>
        /// <returns>The count of edges in the graph.</returns>
        public int getEdgeCount() {
            return eCount;
        }

        /// <summary>
        /// Gets an array of vertex positions in the graph.
        /// </summary>
        /// <returns>An array of vertex positions.</returns>
        public zExtPointArray getVertexPositions() {
            return vPositions;
        }

        /// <summary>
        /// Gets an array of vertex colors in the graph.
        /// </summary>
        /// <returns>An array of vertex colors.</returns>
        public Color[] getVertexColors() {
            return vColors.getItems();
        }

        /// <summary>
        /// Gets an array of edge pairs in the graph.
        /// </summary>
        /// <returns>An array of edge pairs.</returns>
        public int[] getEdgePairs() {
            return ePair.getItems();
        }

        /// <summary>
        /// Gets an array of edge colors in the graph.
        /// </summary>
        /// <returns>An array of edge colors.</returns>
        public Color[] getEdgeColors() {
            return eColors.getItems();
        }

        /// <summary>
        /// Sets the graph data for the ExtGraph object.
        /// </summary>
        /// <param name="vPositions">An array of vertex positions.</param>
        /// <param name="vColors">An array of vertex colors.</param>
        /// <param name="ePairs">An array of edge pairs.</param>
        /// <param name="eColors">An array of edge colors.</param>
        public void setGraphData(zExtPoint[] vPositions, Color[] vColors, int[] ePairs, Color[] eColors) {
            this.vCount = vPositions.Length;
            this.eCount = ePairs.Length;
            this.vPositions = new zExtPointArray(vPositions);
            this.vColors = new zExtColorArray(vColors);
            this.ePair = new zExtIntArray(ePairs);
            this.eColors = new zExtColorArray(eColors);
            zNativeMethods.ext_graph_updateGraph(ref this);
        }
      
        public bool to(string path) {
            return zNativeMethods.ext_graph_to(ref this, path) == 1;
        }
        public bool from(string path) {
            return zNativeMethods.ext_graph_from(path, ref this) == 1;
        }
        private bool from(ref zExtJSON json) {
            return zNativeMethods.ext_graph_fromJSON(ref json, ref this) == 1;
        }
        private bool to(ref zExtJSON json) {
            return zNativeMethods.ext_graph_toJSON(ref this, ref json) == 1;
        }

#if RHINO_CSHARP

        //private class Point3dEqualityComparer : IEqualityComparer<Point3d> {
        //    public bool Equals(Point3d p1, Point3d p2) {
        //        return p1.X == p2.X && p1.Y == p2.Y && p1.Z == p2.Z;
        //    }

        //    public int GetHashCode(Point3d p) {
        //        unchecked {
        //            int hash = 17;
        //            hash = hash * 23 + p.X.GetHashCode();
        //            hash = hash * 23 + p.Y.GetHashCode();
        //            hash = hash * 23 + p.Z.GetHashCode();
        //            return hash;
        //        }
        //    }
        //}

        //// Your existing method
        //private bool toxx(Line[] lines) {
        //    try {
        //        List<Point3d> vrts = new List<Point3d>();
        //        var edges = new int[lines.Length * 2];

        //        for (int i = 0; i < lines.Length; i++) {
        //            Point3d start = lines[i].From;
        //            Point3d end = lines[i].To;
        //            int startId, endId;

        //            if (!vrts.Any(p => p.Equals(start))) {
        //                vrts.Add(start);
        //                startId = vrts.Count - 1;
        //            }
        //            else {
        //                startId = vrts.FindIndex(p => p.Equals(start));
        //            }

        //            if (!vrts.Any(p => p.Equals(end))) {
        //                vrts.Add(end);
        //                endId = vrts.Count - 1;
        //            }
        //            else {
        //                endId = vrts.FindIndex(p => p.Equals(end));
        //            }

        //            edges[i * 2] = startId;
        //            edges[i * 2 + 1] = endId;
        //        }

        //        var extPts = PointUtil.toExtPoint(vrts.ToArray());
        //        this = new zExtGraph(extPts, edges);
        //        return true;
        //    }
        //    catch (Exception) {
        //        return false;
        //        //throw;
        //    }
        //}



        public bool from(Line[] lines, System.Drawing.Color[] eColors = null) {
            try {

                List<Point3d> vrts = new List<Point3d>();
                var edges = new int[lines.Length * 2];
                double tolerance = 0.0000001;
                for (int i = 0; i < lines.Length; i++) {
                    Point3d start = lines[i].From;
                    Point3d end = lines[i].To;
                    int startId = -1; int endId = -1;


                    for (int j = 0; j < vrts.Count; j++) {

                        Point3d p1 = vrts[j];
                        Point3d p2 = start;
                        bool chk = Math.Abs(p1.X - p2.X) < tolerance && Math.Abs(p1.Y - p2.Y) < tolerance && Math.Abs(p1.Z - p2.Z) < tolerance;

                        if (chk) {
                            startId = j;
                            break;
                        }
                    }
                    if (startId == -1) {
                        vrts.Add(start);
                        startId = vrts.Count - 1;
                    }

                    for (int k = 0; k < vrts.Count; k++) {
                        Point3d p1 = vrts[k];
                        Point3d p2 = end;
                        bool chk = Math.Abs(p1.X - p2.X) < tolerance && Math.Abs(p1.Y - p2.Y) < tolerance && Math.Abs(p1.Z - p2.Z) < tolerance;

                        if (chk) {
                            endId = k;
                            break;
                        }
                    }
                    if (endId == -1) {
                        vrts.Add(end);
                        endId = vrts.Count - 1;
                    }
                }
                Console.WriteLine(string.Format("\n zExtGraph to {0} {1}", vrts.Count, edges.Length));
                var extPts = PointUtil.toExtPoint(vrts.ToArray());
                //var extEdges = new zExtIntArray();
                //extEdges.setItems(edges);
                this = new zExtGraph(extPts, edges, eColors);
                return true;
            }
            catch (Exception) {
                return false;
                //throw;
            }
            
        }
        //private bool tox(Line[] lines) {
        //    try {

        //        List<Point3d> vrts = new List<Point3d>();
        //        var edges = new int[lines.Length * 2];

        //        for (int i = 0; i < lines.Length; i++) {
        //            Point3d start = lines[i].From;
        //            Point3d end = lines[i].To;
        //            int startId, endId;
        //            if (!vrts.Contains(start)) {
                        
        //                vrts.Add(start);
        //                startId = vrts.Count - 1;
        //            }
        //            else { 
        //                startId = vrts.FindIndex(x => x == start);
        //            }  
        //            if (!vrts.Contains(end)) {
        //                vrts.Add(end);
        //                endId = vrts.Count - 1;
        //            }
        //            else {
        //                endId = vrts.FindIndex(x => x == end);
        //            }

        //            edges[i * 2] = startId;
        //            edges[i * 2 + 1] = endId;
        //        }
        //        //    var pts = new Point3d[lines.Length * 2];
        //        //var edges = new int[lines.Length * 2];
        //        //for (int i = 0; i < lines.Length; i++) {
        //        //    pts[i * 2] = lines[i].From;
        //        //    pts[i * 2 + 1] = lines[i].To;
        //        //    edges[i * 2] = i * 2;
        //        //    edges[i * 2 + 1] = i * 2 + 1;
        //        //}
        //        var extPts = PointUtil.toExtPoint(vrts.ToArray());
        //        //var extEdges = new zExtIntArray();
        //        //extEdges.setItems(edges);
        //        this = new zExtGraph(extPts, edges);
        //        return true;
        //    }
        //    catch (Exception) {
        //        return false;
        //        throw;
        //    }
            
        //}


#endif
    }



    [StructLayout(LayoutKind.Sequential)]
    public struct zExtGraphPointerArray {
        IntPtr _ptr;
        int arrayCount;

        public zExtGraphPointerArray(zExtGraph[] input) {
            _ptr = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public zExtGraph[] getItems() {
            var output = new zExtGraph[arrayCount];
            zNativeMethods.ext_graph_getGraphsFromGraphPointerArray(this, output);

            return output;
        }
        public int getCount() {
            return arrayCount;
        }

        public void setItems(zExtGraph[] input) {
            arrayCount = input.Length;
            //zNativeMethods.ext_graph_setItemsInArray(ref this, input);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtGraphArray {
        IntPtr _ptr;
        int arrayCount;

        public zExtGraphArray(zExtGraph[] input) {
            _ptr = new IntPtr();
            arrayCount = 0;
            setItems(input);
        }

        public zExtGraph[] getItems() {
            var output = new zExtGraph[arrayCount];
            //zNativeMethods.ext_graph_getGraphsFromGraphArray(this, output);

            return output;
        }
        public int getCount() {
            return arrayCount;
        }

        public void setItems(zExtGraph[] input) {
            arrayCount = input.Length;
            //zNativeMethods.ext_graph_setItemsInArray(ref this, input);
        }
    }

    static partial class zNativeMethods {
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_graph_from([MarshalAs(UnmanagedType.LPStr)] string path, ref zExtGraph graph);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_graph_to(ref zExtGraph graph, [MarshalAs(UnmanagedType.LPStr)] string path);

        //ZSPACE_EXTERNAL int ext_graph_fromJSON(zExtJSON& json, zExtGraph& outGraph);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_graph_fromJSON(ref zExtJSON json, ref zExtGraph outGraph);

        //ZSPACE_EXTERNAL int ext_graph_toJSON(zExtGraph& graph, zExtJSON& outJSON);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_graph_toJSON(ref zExtGraph graph, ref zExtJSON outJSON);


        //ZSPACE_EXTERNAL void ext_graph_getGraphData(zExtGraph extGraph, float* vPositions, float* vColors, int* ePairs, float* eColors);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_graph_getGraphData(zExtGraph extGraph, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] vPositions, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] vColors, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] int[] ePairs, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] float[] eColors);


        //ZSPACE_EXTERNAL void ext_graph_getGraphSequence(zExtGraph extGraph, int* outSequence);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_graph_getGraphSequence(zExtGraph extGraph, [MarshalAs(UnmanagedType.LPArray), In, Out] int[] outSequence);

        //		ZSPACE_EXTERNAL void ext_graph_getGraphsFromGraphPointerArray(zExtGraphPointerArray graphSet, zExtGraph* outGraphArray);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_graph_getGraphsFromGraphPointerArray(zExtGraphPointerArray graphSet, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtGraph[] outGraphArray);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ext_graph_getGraphsFromGraphArray(zExtGraphArray graphSet, 
            [MarshalAs(UnmanagedType.LPArray), In, Out] zExtGraph[] outGraphArray);

        //ZSPACE_EXTERNAL int ext_graph_updateGraph(zExtGraph& extGraph);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int ext_graph_updateGraph(ref zExtGraph extGraph);


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        internal static extern zStatusCode ext_graph_duplicate(in zExtGraph inMesh, out zExtGraph outMesh);


    }

}
