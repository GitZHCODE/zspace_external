using System;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace zSpace.External
{
    /// <summary>
    /// Helper class for loading the native library.
    /// </summary>
    internal static class NativeLibrary
    {
        private const string LibraryName = "zSpace_External";
        private static bool _isInitialized;
        private static bool _initializeAttempted;
        
        /// <summary>
        /// Initializes the native library.
        /// </summary>
        /// <exception cref="DllNotFoundException">Thrown when the native library cannot be loaded.</exception>
        public static void Initialize()
        {
            // Return immediately if we've already successfully initialized
            if (_isInitialized)
            {
                Debug.WriteLine("NativeLibrary.Initialize: Already initialized, returning early");
                return;
            }
                
            // If we've already attempted initialization and failed, don't try again
            if (_initializeAttempted)
            {
                Debug.WriteLine("NativeLibrary.Initialize: Already attempted and failed, returning early");
                return;
            }
                
            _initializeAttempted = true;
            
            Debug.WriteLine("NativeLibrary.Initialize: Starting initialization");
            
            try
            {
                // Look for the DLL in various locations and log what we find
                string[] searchPaths = new[]
                {
                    AppDomain.CurrentDomain.BaseDirectory,
                    Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location),
                    Environment.CurrentDirectory
                };
                
                Debug.WriteLine("NativeLibrary.Initialize: Searching for DLL in the following paths:");
                foreach (string path in searchPaths)
                {
                    string dllPath = Path.Combine(path, LibraryName + ".dll");
                    bool exists = File.Exists(dllPath);
                    Debug.WriteLine($"  {dllPath}: {(exists ? "EXISTS" : "NOT FOUND")}");
                    
                    if (exists)
                    {
                        FileInfo fileInfo = new FileInfo(dllPath);
                        Debug.WriteLine($"    Size: {fileInfo.Length} bytes");
                        Debug.WriteLine($"    Modified: {fileInfo.LastWriteTime}");
                    }
                }
                
                Debug.WriteLine("NativeLibrary.Initialize: Attempting to force load DLL via P/Invoke call");
                
                // Simple approach: try to make a call to force the library to load
                string errorMessage = NativeMethods.zext_get_last_error();
                
                // If we get here, the library loaded successfully
                Debug.WriteLine("NativeLibrary.Initialize: Successfully called zext_get_last_error()");
                _isInitialized = true;
                Debug.WriteLine("NativeLibrary.Initialize: Initialization completed successfully");
            }
            catch (DllNotFoundException ex)
            {
                // Provide minimal but useful error information
                string paths = string.Join(Path.PathSeparator.ToString(), 
                    new[] { 
                        AppDomain.CurrentDomain.BaseDirectory,
                        Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)
                    });
                
                Debug.WriteLine($"NativeLibrary.Initialize: DllNotFoundException: {ex.Message}");
                Debug.WriteLine($"NativeLibrary.Initialize: Search paths: {paths}");
                
                throw new DllNotFoundException(
                    $"Failed to load native library '{LibraryName}'. Error: {ex.Message}\n" +
                    $"Search paths: {paths}", ex);
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"NativeLibrary.Initialize: Unexpected exception: {ex.GetType().Name}: {ex.Message}");
                Debug.WriteLine($"NativeLibrary.Initialize: Stack trace: {ex.StackTrace}");
                
                throw new DllNotFoundException(
                    $"Failed to initialize native library '{LibraryName}'. Error: {ex.GetType().Name} - {ex.Message}", ex);
            }
        }
    }
} 