# zSpace_External Mesh Implementation Guide

## Overview

This guide provides a comprehensive walkthrough for implementing new mesh methods in the zSpace_External library, covering both the C++ implementation and the C# interop layer.

## Table of Contents

- [zSpace\_External Mesh Implementation Guide](#zspace_external-mesh-implementation-guide)
  - [Overview](#overview)
  - [Table of Contents](#table-of-contents)
  - [Architecture Overview](#architecture-overview)
  - [Step-by-Step Implementation Guide](#step-by-step-implementation-guide)
    - [1. C++ Implementation (zExtMesh Class)](#1-c-implementation-zextmesh-class)
    - [2. C API Exposure](#2-c-api-exposure)
    - [3. C# P/Invoke Declaration](#3-c-pinvoke-declaration)
    - [4. C# Wrapper Method](#4-c-wrapper-method)
    - [5. Unit Test](#5-unit-test)
    - [6. Build and Test](#6-build-and-test)
  - [Data Type Marshaling](#data-type-marshaling)

## Architecture Overview

The zSpace_External project uses a layered architecture:

1. **C++ Core Implementation** - The actual mesh functionality in C++
2. **C API Layer** - C-style functions that expose the C++ functionality
3. **C# Interop Layer** - P/Invoke declarations and marshaling 
4. **C# Public API** - C# classes that provide a user-friendly interface

Key files:
- C++ class: `cpp/headers/zCore/Geometry/zExtMesh.h` and `cpp/source/zCore/Geometry/zExtMesh.cpp`
- C API: `cpp/headers/base/zSpace_External_C_API.h` and `cpp/source/base/zSpace_External_C_API_Mesh.cpp`
- C# wrapper: `projects/CS/zSpace.External/zExtMesh.cs`
- C# P/Invoke: `projects/CS/zSpace.External/NativeMethods.cs`
- Tests: `projects/CS/zSpace.External.Tests/MeshTests.cs`

## Step-by-Step Implementation Guide

### 1. C++ Implementation (zExtMesh Class)

Start by implementing the core functionality in the C++ `zExtMesh` class:

```cpp
// In cpp/headers/zCore/Geometry/zExtMesh.h
class zExtMesh {
public:
    // Add your method declaration here
    bool yourNewMethod(param1Type param1, param2Type param2);
    
    // ... existing code ...

private:
    // ... existing code ...
    
    // Update friend declarations if necessary
    friend int zext_mesh_your_new_method(zExtMeshHandle, param1Type, param2Type);
};
```

Then implement the method in the cpp file:

```cpp
// In cpp/source/zCore/Geometry/zExtMesh.cpp
bool zExtMesh::yourNewMethod(param1Type param1, param2Type param2) {
    try {
        if (!m_mesh) {
            m_mesh.reset(new zObjMesh());
        }

        // Implement your functionality here
        zFnMesh fnMesh(*m_mesh);
        
        // ... your implementation ...
        
        // Always update attributes after modifying the mesh
        if (fnMesh.numVertices() > 0) {
            updateAttributes();
            return true;
        } else {
            // Reset mesh in case of failure
            m_mesh.reset(new zObjMesh());
            m_vertexCount = 0;
            m_faceCount = 0;
            return false;
        }
    } catch (const std::exception&) {
        // Reset mesh in case of failure
        m_mesh.reset(new zObjMesh());
        m_vertexCount = 0;
        m_faceCount = 0;
        return false;
    }
}
```

### 2. C API Exposure

Add a declaration to the C API header:

```cpp
// In cpp/headers/base/zSpace_External_C_API.h
/**
 * Your function documentation here
 * 
 * @param mesh_handle Handle to the mesh
 * @param param1 Description of param1
 * @param param2 Description of param2
 * @return 1 if successful, 0 if an error occurred
 */
ZSPACE_EXTERNAL_API int zext_mesh_your_new_method(zExtMeshHandle mesh_handle, 
                                                 param1Type param1, 
                                                 param2Type param2);
```

Implement the C API function:

```cpp
// In cpp/source/base/zSpace_External_C_API_Mesh.cpp
ZSPACE_EXTERNAL_API int zext_mesh_your_new_method(zExtMeshHandle mesh_handle, 
                                                 param1Type param1,
                                                 param2Type param2) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->yourNewMethod(param1, param2) ? 1 : 0;
    , 0)
}
```

### 3. C# P/Invoke Declaration

Add a P/Invoke declaration to the `NativeMethods` class:

```csharp
// In projects/CS/zSpace.External/NativeMethods.cs
/// <summary>
/// Your method documentation here
/// </summary>
[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
[return: MarshalAs(UnmanagedType.I1)]
public static extern bool zext_mesh_your_new_method(
    IntPtr mesh_handle, 
    param1Type param1, 
    param2Type param2);
```

### 4. C# Wrapper Method

Add a public method to the `zExtMesh` class:

```csharp
// In projects/CS/zSpace.External/zExtMesh.cs
/// <summary>
/// Your method documentation here
/// </summary>
/// <param name="param1">Description of param1</param>
/// <param name="param2">Description of param2</param>
/// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
public void YourNewMethod(param1Type param1, param2Type param2)
{
    ThrowIfDisposed();
    
    Debug.WriteLine($"Calling YourNewMethod with params: {param1}, {param2}...");
    if (!NativeMethods.zext_mesh_your_new_method(_handle, param1, param2))
    {
        ThrowLastError("Failed to execute YourNewMethod");
    }
    
    Debug.WriteLine("YourNewMethod completed successfully");
}
```

### 5. Unit Test

Create a unit test for your new functionality:

```csharp
// In projects/CS/zSpace.External.Tests/MeshTests.cs
[TestMethod]
public void CanExecuteYourNewMethod()
{
    using (var mesh = new zSpace.External.zExtMesh())
    {
        // Setup preconditions
        
        // Act
        mesh.YourNewMethod(param1Value, param2Value);
        
        // Debug output
        Console.WriteLine($"Vertex count: {mesh.VertexCount}");
        Console.WriteLine($"Face count: {mesh.FaceCount}");
        
        // Assert expected results
        Assert.IsTrue(/* expected condition */);
    }
}
```

### 6. Build and Test

1. **Build the C++ Project**: 
   - Right-click on the `zSpace_External` project in Solution Explorer
   - Select "Rebuild" to ensure a clean build
   - Check the output for any errors

2. **Build the C# Projects**:
   - Build the `zSpace.External` project
   - Build the `zSpace.External.Tests` project

3. **Run the Unit Tests**:
   - Open the Test Explorer in Visual Studio
   - Run your new test to verify your implementation

## Data Type Marshaling

When passing data between C++ and C#, use these patterns:

| C++ Type | C# Type | Notes |
|----------|---------|-------|
| `int`, `double`, `bool` | `int`, `double`, `bool` | Pass directly |
| `const char*` | `[MarshalAs(UnmanagedType.LPStr)] string` | For string marshaling |
| `const double*` | `[MarshalAs(UnmanagedType.LPArray)] double[]` | For array marshaling |
| struct | `[StructLayout(LayoutKind.Sequential)]` struct | Ensure fields match exactly |

> **Note on Array Data Transfer**: The zSpace External library uses a consistent two-phase pattern for transferring array data between C++ and C#. See the "Array Data Transfer" section in **C_Sharp_CPP_Object_Transfer.md** for detailed information on the pattern, implementation examples, and best practices.

Examples:

```cpp
// C++ side
ZSPACE_EXTERNAL_API int zext_mesh_set_name(zExtMeshHandle mesh_handle, const char* name);
ZSPACE_EXTERNAL_API int zext_mesh_set_vertices(zExtMeshHandle mesh_handle, 
                                             const double* positions, int count);
```

```csharp
// C# side
[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
[return: MarshalAs(UnmanagedType.I1)]
public static extern bool zext_mesh_set_name(IntPtr mesh_handle, 
                                            [MarshalAs(UnmanagedType.LPStr)] string name);

[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
[return: MarshalAs(UnmanagedType.I1)]
public static extern bool zext_mesh_set_vertices(IntPtr mesh_handle, 
                                                [MarshalAs(UnmanagedType.LPArray)] double[] positions, 
                                                int count);