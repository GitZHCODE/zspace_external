using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Provides enhanced native library loading capabilities with diagnostics.
    /// </summary>
    internal static class NativeLibraryLoader
    {
        // Windows API functions for loading libraries
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr LoadLibrary(string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool FreeLibrary(IntPtr hLibModule);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern int GetLastError();

        private static readonly List<string> LoadedLibraries = new List<string>();

        /// <summary>
        /// Loads a native library with extended search paths and diagnostics.
        /// </summary>
        /// <param name="libraryName">Name of the library to load (e.g., "zSpace_External")</param>
        /// <returns>True if the library was loaded successfully, false otherwise.</returns>
        public static bool LoadNativeLibrary(string libraryName)
        {
            Debug.WriteLine($"Attempting to load native library: {libraryName}");

            // Check if the library is already loaded
            if (LoadedLibraries.Contains(libraryName) || GetModuleHandle(libraryName) != IntPtr.Zero)
            {
                Debug.WriteLine($"Library '{libraryName}' is already loaded.");
                return true;
            }

            string dllName = GetDllFileName(libraryName);
            string[] searchPaths = GetSearchPaths();
            string loadedPath = string.Empty;

            foreach (string searchPath in searchPaths)
            {
                string fullPath = Path.Combine(searchPath, dllName);
                if (File.Exists(fullPath))
                {
                    Debug.WriteLine($"Found library at: {fullPath}");
                    
                    // Print file information
                    try
                    {
                        FileInfo fileInfo = new FileInfo(fullPath);
                        Debug.WriteLine($"File size: {fileInfo.Length} bytes");
                        Debug.WriteLine($"Last modified: {fileInfo.LastWriteTime}");
                        Debug.WriteLine($"Created: {fileInfo.CreationTime}");
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine($"Error getting file info: {ex.Message}");
                    }

                    // Try to load the library
                    IntPtr handle = LoadLibrary(fullPath);
                    if (handle != IntPtr.Zero)
                    {
                        LoadedLibraries.Add(libraryName);
                        loadedPath = fullPath;
                        Debug.WriteLine($"Successfully loaded library from: {fullPath}");
                        return true;
                    }
                    else
                    {
                        int errorCode = GetLastError();
                        Debug.WriteLine($"Failed to load library. Error code: {errorCode}");
                        
                        // Try to diagnose common errors
                        DiagnoseLoadFailure(errorCode, fullPath);
                    }
                }
            }

            if (string.IsNullOrEmpty(loadedPath))
            {
                Debug.WriteLine($"Could not find {dllName} in any search paths:");
                foreach (string path in searchPaths)
                {
                    Debug.WriteLine($"  - {path} (Exists: {Directory.Exists(path)})");
                }
            }

            return false;
        }

        /// <summary>
        /// Gets the proper DLL file name with platform-specific extension.
        /// </summary>
        private static string GetDllFileName(string libraryName)
        {
            // On Windows, append .dll if not already present
            if (!libraryName.EndsWith(".dll", StringComparison.OrdinalIgnoreCase))
                return libraryName + ".dll";
            
            return libraryName;
        }

        /// <summary>
        /// Gets an array of paths to search for native libraries, in order of precedence.
        /// </summary>
        private static string[] GetSearchPaths()
        {
            List<string> paths = new List<string>();
            
            // 1. Application directory
            string appDir = AppDomain.CurrentDomain.BaseDirectory;
            paths.Add(appDir);
            
            // 2. Directory of the calling assembly
            string assemblyDir = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            if (!string.Equals(appDir, assemblyDir, StringComparison.OrdinalIgnoreCase))
                paths.Add(assemblyDir);
            
            // 3. Specific architecture subdirectories
            string archDir = Path.Combine(appDir, Environment.Is64BitProcess ? "x64" : "x86");
            if (Directory.Exists(archDir))
                paths.Add(archDir);
                
            // 4. Common library locations
            if (Environment.Is64BitProcess)
            {
                paths.Add(Path.Combine(appDir, "bin", "x64"));
                paths.Add(Path.Combine(assemblyDir, "bin", "x64"));
            }
            else
            {
                paths.Add(Path.Combine(appDir, "bin", "x86"));
                paths.Add(Path.Combine(assemblyDir, "bin", "x86"));
            }
            
            // 5. Environment PATH
            string pathEnv = Environment.GetEnvironmentVariable("PATH") ?? string.Empty;
            paths.AddRange(pathEnv.Split(Path.PathSeparator).Where(p => !string.IsNullOrWhiteSpace(p)));
            
            return paths.Distinct().ToArray();
        }

        /// <summary>
        /// Attempts to diagnose why a library load failed.
        /// </summary>
        private static void DiagnoseLoadFailure(int errorCode, string libraryPath)
        {
            switch (errorCode)
            {
                case 126: // ERROR_MOD_NOT_FOUND
                    Debug.WriteLine("Diagnosis: The specified module could not be found.");
                    Debug.WriteLine("This usually means the DLL is missing dependencies.");
                    CheckDependencies(libraryPath);
                    break;
                    
                case 193: // ERROR_BAD_EXE_FORMAT
                    Debug.WriteLine("Diagnosis: The DLL is not compatible with the current architecture.");
                    Debug.WriteLine($"Current process is {(Environment.Is64BitProcess ? "64-bit" : "32-bit")}.");
                    break;
                    
                case 5: // ERROR_ACCESS_DENIED
                    Debug.WriteLine("Diagnosis: Access denied. Check file permissions.");
                    break;
                    
                default:
                    Debug.WriteLine($"Unknown error code: {errorCode}");
                    break;
            }
        }

        /// <summary>
        /// Attempts to check the dependencies of a library using dumpbin (if available).
        /// </summary>
        private static void CheckDependencies(string libraryPath)
        {
            try
            {
                // Try to find dumpbin.exe (part of Visual Studio)
                string[] possibleDumpbinPaths = new[]
                {
                    @"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.35.32215\bin\Hostx64\x64\dumpbin.exe",
                    @"C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Tools\MSVC\14.35.32215\bin\Hostx64\x64\dumpbin.exe",
                    @"C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Tools\MSVC\14.35.32215\bin\Hostx64\x64\dumpbin.exe",
                    @"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\dumpbin.exe",
                    @"C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\dumpbin.exe",
                    @"C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x64\dumpbin.exe"
                };

                string dumpbinPath = possibleDumpbinPaths.FirstOrDefault(File.Exists);
                
                if (string.IsNullOrEmpty(dumpbinPath))
                {
                    Debug.WriteLine("Could not find dumpbin.exe to analyze dependencies.");
                    return;
                }

                Debug.WriteLine($"Using dumpbin.exe at: {dumpbinPath}");
                
                // Run dumpbin to get dependencies
                ProcessStartInfo psi = new ProcessStartInfo
                {
                    FileName = dumpbinPath,
                    Arguments = $"/DEPENDENTS \"{libraryPath}\"",
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                };

                using (Process process = Process.Start(psi))
                {
                    string output = process.StandardOutput.ReadToEnd();
                    process.WaitForExit();

                    if (process.ExitCode == 0)
                    {
                        Debug.WriteLine("Library dependencies:");
                        
                        // Parse dumpbin output to extract dependencies
                        string[] lines = output.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                        bool inDependenciesSection = false;
                        
                        foreach (string line in lines)
                        {
                            if (line.Contains("Image has the following dependencies:"))
                            {
                                inDependenciesSection = true;
                                continue;
                            }
                            
                            if (inDependenciesSection)
                            {
                                if (line.Trim().StartsWith("Summary"))
                                {
                                    inDependenciesSection = false;
                                    continue;
                                }
                                
                                string dependency = line.Trim();
                                if (!string.IsNullOrWhiteSpace(dependency))
                                {
                                    Debug.WriteLine($"  - {dependency}");
                                    
                                    // Check if the dependency exists in the same directory
                                    string depPath = Path.Combine(Path.GetDirectoryName(libraryPath), dependency);
                                    bool exists = File.Exists(depPath);
                                    Debug.WriteLine($"    Found in same directory: {exists}");
                                    
                                    // Also check in system directories
                                    if (!exists)
                                    {
                                        string[] systemPaths = new[]
                                        {
                                            @"C:\Windows\System32",
                                            @"C:\Windows\SysWOW64"
                                        };
                                        
                                        foreach (string sysPath in systemPaths)
                                        {
                                            string fullDepPath = Path.Combine(sysPath, dependency);
                                            if (File.Exists(fullDepPath))
                                            {
                                                Debug.WriteLine($"    Found in: {fullDepPath}");
                                                exists = true;
                                                break;
                                            }
                                        }
                                        
                                        if (!exists)
                                        {
                                            Debug.WriteLine("    NOT FOUND in system directories!");
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        Debug.WriteLine($"dumpbin.exe failed with exit code: {process.ExitCode}");
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error checking dependencies: {ex.Message}");
            }
        }
    }
} 