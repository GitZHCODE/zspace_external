using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace zSpace {

    [StructLayout(LayoutKind.Sequential)]
    public struct zExtVault {
        IntPtr meshPointer; /**< A pointer to zTsMeshVault */
        IntPtr graphPointer; /**< A pointer to zTsGraphVault */
        int vaultType; /**< 1 if the vault is a mesh, 0 is the vault is a graph */

        public zExtVault(zExtMesh mesh) {
            this.meshPointer = IntPtr.Zero;
            this.graphPointer = IntPtr.Zero;
            this.vaultType = -1;
            zNativeMethods.ext_vault_createMeshVault(in mesh, out this);
        }
        public zExtVault(zExtGraph graph) {
            this.meshPointer = IntPtr.Zero;
            this.graphPointer = IntPtr.Zero;
            this.vaultType = -1;
            zNativeMethods.ext_vault_createGraphVault(in graph, out this);

        }
        public zExtVault(zExtVault vault) {
            this.meshPointer = IntPtr.Zero;
            this.graphPointer = IntPtr.Zero;
            this.vaultType = -1;
            zNativeMethods.ext_vault_
                (in vault, out this);
        }
        public zExtVault copy() {
            return new zExtVault(this);
        }

        public bool setConstraints(zDiagramType type, in zExtIntArray fixedVertices) {
            int chk = zNativeMethods.ext_vault_setConstraints(in this, type, in fixedVertices);
            return chk == 1;
        }
        public bool setConstraints(zDiagramType type, in int[] fixedVertices = null) {

            zExtIntArray fixedVerticesExt =  (fixedVertices == null)? new zExtIntArray() : new zExtIntArray(fixedVertices);
            int chk = zNativeMethods.ext_vault_setConstraints(in this, type, in fixedVerticesExt);
            return chk == 1;
        }
        public bool setVertexWeightsfromConstraints(zDiagramType type) {
            int chk = zNativeMethods.ext_vault_setVertexWeightsfromConstraints(in this, type);
            return chk == 1;
        }
        public bool setVertexThickness(float thickness) {
            int chk = zNativeMethods.ext_vault_setVertexThickness(in this, thickness);
            return chk == 1;
        }
        public bool setVertexThickness(in zExtFloatArray thickness) {
            int chk = zNativeMethods.ext_vault_setVertexThicknessForEach(in this, in thickness);
            return chk == 1;
        }

        public bool setVertexMass(float mass) {
            int chk = zNativeMethods.ext_vault_setVertexMass(in this, mass);
            return chk == 1;
        }
        public bool setVertexMass(in zExtFloatArray mass) {
            int chk = zNativeMethods.ext_vault_setVertexMassForEach(in this, in mass);
            return chk == 1;
        }

        public bool setForceDensity(float fDensity) {
            int chk = zNativeMethods.ext_vault_setForceDensity(in this, fDensity);
            return chk == 1;
        }
        public bool setForceDensity(in zExtFloatArray fDensities) {
            int chk = zNativeMethods.ext_vault_setForceDensityForEach(in this, in fDensities);
            return chk == 1;
        }

        public bool runFDM() {
            int chk = zNativeMethods.ext_vault_forceDensityMethod(ref this);
            return chk == 1;
        }



    }

    public static partial class zNativeMethods {

        //      /*! \brief This method creates a zExtVault object from zExtMesh.*/
        //      ZSPACE_EXTERNAL int ext_vault_createMeshVault(zExtMesh & extMesh, zExtVault & extVault);

        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_createMeshVault(in zExtMesh extMesh, out zExtVault vault);

        //      ZSPACE_EXTERNAL int ext_vault_createGraphVault(zExtGraph& extGraph, zExtVault& extVault);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_createGraphVault(in zExtGraph extGraph, out zExtVault vault);

        //ZSPACE_EXTERNAL int ext_vault_duplicate(zExtVault& extVault, zExtVault& outExtVault);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_duplicate(in zExtVault extVault, out zExtVault outExtVault);



        //      //setConstraints(zDiagramType type, const vector<int>& _fixedVertices)
        //      /*! \brief This method sets the constraints for each vertex of the input diagram type.
        //* \param [in, out]	extVault							- zExtVault object to update.
        //* \param		[in]	type								- type of diagram to update.
        //* \param		[in]	fixedVertices						- vector of fixed vertices.
        //* \return 1 on success, 0 on failure.
        //*/

        //      ZSPACE_EXTERNAL int ext_vault_setConstraints(zExtVault& extVault, zDiagramType type, zExtIntArray& fixedVertices);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setConstraints(in zExtVault extVault, zDiagramType type, in zExtIntArray fixedVertices);





        //      /*! \brief This method sets the result vertex update weights for each vertex of the input diagram type based on the constraints.
        //*	\param [in, out]	extVault							- zExtVault object to update.
        //*	\param		[in]	type								- type of diagram to update.
        //*	\return 1 on success, 0 on failure.
        //*	\since version 0.0.2
        //*/
        //      //setVertexWeightsfromConstraints(zDiagramType type)
        //      ZSPACE_EXTERNAL int ext_vault_setVertexWeightsfromConstraints(zExtVault& extVault, zDiagramType type);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setVertexWeightsfromConstraints(in zExtVault extVault, zDiagramType type);


        //      //void setVertexThickness(float thickness);
        //      /*! \brief This method sets the thickness of the input diagram type.
        //* \param [in, out]	extVault							- zExtVault object to update.
        //* 
        //*/
        //      ZSPACE_EXTERNAL int ext_vault_setVertexThickness(zExtVault& extVault, float thickness);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setVertexThickness(in zExtVault extVault, float thickness);

        //      //void setVertexThickness(vector<float>& thickness);
        //      ZSPACE_EXTERNAL int ext_vault_setVertexThicknessForEach(zExtVault& extVault, zExtFloatArray& thickness);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setVertexThicknessForEach(in zExtVault extVault, in zExtFloatArray thickness);


        //      ///*! \brief This method sets vertex mass of all the result vertices to the input value.
        //      //*
        //      //*	\param		[in]	mass			- mass value.
        //      //*	\since version 0.0.2
        //      //*/
        //      //void setVertexMass(float mass);
        //      ZSPACE_EXTERNAL int ext_vault_setVertexMass(zExtVault& extVault, float mass);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setVertexMass(in zExtVault extVault, float mass);


        //      ///*! \brief This method sets vertex mass of all the result vertices to the input container of values.
        //      //*
        //      //*	\param		[in]	mass			- container of mass values.
        //      //*	\since version 0.0.2
        //      //*/
        //      //void setVertexMass(vector<float>& mass);
        //      ZSPACE_EXTERNAL int ext_vault_setVertexMassForEach(zExtVault& extVault, zExtFloatArray& mass);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setVertexMassForEach(in zExtVault extVault, in zExtFloatArray mass);



        //      ///*! \brief This method sets force density of all the edges to the input value.
        //      //*
        //      //*	\param		[in]	fDensity			- force density value.
        //      //*	\since version 0.0.2
        //      //*/
        //      //void setForceDensity(float fDensity);
        //      ZSPACE_EXTERNAL int ext_vault_setForceDensity(zExtVault& extVault, float fDensity);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setForceDensity(in zExtVault extVault, float fDensity);


        //      ///*! \brief This method sets force density of the edges with the input container of values.
        //      //*
        //      //*	\param		[in]	fDensities			- container of force density values.
        //      //*	\since version 0.0.2
        //      //*/
        //      //void setForceDensities(vector<float>& fDensities);
        //      ZSPACE_EXTERNAL int ext_vault_setForceDensityForEach(zExtVault& extVault, zExtFloatArray& fDensities);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_setForceDensityForEach(in zExtVault extVault, in zExtFloatArray fDensities);


        //      ///*! \brief This method computes the result based on the force density method.
        //      //*
        //      //*	\details Based on Schek, H-J. "The force density method for form finding and computation of general networks." Computer methods in applied mechanics and engineering 3.1 (1974): 115-134. (https://www.sciencedirect.com/science/article/pii/0045782574900450)
        //      //	and Linkwitz, K. (2014). Force density method. Shell Structures for Architecture: Form Finding and Optimization, Routledge, Oxon and New York, 59-71.
        //      //*	\return				bool								- true if solution is found.
        //      //*	\since version 0.0.2
        //      //*/
        //      //bool forceDensityMethod();
        //      ZSPACE_EXTERNAL int ext_vault_forceDensityMethod(zExtVault& extVault);
        [DllImport(dllPaths.tsPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int ext_vault_forceDensityMethod(ref zExtVault extVault);



    }

}
