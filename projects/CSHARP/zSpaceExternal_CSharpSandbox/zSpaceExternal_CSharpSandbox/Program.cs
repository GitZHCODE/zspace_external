using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using Rhino;
using Rhino.Geometry;
using System.Collections;
using System.Drawing;
using System.Collections.Specialized;
using Grasshopper.Kernel.Geometry;
using Rhino.Runtime;

namespace zSpace {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("C# sandbox");

            testEnv();

            testJSON();


            Console.WriteLine("\n Press any key to exit...");
            Console.ReadKey();
        }

        //string usdDir1 = "C:/Users/heba.eiz/AppData/Local/ov/pkg/connectsample-203.0.0/_build/windows-x86_64/release/PYTHON310.DLL";

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool SetDllDirectory(string lpPathName);


        static void test1MeshJSON() {
            string path = "//zaha-hadid.com/Data/Projects/1453_CODE/1453___research/res_heba/0-Projects/Striatus/Blocks/2023-02-23/200_Final/deck_3.json";


            zExtJSON j1 = new zExtJSON();
            //j1.CreateJson();
            j1.ReadJsonFile(path);
            zExtMesh mesh = new zExtMesh();
            //bool meshChck2 = j1.GetMesh(ref mesh);
            try {
                bool meshChck2 = zExtJSON.GetMesh(path, ref mesh);

            }
            catch (Exception) {
                Console.WriteLine("\n \n ERROR ");
                throw;
            }

            // Mesh rhinoMesh = zSpaceRhinoUtil.createRhinoMeshFromExtMesh(mesh);
            //var keys = j1.attributesNames.getItems();
            //var types = j1.attributesTypes.getItems();
            
            var keys = j1.AttributeKeys;
            var types = j1.AttributeTypes;
            for (int i = 0; i < keys.Length; i++) {
                ////    Console.WriteLine("\n");
                Console.WriteLine("\n Key | Type: " + keys[i] + " | " + types[i]);
                Type t = j1.getType(types[i]);
                //Console.WriteLine(t == null);

                Console.WriteLine(t.Name);
                dynamic item;
                j1.ReadJSONAttribute(keys[i], t, out item);
                ////    Console.WriteLine("Type: " + types[i]);
            }
            float[][] floatArray;
            var floatCHK = j1.ReadJSONAttribute("LeftPlanes", out floatArray);
            Console.WriteLine("\n floatchk " + floatCHK + "\n");
            foreach (var item in floatArray) {
                Console.Write(item + ", ");
            }

            float[][] pts = new float[5][];
            for (int i = 0; i < pts.Length; i++) {
                pts[i] = new float[3];
                pts[i][0] = i / 1.0f;
                pts[i][1] = i / 2.0f;
                pts[i][2] = 0f;
            }

            j1.WriteJSONAttribute("ControlPoints", pts);


            printJsonDate(j1);

        }
        static void smoothMesh() {
            string path = "//zaha-hadid.com/Data/Projects/4071_NatPower/4071_Production/user_sketch/HE/1-Rhino/WORKFLOW/JSON/testForSmooth.obj";
            var mesh = new zExtMesh();
            mesh.from(path);

            //zExtIntArray fixedv = new zExtIntArray(new int[] {11, 10, 17, 16, 2 , 5, 8, 0,3,6});
            //zExtIntArray fixedv = new zExtIntArray(new int[] {11, 10, 17, 16, 2 , 5, 8});
            zExtIntArray fixedv = new zExtIntArray(new int[] {8, 22, 5, 14, 2, 17, 23, 9, 10, 25});
            // bool smoothChk = mesh.smoothMesh(1, true, fixedv);
            //bool smoothChk = mesh.smoothMesh(1, true);
            //Console.WriteLine("\n 2_ mesh.smooth " + smoothChk + " _ " + mesh.getVCount());
            var smoothChk = mesh.smoothMesh(1, false, fixedv, false);

            mesh.to("//zaha-hadid.com/Data/Projects/4071_NatPower/4071_Production/user_sketch/HE/1-Rhino/WORKFLOW/JSON/testForSmooth_out.obj");
            //Rhino.Geometry.Mesh mesh1 = new Rhino.Geometry.Mesh();
            mesh.toTest();

            //zFnMesh fnresult = zFnMesh(resultObj);
            ////fnresult.from(path, zJSON);
            //fnresult.from(path, zOBJ);
            //fnresult.subdivide(1);
        }
        static void test2() {
            string writePath = "C:\\Users\\heba.eiz\\Desktop\\JSON_Temp\\testExport.json";
            zExtJSON j1 = new zExtJSON();
            j1.createJson();

            //Write json Attributes
            float[][] pts = new float[5][];
            for (int i = 0; i < pts.Length; i++) {
                pts[i] = new float[3];
                pts[i][0] = i / 1.0f;
                pts[i][1] = i / 2.0f;
                pts[i][2] = 0f;
            }
            j1.WriteJSONAttribute("ControlPoints", pts);

            string[] texts = new string[5];
            for (int i = 0; i < pts.Length; i++) {
                texts[i] = string.Format("testValue {0}", i);
            }
            j1.WriteJSONAttribute("TestongStringArray", texts);

            int degree = 3;
            j1.WriteJSONAttribute("Degree", degree);

            bool periodic = true;
            j1.WriteJSONAttribute("Periodic", periodic);

            //Export Json
            j1.ExportJsonFile(writePath);

            


            printJsonDate(j1, true);



        }

        static void test3() {
            string path = "//zaha-hadid.com/Data/Projects/1453_CODE/1453___research/res_heba/0-Projects/Striatus/Blocks/2023-02-23/200_Final/deck_3.json";


            zExtJSON j1 = new zExtJSON();
            j1.createJson();
            j1.ReadJsonFile(path);
            zExtMesh mesh = new zExtMesh();
            try {
                bool meshChck2 = zExtJSON.GetMesh(path, ref mesh);

            }
            catch (Exception) {
                Console.WriteLine("\n \n ERROR ");
                throw;
            }
            zExtPoint[] pts = new zExtPoint[4];
            pts[0] = new zExtPoint(0, 0, 0);
            pts[1] = new zExtPoint(0, 1, 0);
            pts[2] = new zExtPoint(1, 1, 0);
            pts[3] = new zExtPoint(1, 0, 0);

            zExtPointArray ptarray = new zExtPointArray(pts);

            zExtIntArray counts = new zExtIntArray();
            counts.setItems(new int[] { 4 });

            zExtIntArray connects = new zExtIntArray();
            connects.setItems(new int[] { 0,1,2,3 });

            zExtMesh newmesh = new zExtMesh();
            newmesh.createMesh(ptarray, counts, connects);

            Console.WriteLine("\n  newMesh count = " +  newmesh.getVertexCount());

            zExtJSON j2 = new zExtJSON();
            j2.createJson();
            j2.SetMesh(newmesh);
            
            //Mesh rhinoMesh = zSpaceRhinoUtil.createRhinoMeshFromExtMesh(mesh);
            //var keys = j1.attributesNames.getItems();
            //var types = j1.attributesTypes.getItems();

            //var keys = j1.AttributeKeys;
            //var types = j1.AttributeTypes;
            //for (int i = 0; i < keys.Length; i++) {
            //    ////    Console.WriteLine("\n");
            //    Console.WriteLine("\n Key | Type: " + keys[i] + " | " + types[i]);
            //    Type t = j1.getType(types[i]);
            //    //Console.WriteLine(t == null);

            //    Console.WriteLine(t.Name);
            //    dynamic item;
            //    j1.ReadJSONAttribute(keys[i], t, out item);
            //    ////    Console.WriteLine("Type: " + types[i]);
            //}
            //float[][] floatArray;
            //var floatCHK = j1.ReadJSONAttribute("LeftPlanes", out floatArray);
            //Console.WriteLine("\n floatchk " + floatCHK + "\n");
            //foreach (var item in floatArray) {
            //    Console.Write(item + ", ");
            //}

            //float[][] pts = new float[5][];
            //for (int i = 0; i < pts.Length; i++) {
            //    pts[i] = new float[3];
            //    pts[i][0] = i / 1.0f;
            //    pts[i][1] = i / 2.0f;
            //    pts[i][2] = 0f;
            //}

            //j1.WriteJSONAttribute("ControlPoints", pts);


            printJsonDate(j2, true);

        }

        static void printJsonDate(zExtJSON j1, bool printValues = false) {
            var keys = j1.AttributeKeys;
            var types = j1.AttributeTypes;

            for (int i = 0; i < keys.Length; i++) {
                Console.WriteLine("\n\nAttribute_" + i + ":");
                Console.WriteLine("   Key: " + keys[i]);
                //Console.WriteLine(string.Format("   Key: {0}"), keys[i]);
                Console.WriteLine("   Type: " + types[i]);
                //Console.WriteLine(string.Format("   Type: {0}"), types[i]);
                Type t = j1.getType(types[i]);
                dynamic value;
                j1.ReadJSONAttribute(keys[i], t, out value);
                if (printValues) {
                    
                    Console.WriteLine("   Value: ");
                    Console.Write("       ");
                    try {
                        if (types[i].Contains("[]")) {
                            //Console.Write("       ");
                            foreach (var item in value) {
                                if (types[i].Contains("[][]")) {
                                    foreach (var item2 in item) {
                                        Console.Write(item2.ToString() + ",     ");
                                    }
                                }
                                else {
                                    Console.Write(item.ToString());
                                }
                                Console.Write("\n       ");

                            }
                        }
                        else {
                            Console.Write(value.ToString());
                        }
                    }
                    catch (Exception) {
                        Console.Write("ERROR IN PRINTING VALUE");
                    }

                }
                
            }
        }


        static void testWriteJsonToJson() {
            string writePath = "data/testExport.json";
            zExtJSON mainJson = new zExtJSON();
            mainJson.createJson();

            zExtJSON[] jsons = new zExtJSON[3];
            for (int i = 0; i < jsons.Length; i++) {
                test5(out jsons[i], i);

                string[] st = new string[] { "text1", "text2", "text3", "text4" };

                jsons[i].WriteJSONAttribute<string>("strinAdd", "stringValue");

                var stringArrayOutput = new zExtStringArray();
                stringArrayOutput.setItems(st);

                jsons[i].WriteJSONAttribute("listString", st);

                mainJson.WriteJSONAttribute(string.Format("testValue {0}", i), jsons[i]);
                Console.WriteLine("json written");
            }

            
            

            //Export Json
            mainJson.ExportJsonFile(writePath);







        }


        static void test5(out zExtJSON j1, int addValue) {
            string writePath = "C:\\Users\\heba.eiz\\Desktop\\JSON_Temp\\testExport.json";
            j1 = new zExtJSON();
            j1.createJson();

            //Write json Attributes
            float[][] pts = new float[5][];
            for (int i = 0; i < pts.Length; i++) {
                pts[i] = new float[3];
                pts[i][0] = i / 1.0f;
                pts[i][1] = i / 2.0f;
                pts[i][2] = 0f;
            }
            j1.WriteJSONAttribute("ControlPoints", pts);

            //string[] texts = new string[5];
            //for (int i = 0; i < pts.Length; i++) {
            //    texts[i] = string.Format("testValue {0}", i  +addValue);
            //}


            j1.WriteJSONAttribute("TestongString", string.Format("testValue {0}",  addValue));

            int degree = 3;
            j1.WriteJSONAttribute("Degree", degree);

            bool periodic = true;
            j1.WriteJSONAttribute("Periodic", periodic);

            //Export Json
            //j1.ExportJsonFile(writePath);




            //printJsonDate(j1, true);



        }

        static void testMesh1() {

            //string path = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_alice/ALICE_PLATFORM/x64/Release/EXE/data/cube-2.obj";
            //zExtMesh mesh = new zExtMesh();
            //bool s = mesh.from(path);
            //Console.WriteLine(string.Format("mesh read {0}", s));


            //zExtPoint[] pts = new zExtPoint[4];
            //pts[0] = new zExtPoint(0, 0, 0);
            //pts[1] = new zExtPoint(0, 1, 0);
            //pts[2] = new zExtPoint(1, 1, 0);
            //pts[3] = new zExtPoint(1, 0, 1);

            //zExtPointArray ptarray = new zExtPointArray(pts);

            //zExtIntArray counts = new zExtIntArray();
            //counts.setItems(new int[] { 4 });

            //zExtIntArray connects = new zExtIntArray();
            //connects.setItems(new int[] { 0, 1, 2, 3 });

            //zExtMesh newmesh = new zExtMesh();
            //newmesh.createMesh(ptarray, counts, connects);
            //newmesh.smoothMesh(2, true);

            ////Console.WriteLine("\n  newMesh count = " + newmesh.getVCount());

            //zExtIntArray fixedVerts = new zExtIntArray();
            //fixedVerts.setItems(new int[] { 0, 1 });
            //newmesh.smoothMesh1D(2, false, false, fixedVerts);

            // Console.WriteLine("\n  newMesh smooth count = " + newmesh.getVCount());

            string readPath = "data/cube.obj";
            var newmesh = new zExtMesh();
            newmesh.from(readPath);


            //export to USD
            string exportPath = "data/testMesh.usda";
            newmesh.to(exportPath);

            Console.WriteLine("\n  newMesh exported ");




            double[] devs;
            //newmesh.getPlanarityDeviationPerFace(0.01f, 0, false, out devs);

            //foreach (var item in devs) {
            //    Console.WriteLine(item);
            //}




        }

        static void testMeshUSD1() {

            //string readPath = "data/cube.obj";
            string readPath = "C:/Users/heba.eiz/Downloads/fdm_01.json";
            var mesh = new zExtMesh();
            var output1 = mesh.from(readPath);
            zExtPoint[] pts = mesh.getMeshPoints();
            //Console.WriteLine("\n 2_ mesh" + " _ " + output1);

            ////export to USD
            //string exportPath = "data/testMesh.usda";
            //mesh.to(exportPath);
            //Console.WriteLine("\n 1_ mesh exported usda ");

            //zExtUSD usd = new zExtUSD();
            //zStatus chk = mesh.to(ref usd);
            //Console.WriteLine("\n 1_ mesh.to(ref usd) ");
            //Console.WriteLine("\n 1_ chk0 = " + chk.ToString() + "\n");


            Console.WriteLine("\n 2_ mesh" + " _ " + mesh.getVertexCount());

            //zExtIntArray fixedv = new zExtIntArray(new int[] { });
            // bool smoothChk = mesh.smoothMesh(1, true, fixedv);
            //var smoothChk = mesh.smoothMesh(1, true);
           // Console.WriteLine("\n 2_ mesh.smooth " + smoothChk.ToString() + " _ " +mesh.getVCount());

            
            //zStatus2 sss = new zStatus2();
            //sss.statusCode = 15;
            //var stat2 = zNativeMethods.ext_mesh_meshTest2(ref sss);

            //var stat = zNativeMethods.ext_mesh_meshTest(2);

            //var mesh2 = new zExtMesh();
            //int chk1 = mesh2.from(ref usd);

            //Console.WriteLine("\n 2_ chk1 = " + chk1 + "\n");


            //string exportPath2 = "data/testMesh_2.usda";
            //int chk2= mesh2.to(exportPath2);
            //Console.WriteLine("\n 2_ chk2 = " + chk2 + "\n");

            //Console.WriteLine("\n 2_ mesh_2 exported usda ");




        }

        static void runOmniverse() {
            zExtOmniClient omniClient = new zExtOmniClient();
            string destinationPath = "omniverse://nucleus.zaha-hadid.com/Projects";
            int chk = omniClient.startOmniverse(destinationPath);
            Console.WriteLine("\n omni started = " + chk.ToString());
            
            chk = omniClient.startOmniverse(destinationPath);
            Console.WriteLine("\n omni started2 = " + chk.ToString());
            omniClient.shutdownOmniverse();
        }

        static void testJSONSDF() {
            string readPath = "//zaha-hadid.com/Data/Projects/1453_CODE/1453___research/res_heba/0-Projects/Striatus/Blocks/2023-01-11/200_Final/Export11-4/JSONWrite/Block_17-updatedManually.json";
            zExtJSON json = new zExtJSON();
            json.createJson();
            json.ReadJsonFile(readPath);
            var keys = json.AttributeKeys;
            var types = json.AttributeTypes;

            printJsonDate(json, false);
            


        }
    
        static void testEnv() {

            //string dir = Environment.CurrentDirectory;
            string dir = System.Runtime.InteropServices.RuntimeEnvironment.GetRuntimeDirectory();

            //Console.WriteLine(string.Format("current Dir {0}", dir));

            //Environment.SetEnvironmentVariable("ovDir", "C:/Users/heba.eiz/AppData/Local/ov/pkg/connectsample-203.0.0/_build/windows-x86_64/release/");
            string path = null;


            //Console.WriteLine("GetEnvironmentVariables: ");
            //foreach (DictionaryEntry de in Environment.GetEnvironmentVariables())
            //    Console.WriteLine("  {0} = {1}", de.Key, de.Value);

            SetDllDirectory("depends");


            string usdFolderPath = "lib_omniverse";
            //string usdFolderPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/lib_omniverse";
            SetDllDirectory(usdFolderPath);
        }

        static void testField() {
            zExtMeshScalarField field = new zExtMeshScalarField();
            zExtPoint minBB = new zExtPoint(-10, -10, 0);
            zExtPoint maxBB = new zExtPoint(10, 10, 0);
            int resX = 128;
            int resY = resX;

            Console.WriteLine("\n program 0");

            field.createField(minBB, maxBB, resX, resY, 1, true, false);


            Console.WriteLine("\n program 1");

            float[] circleScalars;
            field.getScalars_Circle(out circleScalars, new zExtPoint(0, 0, 0), 3.0f, 0.0, false);

            //Rhino.Geometry.Plane plane = new Rhino.Geometry.Plane(new Point3d(0, 0, 0), new Vector3d(0, 0, 1));
            //zExtTransform p = zExtRhinoUtil.TransformUtil.toExtTransform(plane);

            //Console.WriteLine("\n program 2");


            ////foreach (var i in circleScalars) {
            ////    Console.WriteLine(i);
            ////}
            ///



            field.setFieldValues(circleScalars);

            //Console.WriteLine("\n program 3");


            //zExtMesh extMesh;
            //field.getMesh(out extMesh);
            //zExtGraph graph;
            //field.getIsoContour(out graph, 0, 6, 0.000001f);

            //Console.WriteLine("\n program 4");
        }

        static void testGraph1() {
            zExtGraph g = new zExtGraph();
            string path = "C:/Users/heba.eiz/Downloads/extGraph.json";
            g.from(path);
            Console.WriteLine("\n graph imported");

            //add colors
            var vpos = g.getVertexPositions().getItems();
            var epair = g.getEdgePairs();

            Color[] ec = new Color[2];
            ec[0] = Color.Aqua;
            ec[1] = Color.Red;

            zExtColorArray eColors = new zExtColorArray(ec);
            zExtColorArray vColors = new zExtColorArray(ec);


            zExtGraph g2 = new zExtGraph(vpos, epair, ec, ec);

            var c0 = ec[0];
            var c = g2.getEdgeColors()[0];
            Console.WriteLine("\n color ___ " + c0.R + c0.G + c0.B);
            Console.WriteLine("\n color ___ " + c.R + c.G + c.B);




        }

        static void testJSON() {
            zExtJSON json = new zExtJSON();
            json.createJson();
            var input = new bool[] {true, true, false, false};
            string key = "test";
            json.WriteJSONAttribute(key, input);

            string path = "C:\\Users\\heba.eiz\\Downloads\\test2.json";
            //json.ExportJsonFile(path);
            json.ReadJsonFile(path);
            var types = json.AttributeTypes;
            int index = Array.IndexOf(json.AttributeKeys, key);
            Type t = json.getType(types[index]);

            Console.WriteLine("\n type " + t.ToString());

            bool[] output;
            json.ReadJSONAttribute(key, out output);
            
            foreach (var item in output) {
                Console.WriteLine("\n" + item);

            }

        }
        //static void testGraphJson() {
        //    zExtGraph g = new zExtGraph();
        //    string path2 = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_alice/ALICE_PLATFORM/x64/Release/EXE/data/NatPower/testing1/inputCenterMeshes/medialGraph/oMedialGraph.json";
        //    bool check1 = g.from(path2);
        //    Console.WriteLine(string.Format("\n c# graph count {0} {1}", check1, g.getVertexPositions().getCount()));
        //    Line[] lines = zExtRhinoUtil.GraphUtil.toRhinoLines(g);
        //    //zExtGraph g2 = new zExtGraph();
        //    Color[] colors = new Color[lines.Length];
        //    for (int i = 0; i < colors.Length; i++) {
        //        colors[i] = Color.Green;
        //    }
        //    zExtGraph g2 = zExtRhinoUtil.GraphUtil.toExtGraph(lines, colors);
        //    //zExtGraph g2 = new zExtGraph(lines, colors);
        //    Console.WriteLine(string.Format("\n c# graph2 count {0} {1}", g2.getVertexPositions().getCount(), g2.getEdgePairs().Length));

        //    Console.WriteLine(g2.getEdgePairs()[0]);

        //    string path3 = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_alice/ALICE_PLATFORM/x64/Release/EXE/data/NatPower/testing1/inputCenterMeshes/medialGraph/tempexternalCOut.json";

        //    g2.to(path3);

        //    zExtJSON j1 = new zExtJSON();
        //    var check = g.to(path3);
        //    Console.WriteLine("\n program 5" + check.ToString());

        //    zExtJSON j2 = new zExtJSON();
        //    j2.createJson();
        //    //j2.ReadJsonFile(path3);

        //    //g2.to(j2);

        //    check = j2.ExportJsonFile(path3);
        //    //Console.WriteLine("\n program 6" + check.ToString());


        //    //Mesh rhinoMesh = new Mesh();// = (zExtRhinoUtil.MeshUtil.toRhinoMesh(extMesh));

        //}

        

    }
}
