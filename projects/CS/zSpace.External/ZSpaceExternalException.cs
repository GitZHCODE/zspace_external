using System;

namespace zSpace.External
{
    /// <summary>
    /// Exception that occurs when using the zSpace External library.
    /// </summary>
    public class ZSpaceExternalException : Exception
    {
        /// <summary>
        /// Gets the error code from the native library.
        /// </summary>
        public int ErrorCode { get; }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="ZSpaceExternalException"/> class.
        /// </summary>
        public ZSpaceExternalException() : base("An error occurred in the zSpace External library.")
        {
        }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="ZSpaceExternalException"/> class.
        /// </summary>
        /// <param name="message">The error message.</param>
        public ZSpaceExternalException(string message) : base(message)
        {
        }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="ZSpaceExternalException"/> class.
        /// </summary>
        /// <param name="message">The error message.</param>
        /// <param name="errorCode">The error code from the native library.</param>
        public ZSpaceExternalException(string message, int errorCode) : base(message)
        {
            ErrorCode = errorCode;
        }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="ZSpaceExternalException"/> class.
        /// </summary>
        /// <param name="message">The error message.</param>
        /// <param name="innerException">The exception that is the cause of the current exception.</param>
        public ZSpaceExternalException(string message, Exception innerException) : base(message, innerException)
        {
        }
        
        /// <summary>
        /// Initializes a new instance of the <see cref="ZSpaceExternalException"/> class.
        /// </summary>
        /// <param name="message">The error message.</param>
        /// <param name="errorCode">The error code from the native library.</param>
        /// <param name="innerException">The exception that is the cause of the current exception.</param>
        public ZSpaceExternalException(string message, int errorCode, Exception innerException) : base(message, innerException)
        {
            ErrorCode = errorCode;
        }
    }
} 