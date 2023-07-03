using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Rhino;
using Rhino.Geometry;


namespace zSpace
{
    public static class zSpaceRhinoUtil
    {
        /// <summary>
        /// Creates a Rhino Mesh object from a zSpace external mesh object.
        /// </summary>
        /// <param name="extMesh">The zSpace external mesh object.</param>
        /// <returns>A Rhino Mesh object.</returns>
        private static Mesh createRhinoMeshFromExtMeshXXX(zExtMesh extMesh) {
            Mesh mesh = new Mesh();
            mesh.Vertices.Clear();
            //Console.WriteLine("extMesh " + extMesh.getVCount());

            mesh.Vertices.AddVertices(createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D()));
            mesh.VertexColors.Clear();
            mesh.VertexColors.AppendColors(extMesh.getMeshColors());
            foreach (var fn in extMesh.getMeshFaceConnection()) {
                MeshFace meshFace;
                if (fn.Count == 3) meshFace = new MeshFace(fn[0], fn[1], fn[2]);
                else //(fn.Count == 4) 
                    meshFace = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                //Write the method to create an ngon if it was more than 4
                //else meshFace = new MeshFace(pConnects[count], pConnects[count + 1], pConnects[count + 2], pConnects[count + 3]);
                mesh.Faces.AddFace(meshFace);
            }
            //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());
            mesh.RebuildNormals();
            //Console.WriteLine("rhinomesh " + mesh.Vertices.Count());

            return mesh;
        }

        public static Mesh createRhinoMeshFromExtMesh(zExtMesh extMesh) {
            Mesh mesh = new Mesh();
            mesh.Vertices.Clear();
            Console.WriteLine("extMesh " + extMesh.getVCount());

            var extPts = extMesh.getMeshPoints();
            var pts = new Point3f[extPts.Length];
            for (int i = 0; i < pts.Length; i++) {
                pts[i] = getRhinoPointFromExtPoint(extPts[i]);
            }
            mesh.Vertices.AddVertices(pts);

            var faceConnect = extMesh.getFaces();
            foreach (var fn in faceConnect) {
                foreach (var iii in fn) {
                    //Console.WriteLine(iii);

                }

                MeshFace face;
                if (fn.Count == 3) face = new MeshFace(fn[0], fn[1], fn[2]);
                else face = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
                Console.WriteLine(face.ToString());
                mesh.Faces.AddFace(face);
            }

            //mesh.Vertices.AddVertices(createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D()));
            //mesh.VertexColors.Clear();
            //mesh.VertexColors.AppendColors(extMesh.getMeshColors());
            //foreach (var fn in extMesh.getMeshFaceConnection()) {
            //    MeshFace meshFace;
            //    if (fn.Count == 3) meshFace = new MeshFace(fn[0], fn[1], fn[2]);
            //    else //(fn.Count == 4) 
            //        meshFace = new MeshFace(fn[0], fn[1], fn[2], fn[3]);
            //    //Write the method to create an ngon if it was more than 4
            //    //else meshFace = new MeshFace(pConnects[count], pConnects[count + 1], pConnects[count + 2], pConnects[count + 3]);
            //    mesh.Faces.AddFace(meshFace);
            //}
            Console.WriteLine("rhinomesh " + mesh.Vertices.Count());
            mesh.RebuildNormals();
            Console.WriteLine("rhinomesh " + mesh.Vertices.Count());

            return mesh;
        }

        /// <summary>
        /// Updates the position of a Rhino Mesh object from a zSpace external mesh object. 
        /// </summary>
        /// <param name="extMesh">The zSpace external mesh object.</param>
        /// <param name="mesh">The Rhino Mesh object to update.</param>
        public static void updateRhinoMeshPosFromExtMesh(zExtMesh extMesh, ref Mesh mesh) {
            //Check if both have the same vCount, otherwise, create new
            if (extMesh.getVCount() == mesh.Vertices.Count) {
                var v = createRhinoPointFrom1DFloat(extMesh.getMeshPositions1D());
                var c = extMesh.getMeshColors();
                for (int i = 0; i < mesh.Vertices.Count; i++) {
                    mesh.Vertices[i] = v[i];
                    mesh.VertexColors[i] = c[i];
                }
            }
            else {
                var m = createRhinoMeshFromExtMesh(extMesh);
                mesh.Vertices.Clear();
                mesh.VertexColors.Clear();
                mesh.Vertices.AddVertices(m.Vertices);
                mesh.VertexColors.AppendColors(m.VertexColors.ToArray());
                mesh.Faces.AddFaces(m.Faces);
                mesh.RebuildNormals();

            }
        }
        
        /// <summary>
        /// Creates a zSpace external mesh object from a Rhino Mesh object.
        /// </summary>
        /// <param name="rhinoMesh">The Rhino Mesh object.</param>
        /// <returns>A zSpace external mesh object.</returns>
        public static zExtMesh createExtMeshFromRhinoMesh(Mesh rhinoMesh) {
            return new zExtMesh();
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

    }
}
