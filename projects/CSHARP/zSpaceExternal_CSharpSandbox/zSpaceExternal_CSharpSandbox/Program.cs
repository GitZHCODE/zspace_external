using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using Rhino;
using Rhino.Geometry;

namespace zSpace {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("C# sandbox");




            test2();

            Console.WriteLine("\n Press any key to exit...");
            Console.ReadKey();
        }

        static void test1() {
            string path = "//zaha-hadid.com/Data/Projects/1453_CODE/1453___research/res_heba/0-Projects/Striatus/Blocks/2023-02-23/200_Final/deck_3.json";


            zExtJSON j1 = new zExtJSON();
            j1.CreateJson();
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

            int[] ints = new int[5];
            for (int i = 0; i < pts.Length; i++) {
                ints[i] = i;
            }
            j1.WriteJSONAttribute("Tests", ints);

            int degree = 3;
            j1.WriteJSONAttribute("Degree", degree);

            bool periodic = true;
            j1.WriteJSONAttribute("Periodic", periodic);

            //Export Json
            j1.ExportJsonFile(writePath);

            


            printJsonDate(j1, true);



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
    
    }
}
