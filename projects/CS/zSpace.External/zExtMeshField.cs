using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Represents a mesh scalar field for use with zSpace.
    /// </summary>
    public class zExtMeshField : IDisposable
    {
        internal IntPtr _handle;
        private bool _disposed;

        /// <summary>
        /// Gets the number of vertices in the field mesh.
        /// </summary>
        public int VertexCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_field_get_vertex_count(_handle);
            }
        }

        /// <summary>
        /// Gets the number of scalar values in the field.
        /// </summary>
        public int ValueCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_field_get_value_count(_handle);
            }
        }

        /// <summary>
        /// Gets whether the field is valid.
        /// </summary>
        public bool IsValid
        {
            get
            {
                // Check if the field is disposed first to avoid accessing a disposed handle
                if (_disposed)
                    return false;
                    
                return _handle != IntPtr.Zero && 
                       NativeMethods.zext_field_is_valid(_handle);
            }
        }

        /// <summary>
        /// Creates a new, empty mesh field.
        /// </summary>
        public zExtMeshField()
        {
            if (!zSpaceExternal.IsInitialized)
            {
                throw new InvalidOperationException(
                    "zSpace.External library is not initialized. Call zSpaceExternal.Initialize() before creating any objects.");
            }

            try
            {
                Debug.WriteLine("Creating native mesh field handle...");
                _handle = NativeMethods.zext_field_create();
                if (_handle == IntPtr.Zero)
                {
                    ThrowLastError("Failed to create mesh field");
                }
                
                Debug.WriteLine($"Mesh field created successfully: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating mesh field: {ex.Message}");
                if (_handle != IntPtr.Zero)
                {
                    try { NativeMethods.zext_field_destroy(_handle); } catch { }
                    _handle = IntPtr.Zero;
                }
                throw;
            }
        }

        /// <summary>
        /// Creates a mesh field from an existing handle (for internal use).
        /// </summary>
        /// <param name="handle">Handle to an existing mesh field.</param>
        internal zExtMeshField(IntPtr handle)
        {
            if (!zSpaceExternal.IsInitialized)
            {
                throw new InvalidOperationException(
                    "zSpace.External library is not initialized. Call zSpaceExternal.Initialize() before creating any objects.");
            }

            try
            {
                if (handle == IntPtr.Zero)
                {
                    throw new ArgumentException("Invalid mesh field handle", nameof(handle));
                }
                
                _handle = handle;
                Debug.WriteLine($"Mesh field created from existing handle: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating mesh field from handle: {ex.Message}");
                _handle = IntPtr.Zero;
                throw;
            }
        }

        /// <summary>
        /// Creates a field with the given bounding box and resolution.
        /// </summary>
        /// <param name="minBB">Array of 3 doubles representing minimum bounding box point (x, y, z)</param>
        /// <param name="maxBB">Array of 3 doubles representing maximum bounding box point (x, y, z)</param>
        /// <param name="numX">Number of grid points in X direction</param>
        /// <param name="numY">Number of grid points in Y direction</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length.</exception>
        public void CreateField(double[] minBB, double[] maxBB, int numX, int numY)
        {
            ThrowIfDisposed();
            
            if (minBB == null) throw new ArgumentNullException(nameof(minBB));
            if (maxBB == null) throw new ArgumentNullException(nameof(maxBB));
            
            if (minBB.Length != 3)
                throw new ArgumentException("minBB array must have exactly 3 elements", nameof(minBB));
            
            if (maxBB.Length != 3)
                throw new ArgumentException("maxBB array must have exactly 3 elements", nameof(maxBB));
            
            if (numX <= 0)
                throw new ArgumentException("numX must be greater than 0", nameof(numX));
            
            if (numY <= 0)
                throw new ArgumentException("numY must be greater than 0", nameof(numY));
            
            Debug.WriteLine($"Creating field with bounds [{minBB[0]}, {minBB[1]}, {minBB[2]}] to [{maxBB[0]}, {maxBB[1]}, {maxBB[2]}] and resolution {numX}x{numY}...");
            if (!NativeMethods.zext_field_create_field(_handle, minBB, maxBB, numX, numY))
            {
                ThrowLastError("Failed to create field");
            }
            
            Debug.WriteLine("Field created successfully");
        }

        /// <summary>
        /// Sets field values.
        /// </summary>
        /// <param name="values">Array of scalar field values</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the array is null.</exception>
        public void SetFieldValues(float[] values)
        {
            ThrowIfDisposed();
            
            if (values == null) throw new ArgumentNullException(nameof(values));
            
            Debug.WriteLine($"Setting {values.Length} field values...");
            if (!NativeMethods.zext_field_set_field_values(_handle, values, values.Length))
            {
                ThrowLastError("Failed to set field values");
            }
            
            Debug.WriteLine("Field values set successfully");
        }

        /// <summary>
        /// Gets field values.
        /// </summary>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public float[] GetFieldValues()
        {
            ThrowIfDisposed();
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_field_values(_handle, true, null, ref valueCount))
            {
                ThrowLastError("Failed to get field value count");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_field_values(_handle, false, values, ref valueCount))
            {
                ThrowLastError("Failed to get field values");
            }
            
            return values;
        }

        /// <summary>
        /// Calculates scalar field values based on distance to a graph's edges.
        /// </summary>
        /// <param name="graph">The graph to calculate distances from</param>
        /// <param name="offset">Distance offset value</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the graph is null.</exception>
        public float[] GetScalarsGraphEdgeDistance(zExtGraph graph, float offset = 0.0f, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (graph == null) throw new ArgumentNullException(nameof(graph));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_scalars_graph_edge_distance(_handle, graph._handle, offset, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to calculate graph edge distance field");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_graph_edge_distance(_handle, graph._handle, offset, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to calculate graph edge distance field");
            }
            
            return values;
        }

        /// <summary>
        /// Calculates scalar field values based on distance to a circle.
        /// </summary>
        /// <param name="centre">Array of 3 doubles representing the circle center (x, y, z)</param>
        /// <param name="radius">Radius of the circle</param>
        /// <param name="offset">Distance offset value</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the centre array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if the centre array has invalid length.</exception>
        public float[] GetScalarsCircle(double[] centre, float radius, float offset = 0.0f, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (centre == null) throw new ArgumentNullException(nameof(centre));
            
            if (centre.Length != 3)
                throw new ArgumentException("centre array must have exactly 3 elements", nameof(centre));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_scalars_circle(_handle, centre, radius, offset, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to calculate circle distance field");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_circle(_handle, centre, radius, offset, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to calculate circle distance field");
            }
            
            return values;
        }

        /// <summary>
        /// Calculates scalar field values based on distance to a line.
        /// </summary>
        /// <param name="start">Array of 3 doubles representing the line start point (x, y, z)</param>
        /// <param name="end">Array of 3 doubles representing the line end point (x, y, z)</param>
        /// <param name="offset">Distance offset value</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if either array has invalid length.</exception>
        public float[] GetScalarsLine(double[] start, double[] end, float offset = 0.0f, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (start == null) throw new ArgumentNullException(nameof(start));
            if (end == null) throw new ArgumentNullException(nameof(end));
            
            if (start.Length != 3)
                throw new ArgumentException("start array must have exactly 3 elements", nameof(start));
            
            if (end.Length != 3)
                throw new ArgumentException("end array must have exactly 3 elements", nameof(end));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_scalars_line(_handle, start, end, offset, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to calculate line distance field");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_line(_handle, start, end, offset, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to calculate line distance field");
            }
            
            return values;
        }

        /// <summary>
        /// Calculates scalar field values based on distance to a polygon defined by a graph.
        /// </summary>
        /// <param name="graph">The graph representing the polygon</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the graph is null.</exception>
        public float[] GetScalarsPolygon(zExtGraph graph, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (graph == null) throw new ArgumentNullException(nameof(graph));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_scalars_polygon(_handle, graph._handle, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to calculate polygon distance field");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_polygon(_handle, graph._handle, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to calculate polygon distance field");
            }
            
            return values;
        }

        /// <summary>
        /// Performs a boolean union operation between two scalar fields.
        /// </summary>
        /// <param name="scalarsA">First input scalar field values</param>
        /// <param name="scalarsB">Second input scalar field values</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either array is null.</exception>
        public float[] BooleanUnion(float[] scalarsA, float[] scalarsB, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_boolean_union(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean union operation");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_boolean_union(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean union operation");
            }
            
            return values;
        }

        /// <summary>
        /// Performs a boolean subtraction operation between two scalar fields.
        /// </summary>
        /// <param name="scalarsA">First input scalar field values</param>
        /// <param name="scalarsB">Second input scalar field values</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either array is null.</exception>
        public float[] BooleanSubtract(float[] scalarsA, float[] scalarsB, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_boolean_subtract(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean subtraction operation");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_boolean_subtract(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean subtraction operation");
            }
            
            return values;
        }

        /// <summary>
        /// Performs a boolean intersection operation between two scalar fields.
        /// </summary>
        /// <param name="scalarsA">First input scalar field values</param>
        /// <param name="scalarsB">Second input scalar field values</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either array is null.</exception>
        public float[] BooleanIntersect(float[] scalarsA, float[] scalarsB, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_boolean_intersect(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean intersection operation");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_boolean_intersect(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean intersection operation");
            }
            
            return values;
        }

        /// <summary>
        /// Performs a boolean difference operation between two scalar fields.
        /// </summary>
        /// <param name="scalarsA">First input scalar field values</param>
        /// <param name="scalarsB">Second input scalar field values</param>
        /// <param name="normalise">Whether to normalize the resulting values</param>
        /// <returns>Array of scalar field values</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either array is null.</exception>
        public float[] BooleanDifference(float[] scalarsA, float[] scalarsB, bool normalise = false)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_boolean_difference(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, null, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean difference operation");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_boolean_difference(_handle, scalarsA, scalarsA.Length, scalarsB, scalarsB.Length, normalise, values, ref valueCount))
            {
                ThrowLastError("Failed to perform boolean difference operation");
            }
            
            return values;
        }

        /// <summary>
        /// Calculates scalar field values using smooth minimum (smin) operation between two scalar fields.
        /// </summary>
        /// <param name="scalarsA">First set of scalar field values</param>
        /// <param name="scalarsB">Second set of scalar field values</param>
        /// <param name="k">Smoothing factor (smaller values = smoother blending)</param>
        /// <param name="mode">Mode for smooth minimum operation (0=polynomial, 1=exponential)</param>
        /// <returns>Array of scalar field values after smin operation</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either scalar array is null.</exception>
        public float[] GetScalarsSMin(float[] scalarsA, float[] scalarsB, float k, int mode = 0)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            
            int valueCount = 0;
            
            // First, get the count of values
            if (!NativeMethods.zext_field_get_scalars_smin(_handle, 
                                                         scalarsA, 
                                                         scalarsA.Length, 
                                                         scalarsB, 
                                                         scalarsB.Length, 
                                                         k, mode, 
                                                         null, ref valueCount,
                                                         true))
            {
                ThrowLastError("Failed to compute smin values");
            }
            
            if (valueCount <= 0)
                return new float[0];
                
            // Then, allocate an array and get the values
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_smin(_handle, 
                                                         scalarsA, 
                                                         scalarsA.Length, 
                                                         scalarsB, 
                                                         scalarsB.Length, 
                                                         k, mode, 
                                                         values, ref valueCount,
                                                         false))
            {
                ThrowLastError("Failed to compute smin values");
            }
            
            return values;
        }
        
        /// <summary>
        /// Calculates scalar field values using weighted smooth minimum (smin) operation between two scalar fields with exponential blending.
        /// </summary>
        /// <param name="scalarsA">First set of scalar field values</param>
        /// <param name="scalarsB">Second set of scalar field values</param>
        /// <param name="k">Smoothing factor (smaller values = smoother blending)</param>
        /// <param name="weight">Weight between two scalar fields (0.0 = all A, 1.0 = all B, 0.5 = equal blend)</param>
        /// <returns>Array of scalar field values after weighted smin operation</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if either scalar array is null.</exception>
        /// <exception cref="ArgumentOutOfRangeException">Thrown if weight is outside the [0,1] range.</exception>
        public float[] GetScalarsSMinExponentialWeighted(float[] scalarsA, float[] scalarsB, float k, float weight)
        {
            ThrowIfDisposed();
            
            if (scalarsA == null) throw new ArgumentNullException(nameof(scalarsA));
            if (scalarsB == null) throw new ArgumentNullException(nameof(scalarsB));
            if (weight < 0 || weight > 1) throw new ArgumentOutOfRangeException(nameof(weight), "Weight must be between 0 and 1");
            
            int valueCount = 0;
            
            // Get the result array size
            valueCount = scalarsA.Length;
            if (valueCount != scalarsB.Length)
            {
                ThrowLastError("Input scalar arrays must have the same length");
            }
            
            // Allocate an array for the result
            float[] values = new float[valueCount];
            
            if (!NativeMethods.zext_field_get_scalars_smin_exponential_weighted(
                _handle,
                scalarsA, scalarsA.Length,
                scalarsB, scalarsB.Length,
                k, weight,
                values, ref valueCount))
            {
                ThrowLastError("Failed to compute weighted smin values");
            }
            
            return values;
        }

        /// <summary>
        /// Gets the field bounds.
        /// </summary>
        /// <param name="minBB">Output array to receive minimum bounding box point (x, y, z)</param>
        /// <param name="maxBB">Output array to receive maximum bounding box point (x, y, z)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public void GetBounds(out double[] minBB, out double[] maxBB)
        {
            ThrowIfDisposed();
            
            minBB = new double[3];
            maxBB = new double[3];
            
            if (!NativeMethods.zext_field_get_bounds(_handle, minBB, maxBB))
            {
                ThrowLastError("Failed to get field bounds");
            }
        }

        /// <summary>
        /// Gets iso contour from the field at a given threshold value.
        /// </summary>
        /// <param name="threshold">Iso value</param>
        /// <returns>Graph containing the contour</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public zExtGraph GetIsoContour(float threshold)
        {
            ThrowIfDisposed();
            
            // Get the current field values (needed to ensure there's data to extract contours from)
            float[] fieldValues = GetFieldValues();
            if (fieldValues.Length == 0)
            {
                ThrowLastError("Failed to get iso contour: No field values available");
            }
            
            // Create a new graph to hold the contour
            zExtGraph graph = new zExtGraph();
            
            // Extract the contour
            Debug.WriteLine($"Extracting iso-contour at threshold {threshold}...");
            if (!NativeMethods.zext_field_get_iso_contour(_handle, graph._handle, threshold))
            {
                graph.Dispose();
                ThrowLastError("Failed to get iso contour");
            }
            
            // Force graph to refresh its internal state if needed
            // (This is done by the C++ updateAttributes() call but we'll double-check)
            try
            {
                double[] positions = graph.GetVertexPositions();
                int vertexCount = graph.VertexCount;
                int edgeCount = graph.EdgeCount;
                
                Debug.WriteLine($"Extracted iso-contour with {vertexCount} vertices and {edgeCount} edges");
                
                if (vertexCount == 0 && positions.Length > 0)
                {
                    Debug.WriteLine("Warning: Graph VertexCount doesn't match actual vertex data");
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error accessing graph data: {ex.Message}");
            }
            
            return graph;
        }

        /// <summary>
        /// Gets field gradient vectors.
        /// </summary>
        /// <returns>Array of gradient vectors (x1, y1, z1, x2, y2, z2, ...)</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public double[] GetGradients()
        {
            ThrowIfDisposed();
            
            // Get the vertex count to pre-allocate the gradient array
            int vertexCount = VertexCount;
            if (vertexCount <= 0)
                return new double[0];
            
            // Pre-allocate the gradient array (3 components per vertex)
            double[] gradients = new double[vertexCount * 3];
            int vectorCount = vertexCount;
            
            // Call the native method directly with the pre-allocated array
            Debug.WriteLine($"Getting gradients for {vertexCount} vertices");
            if (!NativeMethods.zext_field_get_gradients(_handle, false, gradients, ref vectorCount))
            {
                ThrowLastError("Failed to get gradient vectors");
            }
            
            // Check if we got the expected number of vectors
            if (vectorCount != vertexCount)
            {
                Debug.WriteLine($"Warning: Expected {vertexCount} gradient vectors but got {vectorCount}");
            }
            
            return gradients;
        }

        /// <summary>
        /// Gets the vertex ID at the given position.
        /// </summary>
        /// <param name="position">Array of 3 doubles representing the position (x, y, z)</param>
        /// <returns>The closest vertex ID to the given position</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the position array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if the position array has invalid length.</exception>
        public int GetId(double[] position)
        {
            ThrowIfDisposed();
            
            if (position == null) throw new ArgumentNullException(nameof(position));
            
            if (position.Length != 3)
                throw new ArgumentException("Position array must have exactly 3 elements", nameof(position));
            
            int vertexId = 0;
            
            if (!NativeMethods.zext_field_get_id(_handle, position, out vertexId))
            {
                ThrowLastError("Failed to get vertex ID");
            }
            
            return vertexId;
        }

        /// <summary>
        /// Gets all vertex positions from the field.
        /// </summary>
        /// <returns>Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public double[] GetPositions()
        {
            ThrowIfDisposed();

            if (VertexCount == 0)
            {
                return new double[0];
            }

            double[] positions = new double[VertexCount * 3];
            if (!NativeMethods.zext_field_get_positions(_handle, positions))
            {
                ThrowLastError("Failed to get vertex positions");
            }

            return positions;
        }

        /// <summary>
        /// Gets the mesh representation of the field.
        /// </summary>
        /// <returns>A new mesh object representing the field.</returns>
        /// <exception cref="ObjectDisposedException">Thrown when the field has been disposed.</exception>
        /// <exception cref="ZSpaceExternalException">Thrown when the operation fails.</exception>
        public zExtMesh GetMesh()
        {
            ThrowIfDisposed();

            // Create a new graph to hold the contour
            zExtMesh mesh = new zExtMesh();

            // Extract the contour
            Debug.WriteLine($"Getting mesh from field");
            if (!NativeMethods.zext_field_get_mesh(_handle, mesh._handle))
            {
                mesh.Dispose();
                ThrowLastError("Failed to get iso contour");
            }

            return mesh;
        }

        /// <summary>
        /// Disposes the mesh field, releasing unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes the mesh field, releasing unmanaged resources.
        /// </summary>
        /// <param name="disposing">Whether the method was called from Dispose or the finalizer.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (_handle != IntPtr.Zero)
            {
                try
                {
                    Debug.WriteLine($"Destroying mesh field: {_handle}");
                    NativeMethods.zext_field_destroy(_handle);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine($"Error during mesh field destruction: {ex.Message}");
                }
                finally
                {
                    _handle = IntPtr.Zero;
                }
            }

            _disposed = true;
        }

        /// <summary>
        /// Finalizer to ensure resources are released if Dispose is not called.
        /// </summary>
        ~zExtMeshField()
        {
            Dispose(false);
        }

        /// <summary>
        /// Throws an exception if the object has been disposed.
        /// </summary>
        /// <exception cref="ObjectDisposedException">Thrown if the object has been disposed.</exception>
        private void ThrowIfDisposed()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(GetType().Name);
            }
            
            if (_handle == IntPtr.Zero)
            {
                throw new InvalidOperationException("Mesh field handle is invalid");
            }
        }

        /// <summary>
        /// Throws an exception with the last error message from the native code.
        /// </summary>
        /// <param name="message">The message to include in the exception.</param>
        /// <exception cref="ZSpaceExternalException">Always thrown.</exception>
        private void ThrowLastError(string message)
        {
            string error = NativeMethods.zext_get_last_error();
            NativeMethods.zext_clear_last_error();

            if (!string.IsNullOrEmpty(error))
            {
                message = $"{message}: {error}";
            }

            throw new ZSpaceExternalException(message);
        }
    }
}
