<?xml version="1.0" encoding="UTF-8"?>
<flexsim-tree version="3" treetype="tree">
<node f="42"><name>AStar</name>
 <node f="40"><name></name></node>
 <node f="42"><name>installdata</name>
  <node f="40"><name></name></node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/library</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000403b0000</data></node>
    <node f="42" dt="2"><name>after</name><data>dynamo</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>astar</name>
      <node f="40"><name></name></node>
      <node f="10100042" dt="4"><name>AStarNavigator</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>Navigator</name><data><coupling>null</coupling></data></node>
       </node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::AStarNavigator</name><data><coupling>/installdata/add/1/data/astar/AStarNavigator</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>nodeWidth</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>surroundDepth</name><data>0000000040000000</data></node>
        <node f="42" dt="1"><name>drawMode</name><data>0000000040370000</data></node>
        <node f="42" dt="1"><name>defaultPathWeight</name><data>9999999a3fd99999</data></node>
        <node f="42" dt="1"><name>deepSearch</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>ignoreDestBarrier</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>hasEdgeTable</name><data>0000000000000000</data></node>
        <node f="42"><name>barriers</name></node>
        <node f="42" dt="3"><name>activeBarrier</name><data><coupling>null</coupling></data></node>
        <node f="42"><name>fixedResourceBarriers</name></node>
        <node f="42" dt="1"><name>cachePaths</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>pathCount</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>requestCount</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>cacheUseCount</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>enableCollisionAvoidance</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>smoothRotations</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>showAllocations</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>showHeatMap</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>heatMapMode</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>maxHeatValue</name><data>9999999a3fb99999</data></node>
        <node f="42" dt="1"><name>collisionUpdateIntervalFactor</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>ignoreInactiveMemberCollisions</name><data>000000003ff00000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="1000042" dt="2"><name>addBarrier</name><data>dll:"module:AStar" func:"AStarNavigator_addBarrier"</data></node>
         <node f="1000042" dt="2"><name>addMember</name><data>dll:"module:AStar" func:"AStarNavigator_addMember"</data></node>
         <node f="1000042" dt="2"><name>addPoint</name><data>dll:"module:AStar" func:"Barrier_addPoint"</data></node>
         <node f="1000042" dt="2"><name>getActiveBarrierMode</name><data>dll:"module:AStar" func:"AStarNavigator_getActiveBarrierMode"</data></node>
         <node f="1000042" dt="2"><name>getBarrierType</name><data>dll:"module:AStar" func:"Barrier_getBarrierType"</data></node>
         <node f="1000042" dt="2"><name>getPathWeight</name><data>dll:"module:AStar" func:"PreferredPath_getWeight"</data></node>
         <node f="1000042" dt="2"><name>getPointCoord</name><data>dll:"module:AStar" func:"Barrier_getPointCoord"</data></node>
         <node f="1000042" dt="2"><name>rebuildMeshes</name><data>dll:"module:AStar" func:"AStarNavigator_rebuildMeshes"</data></node>
         <node f="1000042" dt="2"><name>removeBarrier</name><data>dll:"module:AStar" func:"AStarNavigator_removeBarrier"</data></node>
         <node f="1000042" dt="2"><name>removeMember</name><data>dll:"module:AStar" func:"AStarNavigator_removeMember"</data></node>
         <node f="1000042" dt="2"><name>removePoint</name><data>dll:"module:AStar" func:"Barrier_removePoint"</data></node>
         <node f="1000042" dt="2"><name>setActiveBarrier</name><data>dll:"module:AStar" func:"AStarNavigator_setActiveBarrier"</data></node>
         <node f="1000042" dt="2"><name>setActiveIndex</name><data>dll:"module:AStar" func:"Barrier_setActiveIndex"</data></node>
         <node f="1000042" dt="2"><name>setPathWeight</name><data>dll:"module:AStar" func:"PreferredPath_setWeight"</data></node>
         <node f="1000042" dt="2"><name>setPointCoords</name><data>dll:"module:AStar" func:"Barrier_setPointCoords"</data></node>
         <node f="1000042" dt="2"><name>swapBarriers</name><data>dll:"module:AStar" func:"AStarNavigator_swapBarriers"</data></node>
         <node f="1000042" dt="2"><name>swapPoints</name><data>dll:"module:AStar" func:"Barrier_swapPoints"</data></node>
         <node f="1000042" dt="2"><name>setEditMode</name><data>dll:"module:AStar" func:"AStarNavigator_setEditMode"</data></node>
         <node f="1000042" dt="2"><name>setBarrierMode</name><data>dll:"module:AStar" func:"Barrier_setMode"</data></node>
         <node f="1000042" dt="2"><name>onMouseMove</name><data>dll:"module:AStar" func:"AStarNavigator_onMouseMove"</data></node>
         <node f="1000042" dt="2"><name>onClick</name><data>dll:"module:AStar" func:"AStarNavigator_onClick"</data></node>
         <node f="1000042" dt="2"><name>blockGridModelPos</name><data>dll:"module:AStar" func:"AStarNavigator_blockGridModelPos"</data></node>
         <node f="1000042" dt="2"><name>dumpBlockageData</name><data>dll:"module:AStar" func:"AStarNavigator_dumpBlockageData"</data></node>
         <node f="1000042" dt="2"><name>addCopiedMember</name><data>dll:"module:AStar" func:"AStarNavigator_addMember"</data></node>
        </node>
        <node f="42"><name>cppfunctions</name>
         <node f="40"><name></name></node></node>
        <node f="42"><name>cppvariables</name></node>
       </node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node>
        <node f="42" dt="7"><name>state_current</name><data/>
         <node f="40"><name></name></node>
         <node f="42" dt="6"><name>profile</name><data f="1">
          <fields>
           <field name="state" bytesize="36" type="3"/>
           <field name="time" bytesize="8" type="1"/>
           <field name="active" bytesize="4" type="2"/>
          </fields>
          <entry><ed>none</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>idle</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>processing</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>busy</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>blocked</ed><ed>0000000000000000</ed><ed>1</ed></entry>
          <entry><ed>generating</ed><ed>0000000000000000</ed><ed>1</ed></entry>
          <entry><ed>empty</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>collecting</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>releasing</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>waiting for operator</ed><ed>0000000000000000</ed><ed>0</ed></entry>
          <entry><ed>waiting for transporter</ed><ed>0000000000000000</ed><ed>1</ed></entry></data></node>
         <node f="42" dt="2"><name>sdt::attributetree</name><data>TrackedVariable</data>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>type</name><data>0000000040080000</data></node>
          <node f="42" dt="1"><name>flags</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>curValue</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>startValue</name><data>0000000000000000</data></node>
         </node>
        </node>
        <node f="42" dt="1"><name>collisionUpdateInterval</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>nextCollisionUpdateTime</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>visual</name>
        <node f="40"><name></name></node>
        <node f="42"><name>color</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>red</name><data>1d1d1d1d3fcd1d1d</data></node>
         <node f="42" dt="1"><name>green</name><data>525252523fd25252</data></node>
         <node f="42" dt="1"><name>blue</name><data>3a3a3a3a3fea3a3a</data></node>
        </node>
        <node f="42" dt="2"><name>shape</name><data>modules\AStar\shapes\AStar.3ds</data></node>
        <node f="42" dt="1"><name>shapeindex</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>imageobject</name><data>***</data></node>
        <node f="42" dt="1"><name>imageindexobject</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>imagebase</name><data>***</data></node>
        <node f="42" dt="1"><name>imageindexbase</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>special</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>title</name><data>AStar Navigator</data></node>
        <node f="42" dt="2"><name>description</name><data></data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/Pages/AStarParameters</data></node>
        <node f="42" dt="2"><name>tooltip</name><data></data></node>
       </node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>8f5c28f63ff0f5c2</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>8f5c28f63ff0f5c2</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>0a3d70a43fe0a3d7</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>centroid</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>offsetx</name><data>000000003fe00000</data></node>
        <node f="42" dt="1"><name>offsety</name><data>e00000003fdffffd</data></node>
        <node f="42" dt="1"><name>offsetz</name><data>400000003fba6f5d</data></node>
        <node f="42" dt="1"><name>offsetsx</name><data>e00000003fee53a9</data></node>
        <node f="42" dt="1"><name>offsetsy</name><data>400000003fee53aa</data></node>
        <node f="42" dt="1"><name>offsetsz</name><data>600000003ffeb86a</data></node>
        <node f="42" dt="1"><name>offsetrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>offsetry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>offsetrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>objectinfo</name>
        <node f="40"><name></name></node>
        <node f="42"><name>info1</name></node>
        <node f="42"><name>info2</name></node>
       </node>
       <node f="42" dt="1"><name>ignoredraw</name><data>0000000000000000</data></node>
      </data></node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/editmodes</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040260000</data></node>
    <node f="42" dt="2"><name>after</name><data>RCreate</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar</name>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>AStar::Create</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>/installdata/add~3/1/data/AStar/LibraryGroup/One-Way Divider</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\solidbarriertool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="1"><name>lastMouseX</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastMouseY</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>dragX</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>dragY</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>dragging</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastModelX</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastModelY</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>creating</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>mode</name><data>0000000000000000</data></node>
        <node f="42" dt="3"><name>activeNavigator</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>currBarrierNode</name><data><coupling>null</coupling></data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
#define BARRIER_MODE_MOVE 0x4

if (!objectexists(i))
	return 0;

if (gets(documentwindow(i)) != "3D")
	return 0;

int mode = getvarnum(c, "mode");
treenode selobj = selectedobject(i/*The view*/);
treenode currBarrierNode = tonode(getvarnum(c, "currBarrierNode"));

treenode activeNavigator = tonode(getvarnum(c, "activeNavigator"));
if (!objectexists(activeNavigator))
	activeNavigator = function_s(c, "findNavigator");
if (!objectexists(activeNavigator))
	activeNavigator = createinstance(node("/?AStarNavigator", library()), model());

applicationcommand("assertmoduledependency", "AStar");
nodepoint(getvarnode(c, "activeNavigator"), activeNavigator);

double mouseX = cursorinfo(i, 2, 1, 1);
double mouseY = cursorinfo(i, 2, 2, 1);
setvarnum(c, "lastMouseX", cursorinfo(i, 1, 1, 1));
setvarnum(c, "lastMouseY", cursorinfo(i, 1, 2, 1));
setvarnum(c, "lastModelX", mouseX);
setvarnum(c, "lastModelY", mouseY);
int clickCode = clickcode();

