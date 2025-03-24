#pragma once

#include <vector>
#include <string>
#include <map>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

namespace zSpace
{
	namespace ABB
	{
		// Constants
		const double PI = 3.14159265358979323846;

		// RAPID Data Type Declarations
		enum class RapidDataType {
			PERS,
			VAR,
			CONSTANT
		};

		enum class RapidDataClass {
			WOBJDATA,
			TOOLDATA,
			ZONEDATA,
			CONFDATA,
			NUM,
			BOOL,
			STRING
		};

		// RAPID Signal Types
		enum class SignalType {
			DO,    // Digital Output
			DI,    // Digital Input
			AO,    // Analog Output
			AI     // Analog Input
		};

		// RAPID Signal Names
		struct RapidSignals {
			static const string START_EXTRUSION;
			static const string EXTRUSION_RATE;
			static const string NOZZLE_TEMP;
			static const string PREHEAT_TEMP;
			static const string FAN_SPEED;
		};

		// Define the static members in the cpp file
		inline const string RapidSignals::START_EXTRUSION = "doStartExtrusion_ZH";
		inline const string RapidSignals::EXTRUSION_RATE = "aoExtrRate_ZH";
		inline const string RapidSignals::NOZZLE_TEMP = "aoNozzleTemp_ZH";
		inline const string RapidSignals::PREHEAT_TEMP = "aoPreheatTemp_ZH";
		inline const string RapidSignals::FAN_SPEED = "aoFanSpeed_ZH";

		// Forward declarations
		class Target;
		class Procedure;
		class Module;

		// RAPID Data Structures
		struct Pos {
			double x, y, z;
			Pos(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}

			static Pos fromMatrix(const Matrix4d& mat);
			string toRapidString() const;
		};

		struct Orient {
			double q1, q2, q3, q4;  // Quaternion components
			Orient(double _q1 = 1, double _q2 = 0, double _q3 = 0, double _q4 = 0)
				: q1(_q1), q2(_q2), q3(_q3), q4(_q4) {}

			static Orient fromMatrix(const Matrix4d& mat);
			string toRapidString() const;
		};

		// Base struct for named RAPID data
		struct NamedData {
			string name;
			NamedData(const string& _name = "default") : name(_name) {}
			virtual ~NamedData() = default;
		};

		struct WObjData : public NamedData {
			bool robhold;
			bool ufprog;
			string ufmec;
			Pos trans;
			Orient rot;
			Pos oframe;
			Orient oframe_rot;

			WObjData(const string& _name = "defaultWObj")
				: NamedData(_name), robhold(false), ufprog(true), ufmec(""),
				trans(1250.26, -572.79, -684.0),
				rot(0.999992, 0.000332, -0.004107, 0.0),
				oframe(0.0, 0.0, 0.0),
				oframe_rot(1.0, 0.0, 0.0, 0.0) {}
			string toRapidString() const;
		};

		struct ToolData : public NamedData {
			bool robhold;
			Pos tframe;
			Orient tframe_rot;
			double mass;
			Pos cog;
			Orient inertia;
			double aios;
			double aios_unit;
			double aios_value;

			ToolData(const string& _name = "defaultTool")
				: NamedData(_name), robhold(true),
				tframe(325.451, 2.555, 91.138),
				tframe_rot(0.707107, 0.0, -0.707107, 0.0),
				mass(25.0),
				cog(1.0, 0.0, 0.0),
				inertia(1.0, 0.0, 0.0, 0.0),
				aios(0.0), aios_unit(0.0), aios_value(0.0) {}
			string toRapidString() const;
		};

		struct ZoneData : public NamedData {
			bool finep;
			double pzone_tcp;
			double pzone_ori;
			double pzone_eax;
			double zone_ori;
			double zone_leax;
			double zone_reax;

			ZoneData(const string& _name = "defaultZone")
				: NamedData(_name), finep(false),
				pzone_tcp(0.1), pzone_ori(0.1),
				pzone_eax(0.1), zone_ori(0.01),
				zone_leax(0.1), zone_reax(0.01) {}
			string toRapidString() const;
		};

		struct ConfData : public NamedData {
			int cf1;
			int cf4;
			int cf6;
			int cfx;

			ConfData(const string& _name = "defaultConfig")
				: NamedData(_name), cf1(0), cf4(-1), cf6(0), cfx(1) {}
			string toRapidString() const;
		};

		// Printer settings structure
		struct PrinterSettings {
			double extrusionRate;
			double printSpeed;
			double travelSpeed;
			double layerHeight;

			PrinterSettings(double _extrusionRate = 46.06824,
				double _printSpeed = 20,
				double _travelSpeed = 100,
				double _layerHeight = 0.2)
				: extrusionRate(_extrusionRate),
				printSpeed(_printSpeed),
				travelSpeed(_travelSpeed),
				layerHeight(_layerHeight) {}
		};

		// Target class declaration
		class Target {
		private:
			Matrix4d transform;
			string name;
			ConfData confData;

		public:
			// Constructor with optional configuration name
			Target(const Matrix4d& trans, const string& targetName = "");

