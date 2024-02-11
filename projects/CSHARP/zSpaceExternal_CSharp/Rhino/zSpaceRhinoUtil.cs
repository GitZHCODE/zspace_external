using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Rhino;
using Rhino.Geometry;
using System.Threading;
using Grasshopper;
using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Types;
using Rhino.Geometry.Intersect;
using System.Drawing;

namespace zSpace {
    public static class zSpaceRhinoUtil {





        ///// <summary>
        ///// Creates a Rhino Mesh object from a zSpace external mesh object.
        ///// </summary>
        ///// <param name="extMesh">The zSpace external mesh object.</param>
        ///// <returns>A Rhino Mesh object.</returns>
        //private static Mesh createRhinoMeshFromExtMeshXXX(zExtMesh extMesh) {
        //    Mesh mesh = new Mesh();
        //    mesh.Vertices.Clear();
        //    //Console.WriteLine("extMesh " + extMesh.getVCount());

        //    mesh.Vertices.AddVertices(createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D()));
        //    mesh.VertexColors.Clear();
        //    mesh.VertexColors.AppendColors(extMesh.getMeshColors());
        //    foreach (var fn in extMesh.getMeshFaceConnection()) {
        //        MeshFace meshFace;
        //        if (fn.Count == 3) meshFace = new MeshFace(fn[0], fn[1], fn[2]);
        //        else //(fn.Count == 4) 
        //            meshFace = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
        //        //Write the method to create an ngon if it was more than 4
        //        //else meshFace = new MeshFace(pConnects[count], pConnects[count + 1], pConnects[count + 2], pConnects[count + 3]);
        //        mesh.Faces.AddFace(meshFace);
        //    }
        //    //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());
        //    mesh.RebuildNormals();
        //    //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());

        //    return mesh;
        //}

        public static Mesh createRhinoMeshFromExtMesh(zExtMesh extMesh) {
            Mesh mesh = new Mesh();
            mesh.Vertices.Clear();
            //Console.WriteLine("extMesh " + extMesh.getVCount());

            var extPts = extMesh.getMeshPoints();
            var pts = new Point3f[extPts.Length];
            for (int i = 0; i < pts.Length; i++) {
                pts[i] = getRhinoPointFromExtPoint(extPts[i]);
            }
            mesh.Vertices.AddVertices(pts);

            var faceConnect = extMesh.getFaces();
            foreach (var fn in faceConnect) {
                //foreach (var iii in fn) {
                //    //Console.WriteLine(iii);

                //}

                MeshFace face;
                if (fn.Count == 3) face = new MeshFace(fn[0], fn[1], fn[2]);
                else face = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                Console.WriteLine(face.ToString());
                mesh.Faces.AddFace(face);
            }

            //mesh.Vertices.AddVertices(createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D()));
            mesh.VertexColors.Clear();
            mesh.VertexColors.AppendColors(extMesh.getMeshColors());
            //foreach (var fn in extMesh.getMeshFaceConnection()) {
            //    MeshFace meshFace;
            //    if (fn.Count == 3) meshFace = new MeshFace(fn[0], fn[1], fn[2]);
            //    else //(fn.Count == 4) 
            //        meshFace = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
            //    //Write the method to create an ngon if it was more than 4
            //    //else meshFace = new MeshFace(pConnects[count], pConnects[count + 1], pConnects[count + 2], pConnects[count + 3]);
            //    mesh.Faces.AddFace(meshFace);
            //}
            //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());
            mesh.RebuildNormals();
            //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());

            return mesh;
        }

