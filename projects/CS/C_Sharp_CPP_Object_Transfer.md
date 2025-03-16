# zSpace External: C++ to C# Object Transfer Mechanism

This document explains how objects (like meshes and graphs) are transferred between C++ and C# in the zSpace External library.

## 1. Architecture Overview

The architecture uses opaque handles as intermediaries between C++ objects and their C# representations:

```
C++ Object <--> Opaque Handle <--> C# Wrapper Object
```

For example:
```
zSpace::zExtMesh <--> zExtMeshHandle (void*) <--> zExtMesh (C# class)
```

## 2. Single Object Transfer

### 2.1 Object Creation

1. **C# Side**:
   ```csharp
   // Create a wrapper object
   public zExtMesh()
   {
       // Call into C++
       _handle = NativeMethods.zext_mesh_create();
       if (_handle == IntPtr.Zero)
       {
           ThrowLastError("Failed to create mesh");
       }
   }
   ```

2. **C++ Side**:
   ```cpp
   ZSPACE_EXTERNAL_API zExtMeshHandle zext_mesh_create() {
       TRY_CATCH_RETURN(
           auto mesh = new zSpace::zExtMesh();
           return static_cast<zExtMeshHandle>(mesh);
       , nullptr)
   }
   ```

The C++ side creates a real object and returns it as an opaque handle, which C# stores as an `IntPtr`.

### 2.2 Method Calls

1. **C# Side**:
   ```csharp
   public int VertexCount
   {
       get
       {
           ThrowIfDisposed();
           return NativeMethods.zext_mesh_get_vertex_count(_handle);
       }
   }
   ```

2. **C++ Side**:
   ```cpp
   ZSPACE_EXTERNAL_API int zext_mesh_get_vertex_count(zExtMeshHandle mesh_handle) {
       TRY_CATCH_RETURN(
           if (!mesh_handle) {
               zSpace::SetError("Invalid mesh handle");
               return -1;
           }
           
           auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
           return mesh->getVertexCount();
       , -1)
   }
   ```

The C# side passes the handle to C++, which casts it back to the real object type and calls the appropriate method.

### 2.3 Memory Management

1. **C# Side**:
   ```csharp
   public void Dispose()
   {
       Dispose(true);
       GC.SuppressFinalize(this);
   }

   protected virtual void Dispose(bool disposing)
   {
       if (_disposed)
           return;

       if (_handle != IntPtr.Zero)
       {
           NativeMethods.zext_mesh_destroy(_handle);
           _handle = IntPtr.Zero;
       }

       _disposed = true;
   }
   ```

2. **C++ Side**:
   ```cpp
   ZSPACE_EXTERNAL_API int zext_mesh_destroy(zExtMeshHandle mesh_handle) {
       if (!mesh_handle) {
           return 1; // Not an error, already null
       }
       
       TRY_CATCH_RETURN(
           auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
           delete mesh;
           return 1;
       , 0)
   }
   ```

The C# object calls `Dispose()` (or has its finalizer called), which calls `zext_mesh_destroy()` to free the C++ object.

## 3. Array Object Transfer (e.g., Geodesic Contours)

The transfer of multiple objects, such as an array of contour graphs, uses a two-step process:

### 3.1 Compute and Cache Objects on C++ Side

1. **C# Side**:
   ```csharp
   // First, get the count of contours by calling the function with null output array
   int contourCount = 0;
   IntPtr[] dummyArray = null;
   
   NativeMethods.zext_mesh_compute_geodesic_contours(
       _handle, sourceVertexIds, sourceVertexIds.Length, 
       steps, dist, dummyArray, ref contourCount, 0);
   ```

