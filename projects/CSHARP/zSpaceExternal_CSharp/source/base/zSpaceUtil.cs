using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zSpace{
    public static class zSpaceUtil {
        public static double Remap(float val, float inStart, float inEnd, float outStart, float outEnd) {
            return (val - inStart) / (inEnd - inStart) * (outEnd - outStart) + outStart;
        }
        public static T[][] Convert1DtoArray2D<T>(T[] array, int stride) { //Updated to manage error handling
            int length = array.Length;
            int resultRows = length / stride;
            int resultCols = stride;
            T[][] result = new T[resultRows][];
            for (int i = 0; i < resultRows; i++) {
                result[i] = new T[resultCols];
                for (int j = 0; j < resultCols; j++) {
                    result[i][j] = array[(i * stride) + j];
                }
            }
            return result;
        }

        public static List<T> matchList<T>(List<T> list, int targetSize) {
            if (list.Count == targetSize) {
                return list;
            }
            List<T> result = new List<T>();

            for (int i = 0; i < targetSize; i++) {
                result.Add(i < list.Count? list[i] : list[list.Count - 1]);
                //if (i < list.Count) {
                //    resutlt.Add(list[i]);
                //}
                //else {
                //    resutlt.Add(list[list.Count - 1]);
                //}
            }
            return result;
        }
        public static T[] matchList<T>(T[] list, int targetSize) {
            if (list.Length == targetSize) {
                return list;
            }
            var result = new T[targetSize];
            for (int i = 0; i < targetSize; i++) {
                result[i] = i < list.Length ? list[i] : list[list.Length - 1];
            }
            return result;
        }



    }
}
