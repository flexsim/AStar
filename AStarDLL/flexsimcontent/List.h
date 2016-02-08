#pragma once

#include "basicclasses.h"
#include "objectdatatype.h"
#include "couplingdatatype.h"
#include "byteblock.h"
#include "flexsimevent.h"
#include <unordered_map>


class List : public ObjectDataType
{
	friend SimpleDataType* engine_createsdtderivative(char* classname, TreeNode* holder);
public:
	int repaintMatchId = 0;
	// flags for pulling
	static const int ALLOCATE_ALL_OR_NOTHING = 0x1;
	static const int PARSE_QUERY = 0x2;
	static const int PULL_ENTRY_NODES = 0x4;
	static const int DO_NOT_REMOVE = 0x8;
	static const int DO_NOT_BACK_ORDER = 0x10;
	static const int PULL_BACK_ORDERS = 0x20;
	static const int DO_NOT_FULFILL = 0x40;

	static const int COL_ID_VALUE = INT_MAX - 1;
	static const int COL_ID_PULLER = INT_MAX - 2;
	static const int COL_ID_REQUESTED = INT_MAX - 3;
	static const int COL_ID_REQUIRED = INT_MAX - 4;
	List() : defaultDataSource(0), backOrderQueueStrategyDataSource(0), defaultBackOrderDataSource(0) {}

	class Entry : public CouplingDataType
	{
		friend class List;
		friend class ListViewDataSource;
	public:
		Entry(size_t numFields, const Variant& value);
		Entry() {}
		bool getEntryNodes = false;
	private:
		virtual const char* getClassFactory() { return "ListEntry"; }
		virtual void bind();
		std::vector<Variant> staticFields;
		double pushTime;
		Variant value;
		bool hasListeners = false;
		const Variant* puller = nullptr;
		TreeNode* onPull = nullptr;
		virtual void bindEvents() override;
	};

