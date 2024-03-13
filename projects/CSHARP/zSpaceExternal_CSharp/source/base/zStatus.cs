using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace zSpace {
	public enum zStatusCode {
		zFail,              ///<The operation failed
		zSuccess,           ///<The operation was successful.
		zMemAllocSuccess,   ///<Memory allocation successful. 
		zMemNotAllocError,  ///<The operation failed due to memory not allocated.
		zThrowError,        ///<The operation failed due to a THROW error
		zInvalidParameter,  ///<The operation failed due to IVALID input
		zPathNotFound,      ///<The operation failed due to NOT FOUND PATH
		zRunning,           ///<The operation is RUNNING
		zSkip               ///<The operation is skipped due to internal condition
	};

	[StructLayout(LayoutKind.Sequential)]
	public struct zStatus {
		zStatusCode statusCode;
		[MarshalAs(UnmanagedType.LPStr)]
		string statusMessage;

		// Overloading == operator
		public static bool operator ==(zStatus left, zStatus right) {
			return zNativeMethods.ext_status_operator_equal(in left, in right);
		}
		public static bool operator !=(zStatus left, zStatus right) {
			return !(left == right);
		}

		public bool getErrorCheck() {
			return zNativeMethods.ext_status_getErrorCheck(in this);
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
		
		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool ext_status_getErrorCheck(in zStatus item);
	}

    #endregion
}