//pt("SelectedObject: "); pt(nodetomodelpath(selobj, 1)); 
//pt(" clickcode: "); pd(clickCode); pr();

if (!objectexists(selobj)) {
	if (clickCode == LEFT_RELEASE) {
		int dx = getvarnum(c, "dragX");
		int dy = getvarnum(c, "dragY");
		
		// Allow the user to pan the view
		if (fabs(dx) &lt; 2 &amp;&amp; fabs(dy) &lt; 2) {
			if (!getvarnum(c, "creating")) {
				setvarnum(c, "creating", 1);
				setvarnum(c, "editing", 0);
				
				treenode activeBarrier = function_s(activeNavigator, "addBarrier", mouseX, mouseY, mouseX, mouseY, mode);
				function_s(activeNavigator, "setBarrierMode", activeBarrier, BARRIER_MODE_DYNAMIC_CREATE);
				setselectedobject(i, activeNavigator);
				nodepoint(getvarnode(c, "currBarrierNode"), activeBarrier); 
				return 0;
			}
		}
	}
} else {
	if (clickCode == LEFT_PRESS) {
		postwindowmessage(windowfromnode(activedocumentnode()),
			FLEXSIM_MESSAGE_USER_NODEFUNCTION,
			node("checkStatus", eventfunctions(c)), 0);	
	}	
}


if (clickCode == LEFT_PRESS) {
	setvarnum(c, "dragX", 0);
	setvarnum(c, "dragY", 0);
	setvarnum(c, "dragging", 1);
}

if (clickCode == LEFT_RELEASE) {
	setvarnum(c, "dragging", 0);
	if (mode == EDITMODE_SOLID_BARRIER &amp;&amp; getvarnum(c, "creating")) {
		setvarnum(c, "creating", 0);
		setvarnum(c, "editing", 1);
		function_s(activeNavigator, "setBarrierMode", currBarrierNode, 0); //So the barrier isn't deleted on right click
	}
}</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>if (!objectexists(i))
		return 0;
		
if (getvarnum(c, "creating")) {
	double mouseX = cursorinfo(i, 2, 1, 1);
	double mouseY = cursorinfo(i, 2, 2, 1);
	double dx = mouseX - getvarnum(c, "lastModelX");
	double dy = mouseY - getvarnum(c, "lastModelY");
	
	setvarnum(c, "lastModelX", mouseX);
	setvarnum(c, "lastModelY", mouseY);
	
	function_s(tonode(getvarnum(c, "activeNavigator")), "onMouseMove", 
		mouseX, mouseY, dx, dy);
	
	#define WM_PAINT 0x000F
	postwindowmessage(windowfromnode(i), WM_PAINT,0,0);

}

if (getvarnum(c, "dragging")) { 
	double mouseX = cursorinfo(i, 1, 1, 1);
	double mouseY = cursorinfo(i, 1, 2, 1);
	double dx = mouseX - getvarnum(c, "lastMouseX");
	double dy = mouseY - getvarnum(c, "lastMouseY");
	
	setvarnum(c, "dragX", dx);
	setvarnum(c, "dragY", dy);
}</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode iconGrid = nodefromwindow(keyboardfocus());
treenode activeNavigator = tonode(getvarnum(c, "activeNavigator"));
if (!objectexists(activeNavigator))
	activeNavigator = function_s(c, "findNavigator");
if (!objectexists(activeNavigator))
	return 0;
function_s(activeNavigator, "setEditMode", getvarnum(c, "mode"));
nodepoint(viewfocus(c), iconGrid);
nodepoint(objectfocus(c), selectedobject(iconGrid));</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>// reset all my variables so I don't get revision control diffs

setvarnum(c, "editing", 0);
setvarnum(c, "creating", 0);
setvarnum(c, "mode", 0);
setvarnum(c, "lastMouseX", 0);
setvarnum(c, "lastMouseY", 0);
setvarnum(c, "dragging", 0);
setvarnum(c, "lastModelX", 0);
setvarnum(c, "lastModelY", 0);
setvarnum(c, "dragX", 0);
setvarnum(c, "dragY", 0);

treenode activeNav = tonode(getvarnum(c, "activeNavigator"));
if (!objectexists(activeNav))
	return 0;
function_s(activeNav, "onClick", activedocumentnode(), RIGHT_RELEASE, 0, 0);
function_s(activeNav, "rebuildMeshes");</data></node>
        <node f="442" dt="2"><name>checkStatus</name><data>#define BARRIER_MODE_CREATE 0x2

treenode activeNavigator = tonode(getvarnum(ownerobject(c), "activeNavigator"));
if (!objectexists(activeNavigator))
	return 0;

treenode theEditMode = ownerobject(c);
int barrierEditMode = function_s(activeNavigator, "getActiveBarrierMode");

if (barrierEditMode &amp; BARRIER_MODE_CREATE)
	return 0;
	
setvarnum(theEditMode, "creating", 0);
setvarnum(theEditMode, "editing", 1);
</data></node>
        <node f="442" dt="2"><name>findNavigator</name><data>forobjecttreeunder(model) {
	if (isclasstype(a, "AStar::AStarNavigator")) {
		nodepoint(getvarnode(c, "activeNavigator"), a);
		return a;
	}
}
</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::Barrier</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\solidbarriertool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_SOLID_BARRIER</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::Divider</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\dividertool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_DIVIDER</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::OneWayDivider</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\onewaydividertool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_ONE_WAY_DIVIDER</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::PreferredPath</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\preferredpathtool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_PREFERRED_PATH</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::Bridge</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\bridgetool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_BRIDGE</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/modules</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>000000003ff00000</data></node>
    <node f="42"><name>after</name></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar</name>
      <node f="40"><name></name></node>
      <node f="42"><name>LibraryGroup</name>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>AStarNavigator</name><data>
        <node f="40"><name></name></node>
        <node f="42"><name>visual</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\astarnavigatorsmall.png</data></node>
        </node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObject = param(1);
double x = param(2);
double y = param(3);
double z = param(4);
treenode view = param(5);

if (objectexists(node("AStarNavigator", model)))
	return 0;

treenode asn = createinstance(node("astar/1", library()), model());
setname(asn, "AStarNavigator");
set(spatialx(asn), x);
set(spatialy(asn), y);
set(spatialz(asn), z);
return asn;
</data></node>
        <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
       </data></node>
       <node f="42" dt="4"><name>Barrier</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>modeleditmode("AStar::Barrier")</data></node>
        <node f="42" dt="1"><name>viewwindowsource</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\solidbarrier.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Divider</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>modeleditmode("AStar::Divider")</data></node>
        <node f="42" dt="1"><name>viewwindowsource</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\divider.bmp</data></node>
       </data></node>
       <node f="10000042" dt="4"><name>One-Way Divider</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>modeleditmode("AStar::OneWayDivider")</data></node>
        <node f="42" dt="1"><name>viewwindowsource</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\onewaydivider.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Preferred Path</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>modeleditmode("AStar::PreferredPath")</data></node>
        <node f="42" dt="1"><name>viewwindowsource</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\preferredpath.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Bridge</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>modeleditmode("AStar::Bridge")</data></node>
        <node f="42" dt="1"><name>viewwindowsource</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\bridge.bmp</data></node>
       </data></node>
      </node>
      <node f="42"><name>Pages</name>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>AStarParameters</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>00000000406e0000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>00000000405d8000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000407db000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>000000004082a000</data></node>
        <node f="42" dt="2"><name>windowtitle</name><data></data></node>
        <node f="442" dt="2"><name>OnOpen</name><data>treenode tabcontrol = node("/tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnOpen",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnOpen",rank(tabcontrol,count)));
}

executefsnode(node("VIEW:/nodefunctions/setparameterstitle"),c,0,0);
repaintview(c);</data></node>
        <node f="42" dt="2"><name>OnPreOpen</name><data>standardpreopen(c);
</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="2"><name>OnClose</name><data></data>
         <node f="40" dt="7"><name></name><data/>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
           <node f="40"><name></name></node></node>
         </node></node>
        <node f="442" dt="2"><name>OnApply</name><data>treenode tabcontrol = node("../tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnApply",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnApply",rank(tabcontrol,count)));
}
</data></node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>overlay</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="2"><name>viewfocus</name><data>../..</data></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040080000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040dfffc0</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040903000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040886000</data></node>
         <node f="42" dt="1"><name>viewpointx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewpointy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewpointz</name><data>7f8ca81a407c965f</data></node>
         <node f="42" dt="1"><name>hidden</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>viewhidealllabels</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>transparent</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>viewhideallbases</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>gridx</name><data>00000000401c0000</data></node>
         <node f="42" dt="1"><name>gridy</name><data>00000000401c0000</data></node>
         <node f="42" dt="1"><name>viewsnaptogrid</name><data>000000003ff00000</data></node>
        </data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="4"><name>static1</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000040240000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040500000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040500000</data></node>
         <node f="42" dt="2"><name>bitmap</name><data>modules\AStar\bitmaps\astarnavigator.png</data></node>
        </data></node>
        <node f="42" dt="4"><name>editname</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000004056c000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000403c0000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab40745aaa</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/EditObjectName</data></node>
        </data></node>
        <node f="42" dt="4"><name>tabcontrol</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405cc000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040518000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab4079aaaa</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>aaaaaaab407c0aaa</data></node>
         <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040100000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040440000</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Source pages</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>AStar</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="442" dt="2"><name>PageOnOpen</name><data>
int gray = !get(node("@&gt;objectfocus+&gt;variables/cachePaths", c));

forobjectsbehind (node("/Paths/Cache Paths", up(c)))
	windowgray(windowfromnode(a), gray);

gray = !get(node("@&gt;objectfocus+&gt;variables/enableCollisionAvoidance", c));

windowgray(windowfromnode(node("/Ignore Inactive Members", up(c))), gray);

listboxrefresh(node("/Members/MemberChooser", up(c)));

nodefunction(node("/Members/MembersList&gt;refresh", up(c)));</data></node>
          <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Node Spacing</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000402a0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditNodeSpacing</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405e0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/nodeWidth</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Enter the spacing between nodes.</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>valuetype</name><data>distance</data></node>
            <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>ishotlink</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>step</name><data>9999999a3fb99999</data></node>
            <node f="42" dt="1"><name>conversion</name><data>0000000000000000</data></node>
            <node f="442" dt="2"><name>OnKillFocus</name><data>treenode parent = ownerobject(c);
