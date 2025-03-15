# zSpace.External C# Library

This is a C# wrapper for the zSpace External native library. It provides a managed interface to interact with the zSpace External functionality from .NET applications.

## Projects

- **zSpace.External**: The main library that wraps the native zSpace_External DLL.
- **zSpace.External.Demo**: A simple console application that demonstrates how to use the library.

## Requirements

- .NET Framework 4.8
- Visual Studio 2019 or later (recommended)
- The native zSpace_External DLL must be built and available (x64 platform)

## Getting Started

1. Build the native zSpace_External DLL using the C++ solution in the `projects/CPP/zSpace_External` directory.
   - Make sure to build for the **x64** platform. The C# wrapper is configured for 64-bit only.
   - The DLL will be built to the `bin/x64/Debug` or `bin/x64/Release` directory.

2. Open the `zSpace.External.sln` solution in Visual Studio.
   - Ensure the platform is set to **x64** in the Solution Platform dropdown.

3. Build the solution.
   - The build process will automatically copy the native DLL to the output directory.

4. Run the `zSpace.External.Demo` project to see a simple demonstration of the library in action.

## Architecture Notes

This solution is configured for **x64 platform only** to match the native C++ DLL. If you need to support other platforms:

1. Build the C++ library for the desired platform (e.g., x86/Win32)
2. Modify the C# solution to include the additional platform configurations
3. Update the DLL copying tasks in the project files to reference the correct platform folder

## Usage Example

```csharp
using zSpace.External;

// Create a new mesh
using (var mesh = new ZSpaceExternal.Mesh())
{
    // Create a test cube
    mesh.CreateTestCube(2.0);
    
    // Get information about the mesh
    Console.WriteLine($"Mesh is valid: {mesh.IsValid}");
    Console.WriteLine($"Vertex count: {mesh.VertexCount}");
    Console.WriteLine($"Face count: {mesh.FaceCount}");
}
```

## Troubleshooting

If you encounter a `DllNotFoundException` when running the demo:

1. Make sure the `zSpace_External.dll` exists in the output directory of the demo application.
2. Verify that you've built both the C++ project and the C# projects for the same platform (x64).
3. Check that the DLL is accessible by the application (not blocked by security or missing dependencies).

## Notes

- This is a minimal viable product (MVP) implementation and provides only basic functionality.
- Error handling is implemented through the `ZSpaceExternalException` class.
- All resources are properly disposed through the `IDisposable` pattern. 