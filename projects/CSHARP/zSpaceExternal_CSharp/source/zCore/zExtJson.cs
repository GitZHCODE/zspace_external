using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {
    public struct zExtJSON {
        public IntPtr pointer;
        public int numOfAttributes;
         zExtStringArray attributesNames;
         zExtStringArray attributesTypes;

        

        //public zExtJSON() {
        //    // Constructor implementation
        //}

        // Other constructors, destructor, and methods

        //public void WriteAttribute<T>(string attributeKey, T inAttributeValue) {
        //    string attributeType = typeof(T).Name;
        //    switch (attributeType) {
        //        case "Int32":
        //            var v = (int)inAttributeValue;
        //            zNativeMethods.ext_json_writeJSONAttributeInt(ref this, attributeKey, inAttributeValue);
        //            break;
        //        case "Int32[]":
        //            zNativeMethods.ext_json_writeJSONAttributeIntArray(ref this, attributeKey,  inAttributeValue);
        //            break;
        //        case "Int32[,]":
        //            zNativeMethods.ext_json_writeJSONAttributeIntArray2D(ref this, attributeKey,  inAttributeValue);
        //            break;
        //        case "Single":
        //            zNativeMethods.ext_json_writeJSONAttributeFloat(ref this, attributeKey, ref inAttributeValue);
        //            break;
        //        case "Single[]":
        //            zNativeMethods.ext_json_writeJSONAttributeFloatArray(ref this, attributeKey, ref inAttributeValue);
        //            break;
        //        // Add cases for other types

        //        default:
        //            throw new NotSupportedException("Unsupported attribute type: " + attributeType);
        //    }
        //}

         bool ReadJSONAttribute2<T>(string attributeKey, out T outAttributeValue) {
            outAttributeValue = default(T);
            if (typeof(T) == typeof(int)) {
                int output;
                int success = zNativeMethods.ext_json_readJSONAttributeInt(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output;
                    return true;
                }
            }
            else if (typeof(T) == typeof(int[])) {
                var output = new zExtIntArray();
                int success = zNativeMethods.ext_json_readJSONAttributeIntArray(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(int[][])) {
                var output = new zExtIntArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeIntArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(float)) {
                float output;
                int success = zNativeMethods.ext_json_readJSONAttributeFloat(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output;
                    return true;
                }
            }
            else if (typeof(T) == typeof(float[])) {
                var output = new zExtFloatArray();
                //Console.WriteLine("trying to read");
                int success = zNativeMethods.ext_json_readJSONAttributeFloatArray(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(float[][])) {
                var output = new zExtFloatArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeFloatArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(double)) {
                double output;
                int success = zNativeMethods.ext_json_readJSONAttributeDouble(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output;
                    return true;
                }
            }
            else if (typeof(T) == typeof(double[])) {
                var output = new zExtDoubleArray();
                int success = zNativeMethods.ext_json_readJSONAttributeDoubleArray(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(double[][])) {
                var output = new zExtDoubleArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeDoubleArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(string)) {
                zExtString output;// = new zExtString();
                int success = zNativeMethods.ext_json_readJSONAttributeString(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getString();
                    return true;
                }
            }
            else if (typeof(T) == typeof(string[])) {
                zExtStringArray output;
                int success = zNativeMethods.ext_json_readJSONAttributeStringArray(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(string[][])) {
                zExtStringArray2D output;
                int success = zNativeMethods.ext_json_readJSONAttributeStringArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(bool)) {
                bool output;
                int success = zNativeMethods.ext_json_readJSONAttributeBool(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output;
                    return true;
                }
            }
            else if (typeof(T) == typeof(bool[])) {
                zExtBoolArray output;
                int success = zNativeMethods.ext_json_readJSONAttributeBoolArray(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            else if (typeof(T) == typeof(bool[][])) {
                zExtBoolArray2D output;
                int success = zNativeMethods.ext_json_readJSONAttributeBoolArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    outAttributeValue = (T)(object)output.getItems();
                    return true;
                }
            }
            return false;
        }
         T ReadJSONAttribute<T>(string attributeKey) {
            if (typeof(T) == typeof(int)) {
                int output;
                int success = zNativeMethods.ext_json_readJSONAttributeInt(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output;
                }
            }
            else if (typeof(T) == typeof(int[])) {
                var output = new zExtIntArray();
                int success = zNativeMethods.ext_json_readJSONAttributeIntArray(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(int[][])) {
                var output = new zExtIntArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeIntArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(float)) {
                float output;
                int success = zNativeMethods.ext_json_readJSONAttributeFloat(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output;
                    
                }
            }
            else if (typeof(T) == typeof(float[])) {
                var output = new zExtFloatArray();
                //Console.WriteLine("trying to read");
                int success = zNativeMethods.ext_json_readJSONAttributeFloatArray(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(float[][])) {
                var output = new zExtFloatArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeFloatArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(double)) {
                double output;
                int success = zNativeMethods.ext_json_readJSONAttributeDouble(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output;
                   
                }
            }
            else if (typeof(T) == typeof(double[])) {
                var output = new zExtDoubleArray();
                int success = zNativeMethods.ext_json_readJSONAttributeDoubleArray(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(double[][])) {
                var output = new zExtDoubleArray2D();
                int success = zNativeMethods.ext_json_readJSONAttributeDoubleArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(string)) {
                zExtString output;// = new zExtString();
                int success = zNativeMethods.ext_json_readJSONAttributeString(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getString();
                    
                }
            }
            else if (typeof(T) == typeof(string[])) {
                zExtStringArray output;
                int success = zNativeMethods.ext_json_readJSONAttributeStringArray(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(string[][])) {
                zExtStringArray2D output;
                int success = zNativeMethods.ext_json_readJSONAttributeStringArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(bool)) {
                bool output;
                int success = zNativeMethods.ext_json_readJSONAttributeBool(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output;
                    
                }
            }
            else if (typeof(T) == typeof(bool[])) {
                zExtBoolArray output;
                int success = zNativeMethods.ext_json_readJSONAttributeBoolArray(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            else if (typeof(T) == typeof(bool[][])) {
                zExtBoolArray2D output;
                int success = zNativeMethods.ext_json_readJSONAttributeBoolArray2D(ref this, attributeKey, out output);
                if (success == 1) {
                    return (T)(object)output.getItems();
                    
                }
            }
            return default(T);
        }

        public bool ReadJSONAttribute<T>(string attributeKey, out T outAttributeValue) {
            outAttributeValue = default(T);

            switch (typeof(T).Name) {
                case nameof(Int32):
                case nameof(Int64):
                    int intValue;
                    int intSuccess = zNativeMethods.ext_json_readJSONAttributeInt(ref this, attributeKey, out intValue);
                    if (intSuccess == 1) {
                        outAttributeValue = (T)(object)intValue;
                        return true;
                    }
                    break;
                case nameof(Int32) + "[]":
                case nameof(Int64) + "[]":
                    var intArrayOutput = new zExtIntArray();
                    int intArraySuccess = zNativeMethods.ext_json_readJSONAttributeIntArray(ref this, attributeKey, out intArrayOutput);
                    if (intArraySuccess == 1) {
                        outAttributeValue = (T)(object)intArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Int32) + "[][]":
                case nameof(Int64) + "[][]":
                    var intArray2DOutput = new zExtIntArray2D();
                    int intArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeIntArray2D(ref this, attributeKey, out intArray2DOutput);
                    if (intArray2DSuccess == 1) {
                        outAttributeValue = (T)(object)intArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Single):
                    float floatValue;
                    int floatSuccess = zNativeMethods.ext_json_readJSONAttributeFloat(ref this, attributeKey, out floatValue);
                    if (floatSuccess == 1) {
                        outAttributeValue = (T)(object)floatValue;
                        return true;
                    }
                    break;
                case nameof(Single) + "[]":
                    var floatArrayOutput = new zExtFloatArray();
                    int floatArraySuccess = zNativeMethods.ext_json_readJSONAttributeFloatArray(ref this, attributeKey, out floatArrayOutput);
                    if (floatArraySuccess == 1) {
                        outAttributeValue = (T)(object)floatArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Single) + "[][]":
                    var floatArray2DOutput = new zExtFloatArray2D();
                    int floatArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeFloatArray2D(ref this, attributeKey, out floatArray2DOutput);
                    if (floatArray2DSuccess == 1) {
                        Console.WriteLine(floatArray2DOutput.getArrayCount());
                        outAttributeValue = (T)(object)floatArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Double):
                    double doubleValue;
                    int doubleSuccess = zNativeMethods.ext_json_readJSONAttributeDouble(ref this, attributeKey, out doubleValue);
                    if (doubleSuccess == 1) {
                        outAttributeValue = (T)(object)doubleValue;
                        return true;
                    }
                    break;
                case nameof(Double) + "[]":
                    var doubleArrayOutput = new zExtDoubleArray();
                    int doubleArraySuccess = zNativeMethods.ext_json_readJSONAttributeDoubleArray(ref this, attributeKey, out doubleArrayOutput);
                    if (doubleArraySuccess == 1) {
                        outAttributeValue = (T)(object)doubleArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Double) + "[][]":
                    var doubleArray2DOutput = new zExtDoubleArray2D();
                    int doubleArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeDoubleArray2D(ref this, attributeKey, out doubleArray2DOutput);
                    if (doubleArray2DSuccess == 1) {
                        outAttributeValue = (T)(object)doubleArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(String):
                    zExtString stringValue;// = new zExtString() ;
                    int stringSuccess = zNativeMethods.ext_json_readJSONAttributeString(ref this, attributeKey, out stringValue);
                    //Console.WriteLine(stringSuccess);
                    if (stringSuccess == 1) {
                        outAttributeValue = (T)(object)stringValue.getString();
                        return true;
                    }
                    break;
                case nameof(String) + "[]":
                    zExtStringArray stringArrayOutput;
                    int stringArraySuccess = zNativeMethods.ext_json_readJSONAttributeStringArray(ref this, attributeKey, out stringArrayOutput);
                    if (stringArraySuccess == 1) {
                        outAttributeValue = (T)(object)stringArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(String) + "[][]":
                    zExtStringArray2D stringArray2DOutput;
                    int stringArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeStringArray2D(ref this, attributeKey, out stringArray2DOutput);
                    if (stringArray2DSuccess == 1) {
                        outAttributeValue = (T)(object)stringArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Boolean):
                    bool boolValue;
                    int boolSuccess = zNativeMethods.ext_json_readJSONAttributeBool(ref this, attributeKey, out boolValue);
                    if (boolSuccess == 1) {
                        outAttributeValue = (T)(object)boolValue;
                        return true;
                    }
                    break;
                case nameof(Boolean) + "[]":
                    zExtBoolArray boolArrayOutput;
                    int boolArraySuccess = zNativeMethods.ext_json_readJSONAttributeBoolArray(ref this, attributeKey, out boolArrayOutput);
                    if (boolArraySuccess == 1) {
                        outAttributeValue = (T)(object)boolArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Boolean) + "[][]":
                    zExtBoolArray2D boolArray2DOutput;
                    int boolArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeBoolArray2D(ref this, attributeKey, out boolArray2DOutput);
                    if (boolArray2DSuccess == 1) {
                        outAttributeValue = (T)(object)boolArray2DOutput.getItems();
                        return true;
                    }
                    break;
            }

            return false;
        }
        public bool ReadJSONAttribute(string attributeKey, Type type, out dynamic outAttributeValue) {
            switch (type.Name) {
                case nameof(Int32):
                case nameof(Int64):
                    int intValue;
                    int intSuccess = zNativeMethods.ext_json_readJSONAttributeInt(ref this, attributeKey, out intValue);
                    if (intSuccess == 1) {
                        outAttributeValue = intValue;
                        return true;
                    }
                    break;
                case nameof(Int32) + "[]":
                case nameof(Int64) + "[]":
                    var intArrayOutput = new zExtIntArray();
                    int intArraySuccess = zNativeMethods.ext_json_readJSONAttributeIntArray(ref this, attributeKey, out intArrayOutput);
                    if (intArraySuccess == 1) {
                        outAttributeValue = intArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Int32) + "[][]":
                case nameof(Int64) + "[][]":
                    var intArray2DOutput = new zExtIntArray2D();
                    int intArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeIntArray2D(ref this, attributeKey, out intArray2DOutput);
                    if (intArray2DSuccess == 1) {
                        outAttributeValue = intArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Single):
                    float floatValue;
                    int floatSuccess = zNativeMethods.ext_json_readJSONAttributeFloat(ref this, attributeKey, out floatValue);
                    if (floatSuccess == 1) {
                        outAttributeValue = floatValue;
                        return true;
                    }
                    break;
                case nameof(Single) + "[]":
                    var floatArrayOutput = new zExtFloatArray();
                    int floatArraySuccess = zNativeMethods.ext_json_readJSONAttributeFloatArray(ref this, attributeKey, out floatArrayOutput);
                    if (floatArraySuccess == 1) {
                        outAttributeValue = floatArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Single) + "[][]":
                    var floatArray2DOutput = new zExtFloatArray2D();
                    int floatArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeFloatArray2D(ref this, attributeKey, out floatArray2DOutput);
                    if (floatArray2DSuccess == 1) {
                        outAttributeValue = floatArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Double):
                    double doubleValue;
                    int doubleSuccess = zNativeMethods.ext_json_readJSONAttributeDouble(ref this, attributeKey, out doubleValue);
                    if (doubleSuccess == 1) {
                        outAttributeValue = doubleValue;
                        return true;
                    }
                    break;
                case nameof(Double) + "[]":
                    var doubleArrayOutput = new zExtDoubleArray();
                    int doubleArraySuccess = zNativeMethods.ext_json_readJSONAttributeDoubleArray(ref this, attributeKey, out doubleArrayOutput);
                    if (doubleArraySuccess == 1) {
                        outAttributeValue = doubleArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Double) + "[][]":
                    var doubleArray2DOutput = new zExtDoubleArray2D();
                    int doubleArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeDoubleArray2D(ref this, attributeKey, out doubleArray2DOutput);
                    if (doubleArray2DSuccess == 1) {
                        outAttributeValue = doubleArray2DOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(String):
                    zExtString stringValue = new zExtString();
                    int stringSuccess = zNativeMethods.ext_json_readJSONAttributeString(ref this, attributeKey, out stringValue);
                    if (stringSuccess == 1) {
                        outAttributeValue = stringValue.getString();
                        return true;
                    }
                    break;
                case nameof(String) + "[]":
                    zExtStringArray stringArrayOutput;
                    int stringArraySuccess = zNativeMethods.ext_json_readJSONAttributeStringArray(ref this, attributeKey, out stringArrayOutput);
                    if (stringArraySuccess == 1) {
                        outAttributeValue = stringArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(String) + "[][]":
                    zExtStringArray2D stringArray2DOutput;
                    int stringArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeStringArray2D(ref this, attributeKey, out stringArray2DOutput);
                    if (stringArray2DSuccess == 1) {
                        outAttributeValue = stringArray2DOutput.getItems();
                        return true;
                    }
                    break;

                case nameof(Boolean):
                    bool boolValue;
                    int boolSuccess = zNativeMethods.ext_json_readJSONAttributeBool(ref this, attributeKey, out boolValue);
                    if (boolSuccess == 1) {
                        outAttributeValue = boolValue;
                        return true;
                    }
                    break;
                case nameof(Boolean) + "[]":
                    zExtBoolArray boolArrayOutput;
                    int boolArraySuccess = zNativeMethods.ext_json_readJSONAttributeBoolArray(ref this, attributeKey, out boolArrayOutput);
                    if (boolArraySuccess == 1) {
                        outAttributeValue = boolArrayOutput.getItems();
                        return true;
                    }
                    break;
                case nameof(Boolean) + "[][]":
                    zExtBoolArray2D boolArray2DOutput;
                    int boolArray2DSuccess = zNativeMethods.ext_json_readJSONAttributeBoolArray2D(ref this, attributeKey, out boolArray2DOutput);
                    if (boolArray2DSuccess == 1) {
                        outAttributeValue = boolArray2DOutput.getItems();
                        return true;
                    }
                    break;
            }
            outAttributeValue = null;
            return false;
        }

        public bool WriteJSONAttribute<T>(string attributeKey, T attributeValue) {
            switch (typeof(T).Name) {
                case nameof(Int32):
                case nameof(Int64):
                    int intValue = Convert.ToInt32(attributeValue);
                    int intSuccess = zNativeMethods.ext_json_writeJSONAttributeInt(ref this, attributeKey, intValue);
                    return intSuccess == 1;
                case nameof(Int32) + "[]":
                case nameof(Int64) + "[]":
                    var intArrayOutput = new zExtIntArray();
                    intArrayOutput.setItems(attributeValue as int[]);
                    int intArraySuccess = zNativeMethods.ext_json_writeJSONAttributeIntArray(ref this, attributeKey, intArrayOutput);
                    return intArraySuccess == 1;
                case nameof(Int32) + "[][]":
                case nameof(Int64) + "[][]":
                    var intArray2DOutput = new zExtIntArray2D();
                    intArray2DOutput.setItems(attributeValue as int[][]);
                    int intArray2DSuccess = zNativeMethods.ext_json_writeJSONAttributeIntArray2D(ref this, attributeKey, intArray2DOutput);
                    return intArray2DSuccess == 1;
                case nameof(Single):
                    float floatValue = Convert.ToSingle(attributeValue);
                    int floatSuccess = zNativeMethods.ext_json_writeJSONAttributeFloat(ref this, attributeKey, floatValue);
                    return floatSuccess == 1;
                case nameof(Single) + "[]":
                    var floatArrayOutput = new zExtFloatArray();
                    floatArrayOutput.setItems(attributeValue as float[]);
                    int floatArraySuccess = zNativeMethods.ext_json_writeJSONAttributeFloatArray(ref this, attributeKey, floatArrayOutput);
                    return floatArraySuccess == 1;
                case nameof(Single) + "[][]":
                    var floatArray2DOutput = new zExtFloatArray2D();
                    floatArray2DOutput.setItems(attributeValue as float[][]);
                    int floatArray2DSuccess = zNativeMethods.ext_json_writeJSONAttributeFloatArray2D(ref this, attributeKey, floatArray2DOutput);
                    return floatArray2DSuccess == 1;
                case nameof(Double):
                    double doubleValue = Convert.ToDouble(attributeValue);
                    int doubleSuccess = zNativeMethods.ext_json_writeJSONAttributeDouble(ref this, attributeKey, doubleValue);
                    return doubleSuccess == 1;
                case nameof(Double) + "[]":
                    var doubleArrayOutput = new zExtDoubleArray();
                    doubleArrayOutput.setItems(attributeValue as double[]);
                    int doubleArraySuccess = zNativeMethods.ext_json_writeJSONAttributeDoubleArray(ref this, attributeKey, doubleArrayOutput);
                    return doubleArraySuccess == 1;
                case nameof(Double) + "[][]":
                    var doubleArray2DOutput = new zExtDoubleArray2D();
                    doubleArray2DOutput.setItems(attributeValue as double[][]);
                    int doubleArray2DSuccess = zNativeMethods.ext_json_writeJSONAttributeDoubleArray2D(ref this, attributeKey, doubleArray2DOutput);
                    return doubleArray2DSuccess == 1;
                case nameof(String):
                    string stringValue = Convert.ToString(attributeValue);
                    int stringSuccess = zNativeMethods.ext_json_writeJSONAttributeString(ref this, attributeKey, stringValue);
                    return stringSuccess == 1;
                case nameof(String) + "[]":
                    var stringArrayOutput = new zExtStringArray();
                    stringArrayOutput.setItems(attributeValue as string[]);
                    int stringArraySuccess = zNativeMethods.ext_json_writeJSONAttributeStringArray(ref this, attributeKey, stringArrayOutput);
                    return stringArraySuccess == 1;
                case nameof(String) + "[][]":
                    var stringArray2DOutput = new zExtStringArray2D();
                    stringArray2DOutput.setItems(attributeValue as string[][]);
                    int stringArray2DSuccess = zNativeMethods.ext_json_writeJSONAttributeStringArray2D(ref this, attributeKey, stringArray2DOutput);
                    return stringArray2DSuccess == 1;
                case nameof(Boolean):
                    bool boolValue = Convert.ToBoolean(attributeValue);
                    int boolSuccess = zNativeMethods.ext_json_writeJSONAttributeBool(ref this, attributeKey, boolValue);
                    return boolSuccess == 1;
                case nameof(Boolean) + "[]":
                    var boolArrayOutput = new zExtBoolArray();
                    boolArrayOutput.setItems(attributeValue as bool[]);
                    int boolArraySuccess = zNativeMethods.ext_json_writeJSONAttributeBoolArray(ref this, attributeKey, boolArrayOutput);
                    return boolArraySuccess == 1;
                case nameof(Boolean) + "[][]":
                    var boolArray2DOutput = new zExtBoolArray2D();
                    boolArray2DOutput.setItems(attributeValue as bool[][]);
                    int boolArray2DSuccess = zNativeMethods.ext_json_writeJSONAttributeBoolArray2D(ref this, attributeKey, boolArray2DOutput);
                    return boolArray2DSuccess == 1;
            }

            return false;
        }

        public Type xxgetType(string typeName) {
            switch (typeName) {
                case nameof(Int32):
                case nameof(Int64):
                    return typeof(int);
                case nameof(Int32) + "[]":
                case nameof(Int64) + "[]":
                    return typeof(int[]);
                case nameof(Int32) + "[][]":
                case nameof(Int64) + "[][]":
                    return typeof(int[][]);
                case nameof(Single):
                    return typeof(float);
                case nameof(Single) + "[]":
                    return typeof(float[]);
                case nameof(Single) + "[][]":
                    return typeof(float[][]);
                case nameof(Double):
                    return typeof(double);

                case nameof(Double) + "[]":
                    return typeof(double[]);

                case nameof(Double) + "[][]":
                    return typeof(double[][]);

                case nameof(String):
                    return typeof(string);

                case nameof(String) + "[]":
                    return typeof(string[]);

                case nameof(String) + "[][]":
                    return typeof(string[][]);

                case nameof(Boolean):
                    return typeof(bool);

                case nameof(Boolean) + "[]":
                    return typeof(bool[]);

                case nameof(Boolean) + "[][]":
                    return typeof(bool[][]);

            }
            return null;

        }
        public Type getType(string typeName) {
            switch (typeName) {
                case nameof(Int32):
                case nameof(Int64):
                case "int":
                    return typeof(int);
                case nameof(Int32) + "[]":
                case nameof(Int64) + "[]":
                case "int[]":
                    return typeof(int[]);
                case nameof(Int32) + "[][]":
                case nameof(Int64) + "[][]":
                case "int[][]":
                    return typeof(int[][]);
                case nameof(Single):
                case "float":
                    return typeof(float);
                case nameof(Single) + "[]":
                case "float[]":
                    return typeof(float[]);
                case nameof(Single) + "[][]":
                case "float[][]":
                    return typeof(float[][]);
                case nameof(Double):
                case "double":
                    return typeof(double);

                case nameof(Double) + "[]":
                case "double[]":
                    return typeof(double[]);
                case nameof(Double) + "[][]":
                case "double[][]":
                    return typeof(double[][]);
                
                case nameof(String):
                case "string":
                    return typeof(string);
                case nameof(String) + "[]":
                case "string[]":
                    return typeof(string[]);
                case nameof(String) + "[][]":
                case "string[][]":
                    return typeof(string[][]);

                case "bool":
                    return typeof(bool);
                case nameof(Boolean) + "[]":
                case "bool[]":
                    return typeof(bool[]);
                case nameof(Boolean) + "[][]":
                case "bool[][]":
                    return typeof(bool[][]);

            }
            return null;

        }

        public zExtJSON copy() {
            zExtJSON outjson;
            zNativeMethods.ext_json_createJsonDeepCopy(ref this, out outjson);
            return outjson;
        }

        public void ExportJsonFile(string filePath) {
            zNativeMethods.ext_json_exportFile(ref this, filePath);
        }
        public bool ReadJsonFile(string filePath) {
            int chk = zNativeMethods.ext_json_readJsonFile(ref this, filePath);
            return chk == 1 ? true : false;
        }
        public bool GetMesh(ref zExtMesh mesh) {
            int chk = zNativeMethods.ext_json_getMeshFromJson(ref this, ref mesh);
            return chk == 1 ? true : false;
        }
        static public bool GetMesh(string path, ref zExtMesh mesh) {
            int chk = zNativeMethods.ext_json_getMeshFromJsonPath(path, ref mesh);
            return chk == 1 ? true : false;
        }
        public void CreateJson() {
            Console.WriteLine("c# create json");
            zNativeMethods.ext_json_createJson(ref this);
        }

        public string[] AttributeTypes {
            get { return this.attributesTypes.getItems(); }
        }
        public string[] AttributeKeys {
            get { return this.attributesNames.getItems(); }
        }
    }

    static partial class zNativeMethods {


        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeInt(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out int outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeIntArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtIntArray outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeIntArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtIntArray2D outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeFloat(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out float outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeFloatArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtFloatArray outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeFloatArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtFloatArray2D outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeDouble(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out double outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeDoubleArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtDoubleArray outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeDoubleArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtDoubleArray2D outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeString(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtString outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeStringArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtStringArray outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeStringArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtStringArray2D outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeBool(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            [MarshalAs(UnmanagedType.Bool)] out bool outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeBoolArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtBoolArray outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJSONAttributeBoolArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            out zExtBoolArray2D outAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeInt(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            int inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeIntArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtIntArray inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeIntArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtIntArray2D inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeFloat(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            float inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeFloatArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtFloatArray inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeFloatArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtFloatArray2D inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeDouble(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            double inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeDoubleArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtDoubleArray inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeDoubleArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtDoubleArray2D inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeString(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            [MarshalAs(UnmanagedType.LPStr)] string inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeStringArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtStringArray inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeStringArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtStringArray2D inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeBool(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            [MarshalAs(UnmanagedType.Bool)] bool inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeBoolArray(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtBoolArray inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_writeJSONAttributeBoolArray2D(
            ref zExtJSON extJSON,
            [MarshalAs(UnmanagedType.LPStr)] string attributeKey,
            in zExtBoolArray2D inAttributeValue);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_json_createJson(ref zExtJSON extJSON);        
        
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ext_json_createJsonDeepCopy(ref zExtJSON inJSON, out zExtJSON outJson);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_readJsonFile(ref zExtJSON extJSON, [MarshalAs(UnmanagedType.LPStr)] string inputPath);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_getMeshFromJson(ref zExtJSON extJSON, ref zExtMesh outMesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_getMeshFromJsonPath([MarshalAs(UnmanagedType.LPStr)] string inputPath, ref zExtMesh outMesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_setMeshToJson(ref zExtJSON extJSON, ref zExtMesh inMesh);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_json_exportFile(ref zExtJSON extJSON, [MarshalAs(UnmanagedType.LPStr)] string outputPath);


    }
}