			// Constructor with explicit configuration
			Target(const Matrix4d& trans, const ConfData& config, const string& targetName = "");

			const Matrix4d& getTransform() const;
			const string& getName() const;
			const ConfData& getConfig() const;

			void setTransform(const Matrix4d& trans);
			void setName(const string& targetName);
			void setConfig(const ConfData& config);

			Target withZ(double newZ) const;
			string toRapidString() const;
		};

		// Procedure class declaration
		class Procedure {
		private:
			string name;
			vector<string> commands;
			int currentLayer;
			string currentLineType;

		public:
			Procedure(const string& procName = "");
			void addCommand(const string& cmd);
			void addMoveL(const Target& target, double speed,
				const string& zoneRef = "defaultZone",
				const string& toolRef = "defaultTool",
				const string& wobjRef = "defaultWObj");
			void addMoveAbsJ(const vector<double>& jRotations, double speed,
				const string& zoneRef = "defaultZone",
				const string& toolRef = "defaultTool",
				const string& wobjRef = "defaultWObj");
			void addSetDO(const string& signal, bool value);
			void addSetAO(const string& signal, double value);
			void addWaitTime(double seconds);
			void setLayer(int layer);
			void setLineType(const string& type);
			const string& getName() const;
			string toRapidString() const;
		};

		// Module class declaration
		class Module {
		private:
			string name;
			vector<Procedure> procedures;
			PrinterSettings settings;

			// Store actual data objects in maps
			map<string, WObjData> wobjData;
			map<string, ToolData> toolData;
			map<string, ZoneData> zoneData;
			map<string, ConfData> confData;

			// RapidData for RAPID code generation
			struct RapidData {
				string name;
				RapidDataType type;
				RapidDataClass dataClass;
				string content;

				// Add default constructor
				RapidData() : name(""), type(RapidDataType::PERS), dataClass(RapidDataClass::NUM), content("") {}

				RapidData(const string& n, RapidDataType t, RapidDataClass dc, const string& cont)
					: name(n), type(t), dataClass(dc), content(cont) {}
				string getDeclaration() const;
			};

			map<string, RapidData> wobjDataList;
			map<string, RapidData> toolDataList;
			map<string, RapidData> zoneDataList;
			map<string, RapidData> confDataList;

			void writeRapidPersistentData(stringstream& ss) const;

			// Helper methods to get or create data
			const WObjData& getOrDefault(const WObjData* data) const;
			const ToolData& getOrDefault(const ToolData* data) const;
			const ZoneData& getOrDefault(const ZoneData* data) const;
			const ConfData& getOrDefault(const ConfData* data) const;

			// Helper to update RapidData lists
			void updateRapidData(const WObjData& data);
			void updateRapidData(const ToolData& data);
			void updateRapidData(const ZoneData& data);
			void updateRapidData(const ConfData& data);

		public:
			Module(const string& modName = "", const PrinterSettings& printerSettings = PrinterSettings());

			// Data management methods
			void addWObjData(const WObjData& data);
			void addToolData(const ToolData& data);
			void addZoneData(const ZoneData& data);
			void addConfData(const ConfData& data);

			// Return references instead of pointers
			const WObjData& findWObjData(const string& name) const;
			const ToolData& findToolData(const string& name) const;
			const ZoneData& findZoneData(const string& name) const;
			const ConfData& findConfData(const string& name) const;

			const string& getName() const;
			Procedure& createProcedure(const string& procName);
			Procedure& getProcedure(const string& procName);
			void setSettings(const PrinterSettings& newSettings);
			const PrinterSettings& getSettings() const;
			string toRapidString() const;
			bool saveToFile(const string& filepath) const;
			void addMoveL(Procedure& proc, const Target& target, double speed,
				const WObjData* wobj = nullptr,
				const ToolData* tool = nullptr,
				const ZoneData* zone = nullptr);
			void addMoveAbsJ(Procedure& proc, const vector<double>& jRotations, double speed,
				const WObjData* wobj = nullptr,
				const ToolData* tool = nullptr,
				const ZoneData* zone = nullptr);
		};

		// RapidMaker class declaration
		class RapidMaker {
		private:
			vector<Module> modules;
			string createFilePath(const string& baseFilePath, const string& moduleName) const;

		public:
			RapidMaker();
			Module& createModule(const string& name, const PrinterSettings& settings = PrinterSettings());
			Module& getModule(const string& name);
			void addPrintMove(Module& module, Procedure& proc, const vector<Target>& targets,
				const ZoneData* zone = nullptr,
				const ToolData* tool = nullptr,
				const WObjData* wobj = nullptr);
			void addPrintMoveWithApproach(Module& module, Procedure& proc,
				const vector<Target>& targets,
				double approachHeight = 5.0,
				const ZoneData* zone = nullptr,
				const ToolData* tool = nullptr,
				const WObjData* wobj = nullptr);
			void addTravelMove(Module& module, Procedure& proc, const Target& target,
				const ZoneData* zone = nullptr,
				const ToolData* tool = nullptr,
				const WObjData* wobj = nullptr);
			bool generateRapidFiles(const string& baseFilePath);
		};
	}
}