if (stringtonum(getviewtext(node("/EditValue", parent))) &lt;= 0.1) {
	setviewtext(node("/EditValue", parent), "0.1");
	set(node("&gt;objectfocus+", parent), 0.1);
}

function_s(node("@&gt;objectfocus+", c), "rebuildMeshes");
repaintall();</data></node>
           </node>
          </data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="4"><name>Surround Depth</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040458000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditSurround</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405e0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040440000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/surroundDepth</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Specify how many nodes will appear around the outside of the AStar area.</data></node>
           <node f="42" dt="1"><name>rangemin</name><data>000000003ff00000</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>ishotlink</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>step</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>conversion</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>exponent</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>precision</name><data>0000000000000000</data></node>
           </node>
          </data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="4"><name>Default Path Weight</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040524000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditPathWeight</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405e0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040518000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/defaultPathWeight</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Default path weight for newly created Preferred Paths.</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>valuetype</name><data></data></node>
            <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>ishotlink</name><data>000000003ff00000</data></node>
            <node f="42" dt="1"><name>conversion</name><data>0000000000000000</data></node>
           </node>
          </data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="4"><name>Deep Search Routing</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040704000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>000000004062c000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/deepSearch</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Toggle deep search</data></node>
          </data></node>
          <node f="42" dt="4"><name>Collision Avoidance</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040704000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000403f0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/enableCollisionAvoidance</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>int gray = !getchecked(c);

windowgray(windowfromnode(node("../Ignore Inactive Members", c)), gray);</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>If checked, travelers will allocate nodes in the travel grid as 
part of their travel, preventing travelers from running 
over each other.</data></node>
          </data></node>
          <node f="42" dt="4"><name>Ignore Inactive Members</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040718000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000404a0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040618000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/ignoreInactiveMemberCollisions</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>If checked, travelers will travel through nodes allocated to 
other inactive travelers.</data></node>
          </data></node>
          <node f="42" dt="4"><name>Smooth Rotations</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040704000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040524000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/smoothRotations</data></node>
          </data></node>
          <node f="42" dt="4"><name>Paths</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ac000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000405b8000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000406b8000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040646000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Cache Paths</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040310000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/cachePaths</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>int gray = !getchecked(c);

forobjectsbehind (c)
	windowgray(windowfromnode(a), gray);</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Toggle cache paths</data></node>
           </data></node>
           <node f="42" dt="4"><name>Paths Cached</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040440000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>pathCount</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040428000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040530000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>The total number of paths that have been cached.</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>hotlink</name><data>@&gt;objectfocus+&gt;variables/pathCount</data></node>
            <node f="42"><name>style</name>
             <node f="40"><name></name></node>
             <node f="42"><name>ES_READONLY</name></node>
             <node f="42" dt="1"><name>FS_PRECISION</name><data>0000000000000000</data></node>
            </node>
           </data></node>
           <node f="42" dt="4"><name>Path Requests</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040504000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>requestCount</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404f0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040530000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>The total number of travel requests made.</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>hotlink</name><data>@&gt;objectfocus+&gt;variables/requestCount</data></node>
            <node f="42"><name>style</name>
             <node f="40"><name></name></node>
             <node f="42"><name>ES_READONLY</name></node>
             <node f="42" dt="1"><name>FS_PRECISION</name><data>0000000000000000</data></node>
            </node>
           </data></node>
           <node f="42" dt="4"><name>Cached Paths Used</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>useCount</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>000000004055c000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040530000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Total number of travel requests that have utilized a cached path.</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>hotlink</name><data>@&gt;objectfocus+&gt;variables/cacheUseCount</data></node>
            <node f="42"><name>style</name>
             <node f="40"><name></name></node>
             <node f="42"><name>ES_READONLY</name></node>
             <node f="42" dt="1"><name>FS_PRECISION</name><data>0000000000000000</data></node>
            </node>
           </data></node>
           <node f="42" dt="4"><name>Utilization</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000405cc000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>utilization</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000405c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040530000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Percentage of travel requests that utilized a cached path.</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>hotlinkx</name><data>if (!eventdata) {
	treenode objfocus = node("@&gt;objectfocus+", c);

	double useCount = getvarnum(objfocus, "cacheUseCount");
	double requestCount = getvarnum(objfocus, "requestCount");
	if (requestCount == 0) {
		setviewtext(c, "0 %");
	} else {
		double utilization = useCount / requestCount * 100;
		setviewtext(c, concat(numtostring(utilization), " %"));
	}
}</data>
             <node f="40" dt="7"><name></name><data/>
              <node f="40"><name></name></node>
              <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
               <node f="40"><name></name></node></node>
             </node></node>
            <node f="42"><name>style</name>
             <node f="40"><name></name></node>
             <node f="42"><name>ES_READONLY</name></node>
            </node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>Members</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ac000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040713000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab40787aaa</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>aaaaaaab40620aaa</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>MemberChooser</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405c8000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000404e0000</data></node>
            <node f="42"><name>items</name>
             <node f="40"><name></name></node>
             <node f="42"><name>All Members</name></node>
             <node f="42"><name>Traveler Members</name></node>
             <node f="42"><name>FR Members</name></node>
            </node>
            <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
            <node f="42" dt="2"><name>OnSelect</name><data>nodefunction(node("../MembersList&gt;refresh",c));</data>
             <node f="40"><name></name></node></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Properties</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>000000004053c000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode list = node("../MembersList", c);
string path = getname(rank(items(list), get(itemcurrent(list))));

treenode member = node(path, model());

if (objectexists(member)) {
  
  createview(
	gets(node("&gt;special/guifocusclass",member)),
	nodetopath(member, 1),
	nodetopath(member, 1)
	);
}</data>
             <node f="40"><name></name></node></node>
            <node f="42" dt="2"><name>tooltip</name><data>Open Properties Window of highlighted member</data></node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Sampler</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/SamplerButton</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000405d4000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Click this button then "sample" an object in FlexSim</data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>valType</name><data>0000000040700000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>onSample</name><data>treenode focus = node("@&gt;objectfocus+", c);

function_s(focus, "addMember", param(3));

nodefunction(node("../MembersList&gt;refresh",c));
repaintall();</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Add</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000405d4000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040430000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>createpopup("VIEW:/standardviews/other/UniversalSelect", "", nodetopath(node("&gt;SelectDelegate",c), 1), c, 0, 0, 0,0);</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Add a new member</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\add.png</data></node>
            <node f="42" dt="4"><name>SelectDelegate</name><data>
             <node f="40"><name></name></node>
             <node f="42"><name>variables</name>
              <node f="40"><name></name></node>
              <node f="42"><name>selected</name>
               <node f="40"><name></name></node>
               <node f="42" dt="3"><name></name><data><coupling>null</coupling></data></node>
               <node f="42" dt="3"><name></name><data><coupling>null</coupling></data></node>
              </node>
              <node f="42" dt="1"><name>singleobjectselect</name><data>0000000000000000</data></node>
             </node>
             <node f="42"><name>eventfunctions</name>
              <node f="40"><name></name></node>
              <node f="442" dt="2"><name>OnApply</name><data>treenode selected = getvarnode(c, "selected");
if (content(selected) == 0)
	return 0;
	
treenode focus = node("@&gt;objectfocus+", c);

for (int i = 1; i &lt;= content(selected); i++) {
	treenode obj = tonode(get(rank(selected, i)));
	
	function_s(focus, "addMember", obj);
}

nodefunction(node("../../MembersList&gt;refresh",c));
repaintall();</data></node>
             </node>
            </data></node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Remove</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000405d4000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404d8000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode membersList = node("../MembersList", c);
int index = get(itemcurrent(membersList));
if (index == 0)
	return 0;
	
string name = getname(rank(items(membersList), index));


int list = get(itemcurrent(node("../MemberChooser", c)));
treenode object = NULL;

switch (list) {
	case 1: //ALL
		object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/activetravelmembers", c));
		if (!object) object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/travelmembers", c));
		if (!object) object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/fixedResourceBarriers", c));
	break;
	
	case 2: //ACTIVE
		object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/activetravelmembers", c));
	break;
	
	case 3: //INACTIVE
		object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/travelmembers", c));
	break;
	
	case 4: //FR
		object = nodefunction(node("&gt;searchObjects", c), name, node("@&gt;objectfocus+&gt;variables/fixedResourceBarriers", c));
	break;
}

if (objectexists(object)) {
	treenode navigator = node("@&gt;objectfocus+", c);
	function_s(navigator, "removeMember", object);
	nodefunction(node("../MembersList&gt;refresh",c));
	repaintall();
}
</data></node>
            <node f="442" dt="2"><name>searchObjects</name><data>string name = param(1);
treenode members = param(2);

for (int i = 1; i &lt;= content(members); i++) {
	treenode object = ownerobject(tonode(get(rank(members, i))));
	string objName = getname(object);
	if (comparetext(name, objName)) {
		return object;
	}
}
return NULL;</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Remove the selected member</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\remove.png</data></node>
           </data></node>
           <node f="42" dt="4"><name>MembersList</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405c8000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040618000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab406daaaa</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>55555555405b9555</data></node>
            <node f="442" dt="2"><name>hotlinkx</name><data>if (!eventdata) {
	int list = get(itemcurrent(node("../MemberChooser", c)));
	if (list == 2 || list == 3) { //Active/Inactive lists
		nodefunction(node("&gt;refresh", c));
	}
}</data></node>
            <node f="442" dt="2"><name>refresh</name><data>treenode parent = up(c);
int list = get(itemcurrent(node("../MemberChooser", parent)));

treenode itms = items(parent);
clearcontents(itms);

switch (list) {
	case 1: //ALL
		nodefunction(node("&gt;displaymembers", parent), node("@&gt;objectfocus+&gt;variables/travelmembers", parent));
		nodefunction(node("&gt;displaymembers", parent), node("@&gt;objectfocus+&gt;variables/fixedResourceBarriers", parent));
	break;
	
	case 2: //Travelers
		nodefunction(node("&gt;displaymembers", parent), node("@&gt;objectfocus+&gt;variables/travelmembers", parent));
	break;
		
	case 3: //FR
		nodefunction(node("&gt;displaymembers", parent), node("@&gt;objectfocus+&gt;variables/fixedResourceBarriers", parent));
	break;
}

