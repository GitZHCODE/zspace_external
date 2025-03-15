using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Helper class for loading the native library.
    /// </summary>
    internal static class NativeLibrary
    {
        private const string LibraryName = "zSpace_External";
        private static bool _isInitialized;
        
        /// <summary>
        /// Initializes the native library.
        /// </summary>
        /// <exception cref="DllNotFoundException">Thrown when the native library cannot be loaded.</exception>
        public static void Initialize()
        {
            if (_isInitialized)
                return;
                
            try
            {
                // Use the enhanced library loader with diagnostics
                bool loaded = NativeLibraryLoader.LoadNativeLibrary(LibraryName);
                
                if (!loaded)
                {
                    // If the enhanced loader fails, try the traditional approach as a fallback
                    TraditionalLoadLibrary();
                }
                
                _isInitialized = true;
            }
            catch (Exception ex)
            {
                throw new DllNotFoundException($"Failed to load native library '{LibraryName}'. Error: {ex.Message}", ex);
            }
        }
        
        /// <summary>
        /// Traditional approach to loading the native library.
        /// </summary>
        private static void TraditionalLoadLibrary()
        {
            // Force loading the DLL to trigger the loader
            // This will throw a DllNotFoundException if it can't be loaded
            try
            {
                // Make a simple API call to force the library to load
                int errorCode = NativeMethods.zext_get_last_error();
                if (errorCode != 0)
                {
                    // Clear any error
                    string errorMsg = NativeMethods.zext_get_last_error_message();
                    NativeMethods.zext_clear_last_error();
                }
                
                _isInitialized = true;
            }
            catch (DllNotFoundException)
            {
                LogDllSearchPaths();
                throw;
            }
            catch (Exception ex)
            {
                throw new DllNotFoundException($"Failed to initialize native library '{LibraryName}'. Error: {ex.Message}", ex);
            }
        }
        
        private static void LogDllSearchPaths()
        {
            // Log search paths to help with debugging
            string dllName = LibraryName + ".dll";
            string appDir = AppDomain.CurrentDomain.BaseDirectory;
            string assemblyDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            
            Console.WriteLine($"Native DLL search paths for '{dllName}':");
            Console.WriteLine($"Current directory: {Environment.CurrentDirectory}");
            Console.WriteLine($"Application directory: {appDir}");
            Console.WriteLine($"Assembly directory: {assemblyDir}");
            
            string dllPath = Path.Combine(appDir, dllName);
            Console.WriteLine($"Looking for: {dllPath}, Exists: {File.Exists(dllPath)}");
            
            if (!string.Equals(appDir, assemblyDir, StringComparison.OrdinalIgnoreCase))
            {
                dllPath = Path.Combine(assemblyDir, dllName);
                Console.WriteLine($"Looking for: {dllPath}, Exists: {File.Exists(dllPath)}");
            }
        }
    }
} 