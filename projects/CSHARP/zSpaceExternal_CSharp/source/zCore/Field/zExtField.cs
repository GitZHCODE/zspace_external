using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtMeshScalarField {
        IntPtr pointer;

        //document all those methods

        /// <summary>
        /// Creates a mesh scalar field with the specified parameters.
        /// </summary>
        /// <param name="minBB">The starting point of the field rectangle mesh.</param>
        /// <param name="maxBB">The ending point of the field rectangle mesh.</param>
        /// <param name="resX">Resolution in the x-direction.</param>
        /// <param name="resY">Resolution in the Y-direction.</param>
        /// <param name="numNeighbors">The number of neighbors.</param>
        /// <param name="setValuesperVertex">A flag to set values per vertex.</param>
        /// <param name="triMesh">A flag indicating whether to use a triangle mesh.</param>
        /// <returns>True if the field creation was successful; otherwise, false.</returns>
        public bool createField(zExtPoint minBB, zExtPoint maxBB, int resX, int resY, int numNeighbors = 1, bool setValuesperVertex = true, bool triMesh  = true) {
            return zNativeMethods.ext_meshField_createMeshScalarField(ref this, in minBB, in maxBB, resX, resY, numNeighbors, setValuesperVertex, triMesh) == 1;
        }

        /// <summary>
        /// Sets the field values using the provided array of floating-point values.
        /// </summary>
        /// <param name="fValues">Array of field values.</param>
        /// <returns>True if the field values were set successfully; otherwise, false.</returns>
        public bool setFieldValues(float[] fValues) {
            zExtFloatArray inExtScalars = new zExtFloatArray(fValues);
            int success = zNativeMethods.ext_meshField_setFieldValues(ref this, in inExtScalars);
            return success == 1;
        }
        
        /// <summary>
        /// Retrieves the mesh representation of the field.
        /// </summary>
        /// <param name="outMesh">Output mesh object.</param>
        /// <returns>True if the mesh was successfully retrieved; otherwise, false.</returns>
        public bool getMesh(out zExtMesh outMesh) {
            return zNativeMethods.ext_meshField_getFieldMesh(ref this, out outMesh) == 1;
        }

        /// <summary>
        /// Creates a duplicate of the current mesh scalar field.
        /// </summary>
        /// <returns>The duplicated mesh scalar field.</returns>
        public zExtMeshScalarField duplicate() {
            zExtMeshScalarField outExtField;
            zNativeMethods.ext_meshField_duplicate(ref this, out outExtField);
            return outExtField;
        }

        /// <summary>
        /// Retrieves scalar values as vertex distance from a collection of positions.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inPositions">Collection of input positions.</param>
        /// <param name="offset">Scalar offset.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalarsAsVertexDistance(out float[] outScalars, zExtPointArray inPositions, float offset, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalarsAsVertexDistance_1(ref this, out outExtScalars, in inPositions, offset, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Retrieves scalar values as vertex distance from a mesh object.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inMeshObj">Input mesh object.</param>
        /// <param name="offset">Scalar offset.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalarsAsVertexDistance(out float[] outScalars, zExtMesh inMeshObj, float offset, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalarsAsVertexDistance_4(ref this, out outExtScalars, in inMeshObj, offset, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Retrieves scalar values as vertex distance from a graph object.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inGraphObj">Input graph object.</param>
        /// <param name="offset">Scalar offset.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalarsAsVertexDistance(out float[] outScalars, zExtGraph inGraphObj, float offset, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalarsAsVertexDistance_5(ref this, out outExtScalars, in inGraphObj, offset, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Retrieves scalar values as edge distance from a mesh object.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inMeshObj">Input mesh object.</param>
        /// <param name="offset">Scalar offset.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalarsAsEdgeDistance(out float[] outScalars, zExtMesh inMeshObj, float offset, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalarsAsEdgeDistance_0(ref this, out outExtScalars, in inMeshObj, offset, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];
            return success;
        }

        /// <summary>
        /// Retrieves scalar values as edge distance from a graph object.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inGraphObj">Input graph object.</param>
        /// <param name="offset">Scalar offset.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalarsAsEdgeDistance(out float[] outScalars, zExtGraph inGraphObj, float offset, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalarsAsEdgeDistance_1(ref this, out outExtScalars, in inGraphObj, offset, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Retrieves scalar values in a polygon region from a graph object.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="inGraphObj">Input graph object.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Polygon(out float[] outScalars, zExtGraph inGraphObj, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Polygon(ref this, out outExtScalars, in inGraphObj, normalise) == 1;
            outScalars = (success) ? outExtScalars.getItems() : new float[0];
            return success;
        }

        /// <summary>
        /// Retrieves scalar values in a circular region from a center point with specified radii.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="cen">Center point of the circle.</param>
        /// <param name="r">Radius of the circle.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Circle(out float[] outScalars, zExtPoint cen, float r, double annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Circle(ref this, out outExtScalars, in cen, r, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Retrieves scalar values in an elliptical region from a center point with specified semi-axes.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="cen">Center point of the ellipse.</param>
        /// <param name="a">Length of the major semi-axis.</param>
        /// <param name="b">Length of the minor semi-axis.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>

        public bool getScalars_Ellipse(out float[] outScalars, zExtPoint cen, float a, float b, double annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Ellipse(ref this, out outExtScalars, in cen, a, b, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Retrieves scalar values along a line segment defined by two points.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="v0">Starting point of the line segment.</param>
        /// <param name="v1">Ending point of the line segment.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Line(out float[] outScalars, zExtPoint v0, zExtPoint v1, double annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Line(ref this, out outExtScalars, in v0, in v1, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Retrieves scalar values within a triangle defined by three points.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="p0">First vertex of the triangle.</param>
        /// <param name="p1">Second vertex of the triangle.</param>
        /// <param name="p2">Third vertex of the triangle.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Triangle(out float[] outScalars, zExtPoint p0, zExtPoint p1, zExtPoint p2, double annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Triangle(ref this, out outExtScalars, in p0, in p1, in p2, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Retrieves scalar values within a square region defined by a center point and dimensions.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="cen">Center point of the square region.</param>
        /// <param name="dimensions">Dimensions of the square region.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Square(out float[] outScalars, zExtPoint cen, zExtPoint dimensions, float annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Square(ref this, out outExtScalars, in cen, in dimensions, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Retrieves scalar values within a trapezoid region defined by top and bottom radii and height.
        /// </summary>
        /// <param name="outScalars">Output array of scalar values.</param>
        /// <param name="r1">Top radius of the trapezoid.</param>
        /// <param name="r2">Bottom radius of the trapezoid.</param>
        /// <param name="he">Height of the trapezoid.</param>
        /// <param name="annularVal">Annular value.</param>
        /// <param name="normalise">A flag indicating whether to normalize the values.</param>
        /// <returns>True if the scalar values were retrieved successfully; otherwise, false.</returns>
        public bool getScalars_Trapezoid(out float[] outScalars, float r1, float r2, float he, float annularVal = 0, bool normalise = true) {
            zExtFloatArray outExtScalars;
            bool success = zNativeMethods.ext_meshField_getScalars_Trapezoid(ref this, out outExtScalars, r1, r2, he, annularVal, normalise) == 1;
            outScalars = outExtScalars.getItems();
            return success;
        }

        

        /// <summary>
        /// Smoothes the field values using diffusion for a specified number of iterations.
        /// </summary>
        /// <param name="outScalars">Array of field values to be smoothed.</param>
        /// <param name="numSmooth">Number of smoothing iterations.</param>
        /// <param name="diffuseDamp">Diffusion damping factor.</param>
        /// <param name="type">Smoothing type.</param>
        /// <returns>True if the field values were smoothed successfully; otherwise, false.</returns>
        public bool smoothField(ref float[] outScalars, int numSmooth, double diffuseDamp = 1.0, int type = 0) {
            zExtFloatArray outExtScalars = new zExtFloatArray(outScalars);
            bool success = zNativeMethods.ext_meshField_smoothField(ref this, ref outExtScalars, numSmooth, diffuseDamp, type) == 1;

            if (success) outScalars = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Computes positions in field index space for a given collection of positions.
        /// </summary>
        /// <param name="extFieldIndexPositions">Output positions in field index space.</param>
        /// <param name="positions">Input positions.</param>
        /// <returns>True if the positions were computed successfully; otherwise, false.</returns>
        public bool computePositionsInFieldIndex(out zExtPointArray2D extFieldIndexPositions, zExtPointArray positions) {
            return zNativeMethods.ext_meshField_computePositionsInFieldIndex(ref this, in positions, out extFieldIndexPositions) == 1;
        }

        /// <summary>
        /// Computes position indices in field index space for a given collection of positions.
        /// </summary>
        /// <param name="extFieldIndexPositionIndicies">Output position indices in field index space.</param>
        /// <param name="positions">Input positions.</param>
        /// <returns>True if the position indices were computed successfully; otherwise, false.</returns>
        public bool computePositionIndicesInFieldIndex(out zExtIntArray2D extFieldIndexPositionIndicies, zExtPointArray positions) {
            return zNativeMethods.ext_meshField_computePositionIndicesInFieldIndex(ref this, in positions, out extFieldIndexPositionIndicies) == 1;
        }

        /// <summary>
        /// Performs a union operation between two sets of scalar values.
        /// </summary>
        /// <param name="scalarsResult">Output array of scalar values.</param>
        /// <param name="scalars0">Array of the first set of scalar values.</param>
        /// <param name="scalars1">Array of the second set of scalar values.</param>
        /// <param name="normalise">A flag indicating whether to normalize the result.</param>
        /// <returns>True if the union operation was successful; otherwise, false.</returns>
        public bool boolean_union(out float[] scalarsResult, float[] scalars0, float[] scalars1, bool normalise = true) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(scalars0);
            zExtFloatArray inExtScalars1 = new zExtFloatArray(scalars1);
            bool success = zNativeMethods.ext_meshField_boolean_union(ref this, in inExtScalars0, in inExtScalars1, out outExtScalars, normalise) == 1;
            scalarsResult =   (success)? outExtScalars.getItems() : new float[0];
            return success;
        }

        /// <summary>
        /// Performs a subtraction operation between two sets of scalar values.
        /// </summary>
        /// <param name="scalarsResult">Output array of scalar values.</param>
        /// <param name="fieldValues_A">Array of the first set of scalar values.</param>
        /// <param name="fieldValues_B">Array of the second set of scalar values.</param>
        /// <param name="normalise">A flag indicating whether to normalize the result.</param>
        /// <returns>True if the subtraction operation was successful; otherwise, false.</returns>
        public bool boolean_subtract(out float[] scalarsResult, float[] fieldValues_A, float[] fieldValues_B, bool normalise = true) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(fieldValues_A);
            zExtFloatArray inExtScalars1 = new zExtFloatArray(fieldValues_B);
            bool success = zNativeMethods.ext_meshField_boolean_subtract(ref this, in inExtScalars0, in inExtScalars1, out outExtScalars, normalise) == 1;
            scalarsResult = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Performs a difference operation between two sets of scalar values.
        /// </summary>
        /// <param name="scalarsResult">Output array of scalar values.</param>
        /// <param name="fieldValues_A">Array of the first set of scalar values.</param>
        /// <param name="fieldValues_B">Array of the second set of scalar values.</param>
        /// <param name="normalise">A flag indicating whether to normalize the result.</param>
        /// <returns>True if the difference operation was successful; otherwise, false.</returns>
        public bool boolean_difference(out float[] scalarsResult, float[] fieldValues_A, float[] fieldValues_B, bool normalise = true) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(fieldValues_A);
            zExtFloatArray inExtScalars1 = new zExtFloatArray(fieldValues_B);
            bool success = zNativeMethods.ext_meshField_boolean_difference(ref this, in inExtScalars0, in inExtScalars1, out outExtScalars, normalise) == 1;
            scalarsResult = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Performs an intersection operation between two sets of scalar values.
        /// </summary>
        /// <param name="scalarsResult">Output array of scalar values.</param>
        /// <param name="fieldValues_A">Array of the first set of scalar values.</param>
        /// <param name="fieldValues_B">Array of the second set of scalar values.</param>
        /// <param name="normalise">A flag indicating whether to normalize the result.</param>
        /// <returns>True if the intersection operation was successful; otherwise, false.</returns>
        public bool boolean_intersect(out float[] scalarsResult, float[] fieldValues_A, float[] fieldValues_B, bool normalise = true) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(fieldValues_A);
            zExtFloatArray inExtScalars1 = new zExtFloatArray(fieldValues_B);
            bool success = zNativeMethods.ext_meshField_boolean_intersect(ref this, in inExtScalars0, in inExtScalars1, out outExtScalars, normalise) == 1;
            scalarsResult = (success) ? outExtScalars.getItems() : new float[0];

            return success;
        }

        /// <summary>
        /// Clips the field values using a plane defined by a transformation.
        /// </summary>
        /// <param name="scalars">Array of field values to be clipped.</param>
        /// <param name="clipPlane">Transformation representing the clipping plane.</param>
        /// <returns>True if the clipping was successful; otherwise, false.</returns>
        public bool boolean_clipwithPlane(ref float[] scalars, zExtTransform clipPlane) {
            zExtFloatArray inExtScalars = new zExtFloatArray(scalars);
            bool success = zNativeMethods.ext_meshField_boolean_clipwithPlane(ref this, ref inExtScalars, in clipPlane) == 1;
            if (success) scalars = inExtScalars.getItems();
            return success;
        }



        /// <summary>
        /// Clips the field values using a plane defined by a center point and a normal vector.
        /// </summary>
        /// <param name="fieldValues_Result">Output array of scalar values.</param>
        /// <param name="fieldValues_A">Array of field values to be clipped.</param>
        /// <param name="clipPlane_center">Center point of the clipping plane.</param>
        /// <param name="clipPlane_Norm">Normal vector of the clipping plane.</param>
        /// <returns>True if the clipping was successful; otherwise, false.</returns>
        public bool boolean_clipwithPlaneCenterAndNormal(out float[] fieldValues_Result, float[] fieldValues_A, zExtPoint clipPlane_center, zExtPoint clipPlane_Norm) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(fieldValues_A);
            bool success = zNativeMethods.ext_meshField_boolean_clipwithPlaneCenterAndNormal(ref this, in inExtScalars0, out outExtScalars, in clipPlane_center, in clipPlane_Norm) == 1;
            fieldValues_Result = outExtScalars.getItems();
            return success;
        }

        /// <summary>
        /// Performs a linear blend between two sets of scalar values.
        /// </summary>
        /// <param name="scalarsResult">Output array of scalar values.</param>
        /// <param name="currentFrame">Current frame of the blend.</param>
        /// <param name="totalFrames">Total number of frames for the blend.</param>
        /// <param name="fieldValues_A">Array of the first set of scalar values.</param>
        /// <param name="fieldValues_B">Array of the second set of scalar values.</param>
        /// <returns>True if the linear blend operation was successful; otherwise, false.</returns>
        public bool blend_linear(out float[] scalarsResult, int currentFrame, int totalFrames, float[] fieldValues_A, float[] fieldValues_B) {
            zExtFloatArray outExtScalars;
            zExtFloatArray inExtScalars0 = new zExtFloatArray(fieldValues_A);
            zExtFloatArray inExtScalars1 = new zExtFloatArray(fieldValues_B);
            bool success = zNativeMethods.ext_meshField_blend_linear(ref this, currentFrame, totalFrames, in inExtScalars0, in inExtScalars1, out outExtScalars) == 1;
            scalarsResult = (success) ? outExtScalars.getItems() : new float[0];
            return success;
        }



        /// <summary>
        /// Retrieves the isocontour graph for a specified threshold value.
        /// </summary>
        /// <param name="outCoutourGraphObj">Output isocontour graph object.</param>
        /// <param name="inThreshold">Threshold value for the isocontour.</param>
        /// <param name="precision">Precision of the isocontour.</param>
        /// <param name="distTolerance">Distance tolerance for the isocontour.</param>
        /// <returns>True if the isocontour was successfully retrieved; otherwise, false.</returns>
        public bool getIsoContour(out zExtGraph outCoutourGraphObj, float inThreshold, int precision, float distTolerance) {

            return zNativeMethods.ext_meshField_getIsocontour(ref this, out  outCoutourGraphObj,  inThreshold,  precision, distTolerance) == 1;
        }

        /// <summary>
        /// Retrieves the isoline mesh for a specified threshold value.
        /// </summary>
        /// <param name="outCoutourMeshObj">Output isoline mesh object.</param>
        /// <param name="inThreshold">Threshold value for the isoline.</param>
        /// <param name="invertMesh">A flag indicating whether to invert the mesh.</param>
        /// <returns>True if the isoline mesh was successfully retrieved; otherwise, false.</returns>
        public bool getIsolineMesh(out zExtMesh outCoutourMeshObj, float inThreshold, bool invertMesh) {
            return zNativeMethods.ext_meshField_getIsolineMesh(ref this, out outCoutourMeshObj, inThreshold, invertMesh) == 1;

        }


    }

    static partial class zNativeMethods {
        #region External methods
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_initPointer(ref zExtMeshScalarField field);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_createMeshScalarField(ref zExtMeshScalarField extField, in zExtPoint minBB, in zExtPoint maxBB, int resX, int resY, int numNeighbors,
            [MarshalAs(UnmanagedType.U1)] bool setValuesperVertex,
            [MarshalAs(UnmanagedType.U1)] bool triMesh);

        //		ZSPACE_EXTERNAL int ext_meshField_setFieldValues(zExtMeshScalarField& extField, zExtFloatArray& fValues);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_setFieldValues(ref zExtMeshScalarField extField, in zExtFloatArray fValues);

        //	ZSPACE_EXTERNAL_INLINE int ext_meshField_getFieldMesh(zExtMeshScalarField& extField, zExtMesh& outMesh)
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getFieldMesh(ref zExtMeshScalarField extField, out zExtMesh outMesh);

        //ZSPACE_EXTERNAL int ext_meshField_duplicate(zExtMeshScalarField& extField, zExtMeshScalarField& outExtField);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_duplicate(ref zExtMeshScalarField extField, out zExtMeshScalarField outExtField);

        //ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtPointArray& inPositions, float offset, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalarsAsVertexDistance_1(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPointArray inPositions, float offset, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_4(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalarsAsVertexDistance_4(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtMesh inMeshObj, float offset, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_5(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalarsAsVertexDistance_5(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtGraph inGraphObj, float offset, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalarsAsEdgeDistance_0(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalarsAsEdgeDistance_0(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtMesh inMeshObj, float offset, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalarsAsEdgeDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalarsAsEdgeDistance_1(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtGraph inGraphObj, float offset, [MarshalAs(UnmanagedType.U1)] bool normalise);








        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Polygon	(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Polygon(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtGraph inGraphObj, [MarshalAs(UnmanagedType.U1)] bool normalise);


        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Circle		(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float r, double annularVal = 0, bool normalise = true);

        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Circle(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPoint cen, float r, double annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Ellipse	(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float a, float b, double annularVal = 0, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Ellipse(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPoint cen, float a, float b, double annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Line		(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& v0, zVector& v1, double annularVal = 0, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Line(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPoint v0, in zExtPoint v1, double annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);

        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Triangle	(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zPoint& p0, zPoint& p1, zPoint& p2, double annularVal = 0, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Triangle(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPoint p0, in zExtPoint p1, in zExtPoint p2, double annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);


        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Square		(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, zVector& dimensions, float annularVal = 0, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Square(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, in zExtPoint cen, in zExtPoint dimensions, float annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);


        //ZSPACE_EXTERNAL int ext_meshField_getScalars_Trapezoid	(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, float r1, float r2, float he, float annularVal = 0, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getScalars_Trapezoid(ref zExtMeshScalarField extField, out zExtFloatArray outExtScalars, float r1, float r2, float he, float annularVal, [MarshalAs(UnmanagedType.U1)] bool normalise);


        //ZSPACE_EXTERNAL int ext_meshField_smoothField							(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, int numSmooth, double diffuseDamp = 1.0, int type = 0);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_smoothField(ref zExtMeshScalarField extField, ref zExtFloatArray outExtScalars, int numSmooth, double diffuseDamp, int type);


        //ZSPACE_EXTERNAL int ext_meshField_computePositionsInFieldIndex			(zExtMeshScalarField& extField, zExtPointArray& positions, zExtPointArray2D& extFieldIndexPositions);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_computePositionsInFieldIndex(ref zExtMeshScalarField extField, in zExtPointArray positions, out zExtPointArray2D extFieldIndexPositions);


        //ZSPACE_EXTERNAL int ext_meshField_computePositionIndicesInFieldIndex	(zExtMeshScalarField& extField, zExtPointArray& positions, zExtIntArray2D& extFieldIndexPositionIndicies);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_computePositionIndicesInFieldIndex(ref zExtMeshScalarField extField, in zExtPointArray positions, out zExtIntArray2D extFieldIndexPositionIndicies);



        //ZSPACE_EXTERNAL int ext_meshField_boolean_union(zExtMeshScalarField& extField, zExtFloatArray& scalars0, zExtFloatArray& scalars1, zExtFloatArray& scalarsResult, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_union(ref zExtMeshScalarField extField, in zExtFloatArray scalars0, in zExtFloatArray scalars1, out zExtFloatArray scalarsResult, [MarshalAs(UnmanagedType.U1)] bool normalise);



        //ZSPACE_EXTERNAL int ext_meshField_boolean_subtract(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_subtract(ref zExtMeshScalarField extField, in zExtFloatArray fieldValues_A, in zExtFloatArray fieldValues_B, out zExtFloatArray fieldValues_Result, [MarshalAs(UnmanagedType.U1)] bool normalise);



        //      ZSPACE_EXTERNAL int ext_meshField_boolean_intersect(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_intersect(ref zExtMeshScalarField extField, in zExtFloatArray fieldValues_A, in zExtFloatArray fieldValues_B, out zExtFloatArray fieldValues_Result, [MarshalAs(UnmanagedType.U1)] bool normalise);
        




        //      ZSPACE_EXTERNAL int ext_meshField_boolean_difference(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="extField">zExtField object </param>
        /// <param name="fieldValues_A">field Values A</param>
        /// <param name="fieldValues_B">field Values B</param>
        /// <param name="fieldValues_Result">resultant field value</param>
        /// <param name="normalise">true if the scalars need to mapped between -1 and 1. generally used for contouring.</param>
        /// <returns>return 1 if the method is executed successfully, 0 otherwise.</returns>
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_difference(ref zExtMeshScalarField extField, in zExtFloatArray fieldValues_A, in zExtFloatArray fieldValues_B, out zExtFloatArray fieldValues_Result, [MarshalAs(UnmanagedType.U1)] bool normalise);




        //      /*! \brief This method uses an input plane to clip an existing scalar field.
        //*
        //*	\param	[in]	field			- input field mesh.
        //*	\param	[in]	scalars				- vector of scalar values. Need to be equivalent to number of mesh vertices.
        //*	\param	[in]	clipPlane			- input zPlane used for clipping.
        //*	\since version 0.0.2
        //*/
        //      ZSPACE_EXTERNAL int ext_meshField_boolean_clipwithPlane(zExtMeshScalarField& extField, zExtFloatArray& scalars, zExtTransform& clipPlane);

        /// <summary>
        /// This method uses an input plane to clip an existing scalar field.
        /// </summary>
        /// <param name="field">input field mesh</param>
        ///  <param name="scalars">vector of scalar values. Need to be equivalent to number of mesh vertices.</param>"
        ///  <param name="clipPlane">input zPlane used for clipping.</param>"
        ///  <remarks>since version 0.0.2</remarks>
        ///  
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_clipwithPlane(ref zExtMeshScalarField extField, ref zExtFloatArray scalars, in zExtTransform clipPlane);






        //      /*! \brief This method uses an input plane to clip an existing scalar field.
        //*
        //*	\param	[in]	fieldValues_A			- field Values A.
        //* 	\param	[in]	fieldValues_Result		- resultant field value.
        //*	\param	[in]	clipPlane_center		- input clipPlane origin.
        //*	\param	[in]	clipPlane_Norm			- input clipPlane normal.
        //*	\since version 0.0.4
        //*/
        //      ZSPACE_EXTERNAL int ext_meshField_boolean_clipwithPlaneCenterAndNormal(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_Result, zPoint& clipPlane_center, zVector& clipPlane_Norm);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_boolean_clipwithPlaneCenterAndNormal(ref zExtMeshScalarField extField, in zExtFloatArray fieldValues_A, out zExtFloatArray fieldValues_Result, in zExtPoint clipPlane_center, in zExtPoint clipPlane_Norm);





        //      //--------------------------
        //      //----  BLEND METHODS
        //      //--------------------------

        //      /*! \brief This method returns the blend between the two fields at the input current frame.
        //*	\param	[in, out]	extField			- zExtField object.
        //*	\param	[in]	currentFrame			- current frame value ( between 0 & totalFrames).
        //*	\param	[in]	totalFrames				- total number of frames for the blend.
        //*	\param	[in]	fieldValues_A			- field Values A.
        //*	\param	[in]	fieldValues_B			- field Values B.
        //*	\param	[in]	fieldValues_Result		- resultant field value.
        //*	\since version 0.0.4
        //*/
        //      ZSPACE_EXTERNAL int ext_meshField_blend_linear(zExtMeshScalarField& extField, int currentFrame, int totalFrames, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_blend_linear(ref zExtMeshScalarField extField, int currentFrame, int totalFrames, in zExtFloatArray fieldValues_A, in zExtFloatArray fieldValues_B, out zExtFloatArray fieldValues_Result);
        #endregion

        //--------------------------
        //---- CONTOUR METHODS
        //--------------------------

        //ZSPACE_EXTERNAL int ext_meshField_getIsocontour(zExtMeshScalarField& extField, zExtGraph& outCoutourGraphObj, float inThreshold, int precision = PRECISION, float distTolerance = distanceTolerance);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getIsocontour(ref zExtMeshScalarField extField, out zExtGraph outCoutourGraphObj, float inThreshold, int precision, float distTolerance);



        //ZSPACE_EXTERNAL int ext_meshField_getIsolineMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThreshold = 0.5, bool invertMesh = false);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getIsolineMesh(ref zExtMeshScalarField extField, out zExtMesh outCoutourMeshObj, float inThreshold, [MarshalAs(UnmanagedType.U1)] bool invertMesh);


        //ZSPACE_EXTERNAL int ext_meshField_getIsobandMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThresholdLow = 0.2, float inThresholdHigh = 0.5);
        [DllImport(path, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_meshField_getIsobandMesh(ref zExtMeshScalarField extField, out zExtMesh outCoutourMeshObj, float inThresholdLow, float inThresholdHigh);





    }

}