listboxrefresh(parent);</data></node>
            <node f="442" dt="2"><name>displaymembers</name><data>treenode members = param(1);

treenode itms = items(up(c));

for (int i = 1; i &lt;= content(members); i++) {
	nodeinsertinto(itms);
	setname(last(itms), nodetomodelpath(ownerobject(tonode(get(rank(members, i)))), 2));
}</data></node>
            <node f="42"><name>items</name>
             <node f="40"><name></name></node></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040310000</data></node>
           </data></node>
          </node>
         </node>
         <node f="42" dt="4"><name>Visual</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="442" dt="2"><name>PageOnOpen</name><data>#define ASTAR_DRAW_MODE_BOUNDS 0x1
#define ASTAR_DRAW_MODE_BARRIERS 0x2
#define ASTAR_DRAW_MODE_TRAFFIC 0x4
#define ASTAR_DRAW_MODE_GRID 0x8
#define ASTAR_DRAW_MODE_MEMBERS 0x10

int drawmode = get(node("@&gt;objectfocus+&gt;variables/drawMode", c));

setchecked(node("/Show Barriers", up(c)), drawmode &amp; ASTAR_DRAW_MODE_BARRIERS);
setchecked(node("/Show Bounds", up(c)), drawmode &amp; ASTAR_DRAW_MODE_BOUNDS);
setchecked(node("/Show Grid", up(c)), drawmode &amp; ASTAR_DRAW_MODE_GRID);
setchecked(node("/Show Members", up(c)), drawmode &amp; ASTAR_DRAW_MODE_MEMBERS);
setchecked(node("/Show Traffic", up(c)), drawmode &amp; ASTAR_DRAW_MODE_TRAFFIC);
</data></node>
          <node f="442" dt="2"><name>PageOnApply</name><data>#define ASTAR_DRAW_MODE_BOUNDS 0x1
#define ASTAR_DRAW_MODE_BARRIERS 0x2
#define ASTAR_DRAW_MODE_TRAFFIC 0x4
#define ASTAR_DRAW_MODE_GRID 0x8
#define ASTAR_DRAW_MODE_MEMBERS 0x10

double drawmode = 0;

drawmode += getchecked(node("/Show Barriers", up(c))) ? ASTAR_DRAW_MODE_BARRIERS : 0;
drawmode += getchecked(node("/Show Bounds", up(c))) ? ASTAR_DRAW_MODE_BOUNDS : 0;
drawmode += getchecked(node("/Show Grid", up(c))) ? ASTAR_DRAW_MODE_GRID : 0;
drawmode += getchecked(node("/Show Members", up(c))) ? ASTAR_DRAW_MODE_MEMBERS : 0;
drawmode += getchecked(node("/Show Traffic", up(c))) ? ASTAR_DRAW_MODE_TRAFFIC : 0;

set(node("@&gt;objectfocus+&gt;variables/drawMode", c), drawmode);</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>enableHeatMapControls</name><data>int gray = !getchecked(c.find("Show Heat Map"));
windowgray(windowfromnode(c.find("SelectHeatMapMode")), gray);
windowgray(windowfromnode(c.find("Max Heat Value")), gray);
windowgray(windowfromnode(c.find("EditMaxHeatValue")), gray);
windowgray(windowfromnode(c.find("TransparentBaseColor")), gray);
</data></node>
          </node>
          <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Show Barriers</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show A* Barriers</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Bounds</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040430000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show A* grid boundaries</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Grid</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040508000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show A* grid</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Members</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040578000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to draw a circle beneath A* Traveler members and a square beneath A* FR members</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Allocations</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000405e8000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>When using collision avoidance, check to show grid node allocations for each traveller</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/showAllocations</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Heat Map</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>000000004062c000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show a heat map of the AStar grid</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>function_s(up(c), "enableHeatMapControls");</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/showHeatMap</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to draw a heatmap over the A* grid</data></node>
          </data></node>
          <node f="42" dt="4"><name>SelectHeatMapMode</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040664000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000406e0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/heatMapMode</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Enter the calculation that determines the colors of the heat map</data></node>
           <node f="42"><name>items</name>
            <node f="40"><name></name></node>
            <node f="42"><name>Traversals Per Time</name></node>
            <node f="42"><name>Average Blockage Time Per Traversal</name></node>
            <node f="42"><name>Percent of Total Time Blocked</name></node>
           </node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000040080000</data></node>
          </data></node>
          <node f="42" dt="4"><name>Max Heat Value</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406a6000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) 
	function_s(up(c), "enableHeatMapControls");</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditMaxHeatValue</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>000000004060e000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406a0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040618000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/maxHeatValue</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Enter the value that corresponds to "maximum heat", or 
bright red, in the heat map.</data></node>
          </data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="4"><name>TransparentBaseColor</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406d6000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040690000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to make the base color of the heat map transparent</data></node>
           <node f="42" dt="2"><name>OnPress</name><data></data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/transparentBaseColor</data></node>
           <node f="42" dt="2"><name>windowtitle</name><data>Transparent Base Color</data></node>
          </data></node>
         </node>
         <node f="42" dt="4"><name>Barriers</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="442" dt="2"><name>PageOnOpen</name><data>treenode parent = up(c);

setchecked(node("/editor view", parent), 1);
setchecked(node("/table view", parent), 0);

treenode editor = node("/Editor/SelectBarrier", parent);
function_s(editor, "refreshList");

//now, hide the table view and show the editor view
windowshow(windowfromnode(node("/Edit Table", parent)), 0);
windowshow(windowfromnode(editor), 1);
</data></node>
          <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>editor view</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a8000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040534000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="2"><name>OnPress</name><data>//refresh the list before showing it. It may have changed in the table view.
treenode editor = node("../Editor", c);
executefsnode(node("&gt;refreshlist", editor), editor, 0, 0);
executefsnode(node("&gt;refreshdata", editor), editor, 0, 0);


//now, hide the table view and show the editor view
windowshow(windowfromnode(node("../Edit Table", c)), 0);
windowshow(windowfromnode(editor), 1);</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
           <node f="42" dt="2"><name>windowtitle</name><data>Editor View</data></node>
           <node f="42" dt="1"><name>hidden</name><data>000000003ff00000</data></node>
          </data></node>
          <node f="42" dt="4"><name>table view</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a8000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="2"><name>OnPress</name><data>applylinks(node("../Edit Table/Table", c), 1);

//hide the editor view and show the table view
windowshow(windowfromnode(node("../Editor", c)), 0);
windowshow(windowfromnode(node("../Edit Table", c)), 1);</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>windowtitle</name><data>Table View</data></node>
           <node f="42" dt="1"><name>hidden</name><data>000000003ff00000</data></node>
          </data></node>
          <node f="42" dt="4"><name>Edit Table</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ac000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab40787aaa</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>5555555540780555</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Add Barrier</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040340000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode TheTable = node("../TheTable",c);
treenode selected = selectedobject(TheTable);

if (content(selected) == 0)// and individual cell is selected (I want the row)
	selected = up(selected);

treenode barrier;

if (objectexists(selected)) {
	barrier = createcopy(selected, up(selected), 1);
	setname(barrier, concat(getname(selected), " copy"));
	setrank(barrier, getrank(selected)+1);
} else {
	treenode focus = node("&gt;viewfocus+",TheTable);
	nodeinsertinto(focus);
	barrier = last(focus);
	for (int i = 1; i &lt;= 5; i++) {
		nodeinsertinto(barrier);
		nodeadddata(last(barrier), DATATYPE_NUMBER);
	}
	set(first(barrier), BARRIER_TYPE_SOLID);
	setname(barrier, concat("Barrier ", numtostring(content(focus))));
}

repaintview(TheTable);</data></node>
           </data></node>
           <node f="42" dt="4"><name>Remove Barrier</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000405a4000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040340000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode TheTable = node("../TheTable",c);

treenode selected = selectedobject(TheTable);
if (!objectexists(selected)) {
	selected = last(node("&gt;viewfocus+",TheTable));
}
if (content(selected) == 0)// and individual cell is selected (I want the row)
	selected = up(selected);

destroyobject(selected);

repaintview(TheTable);</data></node>
           </data></node>
           <node f="42" dt="4"><name>Add Table to MTEI</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
            <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>5555555540705555</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000405e0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040340000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode excelauto = node("/Tools/ExcelAuto",model());
if (!objectexists(excelauto)) {
	createinstance(node("/?ExcelAuto", library()), node("/Tools",model()));
	excelauto = last(node("/Tools",model()));
	setname(excelauto, "ExcelAuto");
}
treenode table = getvarnode(excelauto, "importtable");
createcopy(getvarnode(excelauto, "rowtemplate"),table);
setname(last(table),concat("Row_",numtostring(content(table),0,0)));

// Set the destination cell in the MTI table
//TODO: Modify the excel interface to handle AStar Barriers, right now it's just passing in an Other table type
sets(node("/Flexsim_Object_Type", last(table)), "");
sets(node("/Flexsim_Object_Name", last(table)), "");
sets(node("/Flexsim_Table_Location", last(table)), nodetomodelpath(node("&gt;variables/barriers", node("@&gt;objectfocus+",c)), 1));
sets(node("/Flexsim_Table_Name", last(table)), "");


repaintall();
msg("NOTICE", concat(
	"Please remember to update the other information required",strascii(13),
	"in the Multiple Table Excel Import. Open the Excel Interface", strascii(13),
	"by pressing the Excel button on the toolbar."
), 1);
</data>
             <node f="40"><name></name></node></node>
            <node f="42" dt="2"><name>tooltip</name><data>Add this table to the Multiple Table Excel Import</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040604000</data></node>
           </data></node>
           <node f="42" dt="4"><name>TheTable</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="2"><name>focus</name><data>@&gt;objectfocus+&gt;variables/barriers</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>..&gt;table</data></node>
            <node f="42"><name>table</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040478000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>555555554076f555</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>5555555540747555</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="2"><name>coldlinkx</name><data>/*treenode focus = node("&gt;focus+", c);
treenode table = node("&gt;table", c);

if (!eventdata) {
	for (int i = 1; i &lt;= content(focus); i++) {
		treenode barrier = rank(focus, i);
		if (get(first(barrier)) == BARRIER_TYPE_SOLID) {
			createcopy(barrier, table, 1);
			destroyobject(first(last(table)));
		}
	}
	if (content(focus) &gt;= 1) {
		setname(rank(first(table), 1), "X1");
		setname(rank(first(table), 2), "Y1");
		setname(rank(first(table), 3), "X2");
		setname(rank(first(table), 4), "Y2");
	}
} else {
	return 0;
}*/</data>
             <node f="40" dt="7"><name></name><data/>
              <node f="40"><name></name></node>
              <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
               <node f="40"><name></name></node></node>
             </node></node>
            <node f="42" dt="2"><name>OnMouseWheel</name><data>treenode TheTable = ownerobject(c);

