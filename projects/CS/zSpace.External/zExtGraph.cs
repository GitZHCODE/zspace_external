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
        private IntPtr _handle;
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
            try
            {
                Debug.WriteLine("Initializing native library...");
                NativeLibrary.Initialize();
                
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
        /// Computes the shortest path between two vertices.
        /// </summary>
        /// <param name="startVertexId">Start vertex index</param>
        /// <param name="endVertexId">End vertex index</param>
        /// <returns>Array of vertex indices representing the path from start to end</returns>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentOutOfRangeException">Thrown if vertex indices are out of range.</exception>
        public int[] ComputeShortestPath(int startVertexId, int endVertexId)
        {
            ThrowIfDisposed();
            
            if (startVertexId < 0 || startVertexId >= VertexCount)
                throw new ArgumentOutOfRangeException(nameof(startVertexId), "Start vertex index out of range.");
            
            if (endVertexId < 0 || endVertexId >= VertexCount)
                throw new ArgumentOutOfRangeException(nameof(endVertexId), "End vertex index out of range.");
            
            // Allocate arrays with maximum possible path length (all vertices)
            int[] pathVertices = new int[VertexCount];
            int pathLength = 0;
            
            Debug.WriteLine($"Computing shortest path from vertex {startVertexId} to vertex {endVertexId}...");
            if (!NativeMethods.zext_graph_compute_shortest_path(_handle, startVertexId, endVertexId, 
                                                              pathVertices, ref pathLength, VertexCount))
            {
                ThrowLastError("Failed to compute shortest path");
            }
            
            // Create a correctly sized result array
            int[] result = new int[pathLength];
            Array.Copy(pathVertices, result, pathLength);
            
            Debug.WriteLine($"Shortest path computed successfully with {pathLength} vertices");
            return result;
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