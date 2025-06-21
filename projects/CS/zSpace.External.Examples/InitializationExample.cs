using System;
using zSpace.External;

namespace zSpace.External.Examples
{
    /// <summary>
    /// Example showing how to properly initialize the zSpace.External library.
    /// </summary>
    public static class InitializationExample
    {
        /// <summary>
        /// Entry point for the example.
        /// </summary>
        public static void Run()
        {
            Console.WriteLine("Initializing zSpace.External library...");
            
            // Initialize the library once at the start of your application
            bool initialized = zSpaceExternal.Initialize();
            
            if (!initialized)
            {
                Console.WriteLine("Failed to initialize zSpace.External library. Exiting.");
                return;
            }
            
            Console.WriteLine("zSpace.External library initialized successfully.");
            
            try
            {
                // Now create objects as needed
                using (var mesh = new zExtMesh())
                {
                    Console.WriteLine($"Created mesh: Vertex count = {mesh.VertexCount}, Face count = {mesh.FaceCount}");
                    
                    // Use the mesh...
                }
                
                using (var graph = new zExtGraph())
                {
                    Console.WriteLine($"Created graph: Vertex count = {graph.VertexCount}, Edge count = {graph.EdgeCount}");
                    
                    // Use the graph...
                }
                
                Console.WriteLine("Successfully created and used zSpace.External objects.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }
} 