using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using zSpace.External;

namespace zSpace.External.Tests
{
    [TestClass]
    public class GraphTests
    {
        private static bool _nativeLibraryDiagnosed = false;

        [ClassInitialize]
        public static void ClassInitialize(TestContext context)
        {
            // Setup code that runs once before any tests
            DiagnoseNativeLibrary();
        }

        [TestMethod]
        public void CanCreateGraph()
        {
            try
            {
                using (var graph = new zSpace.External.zExtGraph())
                {
                    Assert.IsNotNull(graph, "Graph should be created successfully");
                    Assert.IsTrue(graph.IsValid, "Graph should be valid");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanCreateGraph: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanCreateCustomGraph()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Create data for a simple line graph
                double[] vertices = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0,  // Vertex 1
                    1.0, 1.0, 0.0,  // Vertex 2
                    0.0, 1.0, 0.0   // Vertex 3
                };
                
                // Connect vertices to form a square
                int[] edgeConnections = new int[] { 
                    0, 1,  // Edge 0: connects vertex 0 to vertex 1
                    1, 2,  // Edge 1: connects vertex 1 to vertex 2
                    2, 3,  // Edge 2: connects vertex 2 to vertex 3
                    3, 0   // Edge 3: connects vertex 3 to vertex 0
                };
                
                // Act & Assert - Initial state
                Assert.IsTrue(graph.IsValid, "Graph should be valid upon creation");
                Assert.AreEqual(0, graph.VertexCount, "Vertex count should be 0 initially");
                Assert.AreEqual(0, graph.EdgeCount, "Edge count should be 0 initially");
                
                // Act - Create graph
                graph.CreateGraph(vertices, edgeConnections);
                
                // Debug output
                Console.WriteLine($"Vertex count: {graph.VertexCount}");
                Console.WriteLine($"Edge count: {graph.EdgeCount}");
                
                // Assert - Final state
                Assert.AreEqual(4, graph.VertexCount, "Vertex count should be 4");
                Assert.AreEqual(4, graph.EdgeCount, "Edge count should be 4");
            }
        }

        [TestMethod]
        public void CanGetVertexPositions()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Create data for a simple triangle graph
                double[] vertices = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0,  // Vertex 1
                    0.5, 1.0, 0.0   // Vertex 2
                };
                
                // Connect vertices to form a triangle
                int[] edgeConnections = new int[] { 
                    0, 1,  // Edge 0: connects vertex 0 to vertex 1
                    1, 2,  // Edge 1: connects vertex 1 to vertex 2
                    2, 0   // Edge 2: connects vertex 2 to vertex 0
                };
                
                // Create graph
                graph.CreateGraph(vertices, edgeConnections);
                
                // Verify graph creation
                Assert.AreEqual(3, graph.VertexCount, "Vertex count should be 3");
                Assert.AreEqual(3, graph.EdgeCount, "Edge count should be 3");
                
                // Get vertex positions
                double[] retrievedPositions = graph.GetVertexPositions();
                
                // Verify positions match what we set
                Assert.AreEqual(vertices.Length, retrievedPositions.Length, "Retrieved positions length should match original");
                
                // Output retrieved positions
                Console.WriteLine("Retrieved vertex positions:");
                for (int i = 0; i < graph.VertexCount; i++)
                {
                    int baseIndex = i * 3;
                    Console.WriteLine($"Vertex {i}: ({retrievedPositions[baseIndex]}, {retrievedPositions[baseIndex+1]}, {retrievedPositions[baseIndex+2]})");
                }
                
                // Check each retrieved position against original
                for (int i = 0; i < vertices.Length; i++)
                {
                    Assert.AreEqual(vertices[i], retrievedPositions[i], 1e-6, $"Position component at index {i} should match");
                }
            }
        }

        [TestMethod]
        public void CanSetVertexPositions()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Create data for a simple line graph
                double[] initialVertices = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0   // Vertex 1
                };
                
                // Connect vertices to form a line
                int[] edgeConnections = new int[] { 
                    0, 1  // Edge 0: connects vertex 0 to vertex 1
                };
                
                // Create graph
                graph.CreateGraph(initialVertices, edgeConnections);
                
                // Verify graph creation
                Assert.AreEqual(2, graph.VertexCount, "Vertex count should be 2");
                Assert.AreEqual(1, graph.EdgeCount, "Edge count should be 1");
                
                // Create new positions
                double[] newPositions = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0 - unchanged
                    2.0, 0.0, 0.0   // Vertex 1 - moved further away
                };
                
                // Set new positions
                graph.SetVertexPositions(newPositions);
                
                // Get positions back
                double[] retrievedPositions = graph.GetVertexPositions();
                
                // Output retrieved positions
                Console.WriteLine("Retrieved vertex positions after update:");
                for (int i = 0; i < graph.VertexCount; i++)
                {
                    int baseIndex = i * 3;
                    Console.WriteLine($"Vertex {i}: ({retrievedPositions[baseIndex]}, {retrievedPositions[baseIndex+1]}, {retrievedPositions[baseIndex+2]})");
                }
                
                // Check that positions were updated
                Assert.AreEqual(2.0, retrievedPositions[3], 1e-6, "X coordinate of vertex 1 should be updated to 2.0");
            }
        }

        [TestMethod]
        public void HandleInvalidGraphOperations()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Test with invalid vertex data
                double[] vertices = new double[] {
                    0.0, 0.0, 0.0  // Incomplete vertex data - missing 2 components
                };
                
                int[] edgeConnections = new int[] { 0, 1 }; // Invalid reference to non-existent vertex 1
                
                // This should not crash but should handle the error gracefully
                try
                {
                    graph.CreateGraph(vertices, edgeConnections);
                    // If we get here, the operation didn't throw, but the graph should still be empty
                    Assert.AreEqual(0, graph.VertexCount, "Vertex count should be 0 after invalid creation attempt");
                }
                catch (Exception ex)
                {
                    // It's also acceptable if the API throws a proper exception
                    Console.WriteLine($"Expected exception: {ex.Message}");
                    Assert.IsTrue(ex is ArgumentException || ex is ZSpaceExternalException, 
                        "Should throw ArgumentException or ZSpaceExternalException");
                }
                
                // Test with null inputs
                try
                {
                    graph.CreateGraph(null, edgeConnections);
                    Assert.Fail("Should throw exception on null vertex array");
                }
                catch (ArgumentNullException)
                {
                    // Expected behavior
                }
                
                try
                {
                    graph.CreateGraph(vertices, null);
                    Assert.Fail("Should throw exception on null edge connections array");
                }
                catch (ArgumentNullException)
                {
                    // Expected behavior
                }
            }
        }

        #region Helper Methods

        private static void DiagnoseNativeLibrary()
        {
            if (_nativeLibraryDiagnosed)
                return;

            Console.WriteLine("Running native library diagnostics for graph tests...");
            
            string assemblyPath = typeof(zSpace.External.zExtGraph).Assembly.Location;
            string assemblyDir = Path.GetDirectoryName(assemblyPath);
            string dllPath = Path.Combine(assemblyDir, "zSpace_External.dll");
            
            Console.WriteLine($"Assembly directory: {assemblyDir}");
            
            if (File.Exists(dllPath))
            {
                Console.WriteLine($"DLL exists at: {dllPath}");
                Console.WriteLine($"File size: {new FileInfo(dllPath).Length} bytes");
                Console.WriteLine($"Last modified: {File.GetLastWriteTime(dllPath)}");
            }
            else
            {
                Console.WriteLine($"DLL does not exist at: {dllPath}");
            }
            
            _nativeLibraryDiagnosed = true;
        }

        #endregion
    }
} 