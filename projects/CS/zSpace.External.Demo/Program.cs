using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Runtime.InteropServices;
using zSpace.External;

namespace zSpace.External.Demo
{
    class Program
    {
        // Import Windows API functions for DLL diagnostics
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr LoadLibrary(string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern int GetLastError();

        static void Main(string[] args)
        {
            Console.WriteLine("zSpace External Demo");
            Console.WriteLine("-------------------");
            Console.WriteLine($"Current directory: {Environment.CurrentDirectory}");
            Console.WriteLine($"Application path: {AppDomain.CurrentDomain.BaseDirectory}");
            Console.WriteLine($"OS Version: {Environment.OSVersion}");
            Console.WriteLine($"Runtime Version: {Environment.Version}");
            Console.WriteLine($"64-bit Process: {Environment.Is64BitProcess}");
            Console.WriteLine();

            try
            {
                // Check if the native DLL exists before trying to use it
                RunNativeDllDiagnostics();

                // Create a mesh
                Console.WriteLine("Creating mesh...");
                using (var mesh = new zExtMesh())
                {
                    Console.WriteLine("Mesh created successfully.");
                    Console.WriteLine($"Initial vertex count: {mesh.VertexCount}");
                    Console.WriteLine($"Initial face count: {mesh.FaceCount}");
                    
                }
                
                Console.WriteLine("\nDemo completed successfully!");
            }
            catch (DllNotFoundException ex)
            {
                Console.WriteLine("\nERROR: Failed to load the native library.");
                Console.WriteLine($"Exception: {ex.Message}");
                Console.WriteLine("\nAdditional diagnostics:");
                RunNativeDllDiagnostics();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"\nERROR: {ex.GetType().Name} - {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                if (ex.InnerException != null)
                {
                    Console.WriteLine($"Inner exception: {ex.InnerException.Message}");
                }
            }
            
            Console.WriteLine("\nPress any key to exit...");
            Console.ReadKey();
        }

        private static void RunNativeDllDiagnostics()
        {
            string dllName = "zSpace.External.dll";
            string[] searchPaths = new[]
            {
                Environment.CurrentDirectory,
                AppDomain.CurrentDomain.BaseDirectory,
                Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location),
            };

            Console.WriteLine("\nNative DLL Diagnostics:");
            Console.WriteLine("------------------------");
            
            bool found = false;
            foreach (string path in searchPaths)
            {
                if (!Directory.Exists(path))
                {
                    Console.WriteLine($"Search path does not exist: {path}");
                    continue;
                }
                
                string fullPath = Path.Combine(path, dllName);
                bool exists = File.Exists(fullPath);
                Console.WriteLine($"Checking: {fullPath} - {(exists ? "FOUND" : "NOT FOUND")}");
                
                if (exists)
                {
                    found = true;
                    
                    // Print file information
                    FileInfo fileInfo = new FileInfo(fullPath);
                    Console.WriteLine($"  - Size: {fileInfo.Length} bytes");
                    Console.WriteLine($"  - Created: {fileInfo.CreationTime}");
                    Console.WriteLine($"  - Modified: {fileInfo.LastWriteTime}");
                    
                    // Try to load the DLL manually
                    IntPtr handle = LoadLibrary(fullPath);
                    if (handle != IntPtr.Zero)
                    {
                        Console.WriteLine($"  - Successfully loaded manually using LoadLibrary");
                    }
                    else
                    {
                        int errorCode = GetLastError();
                        Console.WriteLine($"  - Failed to load manually. Error code: {errorCode}");
                        
                        // Diagnose common errors
                        switch (errorCode)
                        {
                            case 126: // ERROR_MOD_NOT_FOUND
                                Console.WriteLine("    Diagnosis: The DLL has missing dependencies.");
                                break;
                            case 193: // ERROR_BAD_EXE_FORMAT
                                Console.WriteLine("    Diagnosis: The DLL is not compatible with the current process architecture.");
                                Console.WriteLine($"    Current process is {(Environment.Is64BitProcess ? "64-bit" : "32-bit")}.");
                                break;
                            case 5: // ERROR_ACCESS_DENIED
                                Console.WriteLine("    Diagnosis: Access denied. Check file permissions.");
                                break;
                        }
                    }
                }
            }
            
            if (!found)
            {
                Console.WriteLine("\nThe native DLL was not found in any expected location!");
                
                // Check for VC++ Redistributable
                Console.WriteLine("\nChecking for VC++ Redistributable packages:");
                string[] vcRedistPaths = new[]
                {
                    @"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.35.32215\x64\Microsoft.VC143.CRT",
                    @"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Redist\MSVC\14.29.30133\x64\Microsoft.VC142.CRT"
                };
                
                foreach (string vcPath in vcRedistPaths)
                {
                    bool exists = Directory.Exists(vcPath);
                    Console.WriteLine($"  {vcPath} - {(exists ? "FOUND" : "NOT FOUND")}");
                }
            }
            
            Console.WriteLine();
        }
    }
} 