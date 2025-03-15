using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using zSpace.External;

namespace zSpace.External.Tests
{
    [TestClass]
    public class MeshTests
    {
        private static bool _nativeLibraryDiagnosed = false;

        [ClassInitialize]
        public static void ClassInitialize(TestContext context)
        {
            // Setup code that runs once before any tests
            DiagnoseNativeLibrary();
        }

        [TestMethod]
        public void CanCreateMesh()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                {
                    Assert.IsNotNull(mesh, "Mesh should be created successfully");
                    Assert.IsTrue(mesh.IsValid, "Mesh should be valid");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanCreateMesh: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanCreateCustomMesh()
        {
            using (var mesh = new zSpace.External.zExtMesh())
            {
                // Create data for a simple triangle
                double[] vertices = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0,  // Vertex 1
                    0.0, 1.0, 0.0   // Vertex 2
                };
                
                int[] polyCounts = new int[] { 3 }; // One face with 3 vertices
                int[] polyConnections = new int[] { 0, 1, 2 }; // Vertices 0, 1, 2 form the face
                
                // Act & Assert - Initial state
                Assert.IsTrue(mesh.IsValid, "Mesh should be valid upon creation");
                Assert.AreEqual(0, mesh.VertexCount, "Vertex count should be 0 initially");
                Assert.AreEqual(0, mesh.FaceCount, "Face count should be 0 initially");
                
                // Act - Create mesh
                mesh.CreateMesh(vertices, polyCounts, polyConnections);
                
                // Debug output
                Console.WriteLine($"Vertex count: {mesh.VertexCount}");
                Console.WriteLine($"Face count: {mesh.FaceCount}");
                
                // Assert - Final state
                Assert.AreEqual(3, mesh.VertexCount, "Vertex count should be 3");
                Assert.AreEqual(1, mesh.FaceCount, "Face count should be 1");
            }
        }

        #region Helper Methods

        private static void DiagnoseNativeLibrary()
        {
            if (_nativeLibraryDiagnosed)
                return;

            Console.WriteLine("Running native library diagnostics...");
            
            string assemblyPath = typeof(zSpace.External.zExtMesh).Assembly.Location;
            string assemblyDir = Path.GetDirectoryName(assemblyPath);
            string dllPath = Path.Combine(assemblyDir, "zSpace_External.dll");
            
            Console.WriteLine($"Assembly directory: {assemblyDir}");
            
            if (File.Exists(dllPath))
            {
                Console.WriteLine($"DLL exists at: {dllPath}");
                Console.WriteLine($"File size: {new FileInfo(dllPath).Length} bytes");
                Console.WriteLine($"Last modified: {File.GetLastWriteTime(dllPath)}");
                
                try
                {
                    // Check file version and other properties 
                    var versionInfo = FileVersionInfo.GetVersionInfo(dllPath);
                    Console.WriteLine($"File version: {versionInfo.FileVersion}");
                    Console.WriteLine($"Product version: {versionInfo.ProductVersion}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error getting version info: {ex.Message}");
                }

                // List dependencies if DumpBin is available
                try
                {
                    var process = new Process()
                    {
                        StartInfo = new ProcessStartInfo("dumpbin", $"/dependents \"{dllPath}\"")
                        {
                            UseShellExecute = false,
                            RedirectStandardOutput = true,
                            CreateNoWindow = true
                        }
                    };
                    
                    process.Start();
                    string output = process.StandardOutput.ReadToEnd();
                    process.WaitForExit();
                    
                    Console.WriteLine("DLL Dependencies:");
                    Console.WriteLine(output);
                }
                catch
                {
                    Console.WriteLine("Could not run dumpbin to check dependencies");
                }
                
                // Try to load the DLL manually to see detailed errors
                try
                {
                    IntPtr handle = NativeMethods.LoadLibrary(dllPath);
                    if (handle == IntPtr.Zero)
                    {
                        int error = Marshal.GetLastWin32Error();
                        Console.WriteLine($"Failed to load library: Error {error}");
                    }
                    else
                    {
                        Console.WriteLine("Successfully loaded library manually");
                        NativeMethods.FreeLibrary(handle);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error loading library: {ex.Message}");
                }
            }
            else
            {
                Console.WriteLine($"DLL does not exist at: {dllPath}");
            }
            
            _nativeLibraryDiagnosed = true;
        }

        #endregion
    }

    internal static class NativeMethods
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool FreeLibrary(IntPtr hModule);
    }
} 