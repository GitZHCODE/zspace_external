using System;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Provides utility methods for the zSpace External library.
    /// </summary>
    public static class zSpaceExternal
    {
        #region Helper Methods

        /// <summary>
        /// Gets the last error message from the native library.
        /// </summary>
        public static string GetLastError()
        {
            string errorMessage = NativeMethods.zext_get_last_error();
            if (string.IsNullOrEmpty(errorMessage))
                return string.Empty;
                
            return errorMessage;
        }

        /// <summary>
        /// Throws an exception with the last error message if the condition is false.
        /// </summary>
        public static void ThrowIfFailed(bool condition, string message = null)
        {
            if (!condition)
            {
                string errorMessage = GetLastError();
                
                if (string.IsNullOrEmpty(errorMessage) && !string.IsNullOrEmpty(message))
                {
                    errorMessage = message;
                }
                
                throw new ZSpaceExternalException(errorMessage, -1);
            }
        }

        #endregion
    }
} 