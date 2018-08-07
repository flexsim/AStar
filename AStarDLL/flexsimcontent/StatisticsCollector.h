#pragma once

#include "datatypes.h"
#include "objectdatatype.h"
#include "flexsimevent.h"

#include <functional>
#include <map>

#define DATA_FORMAT_NONE 0
#define DATA_FORMAT_OBJECT 1
#define DATA_FORMAT_TIME 2
#define DATA_FORMAT_PERCENT 3

namespace FlexSim
{

#ifdef FLEXSIM_COMMANDS
visible treenode nodeaddsimpledata(treenode, SimpleDataType*, int);
#endif


#pragma region class SDTMember

template <class SDT>
class SDTMember
{
protected:
	TreeNode* memberNode;

public:
	SDT* operator->() {
		if (memberNode->dataType != DATA_SIMPLE) {
			memberNode->addSimpleData(new SDT, 1);
		}

		return memberNode->objectAs(SDT);
	}

	SDT& operator*() { return *(operator->()); }
	operator SDT*() { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

template <class CDT>
class CDTMember
{
protected:
	TreeNode* memberNode;

public:
	CDT* operator->() {
		if (memberNode->dataType != DATA_POINTERCOUPLING) {
			memberNode->addCouplingData(new CDT, 1);
		}

		return memberNode->objectAs(CDT);
	}

	CDT& operator*() { return *(operator->()); }
	operator CDT*() { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

class BundleMember
{
protected:
	TreeNode* memberNode;

public:
	Bundle* operator->() const { return memberNode->objectAs(Bundle); }
	Bundle& operator*() const { return *(operator->()); }
	operator Bundle*() const { return operator->(); }
	operator TreeNode*&() { return memberNode; }
};

#pragma endregion

#pragma region IDService
class IDServiceCore : public SimpleDataType
{
protected:
	typedef std::unordered_map<TreeNode*, std::pair<NodeRef, double>> IDMap;
	IDMap itemMap;
	double itemID = 1;
	IDMap::iterator itemMapEnd = itemMap.end();

public:
	class IDInfo : public CouplingDataType
	{
	public:
		// holder->partner() stores the reference to the object
		// holder's name stores the path
		double hash;
		ByteBlock path;

		virtual void bind() override
		{
			__super::bind();
			bindDouble(hash, true);
			bindByteBlock(path, true);
		}
		virtual const char* getClassFactory() override { return "IDServiceCoreIDInfo"; }
	};
protected:
	NodeListArray<IDInfo>::CouplingSdtSubNodeBindingType idInfoObjects;
	bool mapsBuilt = false;
	std::unordered_map<TreeNode*, IDInfo*> nodeIDMap;
	std::unordered_map<unsigned int, IDInfo*> idPathMap;

	std::unordered_map<TreeNode*, IDInfo*>::iterator nodeIDMapEnd = nodeIDMap.end();
	std::unordered_map<unsigned int, IDInfo*>::iterator idPathMapEnd = idPathMap.end();

	std::string getObjectHashPath(TreeNode* object);
	unsigned int hashPath(const char* path, size_t length);
	void buildIDInfoMaps();

	double getObjectID(TreeNode* object);
	double getItemID(TreeNode* item);

public:
	// The model IDService should not keep dead IDs.
	// The experimenter IDService, on the other hand, should,
	// because a replication might have created an object that
	// doesn't exist in the original.
	double keepDeadIDs = 0;

	void onReset();
	double getID(TreeNode* object);

	int isValueID(double id);
	TreeNode* getObjectFromID(double id);
	const char* getPathFromID(double id);

	void mergeWith(IDServiceCore* other);

	void clear();

	virtual void bind() override;
	virtual const char* getClassFactory() { return "IDServiceCore"; }
};

class IDService : public ObjectDataType
{
protected:
	static ObjRef<IDService> idService;
	static IDService& getIDService();

	ObjRef<IDServiceCore> __idServiceCore;
	TreeNode* __idServiceCoreNode;
	IDServiceCore& __getIDServiceCore();
	__declspec(property(get = __getIDServiceCore)) IDServiceCore& idServiceCore;

public:
	class IDServiceSQLSource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		NodeRef itemInfoList;
		IDServiceSQLSource(IDService* idService);
	};

	double saved = 0;
	engine_export void enableExperimenterMode();
	engine_export void onReset();

	engine_export static double getID(TreeNode* object);

	engine_export static int isValueID(double id);
	engine_export static TreeNode* getObjectFromID(double id);
	engine_export static const char* getPathFromID(double id);
	const char* getPathFromIDLocal(double id);

	engine_export static Array getIDsAndPathsInBundle(TreeNode* bundleNode, const Variant& columns, int startEntry = 0);

	engine_export static void clear();
	engine_export void mergeWith(IDService* other);

	engine_export virtual void bindVariables() override;
	
	static IDService* create(TreeNode* parent);
};
#pragma endregion (classes IDService, IDServiceCore)

// This interface makes it easier to deal with the fact that both
// the statistics collector and the calculated table specify column
// formats (DATA_FORMAT_*)
class StatisticsCollector;
class CalculatedTable;
class ColumnFormatter : public ObjectDataType
{
public:
	virtual int getColumnFormat(int colNr) = 0;
	virtual Array getColumnFormats() = 0;
	virtual StatisticsCollector* toStatisticsCollector() { return nullptr; }
	virtual CalculatedTable* toCalculatedTable() { return nullptr; }
};

class StatisticsCollector : public ColumnFormatter
{
protected:
	class CollectedData
	{
	public:
		StatisticsCollector* collector = nullptr;

		// These are set in the event phase
		Group* group = nullptr;
		TreeNode* eventNode = nullptr;
		ObjectDataType* processFlowInstance = nullptr;
		std::string eventName;

		bool dataAvailable = false;
		bool rowValueAvailable = false;
		bool rowDataAvailable = false;

		// The row function iterates through all rows, setting the row object and number
		Variant rowValue;
		int rowNum;
		int rowValueIndex;

		bool colDataAvailable = false;
		// Then the row function iterates through all columns, setting the col number
		int colNum;

		// Any additional properties are stored here
		std::map<std::string, Variant> properties;

		// This is called after every event is handled
		void clear();

		CollectedData() {}
		CollectedData(StatisticsCollector* collector) : collector(collector) {}
	};

	class CollectedDataInterface
	{
	protected:
		CollectedData* data = nullptr;
	public:
		CollectedDataInterface(CollectedData* data) : data(data) {}
		void construct(const CollectedDataInterface& other) { data = other.data; }
		CollectedDataInterface& operator =(const CollectedDataInterface& other) { data = other.data; return *this; }

		Group* __getGroup();
		TreeNode* __getEventNode();
		ObjectDataType* __getProcessFlowInstance();
		std::string __getEventName();
		Variant __getRowValue();
		int __getRowNumber();
		int __getRowValueIndex();
		int __getColNumber();
		Variant __getCurrentValue();

		__declspec(property(get = __getGroup)) Group* group;
		__declspec(property(get = __getEventNode)) TreeNode* eventNode;
		__declspec(property(get = __getProcessFlowInstance)) ObjectDataType* processFlowInstance;
		__declspec(property(get = __getEventName)) std::string eventName;
		__declspec(property(get = __getRowObject)) Variant rowObject;
		__declspec(property(get = __getRowNumber)) int rowNumber;
		__declspec(property(get = __getRowValueIndex)) int rowValueIndex;
		__declspec(property(get = __getColNumber)) int colNumber;
		__declspec(property(get = __getCurrentValue)) Variant currentValue;

		Variant getProperty(const char* name, unsigned nameHash, bool dieHard);
		void setProperty(const char* name, unsigned nameHash, const Variant& value);

		static void bindInterface();
	};

	CollectedData __collectedData = CollectedData(this);

public:
	// Row/object map
	class NodeMapBinder : public SimpleDataType
	{
	public:
		std::unordered_map<TreeNode*, std::pair<NodeRef, int>> map;
		std::unordered_map<TreeNode*, std::pair<NodeRef, int>>::iterator mapEnd = map.end();
		void clear() { map.clear(); }
		virtual void bind() override;
		virtual const char* getClassFactory() { return "StatisticsCollectorNodeMapBinder"; }
	};

	class VariantMapBinder : public SimpleDataType
	{
	public:
		std::unordered_map<Variant, int, Variant::Hash> map;
		std::unordered_map<Variant, int, Variant::Hash>::iterator mapEnd = map.end();
		void clear() { map.clear(); }
#if defined FLEXSIM_COMMANDS
		virtual void bind()	{ __super::bind(); bindStlMap(map); }
#endif
		virtual const char* getClassFactory() { return "StatisticsCollectorVariantMapBinder"; }
	};


protected:
	SDTMember<NodeMapBinder> nodeRowMapData;
	SDTMember<VariantMapBinder> varRowMapData;

	std::pair<int, bool> getRowForVariant(const Variant& value);
	double willSort = 0;
	void updateRowOrder(int& newRow, const Variant& rowValue);

public:
	class EventReference;
	class Column : public SimpleDataType
	{
	public:
		enum ValueApplicationMode {
			OnEventOnly = 1,
			AtInitialize,
			Always,
		};

		double bundleFieldType = 1;
		double valueFormat = DATA_FORMAT_NONE;
		TreeNode* valueNode;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorColumn"; }

		const static int NO_INDEX = -1;

		StatisticsCollector* __getCollector();
		__declspec(property(get = __getCollector)) StatisticsCollector* collector;

		double valueApplicationMode = (double)OnEventOnly;
		double bundleIndex = NO_INDEX;

		Variant getValue() { return valueNode->evaluate(); }
		int getBundleFieldType() { return (int)bundleFieldType;	};

		int getColumnFormat() { return (int)valueFormat; }
		bool isDynamic() { return valueApplicationMode == (double)Always; }

		virtual bool isClassType(const char* className) override {
			return strcmp(className, "StatisticsCollectorColumn") == 0;
		}

		static void eventAdder(TreeNode* x, EventReference* column);
		static EventReference* eventGetter(TreeNode* x);
		NodeListArray<EventReference, eventAdder, eventGetter, 0> events;
	};

	class EventParamProperty : public SimpleDataType
	{
	public:
		double enabled;
		ByteBlock paramName;
		double paramNumber;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventParamProperty"; }
	};

	class CollectedDataProperty : public SimpleDataType
	{
	public:
		TreeNode* propertyValue;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorCollectedDataProperty"; }
	};

	class TimerEventReference;
	
	class EventReference : public SimpleDataType
	{
	public:
		NodeRef object;
		ByteBlock eventName;

		double changeRule = 0;
		TreeNode* changeValue;

		// The view fills in this list using enumerateEvents
		TreeNode* eventList;

		SimpleDataType* getSDT();

		NodeListArray<EventParamProperty>::SdtSubNodeBindingType eventProperties;
		NodeListArray<CollectedDataProperty>::SdtSubNodeBindingType collectedProperties;

		TreeNode* condition;

		static void columnAdder(TreeNode* x, Column* column);
		static Column* columnGetter(TreeNode* x);
		NodeListArray<Column, columnAdder, columnGetter, 0> columns;

		bool isTrackedVariableType();

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventReference"; }
		virtual bool isClassType(const char* className) {
			return strcmp(className, "StatisticsCollectorEventReference") == 0;
		}

		virtual const char* getType();
		virtual TimerEventReference* toTimerEventReference() { return nullptr; }
	};

	class EventReferenceListener : public FlexSimEvent
	{
	public:
		ObjRef<EventReference> linkedEvent;
		NodeRef eventObject;
		ByteBlock eventName;
		double flags = 0;
		NodeRef instanceObject;
		double changeRule = 0;
		TreeNode* changeValue;
		virtual void execute() override;
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorEventReferenceListener"; }
	};

	class TimerEventReference : public EventReference
	{
	public:
		double offsetTime = 0;
		double repeatSchedule = 0;
		double repeatInterval = 100;

		// The schedule should be a table
		// First column - time to fire
		// Additional columns - data to collect
		TreeNode* schedule;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTimerEventReference"; }

		virtual const char* getType() { return "Timer"; }

		virtual TimerEventReference* toTimerEventReference() override { return this; }
	};

	class TimerEventReferenceListener : public FlexSimEvent
	{
	public:
		ObjRef<EventReference> linkedEvent;
		double rowNumber;
		virtual void execute() override;
		virtual void bind() override;
		virtual const char* getClassFactory() { return "StatisticsCollectorTimerEventReferenceListener"; }
	};

#if (defined FLEXSIM_EXECUTIVE && defined FLEXSIM_FLEXSCRIPT_CPP)
	class TrackedVariableEventReferenceListener : public ValueChangeListener
	{
	public:
		ObjRef<EventReference> linkedEvent;
		NodeRef eventObject;
		ByteBlock eventName;
		NodeRef instanceObject;

		virtual void onChangeRuleMet(const Variant& newValue, const Variant& oldValue) override;

		virtual void bind() override;
		virtual const char* getClassFactory() override { return "StatisticsCollectorTrackedVariableEventReferenceListener"; }
	};
#endif

	engine_export static bool isStatsCollectorListener(TreeNode* listener);
	engine_export static const char* getListenerEventName(TreeNode* listener);
	engine_export static bool areListenersEqual(TreeNode* listener1, TreeNode* listener2);
	engine_export static void setListenerInstance(TreeNode* listener, TreeNode* instanceObject);

	class QuerySource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		ObjRef<StatisticsCollector> collector;
		QuerySource(StatisticsCollector* collector) : collector(collector) {}
	};

	class ExperimentQuerySource : public SqlDataSource
	{
	protected:
		struct BundleInfo
		{
			Bundle* bundle;
			int scenario;
			int replication;
		};

		// I reverse the comparison, so that lower_bound gets me what I want
		std::map<int, BundleInfo, std::greater<int>> cache;
		std::map<int, BundleInfo, std::greater<int>>::iterator cacheEnd = cache.end();
		int numRows = 0;
		void buildCache();

		ObjRef<StatisticsCollector> collector;
		
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		ExperimentQuerySource(StatisticsCollector* collector);
	};

	class DataSource : public Table::TableDataSource
	{
	protected:
		ObjRef<StatisticsCollector> curCollector;
		void throwError(std::string message) { throw message + " (for " + curCollector->holder->name + ")"; }
	public:
		DataSource(StatisticsCollector* curCollector) : curCollector(curCollector) {}
		bool isValid() { return (bool)curCollector; }

		virtual int getConstraints() const override { return READ_ONLY | BUNDLE_TYPES_ONLY; }
		engine_export virtual int __numRows() const override;
		engine_export virtual int __numCols() const override;

		virtual std::string __name() const override;

		virtual void addCol(int, int) override { throwError("Error: cannot add columns"); }
		virtual void addRow(int, int) override { throwError("Error: cannot add rows"); }
		virtual TreeNode* cell(const Variant&, const Variant&) override { throwError("Error: cannot get cell"); throw; }
		virtual void clear(int) { throwError("Error: cannot clear table"); }
		virtual void deleteCol(int) override { throwError("Error: cannot delete column"); }
		virtual void deleteRow(int) override { throwError("Error: cannot delete row"); }
		// executeCell is okay
		virtual std::string getColHeader(int colNum) override;
		// getRowHeader is okay
		virtual void moveCol(int, int) override { throwError("Error: cannnot move column"); }
		virtual void moveRow(int, int) override { throwError("Error: cannnot move row"); }
		virtual void setColHeader(int, const char*) override { throwError("Error: cannnot set column header"); }
		virtual void setRowHeader(int, const char*) override { throwError("Error: cannnot set row header"); }
		virtual void setSize(int, int, int, int) override { throwError("Error: cannnot set size"); }
		virtual void sort(const Variant&, const Variant&) override { throwError("Error: cannnot sort"); }
		virtual void swapCols(int, int) override { throwError("Error: swap columns"); }
		virtual void swapRows(int, int) override { throwError("Error: swap rows"); }

		engine_export virtual Variant getValue(int row, int col) override;
		virtual void setValue(int row, int col, const Variant& val) override { throwError("Error: cannnot set value"); }
	};

	std::shared_ptr<Table::TableDataSource> getTableDataSource();
protected:
	std::shared_ptr<Table::TableDataSource> dataSource;

protected:
	NodeListArray<CollectedDataProperty>::SdtSubNodeBindingType sharedProperties;
	static bool checkNodeForSDTType(TreeNode* obj, const char* classType);

	// This class is for allocating on the stack first, since that is usually the case,
	// and only on the heap if neccessary. It gets used in the onEventOccured() function
	template <class T, int BUFFER_SIZE = 64>
	class Buffer
	{
	protected:
		T stackBuffer[BUFFER_SIZE];
		std::unique_ptr<T[]> bigBuffer;

		T* buffer = stackBuffer;
		int _size = 0;
		int maxSize = BUFFER_SIZE;

	public:
		T& operator[](int index) { 
#ifdef _DEBUG
			if (index < 0 || index > _size)
				throw "index out of bounds";
#endif
			return buffer[index]; 
		}

		void reserve(int count) {
#ifdef _DEBUG
			if (_size > 0)
				throw "must reserve before entries are added";
#endif
			if (count > maxSize)  {
				bigBuffer = std::make_unique<T[]>(count);
				buffer = bigBuffer.get();
				maxSize = count;
			}
		}

		void push_back(T value) { 
#ifdef _DEBUG
			if (_size == maxSize) 
				throw "cannot add more values to buffer"; 
#endif
			buffer[_size++] = value; 
		}
		int size() { return _size; }
	};

public:
	double enabled = 1;
	double ignoreWarmup = 0;
	double inErrorState = 0;
	double changeCount;
	double saved = 0;
	double storeDataOnDrive = 0;

	double resetRowMode = 0;
	ByteBlock resetRowProperty;

	enum RowMode { Add = 1, Assert, Enumerate };
	double rowMode = (double)Add;
	TreeNode* rowTableObjects;
	TreeNode* rowTable;
	ByteBlock rowProperty;
	TreeNode* rowSortInfo;
	
	NodeRef instanceObject;

	double lastUpdateTime = 0;
	double updateSinceReset = 0;
	NodeRef lastUpdateEvent;

	NodeListArray<EventReference>::SdtSubNodeBindingType eventReferences;
	NodeListArray<Column>::SdtSubNodeBindingType columns;

	NodeListArray<Column>::ObjPtrType dynamicColumns;
	NodeListArray<FlexSimEvent>::CouplingSdtPtrType liveListeners;

	BundleMember data;
	TreeNode* rowScores;

	engine_export TreeNode* addEventReference(TreeNode* object, const char* eventName);
	engine_export TreeNode* addTimerEventReference();
	engine_export const char* getEventReferenceType(TreeNode* eventReference);
	engine_export void updateEventReferenceParams(TreeNode* eventReference);
	engine_export TreeNode* addPropertyToEventReference(TreeNode* eventReference);
	engine_export TreeNode* addSharedProperty();
	engine_export TreeNode* addRowSortInfo();

protected:
	void addColumnInternal(Column* newColumn);
public:
	engine_export TreeNode* addColumn(const char* type);

	engine_export void linkColumnAndEvent(TreeNode* column, TreeNode* eventRef);
	engine_export void unlinkColumnAndEvent(TreeNode* column, TreeNode* eventRef);
	engine_export void unlinkAllEvents(TreeNode* column);
	engine_export void unlinkAllColumns(TreeNode* eventRef);

	engine_export Array getEventsForColumn(TreeNode* column);

	engine_export TreeNode* addRowTableObject(TreeNode* object);
	void updateRowTable();

	void onEventOccured(EventReference* eventReference,
		TreeNode* eventObject, const char* eventName, TreeNode* instanceObject, CallPoint* listenerCP, int flags = 0);

	engine_export void update();

	engine_export Array getUniquePropertyNames();

	engine_export CollectedDataInterface __getCollectedData() { return CollectedDataInterface(&__collectedData); }
	__declspec(property (get = __getCollectedData)) CollectedDataInterface collectedData;

	engine_export TreeNode* __getData() { return data; }

	engine_export const char* __getRowObjectsProperty() { return rowProperty.getBuffer(); }
	engine_export void __setRowObjectsProperty(const char* prop) { rowProperty.write(prop); }

	engine_export int __getRowMode() { return (int)rowMode; }
	engine_export void __setRowMode(int value) { rowMode = value; }

	engine_export TreeNode* __getInstanceObject() { return instanceObject; }
	engine_export void __setInstanceObject(TreeNode* obj) { instanceObject = obj; }

	engine_export operator Table();
	engine_export operator TreeNode*() { return holder; }

	// These methods allow access to some column metadata
	engine_export int getColumnFormat(int columnNr) override;
	engine_export Array getColumnFormats() override;

	engine_export static StatisticsCollector* createGlobal();
	engine_export static StatisticsCollector* getGlobal(const Variant& id);

	engine_export void onReset();
	engine_export void onPostReset();
	void createListeners();
	void createEvents();
	engine_export void onRunWarm();
	// double onStartSimulation() override;

	// Events
protected:
	TreeNode* onRowAdded = nullptr;
	TreeNode* onRowUpdated = nullptr;
	Array columnsUpdated;
	Array previousValues;
public:

	// getEventInfo
	engine_export virtual TreeNode* getEventInfoObject(const char* eventTitle);

	// Bind
	engine_export virtual void bindEvents() override;
	engine_export virtual void bindVariables() override;
	engine_export virtual void bindInterface() override;

	// ID Service functions
	engine_export static double getID(TreeNode* object) { return IDService::getID(object); }

	engine_export static int isValueID(double id) { return IDService::isValueID(id); }
	engine_export static TreeNode* getObjectFromID(double id) { return IDService::getObjectFromID(id); }
	engine_export static const char* getPathFromID(double id) { return IDService::getPathFromID(id); }

	engine_export static void clearIDs() { IDService::clear(); }

	engine_export Variant getDBExportColumnExpression(const char* colName, int dbDataType);

	virtual StatisticsCollector* toStatisticsCollector() { return this; }
};

class CalculatedTable : public ColumnFormatter
{
protected:
	bool shouldUpdate() const;

public:
	class Timer : public FlexSimEvent
	{
	public:
		virtual void execute() override;
		virtual const char* getClassFactory() { return "CalculatedTableTimer"; }
	};

	class QuerySource : public SqlDataSource
	{
	public:
		virtual int getColID(int tableId, const char* colName, int& colFlags) override;
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		// I don't need to set the value; collector tables are read-only for queries
		// I don't need to worry about table ID either
		virtual int getRowCount(int tableID) override;
		ObjRef<CalculatedTable> table;
		QuerySource(CalculatedTable* table) : table(table) {}
	};

	class DataSource : public Table::TableDataSource
	{
	protected:
		ObjRef<CalculatedTable> table;
		void throwError(std::string message) { throw message + " (for " + table->holder->name + ")"; }
	public:
		DataSource(CalculatedTable* table) : table(table) {}
		bool isValid() { return (bool)table; }

		virtual int getConstraints() const override { return READ_ONLY | BUNDLE_TYPES_ONLY; }
		engine_export virtual int __numRows() const override;
		engine_export virtual int __numCols() const override;

		virtual std::string __name() const override;

		virtual void addCol(int, int) override { throwError("Error: cannot add columns"); }
		virtual void addRow(int, int) override { throwError("Error: cannot add rows"); }
		virtual TreeNode* cell(const Variant&, const Variant&) override { throwError("Error: cannot get cell"); throw; }
		virtual void clear(int) { throwError("Error: cannot clear table"); }
		virtual void deleteCol(int) override { throwError("Error: cannot delete column"); }
		virtual void deleteRow(int) override { throwError("Error: cannot delete row"); }
		// executeCell is okay
		virtual std::string getColHeader(int colNum) override;
		// getRowHeader is okay
		virtual void moveCol(int, int) override { throwError("Error: cannnot move column"); }
		virtual void moveRow(int, int) override { throwError("Error: cannnot move row"); }
		virtual void setColHeader(int, const char*) override { throwError("Error: cannnot set column header"); }
		virtual void setRowHeader(int, const char*) override { throwError("Error: cannnot set row header"); }
		virtual void setSize(int, int, int, int) override { throwError("Error: cannnot set size"); }
		virtual void sort(const Variant&, const Variant&) override { throwError("Error: cannnot sort"); }
		virtual void swapCols(int, int) override { throwError("Error: swap columns"); }
		virtual void swapRows(int, int) override { throwError("Error: swap rows"); }

		engine_export virtual Variant getValue(int row, int col) override;
		virtual void setValue(int row, int col, const Variant& val) override { throwError("Error: cannnot set value"); }
	};

	std::shared_ptr<Table::TableDataSource> dataSource;
	std::shared_ptr<Table::TableDataSource> getTableDataSource();

	// Inputs
	ByteBlock query;
	enum UpdateMode { Manual = 0, ByInterval = 1, Always = 2, LazyInterval = 3 };
	double updateMode = 0;
	double updateInterval = 0;
	double enabled = 1;
	double updateCount = 0;
	double displayTimeAsText = 0;

	TreeNode* formatList;

	// Internal state
	TreeNode* queryNode;

	// This gets set for unrecoverable errors (sql build or query errors)
	double buildFailed = 0;
	ByteBlock badQuery;

	// and here's the last update time
	double lastUpdateTime = -1;
	double updateSinceReset = 0;
	NodeRef lastUpdateEvent;

	// and here's where the result gets dumped
	BundleMember data;

	engine_export static CalculatedTable* getGlobal(const Variant& queryTable);

	// OnReset - build the sql query, and run it for the first time
	engine_export void onReset();
	bool isQueryBuildable();

	// update runs the query, and dumps the table
	engine_export void update(int force = 0);
	void updateFormatList();

	engine_export int getColumnFormat(int columnNr) override;
	engine_export Array getColumnFormats() override;

	engine_export int dependsOnExperimentData();

	engine_export virtual void bindVariables() override;

	virtual CalculatedTable* toCalculatedTable() { return this; }
};

}