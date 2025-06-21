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

            // Configure debug output to go to console
            Debug.Listeners.Add(new ConsoleTraceListener());

            try
            {
                // First check if the native DLL exists before trying to use it
                Console.WriteLine("Checking native libraries before initialization...");
                PreInitDllCheck();

                // Try a minimal DLL load test first
                if (ShouldTryMinimalDllTest())
                {
                    TryMinimalDllLoadTest();
                    return; // Stop here for diagnostic purposes
                }

                Console.WriteLine("\nInitializing zSpace.External library...");
                bool initialized = false;
                
                try
                {
                    initialized = zSpaceExternal.Initialize();
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"ERROR during initialization: {ex.GetType().Name}");
                    Console.WriteLine($"Message: {ex.Message}");
                    Console.WriteLine($"Stack trace: {ex.StackTrace}");
                    
                    if (ex.InnerException != null)
                    {
                        Console.WriteLine($"Inner exception: {ex.InnerException.GetType().Name}: {ex.InnerException.Message}");
                    }
                    
                    throw; // Rethrow to be caught by outer try-catch
                }
                
                if (!initialized)
                {
                    Console.WriteLine("ERROR: Failed to initialize zSpace.External library. Exiting.");
                    return;
                }
                
                Console.WriteLine("Library initialized successfully!");

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
                    Console.WriteLine($"Inner stack trace: {ex.InnerException.StackTrace}");
                }
            }
            
            Console.WriteLine("\nPress any key to exit...");
            Console.ReadKey();
        }

        private static void PreInitDllCheck()
        {
            string dllName = "zSpace_External.dll";
            string[] searchPaths = new[]
            {
                Environment.CurrentDirectory,
                AppDomain.CurrentDomain.BaseDirectory,
                Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location),
            };

            Console.WriteLine("Pre-initialization DLL Check:");
            Console.WriteLine("-----------------------------");
            
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
                    
                    // Check if the DLL is bitness compatible
                    bool is64BitDll = Is64BitDll(fullPath);
                    Console.WriteLine($"  - 64-bit DLL: {is64BitDll}");
                    Console.WriteLine($"  - Matches process bitness: {is64BitDll == Environment.Is64BitProcess}");
                    
                    // Try to load the DLL manually
                    Console.WriteLine("  - Attempting to load DLL manually...");
                    IntPtr handle = IntPtr.Zero;
                    try
                    {
                        handle = LoadLibrary(fullPath);
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
                    catch (Exception ex)
                    {
                        Console.WriteLine($"  - Exception while loading DLL: {ex.Message}");
                    }
                }
            }
            
            if (!found)
            {
                Console.WriteLine("\nWARNING: The native DLL was not found in any expected location!");
            }
        }

        private static bool Is64BitDll(string dllPath)
        {
            try
            {
                // Check if the DLL is 64-bit by examining the PE header
                using (FileStream fs = new FileStream(dllPath, FileMode.Open, FileAccess.Read))
                {
                    byte[] buffer = new byte[4096]; // PE header should fit in 4KB
                    fs.Read(buffer, 0, buffer.Length);
                    
                    // Check MZ signature
                    if (buffer[0] != 'M' || buffer[1] != 'Z')
                        return false;
                    
                    // Get offset to PE header
                    int peOffset = BitConverter.ToInt32(buffer, 60);
                    
                    // Check PE signature
                    if (peOffset < 0 || peOffset > buffer.Length - 4)
                        return false;
                    
                    if (buffer[peOffset] != 'P' || buffer[peOffset + 1] != 'E' || 
                        buffer[peOffset + 2] != 0 || buffer[peOffset + 3] != 0)
                        return false;
                    
                    // Machine type is at offset 4 from PE signature
                    // 0x014c = I386 (32-bit), 0x8664 = AMD64 (64-bit)
                    int machineType = BitConverter.ToInt16(buffer, peOffset + 4);
                    
                    // Check if PE32+ (PE32+ is 64-bit)
                    int optionalHeaderMagic = BitConverter.ToInt16(buffer, peOffset + 24);
                    
                    return machineType == 0x8664 || optionalHeaderMagic == 0x20B;
                }
            }
            catch
            {
                return false; // If we can't determine, assume it's not 64-bit
            }
        }

        private static void RunNativeDllDiagnostics()
        {
            string dllName = "zSpace_External.dll";
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

        private static bool ShouldTryMinimalDllTest()
        {
            // For now, always run the minimal test as we're diagnosing the issue
            return true;
        }

        private static void TryMinimalDllLoadTest()
        {
            Console.WriteLine("\nRunning minimal DLL load test...");
            Console.WriteLine("--------------------------------");
            
            string dllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "zSpace_External.dll");
            if (!File.Exists(dllPath))
            {
                Console.WriteLine($"DLL not found at {dllPath}");
                return;
            }
            
            Console.WriteLine($"DLL found at {dllPath}");
            
            try
            {
                // Step 1: Load the DLL manually
                Console.WriteLine("Step 1: Loading DLL manually...");
                IntPtr dllHandle = LoadLibrary(dllPath);
                if (dllHandle == IntPtr.Zero)
                {
                    int errorCode = GetLastError();
                    Console.WriteLine($"Failed to load DLL. Error code: {errorCode}");
                    return;
                }
                
                Console.WriteLine("Successfully loaded DLL manually!");
                
                // Step 2: Get a function pointer (but don't call it yet)
                Console.WriteLine("Step 2: Getting function pointer for zext_get_last_error...");
                
                IntPtr funcPtr = GetProcAddress(dllHandle, "zext_get_last_error");
                if (funcPtr == IntPtr.Zero)
                {
                    int errorCode = GetLastError();
                    Console.WriteLine($"Failed to get function pointer. Error code: {errorCode}");
                }
                else
                {
                    Console.WriteLine("Successfully got function pointer!");
                }
                
                // Step 3: Try to initialize the zSpaceExternal class using the minimal approach
                Console.WriteLine("Step 3: Calling zSpaceExternal.Initialize() with minimal approach...");
                bool initialized = zSpaceExternal.Initialize();
                Console.WriteLine($"zSpaceExternal.Initialize() returned: {initialized}");
                
                Console.WriteLine("Step 4: Try to create a zExtMesh object without using it...");
                try
                {
                    var mesh = new zExtMesh();
                    Console.WriteLine("Successfully created zExtMesh object!");
                    // Don't call any methods on it yet
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Failed to create zExtMesh object: {ex.Message}");
                }
                
                // Free the library when done
                FreeLibrary(dllHandle);
                Console.WriteLine("Successfully freed DLL!");
                
                Console.WriteLine("\nMinimal DLL load test completed successfully!");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception during minimal DLL load test: {ex.GetType().Name}: {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
            }
        }
        
        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool FreeLibrary(IntPtr hModule);
    }
} 