using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zSpace {

	/*! \enum	zHEData
*	\brief	Data types of a halfedge data structure.
*	\since	version 0.0.1
*/
	public enum zHEData { zVertexData = 0, zHalfEdgeData, zEdgeData, zFaceData };

	/*! \enum	zScalarfieldData
	*	\brief	Algorithm types for field navigation.
	*	\since	version 0.0.1
	*/
	public enum zScalarfieldData { zGradientDescent = 30, zGradientAscent };

	/*! \enum	zColourData
	*	\brief	Data types of color.
	*	\since	version 0.0.1
	*/
	public enum zColorType { zRGB = 40, zHSV };


	/*! \enum	zIntergrationType
	*	\brief	Integration types.
	*	\since	version 0.0.1
	*/
	public enum zIntergrationType { zEuler = 60, zRK4, zPixel };

	/*! \enum	zDiffusionType
	*	\brief	Diffusion or averaging types.
	*	\since	version 0.0.1
	*/
	public enum zDiffusionType { zLaplacian = 70, zAverage, zLaplacianAdjacent };

	/*! \enum	zSlimeParameter
	*	\brief	Slime mold parameters.
	*	\since	version 0.0.1
	*/
	public enum zSlimeParameter { zSO = 80, zSA, zRA, zdepT };


	/*! \enum	zSQLCommand
	*	\brief SQLite database command types.
	*	\since	version 0.0.1
	*/
	public enum zSQLCommand { zCreate = 90, zInsert, zSelect, zSelectExists, zSelectCreate, zSelectCount, zUpdate, zDrop, zExportCSV };

	/*! \enum	zDataLevel
	*	\brief	Grid levels for data in London.
	*	\since	version 0.0.1
	*/
	public enum zDataLevel { zLsoaData = 50, zMsoaData, zPostcodeData };


	/*! \enum	zDataBuilding
	*	\brief	Grid levels for data in London.
	*	\since	version 0.0.1
	*/
	public enum zDataBuilding { zCommercialBuilding = 100, zResidentialBuilding, zPublicBuilding, zUniversityBuilding, zUndefinedBuilding };

	/*! \enum	zDataStreet
	*	\brief	Grid levels for data in London.
	*	\since	version 0.0.1
	*/
	public enum zDataStreet { zTrunkStreet = 20, zPrimaryStreet, zSecondaryStreet, zTertiaryStreet, zResidentialStreet, zPedestrianStreet, zCycleStreet, zServiceStreet, zUndefinedStreet };

	/*! \enum	zDatatypes
	*	\brief	Grid levels for data in London.
	*	\since	version 0.0.1
	*/
	public enum zDatatypes { zInt = 110, zFloat, zDouble, zString };

	/*! \enum	zWalkTypes
	*	\brief	walk types for Shortest Path Trees.
	*	\since	version 0.0.1
	*/
	public enum zWalkType { zEdgePath = 120, zEdgeVisited };

	/*! \enum	zFieldValueType
	*	\brief	field value sampling types.
	*	\since	version 0.0.1
	*/
	public enum zFieldValueType { zFieldIndex = 130, zFieldNeighbourWeighted, zFieldAdjacentWeighted, zFieldContainedWeighted };

	/*! \enum	zFieldStreamType
	*	\brief	field stream sampling types.
	*	\since	version 0.0.1
	*/
	public enum zFieldStreamType { zForward = 140, zBackward, zForwardBackward };

	/*! \enum	zFileTpye
	*	\brief	input and ouput file types.
	*	\since	version 0.0.2
	*/
	public enum zFileTpye { zJSON = 150, zUSD, zOBJ, zTXT, zMAYATXT, zCSV, zBMP, zPNG, zJPEG, zMESH, zGRAPH };

	/*! \enum	zFnType
	*	\brief	functionset types.
	*	\since	version 0.0.2
	*/
	public enum zFnType { zInvalidFn = 160, zPointsFn, zMeshFn, zGraphFn, zMeshFieldFn, zPointFieldFn, zParticleFn, zMeshDynamicsFn, zGraphDynamicsFn, zComputeMeshFn, zNurbsCurveFn, zArcFn, zPlaneFn };

	/*! \enum	zDiagramType
	*	\brief	diagram types for vaults.
	*	\since	version 0.0.2
	*/
	public enum zDiagramType { zFormDiagram = 190, zForceDiagram, zResultDiagram };

	/*! \enum	zRobotType
	*	\brief	robot types.
	*	\since	version 0.0.2
	*/
	public enum zRobotType { zRobotABB = 200, zRobotKuka, zRobotNachi };

	/*! \enum	zRobotRotationType
	*	\brief	robot rotation types.
	*	\since	version 0.0.2
	*/
	public enum zRobotRotationType { zJoint = 210, zJointHome, zJointMinimum, zJointMaximum };

	/*! \enum	zRobotMoveType
	*	\brief	robot move types.
	*	\since	version 0.0.2
	*/
	public enum zRobotMoveType { zMoveLinear = 220, zMoveJoint };

	/*! \enum	zRobotEEControlType
	*	\brief	robot end effector control types.
	*	\since	version 0.0.2
	*/
	public enum zRobotEEControlType { zEEOn = 230, zEEOff, zEENeutral };

	/*! \enum	zSpectralVertexType
	*	\brief	spectral processing vertex types.
	*	\since	version 0.0.2
	*/
	public enum zSpectralVertexType { zRegular = 240, zMinima, zMaxima, zSaddle };

	/*! \enum	zConnectivityType
	*	\brief	connectivty matrix types.
	*	\since	version 0.0.4
	*/
	public enum zConnectivityType { zVertexVertex = 250, zVertexEdge, zFaceVertex, zFaceEdge };

	/*! \enum	zPlanarSolverType
	*	\brief	Types of planarisation solver.
	*	\since	version 0.0.4
	*/
	public enum zPlanarSolverType { zQuadPlanar = 260, zVolumePlanar };

	/*! \enum	zMSSolverType
	*	\brief	Types of planarisation.
	*	\since	version 0.0.4
	*/
	public enum zMSSolverType { zMinimiseArea = 270, zRestlength };

	/*! \enum	zMSSolverType
	*	\brief	Types of planarisation.
	*	\since	version 0.0.4
	*/
	public enum zSolverForceConstraints { zConstraintFree = 280, zConstraintXY, zConstraintYZ, zConstraintZX, zConstraintX, zConstraintY, zConstraintZ };

	/*! \enum	zFieldColorType
	*	\brief	Types of coloring for the field.
	*	\since	version 0.0.4
	*/
	public enum zFieldColorType { zFieldRegular = 290, zFieldSDF, zFieldSlime };

}