        ///// <summary>
        ///// Updates the position of a Rhino Mesh object from a zSpace external mesh object. 
        ///// </summary>
        ///// <param name="extMesh">The zSpace external mesh object.</param>
        ///// <param name="mesh">The Rhino Mesh object to update.</param>
        //public static void updateRhinoMeshPosFromExtMesh(zExtMesh extMesh, ref Mesh mesh) {
        //    //Check if both have the same vCount, otherwise, create new
        //    if (extMesh.getVCount() == mesh.Vertices.Count) {
        //        var v = createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D());
        //        var c = extMesh.getMeshColors();
        //        for (int i = 0; i < mesh.Vertices.Count; i++) {
        //            mesh.Vertices[i] = v[i];
        //            mesh.VertexColors[i] = c[i];
        //        }
        //    }
        //    else {
        //        var m = createRhinoMeshFromExtMesh(extMesh);
        //        mesh.Vertices.Clear();
        //        mesh.VertexColors.Clear();
        //        mesh.Vertices.AddVertices(m.Vertices);
        //        mesh.VertexColors.AppendColors(m.VertexColors.ToArray());
        //        mesh.Faces.AddFaces(m.Faces);
        //        mesh.RebuildNormals();

        //    }
        //}

        /// <summary>
        /// Creates a zSpace external mesh object from a Rhino Mesh object.
        /// </summary>
        /// <param name="rhinoMesh">The Rhino Mesh object.</param>
        /// <returns>A zSpace external mesh object.</returns>
        public static zExtMesh createExtMeshFromRhinoMesh(Mesh rhinoMesh) {
            zExtMesh extMesh = new zExtMesh();
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
            //for (int i = 0; i < rhinoMesh.Faces.Count; i++) {
            //    counter += rhinoMesh.Faces[i].IsQuad ? 4 : 3;// : rhinoMesh.GetNgonAndFacesEnumerable().ToList()[i].
            //}
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
            //Console.WriteLine("\n colors" + colors.Length);
            //for (int i = 0; i < colors.Length; i++) {
            //    Console.WriteLine("\n colors1 " + colors[i]);

            //}
            extMesh.createMesh(in extpts, in countArray, in connectArray, ref colors);



            return extMesh;
        }

        /// <summary>
        /// Creates Rhino Point3f objects from a 1D float array.
        /// </summary>
        /// <param name="values">The 1D float array containing the values.</param>
        /// <returns>An array of Rhino Point3f objects.</returns>
        public static Point3f[] createRhinoPointFrom1DFloat(float[] values) {
            int count = (int)values.Length / 3;
            Console.WriteLine("count " + values.Length);
            Console.WriteLine("count " + values.Length / 3);
            Console.WriteLine("count " + count);

            Point3f[] pts = new Point3f[count];
            for (int i = 0; i < count; i++) {
                pts[i] = new Point3f(values[i * 3 + 0], values[i * 3 + 1], values[i * 3 + 2]);
            }
            return pts;
        }


        public static Point3f getRhinoPointFromExtPoint(zExtPoint pt) {
            return new Point3f(pt.x, pt.y, pt.z);
        }


        public static double roundToFactor(double value, double factor) {
            return Math.Round(value / factor) * factor;
        }



    }

