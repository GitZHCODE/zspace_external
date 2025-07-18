using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Represents a 3D graph for use with zSpace.
    /// </summary>
    public class zExtGraph : IDisposable
    {
        internal IntPtr _handle;
        private bool _disposed;

        /// <summary>
        /// Gets the number of vertices in the graph.
        /// </summary>
        public int VertexCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_graph_get_vertex_count(_handle);
            }
        }

        /// <summary>
        /// Gets the number of edges in the graph.
        /// </summary>
        public int EdgeCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_graph_get_edge_count(_handle);
            }
        }

        /// <summary>
        /// Gets whether the graph is valid.
        /// </summary>
        public bool IsValid
        {
            get
            {
                // Check if the graph is disposed first to avoid accessing a disposed handle
                if (_disposed)
                    return false;
                    
                return _handle != IntPtr.Zero && 
                       NativeMethods.zext_graph_is_valid(_handle);
            }
        }

        /// <summary>
        /// Creates a new, empty graph.
        /// </summary>
        public zExtGraph()
        {
            if (!zSpaceExternal.IsInitialized)
            {
                throw new InvalidOperationException(
                    "zSpace.External library is not initialized. Call zSpaceExternal.Initialize() before creating any objects.");
            }

            try
            {
                Debug.WriteLine("Creating native graph handle...");
                _handle = NativeMethods.zext_graph_create();
                if (_handle == IntPtr.Zero)
                {
                    ThrowLastError("Failed to create graph");
                }
                
                Debug.WriteLine($"Graph created successfully: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating graph: {ex.Message}");
                if (_handle != IntPtr.Zero)
                {
                    try { NativeMethods.zext_graph_destroy(_handle); } catch { }
                    _handle = IntPtr.Zero;
                }
                throw;
            }
        }

        /// <summary>
        /// Creates a graph from an existing handle (for internal use).
        /// </summary>
        /// <param name="handle">Handle to an existing graph.</param>
        internal zExtGraph(IntPtr handle)
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
                    throw new ArgumentException("Invalid graph handle", nameof(handle));
                }
                
                _handle = handle;
                Debug.WriteLine($"Graph created from existing handle: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating graph from handle: {ex.Message}");
                _handle = IntPtr.Zero;
                throw;
            }
        }

        /// <summary>
        /// Creates a graph from vertex positions and edge data.
        /// </summary>
        /// <param name="vertexPositions">Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <param name="edgeConnections">Array of vertex indices for each edge (start1, end1, start2, end2, ...)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length.</exception>
        public void CreateGraph(double[] vertexPositions, int[] edgeConnections)
        {
            ThrowIfDisposed();
            
            if (vertexPositions == null) throw new ArgumentNullException(nameof(vertexPositions));
            if (edgeConnections == null) throw new ArgumentNullException(nameof(edgeConnections));
            
            if (vertexPositions.Length % 3 != 0)
                throw new ArgumentException("Vertex positions array length must be divisible by 3.", nameof(vertexPositions));
            
            if (edgeConnections.Length % 2 != 0)
                throw new ArgumentException("Edge connections array length must be divisible by 2.", nameof(edgeConnections));
            
            int vertexCount = vertexPositions.Length / 3;
            
            Debug.WriteLine($"Creating graph with {vertexCount} vertices and {edgeConnections.Length / 2} edges...");
            if (!NativeMethods.zext_graph_create_graph(_handle, vertexPositions, vertexCount, 
                                                    edgeConnections, edgeConnections.Length))
            {
                ThrowLastError("Failed to create graph");
            }
            
            Debug.WriteLine("Graph created successfully");
        }

        /// <summary>
        /// Sets the positions of all vertices in the graph.
        /// </summary>
        /// <param name="vertexPositions">Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if the array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if the array has invalid length.</exception>
        public void SetVertexPositions(double[] vertexPositions)
        {
            ThrowIfDisposed();
            
            if (vertexPositions == null) throw new ArgumentNullException(nameof(vertexPositions));
            
            if (vertexPositions.Length % 3 != 0)
                throw new ArgumentException("Vertex positions array length must be divisible by 3.", nameof(vertexPositions));
            
            int vertexCount = vertexPositions.Length / 3;
            if (vertexCount != VertexCount)
                throw new ArgumentException($"Expected {VertexCount * 3} values in vertex positions array (3 per vertex).", nameof(vertexPositions));
            
            Debug.WriteLine($"Setting positions for {vertexCount} vertices...");
            if (!NativeMethods.zext_graph_set_vertex_positions(_handle, vertexPositions, vertexCount))
            {
                ThrowLastError("Failed to set vertex positions");
            }
            
            Debug.WriteLine("Vertex positions set successfully");
        }

        /// <summary>
        /// Gets the positions of all vertices in the graph.
        /// </summary>
        /// <returns>Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public double[] GetVertexPositions()
        {
            ThrowIfDisposed();
            
            int count = VertexCount;
            if (count <= 0)
                return new double[0];
                
            double[] positions = new double[count * 3]; // 3 components (x, y, z) per vertex
            
            Debug.WriteLine($"Getting positions for {count} vertices...");
            if (!NativeMethods.zext_graph_get_vertex_positions(_handle, positions))
            {
                ThrowLastError("Failed to get vertex positions");
            }
            
            Debug.WriteLine("Vertex positions retrieved successfully");
            return positions;
        }

        /// <summary>
        /// Gets the graph data including vertex positions and edge connections.
        /// </summary>
        /// <param name="vertexPositions">Output array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <param name="edgeConnections">Output array of edge connections (start1, end1, start2, end2, ...)</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public void GetGraphData(out double[] vertexPositions, out int[] edgeConnections)
        {
            ThrowIfDisposed();
            
            // First, get the counts to determine array sizes
            int vertexCount = 0;
            int edgeConnectionsSize = 0;
            
            Debug.WriteLine("Getting graph data sizes...");
            if (!NativeMethods.zext_graph_get_graph_data(
                _handle,
                true, // checkCount = true, only get sizes
                null, // no arrays yet
                ref vertexCount,
                null,
                ref edgeConnectionsSize))
            {
                ThrowLastError("Failed to get graph data sizes");
            }
            
            // Allocate arrays with the correct sizes
            vertexPositions = new double[vertexCount];
            edgeConnections = new int[edgeConnectionsSize];
            
            Debug.WriteLine($"Getting graph data: Vertices={vertexCount}, EdgeConnections={edgeConnectionsSize}");
            
            // Get the actual data
            if (!NativeMethods.zext_graph_get_graph_data(
                _handle,
                false, // checkCount = false, get the actual data
                vertexPositions,
                ref vertexCount,
                edgeConnections,
                ref edgeConnectionsSize))
            {
                ThrowLastError("Failed to get graph data");
            }
            
            Debug.WriteLine($"Retrieved graph data: Vertices={vertexCount}, EdgeConnections={edgeConnectionsSize}");
        }

        /// <summary>
        /// Merges vertices in the graph that are within a given tolerance distance of each other.
        /// This is useful for cleaning up graphs with duplicate or nearly-duplicate vertices.
        /// </summary>
        /// <param name="tolerance">Maximum distance between vertices to be considered for merging</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public void MergeVertices(double tolerance)
        {
            ThrowIfDisposed();
            
            if (tolerance < 0)
                throw new ArgumentException("Tolerance must be a non-negative value", nameof(tolerance));
            
            Debug.WriteLine($"Merging vertices with tolerance {tolerance}...");
            if (!NativeMethods.zext_graph_merge_vertices(_handle, tolerance))
            {
                ThrowLastError("Failed to merge vertices");
            }
            
            Debug.WriteLine("Vertices merged successfully");
        }
        
        /// <summary>
        /// Separates a graph into its disconnected components.
        /// Each component is a subgraph that has no connections to other components.
        /// </summary>
        /// <returns>Array of graph components</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        public zExtGraph[] SeparateGraph()
        {
            ThrowIfDisposed();
            
            // First, get the count of components
            int componentCount = 0;
            Debug.WriteLine("Getting component count...");
            if (!NativeMethods.zext_graph_separate_graph(
                _handle,
                true, // checkCount = true, only get count
                null, // no array yet
                ref componentCount))
            {
                ThrowLastError("Failed to get component count");
            }
            
            Debug.WriteLine($"Found {componentCount} components");
            
            // If no components, return empty array
            if (componentCount == 0)
            {
                return Array.Empty<zExtGraph>();
            }
            
            // Allocate array for component handles
            IntPtr[] componentHandles = new IntPtr[componentCount];
            
            // Get the actual components
            Debug.WriteLine("Retrieving components...");
            if (!NativeMethods.zext_graph_separate_graph(
                _handle,
                false, // checkCount = false, get the actual components
                componentHandles,
                ref componentCount))
            {
                ThrowLastError("Failed to retrieve components");
            }
            
            // Convert handles to zExtGraph objects
            zExtGraph[] components = new zExtGraph[componentCount];
            for (int i = 0; i < componentCount; i++)
            {
                components[i] = new zExtGraph(componentHandles[i]);
            }
            
            Debug.WriteLine($"Retrieved {componentCount} components successfully");
            return components;
        }

        /// <summary>
        /// Transforms the graph using a 4x4 transformation matrix.
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
            
            Debug.WriteLine("Transforming graph with 4x4 transformation matrix...");
            
            if (!NativeMethods.zext_graph_transform(_handle, tMatrix))
            {
                ThrowLastError("Failed to transform graph");
            }
            
            Debug.WriteLine("Graph transformation completed successfully");
        }

        /// <summary>
        /// Disposes the graph resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes the graph resources.
        /// </summary>
        /// <param name="disposing">Whether the method was called from Dispose() or the finalizer.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (_handle != IntPtr.Zero)
            {
                Debug.WriteLine($"Destroying graph handle: {_handle}");
                NativeMethods.zext_graph_destroy(_handle);
                _handle = IntPtr.Zero;
            }

            _disposed = true;
        }

        /// <summary>
        /// Finalizer to clean up native resources if the object is not disposed.
        /// </summary>
        ~zExtGraph()
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
                throw new ObjectDisposedException(nameof(zExtGraph), "Cannot access a disposed graph.");
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