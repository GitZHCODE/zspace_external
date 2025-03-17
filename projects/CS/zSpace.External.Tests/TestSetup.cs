using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using zSpace.External;

namespace zSpace.External.Tests
{
    [TestClass]
    public class TestSetup
    {
        [AssemblyInitialize]
        public static void AssemblyInit(TestContext context)
        {
            Console.WriteLine("Initializing zSpace.External library for all tests...");
            
            // Initialize the library once for all tests
            if (!zSpaceExternal.Initialize())
            {
                Assert.Fail("Failed to initialize zSpace.External library");
            }
            
            Console.WriteLine("zSpace.External library initialized successfully.");
        }
    }
} 