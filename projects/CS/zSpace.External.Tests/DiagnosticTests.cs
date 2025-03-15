using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace zSpace.External.Tests
{
    [TestClass]
    public class DiagnosticTests
    {
        [TestMethod]
        public void ShowSystemInfo()
        {
            Console.WriteLine("=== System Information ===");
            Console.WriteLine($"OS Version: {Environment.OSVersion}");
            Console.WriteLine($".NET Framework: {Environment.Version}");
            Console.WriteLine($"64-bit OS: {Environment.Is64BitOperatingSystem}");
            Console.WriteLine($"64-bit Process: {Environment.Is64BitProcess}");
            Console.WriteLine($"CPU Count: {Environment.ProcessorCount}");
            Console.WriteLine($"Working Directory: {Environment.CurrentDirectory}");
            Console.WriteLine($"CLR Path: {RuntimeEnvironment.GetRuntimeDirectory()}");
        }

        [TestMethod]
        public void ShowAssemblyInfo()
        {
            Console.WriteLine("=== Assembly Information ===");

            var currentAssembly = Assembly.GetExecutingAssembly();
            var libAssembly = typeof(ZSpaceExternal).Assembly;

            DisplayAssemblyInfo("Current Assembly", currentAssembly);
            DisplayAssemblyInfo("Library Assembly", libAssembly);

            // List all referenced assemblies
            Console.WriteLine("\nReferenced Assemblies:");
            foreach (var reference in libAssembly.GetReferencedAssemblies().OrderBy(a => a.Name))
            {
                Console.WriteLine($"  - {reference.Name} ({reference.Version})");
            }
        }

        [TestMethod]
        public void ListLoadedModules()
        {
            Console.WriteLine("=== Loaded Modules ===");
            var currentProcess = System.Diagnostics.Process.GetCurrentProcess();
            
            foreach (var module in currentProcess.Modules.Cast<System.Diagnostics.ProcessModule>().OrderBy(m => m.ModuleName))
            {
                Console.WriteLine($"{module.ModuleName,-40} {module.FileName}");
            }
        }

        [TestMethod]
        public void CheckNativeDll()
        {
            Console.WriteLine("=== Native DLL Check ===");
            
            string assemblyPath = typeof(ZSpaceExternal).Assembly.Location;
            string assemblyDir = Path.GetDirectoryName(assemblyPath);
            string dllPath = Path.Combine(assemblyDir, "zSpace_External.dll");
            
            Console.WriteLine($"Looking for DLL at: {dllPath}");
            
            if (File.Exists(dllPath))
            {
                Console.WriteLine("DLL found!");
                FileInfo fileInfo = new FileInfo(dllPath);
                Console.WriteLine($"Size: {fileInfo.Length:N0} bytes");
                Console.WriteLine($"Created: {fileInfo.CreationTime}");
                Console.WriteLine($"Modified: {fileInfo.LastWriteTime}");
                
                // Try to manually load the DLL
                try
                {
                    Console.WriteLine("\nAttempting to manually load DLL...");
                    IntPtr handle = LoadLibrary(dllPath);
                    if (handle == IntPtr.Zero)
                    {
                        int error = Marshal.GetLastWin32Error();
                        Console.WriteLine($"Failed to load DLL: Error {error}");
                        ReportMissingDependencies(dllPath);
                    }
                    else
                    {
                        Console.WriteLine("Successfully loaded DLL manually!");
                        FreeLibrary(handle);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Exception during manual loading: {ex.Message}");
                }
            }
            else
            {
                Console.WriteLine("DLL not found!");
                
                // Check other potential locations
                string[] searchPaths = new[] 
                {
                    Environment.CurrentDirectory,
                    Path.GetDirectoryName(Assembly.GetEntryAssembly().Location),
                    Path.Combine(Path.GetDirectoryName(assemblyDir), "bin", "x64", "Debug"),
                    Path.Combine(Path.GetDirectoryName(assemblyDir), "bin", "x64", "Release"),
                };
                
                Console.WriteLine("\nSearching in alternative locations:");
                foreach (string path in searchPaths)
                {
                    string altPath = Path.Combine(path, "zSpace_External.dll");
                    bool exists = File.Exists(altPath);
                    Console.WriteLine($"{altPath}: {(exists ? "FOUND" : "not found")}");
                }
            }
        }

        [TestMethod]
        public void ShowSearchPath()
        {
            Console.WriteLine("=== DLL Search Path ===");
            string path = Environment.GetEnvironmentVariable("PATH");
            string[] paths = path.Split(Path.PathSeparator);
            
            foreach (string dir in paths)
            {
                if (string.IsNullOrWhiteSpace(dir)) continue;
                
                try
                {
                    bool exists = Directory.Exists(dir);
                    Console.WriteLine($"{dir,-60} {(exists ? "[exists]" : "[not found]")}");
                }
                catch
                {
                    Console.WriteLine($"{dir,-60} [error accessing]");
                }
            }
        }

        #region Helper Methods

        private void DisplayAssemblyInfo(string label, Assembly assembly)
        {
            Console.WriteLine($"\n{label}:");
            Console.WriteLine($"  Name: {assembly.GetName().Name}");
            Console.WriteLine($"  Version: {assembly.GetName().Version}");
            Console.WriteLine($"  Location: {assembly.Location}");
            Console.WriteLine($"  CodeBase: {assembly.CodeBase}");
            
            var attribs = assembly.GetCustomAttributes(typeof(AssemblyInformationalVersionAttribute), false);
            if (attribs.Length > 0)
            {
                var informationalVersion = (AssemblyInformationalVersionAttribute)attribs[0];
                Console.WriteLine($"  Informational Version: {informationalVersion.InformationalVersion}");
            }
        }

        private void ReportMissingDependencies(string dllPath)
        {
            try
            {
                var commonDependencies = new List<string>
                {
                    "KERNEL32.DLL",
                    "USER32.DLL", 
                    "SHELL32.DLL",
                    "ADVAPI32.DLL",
                    "msvcrt.dll",
                    "VCRUNTIME140.dll",
                    "MSVCP140.dll",
                    "api-ms-win-crt-runtime-l1-1-0.dll"
                };

                Console.WriteLine("\nChecking for common dependencies:");
                foreach (var dep in commonDependencies)
                {
                    string depPath = null;
                    
                    // Check in the same directory
                    string localPath = Path.Combine(Path.GetDirectoryName(dllPath), dep);
                    if (File.Exists(localPath))
                    {
                        depPath = localPath;
                    }
                    else
                    {
                        // Check in system directories
                        // First Windows directory
                        string winDir = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.Windows), "System32", dep);
                        if (File.Exists(winDir))
                        {
                            depPath = winDir;
                        }
                    }
                    
                    Console.WriteLine($"  {dep,-30} {(depPath != null ? $"Found at: {depPath}" : "NOT FOUND")}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error checking dependencies: {ex.Message}");
            }
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr LoadLibrary(string lpFileName);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool FreeLibrary(IntPtr hModule);

        #endregion
    }
} 