	class LabelField;
	class Field : public SimpleDataType
	{
		friend class List;
		friend class ListViewDataSource;
	public:
		engine_export virtual void bind() override;
		engine_export virtual void bindStatistics() override;
		engine_export void bindEvents() override { bindStatisticsAsEvents(); }
		void reset(List* list);
		double isDynamic;
		double staticIndex;
		bool shouldTrackTotal(List* list) { return !isDynamic && list->trackStaticFieldTotals; }
		TreeNode* total = nullptr;
		TreeNode* totalInput = nullptr;
		TreeNode* totalOutput = nullptr;
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) { return Variant(); }
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) { return Variant(); }
		virtual bool needsPuller() { return false; }
		virtual LabelField* toLabelField() { return nullptr; }
	};

	class LabelField : public Field
	{
		virtual const char* getClassFactory() override { return "ListLabelField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) override;
		virtual LabelField* toLabelField() { return this; }
	};
	class ExpressionField : public Field
	{
		treenode expression;
		virtual void bind() override;
		virtual const char* getClassFactory() { return "ListExpressionField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
		virtual Variant evaluateOnQuery(Entry* entry, const Variant& requester) override;
		virtual bool needsPuller() override;
	};
	class PushArgumentField : public Field
	{
		double paramNum;
		virtual void bind() override;
		virtual const char* getClassFactory() override { return "ListPushArgumentField"; }
		virtual Variant evaluateOnAdd(Entry* entry, const VariantParams& params) override;
	};

	struct OverflowTrackableValue
	{
		TreeNode* labelNode = nullptr;
		Variant* varRef = nullptr;
		Field* fieldRef = nullptr;
	};

	class Partition;
	class ListSqlDataSource : public SqlDataSource
	{
	public:
		ListSqlDataSource() {}
		ListSqlDataSource(List* list) : list(list) {}
		virtual const char* getClassFactory() override { return "ListSqlDataSource"; }
		virtual void bind() override;
		virtual int getColId(int tableId, const char* colName) override;
		void reset();
		void onModelReset();
		virtual const char* enumerateColNames(int tableId, int colNum) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		virtual int getTableId(const char* tableName) override;
		virtual int getRowCount(int tableId) override;
		virtual OverflowTrackableValue getOverflowTrackableValue(int row, int colId);

		TreeNode* curPuller = 0;
		List* list;
		Partition* partition;
		TreeNode* sqlParse = 0;
		bool queryHasSelectStatement = false;
		std::vector<std::string> labelNames;
		void assertSQLParse();
		void setQuery(SqlQuery* q);
		static const int VALUE_TABLE = 0;
		static const int PULLER_TABLE = 1;
	};
	class ListBackOrderSqlDataSource : public ListSqlDataSource
	{
	public:
		ListBackOrderSqlDataSource() : ListSqlDataSource() {}
		ListBackOrderSqlDataSource(List* list) : ListSqlDataSource(list) {}
		virtual const char* getClassFactory() override { return "ListBackOrderSqlDataSource"; }
		virtual void bind() override;
		virtual int getColId(int tableId, const char* colName) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		virtual int getRowCount(int tableId) override;
		int curEntryRow = 0;
	};

	struct EntryRange {
		EntryRange() {}
		EntryRange(int begin, int end) : begin(begin), end(end) {}
		int begin;
		int end;
	};

	class BackOrder : public ListSqlDataSource
	{
	public:
		BackOrder() {}
		BackOrder(List* list, double numRequested, double numRequired, double numFulfilled,
			const Variant& puller, Partition* partition, int flags, ListSqlDataSource* originalDelegate)
			: ListSqlDataSource(list), numRequested(numRequested), numRequired(numRequired), numFulfilled(numFulfilled),
			puller(puller), flags(flags), originalDelegate(originalDelegate)
		{
			orderTime = time();
			incrementalAllocation = !(flags & List::ALLOCATE_ALL_OR_NOTHING);
			this->partition = partition;
		}
		virtual const char* getClassFactory() override { return "ListBackOrder"; }
		virtual void bind() override;
		double numFulfilled;
		double numRequired;
		double numRequested;
		double lastFulfillQty = 0.0;
		double orderTime;
		Variant puller;
		int flags;
		bool incrementalAllocation;
		EntryRange range;
		ListSqlDataSource* originalDelegate;
		enum class Fulfillment {
			None,
			Partial,
			Full
		};
		Fulfillment checkFulfill(EntryRange& range);
		virtual int getRowCount(int tableId) override;
		virtual Variant getValue(int tableId, int row, int colId) override;
		virtual OverflowTrackableValue getOverflowTrackableValue(int row, int colId) override;
		TreeNode* onFulfill = nullptr;
		virtual void bindEvents() override;
		Variant value;
	};

	struct PushResult
	{
		PushResult() {}
		PushResult(const Variant& val) { addToResult(returnVal); }
		PushResult(PushResult&& other) : returnVal(std::move(other.returnVal)), returnArray(std::move(other.returnArray)) {  }
		Variant returnVal;
		std::unique_ptr<std::vector<Variant>> returnArray;
		int numResults = 0;
		Variant getResult();
		void addToResult(const Variant& puller);
	};

	typedef NodeListArray<Entry>::CouplingSdtSubNodeType EntryList;

	NodeListArray<Field>::SdtSubNodeType fields;
	double numTrackingFields;
	double trackStaticFieldTotals;
	NodeListArray<Entry>::CouplingSdtSubNodeType removedEntries;
	TreeNode* contentsOnReset;

	ByteBlock listType;	
protected:
	std::vector<int> staticFields;
	std::vector<int> dynamicFields;
	void cacheFieldIndices();
	void cacheBackOrderIndices();
	Variant push(const VariantParams& params);
	static Variant curPuller;

	class PartitionHash
	{
	public:
		size_t operator() (const Variant& pullerKey);
	};

	class VariantKeyEqual
	{
	public:
		bool operator() (const Variant& a, const Variant& b);
	};

public:
	// Events
	TreeNode* onPush = nullptr;
	TreeNode* onPull = nullptr;

	class Partition : public SimpleDataType
	{
	public:
		Partition() {}
		Partition(Variant partitionID, List* list) : id(partitionID), list(list) {}

		std::unordered_map<Variant, Entry*, PartitionHash, VariantKeyEqual> entryMap;
		std::unordered_map<Variant, BackOrder*, PartitionHash, VariantKeyEqual> backOrderMap;

		NodeListArray<BackOrder>::SdtSubNodeBindingType backOrders;
		NodeListArray<Entry>::CouplingSdtSubNodeBindingType entries;

		Variant id;
		List* list;

		std::vector<BackOrder*> backOrderCallbacks;
		NodeListArray<BackOrder>::SdtSubNodeType backOrdersToRemove;
		NodeListArray<Entry>::SdtSubNodeType entriesToRemove;
		/// <summary>	The overflow entry. This is only valid if there is a select clause in the 
		/// 			pull query. If there is an entry it is pulled but not removed (there is leftover
		/// 			then this pointer will be set so it can call its onPull. </summary>
		Entry* overflowEntry = nullptr;

		engine_export virtual void bind() override;
		virtual const char* getClassFactory() override { return "ListPartition"; }

		Variant pull(SqlQuery* q, double requestNum, double requireNum, const Variant& puller, int flags);
		Variant pullBackOrders(SqlQuery* q, double requestNum, const Variant& value, int flags);
		double calculateFulfillQty(int queryMatchIndex, SqlQuery* q, OverflowTrackableValue* tracker);
		/// <summary>	Gets the result from the last pull query. </summary>
		/// <remarks>	Returns either a scalar value or an array, depending on what the query is. Also,
		/// 			this will remove the entries that are fulfilled. </remarks>
		/// <param name="numMatches">		  	Number of matching entries in the last pull query. </param>
		/// <param name="q">				  	[in] The SqlQuery* to process. </param>
		/// <param name="puller">			  	The puller. </param>
		/// <param name="shouldRemoveEntries">	true if should remove entries. </param>
		/// <param name="range">			  	[in, out] The entry range that is currently active. </param>
		/// <param name="getEntryNodes">	  	true if you want to return the entry nodes instead of just
		/// 									the values of the entries. </param>
		/// <param name="fulfillQty">		  	[out] The fulfill qty. This is calculated within getResult(), and returned. </param>
		/// <param name="maxFulfillQty">	  	The maximum fulfill qty. Mostly needed for pull queries with a select 
		/// 									statement. Here the request num is a potentially continuous value, and
		/// 									the fulfill qty is incremented as it traverses the result, until it
		/// 									reaches the maximum fulfill qty.</param>
		/// <param name="innerRange">		  	[in,out] (Optional) If non-null, (Optional) the inner range.
		/// 									range. </param>
		/// <returns>	The result. </returns>
		Variant getResult(int numMatches, SqlQuery* q, const Variant& puller, bool shouldRemoveEntries,
			EntryRange& range, bool getEntryNodes, double& fulfillQty, double maxFulfillQty, EntryRange* innerRange = nullptr);

		Variant push(const VariantParams& params);
		PushResult matchEntriesToBackOrders(EntryRange range);
		engine_export virtual Variant getEntryValue(int entryIndex, int fieldId);

		Entry* addEntry(Entry* entry, const VariantParams& params);
		void removeEntry(Entry* entry, bool getEntryNodes, bool fireOnPull);
		BackOrder* addBackOrder(BackOrder* backOrder, SqlQuery* q);
		void removeBackOrder(BackOrder* backOrder, bool fireOnFulfill);

		bool isEmpty() { return entries.size() == 0 && backOrders.size() == 0; };

		engine_export virtual void bindEvents() override;
		std::pair<int, int> getListLevels() { return { entries.size(), backOrders.size() }; }
		double getCurListLevel() { return entries.size(); }
		double getCurBackOrderLevel() { return backOrders.size(); }

		engine_export virtual void bindStatistics() override;
		TreeNode* content = nullptr;
		TreeNode* input = nullptr;
		TreeNode* output = nullptr;
		TreeNode* staytime = nullptr;

		TreeNode* backOrderContent = nullptr;
		TreeNode* backOrderInput = nullptr;
		TreeNode* backOrderOutput = nullptr;
		TreeNode* backOrderStaytime = nullptr;
	};

	NodeListArray<Partition>::SdtSubNodeBindingType partitions;
	NodeListArray<Partition>::SdtSubNodeBindingType deadPartitions;
	std::unordered_map<Variant, Partition*, PartitionHash, VariantKeyEqual> partitionMap;
	
	double uniqueValues;
	double uniquePullers;
	
	Partition* assertPartition(const Variant& partitionID);
	void removePartition(Partition& partition);
	void endPartitionOperation(Partition& partition, std::pair<int, int>& previousLevels);

	ListSqlDataSource* defaultDataSource;
	NodeListArray<ListSqlDataSource>::SdtSubNodeBindingType parsedQueries;
	NodeListArray<ListBackOrderSqlDataSource>::SdtSubNodeBindingType parsedBackOrderQueries;
	std::unordered_map<const char*, ListSqlDataSource*, CharStrHash, CharStrEquals> backOrderQueryCache;
	
	/// <summary>	boolean whether the list should cache queries. </summary>
	double cacheQueries;
	std::unordered_map<const char*, ListSqlDataSource*, CharStrHash, CharStrEquals> queryCache;

	ByteBlock backOrderQueueStrategy;
	ListBackOrderSqlDataSource* defaultBackOrderDataSource;
	ListBackOrderSqlDataSource* backOrderQueueStrategyDataSource;
	TreeNode* backOrderQueueStrategyDataSourceNode;

	void buildQueryCache();

public:
	static bool isVariantNonNull(const Variant& partitionID);

	/// <summary>	Gets the result from a pull query and, if needed, removes the pulled entries. </summary>
	/// <remarks>	This is called by a pull operation if valid results are pulled, and from the 
	/// 			back order fulfillment mechanism. </remarks>
	/// <param name="numMatches">				Number of matches previously returned from an sql query. </param>
	/// <param name="q">						The SqlQuery to retrieve the result from. </param>
	/// <param name="puller">					The puller. </param>
	/// <param name="removeEntries">			true if result entries should be removed. </param>
	/// <param name="range">					[in,out] The range of entries that were queried. </param>
	/// <param name="partitionID">				Partition ID. </param>
	/// <param name="getEntryNodes">			If true, the result will get the entry nodes instead of their associated values. </param>
	/// <param name="innerRange">				[in,out] An optional inner range. This is used 
	/// 										for all-or-nothing back order fulfillment. When this type of back order tries to be 
	/// 										fulfilled, it will set the normal range to the full range of entries because it needs
	/// 										to query the full list again. However, it also needs to track how the "incremental
	/// 										range" was changed so that the incremental range integrity will be preserved when 
	/// 										fulfilling multiple back orders. So it passes the incremental range as an "innerRange",
	/// 										the getResult() will properly update innerRange if entries from within that innerRange
	/// 										are removed.</param>
	/// <returns>	The result. </returns>
	Variant getResult(int numMatches, SqlQuery* q, const Variant& puller, bool removeEntries, EntryRange& range, const Variant& partitionID, bool getEntryNodes, EntryRange* innerRange = nullptr);


	// statistics
	TreeNode* content = nullptr;
	TreeNode* input = nullptr;
	TreeNode* output = nullptr;
	TreeNode* staytime = nullptr;

	TreeNode* backOrderContent = nullptr;
	TreeNode* backOrderInput = nullptr;
	TreeNode* backOrderOutput = nullptr;
	TreeNode* backOrderStaytime = nullptr;
	
	TreeNode* getBackOrderList(const Variant& partitionID);
	TreeNode* getEntryList(const Variant& partitionID);
	int getTotalBackOrders();
	engine_export virtual void bindVariables() override;
	engine_export virtual void bindEvents() override;
	engine_export virtual void bindStatistics() override;
	engine_export TreeNode* getPartitionNode(const Variant& partitionID);
	engine_export TreeNode* partitionResolver(const Variant& partitionID);
	engine_export int getPartitionPossibilities(TreeNode* dest, const Variant& p1, const Variant& p2);
	engine_export TreeNode* fieldResolver(const Variant& fieldID);
	engine_export int getFieldPossibilities(TreeNode* dest, const Variant& p1, const Variant& p2);
	engine_export virtual void onReset();
	engine_export virtual int getFieldId(const char* fieldName);
	engine_export virtual const char* enumerateColNames(int colNum);
	engine_export Variant push(const Variant& involved);
	engine_export Variant push(const Variant& involved, const Variant& partitionID);
	engine_export Variant push(const Variant& involved, const Variant& partitionID, const Variant& p1);
	engine_export Variant push(const Variant& involved, const Variant& partitionID, const Variant& p1, const Variant& p2);
	engine_export Variant push(const Variant& involved, const Variant& partitionID, const Variant& p1, const Variant& p2, const Variant& p3);
	engine_export Variant push(const Variant& involved, const Variant& partitionID, const Variant& p1, const Variant& p2, const Variant& p3, const Variant& p4, const Variant& p5 = Variant(), const Variant& p6 = Variant(),
		const Variant& p7 = Variant(), const Variant& p8 = Variant());

private:
	ListSqlDataSource* processQuery(const char* sqlQuery, int flags, TreeNode* parsedContainer, bool isBackOrderQuery);
	inline Variant pull(SqlQuery* q, double requestNum, double requireNum, const Variant& puller, const Variant& partitionID, int flags);
	inline Variant pullBackOrders(SqlQuery* q, double requestNum, const Variant& value, const Variant& partitionID, int flags);
	Variant pullBackOrders(const char* sqlQuery, double requestNum, const Variant& value, const Variant& partitionID, int flags);
	Variant pullBackOrders(TreeNode* cachedQuery, double requestNum, const Variant& value, const Variant& partitionID, int flags);
public:
	engine_export Variant pull(const char* sqlQuery, double requestNum, double requireNum, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);
	engine_export Variant pull(TreeNode* cachedQuery, double requestNum, double requireNum, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);

	engine_export void listenToEntry(treenode entry, treenode callback, const Variant& p1);


public:
	class BackOrderListener;
	class BackOrderListenerEvent : public FlexSimEvent
	{
	public:
		BackOrderListenerEvent() : FlexSimEvent() {}
		BackOrderListenerEvent(List* list, double eventCode): 
			list(list), listenerType(BackOrderListener::GLOBAL), isEventQueueEvent(false),
			FlexSimEvent(nullptr, 0.0, nullptr, (int)eventCode, nullptr) {}
		BackOrderListenerEvent(List* list, Entry* entry, double eventCode, bool isEventQueueEvent) : 
			list(list), listenerType(BackOrderListener::VALUE_BASED), isEventQueueEvent(isEventQueueEvent),
			FlexSimEvent(isEventQueueEvent ? list->holder : nullptr, isEventQueueEvent ? ::time() : 0.0, entry->holder, (int)eventCode, nullptr) {}
		BackOrderListenerEvent(List* list, BackOrder* backOrder, double eventCode, bool isEventQueueEvent): 
			list(list), listenerType(BackOrderListener::PULLER_BASED), isEventQueueEvent(isEventQueueEvent),
			FlexSimEvent(isEventQueueEvent ? list->holder : nullptr, isEventQueueEvent ? ::time() : 0.0, backOrder->holder, (int)eventCode, nullptr) {}
		BackOrderListenerEvent(List* list, double time, BackOrderListener* timeIntervalListener): 
			list(list),	listenerType(BackOrderListener::TIME_INTERVAL), timeIntervalListener(timeIntervalListener), 
			FlexSimEvent(list->holder, time, nullptr, 0, nullptr), isEventQueueEvent(false) {}

		virtual const char* getClassFactory() override { return "ListBackOrderListenerEvent"; }
		virtual void execute() override;
		virtual void bind() override;
		int listenerType;
		List* list;
		BackOrderListener* timeIntervalListener = nullptr;
		bool executingNow = false;
		bool isEventQueueEvent;
	};
	class BackOrderListener : public SimpleDataType
	{
	public:
		BackOrderListener() {}
		BackOrderListener(int theListenerType) { listenerType = theListenerType; }
		virtual const char* getClassFactory() override { return "ListBackOrderListener"; }
		List* list;
		treenode focusExpression;
		treenode eventExpression;
		NodeRef focus;
		static const int PULLER_BASED = 1;
		static const int VALUE_BASED = 2;
		static const int GLOBAL = 3;
		static const int TIME_INTERVAL = 4;
		double listenerType;
		ObjRef<BackOrderListenerEvent> timeIntervalEvent;
		virtual void bind() override;
		void createNextTimeIntervalEvent();
	};
	ListBackOrderSqlDataSource* defaultBackOrderListener;
	NodeListArray<BackOrderListener>::SdtSubNodeType backOrderListeners;
	NodeListArray<BackOrderListener>::ObjPtrType valueBackOrderListeners;
	NodeListArray<BackOrderListener>::ObjPtrType pullerBackOrderListeners;
	NodeListArray<BackOrderListener>::ObjPtrType globalBackOrderListeners;
	NodeListArray<BackOrderListener>::ObjPtrType timeIntervalBackOrderListeners;
	treenode globalListenerPointers;

	double keepEmptyPartitions = 0;

	void addValueListeners(Entry* entry);
	void addPullerListeners(BackOrder* backOrder);
	void addGlobalListeners();
	void addTimeIntervalListeners();

	void removeGlobalListeners();
	void removeTimeIntervalListeners();

	void reevaluateBackOrder(BackOrder* backOrder);
	void reevaluateBackOrders(Entry* entry);
	void reevaluateBackOrders();

	static bool hasSelectStatement(SqlQuery* q);
	engine_export virtual TreeNode* getEventInfoObject(const char* eventTitle) override;

	/// <summary>	Manually removes the given node, whether it is an entry or a back order. </summary>
	/// <remarks>	Anthony.johnson, 9/28/2015. </remarks>
	/// <param name="node">	[in,out] If non-null, the node to remove. </param>
	engine_export static void remove(TreeNode* node);
};

#ifdef FLEXSIM_ENGINE_COMPILE
engine_export Variant listpush(const char* listName, const Variant& involved);
engine_export Variant listpush(treenode list, const Variant& involved);
engine_export Variant listpush(const char* listName, const Variant& involved, const Variant& partitionID, const Variant& p1, const Variant& p2,
                                            const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6,
                                            const Variant& p7, const Variant& p8);
engine_export Variant listpush(treenode list, const Variant& involved);
engine_export Variant listpush(treenode list, const Variant& involved, const Variant& partitionID, const Variant& p1, const Variant& p2,
                                            const Variant& p3, const Variant& p4, const Variant& p5, const Variant& p6,
                                            const Variant& p7, const Variant& p8);
engine_export treenode listbackorders(TreeNode* listNode, const Variant& partitionID);
engine_export treenode listentries(TreeNode* listNode, const Variant& partitionID);
engine_export Variant listpull(TreeNode* listNode, TreeNode* cachedQuery, double requestNum = 1, double requireNum = 1, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);
engine_export Variant listpull(TreeNode* listNode, const char* query, double requestNum = 1, double requireNum = 1, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);
engine_export Variant listpull(const char* listName, TreeNode* cachedQuery, double requestNum = 1, double requireNum = 1, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);
engine_export Variant listpull(const char* listName, const char* query, double requestNum = 1, double requireNum = 1, const Variant& puller = Variant(), const Variant& partitionID = Variant(), int flags = 0);

engine_export void listremove(TreeNode* entryOrBackOrderNode);

#endif
