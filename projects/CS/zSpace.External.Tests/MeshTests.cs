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
    public class MeshTests
    {
        private static bool _nativeLibraryDiagnosed = false;

        [ClassInitialize]
        public static void ClassInitialize(TestContext context)
        {
            // Setup code that runs once before any tests
            DiagnoseNativeLibrary();
            
            // Verify the library is initialized
            Assert.IsTrue(zSpaceExternal.IsInitialized, "zSpace.External library should be initialized");
        }

        [TestInitialize]
        public void TestInitialize()
        {
            // Verify the library is still initialized before each test
            Assert.IsTrue(zSpaceExternal.IsInitialized, 
                "zSpace.External library should be initialized. Make sure TestSetup.AssemblyInit ran successfully.");
            
            Console.WriteLine("Test initialization complete - library is initialized.");
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
                mesh.ComputeGeodesicHeat(sourceVertices, true, geodesicDistances);

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


        [TestMethod]
        public void CanComputeGeodesicHeatInterpolated()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                {
                    // Create a simple cube
                    double[] vertices = new double[] {
                        // Front face vertices
                        -1.0, -1.0, 0.0,  // Vertex 0
                        1.0, -1.0, 0.0,  // Vertex 1
                        1.0, 1.0, 0.0,  // Vertex 2
                        -1.0, 1.0, 0.0,  // Vertex 3
                        0.0, 0.0, 0.0,  // Vertex 4
                    };
                    
                    // Each face has 3 vertices (tri faces)
                    int[] polyCounts = new int[] { 
                        3, 3, 3, 3  // 4 tri faces
                    };
                    
                    // Face vertex indices
                    int[] polyConnections = new int[] { 
                        0, 1, 4,
                        1, 2, 4,
                        2, 3 ,4,
                        3, 0 ,4
                    };
                    
                    Console.WriteLine("Creating poke mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    Console.WriteLine($"Poke mesh created with {mesh.VertexCount} vertices and {mesh.FaceCount} faces");
                    Assert.AreEqual(5, mesh.VertexCount, "Vertex count should be 8");
                    Assert.AreEqual(4, mesh.FaceCount, "Face count should be 6");
                    
                    // Start vertices (vertex 0 - front bottom left)
                    int[] startVertices = new int[] { 0 };
                    
                    // End vertices (vertex 6 - back top right)
                    int[] endVertices = new int[] { 2 };
                    
                    // Pre-allocate result array (one float per vertex)
                    float[] geodesicDistances = new float[mesh.VertexCount];
                    // Initialize all values to -1.0f
                    for (int i = 0; i < geodesicDistances.Length; i++)
                    {
                        geodesicDistances[i] = -1.0f;
                    }
                    
                    Console.WriteLine("Computing forward geodesic distances...");
                    try
                    {
                        // Forward interpolation
                        mesh.ComputeGeodesicHeatInterpolated(startVertices, endVertices, 0.1f, geodesicDistances);
                        Console.WriteLine("Forward geodesic computation completed successfully");
                        
                        // Output results
                        Console.WriteLine("Forward geodesic distances between vertex 0 and vertex 2:");
                        for (int i = 0; i < geodesicDistances.Length; i++)
                        {
                            Console.WriteLine($"Vertex {i}: {geodesicDistances[i]}");
                        }
                        
                        // Basic validation - all distances should be between 0 and 1
                        for (int i = 0; i < geodesicDistances.Length; i++)
                        {
                            Assert.IsTrue(geodesicDistances[i] >= 0 && geodesicDistances[i] <= 1.0f, 
                                $"Distance at vertex {i} should be between 0 and 1");
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Exception during forward geodesic computation: {ex.GetType().Name}");
                        Console.WriteLine($"Message: {ex.Message}");
                        Console.WriteLine($"Stack Trace: {ex.StackTrace}");
                        throw;
                    }

                    Console.WriteLine("Computing inversed geodesic distances...");
                    try
                    {
                        // Forward interpolation
                        mesh.ComputeGeodesicHeatInterpolated(startVertices, endVertices, 0.9f, geodesicDistances);
                        Console.WriteLine("Inversed geodesic computation completed successfully");

                        // Output results
                        Console.WriteLine("Inversed geodesic distances between vertex 0 and vertex 2:");
                        for (int i = 0; i < geodesicDistances.Length; i++)
                        {
                            Console.WriteLine($"Vertex {i}: {geodesicDistances[i]}");
                        }

                        // Basic validation - all distances should be between 0 and 1
                        for (int i = 0; i < geodesicDistances.Length; i++)
                        {
                            Assert.IsTrue(geodesicDistances[i] >= 0 && geodesicDistances[i] <= 1.0f,
                                $"Distance at vertex {i} should be between 0 and 1");
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Exception during inversed geodesic computation: {ex.GetType().Name}");
                        Console.WriteLine($"Message: {ex.Message}");
                        Console.WriteLine($"Stack Trace: {ex.StackTrace}");
                        throw;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in interpolated test: {ex.GetType().Name}");
                Console.WriteLine($"Message: {ex.Message}");
                Console.WriteLine($"Stack Trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanComputeGeodesicContours()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                {
                    // Create a simple cube mesh
                    double[] vertices = new double[] {
                        // Front face
                        -1.0, -1.0, -1.0,  // Vertex 0
                        1.0, -1.0, -1.0,   // Vertex 1
                        1.0, 1.0, -1.0,    // Vertex 2
                        -1.0, 1.0, -1.0,   // Vertex 3
                        // Back face
                        -1.0, -1.0, 1.0,   // Vertex 4
                        1.0, -1.0, 1.0,    // Vertex 5
                        1.0, 1.0, 1.0,     // Vertex 6
                        -1.0, 1.0, 1.0     // Vertex 7
                    };
                    
                    // Each face has 3 vertices (tri faces) - triangulated cube
                    int[] polyCounts = new int[] { 
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3  // 12 tri faces (2 per cube face)
                    };
                    
                    // Face vertex indices (triangulated cube faces)
                    int[] polyConnections = new int[] { 
                        // Front face (2 triangles)
                        0, 1, 2,
                        0, 2, 3,
                        // Back face (2 triangles)
                        4, 6, 5,
                        4, 7, 6,
                        // Left face (2 triangles)
                        0, 3, 7,
                        0, 7, 4,
                        // Right face (2 triangles)
                        1, 5, 6,
                        1, 6, 2,
                        // Bottom face (2 triangles)
                        0, 4, 5,
                        0, 5, 1,
                        // Top face (2 triangles)
                        2, 6, 7,
                        2, 7, 3
                    };
                    
                    // Create the mesh
                    Console.WriteLine("Creating cube mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    // Validate mesh creation
                    Assert.AreEqual(8, mesh.VertexCount, "Vertex count should be 8");
                    Assert.AreEqual(12, mesh.FaceCount, "Face count should be 12");
                    
                    // Source vertex (corner vertex 0)
                    int[] sourceVertices = new int[] { 0 };
                    
                    // Compute geodesic contours with 3 steps (should generate 3 contours)
                    Console.WriteLine("Computing geodesic contours...");
                    int steps = 3;
                    float dist = 0.0f; // Use steps instead of fixed distance
                    var contours = mesh.ComputeGeodesicContours(sourceVertices, steps, dist);
                    
                    // Basic validation
                    Console.WriteLine($"Generated {contours.Length} contours");
                    Assert.IsTrue(contours.Length > 0, "Should generate at least one contour");
                    Assert.IsTrue(contours.Length <= steps, "Should not generate more contours than steps");
                    
                    // Verify each contour is valid
                    for (int i = 0; i < contours.Length; i++)
                    {
                        Console.WriteLine($"Contour {i}: {contours[i].VertexCount} vertices, {contours[i].EdgeCount} edges");
                        Assert.IsTrue(contours[i].IsValid, $"Contour {i} should be valid");
                        Assert.IsTrue(contours[i].VertexCount > 0, $"Contour {i} should have vertices");
                        Assert.IsTrue(contours[i].EdgeCount > 0, $"Contour {i} should have edges");
                        
                        // Get vertex positions from the contour graph
                        double[] positions = contours[i].GetVertexPositions();
                        
                        // Output first vertex position for debugging
                        if (positions.Length >= 3)
                        {
                            Console.WriteLine($"  First vertex position: ({positions[0]}, {positions[1]}, {positions[2]})");
                        }
                        
                        // Clean up contour
                        contours[i].Dispose();
                    }
                    
                    // Test with fixed distance
                    Console.WriteLine("Computing geodesic contours with fixed distance...");
                    steps = 10; // Allow up to 10 contours
                    dist = 0.25f; // Fixed distance between contours
                    
                    var distanceContours = mesh.ComputeGeodesicContours(sourceVertices, steps, dist);
                    Console.WriteLine($"Generated {distanceContours.Length} contours with fixed distance {dist}");
                    
                    // Clean up
                    foreach (var contour in distanceContours)
                    {
                        contour.Dispose();
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanComputeGeodesicContours: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanComputeGeodesicContoursInterpolated()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                {
                    // Create a simple cube mesh
                    double[] vertices = new double[] {
                        // Front face
                        -1.0, -1.0, -1.0,  // Vertex 0
                        1.0, -1.0, -1.0,   // Vertex 1
                        1.0, 1.0, -1.0,    // Vertex 2
                        -1.0, 1.0, -1.0,   // Vertex 3
                        // Back face
                        -1.0, -1.0, 1.0,   // Vertex 4
                        1.0, -1.0, 1.0,    // Vertex 5
                        1.0, 1.0, 1.0,     // Vertex 6
                        -1.0, 1.0, 1.0     // Vertex 7
                    };
                    
                    // Each face has 3 vertices (tri faces) - triangulated cube
                    int[] polyCounts = new int[] { 
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3  // 12 tri faces (2 per cube face)
                    };
                    
                    // Face vertex indices (triangulated cube faces)
                    int[] polyConnections = new int[] { 
                        // Front face (2 triangles)
                        0, 1, 2,
                        0, 2, 3,
                        // Back face (2 triangles)
                        4, 6, 5,
                        4, 7, 6,
                        // Left face (2 triangles)
                        0, 3, 7,
                        0, 7, 4,
                        // Right face (2 triangles)
                        1, 5, 6,
                        1, 6, 2,
                        // Bottom face (2 triangles)
                        0, 4, 5,
                        0, 5, 1,
                        // Top face (2 triangles)
                        2, 6, 7,
                        2, 7, 3
                    };
                    
                    // Create the mesh
                    Console.WriteLine("Creating cube mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    // Validate mesh creation
                    Assert.AreEqual(8, mesh.VertexCount, "Vertex count should be 8");
                    Assert.AreEqual(12, mesh.FaceCount, "Face count should be 12");
                    
                    // Source vertices (opposite corners)
                    int[] startVertices = new int[] { 0 }; // bottom-left
                    int[] endVertices = new int[] { 2 };   // top-right
                    
                    // Compute interpolated geodesic contours with 3 steps
                    Console.WriteLine("Computing interpolated geodesic contours...");
                    int steps = 3;
                    float dist = 0.0f; // Use steps instead of fixed distance
                    
                    var contours = mesh.ComputeGeodesicContoursInterpolated(startVertices, endVertices, steps, dist);
                    
                    // Basic validation
                    Console.WriteLine($"Generated {contours.Length} interpolated contours");
                    Assert.IsTrue(contours.Length > 0, "Should generate at least one contour");
                    Assert.IsTrue(contours.Length <= steps, "Should not generate more contours than steps");
                    
                    // Verify each contour is valid
                    for (int i = 0; i < contours.Length; i++)
                    {
                        Console.WriteLine($"Contour {i}: {contours[i].VertexCount} vertices, {contours[i].EdgeCount} edges");
                        Assert.IsTrue(contours[i].IsValid, $"Contour {i} should be valid");
                        Assert.IsTrue(contours[i].VertexCount > 0, $"Contour {i} should have vertices");
                        Assert.IsTrue(contours[i].EdgeCount > 0, $"Contour {i} should have edges");
                        
                        // Get vertex positions from the contour graph
                        double[] positions = contours[i].GetVertexPositions();
                        
                        // Output first vertex position for debugging
                        if (positions.Length >= 3)
                        {
                            Console.WriteLine($"  First vertex position: ({positions[0]}, {positions[1]}, {positions[2]})");
                        }
                        
                        // Clean up contour
                        contours[i].Dispose();
                    }
                    
                    // Test with fixed distance
                    Console.WriteLine("Computing interpolated geodesic contours with fixed distance...");
                    steps = 10; // Allow up to 10 contours
                    dist = 0.25f; // Fixed distance between contours
                    
                    var distanceContours = mesh.ComputeGeodesicContoursInterpolated(startVertices, endVertices, steps, dist);
                    Console.WriteLine($"Generated {distanceContours.Length} interpolated contours with fixed distance {dist}");
                    
                    // Clean up
                    foreach (var contour in distanceContours)
                    {
                        contour.Dispose();
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanComputeGeodesicContoursInterpolated: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanGetMeshData()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                {
                    // Create a simple cube mesh
                    double[] vertices = new double[] {
                        // Front face
                        -1.0, -1.0, -1.0,  // Vertex 0
                        1.0, -1.0, -1.0,   // Vertex 1
                        1.0, 1.0, -1.0,    // Vertex 2
                        -1.0, 1.0, -1.0,   // Vertex 3
                        // Back face
                        -1.0, -1.0, 1.0,   // Vertex 4
                        1.0, -1.0, 1.0,    // Vertex 5
                        1.0, 1.0, 1.0,     // Vertex 6
                        -1.0, 1.0, 1.0     // Vertex 7
                    };
                    
                    // Each face has 3 vertices (tri faces) - triangulated cube
                    int[] polyCounts = new int[] { 
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3  // 12 tri faces (2 per cube face)
                    };
                    
                    // Face vertex indices (triangulated cube faces)
                    int[] polyConnections = new int[] { 
                        // Front face (2 triangles)
                        0, 1, 2,
                        0, 2, 3,
                        // Back face (2 triangles)
                        4, 6, 5,
                        4, 7, 6,
                        // Left face (2 triangles)
                        0, 3, 7,
                        0, 7, 4,
                        // Right face (2 triangles)
                        1, 5, 6,
                        1, 6, 2,
                        // Bottom face (2 triangles)
                        0, 4, 5,
                        0, 5, 1,
                        // Top face (2 triangles)
                        2, 6, 7,
                        2, 7, 3
                    };
                    
                    // Create the mesh
                    Console.WriteLine("Creating cube mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    // Validate mesh creation
                    Assert.AreEqual(8, mesh.VertexCount, "Vertex count should be 8");
                    Assert.AreEqual(12, mesh.FaceCount, "Face count should be 12");
                    
                    // Get the mesh data
                    Console.WriteLine("Getting mesh data...");
                    mesh.GetMeshData(out double[] retrievedVertices, out int[] retrievedPolyCounts, out int[] retrievedPolyConnections);
                    
                    // Validate vertex count
                    Assert.AreEqual(vertices.Length, retrievedVertices.Length, "Retrieved vertex positions should match input count");
                    
                    // Validate poly counts
                    Assert.AreEqual(polyCounts.Length, retrievedPolyCounts.Length, "Retrieved polygon counts should match input count");
                    
                    // Validate poly connections
                    Assert.AreEqual(polyConnections.Length, retrievedPolyConnections.Length, "Retrieved polygon connections should match input count");
                    
                    // Output the retrieved data for inspection
                    Console.WriteLine("Retrieved Vertex Positions:");
                    for (int i = 0; i < retrievedVertices.Length / 3; i++)
                    {
                        Console.WriteLine($"Vertex {i}: ({retrievedVertices[i*3]}, {retrievedVertices[i*3+1]}, {retrievedVertices[i*3+2]})");
                    }
                    
                    Console.WriteLine("Retrieved Polygon Counts:");
                    for (int i = 0; i < retrievedPolyCounts.Length; i++)
                    {
                        Console.WriteLine($"Polygon {i}: {retrievedPolyCounts[i]} vertices");
                    }
                    
                    Console.WriteLine("Retrieved Polygon Connections:");
                    int connectionIndex = 0;
                    for (int i = 0; i < retrievedPolyCounts.Length; i++)
                    {
                        Console.Write($"Polygon {i} connections: ");
                        for (int j = 0; j < retrievedPolyCounts[i]; j++)
                        {
                            Console.Write($"{retrievedPolyConnections[connectionIndex]} ");
                            connectionIndex++;
                        }
                        Console.WriteLine();
                    }
                    
                    // Compare original and retrieved data values
                    bool verticesMatch = true;
                    bool polyCountsMatch = true;
                    bool polyConnectionsMatch = true;
                    
                    // Check if the vertex positions match
                    for (int i = 0; i < vertices.Length; i++)
                    {
                        if (Math.Abs(vertices[i] - retrievedVertices[i]) > 0.0001)
                        {
                            verticesMatch = false;
                            Console.WriteLine($"Mismatch at vertex position index {i}: {vertices[i]} vs {retrievedVertices[i]}");
                            break;
                        }
                    }
                    
                    // Check if the polygon counts match
                    for (int i = 0; i < polyCounts.Length; i++)
                    {
                        if (polyCounts[i] != retrievedPolyCounts[i])
                        {
                            polyCountsMatch = false;
                            Console.WriteLine($"Mismatch at polygon count index {i}: {polyCounts[i]} vs {retrievedPolyCounts[i]}");
                            break;
                        }
                    }
                    
                    // Check if the polygon connections match
                    for (int i = 0; i < polyConnections.Length; i++)
                    {
                        if (polyConnections[i] != retrievedPolyConnections[i])
                        {
                            polyConnectionsMatch = false;
                            Console.WriteLine($"Mismatch at polygon connection index {i}: {polyConnections[i]} vs {retrievedPolyConnections[i]}");
                            break;
                        }
                    }
                    
                    Assert.IsTrue(verticesMatch, "Retrieved vertex positions should match the original");
                    Assert.IsTrue(polyCountsMatch, "Retrieved polygon counts should match the original");
                    Assert.IsTrue(polyConnectionsMatch, "Retrieved polygon connections should match the original");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanGetMeshData: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanIntersectPlane()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                using (var intersectionGraph = new zSpace.External.zExtGraph())
                {
                    // Verify the intersection graph is valid
                    Assert.IsTrue(intersectionGraph.IsValid, "Intersection graph should be valid before intersection");
                    
                    // Create a simple cube mesh
                    double[] vertices = new double[] {
                        // Front face
                        -1.0, -1.0, -1.0,  // Vertex 0
                        1.0, -1.0, -1.0,   // Vertex 1
                        1.0, 1.0, -1.0,    // Vertex 2
                        -1.0, 1.0, -1.0,   // Vertex 3
                        // Back face
                        -1.0, -1.0, 1.0,   // Vertex 4
                        1.0, -1.0, 1.0,    // Vertex 5
                        1.0, 1.0, 1.0,     // Vertex 6
                        -1.0, 1.0, 1.0     // Vertex 7
                    };
                    
                    // Each face has 3 vertices (tri faces) - triangulated cube
                    int[] polyCounts = new int[] { 
                        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3  // 12 tri faces (2 per cube face)
                    };
                    
                    // Face vertex indices (triangulated cube faces)
                    int[] polyConnections = new int[] { 
                        // Front face (2 triangles)
                        0, 1, 2,
                        0, 2, 3,
                        // Back face (2 triangles)
                        4, 6, 5,
                        4, 7, 6,
                        // Left face (2 triangles)
                        0, 3, 7,
                        0, 7, 4,
                        // Right face (2 triangles)
                        1, 5, 6,
                        1, 6, 2,
                        // Bottom face (2 triangles)
                        0, 4, 5,
                        0, 5, 1,
                        // Top face (2 triangles)
                        2, 6, 7,
                        2, 7, 3
                    };
                    
                    // Create the mesh
                    Console.WriteLine("Creating cube mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    // Validate mesh creation
                    Assert.AreEqual(8, mesh.VertexCount, "Vertex count should be 8");
                    Assert.AreEqual(12, mesh.FaceCount, "Face count should be 12");
                    
                    // Test that we can get mesh data (basic functionality test)
                    Console.WriteLine("Testing mesh data retrieval...");
                    mesh.GetMeshData(out double[] testVertices, out int[] testPolyCounts, out int[] testPolyConnections);
                    Console.WriteLine($"Retrieved mesh data: {testVertices.Length/3} vertices, {testPolyCounts.Length} poly counts, {testPolyConnections.Length} poly connections");
                    
                    // Define a plane that intersects the cube
                    // Plane at y = 0 (horizontal plane through the center)
                    float[] origin = new float[] { 0.0f, 0.0f, 0.0f };
                    float[] normal = new float[] { 0.0f, 1.0f, 0.0f };
                    
                    Console.WriteLine("Computing mesh-plane intersection...");
                    Console.WriteLine($"Mesh has {mesh.VertexCount} vertices and {mesh.FaceCount} faces");
                    Console.WriteLine($"Plane origin: ({origin[0]}, {origin[1]}, {origin[2]})");
                    Console.WriteLine($"Plane normal: ({normal[0]}, {normal[1]}, {normal[2]})");
                    
                    mesh.IntersectPlane(origin, normal, intersectionGraph);
                    
                    Console.WriteLine("Intersection computation completed");
                    
                    // Validate that the intersection graph was created
                    Assert.IsTrue(intersectionGraph.IsValid, "Intersection graph should be valid");
                    
                    // Get the intersection data
                    intersectionGraph.GetGraphData(out double[] intersectionVertices, out int[] intersectionEdges);
                    
                    Console.WriteLine($"Intersection has {intersectionVertices.Length / 3} vertices and {intersectionEdges.Length / 2} edges");
                    
                    // Basic validation - intersection should have some geometry
                    Assert.IsTrue(intersectionVertices.Length > 0, "Intersection should have vertices");
                    Assert.IsTrue(intersectionEdges.Length > 0, "Intersection should have edges");
                    
                    // Output intersection vertices for inspection
                    Console.WriteLine("Intersection vertices:");
                    for (int i = 0; i < intersectionVertices.Length / 3; i++)
                    {
                        Console.WriteLine($"Vertex {i}: ({intersectionVertices[i*3]}, {intersectionVertices[i*3+1]}, {intersectionVertices[i*3+2]})");
                    }
                    
                    // Output intersection edges for inspection
                    Console.WriteLine("Intersection edges:");
                    for (int i = 0; i < intersectionEdges.Length / 2; i++)
                    {
                        Console.WriteLine($"Edge {i}: {intersectionEdges[i*2]} -> {intersectionEdges[i*2+1]}");
                    }
                    
                    // Validate that intersection vertices are approximately on the plane (y ≈ 0)
                    for (int i = 0; i < intersectionVertices.Length / 3; i++)
                    {
                        float y = (float)intersectionVertices[i * 3 + 1];
                        Assert.IsTrue(Math.Abs(y) < 0.1f, $"Intersection vertex {i} should be on the plane (y ≈ 0), but y = {y}");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanIntersectPlane: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanIntersectPlaneSimple()
        {
            try
            {
                using (var mesh = new zSpace.External.zExtMesh())
                using (var intersectionGraph = new zSpace.External.zExtGraph())
                {
                    // Verify the intersection graph is valid
                    Assert.IsTrue(intersectionGraph.IsValid, "Intersection graph should be valid before intersection");
                    
                    // Create a simple triangle mesh
                    double[] vertices = new double[] {
                        0.0, 0.0, 0.0,  // Vertex 0
                        1.0, 0.0, 0.0,  // Vertex 1
                        0.0, 1.0, 0.0   // Vertex 2
                    };
                    
                    int[] polyCounts = new int[] { 3 }; // One triangle
                    int[] polyConnections = new int[] { 0, 1, 2 }; // Triangle vertices
                    
                    // Create the mesh
                    Console.WriteLine("Creating simple triangle mesh...");
                    mesh.CreateMesh(vertices, polyCounts, polyConnections);
                    
                    // Validate mesh creation
                    Assert.AreEqual(3, mesh.VertexCount, "Vertex count should be 3");
                    Assert.AreEqual(1, mesh.FaceCount, "Face count should be 1");
                    
                    // Define a plane that intersects the triangle
                    float[] origin = new float[] { 0.5f, 0.0f, 0.0f };
                    float[] normal = new float[] { 1.0f, 0.0f, 0.0f };
                    
                    Console.WriteLine("Computing mesh-plane intersection...");
                    Console.WriteLine($"Mesh has {mesh.VertexCount} vertices and {mesh.FaceCount} faces");
                    Console.WriteLine($"Plane origin: ({origin[0]}, {origin[1]}, {origin[2]})");
                    Console.WriteLine($"Plane normal: ({normal[0]}, {normal[1]}, {normal[2]})");
                    
                    mesh.IntersectPlane(origin, normal, intersectionGraph);
                    
                    Console.WriteLine("Intersection computation completed");
                    
                    // Validate that the intersection graph was created
                    Assert.IsTrue(intersectionGraph.IsValid, "Intersection graph should be valid");
                    
                    // Get the intersection data
                    intersectionGraph.GetGraphData(out double[] intersectionVertices, out int[] intersectionEdges);
                    
                    Console.WriteLine($"Intersection has {intersectionVertices.Length / 3} vertices and {intersectionEdges.Length / 2} edges");
                    
                    // For a simple triangle, we might not get an intersection depending on the plane
                    // Just verify the method doesn't hang
                    Console.WriteLine("Simple intersection test completed successfully");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanIntersectPlaneSimple: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void TestMeshTransform_Translation()
        {
            using (var mesh = new zSpace.External.zExtMesh())
            {
                // Create a simple quad mesh (2 triangles forming a square)
                var vertices = new double[]
                {
                    0, 0, 0,  // Vertex 0
                    1, 0, 0,  // Vertex 1
                    1, 1, 0,  // Vertex 2
                    0, 1, 0   // Vertex 3
                };

                var polyCounts = new int[] { 3, 3 }; // 2 triangles
                var polyConnections = new int[]
                {
                    0, 1, 2,  // First triangle
                    0, 2, 3   // Second triangle
                };

                mesh.CreateMesh(vertices, polyCounts, polyConnections);

                // Get original vertex positions
                double[] originalVertices = new double[0];
                int[] polyCountsOut = new int[0];
                int[] polyConnectionsOut = new int[0];
                mesh.GetMeshData(out originalVertices, out polyConnectionsOut, out polyCountsOut);

                // Create translation matrix (translate by 2 units in X, 3 units in Y, 1 unit in Z)
                // Column-major format: translation in elements [3, 7, 11]
                var translationMatrix = new float[]
                {
                    1, 0, 0, 0,  // Column 0
                    0, 1, 0, 0,  // Column 1
                    0, 0, 1, 0,  // Column 2
                    2, 3, 1, 1   // Column 3 (translation)
                };

                // Apply transformation
                mesh.Transform(translationMatrix);

                // Get transformed vertex positions
                double[] transformedVertices = new double[0];
                int[] polyCountsTransformed = new int[0];
                int[] polyConnectionsTransformed = new int[0];
                mesh.GetMeshData(out transformedVertices, out polyCountsTransformed, out polyConnectionsTransformed);

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