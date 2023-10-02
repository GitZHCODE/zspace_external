using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using Rhino;
using Rhino.Geometry;
using System.Collections;

namespace zSpace {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("C# sandbox");

            //string dir = Environment.CurrentDirectory;
            string dir = System.Runtime.InteropServices.RuntimeEnvironment.GetRuntimeDirectory();
            
            //Console.WriteLine(string.Format("current Dir {0}", dir));

            //Environment.SetEnvironmentVariable("ovDir", "C:/Users/heba.eiz/AppData/Local/ov/pkg/connectsample-203.0.0/_build/windows-x86_64/release/");
            string path = null;


            Console.WriteLine("GetEnvironmentVariables: ");
            foreach (DictionaryEntry de in Environment.GetEnvironmentVariables())
                Console.WriteLine("  {0} = {1}", de.Key, de.Value);

            //string usdFolderPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/ov";
            string usdFolderPath = "ov";
            SetDllDirectory(usdFolderPath);

            //string zSpaceFolderPath = "C:/Users/heba.eiz/source/repos/GitZHCODE/zspace_external/projects/CSHARP/zSpaceExternal_CSharpSandbox/zSpaceExternal_CSharpSandbox/bin/Release/zspace";
            //SetDllDirectory(zSpaceFolderPath);


            //zExtJSON j1 = new zExtJSON();
            //j1.CreateJson();
            //j1.ReadJsonFile(path);

            testMesh1();
            //testWriteJsonToJson();


            Console.WriteLine("\n Press any key to exit...");
            Console.ReadKey();
        }

        //string usdDir1 = "C:/Users/heba.eiz/AppData/Local/ov/pkg/connectsample-203.0.0/_build/windows-x86_64/release/PYTHON310.DLL";

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool SetDllDirectory(string lpPathName);


        static void test1() {
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

        static void test2() {
            string writePath = "C:\\Users\\heba.eiz\\Desktop\\JSON_Temp\\testExport.json";
            zExtJSON j1 = new zExtJSON();
            j1.CreateJson();

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
            j1.CreateJson();
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

            Console.WriteLine("\n  newMesh count = " +  newmesh.getVCount());

            zExtJSON j2 = new zExtJSON();
            j2.CreateJson();
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
            string writePath = "C:\\Users\\heba.eiz\\Desktop\\JSON_Temp\\testExport.json";
            zExtJSON mainJson = new zExtJSON();
            mainJson.CreateJson();

            zExtJSON[] jsons = new zExtJSON[3];
            for (int i = 0; i < jsons.Length; i++) {
                test5(out jsons[i], i);

                mainJson.WriteJSONAttribute(string.Format("testValue {0}", i), jsons[i]);
                Console.WriteLine("json written");
            }

            
            

            //Export Json
            mainJson.ExportJsonFile(writePath);







        }


        static void test5(out zExtJSON j1, int addValue) {
            string writePath = "C:\\Users\\heba.eiz\\Desktop\\JSON_Temp\\testExport.json";
            j1 = new zExtJSON();
            j1.CreateJson();

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
            zExtPoint[] pts = new zExtPoint[4];
            pts[0] = new zExtPoint(0, 0, 0);
            pts[1] = new zExtPoint(0, 1, 0);
            pts[2] = new zExtPoint(1, 1, 0);
            pts[3] = new zExtPoint(1, 0, 1);

            zExtPointArray ptarray = new zExtPointArray(pts);

            zExtIntArray counts = new zExtIntArray();
            counts.setItems(new int[] { 4 });

            zExtIntArray connects = new zExtIntArray();
            connects.setItems(new int[] { 0, 1, 2, 3 });

            zExtMesh newmesh = new zExtMesh();
            newmesh.createMesh(ptarray, counts, connects);

            Console.WriteLine("\n  newMesh count = " + newmesh.getVCount());

            double[] devs;
            newmesh.checkPlanrityPerFace(0.01f, 0, false, out devs);

            foreach (var item in devs) {
                Console.WriteLine(item);
            }




        }

    }
}
