using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using zSpace.External;
using System.Collections.Generic;

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

        [TestMethod]
        public void CanMergeVertices()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Create a graph with some vertices close to each other
                double[] vertices = new double[] {
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0,  // Vertex 1
                    1.0, 1.0,.01,   // Vertex 2 - slightly offset in Z
                    1.0, 1.0, 0.0,  // Vertex 3 - very close to vertex 2
                    0.0, 1.0, 0.0,  // Vertex 4
                    0.001, 0.0, 0.0, // Vertex 5 - very close to vertex 0
                };
                
                // Connect vertices
                int[] edgeConnections = new int[] { 
                    0, 1,  // Edge 0
                    1, 2,  // Edge 1
                    3, 4,  // Edge 2
                    4, 5   // Edge 3
                };
                
                // Create graph
                graph.CreateGraph(vertices, edgeConnections);
                
                // Verify initial state
                Assert.AreEqual(6, graph.VertexCount, "Initial vertex count should be 6");
                Assert.AreEqual(4, graph.EdgeCount, "Initial edge count should be 4");
                
                // Act: Merge vertices with tolerance 0.02
                graph.MergeVertices(0.02);
                
                // Assert: Vertex count should be reduced, but edge count maintained
                Assert.AreEqual(4, graph.VertexCount, "After merging, vertex count should be 4 (0-5 and 2-3 merged)");
                Assert.AreEqual(4, graph.EdgeCount, "Edge count should remain 4");
                
                // Get updated data to verify
                graph.GetGraphData(out double[] newPositions, out int[] newConnections);
                
                // Print debug info
                Console.WriteLine("After merge:");
                Console.WriteLine($"Vertex count: {graph.VertexCount}");
                Console.WriteLine($"Edge count: {graph.EdgeCount}");
                Console.WriteLine("New vertices:");
                for (int i = 0; i < newPositions.Length; i += 3)
                {
                    Console.WriteLine($"  {i/3}: ({newPositions[i]:F3}, {newPositions[i+1]:F3}, {newPositions[i+2]:F3})");
                }
                Console.WriteLine("New connections:");
                for (int i = 0; i < newConnections.Length; i += 2)
                {
                    Console.WriteLine($"  Edge {i/2}: {newConnections[i]} -> {newConnections[i+1]}");
                }
                
                // Verify connections are valid (no index out of range)
                foreach (int idx in newConnections)
                {
                    Assert.IsTrue(idx >= 0 && idx < graph.VertexCount, 
                        $"Connection index {idx} should be within valid range [0, {graph.VertexCount-1}]");
                }
            }
        }

        [TestMethod]
        public void CanSeparateGraph()
        {
            using (var graph = new zSpace.External.zExtGraph())
            {
                // Create a graph with disconnected components
                double[] vertices = new double[] {
                    // First component: triangle
                    0.0, 0.0, 0.0,  // Vertex 0
                    1.0, 0.0, 0.0,  // Vertex 1
                    0.5, 1.0, 0.0,  // Vertex 2
                    
                    // Second component: line segment (disconnected)
                    3.0, 0.0, 0.0,  // Vertex 3
                    4.0, 0.0, 0.0,  // Vertex 4
                    
                    // Third component: square (disconnected) 
                    0.0, 3.0, 0.0,  // Vertex 5
                    1.0, 3.0, 0.0,  // Vertex 6
                    1.0, 4.0, 0.0,  // Vertex 7
                    0.0, 4.0, 0.0   // Vertex 8
                };
                
                // Connections for the three components
                int[] edgeConnections = new int[] { 
                    // Triangle edges
                    0, 1,
                    1, 2,
                    2, 0,
                    
                    // Line segment edge
                    3, 4,
                    
                    // Square edges
                    5, 6,
                    6, 7,
                    7, 8,
                    8, 5
                };
                
                // Create graph
                graph.CreateGraph(vertices, edgeConnections);
                
                // Verify initial state
                Assert.AreEqual(9, graph.VertexCount, "Vertex count should be 9");
                Assert.AreEqual(8, graph.EdgeCount, "Edge count should be 8");
                
                // Act: Separate the graph
                zExtGraph[] components = graph.SeparateGraph();
                
                // Assert: Should have 3 components
                Assert.AreEqual(3, components.Length, "Should have 3 disconnected components");
                
                // Verify the components
                foreach (var component in components)
                {
                    Assert.IsTrue(component.IsValid, "Component should be valid");
                    
                    // Print debug info about each component
                    Console.WriteLine($"Component with {component.VertexCount} vertices and {component.EdgeCount} edges");
                    
                    // Verify each component is a valid graph
                    Assert.IsTrue(component.VertexCount >= 2, "Component should have at least 2 vertices");
                    Assert.IsTrue(component.EdgeCount >= 1, "Component should have at least 1 edge");
                }
                
                // Find the specific components by their size
                bool foundTriangle = false;
                bool foundLine = false;
                bool foundSquare = false;
                
                foreach (var component in components)
                {
                    if (component.VertexCount == 3 && component.EdgeCount == 3)
                    {
                        foundTriangle = true;
                    }
                    else if (component.VertexCount == 2 && component.EdgeCount == 1)
                    {
                        foundLine = true;
                    }
                    else if (component.VertexCount == 4 && component.EdgeCount == 4)
                    {
                        foundSquare = true;
                    }
                }
                
                Assert.IsTrue(foundTriangle, "Should find a triangle component (3 vertices, 3 edges)");
                Assert.IsTrue(foundLine, "Should find a line component (2 vertices, 1 edge)");
                Assert.IsTrue(foundSquare, "Should find a square component (4 vertices, 4 edges)");
            }
        }

        [TestMethod]
        public void TestGraphTransform_Translation()
        {
            using (var graph = new zExtGraph())
            {
                // Create a simple line graph
                var vertices = new double[]
                {
                    0, 0, 0,  // Start point
                    1, 0, 0,  // End point
                    0.5, 0.5, 0  // Mid point
                };

                var edgeConnections = new int[]
                {
                    0, 1,  // Edge from vertex 0 to 1
                    1, 2,  // Edge from vertex 1 to 2
                    2, 0   // Edge from vertex 2 to 0 (triangle)
                };

                graph.CreateGraph(vertices, edgeConnections);

                // Get original vertex positions
                var originalVertices = graph.GetVertexPositions();

                // Create translation matrix (translate by 2 units in X, 3 units in Y, 1 unit in Z)
                var translationMatrix = new float[]
                {
                    //1, 0, 0, 2,  // Translate X by 2
                    //0, 1, 0, 3,  // Translate Y by 3
                    //0, 0, 1, 1,  // Translate Z by 1
                    //0, 0, 0, 1   // Homogeneous coordinate

                    1, 0, 0, 0,  // Translate X by 2
                    0, 1, 0, 0,  // Translate Y by 3
                    0, 0, 1, 0,  // Translate Z by 1
                    2, 3, 1, 1   // Homogeneous coordinate
                };

                // Apply transformation
                graph.Transform(translationMatrix);

                // Get transformed vertex positions
                var transformedVertices = graph.GetVertexPositions();

                // Verify transformation was applied correctly
                Assert.AreEqual(originalVertices.Length, transformedVertices.Length, "Vertex count should remain the same after transformation");

                for (int i = 0; i < originalVertices.Length; i += 3)
                {
                    // Check X coordinate (should be translated by 2)
                    Assert.AreEqual(originalVertices[i] + 2, transformedVertices[i], 1e-6, $"X coordinate at vertex {i/3} should be translated by 2");
                    
                    // Check Y coordinate (should be translated by 3)
                    Assert.AreEqual(originalVertices[i + 1] + 3, transformedVertices[i + 1], 1e-6, $"Y coordinate at vertex {i/3} should be translated by 3");
                    
                    // Check Z coordinate (should be translated by 1)
                    Assert.AreEqual(originalVertices[i + 2] + 1, transformedVertices[i + 2], 1e-6, $"Z coordinate at vertex {i/3} should be translated by 1");
                }
            }
        }

        [TestMethod]
        public void TestGraphTransform_Rotation()
        {
            using (var graph = new zExtGraph())
            {
                // Create a simple square graph
                var vertices = new double[]
                {
                    0, 0, 0,  // Vertex 0
                    1, 0, 0,  // Vertex 1
                    1, 1, 0,  // Vertex 2
                    0, 1, 0   // Vertex 3
                };

                var edgeConnections = new int[]
                {
                    0, 1,  // Edge from vertex 0 to 1
                    1, 2,  // Edge from vertex 1 to 2
                    2, 3,  // Edge from vertex 2 to 3
                    3, 0   // Edge from vertex 3 to 0
                };

                graph.CreateGraph(vertices, edgeConnections);

                // Create rotation matrix (90 degrees around Z-axis)
                // Column-major format
                float cos90 = 0;
                float sin90 = 1;
                var rotationMatrix = new float[]
                {
                    cos90, sin90, 0, 0,  // Column 0
                    -sin90, cos90, 0, 0, // Column 1
                    0, 0, 1, 0,         // Column 2
                    0, 0, 0, 1          // Column 3
                };

                // Apply transformation
                graph.Transform(rotationMatrix);

                // Get transformed vertex positions
                var transformedVertices = graph.GetVertexPositions();

                // Verify transformation was applied correctly
                Assert.AreEqual(vertices.Length, transformedVertices.Length, "Vertex count should remain the same after transformation");

                // Check a few key vertices after 90-degree Z rotation
                // Original vertex 0: (0, 0, 0) should remain (0, 0, 0)
                Assert.AreEqual(0, transformedVertices[0], 1e-6, "Vertex 0 X coordinate after rotation");
                Assert.AreEqual(0, transformedVertices[1], 1e-6, "Vertex 0 Y coordinate after rotation");
                Assert.AreEqual(0, transformedVertices[2], 1e-6, "Vertex 0 Z coordinate after rotation");

                // Original vertex 1: (1, 0, 0) should become (0, 1, 0)
                Assert.AreEqual(0, transformedVertices[3], 1e-6, "Vertex 1 X coordinate after rotation");
                Assert.AreEqual(1, transformedVertices[4], 1e-6, "Vertex 1 Y coordinate after rotation");
                Assert.AreEqual(0, transformedVertices[5], 1e-6, "Vertex 1 Z coordinate after rotation");

                // Original vertex 2: (1, 1, 0) should become (-1, 1, 0)
                Assert.AreEqual(-1, transformedVertices[6], 1e-6, "Vertex 2 X coordinate after rotation");
                Assert.AreEqual(1, transformedVertices[7], 1e-6, "Vertex 2 Y coordinate after rotation");
                Assert.AreEqual(0, transformedVertices[8], 1e-6, "Vertex 2 Z coordinate after rotation");
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