double vert_nMin = scrollinfo(TheTable,0,1,1);
double vert_nMax = scrollinfo(TheTable,0,1,2);
double vert_nPage = scrollinfo(TheTable,0,1,3);
double vert_nPos = scrollinfo(TheTable,0,1,4);

// OnMouseWheelDelta is set to an amount when you scroll the wheel
// this amount is about 1/4 of a page size to scroll each time the mousewheel clicks once
double amount = get(node("&gt;OnMouseWheelDelta",TheTable))/480*vert_nPage;

// set the position based on the wheeled amount
scrollinfo(TheTable,1,1,4,vert_nPos-amount);
repaintview(TheTable);


</data></node>
            <node f="42" dt="1"><name>OnMouseWheelDelta</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>cellwidth</name><data>5e02ea9640526666</data></node>
            <node f="42" dt="1"><name>cellheight</name><data>0000000040320000</data></node>
            <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040240000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040240000</data></node>
            <node f="42" dt="1"><name>dataentry</name><data>0000000000000000</data></node>
            <node f="42"><name>noformat</name></node>
            <node f="42"><name>undohistory</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>undo limit</name><data>0000000040900000</data></node>
             <node f="42" dt="3"><name>history</name><data><coupling>null</coupling></data></node>
             <node f="42" dt="1"><name>bin</name><data>0000000000000000</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
          </node>
          <node f="42" dt="4"><name>Editor</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ac000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>aaaaaaab40787aaa</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>555555554079c555</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>00000000401c0000</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>FilterType</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
            <node f="42"><name>spatial</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040320000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>5555555540535555</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            </node>
            <node f="42"><name>items</name>
             <node f="40"><name></name></node>
             <node f="42"><name>Show All</name></node>
             <node f="42"><name>Barriers</name></node>
             <node f="42"><name>Dividers</name></node>
             <node f="42"><name>One-Way Dividers</name></node>
             <node f="42"><name>Preferred Paths</name></node>
             <node f="42"><name>Bridges</name></node>
            </node>
            <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
            <node f="42" dt="2"><name>OnSelect</name><data>function_s(node("../SelectBarrier", c), "refreshList");</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Filter by barrier type</data></node>
            <node f="42" dt="1"><name>beveltype</name><data>000000003ff00000</data></node>
            <node f="42" dt="2"><name>windowtitle</name><data></data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>000000004072c000</data></node>
           </data></node>
           <node f="42" dt="4"><name>Add</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42"><name>menuitems</name>
             <node f="40"><name></name></node>
             <node f="42" dt="2"><name>Add Barrier</name><data>function_s(ownerobject(c), "add", EDITMODE_SOLID_BARRIER);</data></node>
             <node f="42" dt="2"><name>Add Divider</name><data>function_s(ownerobject(c), "add", EDITMODE_DIVIDER);</data></node>
             <node f="42" dt="2"><name>Add One-Way Divider</name><data>function_s(ownerobject(c), "add", EDITMODE_ONE_WAY_DIVIDER);</data></node>
             <node f="42" dt="2"><name>Add Preferred Path</name><data>function_s(ownerobject(c), "add", EDITMODE_PREFERRED_PATH);</data></node>
             <node f="42" dt="2"><name>Add Bridge</name><data>function_s(ownerobject(c), "add", EDITMODE_BRIDGE);</data></node>
            </node>
            <node f="42" dt="1"><name>menupopup</name><data>000000003ff00000</data>
             <node f="40"><name></name></node></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>add</name><data>int type = param(1);
treenode focus = node("@&gt;objectfocus+", c);

function_s(focus, "addBarrier", 0, 0, 10, 10, type);
function_s(focus, "rebuildMeshes");
treenode selectBarrier = node("../SelectBarrier", c);
function_s(selectBarrier, "refreshList");
set(itemcurrent(selectBarrier), content(items(selectBarrier)));
listboxrefresh(selectBarrier);
executefsnode(OnSelect(selectBarrier), selectBarrier);
repaintall();</data></node>
             <node f="42" dt="2"><name>OnPress</name><data>int filter = get(itemcurrent(node("../FilterType", c)));

clearcontents(menupopup(c));
switch (filter) {
	case 1:  //Have them select the barrier type manually
		treenode menuitems = node("&gt;menuitems", c);
		for (int i = 1; i &lt;= content(menuitems); i++)
			createcopy(rank(menuitems, i), menupopup(c), 1);
	break;
	
	case 2:  //Barriers
		function_s(c, "add", EDITMODE_SOLID_BARRIER);
	break;
	
	case 3:  //Divider
		function_s(c, "add", EDITMODE_DIVIDER);
	break;
	
	case 4:  //One-Way Divider
		function_s(c, "add", EDITMODE_ONE_WAY_DIVIDER);
	break;
	
	case 5:  //Preferred Path	
		function_s(c, "add", EDITMODE_PREFERRED_PATH);
	break;
	
	case 6:  //Bridge
		function_s(c, "add", EDITMODE_BRIDGE);
	break;
}
</data></node>
            </node>
            <node f="42" dt="2"><name>tooltip</name><data>Add a new barrier</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\add.png</data></node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Remove</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040458000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>int index = get(itemcurrent(node("../SelectBarrier", c)));

if (index == 0)
	return 0;
	
treenode barriers = node("@&gt;objectfocus+&gt;variables/barriers", c);
string name = getname(rank(items(node("../SelectBarrier", c)), index));
treenode focus = node("@&gt;objectfocus+", c);

//Find the barrier's index in the object's barriers node
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		index = i;
		break;
	}
}
index--; //Base 0
function_s(focus, "removeBarrier", index);
treenode selectBarrier = node("../SelectBarrier", c);
function_s(selectBarrier, "refreshList");
set(itemcurrent(selectBarrier), index);
listboxrefresh(selectBarrier);
executefsnode(OnSelect(selectBarrier), selectBarrier);</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Remove the selected section</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\remove.png</data></node>
           </data></node>
           <node f="42" dt="4"><name>Up</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040520000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\uparrow_blue.png</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode selectBarrier = node("../SelectBarrier", c);
int index = get(itemcurrent(selectBarrier));

if (index &lt;= 1)
	return 0;

int index1;
treenode barriers = node("@&gt;objectfocus+&gt;variables/barriers", c);
string name = getname(rank(items(selectBarrier), index));
treenode focus = node("@&gt;objectfocus+", c);

//Find the barrier's index in the object's barriers node
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		index1 = i;
		break;
	}
}
index1--; //Base 0

//Find the object above the selected object
int index2;
name = getname(rank(items(selectBarrier), index -1));
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		index2 = i;
		break;
	}
}
index2--; //Base 0

function_s(focus, "swapBarriers", index1, index2);
function_s(focus, "rebuildMeshes");
set(itemcurrent(selectBarrier), index -1);
function_s(selectBarrier, "refreshList");
repaintall();</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Move the selected barrier up in the list</data></node>
           </data></node>
           <node f="42" dt="4"><name>Down</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040594000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\downarrow_blue.png</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>treenode selectBarrier = node("../SelectBarrier", c);
int index = get(itemcurrent(selectBarrier));

if (index == 0 || index == content(items(selectBarrier)))
	return 0;

int index1;
treenode barriers = node("@&gt;objectfocus+&gt;variables/barriers", c);
string name = getname(rank(items(selectBarrier), index));
treenode focus = node("@&gt;objectfocus+", c);

//Find the barrier's index in the object's barriers node
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		index1 = i;
		break;
	}
}
index1--; //Base 0

//Find the object above the selected object
int index2;
name = getname(rank(items(selectBarrier), index +1));
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		index2 = i;
		break;
	}
}
index2--; //Base 0

function_s(focus, "swapBarriers", index1, index2);
function_s(focus, "rebuildMeshes");
set(itemcurrent(selectBarrier), index +1);
function_s(selectBarrier, "refreshList");
repaintall();</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Move the selected barrier down in the list</data></node>
           </data></node>
           <node f="42" dt="4"><name>SelectBarrier</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405c8000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040508000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>5555555540535555</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>000000004074c000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Choose a barrier to edit</data></node>
            <node f="42"><name>items</name>
             <node f="40"><name></name></node></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
            <node f="42" dt="2"><name>result</name><data></data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>refreshList</name><data>int filter = get(itemcurrent(node("../FilterType", c)));
treenode barriers = node("@&gt;objectfocus+&gt;variables/barriers", c);

clearcontents(items(c));

switch (filter) {
	case 1:  //Show All
		function_s(c, "filterList", "");
	break;
	
	case 2:  //Barriers
		function_s(c, "filterList", "AStar::Barrier");
	break;
	
	case 3:  //Divider
		function_s(c, "filterList", "AStar::Divider");
	break;
	
	case 4:  //One-Way Divider
		function_s(c, "filterList", "AStar::OneWayDivider");
	break;
	
	case 5:  //Preferred Path	
		function_s(c, "filterList", "AStar::PreferredPath");
	break;
	
	case 6:  //Bridge	
		function_s(c, "filterList", "AStar::Bridge");
	break;
}

listboxrefresh(c);

string name = getname(rank(items(c), get(itemcurrent(c))));
treenode barrierNode = 0;
for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		barrierNode = rank(barriers, i);
		break;
	}
}

nodepoint(node("../Attributes&gt;objectfocus", c), barrierNode);
function_s(node("../Attributes", c), "refreshData");</data></node>
             <node f="442" dt="2"><name>filterList</name><data>string type = param(1);

treenode result = node("&gt;result", c);
treenode barriers = node("@&gt;objectfocus+&gt;variables/barriers", c);

