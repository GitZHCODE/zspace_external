using System.IO;
using System.Reflection;
using System.Collections.Generic;

using Rhino.Runtime.InProcess;
using Rhino.Geometry;
using Rhino.Display;
using Eto;
using Eto.Forms;
using Eto.Drawing;
using Rhino.FileIO;
using System.Runtime.InteropServices;

using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Linq;

using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Data;
using Grasshopper.Kernel.Types;

namespace zSpace {
    public static class zSpaceRhinoDataTreeUtil {
        public static DataTree<T> Cast<T>(List<List<T>> a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Count; i++) {
                d.AddRange(a[i], new GH_Path(i));
            }
            return d;
        }

        public static DataTree<T> Cast<T>(List<T[]> a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Count; i++) {
                d.AddRange(a[i], new GH_Path(i));
            }
            return d;
        }

        public static DataTree<T> Cast<T>(List<T>[] a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Length; i++) {
                for (int j = 0; j < a[i].Count; j++) {
                    var args = new int[2];
                    args[0] = i; args[1] = j;
                    d.Add(a[i][j], new GH_Path(args));
                }
            }
            return d;
        }

        public static DataTree<T> Cast<T>(T[][] a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Length; i++) {
                d.AddRange(a[i], new GH_Path(i));
            }
            return d;
        }

        public static DataTree<T> Cast<T>(T[] a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Length; i++) {
                d.Add(a[i], new GH_Path(i));
            }
            return d;
        }
        public static DataTree<T> Cast<T>(List<T> a) {
            var d = new DataTree<T>();
            for (int i = 0; i < a.Count; i++) {
                d.Add(a[i], new GH_Path(i));
            }
            return d;
        }

        public static T[][] CastTo2D<T>(DataTree<T> a) {
            var d = new T[a.BranchCount][];
            for (int i = 0; i < d.Length; i++) {
                d[i] = a.Branch(i).ToArray();
            }
            return d;
        }
    }
}