    public static class zExtRhinoUtil {
        public static class MeshUtil {
            public static Mesh toRhinoMesh(zExtMesh extMesh) {
                Mesh mesh = new Mesh();
                mesh.Vertices.Clear();
                //Console.WriteLine("extMesh " + extMesh.getVCount());

                var extPts = extMesh.getMeshPoints();
                var pts = new Point3d[extPts.Length];
                for (int i = 0; i < pts.Length; i++) {
                    pts[i] = PointUtil.toRhinoPoint(extPts[i]);
                }
                mesh.Vertices.AddVertices(pts);

                var faceConnect = extMesh.getFaces();
                foreach (var fn in faceConnect) {
                    //foreach (var iii in fn) {
                    //    //Console.WriteLine(iii);

                    //}

                    MeshFace face;
                    if (fn.Count == 3) face = new MeshFace(fn[0], fn[1], fn[2]);
                    else face = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                    //Console.WriteLine(face.ToString());
                    mesh.Faces.AddFace(face);
                }

                //mesh.Vertices.AddVertices(createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D()));
                mesh.VertexColors.Clear();
                var colors = extMesh.getMeshColors();
                if (colors.Length == mesh.Vertices.Count) {
                    mesh.VertexColors.AppendColors(colors);

                }
                
                mesh.RebuildNormals();

                return mesh;
            }
            public static zExtMesh toExtMesh(Mesh rhinoMesh) {
                zExtMesh extMesh = new zExtMesh();
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
                //for (int i = 0; i < rhinoMesh.Faces.Count; i++) {
                //    counter += rhinoMesh.Faces[i].IsQuad ? 4 : 3;// : rhinoMesh.GetNgonAndFacesEnumerable().ToList()[i].
                //}
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
                //Console.WriteLine("\n colors" + colors.Length);
                //for (int i = 0; i < colors.Length; i++) {
                //    Console.WriteLine("\n colors1 " + colors[i]);

                //}
                extMesh.createMesh(in extpts, in countArray, in connectArray, ref colors);



                return extMesh;
            }
        }
        public static class PointUtil {
            public static Point3d toRhinoPoint(zExtPoint pt) {
                return new Point3d(pt.x, pt.y, pt.z);
            }
            public static Point3d[] toRhinoPoint(zExtPoint[] points) {
                var pts = new Point3d[points.Length];
                for (int i = 0; i < points.Length; i++) {
                    pts[i] = new Point3d(points[i].x, points[i].y, points[i].z);
                }
                return pts;
            }
            public static Point3d[] toRhinoPoint(zExtPointArray pointsArray) {
                return toRhinoPoint(pointsArray.getItems());
            }
            public static zExtPoint[] toExtPoint(Point3d[] points) {
                var pts = new zExtPoint[points.Length];
                for (int i = 0; i < points.Length; i++) {
                    pts[i] = new zExtPoint((float)points[i].X, (float)points[i].Y, (float)points[i].Z);
                }
                return pts;
            }

