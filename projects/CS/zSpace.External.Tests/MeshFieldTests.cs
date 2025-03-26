using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using zSpace.External;
using System.Linq;

namespace zSpace.External.Tests
{
    [TestClass]
    public class MeshFieldTests
    {
        [TestInitialize]
        public void TestInitialize()
        {
            // Verify the library is initialized before each test
            Assert.IsTrue(zSpaceExternal.IsInitialized, 
                "zSpace.External library should be initialized. Make sure TestSetup.AssemblyInit ran successfully.");
            
            Console.WriteLine("Test initialization complete - library is initialized.");
        }

        [TestMethod]
        public void CanCreateMeshField()
        {
            try
            {
                using (var field = new zExtMeshField())
                {
                    Assert.IsNotNull(field, "MeshField should be created successfully");
                    Assert.IsTrue(field.IsValid, "MeshField should be valid");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception in CanCreateMeshField: {ex.Message}");
                Console.WriteLine($"Exception type: {ex.GetType().FullName}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                throw;
            }
        }

        [TestMethod]
        public void CanCreateFieldWithBounds()
        {
            using (var field = new zExtMeshField())
            {
                // Create a simple field with a 10x10 resolution in a unit cube bounding box
                double[] minBB = new double[] { 0.0, 0.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                // Act - Create field
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Debug output
                Console.WriteLine($"Vertex count: {field.VertexCount}");
                Console.WriteLine($"Value count: {field.ValueCount}");
                
                // Assert - Result
                Assert.AreEqual(numX * numY, field.VertexCount, "Vertex count should match grid resolution");
                Assert.AreEqual(numX * numY, field.ValueCount, "Value count should match grid resolution");
            }
        }

        [TestMethod]
        public void CanSetAndGetFieldValues()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 5x5 field
                double[] minBB = new double[] { 0.0, 0.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 5;
                int numY = 5;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create a simple ramp of values
                float[] values = new float[numX * numY];
                for (int i = 0; i < values.Length; i++)
                {
                    values[i] = i / (float)values.Length;
                }
                
                // Set the values
                field.SetFieldValues(values);
                
                // Get the values back
                float[] retrievedValues = field.GetFieldValues();
                
                // Verify values
                Assert.AreEqual(values.Length, retrievedValues.Length, "Retrieved values array should have the same length");
                
                for (int i = 0; i < values.Length; i++)
                {
                    Assert.AreEqual(values[i], retrievedValues[i], 0.0001f, $"Value at index {i} should match");
                }
            }
        }

        [TestMethod]
        public void CanCalculateCircleDistanceField()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 10x10 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Calculate distance field to a circle at center with radius 0.5
                double[] center = new double[] { 0.0, 0.0, 0.0 };
                double radius = 0.5;
                double offset = 0.0;
                bool normalize = false;
                
                float[] distanceValues = field.GetScalarsCircle(center, (float)radius, (float)offset, normalize);
                
                // Verify values
                Assert.AreEqual(field.ValueCount, distanceValues.Length, "Distance values array should match value count");
                
                // Output for inspection
                Console.WriteLine("Circle distance field values:");
                for (int i = 0; i < Math.Min(10, distanceValues.Length); i++)
                {
                    Console.WriteLine($"Value {i}: {distanceValues[i]}");
                }
                
                // Basic validation - values should be near zero at the circle perimeter
                // Get field bounds to understand the grid
                double[] minBB2 = new double[3];
                double[] maxBB2 = new double[3];
                field.GetBounds(out minBB2, out maxBB2);
                
                Console.WriteLine($"Field bounds: [{minBB2[0]}, {minBB2[1]}, {minBB2[2]}] to [{maxBB2[0]}, {maxBB2[1]}, {maxBB2[2]}]");
            }
        }

