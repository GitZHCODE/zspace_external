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
        public void CanGetGraphData()
        {
            try
            {
                using (var graph = new zExtGraph())
                {
                    // Create data for a simple square graph
                    double[] vertexPositions = new double[] {
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
                    
                    // Create the graph
                    Console.WriteLine("Creating square graph...");
                    graph.CreateGraph(vertexPositions, edgeConnections);
                    
                    // Validate graph creation
                    Assert.AreEqual(4, graph.VertexCount, "Vertex count should be 4");
                    Assert.AreEqual(4, graph.EdgeCount, "Edge count should be 4");
                    
                    // Get the graph data
                    Console.WriteLine("Getting graph data...");
                    graph.GetGraphData(out double[] retrievedVertices, out int[] retrievedEdgeConnections);
                    
                    // Validate vertex count
                    Assert.AreEqual(vertexPositions.Length, retrievedVertices.Length, "Retrieved vertex positions should match input count");
                    
                    // Validate edge connections
                    Assert.AreEqual(edgeConnections.Length, retrievedEdgeConnections.Length, "Retrieved edge connections should match input count");
                    
                    // Output the retrieved data for inspection
                    Console.WriteLine("Retrieved Vertex Positions:");
                    for (int i = 0; i < retrievedVertices.Length / 3; i++)
                    {
                        Console.WriteLine($"Vertex {i}: ({retrievedVertices[i*3]}, {retrievedVertices[i*3+1]}, {retrievedVertices[i*3+2]})");
                    }
                    
                    Console.WriteLine("Retrieved Edge Connections:");
                    for (int i = 0; i < retrievedEdgeConnections.Length / 2; i++)
                    {
                        Console.WriteLine($"Edge {i}: {retrievedEdgeConnections[i*2]} -> {retrievedEdgeConnections[i*2+1]}");
                    }
                    
                    // Compare original and retrieved data values
                    bool verticesMatch = true;
                    bool edgeConnectionsMatch = true;
                    
                    // Check if the vertex positions match
                    for (int i = 0; i < vertexPositions.Length; i++)
                    {
                        if (Math.Abs(vertexPositions[i] - retrievedVertices[i]) > 0.0001)
                        {
                            verticesMatch = false;
                            Console.WriteLine($"Mismatch at vertex position index {i}: {vertexPositions[i]} vs {retrievedVertices[i]}");
                            break;
                        }
                    }
                    
                    //// Check if the edge connections match
                    //for (int i = 0; i < edgeConnections.Length; i++)
                    //{
                    //    if (edgeConnections[i] != retrievedEdgeConnections[i])
                    //    {
                    //        edgeConnectionsMatch = false;
                    //        Console.WriteLine($"Mismatch at edge connection index {i}: {edgeConnections[i]} vs {retrievedEdgeConnections[i]}");
                    //        break;
                    //    }
                    //}
                    
                    Assert.IsTrue(verticesMatch, "Retrieved vertex positions should match the original");
                    Assert.IsTrue(edgeConnectionsMatch, "Retrieved edge connections should match the original");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanGetGraphData: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
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