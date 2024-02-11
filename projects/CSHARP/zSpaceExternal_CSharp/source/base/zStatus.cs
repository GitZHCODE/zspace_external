using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace {
	public enum zStatusCode {
		zFAIL,              ///<The operation failed
		zSUCCESS,           ///<The operation was successful.
		zMemAllocSUCCESS,   ///<Memory allocation successful. 
		zMemNotAllocERROR,  ///<The operation failed due to memory not allocated.
		zThrowERROR,        ///<The operation failed due to a THROW error
		zInvalidParameter,  ///<The operation failed due to IVALID input
		zPathNotFound,      ///<The operation failed due to NOT FOUND PATH
		zRUNNING            ///<The operation is RUNNING
	};

	[StructLayout(LayoutKind.Sequential)]
	public struct zStatus {
		zStatusCode statusCode;
		[MarshalAs(UnmanagedType.LPStr)]
		string errorString;

		// Overloading == operator
		public static bool operator ==(zStatus left, zStatus right) {
			return zNativeMethods.ext_status_operator_equal(in left, in right);
		}
		public static bool operator !=(zStatus left, zStatus right) {
			return !(left == right);
		}
	}
	#region External methods for array
	static partial class zNativeMethods {
		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool ext_status_operator_equal(in zStatus item, in zStatus item2);

		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool ext_status_operator_equalCode(in zStatus item, in zStatusCode code);

		


	}

    #endregion
}