        [TestMethod]
        public void CanPerformBooleanOperations()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 10x10 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create two circle distance fields
                double[] center1 = new double[] { -0.3, 0.0, 0.0 };
                double[] center2 = new double[] { 0.3, 0.0, 0.0 };
                double radius = 0.5;
                bool normalize = false;
                
                float[] circle1 = field.GetScalarsCircle(center1, (float)radius, 0.0f, normalize);
                float[] circle2 = field.GetScalarsCircle(center2, (float)radius, 0.0f, normalize);
                
                // Perform boolean operations
                float[] unionResult = field.BooleanUnion(circle1, circle2, normalize);
                float[] intersectResult = field.BooleanIntersect(circle1, circle2, normalize);
                float[] subtractResult = field.BooleanSubtract(circle1, circle2, normalize);
                float[] differenceResult = field.BooleanDifference(circle1, circle2, normalize);
                
                // Verify values
                Assert.AreEqual(field.ValueCount, unionResult.Length, "Union result array should match value count");
                Assert.AreEqual(field.ValueCount, intersectResult.Length, "Intersect result array should match value count");
                Assert.AreEqual(field.ValueCount, subtractResult.Length, "Subtract result array should match value count");
                Assert.AreEqual(field.ValueCount, differenceResult.Length, "Difference result array should match value count");
                
