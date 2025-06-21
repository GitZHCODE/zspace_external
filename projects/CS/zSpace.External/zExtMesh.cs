using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Represents a 3D mesh for use with zSpace.
    /// </summary>
    public class zExtMesh : IDisposable
    {
        internal IntPtr _handle;
        private bool _disposed;

        /// <summary>
        /// Gets the number of vertices in the mesh.
        /// </summary>
        public int VertexCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_mesh_get_vertex_count(_handle);
            }
        }

        /// <summary>
        /// Gets the number of faces in the mesh.
        /// </summary>
        public int FaceCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_mesh_get_face_count(_handle);
            }
        }

        /// <summary>
        /// Gets whether the mesh is valid.
        /// </summary>
        public bool IsValid
        {
            get
            {
                // Check if the mesh is disposed first to avoid accessing a disposed handle
                if (_disposed)
                    return false;
                    
                return _handle != IntPtr.Zero && 
                       NativeMethods.zext_mesh_is_valid(_handle);
            }
        }

        /// <summary>
        /// Creates a new, empty mesh.
        /// </summary>
        public zExtMesh()
        {
            if (!zSpaceExternal.IsInitialized)
            {
                throw new InvalidOperationException(
                    "zSpace.External library is not initialized. Call zSpaceExternal.Initialize() before creating any objects.");
            }

            try
            {
                Debug.WriteLine("Creating native mesh handle...");
                _handle = NativeMethods.zext_mesh_create();
                if (_handle == IntPtr.Zero)
                {
                    ThrowLastError("Failed to create mesh");
                }
                
                Debug.WriteLine($"Mesh created successfully: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating mesh: {ex.Message}");
                if (_handle != IntPtr.Zero)
                {
                    try { NativeMethods.zext_mesh_destroy(_handle); } catch { }
                    _handle = IntPtr.Zero;
                }
                throw;
            }
        }

        /// <summary>
        /// Creates a mesh from vertex positions and face data.
        /// </summary>
        /// <param name="vertexPositions">Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <param name="polyCounts">Array specifying number of vertices per face</param>
        /// <param name="polyConnections">Array of vertex indices for each face</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length.</exception>
        public void CreateMesh(double[] vertexPositions, int[] polyCounts, int[] polyConnections)
        {
            ThrowIfDisposed();
            
            if (vertexPositions == null) throw new ArgumentNullException(nameof(vertexPositions));
            if (polyCounts == null) throw new ArgumentNullException(nameof(polyCounts));
            if (polyConnections == null) throw new ArgumentNullException(nameof(polyConnections));
            
            if (vertexPositions.Length % 3 != 0)
                throw new ArgumentException("Vertex positions array length must be divisible by 3.", nameof(vertexPositions));
            
            int vertexCount = vertexPositions.Length / 3;
            
            Debug.WriteLine($"Creating mesh with {vertexCount} vertices and {polyCounts.Length} faces...");
            if (!NativeMethods.zext_mesh_create_mesh(_handle, vertexPositions, vertexCount, 
                                                   polyCounts, polyCounts.Length, 
                                                   polyConnections, polyConnections.Length))
            {
                ThrowLastError("Failed to create mesh");
            }
            
            Debug.WriteLine("Mesh created successfully");
        }

        /// <summary>
        /// Computes geodesic distances from source vertices using the heat method.
        /// </summary>
        /// <param name="sourceVertexIds">Array of source vertex indices</param>
        /// <param name="normalised">Option to normalise the output geodesic distances</param>
        /// <param name="outGeodesicDistances">Pre-allocated array that will be filled with geodesic distances (must be of length VertexCount)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length or if there are no source vertices.</exception>
        public void ComputeGeodesicHeat(int[] sourceVertexIds,bool normalised, float[] outGeodesicDistances)
        {
            ThrowIfDisposed();
            
            if (sourceVertexIds == null) throw new ArgumentNullException(nameof(sourceVertexIds));
            if (outGeodesicDistances == null) throw new ArgumentNullException(nameof(outGeodesicDistances));
            
            if (sourceVertexIds.Length == 0)
                throw new ArgumentException("Source vertex IDs array cannot be empty.", nameof(sourceVertexIds));
            
            if (outGeodesicDistances.Length < VertexCount)
                throw new ArgumentException($"Output array must have at least {VertexCount} elements (one per vertex).", nameof(outGeodesicDistances));
            
            Debug.WriteLine($"Computing geodesic distances from {sourceVertexIds.Length} source vertices...");
            if (!NativeMethods.zext_mesh_compute_geodesic_heat(_handle, sourceVertexIds, sourceVertexIds.Length, normalised, outGeodesicDistances))
            {
                ThrowLastError("Failed to compute geodesic distances");
            }
            
            Debug.WriteLine("Geodesic distances computed successfully");
        }

        /// <summary>
        /// Computes interpolated geodesic distances between two sets of vertices using the heat method.
        /// </summary>
        /// <param name="startVertexIds">Array of start vertex indices</param>
        /// <param name="endVertexIds">Array of end vertex indices</param>
        /// <param name="weight">Interpolation weight (0 to 1) where 0 favors end vertices and 1 favors start vertices</param>
        /// <param name="outGeodesicDistances">Pre-allocated array that will be filled with geodesic distances (must be of length VertexCount)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length, if there are no source vertices, or if weight is outside valid range.</exception>
        public void ComputeGeodesicHeatInterpolated(int[] startVertexIds, int[] endVertexIds, float weight, float[] outGeodesicDistances)
        {
            ThrowIfDisposed();
            
            if (startVertexIds == null) throw new ArgumentNullException(nameof(startVertexIds));
            if (endVertexIds == null) throw new ArgumentNullException(nameof(endVertexIds));
            if (outGeodesicDistances == null) throw new ArgumentNullException(nameof(outGeodesicDistances));
            
            if (startVertexIds.Length == 0)
                throw new ArgumentException("Start vertex IDs array cannot be empty.", nameof(startVertexIds));
            
            if (endVertexIds.Length == 0)
                throw new ArgumentException("End vertex IDs array cannot be empty.", nameof(endVertexIds));
            
            if (weight <= 0.0f || weight >= 1.0f)
                throw new ArgumentException("Weight must be between 0 and 1 exclusive.", nameof(weight));
            
            if (outGeodesicDistances.Length < VertexCount)
                throw new ArgumentException($"Output array must have at least {VertexCount} elements (one per vertex).", nameof(outGeodesicDistances));
            
            Debug.WriteLine($"Computing interpolated geodesic distances between {startVertexIds.Length} start vertices and {endVertexIds.Length} end vertices...");
            if (!NativeMethods.zext_mesh_compute_geodesic_heat_interpolated(_handle, startVertexIds, startVertexIds.Length, 
                                                                         endVertexIds, endVertexIds.Length, 
                                                                         weight, outGeodesicDistances))
            {
                ThrowLastError("Failed to compute interpolated geodesic distances");
            }
            
            Debug.WriteLine("Interpolated geodesic distances computed successfully");
        }
        
        /// <summary>
        /// Computes geodesic contours on the mesh from source vertices.
        /// </summary>
        /// <param name="sourceVertexIds">Array of source vertex indices</param>
        /// <param name="steps">Number of contour steps to generate</param>
        /// <param name="dist">Distance between contours (if 0, uses steps instead)</param>
        /// <returns>Array of contour graphs</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the source vertex array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if there are no source vertices or if steps is less than or equal to 0.</exception>
        public zExtGraph[] ComputeGeodesicContours(int[] sourceVertexIds, int steps, float dist = 0.0f)
        {
            ThrowIfDisposed();
            
            if (sourceVertexIds == null) throw new ArgumentNullException(nameof(sourceVertexIds));
            
            if (sourceVertexIds.Length == 0)
                throw new ArgumentException("Source vertex IDs array cannot be empty.", nameof(sourceVertexIds));
            
            if (steps <= 0)
                throw new ArgumentException("Steps must be greater than 0.", nameof(steps));
            
            // First, get the count of contours
            int contourCount = 0;
            Debug.WriteLine($"Getting count of geodesic contours for {sourceVertexIds.Length} source vertices with {steps} steps...");
            if (!NativeMethods.zext_mesh_compute_geodesic_contours(
                _handle, 
                true, // checkCount = true, only get count
                sourceVertexIds, sourceVertexIds.Length, 
                steps, dist, 
                null, ref contourCount))
            {
                ThrowLastError("Failed to get geodesic contours count");
            }
            
            Debug.WriteLine($"Expected count: {contourCount} contours");
            
            // If no contours, return an empty array
            if (contourCount == 0)
            {
                return new zExtGraph[0];
            }
            
            // Now allocate the array and retrieve the contours
            IntPtr[] contourHandles = new IntPtr[contourCount];
            
            Debug.WriteLine($"Retrieving {contourCount} geodesic contours...");
            if (!NativeMethods.zext_mesh_compute_geodesic_contours(
                _handle, 
                false, // checkCount = false, get actual contours
                sourceVertexIds, sourceVertexIds.Length, 
                steps, dist, 
                contourHandles, ref contourCount))
            {
                ThrowLastError("Failed to retrieve geodesic contours");
            }
            
            // Create managed wrappers for the contour graphs
            zExtGraph[] contours = new zExtGraph[contourCount];
            for (int i = 0; i < contourCount; i++)
            {
                contours[i] = new zExtGraph(contourHandles[i]);
            }
            
            Debug.WriteLine($"Retrieved {contourCount} geodesic contours successfully");
            return contours;
        }
        
        /// <summary>
        /// Computes interpolated geodesic contours on the mesh between two sets of vertices.
        /// </summary>
        /// <param name="startVertexIds">Array of start vertex indices</param>
        /// <param name="endVertexIds">Array of end vertex indices</param>
        /// <param name="steps">Number of contour steps to generate</param>
        /// <param name="dist">Distance between contours (if 0, uses steps instead)</param>
        /// <returns>Array of contour graphs</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any vertex array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if there are no source vertices or if steps is less than or equal to 0.</exception>
        public zExtGraph[] ComputeGeodesicContoursInterpolated(int[] startVertexIds, int[] endVertexIds, int steps, float dist = 0.0f)
        {
            ThrowIfDisposed();
            
            if (startVertexIds == null) throw new ArgumentNullException(nameof(startVertexIds));
            if (endVertexIds == null) throw new ArgumentNullException(nameof(endVertexIds));
            
            if (startVertexIds.Length == 0)
                throw new ArgumentException("Start vertex IDs array cannot be empty.", nameof(startVertexIds));
            
            if (endVertexIds.Length == 0)
                throw new ArgumentException("End vertex IDs array cannot be empty.", nameof(endVertexIds));
            
            if (steps <= 0)
                throw new ArgumentException("Steps must be greater than 0.", nameof(steps));
            
            // First, get the count of contours
            int contourCount = 0;
            Debug.WriteLine($"Getting count of interpolated geodesic contours between {startVertexIds.Length} start vertices and {endVertexIds.Length} end vertices with {steps} steps...");
            if (!NativeMethods.zext_mesh_compute_geodesic_contours_interpolated(
                _handle, 
                true, // checkCount = true, only get count
                startVertexIds, startVertexIds.Length, 
                endVertexIds, endVertexIds.Length, 
                steps, dist, 
                null, ref contourCount))
            {
                ThrowLastError("Failed to get interpolated geodesic contours count");
            }
            
            Debug.WriteLine($"Expected count: {contourCount} contours");
            
            // If no contours, return an empty array
            if (contourCount == 0)
            {
                return new zExtGraph[0];
            }
            
            // Now allocate the array and retrieve the contours
            IntPtr[] contourHandles = new IntPtr[contourCount];
            
            Debug.WriteLine($"Retrieving {contourCount} interpolated geodesic contours...");
            if (!NativeMethods.zext_mesh_compute_geodesic_contours_interpolated(
                _handle, 
                false, // checkCount = false, get actual contours
                startVertexIds, startVertexIds.Length, 
                endVertexIds, endVertexIds.Length, 
                steps, dist, 
                contourHandles, ref contourCount))
            {
                ThrowLastError("Failed to retrieve interpolated geodesic contours");
            }
            
            // Create managed wrappers for the contour graphs
            zExtGraph[] contours = new zExtGraph[contourCount];
            for (int i = 0; i < contourCount; i++)
            {
                contours[i] = new zExtGraph(contourHandles[i]);
            }
            
            Debug.WriteLine($"Retrieved {contourCount} interpolated geodesic contours successfully");
            return contours;
        }

        /// <summary>
        /// Gets the mesh data including vertex positions, polygon counts, and polygon connections.
        /// </summary>
        /// <param name="vertexPositions">Output array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <param name="polygonCounts">Output array of polygon counts</param>
        /// <param name="polygonConnections">Output array of polygon connections</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public void GetMeshData(out double[] vertexPositions, out int[] polygonCounts, out int[] polygonConnections)
        {
            ThrowIfDisposed();
            
            // First, get the counts to determine array sizes
            int vertexCount = 0;
            int polyCountsSize = 0;
            int polyConnectionsSize = 0;
            
            Debug.WriteLine("Getting mesh data sizes...");
            if (!NativeMethods.zext_mesh_get_mesh_data(
                _handle,
                true, // checkCount = true, only get sizes
                null, // no arrays yet
                ref vertexCount,
                null,
                ref polyCountsSize,
                null,
                ref polyConnectionsSize))
            {
                ThrowLastError("Failed to get mesh data sizes");
            }
            
            // Allocate arrays with the correct sizes
            vertexPositions = new double[vertexCount];
            polygonCounts = new int[polyCountsSize];
            polygonConnections = new int[polyConnectionsSize];
            
            Debug.WriteLine($"Getting mesh data: Vertices={vertexCount}, PolyCounts={polyCountsSize}, PolyConnections={polyConnectionsSize}");
            
            // Get the actual data
            if (!NativeMethods.zext_mesh_get_mesh_data(
                _handle,
                false, // checkCount = false, get the actual data
                vertexPositions,
                ref vertexCount,
                polygonCounts,
                ref polyCountsSize,
                polygonConnections,
                ref polyConnectionsSize))
            {
                ThrowLastError("Failed to get mesh data");
            }
            
            Debug.WriteLine($"Retrieved mesh data: Vertices={vertexCount}, PolyCounts={polyCountsSize}, PolyConnections={polyConnectionsSize}");
        }

        /// <summary>
        /// Computes the intersection of the mesh with a plane.
        /// </summary>
        /// <param name="origin">Origin point of the plane (x, y, z)</param>
        /// <param name="normal">Normal vector of the plane (x, y, z)</param>
        /// <param name="intersection">Graph that will contain the intersection result</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any parameter is null.</exception>
        /// <exception cref="ArgumentException">Thrown if origin or normal arrays don't have exactly 3 elements.</exception>
        public void IntersectPlane(float[] origin, float[] normal, zExtGraph intersection)
        {
            ThrowIfDisposed();
            
            if (origin == null) throw new ArgumentNullException(nameof(origin));
            if (normal == null) throw new ArgumentNullException(nameof(normal));
            if (intersection == null) throw new ArgumentNullException(nameof(intersection));
            
            if (origin.Length != 3)
                throw new ArgumentException("Origin array must have exactly 3 elements (x, y, z).", nameof(origin));
            
            if (normal.Length != 3)
                throw new ArgumentException("Normal array must have exactly 3 elements (x, y, z).", nameof(normal));
            
            Debug.WriteLine($"Computing mesh-plane intersection with origin ({origin[0]}, {origin[1]}, {origin[2]}) and normal ({normal[0]}, {normal[1]}, {normal[2]})...");
            Debug.WriteLine($"Mesh handle: {_handle}, Graph handle: {intersection._handle}");
            
            if (!NativeMethods.zext_mesh_intersect_plane(_handle, origin, normal, intersection._handle))
            {
                ThrowLastError("Failed to compute mesh-plane intersection");
            }
            
            Debug.WriteLine("Mesh-plane intersection computed successfully");
        }

        /// <summary>
        /// Transforms the mesh using a 4x4 transformation matrix.
        /// 
        /// IMPORTANT: The matrix should be provided in column-major format (translation in last column).
        /// This is because Eigen stores matrices internally in column-major format.
        /// 
        /// Matrix layout (column-major):
        /// [m00, m10, m20, m30]  // Column 0
        /// [m01, m11, m21, m31]  // Column 1  
        /// [m02, m12, m22, m32]  // Column 2
        /// [m03, m13, m23, m33]  // Column 3 (translation)
        /// 
        /// For a translation matrix, the translation vector should be in elements [3, 7, 11].
        /// </summary>
        /// <param name="tMatrix">Array of 16 floats representing a 4x4 transformation matrix (column-major order)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the transformation matrix is null.</exception>
        /// <exception cref="ArgumentException">Thrown if the transformation matrix doesn't have exactly 16 elements.</exception>
        public void Transform(float[] tMatrix)
        {
            ThrowIfDisposed();
            
            if (tMatrix == null) throw new ArgumentNullException(nameof(tMatrix));
            
            if (tMatrix.Length != 16)
                throw new ArgumentException("Transformation matrix must have exactly 16 elements (4x4 matrix).", nameof(tMatrix));
            
            Debug.WriteLine("Transforming mesh with 4x4 transformation matrix...");
            
            if (!NativeMethods.zext_mesh_transform(_handle, tMatrix))
            {
                ThrowLastError("Failed to transform mesh");
            }
            
            Debug.WriteLine("Mesh transformation completed successfully");
        }

        /// <summary>
        /// Disposes the mesh resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes the mesh resources.
        /// </summary>
        /// <param name="disposing">Whether the method was called from Dispose() or the finalizer.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (_handle != IntPtr.Zero)
            {
                Debug.WriteLine($"Destroying mesh handle: {_handle}");
                NativeMethods.zext_mesh_destroy(_handle);
                _handle = IntPtr.Zero;
            }

            _disposed = true;
        }

        /// <summary>
        /// Finalizer to clean up native resources if the object is not disposed.
        /// </summary>
        ~zExtMesh()
        {
            Dispose(false);
        }

        /// <summary>
        /// Throws an exception if the object has been disposed.
        /// </summary>
        private void ThrowIfDisposed()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(nameof(zExtMesh), "Cannot access a disposed mesh.");
            }
        }

        /// <summary>
        /// Throws an exception with the last error message from the native library.
        /// </summary>
        /// <param name="message">The error message prefix.</param>
        private void ThrowLastError(string message)
        {
            string errorMessage = NativeMethods.zext_get_last_error();
            NativeMethods.zext_clear_last_error();

            string fullMessage = $"{message}: {errorMessage}";
            Debug.WriteLine($"ERROR: {fullMessage}");
            throw new ZSpaceExternalException(fullMessage, -1);
        }
    }
} 