using System;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace zSpace.External
{
    /// <summary>
    /// Main entry point and utility class for the zSpace.External library.
    /// </summary>
    public static class zSpaceExternal
    {
        private static bool _isInitialized = false;
        
        /// <summary>
        /// Initializes the zSpace.External library. This method must be called once
        /// before using any other functionality in the library.
        /// </summary>
        /// <returns>True if initialization was successful, false otherwise.</returns>
        public static bool Initialize()
        {
            if (_isInitialized)
                return true;
                
            try
            {
                Debug.WriteLine("zSpaceExternal.Initialize: Starting initialization with minimal approach");
                
                // Skip actual initialization for now - just test if the library can be loaded
                // This is a diagnostic version that avoids triggering the heap corruption
                _isInitialized = true;
                Debug.WriteLine("zSpaceExternal.Initialize: Minimal initialization completed successfully");
                return true;
                
                /* Normal initialization code - temporarily disabled for diagnosis
                Debug.WriteLine("Initializing zSpace.External library...");
                NativeLibrary.Initialize();
                _isInitialized = true;
                Debug.WriteLine("zSpace.External library initialized successfully.");
                return true;
                */
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Failed to initialize zSpace.External library: {ex.Message}");
                return false;
            }
        }
        
        /// <summary>
        /// Gets whether the library has been initialized.
        /// </summary>
        public static bool IsInitialized => _isInitialized;

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