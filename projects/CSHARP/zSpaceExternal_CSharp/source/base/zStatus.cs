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
	public static class zStatusCodeUtil {
		/// <summary>
		/// check if the status is an error
		/// </summary>
		/// <param name="code"></param>
		/// <returns>TRUE if an error occured</returns>
		public static bool getErrorCheck(zStatusCode code) {
			switch (code) {
				case zStatusCode.zFail: return true;
				case zStatusCode.zSuccess: return false;
				case zStatusCode.zMemAllocSuccess: return false;
				case zStatusCode.zMemNotAllocError: return true;
				case zStatusCode.zThrowError: return true;
				case zStatusCode.zInvalidParameter: return true;
				case zStatusCode.zPathNotFound: return true;
				case zStatusCode.zRunning: return false;

				default: return false;
			}
		}
		public static string getCodeString(zStatusCode code) {
			switch (code) {
				case zStatusCode.zFail: return "Process failed";
				case zStatusCode.zSuccess: return "Process success";
				case zStatusCode.zMemAllocSuccess: return "Process success: Memory allocation success";
				case zStatusCode.zMemNotAllocError: return "Process failed: Memory allocation error";
				case zStatusCode.zThrowError: return "Process failed: Unknown error";
				case zStatusCode.zInvalidParameter: return "Process failed: Invalid input parameter";
				case zStatusCode.zPathNotFound: return "Process failed: Path/Directory is not found";
				case zStatusCode.zRunning: return "Process is running";
				case zStatusCode.zSkip: return "Process is skipped";

				default: return "code value is invalid/not set";
			}
		}
	};
	[StructLayout(LayoutKind.Sequential)]
	public struct zStatus {
		zStatusCode statusCode;
		//[MarshalAs(UnmanagedType.LPWStr)]
		//string statusMessage;

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
		public zStatusCode getCode() {
			return statusCode;
        }
		public string getMessage() {
			return "";
			//return statusMessage;
        }

	}

	[StructLayout(LayoutKind.Sequential)]
	public struct zStatus2 {
		public int statusCode;
		//public zStatus2() {
		//	statusCode = 10;

		//}
	}



	#region External methods for array
	static partial class zNativeMethods {
		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		public static extern bool ext_status_operator_equal(in zStatus item, in zStatus item2);

		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		public static extern bool ext_status_operator_equalCode(in zStatus item, in zStatusCode code);
		
		[DllImport(path, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		public static extern bool ext_status_getErrorCheck(in zStatus item);
	}

    #endregion
}