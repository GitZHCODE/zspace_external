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
            Console.WriteLine("sandbox");

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
            var keys = j1.attributesNames.getItems();
            var types = j1.attributesTypes.getItems();
            for (int i = 0; i < keys.Length; i++) {
                ////    Console.WriteLine("\n");
                    Console.WriteLine("\n Key | Type: " + keys[i] + " | " + types[i]);
                ////    Console.WriteLine("Type: " + types[i]);
            }
                float[][] floatArray;
            var floatCHK = j1.ReadJSONAttribute2("LeftPlanes", out floatArray);
            Console.WriteLine("\n floatchk " + floatCHK + "\n");
            foreach (var item in floatArray) {
                Console.Write(item + ", ");
            }

            ////int rhVCount = rhinoMesh.Vertices.ToList().Count;
            ////Console.WriteLine("\n \n Rhino Mesh count: " + rhVCount);

            //try {
            //    //bool meshChck = j1.GetMesh(ref mesh);
            //}
            //catch (Exception ex) {
            //    //Console.WriteLine("\n \n Exception caught0: \n " + ex.Message);
            //    //Console.WriteLine("\n \n Exception caught1: \n " + ex.ToString());
            //    //Console.WriteLine("\n \n Exception caught3: \n " + ex.GetBaseException());
            //    //Console.WriteLine("\n \n Exception caught4: \n " + ex.Source);
            //    Console.WriteLine("\n \n Exception caught5: \n " + ex.StackTrace); //best
            //    //Console.WriteLine("\n \n Exception caught6: \n " + ex.TargetSite);
            //}


            //Console.WriteLine("Mesh vertices: " + mesh.getVCount());
            //Console.WriteLine("Mesh face: " + mesh.getFaceCount());


            //////var k = new string[j.attributesNames.getArrayCount()];
            ////var keys = j.attributesNames.getItems();
            ////var types = j.attributesTypes.getItems();

            //////var types = j.attributesTypes.getItems();
            ////for (int i = 0; i < keys.Length; i++) {
            ////    Console.WriteLine("\n");
            ////    Console.WriteLine("\n Key: " + keys[i]);
            ////    Console.WriteLine("Type: " + types[i]);
            ////    Type t = j.getType(types[i]);
            ////    Console.WriteLine(t == null);

            ////    Console.WriteLine(t.Name);
            ////    dynamic item;
            ////    j.ReadJSONAttribute4(keys[i], t, out item);
            ////    Console.WriteLine("");

            ////    if (t.Name != "String") {
            ////        //if (t.Name.Contains("[]")) {
            ////        //    foreach (var dynamic in item) {
            ////        //        if (t.Name.Contains("[][]")) {
            ////        //            Console.WriteLine("");

            ////        //            foreach (var x in dynamic) {
            ////        //                Console.Write(x);
            ////        //                Console.Write(" , ");
            ////        //            }
            ////        //        }
            ////        //        else {
            ////        //            Console.Write(dynamic);
            ////        //            Console.Write(" , ");
            ////        //        }

            ////        //    }
            ////        //}
            ////        //else {
            ////        //    Console.WriteLine(item);
            ////        //}
            ////        Console.WriteLine(item);
            ////    }
            ////}

            

            //bool chk = j1.WriteJSONAttribute<string>("json1", "tempValueJson_1");
            //Console.WriteLine("\n succsess write j1?: " + chk);

            //var j2 = j1.copy();

            //bool chk2 = j2.WriteJSONAttribute<string>("json2", "tempValueJson_2");
            //Console.WriteLine("\n succsess write j2?: " + chk);

            //var keys1 = j1.attributesNames.getItems();
            //var types1 = j1.attributesTypes.getItems();

            ////var types = j.attributesTypes.getItems();
            //for (int i = 0; i < keys1.Length; i++) {
            //    Console.WriteLine("\n");
            //    Console.WriteLine("\n JSON _ 1 Key: " + keys1[i]);
            //    Console.WriteLine(" JSON _ 1 Type: " + types1[i]);
            //    Type t = j1.getType(types1[i]);
            //    //Console.WriteLine(t == null);

            //    //Console.WriteLine(t.Name);
            //    dynamic item;
            //    j1.ReadJSONAttribute4(keys1[i], t, out item);
            //    Console.WriteLine("");

            //    if (t.Name != "String") {
            //        //Console.WriteLine(item);
            //    }
            //    else {
            //        string s;
            //        j1.ReadJSONAttribute<string>(keys1[i], out s);
            //        Console.WriteLine(s);
            //    }
            //}
            //var keys2 = j2.attributesNames.getItems();
            //var types2 = j2.attributesTypes.getItems();
            ////var types = j.attributesTypes.getItems();
            //for (int i = 0; i < keys2.Length; i++) {
            //    Console.WriteLine("\n");
            //    Console.WriteLine("\n JSON _ 2 Key: " + keys2[i]);
            //    Console.WriteLine(" JSON _ 2 Type: " + types2[i]);
            //    Type t = j2.getType(types2[i]);
            //    //Console.WriteLine(t == null);

            //    //Console.WriteLine(t.Name);
            //    dynamic item;
            //    j2.ReadJSONAttribute4(keys2[i], t, out item);
            //    //Console.WriteLine("");

            //    if (t.Name != "String") {
            //        //Console.WriteLine(item);
            //    }
            //    else {
            //        string s;
            //        bool c = j2.ReadJSONAttribute<string>(keys2[i], out s);
            //        Console.WriteLine(c);

            //        Console.WriteLine(s);
            //    }
            //}

            //////var newk = j.attributesNames.getItems();
            ////////var types = j.attributesTypes.getItems();
            //////for (int i = 0; i < newk.Length; i++) {
            //////    Console.WriteLine("\n newKey: " + newk[i]);
            //////}






            Console.WriteLine("\n Press any key to exit...");
            Console.ReadKey();
        }
    }
}
