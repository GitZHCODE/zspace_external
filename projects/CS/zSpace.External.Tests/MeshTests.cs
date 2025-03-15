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

        [TestMethod]
        public void CanComputeGeodesicHeat()
        {
            using (var mesh = new zSpace.External.zExtMesh())
            {
                // Create a simple quad mesh
                double[] vertices = new double[] {
                    // Front face vertices
                    -1.0, -1.0, 0.0,  // Vertex 0
                    1.0, -1.0, 0.0,  // Vertex 1
                    1.0, 1.0, 0.0,  // Vertex 2
                    -1.0, 1.0, 0.0,  // Vertex 3
                    0.0, 0.0, 0.0,  // Vertex 4
                };
                
                // Each face has 4 vertices (quad faces)
                int[] polyCounts = new int[] { 
                    3, 3, 3, 3  // 4 tri faces
                };
                
                // Face vertex indices
                int[] polyConnections = new int[] { 
                    0, 1, 4,
                    1, 2, 4,
                    2, 3, 4,
                    3, 0, 4
                };
                
                // Create the mesh
                mesh.CreateMesh(vertices, polyCounts, polyConnections);
                
                // Validate mesh creation
                Assert.AreEqual(5, mesh.VertexCount, "Vertex count should be 8");
                Assert.AreEqual(4, mesh.FaceCount, "Face count should be 6");
                
                // Set source vertex (vertex 0 at corner)
                int[] sourceVertices = new int[] { 0 };
                
                // Pre-allocate result array (one float per vertex)
                float[] geodesicDistances = new float[mesh.VertexCount];
                
                // Compute geodesic distances
                mesh.ComputeGeodesicHeat(sourceVertices, geodesicDistances);

                // Basic validation
                Assert.IsTrue(geodesicDistances.Length == mesh.VertexCount, "GeodesicDistances should have equal number of values as mesh vertices");

                // Output results for inspection
                Console.WriteLine("Geodesic distances from vertex 0:");
                for (int i = 0; i < geodesicDistances.Length; i++)
                {
                    Console.WriteLine($"Vertex {i}: {geodesicDistances[i]}");
                }
                
                // Basic validation
                // Distance to source vertex should be 0 (or very close to it)
                Assert.IsTrue(geodesicDistances[0] < 0.001f, "Distance to source vertex should be near zero");
                
                // All distances should be non-negative
                for (int i = 0; i < geodesicDistances.Length; i++)
                {
                    Assert.IsTrue(geodesicDistances[i] >= 0, $"Distance at vertex {i} should be non-negative");
                }
                
                // Diagonal vertex (6) should have the largest distance
                float maxDistance = 0;
                int maxDistanceIndex = 0;
                for (int i = 0; i < geodesicDistances.Length; i++)
                {
                    if (geodesicDistances[i] > maxDistance)
                    {
                        maxDistance = geodesicDistances[i];
                        maxDistanceIndex = i;
                    }
                }
                
                // Verify maximum distance is at the diagonally opposite vertex
                Console.WriteLine($"Maximum distance {maxDistance} is at vertex {maxDistanceIndex}");
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