for (int i = 1; i &lt;= content(barriers); i++) {
	function_s(ownerobject(barriers), "getBarrierType", rank(barriers, i), result);
	if (comparetext(type, gets(result)) || stringlen(type) == 0) {
		treenode itm = nodeadddata(nodeinsertinto(items(c)), DATATYPE_NUMBER);
		setname(itm, getname(rank(barriers, i)));
		set(itm, i);
	}
}</data></node>
             <node f="42" dt="2"><name>OnSelect</name><data>treenode focus = node("@&gt;objectfocus+", c);
treenode barriers = getvarnode(focus, "barriers");
string name = getname(rank(items(c), get(itemcurrent(c))));
treenode barrierNode;

for (int i = 1; i &lt;= content(barriers); i++) {
	if (comparetext(getname(rank(barriers, i)), name)) {
		barrierNode = rank(barriers, i);
		break;
	}
}

nodepoint(node("../Attributes&gt;objectfocus", c), barrierNode);
function_s(node("../Attributes", c), "refreshData");

function_s(focus, "setActiveBarrier", barrierNode);
function_s(focus, "rebuildMeshes");
repaintall();</data></node>
            </node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>000000004072c000</data></node>
            <node f="42" dt="1"><name>alignbottommargin</name><data>00000000402c0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>Attributes</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>5555555540545555</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>000000004072e000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>555555554076f555</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="2"><name>result</name><data></data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>refreshData</name><data>treenode focus = node("&gt;objectfocus+", c);
int enable = objectexists(focus);

int path = 0;
int bridge = 0;
int useVirtualDistance = 0;
if (enable) {
	treenode pointsEdit = node("/PointsEdit", c);
	
	treenode result = node("&gt;result", c);
	function_s(ownerobject(focus), "getBarrierType", focus, result);
	string type = gets(result);
	
	path = comparetext(type, "AStar::PreferredPath");
	if (path) {
		double pathWeight = function_s(ownerobject(focus), "getPathWeight", focus);
		setvarnum(node("/PathWeight/editPathWeight", c), "weight", pathWeight);
	} else {
		setvarnum(node("/PathWeight/editPathWeight", c), "weight", 0);
	}
	
	int showPoints = !comparetext(type, "AStar::Barrier");
	windowshow(windowfromnode(pointsEdit), showPoints);
	windowshow(windowfromnode(node("/BarrierPoints", c)), !showPoints);
	
	bridge = comparetext(type, "AStar::Bridge");
	windowshow(windowfromnode(node("/VirtualDistance", c)), bridge);
	windowshow(windowfromnode(node("/PathWeight", c)), !bridge);
	if (bridge) {
		useVirtualDistance = get(node("/useVirtualDistance", focus));
		double virtualDistance = node("/virtualDistance", focus).value;
		setvarnum(node("/VirtualDistance/editVirtualDistance", c), "virtualDistance", virtualDistance);
	} else {
		setvarnum(node("/VirtualDistance/editVirtualDistance", c), "weight", 0);
	}
	
	applylinks(c, 1);
}

windowgray(windowfromnode(node("/Name", c)), !enable);
windowgray(windowfromnode(node("/editName", c)), !enable);
windowgray(windowfromnode(node("/VirtualDistance/Virtual Distance", c)), !enable || !bridge);

forobjecttreeunder(node("/PathWeight", c))
	windowgray(windowfromnode(a), !enable || !path);

forobjecttreeunder(node("/VirtualDistance/editVirtualDistance", c))
	windowgray(windowfromnode(a), !useVirtualDistance);

forobjecttreeunder(node("/PointsEdit", c))
	windowgray(windowfromnode(a), !enable);

forobjecttreeunder(node("/BarrierPoints", c))
	windowgray(windowfromnode(a), !enable);</data></node>
            </node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040736000</data></node>
            <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040240000</data></node>
           </data>
            <node f="40"><name></name></node>
            <node f="42" dt="4"><name>Name</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000040310000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>00000000403e0000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
            </data></node>
            <node f="42" dt="4"><name>editName</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>00000000406b2000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>0000000040340000</data></node>
             <node f="42" dt="2"><name>tooltip</name><data>Enter the name of the barrier</data></node>
             <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>applylinks(c);
treenode selectBarrier = node("../../SelectBarrier", c);
setname(rank(items(selectBarrier), get(itemcurrent(selectBarrier))), getviewtext(c));
listboxrefresh(selectBarrier);</data></node>
             <node f="42" dt="2"><name>coldlinkx</name><data>treenode focus = node("..&gt;objectfocus+", c);
if (objectexists(focus)) {
	if (eventdata) {
		setname(focus, getviewtext(c));
	} else {
		setviewtext(c, getname(focus));
	}
}</data>
              <node f="40" dt="7"><name></name><data/>
               <node f="40"><name></name></node>
               <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
                <node f="40"><name></name></node></node>
              </node></node>
            </data></node>
            <node f="42" dt="4"><name>PathWeight</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040458000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
             <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
              <node f="40"><name></name></node></node>
             <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
            </data>
             <node f="40"><name></name></node>
             <node f="42" dt="4"><name>Path Weight</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040310000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
             </data></node>
             <node f="42" dt="4"><name>editPathWeight</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
              <node f="42" dt="2"><name>objectfocus</name><data>..&gt;variables/weight</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Path Weight</data></node>
              <node f="42"><name>variables</name>
               <node f="40"><name></name></node>
               <node f="42" dt="2"><name>valuetype</name><data></data></node>
               <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
               <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
               <node f="42" dt="1"><name>ishotlink</name><data>000000003ff00000</data></node>
               <node f="42" dt="1"><name>conversion</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>weight</name><data>0000000000000000</data></node>
               <node f="442" dt="2"><name>OnKillFocus</name><data>treenode focus = node("../../../..&gt;objectfocus+", c);

 function_s(ownerobject(focus), "setPathWeight", focus, getvarnum(up(up(c)), "weight"));</data></node>
              </node>
             </data>
              <node f="40"><name></name></node></node>
            </node>
            <node f="42" dt="4"><name>VirtualDistance</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040458000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
             <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
              <node f="40"><name></name></node></node>
             <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
            </data>
             <node f="40"><name></name></node>
             <node f="42" dt="4"><name>Virtual Distance</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
              <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+/useVirtualDistance</data></node>
              <node f="42" dt="2"><name>OnPress</name><data>applylinks(c);

int gray = !getchecked(c);
forobjecttreeunder(node("../editVirtualDistance", c))
	windowgray(windowfromnode(a), gray);</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Use a virtual distance instead of the actual bridge distance.</data></node>
             </data></node>
             <node f="42" dt="4"><name>editVirtualDistance</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>000000004067c000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
              <node f="42" dt="2"><name>objectfocus</name><data>..&gt;variables/virtualDistance</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Virtual Distance</data></node>
              <node f="42"><name>variables</name>
               <node f="40"><name></name></node>
               <node f="42" dt="2"><name>valuetype</name><data></data></node>
               <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
               <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
               <node f="42" dt="1"><name>ishotlink</name><data>000000003ff00000</data></node>
               <node f="42" dt="1"><name>conversion</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>virtualDistance</name><data>0000000000000000</data></node>
               <node f="442" dt="2"><name>OnKillFocus</name><data>treenode focus = node("../../../..&gt;objectfocus+", c);

node("/virtualDistance", focus).value = getvarnum(up(up(c)), "virtualDistance");</data></node>
              </node>
             </data>
              <node f="40"><name></name></node></node>
            </node>
            <node f="42" dt="4"><name>PointsEdit</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040524000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>000000004072e000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>aaaaaaab40726aaa</data></node>
             <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
            </data>
             <node f="40"><name></name></node>
             <node f="42" dt="4"><name>Points</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040310000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040440000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
             </data></node>
             <node f="42" dt="4"><name>Add</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("/points", barrier);
double x = get(node("/x", last(pointsNode)));
double y = get(node("/y", last(pointsNode)));

function_s(ownerobject(barrier), "addPoint", barrier, x +2, y +2);
applylinks(table, 1);
refreshview(table);
function_s(ownerobject(barrier), "setActiveIndex", barrier, content(pointsNode) -1);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
</data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="2"><name>tooltip</name><data>Add a new point</data></node>
              <node f="42" dt="2"><name>bitmap</name><data>buttons\add.png</data></node>
             </data>
              <node f="40"><name></name></node></node>
             <node f="42" dt="4"><name>Remove</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>00000000405b4000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("/points", barrier);

if (content(node("&gt;viewfocus+", table)) &lt;= 2) {
	msg("Error", "You must have at least 2 points.", 1);
	return 0;
}

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

function_s(ownerobject(barrier), "removePoint", barrier, index-1);
applylinks(table, 1);
refreshview(table);
function_s(ownerobject(barrier), "setActiveIndex", barrier, index -2);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
settableviewselection(table, maxof(1, index -1), 0, maxof(1, index -1), 2);
repaintview(table);</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Remove the selected point</data></node>
              <node f="42" dt="2"><name>bitmap</name><data>buttons\remove.png</data></node>
             </data></node>
             <node f="42" dt="4"><name>Up</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040614000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>bitmap</name><data>buttons\uparrow_blue.png</data></node>
              <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

if (index &lt;= 1)
	return 0;

function_s(ownerobject(barrier), "swapPoints", barrier, index -1, index -2);
applylinks(table, 1);
refreshview(table);
function_s(ownerobject(barrier), "setActiveIndex", barrier, index -2);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
settableviewselection(table, index -1, 0, index -1, 2);
repaintview(table);</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Move the selected point up in the list</data></node>
             </data></node>
             <node f="42" dt="4"><name>Down</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>000000004064e000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
              <node f="42" dt="2"><name>bitmap</name><data>buttons\downarrow_blue.png</data></node>
              <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;
	
if (index == 0 || index &gt;= content(node("&gt;viewfocus+", table)))
	return 0;

function_s(ownerobject(barrier), "swapPoints", barrier, index -1, index);
applylinks(table, 1);
refreshview(table);
function_s(ownerobject(barrier), "setActiveIndex", barrier, index);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
settableviewselection(table, index +1, 0, index +1, 2);
repaintview(table);</data></node>
              <node f="42" dt="2"><name>tooltip</name><data>Move the selected point down in the list</data></node>
             </data></node>
             <node f="42" dt="4"><name>PointsTable</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="2"><name>viewfocus</name><data>..&gt;table</data></node>
              <node f="42"><name>table</name>
               <node f="40"><name></name></node></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040140000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000040380000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>00000000406b2000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>aaaaaaab40709aaa</data></node>
              <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
              <node f="42" dt="2"><name>hotlinkx</name><data>#define POINT_X 1