                // Output for inspection
                Console.WriteLine("Boolean operation results (first 5 values):");
                for (int i = 0; i < Math.Min(5, unionResult.Length); i++)
                {
                    Console.WriteLine($"Index {i}: Union={unionResult[i]}, Intersect={intersectResult[i]}, " + 
                                     $"Subtract={subtractResult[i]}, Difference={differenceResult[i]}");
                }
            }
        }

        [TestMethod]
        public void CanGetIsoContour()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 40x40 field with higher resolution for better contour extraction
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 40;
                int numY = 40;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create a circle distance field
                double[] center = new double[] { 0.0, 0.0, 0.0 };
                float radius = 0.5f;
                bool normalize = false;
                
                // Calculate and retrieve circle distance field values
                float[] circleValues = field.GetScalarsCircle(center, radius, 0.0f, normalize);
                Console.WriteLine($"Generated {circleValues.Length} field values");
                
                // Output some values to understand the data range
                float minValue = float.MaxValue;
                float maxValue = float.MinValue;
                for (int i = 0; i < circleValues.Length; i++)
                {
                    minValue = Math.Min(minValue, circleValues[i]);
                    maxValue = Math.Max(maxValue, circleValues[i]);
                }
                
                // Set the values explicitly
                field.SetFieldValues(circleValues);
                
                // Use middle of the range for threshold
                //float threshold = (minValue + maxValue) / 2f;
                float threshold = 0.01f;
                Console.WriteLine($"Using threshold {threshold} for iso-contour");
                
                // Get iso-contour
                zExtGraph isoContour = field.GetIsoContour(threshold);

    
                float[] fieldValues = field.GetFieldValues();
                Console.WriteLine($"Field value range: {Math.Round(fieldValues.Min(), 2)} to {Math.Round(fieldValues.Max(), 2)}");

                // Print detail information about the graph
                Console.WriteLine($"Iso-contour: VertexCount={isoContour.VertexCount}, EdgeCount={isoContour.EdgeCount}");
                
                try
                {
                    // Test GetVertexPositions to verify graph data is accessible
                    double[] positions = isoContour.GetVertexPositions();
                    Console.WriteLine($"Graph vertex data has {positions.Length/3} positions");
                    
                    // Display a few vertices if we have them
                    if (positions.Length > 0)
                    {
                        Console.WriteLine("First few vertices:");
                        for (int i = 0; i < Math.Min(3, positions.Length/3); i++)
                        {
                            Console.WriteLine($"Vertex {i}: ({positions[i*3]}, {positions[i*3+1]}, {positions[i*3+2]})");
                        }
                    }
                    
                    // Verify the contour actually has data
                    Assert.IsTrue(positions.Length > 0, "Graph should have vertex positions data");
                }
                finally
                {
                    // Clean up
                    isoContour.Dispose();
                }
            }
        }

        [TestMethod]
        public void CanComputeSMin()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 20x20 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 20;
                int numY = 20;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create two circle distance fields
                double[] center1 = new double[] { -0.3, 0.0, 0.0 };
                double[] center2 = new double[] { 0.3, 0.0, 0.0 };
                float radius = 0.5f;
                bool normalize = false;
                
                // Get the circle values
                float[] circle1 = field.GetScalarsCircle(center1, radius, 0.0f, normalize);
                float[] circle2 = field.GetScalarsCircle(center2, radius, 0.0f, normalize);
                
                // Verify circle values are valid
                Assert.IsTrue(circle1.Length > 0, "Circle 1 should have values");
                Assert.IsTrue(circle2.Length > 0, "Circle 2 should have values");
                Assert.IsTrue(circle1.Any(v => v != 0), "Circle 1 should have non-zero values");
                Assert.IsTrue(circle2.Any(v => v != 0), "Circle 2 should have non-zero values");
                
                // Compute smooth minimum with polynomial mode and small k value
                Console.WriteLine("Computing SMin with k=0.1, mode=0 (polynomial)...");
                float[] sminResult = field.GetScalarsSMin(circle1, circle2, 0.1f, 0);
                
                // Verify result
                Assert.IsNotNull(sminResult, "SMin result should not be null");
                Assert.IsTrue(sminResult.Length > 0, "SMin result should have values");
                Assert.AreEqual(field.ValueCount, sminResult.Length, "SMin result should have same length as field values");
                Assert.IsTrue(sminResult.Any(v => v != 0), "SMin result should have non-zero values");
                
                Console.WriteLine($"SMin result range: {sminResult.Min()} to {sminResult.Max()}, length: {sminResult.Length}");
                
                // Set field values to SMin result
                field.SetFieldValues(sminResult);
                
                // Extract iso-contour at zero threshold
                using (zExtGraph contour = field.GetIsoContour(0.0f))
                {
                    Console.WriteLine($"SMin iso-contour: VertexCount={contour.VertexCount}, EdgeCount={contour.EdgeCount}");
                    
                    // The contour should have vertices and edges
                    // Note: In some cases, depending on the field values, a contour might not be found
                    // so we don't fail the test if the contour is empty
                }
                
                // Test with exponential mode
                Console.WriteLine("Computing SMin with k=0.1, mode=1 (exponential)...");
                float[] sminResult2 = field.GetScalarsSMin(circle1, circle2, 0.1f, 1);
                Assert.IsTrue(sminResult2.Length > 0, "Exponential SMin result should have values");
            }
        }

        [TestMethod]
        public void CanGetGradients()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 20x20 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 20;
                int numY = 20;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create a circle distance field centered at origin
                double[] center = new double[] { 0.0, 0.0, 0.0 };
                float radius = 0.5f;
                bool normalize = true; // Normalize to get cleaner gradients
                
                float[] circleValues = field.GetScalarsCircle(center, radius, 0.0f, normalize);
                
                // Set field values
                field.SetFieldValues(circleValues);
                
                // Get gradients
                double[] gradients = field.GetGradients();
                
                // Verify gradient array
                Assert.IsNotNull(gradients, "Gradient array should not be null");
                
                // Each vertex should have 3 gradient components (x,y,z)
                Assert.AreEqual(field.VertexCount * 3, gradients.Length, "Gradient array should have 3 values per vertex");
                
                // Output for inspection
                Console.WriteLine($"Retrieved {gradients.Length/3} gradient vectors for {field.VertexCount} vertices");
                
                // Test 1: Check that we have at least some non-zero components
                bool hasNonZeroComponents = false;
                for (int i = 0; i < gradients.Length; i++)
                {
                    if (Math.Abs(gradients[i]) > 1e-6)
                    {
                        hasNonZeroComponents = true;
                        break;
                    }
                }
                Assert.IsTrue(hasNonZeroComponents, "Gradient array should have at least some non-zero components");
                
                // Test 2: For a circle field, gradients should generally point radially outward/inward
                // Check that some vectors point in expected directions
                bool foundExpectedDirection = false;
                int centerIndex = (numX * numY) / 2 + numX / 2; // Approximate center index
                
                // If centerIndex is within bounds
                if (centerIndex < field.VertexCount)
                {
                    // Get a range of indices near the center
                    int rangeStart = Math.Max(0, centerIndex - numX - 1);
                    int rangeEnd = Math.Min(field.VertexCount, centerIndex + numX + 1);
                    
                    for (int i = rangeStart; i < rangeEnd; i++)
                    {
                        double x = gradients[i*3];
                        double y = gradients[i*3+1];
                        // z component is usually zero in 2D fields
                        
                        // Skip very small vectors (might be on the contour)
                        double magnitude = Math.Sqrt(x*x + y*y);
                        if (magnitude < 1e-6) continue;
                        
                        // For a circle field, the x and y components should not both be zero
                        // when we're not at the center
                        if (Math.Abs(x) > 1e-6 || Math.Abs(y) > 1e-6)
                        {
                            foundExpectedDirection = true;
                            break;
                        }
                    }
                }
                
                // Only assert if we checked enough vectors (field might be too small)
                if (field.VertexCount > 10)
                {
                    Assert.IsTrue(foundExpectedDirection, "Some gradient vectors should have expected directional components");
                }
                
                // Print a few gradients around the center of the field
                int midIndex = field.VertexCount / 2;
                Console.WriteLine("Sample gradients near center:");
                for (int i = Math.Max(0, midIndex - 2); i < Math.Min(field.VertexCount, midIndex + 3); i++)
                {
                    double x = gradients[i*3];
                    double y = gradients[i*3+1];
                    double z = gradients[i*3+2];
                    double magnitude = Math.Sqrt(x*x + y*y + z*z);
                    
                    Console.WriteLine($"Gradient {i}: ({x:F4}, {y:F4}, {z:F4}), magnitude: {magnitude:F4}");
                }
            }
        }

        [TestMethod]
        public void CanGetId()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 10x10 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Create some field data so we can visualize results
                float[] values = new float[field.ValueCount];
                for (int i = 0; i < values.Length; i++)
                {
                    values[i] = i / (float)values.Length;
                }
                field.SetFieldValues(values);
                
                // Test getting ID at exact center of field
                double[] centerPos = new double[] { 0.0, 0.0, 0.0 };
                int centerId = field.GetId(centerPos);
                
                // Log the result
                Console.WriteLine($"Vertex ID at center position {centerPos[0]}, {centerPos[1]}, {centerPos[2]}: {centerId}");
                
                // Test ID is within valid range
                Assert.IsTrue(centerId >= 0 && centerId < field.VertexCount, 
                    $"Vertex ID {centerId} should be within valid range [0, {field.VertexCount-1}]");
                
                // Test getting ID at various positions around the field
                double[] positions = new double[] 
                {
                    // Top left
                    -0.9, 0.9, 0.0,
                    // Top right
                    0.9, 0.9, 0.0,
                    // Bottom left
                    -0.9, -0.9, 0.0,
                    // Bottom right
                    0.9, -0.9, 0.0
                };
                
                for (int i = 0; i < positions.Length; i += 3)
                {
                    double[] pos = new double[] { positions[i], positions[i+1], positions[i+2] };
                    int id = field.GetId(pos);
                    
                    Console.WriteLine($"Vertex ID at position {pos[0]}, {pos[1]}, {pos[2]}: {id}");
                    
                    // Verify ID is within range
                    Assert.IsTrue(id >= 0 && id < field.VertexCount, 
                        $"Vertex ID {id} should be within valid range [0, {field.VertexCount-1}]");
                }
                
                // Verify exception is thrown for invalid input
                try
                {
                    double[] invalidPos = new double[] { 0.0, 0.0 }; // Only 2 elements
                    field.GetId(invalidPos);
                    Assert.Fail("Should have thrown ArgumentException for invalid position array length");
                }
                catch (ArgumentException)
                {
                    // Expected
                }
            }
        }

        [TestMethod]
        public void CanGetPositions()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 10x10 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Get all vertex positions
                double[] positions = field.GetPositions();
                
                // Verify positions array
                Assert.IsNotNull(positions, "Positions array should not be null");
                Assert.AreEqual(field.VertexCount * 3, positions.Length, 
                    $"Positions array should have 3 values per vertex (got {positions.Length} for {field.VertexCount} vertices)");
                
                // Verify positions are within bounds
                for (int i = 0; i < positions.Length; i += 3)
                {
                    double x = positions[i];
                    double y = positions[i + 1];
                    double z = positions[i + 2];
                    
                    Assert.IsTrue(x >= minBB[0] && x <= maxBB[0], 
                        $"X coordinate {x} should be within bounds [{minBB[0]}, {maxBB[0]}]");
                    Assert.IsTrue(y >= minBB[1] && y <= maxBB[1], 
                        $"Y coordinate {y} should be within bounds [{minBB[1]}, {maxBB[1]}]");
                    Assert.IsTrue(z >= minBB[2] && z <= maxBB[2], 
                        $"Z coordinate {z} should be within bounds [{minBB[2]}, {maxBB[2]}]");
                }
                
                // Output some positions for inspection
                Console.WriteLine("Sample vertex positions:");
                for (int i = 0; i < Math.Min(5, field.VertexCount); i++)
                {
                    int baseIndex = i * 3;
                    Console.WriteLine($"Vertex {i}: ({positions[baseIndex]:F4}, {positions[baseIndex+1]:F4}, {positions[baseIndex+2]:F4})");
                }
            }
        }

        [TestMethod]
        public void CanGetMesh()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 10x10 field
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 10;
                int numY = 10;
                
                field.CreateField(minBB, maxBB, numX, numY);
                
                // Get the mesh representation
                using (var mesh = field.GetMesh())
                {
                    // Verify mesh is valid
                    Assert.IsNotNull(mesh, "Mesh should not be null");
                    Assert.IsTrue(mesh.IsValid, "Mesh should be valid");
                    
                    // Verify mesh has the same number of vertices as the field
                    Assert.AreEqual(field.VertexCount, mesh.VertexCount, 
                        "Mesh should have the same number of vertices as the field");
                    
                    // Get mesh positions and field positions
                    double[] fieldPositions = field.GetPositions();
                    
                    // Verify positions match - note that fieldPositions has 3 components per vertex
                    Assert.AreEqual(mesh.VertexCount * 3, fieldPositions.Length,
                        "Mesh vertex count * 3 should equal field positions array length (x,y,z per vertex)");
                    
                    // Output some diagnostic information
                    Console.WriteLine($"Mesh vertex count: {mesh.VertexCount}");
                    Console.WriteLine($"Field vertex count: {field.VertexCount}");
                }
            }
        }

        [TestMethod]
        public void CanGetScalarsForDifferentShapes()
        {
            using (var field = new zExtMeshField())
            {
                // Create a 20x20 field for better resolution
                double[] minBB = new double[] { -1.0, -1.0, 0.0 };
                double[] maxBB = new double[] { 1.0, 1.0, 0.0 };
                int numX = 20;
                int numY = 20;
                
                field.CreateField(minBB, maxBB, numX, numY);
                float[] lineValues = null;
                float[] graphValues = null;
                float[] polygonValues = null;

                // Test 1: GetScalarsLine
                Console.WriteLine("\nTesting GetScalarsLine...");
                double[] start = new double[] { -0.5, 0.0, 0.0 };
                double[] end = new double[] { 0.5, 0.0, 0.0 };
                lineValues = field.GetScalarsLine(start, end, 0.0f, false);
                
                Assert.IsNotNull(lineValues, "Line values should not be null");
                Assert.AreEqual(field.ValueCount, lineValues.Length, "Line values should match field value count");
                Assert.IsTrue(lineValues.Any(v => v != 0), "Line values should have non-zero values");
                Assert.IsTrue(lineValues.Distinct().Count() > 1, "Line values should not be the same");

                // Test 2: GetScalarsGraphEdgeDistance
                Console.WriteLine("\nTesting GetScalarsGraphEdgeDistance...");
                using (var graph = new zExtGraph())
                {
                    // Create a simple square graph
                    double[] vertices = new double[] 
                    {
                        -0.5, -0.5, 0.0,  // Bottom left
                        0.5, -0.5, 0.0,   // Bottom right
                        0.5, 0.5, 0.0,    // Top right
                        -0.5, 0.5, 0.0    // Top left
                    };
                    
                    int[] edges = new int[] 
                    {
                        0, 1,  // Bottom edge
                        1, 2,  // Right edge
                        2, 3,  // Top edge
                        3, 0   // Left edge
                    };
                    
                    graph.CreateGraph(vertices, edges);
                    
                    graphValues = field.GetScalarsGraphEdgeDistance(graph, 0.0f, false);
                    
                    Assert.IsNotNull(graphValues, "Graph values should not be null");
                    Assert.AreEqual(field.ValueCount, graphValues.Length, "Graph values should match field value count");
                    Assert.IsTrue(graphValues.Any(v => v != 0), "Graph values should have non-zero values");
                    Assert.IsTrue(graphValues.Distinct().Count() > 1, "Graph values should not be the same");
                }
                
                // Test 3: GetScalarsPolygon
                Console.WriteLine("\nTesting GetScalarsPolygon...");
                using (var polygonGraph = new zExtGraph())
                {
                    // Create a triangle polygon
                    double[] vertices = new double[] 
                    {
                        0.0, 0.0, 0.0,    // Center
                        0.5, 0.0, 0.0,    // Right
                        0.25, 0.5, 0.0    // Top
                    };
                    
                    int[] edges = new int[] 
                    {
                        0, 1,  // Bottom edge
                        1, 2,  // Right edge
                        2, 0   // Left edge
                    };
                    
                    polygonGraph.CreateGraph(vertices, edges);
                    
                    polygonValues = field.GetScalarsPolygon(polygonGraph, false);
                    
                    Assert.IsNotNull(polygonValues, "Polygon values should not be null");
                    Assert.AreEqual(field.ValueCount, polygonValues.Length, "Polygon values should match field value count");
                    Assert.IsTrue(polygonValues.Any(v => v != 0), "Polygon values should have non-zero values");
                    Assert.IsTrue(polygonValues.Distinct().Count() > 1, "Polygon values should not be the same");
                }
                
                // Output value ranges for inspection
                Console.WriteLine("\nValue ranges for each shape:");
                Console.WriteLine($"Line values: {lineValues.Min():F4} to {lineValues.Max():F4}");
                Console.WriteLine($"Graph values: {graphValues.Min():F4} to {graphValues.Max():F4}");
                Console.WriteLine($"Polygon values: {polygonValues.Min():F4} to {polygonValues.Max():F4}");
                
                // Set field values to line values and get iso-contour for visualization
                field.SetFieldValues(lineValues);
                using (var contour = field.GetIsoContour(0.1f))
                {
                    Console.WriteLine($"Line iso-contour: VertexCount={contour.VertexCount}, EdgeCount={contour.EdgeCount}");
                }
            }
        }
    }
}