            public static Vector3d toRhinoVector(zExtPoint pt) {
                return new Vector3d(pt.x, pt.y, pt.z);
            }
            public static zExtPoint toExtPoint(Point3d pt) {
                return new zExtPoint((float)pt.X, (float)pt.Y, (float)pt.Z);
            }
            public static zExtPoint toExtPoint(Point3f pt) {
                return new zExtPoint(pt.X, pt.Y, pt.Z);
            }
            public static zExtPoint toExtPoint(Vector3d pt) {
                return new zExtPoint((float)pt.X, (float)pt.Y, (float)pt.Z);
            }
            public static zExtPoint toExtPoint(Vector3f pt) {
                return new zExtPoint(pt.X, pt.Y, pt.Z);
            }

        }
        public static class TransformUtil {
            public static Plane toRhinoPlane(zExtTransform transform) {
                Vector3d x = new Vector3d(transform.row0[0], transform.row0[1], transform.row0[2]);
                Vector3d y = new Vector3d(transform.row1[0], transform.row1[1], transform.row1[2]);
                Vector3d n = new Vector3d(transform.row2[0], transform.row2[1], transform.row2[2]);
                Point3d o = new Point3d(transform.row3[0], transform.row3[1], transform.row3[2]);
                return new Plane(o, x, y);
            }
            public static zExtTransform toExtTransform(Plane plane) {
                zExtTransform transform = new zExtTransform();
                transform.initPointer();
                transform.row0[0] = (float)plane.XAxis.X;
                transform.row0[1] = (float)plane.XAxis.Y;
                transform.row0[2] = (float)plane.XAxis.Z;

                transform.row1[0] = (float)plane.YAxis.X;
                transform.row1[1] = (float)plane.YAxis.Y;
                transform.row1[2] = (float)plane.YAxis.Z;

                transform.row2[0] = (float)plane.ZAxis.X;
                transform.row2[1] = (float)plane.ZAxis.Y;
                transform.row2[2] = (float)plane.ZAxis.Z;

                transform.row3[0] = (float)plane.Origin.X;
                transform.row3[1] = (float)plane.Origin.Y;
                transform.row3[2] = (float)plane.Origin.Z;
                return transform;
            }
        }
        public static class GraphUtil {
            public static Line[] toRhinoLines(zExtGraph graph) {
                var lines = new Line[graph.getEdgeCount()];
                Console.WriteLine("\n lines " + lines.Length);
                var pts = PointUtil.toRhinoPoint( graph.getVertexPositions().getItems());
                var edges = graph.getEdgePairs();
                for (int i = 0; i < lines.Length; i++) {
                    lines[i] = new Line(pts[edges[i * 2]], pts[edges[i * 2 + 1]]);
                    //Console.WriteLine("\n pt0 " + (pts[edges[i * 2]]).X + ", " + (pts[edges[i * 2 + 1]]).X);

                }
                return lines;
            }
            
                 
            //public static zExtGraph toExtGraph(Line[] lines) {
            //    var pts = new Point3d[lines.Length * 2];
            //    var edges = new int[lines.Length * 2];
            //    for (int i = 0; i < lines.Length; i++) {
            //        pts[i * 2] = lines[i].From;
            //        pts[i * 2 + 1] = lines[i].To;
            //        edges[i * 2] = i * 2;
            //        edges[i * 2 + 1] = i * 2 + 1;
            //    }
            //    var extPts = PointUtil.toExtPoint(pts);
            //    //var extEdges = new zExtIntArray();
            //    //extEdges.setItems(edges);
            //    zExtGraph graph = new zExtGraph(extPts, edges);
            //    return graph;
            //}
            public static zExtGraph toExtGraph(Line[] lines, Color[] edgeColors = null) {
                //var pts = new Point3d[lines.Length * 2];
                //var edges = new int[lines.Length * 2];
                //for (int i = 0; i < lines.Length; i++) {
                //    pts[i * 2] = lines[i].From;
                //    pts[i * 2 + 1] = lines[i].To;
                //    edges[i * 2] = i * 2;
                //    edges[i * 2 + 1] = i * 2 + 1;
                //}
                //var extPts = PointUtil.toExtPoint(pts);
                ////var extEdges = new zExtIntArray();
                ////extEdges.setItems(edges);
                zExtGraph graph;
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
                    Console.WriteLine(string.Format("\n c# zExtGraph to {0} {1}", vrts.Count, edges.Length));
                    var extPts = PointUtil.toExtPoint(vrts.ToArray());

                    Console.WriteLine(string.Format("\n c# zExtGraph to {0} {1}", vrts.Count, extPts.Length));

                    //var extEdges = new zExtIntArray();
                    //extEdges.setItems(edges);
                    return new zExtGraph(extPts, edges, edgeColors);
                }
                catch (Exception) {
                    return new zExtGraph();
                    //throw;
                }


                //if (edgeColors.Length == lines.Length) {
                //     graph = new zExtGraph(lines, edgeColors);
                //    return graph;
                //}
                //else {
                //     graph = new zExtGraph(lines);
                //    return graph;
                //}
                return graph;
            }

            public static zExtGraph toExtGraph2(Line[] lines, Color[] edgeColors = null) {

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
                Console.WriteLine(string.Format("\n c# zExtGraph to {0} {1}", vrts.Count, edges.Length));
                var extPts = PointUtil.toExtPoint(vrts.ToArray());

                Console.WriteLine(string.Format("\n c# zExtGraph to {0} {1}", vrts.Count, extPts.Length));


                return new zExtGraph(extPts, edges);

            }


            public static zExtGraph toExtGraph(Polyline polyline) {
                int size = polyline.Count;
                if (polyline.IsClosed) {
                    size--;
                }
                var pts = new Point3d[size];
                var edges = new int[size * 2]; //<<
                for (int i = 0; i < size; i++) {
                    pts[i] = polyline[i];

                    edges[i * 2] = i;

                    if (i == size-1 && polyline.IsClosed) {
                        edges[i * 2 + 1] = 0;

                    }
                    else {
                        edges[i * 2 + 1] = i + 1;
                    }

                    Console.WriteLine("\n edges " + edges[i * 2] + ", " + edges[i * 2 + 1]);
                }
                var extPts = PointUtil.toExtPoint(pts);
               
                var graph = new zExtGraph(extPts, edges);
                return graph;
            }
        }
    }

   
}