2. **C++ Side**:
   ```cpp
   ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours(
       zExtMeshHandle mesh_handle,
       const int* source_vertex_ids, int source_vertex_count,
       int steps, float dist,
       zExtGraphHandle* out_contours, int* out_contour_count,
       int max_contours) {
       
       // Clear any existing cached contours
       for (auto contour : g_cachedContours) {
           delete contour;
       }
       g_cachedContours.clear();
       
       auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
       
       // Compute the contours and store them in our global cache
       bool success = mesh->computeGeodesicContours(
           source_vertex_ids, source_vertex_count, steps, dist, g_cachedContours);
       
       if (!success) {
           *out_contour_count = 0;
           return 0;
       }
       
       // Set the output count
       *out_contour_count = static_cast<int>(g_cachedContours.size());
       
       // If output array is provided, copy contours into it (up to max_contours)
       if (out_contours && max_contours > 0) {
           int copyCount = std::min(static_cast<int>(g_cachedContours.size()), max_contours);
           for (int i = 0; i < copyCount; i++) {
               out_contours[i] = static_cast<zExtGraphHandle>(g_cachedContours[i]);
           }
       }
       
       return 1;
   }
   ```

The C++ side computes all contours, stores them in a global cache (`g_cachedContours`), and returns the count to C#.

### 3.2 Retrieve Individual Objects

1. **C# Side**:
   ```csharp
   // Then, create array and get each contour individually
   zExtGraph[] contours = new zExtGraph[contourCount];
   for (int i = 0; i < contourCount; i++)
   {
       IntPtr contourHandle;
       if (!NativeMethods.zext_mesh_get_geodesic_contour(_handle, i, out contourHandle))
       {
           ThrowLastError($"Failed to get contour at index {i}");
       }
       
       contours[i] = new zExtGraph(contourHandle);
   }
   ```

2. **C++ Side**:
   ```cpp
   ZSPACE_EXTERNAL_API int zext_mesh_get_geodesic_contour(
       zExtMeshHandle mesh_handle,
       int contour_index,
       zExtGraphHandle* out_contour) {
       
       if (contour_index < 0 || contour_index >= static_cast<int>(g_cachedContours.size())) {
           zSpace::SetError("Invalid contour index");
           return 0;
       }
       
       // Return the contour at the specified index
       *out_contour = static_cast<zExtGraphHandle>(g_cachedContours[contour_index]);
       
       return 1;
   }
   ```

The C# side creates an array of wrapper objects, then calls `zext_mesh_get_geodesic_contour()` for each index to get the corresponding handle from the C++ cache.

## 4. Memory Management Considerations

### 4.1 Ownership

The current implementation has a shared ownership model:
- C++ owns the objects while they're in the cache
- Once they're transferred to C#, they belong to the C# wrapper objects
- When the C# objects are disposed, they call back to C++ to delete the native objects

### 4.2 Potential Issues

1. **Cache Lifetime**: The global cache is cleared at the beginning of each computation, but not when the mesh is destroyed, which could lead to memory leaks if contours are computed but never retrieved.

2. **Thread Safety**: The global cache is not thread-safe, which could cause issues in multi-threaded applications.

3. **Orphaned Objects**: If a C# wrapper object is garbage collected before its finalizer runs, the corresponding C++ object might be leaked.

## 5. Best Practices

1. **Always Dispose C# Wrapper Objects**: Explicitly call `Dispose()` on C# objects to ensure resources are freed.

2. **Avoid Long-Lived Cached Objects**: Retrieve the contours soon after computing them to minimize the lifetime of objects in the cache.

3. **Consider Using `using` Statements**: In C#, wrap object usage in `using` statements to ensure proper disposal.

4. **Implement a Clear Method**: Consider implementing a method to explicitly clear the cache if it's no longer needed.

5. **Document the Ownership Model**: Ensure that developers using the library understand who owns what and when.

## 6. Potential Improvements

1. **Explicit Reference Counting**: Add reference counting to C++ objects to ensure they're only deleted when no longer needed.

2. **Thread-Safe Cache**: Use thread-local storage or locks to make the cache thread-safe.

3. **More Explicit Ownership Model**: Make it clearer who owns the objects and when they should be freed.

4. **Direct Array Transfer**: For small arrays, consider transferring all handles in a single call rather than retrieving them individually. 