#define POINT_Y 2
#define POINT_Z 3

treenode focus = node("../..&gt;objectfocus+", c);
treenode table = node("&gt;table", c);
treenode astarNavigator = ownerobject(focus);
treenode result = node("../..&gt;result", c);

if (!objectexists(focus))
	return 0;
	
if (gets(result) == "AStar::Barrier")
	return 0;

if (!eventdata) {
	clearcontents(table);
	for (int i = 0; i &lt; content(node("/points", focus)); i++) {
		double x = function_s(astarNavigator, "getPointCoord", focus, i, POINT_X);
		double y = function_s(astarNavigator, "getPointCoord", focus, i, POINT_Y);
		
		treenode parent = nodeinsertinto(table);
		treenode xNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(xNode, x);
		treenode yNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(yNode, y);
		
		if (gets(result) == "AStar::Bridge") {
			double z = function_s(astarNavigator, "getPointCoord", focus, i, POINT_Z);
			treenode zNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
			set(zNode, z);
		}
	}
	if (content(table) &gt;= 1) {
		setname(rank(first(table), POINT_X), "X");
		setname(rank(first(table), POINT_Y), "Y");
		if (gets(result) == "AStar::Bridge")
			setname(rank(first(table), POINT_Z), "Z");
	}
} else {
	int rebuildMeshes = 0;
	for (int i = 0; i &lt; content(node("/points", focus)); i++) {
		double x = function_s(astarNavigator, "getPointCoord", focus, i, POINT_X);
		double y = function_s(astarNavigator, "getPointCoord", focus, i, POINT_Y);
		double z = 0;
		
		treenode newpoints = rank(table, i+1);
		double newx = get(newpoints.subnodes[POINT_X]);
		double newy = get(newpoints.subnodes[POINT_Y]);
		double newz = 0;
		
		if (gets(result) == "AStar::Bridge") {
			z = function_s(astarNavigator, "getPointCoord", focus, i, POINT_Z);
			newz = get(newpoints.subnodes[POINT_Z]);
		}
		
		if (x != newx || y != newy || z != newz) {
			rebuildMeshes = 1;
			function_s(astarNavigator, "setPointCoords", focus, i, newx, newy, newz);
		}
	}
	
	if (rebuildMeshes) {
		function_s(astarNavigator, "rebuildMeshes");
		repaintall();
	}	
}</data>
               <node f="40" dt="7"><name></name><data/>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
                 <node f="40"><name></name></node></node>
               </node></node>
              <node f="42" dt="2"><name>OnKeyUp</name><data>#define VK_RETURN 13
if (lastkeydown() == VK_RETURN) {
	applylinks(c);
}</data></node>
              <node f="42" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE) {
	applylinks(c);

	treenode barrier = node("../..&gt;objectfocus+", c);
	treenode focus = node("&gt;table", c);
	treenode selected = selectedobject(c);

	if (objectexists(selected)) {
		int index;
		if (up(selected) == focus) {
			index = getrank(selected);
		} else if (up(up(selected)) == focus) {
			index = getrank(up(selected));
		}
		if (get(itemcurrent(c)) == index) 
			return 0;
		set(itemcurrent(c), index);
		
		function_s(ownerobject(barrier), "setActiveIndex", barrier, index -1);
		function_s(ownerobject(barrier), "rebuildMeshes");
		repaintall();
	}
}
</data></node>
              <node f="42" dt="2"><name>OnMouseWheel</name><data>treenode TheTable = ownerobject(c);

double vert_nMin = scrollinfo(TheTable,0,1,1);
double vert_nMax = scrollinfo(TheTable,0,1,2);
double vert_nPage = scrollinfo(TheTable,0,1,3);
double vert_nPos = scrollinfo(TheTable,0,1,4);

// OnMouseWheelDelta is set to an amount when you scroll the wheel
// this amount is about 1/4 of a page size to scroll each time the mousewheel clicks once
double amount = get(node("&gt;OnMouseWheelDelta",TheTable))/480*vert_nPage;

// set the position based on the wheeled amount
scrollinfo(TheTable,1,1,4,vert_nPos-amount);
repaintview(TheTable);


</data></node>
              <node f="42" dt="1"><name>OnMouseWheelDelta</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>cellwidth</name><data>0000000040540000</data>
               <node f="40"><name></name></node>
               <node f="42" dt="1"><name></name><data>0000000040140000</data></node>
               <node f="42" dt="1"><name></name><data>0000000040504000</data></node>
               <node f="42" dt="1"><name></name><data>0000000040504000</data></node>
               <node f="42" dt="1"><name></name><data>00000000404e0000</data></node>
              </node>
              <node f="42" dt="1"><name>cellheight</name><data>0000000040320000</data></node>
              <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040140000</data></node>
              <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
              <node f="42" dt="1"><name>dataentry</name><data>0000000000000000</data></node>
              <node f="42"><name>noformat</name></node>
              <node f="42"><name>undohistory</name>
               <node f="40"><name></name></node>
               <node f="42" dt="1"><name>undo limit</name><data>0000000040900000</data></node>
               <node f="42" dt="3"><name>history</name><data><coupling>null</coupling></data></node>
               <node f="42" dt="1"><name>bin</name><data>0000000000000000</data></node>
              </node>
             </data>
              <node f="40"><name></name></node></node>
            </node>
            <node f="42" dt="4"><name>BarrierPoints</name><data>
             <node f="40"><name>object</name></node>
             <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
             <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
             <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
             <node f="42" dt="1"><name>spatialy</name><data>0000000040524000</data></node>
             <node f="42" dt="1"><name>spatialsx</name><data>000000004072e000</data></node>
             <node f="42" dt="1"><name>spatialsy</name><data>000000004057c000</data></node>
             <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
             <node f="42" dt="2"><name>hotlinkx</name><data>#define POINT_X 1
#define POINT_Y 2

treenode focus = node("..&gt;objectfocus+", c);
treenode astarNavigator = ownerobject(focus);

if (!objectexists(focus))
	return 0;
	
if (gets(node("..&gt;result", c)) != "AStar::Barrier")
	return 0;

if (eventdata) {
	double x1 = getvarnum(c, "posx");
	double y1 = getvarnum(c, "posy");
	double sizex = getvarnum(c, "sizex");
	double sizey = getvarnum(c, "sizey");

	double nodeWidth = getvarnum(ownerobject(focus), "nodeWidth");
	if (sizex &lt; nodeWidth) {
		sizex = nodeWidth;
		setvarnum(c, "sizex", sizex);
	}
	if (sizey &lt; nodeWidth) {
		sizey = nodeWidth;
		setvarnum(c, "sizey", sizey);
	}

	double x2 = sizex + x1;
	double y2 = sizey + y1;
	
	if (x1 != getvarnum(c, "x1") || y1 != getvarnum(c, "y1") || x2 != getvarnum(c, "x2") || y2 != getvarnum(c, "y2")) {
		function_s(astarNavigator, "setPointCoords", focus, 0, x1, y1);
		function_s(astarNavigator, "setPointCoords", focus, 1, x2, y2);
		function_s(astarNavigator, "rebuildMeshes");
		repaintall();
	}
} else {
	double x1 = function_s(astarNavigator, "getPointCoord", focus, 0, POINT_X);
	double y1 = function_s(astarNavigator, "getPointCoord", focus, 0, POINT_Y);
	double x2 = function_s(astarNavigator, "getPointCoord", focus, 1, POINT_X);
	double y2 = function_s(astarNavigator, "getPointCoord", focus, 1, POINT_Y);
	
	setvarnum(c, "posx", x1);
	setvarnum(c, "posy", y1);
	setvarnum(c, "sizex", x2 - x1);
	setvarnum(c, "sizey", y2 - y1);
	
	setvarnum(c, "x1", x1);
	setvarnum(c, "y1", y1);
	setvarnum(c, "x2", x2);
	setvarnum(c, "y2", y2);
	
	//Create our own hotlink with the MeasuredValueEdit THIS IS NECESSARY!
	applylinks(node("/X/editX/EditValue", c), 1);
	applylinks(node("/X/editSX/EditValue", c), 1);
	applylinks(node("/Y/editY/EditValue", c), 1);
	applylinks(node("/Y/editSY/EditValue", c), 1);
}</data>
              <node f="40" dt="7"><name></name><data/>
               <node f="40"><name></name></node>
               <node f="42" dt="2"><name>sdt::attributetree</name><data>FlexScriptCode</data>
                <node f="40"><name></name></node></node>
              </node></node>
             <node f="42"><name>variables</name>
              <node f="40"><name></name></node>
              <node f="42" dt="1"><name>posx</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>sizex</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>posy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>sizey</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>oldposx</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>oldsizex</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>oldposy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>oldsizey</name><data>0000000000000000</data></node>
             </node>
            </data>
             <node f="40"><name></name></node>
             <node f="42" dt="4"><name>Position and Size</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040310000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040490000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>00000000403e0000</data></node>
             </data></node>
             <node f="42" dt="4"><name>Labels</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040540000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040518000</data></node>
              <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
             </data>
              <node f="40"><name></name></node>
              <node f="42" dt="4"><name>Loc</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
               <node f="42" dt="2"><name>bitmap</name><data>buttons\move.png</data></node>
              </data></node>
              <node f="42" dt="4"><name>Size</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
               <node f="42" dt="2"><name>bitmap</name><data>buttons\resize.png</data></node>
              </data></node>
             </node>
             <node f="42" dt="4"><name>X</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040580000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040518000</data></node>
              <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
             </data>
              <node f="40"><name></name></node>
              <node f="42" dt="4"><name>Label</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>55555555404a5555</data></node>
               <node f="42" dt="1"><name>aligncenterx</name><data>0000000040240000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
               <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
              </data></node>
              <node f="42" dt="4"><name>editX</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040558000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
               <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;variables/posx</data></node>
               <node f="42" dt="2"><name>tooltip</name><data>X Position
(in $LENGTH_PLURAL$)</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
               <node f="42"><name>variables</name>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>valuetype</name><data>length</data></node>
                <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
                <node f="42" dt="1"><name>ishotlink</name><data>0000000000000000</data></node>
                <node f="442" dt="2"><name>OnKillFocus</name><data>treenode parent = up(up(up(up(c))));
setvarnum(parent, "posx", stringtonum(getviewtext(node("/EditValue", up(up(c))))));
applylinks(parent);</data></node>
                <node f="42" dt="1"><name>unsigned</name><data>0000000000000000</data></node>
                <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               </node>
              </data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="4"><name>editSX</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040558000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
               <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;variables/sizex</data></node>
               <node f="42" dt="2"><name>tooltip</name><data>X Size
(in $LENGTH_PLURAL$)</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
               <node f="42"><name>variables</name>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>valuetype</name><data>length</data></node>
                <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
                <node f="42" dt="1"><name>ishotlink</name><data>0000000000000000</data></node>
                <node f="442" dt="2"><name>OnKillFocus</name><data>treenode parent = up(up(up(up(c))));
setvarnum(parent, "sizex", stringtonum(getviewtext(node("/EditValue", up(up(c))))));
applylinks(parent);</data></node>
                <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               </node>
              </data>
               <node f="40"><name></name></node></node>
             </node>
             <node f="42" dt="4"><name>Y</name><data>
              <node f="40"><name>object</name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040686000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="1"><name>spatialsy</name><data>0000000040518000</data></node>
              <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
             </data>
              <node f="40"><name></name></node>
              <node f="42" dt="4"><name>Label</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>55555555404a5555</data></node>
               <node f="42" dt="1"><name>aligncenterx</name><data>0000000040240000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
               <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
              </data></node>
              <node f="42" dt="4"><name>editY</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040558000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
               <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;variables/posy</data></node>
               <node f="42" dt="2"><name>tooltip</name><data>Y Position
(in $LENGTH_PLURAL$)</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
               <node f="42"><name>variables</name>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>valuetype</name><data>length</data></node>
                <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
                <node f="42" dt="1"><name>ishotlink</name><data>0000000000000000</data></node>
                <node f="442" dt="2"><name>OnKillFocus</name><data>treenode parent = up(up(up(up(c))));
setvarnum(parent, "posy", stringtonum(getviewtext(node("/EditValue", up(up(c))))));
applylinks(parent);</data></node>
                <node f="42" dt="1"><name>unsigned</name><data>0000000000000000</data></node>
                <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               </node>
              </data>
               <node f="40"><name></name></node></node>
              <node f="42" dt="4"><name>editSY</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040558000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
               <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;variables/sizey</data></node>
               <node f="42" dt="2"><name>tooltip</name><data>Y Size
(in $LENGTH_PLURAL$)</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
               <node f="42"><name>variables</name>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>valuetype</name><data>length</data></node>
                <node f="42" dt="1"><name>spinner</name><data>000000003ff00000</data></node>
                <node f="42" dt="1"><name>ishotlink</name><data>0000000000000000</data></node>
                <node f="442" dt="2"><name>OnKillFocus</name><data>treenode parent = up(up(up(up(c))));
setvarnum(parent, "sizey", stringtonum(getviewtext(node("/EditValue", up(up(c))))));
applylinks(parent);</data></node>
                <node f="42" dt="1"><name>eternalSpinner</name><data>0000000000000000</data></node>
               </node>
              </data>
               <node f="40"><name></name></node></node>
             </node>
            </node>
           </node>
          </node>
         </node>
         <node f="42" dt="4"><name>Triggers</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>helptopic</name><data>TriggersTab</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>OnReset</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040468000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditOnReset</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040550000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>555555554073a555</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/EasyCodeTrigger</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/resettrigger</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>picklist</name><data>VIEW:/picklists/resettriggerpicklist</data></node>
            <node f="42" dt="2"><name>codedescription</name><data>OnReset</data></node>
           </node>
          </data></node>
          <node f="42" dt="4"><name>OnMessage</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040430000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditOnMessage</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040550000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>555555554073a555</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/EasyCodeTrigger</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/messagetrigger</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when messages are sent to this object</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>picklist</name><data>VIEW:/picklists/messagetriggerpicklist</data></node>
            <node f="42" dt="2"><name>codedescription</name><data>OnMessage</data></node>
           </node>
          </data></node>
          <node f="42" dt="4"><name>Custom Draw</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040508000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditOnDraw</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040550000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000404f8000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>555555554073a555</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/EasyCodeTrigger</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/ondrawtrigger</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Define custom drawing logic</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>picklist</name><data>VIEW:/picklists/ondrawpicklist</data></node>
            <node f="42" dt="2"><name>codedescription</name><data>Custom Draw</data></node>
           </node>
          </data></node>
         </node>
         <node f="42" dt="4"><name>Labels</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/pages/shared/Labels</data></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>General</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/pages/shared/General</data></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040796000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         </data>
          <node f="40"><name></name></node></node>
        </node>
        <node f="42" dt="4"><name>BottomButtons</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000403c0000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>55555555407a5555</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040360000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/BottomButtons</data></node>
        </data></node>
       </node>
      </node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/fsmacros</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>000000003ff00000</data></node>
    <node f="42"><name>after</name></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="2"><name>AStar</name><data>#define EDITMODE_PREFERRED_PATH 35
#define EDITMODE_DIVIDER 36
#define EDITMODE_ONE_WAY_DIVIDER 37
#define EDITMODE_SOLID_BARRIER 38
#define EDITMODE_BRIDGE 39
</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/nodevariables/ModelUnitScaling</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000404c0000</data></node>
    <node f="42" dt="2"><name>after</name><data>ThreeDView</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="2"><name>AStarNavigator</name><data>/?AStarNavigator</data>
      <node f="40"><name></name></node>
      <node f="42"><name>size</name>
       <node f="40"><name></name></node>
       <node f="42" dt="1"><name></name><data>8f5c28f63ff0f5c2</data></node>
       <node f="42" dt="1"><name></name><data>8f5c28f63ff0f5c2</data></node>
       <node f="42" dt="1"><name></name><data>0a3d70a43fe0a3d7</data></node>
      </node>
      <node f="42"><name>length</name>
       <node f="40"><name></name></node>
       <node f="42" dt="2"><name>nodeWidth</name><data>&gt;variables/nodeWidth</data>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name></name><data>000000003ff00000</data></node>
       </node>
      </node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/picklists/transportrefpicklist</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000402c0000</data></node>
    <node f="42" dt="2"><name>after</name><data>Task Executer as Flowitem</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="2"><name>AStar: Task Executer as Flowitem</name><data>/**AStar: Task Executer as Flowitem*/
/**\nMove the item into the model, then connect it to the AStar Navigator. Then tell it to travel to the destination and unload itself into the object. Note: this will only work for flow items created from the TaskExecuterFlowItem in the flow item bin.*/

Array absloc = Array(3);
Array absrot = Array(3);
// find out the location of the item relative to the model.
updatelocations(current);
absloc[1] = vectorprojectx(item, 0.5*xsize(item),-0.5*ysize(item),0, model());
absloc[2] = vectorprojecty(item, 0.5*xsize(item),-0.5*ysize(item),0, model());
absloc[3] = vectorprojectz(item, 0.5*xsize(item),-0.5*ysize(item),0, model());

// find out the rotation of the item relative to the model.
treenode container = up(item);
absrot[1] = xrot(item);
absrot[2] = yrot(item);
absrot[3] = zrot(item);
while (container != model()){
	absrot[1]+=xrot(container);
	absrot[2]+=yrot(container);
	absrot[3]+=zrot(container);
	container = up(container);
}

// notify myself that the item is about to be loaded.
transportoutcomplete(current, item, port);
// move the item into the model.
moveobject(item, model(), port);
// set the location of the item.
setloc(item, absloc[1] - (0.5*xsize(item)), absloc[2] + (0.5*ysize(item)), absloc[3]);
// set the rotation of the item
setrot(item,absrot[1], absrot[2], absrot[3]);

// connect the item to the AStar Navigator
treenode aStar = node("AStarNavigator", model());
if (objectexists(aStar)) {
	contextdragconnection(aStar, item, 'A');
}

// create a task sequence to travel to the destination location and unload itself into the object.
treenode ts = createemptytasksequence(item,0,0);
inserttask(ts,TASKTYPE_TRAVEL,current.outObjects[port],NULL);
inserttask(ts,TASKTYPE_FRUNLOAD,item,current.outObjects[port],opipno(current,port));
dispatchtasksequence(ts);
return 0;</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/LibraryIconGrid/GroupIconGrid&gt;variables/visibilityLists/base/list</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040180000</data></node>
    <node f="42" dt="2"><name>after</name><data>Visual</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStar</name><data>
      <node f="40"><name></name></node>
      <node f="42" dt="2"><name>viewfocus</name><data>VIEW:/modules/AStar/LibraryGroup</data></node>
      <node f="42" dt="1"><name>picturealignleft</name><data>0000000040360000</data></node>
      <node f="42" dt="1"><name>expanded</name><data>0000000000000000</data></node>
     </data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/events/OnUpdateModel/Update to 17.2</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040080000</data></node>
    <node f="42" dt="2"><name>after</name><data>update Groups</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="442" dt="2"><name>update AStar</name><data>treenode updaterootnode = param(1);
double oldVersion = param(2);

if (oldVersion &gt;= 17.2 || updaterootnode != model())
	return 0;

treenode nav = model().find("AStarNavigator");

if (objectexists(nav)) {
	setvarnum(nav, "enableCollisionAvoidance", 0);
	return 1;
}

return 0;
</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/DefaultEventInfo</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040140000</data></node>
    <node f="42" dt="2"><name>after</name><data>AGVData</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStarTraveler</name>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>OnBlock</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>Object</data></node>
         </node>
         <node f="42"><name>Needs Reroute</name>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Needs Reroute</data></node>
          <node f="42" dt="2"><name>Name</name><data>needsReroute</data></node>
          <node f="42" dt="2"><name>Type</name><data>int</data></node>
         </node>
        </node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>OnContinue</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>Object</data></node>
         </node>
        </node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>OnReroute</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>Object</data></node>
         </node>
        </node>
       </node>
      </data></node>
     </node>
    </node>
   </node>
  </node>
 </node>
 <node f="42" dt="2"><name>release</name><data>17.2</data></node>
 <node f="42" dt="2"><name>revision</name><data>.0</data></node>
 <node f="42" dt="2"><name>flexsim release</name><data>17.2</data></node>
</node></flexsim-tree>
