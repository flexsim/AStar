<?xml version="1.0" encoding="UTF-8"?>
<flexsim-tree version="4" treetype="tree">
<node f="42"><name>AStar</name>
 <node f="40"><name></name></node>
 <node f="42"><name>installdata</name>
  <node f="40"><name></name></node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/library</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000403a0000</data></node>
    <node f="42" dt="2"><name>after</name><data>AGV</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>astar</name>
      <node f="40"><name></name></node>
      <node f="10000042" dt="4"><name>AStarNavigator</name><data>
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
        <node f="42" dt="1"><name>surroundDepth</name><data>0000000040000000</data></node>
        <node f="42" dt="1"><name>drawMode</name><data>0000000040370000</data></node>
        <node f="42" dt="1"><name>defaultPathWeight</name><data>9999999a3fd99999</data></node>
        <node f="42" dt="1"><name>deepSearch</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>ignoreDestBarrier</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>hasEdgeTable</name><data>0000000000000000</data></node>
        <node f="42"><name>grids</name>
         <node f="40"><name></name></node>
         <node f="42" dt="7"><name>MainGrid</name><data/>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>nodeWidth</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>minPointX</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>minPointY</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>minPointZ</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>maxPointX</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>maxPointY</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>maxPointZ</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>gridOriginX</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>gridOriginY</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>gridOriginZ</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>isUserCustomized</name><data>0000000000000000</data></node>
          <node f="42"><name>bridgeData</name></node>
          <node f="42" dt="2"><name>sdt::attributetree</name><data>AStar::Grid</data>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isBounded</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>isLowestGrid</name><data>0000000000000000</data></node>
          </node>
         </node>
        </node>
        <node f="42"><name>barriers</name></node>
        <node f="42" dt="3"><name>activeBarrier</name><data><coupling>null</coupling></data></node>
        <node f="42"><name>barrierConditions</name></node>
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
        <node f="42" dt="1"><name>showTravelThreshold</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>snapBetweenGrid</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>stopForTurns</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>turnDelay</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>turnSpeed</name><data>0000000040568000</data></node>
        <node f="42" dt="1"><name>estimatedIndefiniteAllocTimeDelay</name><data>0000000040240000</data></node>
        <node f="42" dt="1"><name>routeByTravelTime</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>deallocTimeOffset</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>transparentBaseColor</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>debugRoutingAlgorithm</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>routingAlgorithmCompletionRatio</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>hasCustomUserGrids</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="1000042" dt="2"><name>addObject</name><data>dll:"module:AStar" func:"AStarNavigator_addObject"</data></node>
         <node f="1000042" dt="2"><name>addMember</name><data>dll:"module:AStar" func:"AStarNavigator_addMember"</data></node>
         <node f="1000042" dt="2"><name>getGrid</name><data>dll:"module:AStar" func:"AStarNavigator_getGrid"</data></node>
         <node f="1000042" dt="2"><name>rebuildMeshes</name><data>dll:"module:AStar" func:"AStarNavigator_rebuildMeshes"</data></node>
         <node f="1000042" dt="2"><name>rebuildEdgeTable</name><data>dll:"module:AStar" func:"AStarNavigator_rebuildEdgeTable"</data></node>
         <node f="1000042" dt="2"><name>removeBarrier</name><data>dll:"module:AStar" func:"AStarNavigator_removeBarrier"</data></node>
         <node f="1000042" dt="2"><name>removeMember</name><data>dll:"module:AStar" func:"AStarNavigator_removeMember"</data></node>
         <node f="1000042" dt="2"><name>setActiveBarrier</name><data>dll:"module:AStar" func:"AStarNavigator_setActiveBarrier"</data></node>
         <node f="1000042" dt="2"><name>swapBarriers</name><data>dll:"module:AStar" func:"AStarNavigator_swapBarriers"</data></node>
         <node f="1000042" dt="2"><name>blockGridModelPos</name><data>dll:"module:AStar" func:"AStarNavigator_blockGridModelPos"</data></node>
         <node f="1000042" dt="2"><name>divideGridModelLine</name><data>dll:"module:AStar" func:"AStarNavigator_divideGridModelLine"</data></node>
         <node f="1000042" dt="2"><name>dumpBlockageData</name><data>dll:"module:AStar" func:"AStarNavigator_dumpBlockageData"</data></node>
         <node f="1000042" dt="2"><name>addCopiedMember</name><data>dll:"module:AStar" func:"AStarNavigator_addMember"</data></node>
         <node f="1000042" dt="2"><name>addObjectBarrierToTable</name><data>dll:"module:AStar" func:"AStarNavigator_addObjectBarrierToTable"</data></node>
         <node f="42" dt="2"><name>flexScriptInterface</name><data>AStar.Navigator</data></node>
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
          <node f="42" dt="1"><name>type</name><data>0000000040100000</data></node>
          <node f="42" dt="1"><name>flags</name><data>0000000040400000</data></node>
          <node f="42" dt="1"><name>curValue</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>startValue</name><data>0000000000000000</data></node>
         </node>
        </node>
        <node f="42" dt="1"><name>collisionUpdateInterval</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>nextCollisionUpdateTime</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>heatMapTotalTraversals</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>minNodeWidth</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>hasConditionalBarriers</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>hasMandatoryPaths</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>extraData</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>visual</name>
        <node f="40"><name></name></node>
        <node f="42"><name>color</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>red</name><data>1d1d1d1d3fcd1d1d</data></node>
         <node f="42" dt="1"><name>green</name><data>525252523fd25252</data></node>
         <node f="42" dt="1"><name>blue</name><data>3a3a3a3a3fea3a3a</data></node>
        </node>
        <node f="42" dt="2"><name>shape</name><data>***</data></node>
        <node f="42" dt="1"><name>shapeindex</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>imageobject</name><data>***</data>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>split</name><data>modules\AStar\bitmaps\split.png</data></node>
         <node f="42" dt="2"><name>merge</name><data>modules\AStar\bitmaps\merge.png</data></node>
        </node>
        <node f="42" dt="1"><name>imageindexobject</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>split</name><data>000000004052c000</data></node>
         <node f="42" dt="1"><name>merge</name><data>0000000040530000</data></node>
        </node>
        <node f="42" dt="2"><name>imagebase</name><data>***</data></node>
        <node f="42" dt="1"><name>imageindexbase</name><data>0000000000000000</data></node>
        <node f="42"><name>drawsurrogate</name>
         <node f="40"><name></name></node>
         <node f="100062" dt="4"><name>Shape</name><data>
          <node f="40"><name></name></node>
          <node f="42"><name>spatial</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>9999999a3ff19999</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>000000003ff00000</data></node>
           <node f="42" dt="1"><name>spatialsz</name><data>9999999a3fc99999</data></node>
           <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>centroid</name><data>000000003ff00000</data></node>
           <node f="42" dt="1"><name>offsetx</name><data>000000003fe00000</data></node>
           <node f="42" dt="1"><name>offsety</name><data>e00000003fdffffd</data></node>
           <node f="42" dt="1"><name>offsetz</name><data>000000003fe00000</data></node>
           <node f="42" dt="1"><name>offsetsx</name><data>0a3d70a43fe8a3d7</data></node>
           <node f="42" dt="1"><name>offsetsy</name><data>a3d70a3d3fea3d70</data></node>
           <node f="42" dt="1"><name>offsetsz</name><data>3333333340133333</data></node>
           <node f="42" dt="1"><name>offsetrx</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>offsetry</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>offsetrz</name><data>0000000000000000</data></node>
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
           <node f="42" dt="2"><name>imageobject</name><data>***</data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="1"><name>imageindexobject</name><data>0000000000000000</data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="2"><name>imagebase</name><data>***</data></node>
           <node f="42" dt="1"><name>imageindexbase</name><data>0000000000000000</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
        </node>
       </node>
       <node f="42"><name>special</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>title</name><data>AStar Navigator</data></node>
        <node f="42" dt="2"><name>description</name><data></data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/Pages/AStarProperties</data></node>
        <node f="42" dt="2"><name>tooltip</name><data></data></node>
       </node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>centroid</name><data>000000003ff00000</data></node>
       </node>
      </data></node>
      <node f="10100062" dt="4"><name>Barrier</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Barrier</name><data><coupling>/installdata/add/1/data/astar/Barrier</coupling></data></node>
       </node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>FlexSimEventHandler</name><data><coupling>null</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="80000040"><name></name></node>
        <node f="42" dt="1"><name>points</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="42" dt="7"><name>p1</name><data/>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>x</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>y</name><data>00000000c0140000</data></node>
          <node f="42" dt="1"><name>z</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>sdt::attributetree</name><data>AStar::Point</data>
           <node f="40"><name></name></node></node>
         </node>
         <node f="42" dt="7"><name>p2</name><data/>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>x</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>y</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>z</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>sdt::attributetree</name><data>AStar::Point</data>
           <node f="40"><name></name></node></node>
         </node>
        </node>
        <node f="42" dt="1"><name>patternTable</name><data>0000000000000000</data></node>
        <node f="42" dt="3"><name>conditionRule</name><data><coupling>null</coupling></data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node>
        <node f="42"><name>navigator</name></node>
        <node f="42" dt="1"><name>nodeWidth</name><data>000000003ff00000</data></node>
       </node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>47ae147b3f847ae1</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>special</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>title</name><data>AStar Divider</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/Pages/BarrierProperties</data></node>
       </node>
       <node f="42"><name>stored</name></node>
      </data>
       <node f="40"><name></name></node></node>
      <node f="10100062" dt="4"><name>Divider</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Divider</name><data><coupling>/installdata/add/1/data/astar/Divider</coupling></data></node>
       </node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Barrier</name><data><coupling>/installdata/add/1/data/astar/Barrier</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="80000040"><name></name></node>
        <node f="42" dt="1"><name>isTwoWay</name><data>000000003ff00000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>47ae147b3f847ae1</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>special</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>title</name><data>AStar Divider</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/Pages/DividerProperties</data></node>
       </node>
       <node f="42"><name>stored</name></node>
      </data>
       <node f="40"><name></name></node></node>
      <node f="10100062" dt="4"><name>PreferredPath</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::PreferredPath</name><data><coupling>/installdata/add/1/data/astar/PreferredPath</coupling></data></node>
       </node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Divider</name><data><coupling>/installdata/add/1/data/astar/Divider</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="80000040"><name></name></node>
        <node f="42" dt="1"><name>pathWeight</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>isTwoWay</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>47ae147b3f847ae1</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>stored</name></node>
      </data>
       <node f="40"><name></name></node></node>
      <node f="10100062" dt="4"><name>Bridge</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Bridge</name><data><coupling>/installdata/add/1/data/astar/Bridge</coupling></data></node>
       </node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Divider</name><data><coupling>/installdata/add/1/data/astar/Divider</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="80000040"><name></name></node>
        <node f="42" dt="1"><name>useVirtualDistance</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>virtualDistance</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>isTwoWay</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>geometricDistance</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>travelDistance</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>filledDistance</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>isAvailable</name><data>0000000000000000</data></node>
        <node f="42" dt="3"><name>blockedTraveler</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>firstTraveler</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>lastTraveler</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="1"><name>blockedPathIndex</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>47ae147b3f847ae1</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>stored</name></node>
      </data>
       <node f="40"><name></name></node></node>
      <node f="10100062" dt="4"><name>MandatoryPath</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>classes</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::MandatoryPath</name><data><coupling>/installdata/add/1/data/astar/MandatoryPath</coupling></data></node>
       </node>
       <node f="42"><name>superclasses</name>
        <node f="40"><name></name></node>
        <node f="42" dt="3"><name>AStar::Divider</name><data><coupling>/installdata/add/1/data/astar/Divider</coupling></data></node>
       </node>
       <node f="42"><name>variables</name>
        <node f="80000040"><name></name></node>
        <node f="42" dt="1"><name>isTwoWay</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>behaviour</name>
        <node f="40"><name></name></node></node>
       <node f="42"><name>stats</name>
        <node f="40"><name></name></node>
        <node f="42"><name>navigator</name></node>
       </node>
       <node f="42"><name>spatial</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialz</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialsz</name><data>47ae147b3f847ae1</data></node>
        <node f="42" dt="1"><name>spatialrx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialry</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialrz</name><data>0000000000000000</data></node>
       </node>
       <node f="42"><name>stored</name></node>
      </data>
       <node f="40"><name></name></node></node>
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
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\solidbarriertool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="1"><name>mode</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>class</name><data></data></node>
        <node f="42" dt="1"><name>mouseDownScreenX</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>mouseDownScreenY</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>mouseState</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastModelX</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastModelY</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>lastModelZ</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>addToStart</name><data>0000000000000000</data></node>
        <node f="42" dt="3"><name>activeNavigator</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>curObjectNode</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>previousPoint</name><data><coupling>null</coupling></data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
#define BARRIER_MODE_MOVE 0x4

if (!objectexists(i))
	return 0;

if (gets(documentwindow(i)) != "3D")
	return 0;

applicationcommand("assertmoduledependency", "AStar");

int clickCode = clickcode();
int mode = getvarnum(c, "mode");
treenode curObjectNode = tonode(getvarnum(c, "curObjectNode"));

treenode activeNavigator = tonode(getvarnum(c, "activeNavigator"));
if (!objectexists(activeNavigator))
	activeNavigator = function_s(c, "findNavigator");
if (!objectexists(activeNavigator) &amp;&amp; (clickCode == LEFT_PRESS || clickCode == LEFT_RELEASE))
	activeNavigator = createinstance(node("/?AStarNavigator", library()), model());

nodepoint(getvarnode(c, "activeNavigator"), activeNavigator);

Vec3 modelPos = Vec3(cursorinfo(i, 2, 1, 1), cursorinfo(i, 2, 2, 1), cursorinfo(i, 2, 3, 1));
double screenX = cursorinfo(i, 1, 1, 1);
double screenY = cursorinfo(i, 1, 2, 1);
setvarnum(c, "lastModelX", modelPos.x);
setvarnum(c, "lastModelY", modelPos.y);
setvarnum(c, "lastModelZ", modelPos.z);

switch (clickCode) {
	case LEFT_PRESS:
		setvarnum(c, "mouseDownScreenX", screenX);
		setvarnum(c, "mouseDownScreenY", screenY);
		setvarnum(c, "mouseState", LEFT_PRESS);
		break;
	
	case LEFT_RELEASE:
		setvarnum(c, "mouseState", 0);
		
		//Adding onto the ends of dividers
		if(!objectexists(curObjectNode) || up(curObjectNode) != activeNavigator) {
			treenode pointNode = tonode(getpickingdrawfocus(i, PICK_SECONDARY_OBJECT, PICK_PRESSED));
			treenode classNode = first(classes(ownerobject(pointNode)));
			
			if(objectexists(classNode) &amp;&amp; classNode.value.getPath(0, 1) == getvarstr(c, "class")) {
				if(pointNode.rank == 1 || pointNode.rank == content(pointNode.up)) {
					curObjectNode = ownerobject(pointNode);
					function_s(curObjectNode, "setEditMode", BARRIER_MODE_DYNAMIC_CREATE);
					nodepoint(getvarnode(c, "curObjectNode"), curObjectNode);
					nodepoint(getvarnode(c, "previousPoint"), 0);
					
					if(pointNode.rank == 1)
						setvarnum(c, "addToStart", 1);
					
					modeleditmode(EDIT_MODE_DEPTH_PUSH);
				}
			}
		}
		
		if (objectexists(curObjectNode) &amp;&amp; (curObjectNode.up == activeNavigator || curObjectNode.up.up == variables(activeNavigator))) {
			// if I'm currently editing a solid barrier or grid, (it's the second up click)
			// then I should set curObjectNode to 0, meaning I'm done editing the barrier
			if (mode == EDITMODE_SOLID_BARRIER || mode == EDITMODE_GRID) {
				function_s(curObjectNode, "setEditMode", BARRIER_MODE_DYNAMIC_CREATE);
				nodepoint(getvarnode(c, "curObjectNode"), 0); // on a sold barrier, on
				modeleditmode(EDIT_MODE_DEPTH_POP);
			} else {
				// if I'm editing a multi-point object, then subsequent left-releases should add a new point.
				treenode newPoint = function_s(curObjectNode, "addPoint", modelPos.x, modelPos.y, modelPos.z);
				setpickingdrawfocus(i, curObjectNode, PICK_ASTAR_POINT, newPoint, OVERRIDE_SET_MOUSE_DOWN_PICK);
				if(getvarnum(c, "addToStart"))
					newPoint.rank = 1;
				
				treenode previousPoint = getvarnode(c, "previousPoint").value;
				if(objectexists(previousPoint) &amp;&amp; ownerobject(previousPoint) == curObjectNode) {
					// Make an undo record for the created point
					int undoId = beginaggregatedundo(i, "Create A* Object Point");
					createundorecord(i, curObjectNode, UNDO_UPDATE_LINKS_ON_UNDO, 0, 0, 0);
					createundorecord(i, previousPoint, UNDO_CREATE_OBJECT, 0, 0, 0);
					createundorecord(i, curObjectNode, UNDO_UPDATE_LINKS_ON_REDO, 0, 0, 0);
					endaggregatedundo(i, undoId);
				}
				nodepoint(getvarnode(c, "previousPoint"), newPoint);
			}
		} else {
			// on an up-click where there's no currently editing object, then I should see about creating one
			int dx = fabs(screenX - getvarnum(c, "mouseDownScreenX"));
			int dy = fabs(screenY - getvarnum(c, "mouseDownScreenY"));
			
			// I only create a new object on the left release if the user did not drag the mouse (pan the view)
			if (fabs(dx) &lt; 2 &amp;&amp; fabs(dy) &lt; 2) {
				
				double nodeWidth = function_s(activeNavigator, "getGrid", modelPos.x, modelPos.y, modelPos.z).find("nodeWidth").value;
				if (mode != EDITMODE_GRID) {
					// Snap between grid points
					if (getvarnum(activeNavigator, "snapBetweenGrid") &amp;&amp; (mode == EDITMODE_DIVIDER || mode == EDITMODE_ONE_WAY_DIVIDER)) {
						modelPos.x = floor((modelPos.x + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
						modelPos.y = floor((modelPos.y + 0.5 * nodeWidth) / nodeWidth) * nodeWidth;
					}
				}
				string classPath = getvarstr(c, "class");
				if (classPath.length &gt; 0) {
					curObjectNode = createinstance(library().find(classPath), activeNavigator);
					curObjectNode.as(Object).setLocation(modelPos.x, modelPos.y, modelPos.z);
					treenode firstPoint = first(getvarnode(curObjectNode, "points"));
					treenode lastPoint = last(getvarnode(curObjectNode, "points"));
					firstPoint.find("y").value = -0.01 * nodeWidth;
					lastPoint.find("x").value = 0.01 * nodeWidth;
					function_s(curObjectNode, "setEditMode", BARRIER_MODE_DYNAMIC_CREATE);
					setpickingdrawfocus(i, curObjectNode, PICK_ASTAR_POINT, lastPoint, OVERRIDE_SET_MOUSE_DOWN_PICK);
				} else {
					curObjectNode = function_s(activeNavigator, "addObject", modelPos.x, modelPos.y, modelPos.z, modelPos.x, modelPos.y, modelPos.z, mode);
				}
				
				// Make an undo record
				int undoId = beginaggregatedundo(i, "Create A* Object");
				createundorecord(i, activeNavigator, UNDO_UPDATE_LINKS_ON_UNDO, 0, 0, 0);
				createundorecord(i, curObjectNode, UNDO_CREATE_OBJECT, 0, 0, 0);
				createundorecord(i, activeNavigator, UNDO_UPDATE_LINKS_ON_REDO, 0, 0, 0);
				endaggregatedundo(i, undoId);
				
				nodepoint(getvarnode(c, "curObjectNode"), curObjectNode);
				nodepoint(getvarnode(c, "previousPoint"), 0);
				setvarnum(c, "addToStart", 0);
				
				modeleditmode(EDIT_MODE_DEPTH_PUSH);
			}

		}
		break;
	
	case RIGHT_RELEASE:
		if(getvarnum(c, "addToStart")) {
			treenode firstPoint = first(getvarnode(curObjectNode, "points"));
			// Move point into position to be deleted
			if (objectexists(firstPoint))
				firstPoint.rank = content(firstPoint.up);
		}
		if (objectexists(curObjectNode))
			function_s(curObjectNode, "abortCreationMode");
		if (objectexists(activeNavigator))
			function_s(activeNavigator, "rebuildMeshes");
		
		function_s(c, "initialize");
		break;
}
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>if (!objectexists(i))
		return 0;

treenode createdObj = tonode(getvarnum(c, "curObjectNode"));
int mouseState = getvarnum(c, "mouseState");
Vec3 modelPos = Vec3(cursorinfo(i, 2, 1, 1), cursorinfo(i, 2, 2, 1), cursorinfo(i, 2, 3, 1));
if (mouseState == 0) {
	if (createdObj) {
		double dx = modelPos.x - getvarnum(c, "lastModelX");
		double dy = modelPos.y - getvarnum(c, "lastModelY");
		function_s(createdObj, "dragPressedPick", i, modelPos.x, modelPos.y, modelPos.z, dx, dy);
		
		#define WM_PAINT 0x000F
		postwindowmessage(windowfromnode(i), WM_PAINT,0,0);
	}
}

setvarnum(c, "lastModelX", modelPos.x);
setvarnum(c, "lastModelY", modelPos.y);

</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode iconGrid = nodefromwindow(keyboardfocus());
nodepoint(viewfocus(c), iconGrid);
nodepoint(objectfocus(c), selectedobject(iconGrid));

function_s(c, "initialize");</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>// reset all my variables so I don't get revision control diffs
treenode curObjectNode = tonode(getvarnum(c, "curObjectNode"));
treenode activeNavigator = tonode(getvarnum(c, "activeNavigator"));

if(getvarnum(c, "addToStart")) {
	treenode firstPoint = first(getvarnode(curObjectNode, "points"));
	// Move point into position to be deleted
	if (objectexists(firstPoint))
		firstPoint.rank = content(firstPoint.up);
}
if (objectexists(curObjectNode))
	function_s(curObjectNode, "abortCreationMode");
if (objectexists(activeNavigator))
	function_s(activeNavigator, "rebuildMeshes");

nodepoint(objectfocus(c), 0);
nodepoint(viewfocus(c), 0);

setvarnum(c, "mode", 0);
setvarstr(c, "class", "");

function_s(c, "initialize");</data></node>
        <node f="442" dt="2"><name>initialize</name><data>setvarnum(c, "mouseDownScreenX", 0);
setvarnum(c, "mouseDownScreenY", 0);
setvarnum(c, "mouseState", 0);
setvarnum(c, "lastModelX", 0);
setvarnum(c, "lastModelY", 0);
setvarnum(c, "lastModelZ", 0);
setvarnum(c, "addToStart", 0);

nodepoint(getvarnode(c, "activeNavigator"), 0);
nodepoint(getvarnode(c, "curObjectNode"), 0);
nodepoint(getvarnode(c, "previousPoint"), 0);</data></node>
        <node f="442" dt="2"><name>checkStatus</name><data>#define BARRIER_MODE_CREATE 0x2

treenode theEditMode = ownerobject(c);
treenode activeNavigator = tonode(getvarnum(theEditMode, "activeNavigator"));
if (!objectexists(activeNavigator))
	return 0;

treenode object = tonode(getvarnum(theEditMode, "curObjectNode"));
int barrierEditMode = function_s(object, "getEditMode");

if (barrierEditMode &amp; BARRIER_MODE_CREATE)
	return 0;
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
        <node f="42" dt="2"><name>class</name><data>MAIN:/project/library/astar/Barrier</data></node>
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
setvarstr(handler, "class", getvarstr(c, "class"));
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
        <node f="42" dt="2"><name>class</name><data>MAIN:/project/library/astar/Divider</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
setvarstr(handler, "class", getvarstr(c, "class"));
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
        <node f="42" dt="2"><name>class</name><data>MAIN:/project/library/astar/PreferredPath</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
setvarstr(handler, "class", getvarstr(c, "class"));
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
        <node f="42" dt="2"><name>class</name><data>MAIN:/project/library/astar/Bridge</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
setvarstr(handler, "class", getvarstr(c, "class"));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::MandatoryPath</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\mandatorypathtool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_MANDATORY_PATH</data></node>
        <node f="42" dt="2"><name>class</name><data>MAIN:/project/library/astar/MandatoryPath</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnClick(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnMouseMove</name><data>treenode handler = tonode(get(objectfocus(c)));
executefsnode(OnMouseMove(handler), handler, i, eventdata);
</data></node>
        <node f="442" dt="2"><name>OnEntering</name><data>treenode handler = node("../AStar::Create", c);
nodepoint(objectfocus(c), handler);
setvarnum(handler, "mode", executestring(getvarstr(c, "mode")));
setvarstr(handler, "class", getvarstr(c, "class"));
executefsnode(OnEntering(handler), handler, i, eventdata);</data></node>
        <node f="442" dt="2"><name>OnExiting</name><data>executefsnode(OnExiting(first(up(c))), first(up(c)), i, eventdata);
nodepoint(objectfocus(c), 0);</data></node>
       </node>
      </data></node>
      <node f="42" dt="4"><name>AStar::Grid</name><data>
       <node f="40"><name></name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>state</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>type</name><data>Clicker</data></node>
        <node f="42" dt="2"><name>cursor</name><data>modules\AStar\cursors\gridtool.cur</data></node>
        <node f="42"><name>views</name>
         <node f="40"><name></name></node>
         <node f="42"><name>Spatial</name></node>
        </node>
        <node f="42" dt="2"><name>mode</name><data>EDITMODE_GRID</data></node>
       </node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>#define BARRIER_MODE_DYNAMIC_CREATE 0x3
treenode handler = tonode(get(objectfocus(c)));
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
        <node f="42" dt="2"><name>windowtitle</name><data>A* Navigator</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\astarnavigatorsmall.png</data></node>
       </data></node>
       <node f="42" dt="4"><name>Barrier</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::Barrier");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/Barrier</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>WorkingWithAStar#divider</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	treenode obj = c.find("..&gt;objectfocus+");
	treenode createdObj = dropuserlibraryobject(obj, ontoObj, ontoLoc.x, ontoLoc.y, ontoLoc.z, ontoView);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>An area where travelers cannot go 
or where travel direction is constrained</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\solidbarrier.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Divider</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::Divider");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/Divider</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>WorkingWithAStar#divider</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	treenode obj = c.find("..&gt;objectfocus+");
	treenode createdObj = dropuserlibraryobject(obj, ontoObj, ontoLoc.x, ontoLoc.y, ontoLoc.z, ontoView);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>A line or set of lines that blocks travel
like a wall</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\divider.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Preferred Path</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::PreferredPath");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/PreferredPath</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>WorkingWithAStar#preferred</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	treenode obj = c.find("..&gt;objectfocus+");
	treenode createdObj = dropuserlibraryobject(obj, ontoObj, ontoLoc.x, ontoLoc.y, ontoLoc.z, ontoView);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>A path that acts as a "magnet" for travelers to travel on</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\preferredpath.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Bridge</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::Bridge");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/Bridge</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>WorkingWithAStar#bridges</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	treenode obj = c.find("..&gt;objectfocus+");
	treenode createdObj = dropuserlibraryobject(obj, ontoObj, ontoLoc.x, ontoLoc.y, ontoLoc.z, ontoView);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>A path that directly connects one location to another.</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\bridge.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Mandatory Path</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::MandatoryPath");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/MandatoryPath</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>WorkingWithAStar#mandatoryPaths</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	treenode obj = c.find("..&gt;objectfocus+");
	treenode createdObj = dropuserlibraryobject(obj, ontoObj, ontoLoc.x, ontoLoc.y, ontoLoc.z, ontoView);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>A path that designated travelers must travel on</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\mandatorypath.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Grid</name><data>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_RELEASE)
	modeleditmode("AStar::Grid");</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>MAIN:/project/library/astar/Grid</data>
         <node f="2000040"><name></name></node></node>
        <node f="42" dt="2"><name>helptopic</name><data>AStarTool#grids</data></node>
        <node f="442" dt="2"><name>dropscript</name><data>treenode ontoObj = param(1);
Vec3 ontoLoc = Vec3(param(2), param(3), param(4));
treenode ontoView = param(5);
if (ontoView) {
	Object nav = model().find("AStarNavigator");
	if (!nav)
		nav = createinstance(library().find("?AStarNavigator"), model());
	treenode createdObj = function_s(nav, "createGrid", ontoLoc.x, ontoLoc.y, ontoLoc.z);
	postwindowmessage(systemwindow(0), FLEXSIM_MESSAGE_USER_NODEFUNCTION, c);
	return createdObj;
} else {
	modeleditmode(0);
}</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>A custom-definable A* grid</data></node>
        <node f="42" dt="2"><name>picture</name><data>modules\AStar\bitmaps\grid.bmp</data></node>
       </data></node>
      </node>
      <node f="42"><name>Pages</name>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>AStarProperties</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040666000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>000000004057c000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000407db000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>000000004082a000</data></node>
        <node f="42" dt="2"><name>windowtitle</name><data>A* Navigator Properties</data></node>
        <node f="442" dt="2"><name>OnOpen</name><data>treenode tabcontrol = node("/tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnOpen",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnOpen",rank(tabcontrol,count)));
}

repaintview(c);</data></node>
        <node f="42" dt="2"><name>OnPreOpen</name><data>c.name = "AStarProperties";
standardpreopen(c);
</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="2"><name>OnClose</name><data></data></node>
        <node f="442" dt="2"><name>OnApply</name><data>treenode tabcontrol = node("../tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnApply",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnApply",rank(tabcontrol,count)));
}</data></node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>addBarrierCondition</name><data>treenode addedView = function_s(c.find("/tabcontrol/BarrierConditions/Panel"), "addItem");
treenode addedCondition = addedView.find("&gt;objectfocus+");
function_s(c, "selectBarrierCondition", addedCondition, addedView);
return addedCondition;
</data></node>
         <node f="442" dt="2"><name>selectBarrierCondition</name><data>treenode focusedCondition = param(1);
treenode focusedPanel = param(2);
Object tabControl = c.find("/tabcontrol");
Object conditionsTab = tabControl.find("/BarrierConditions");
Object dragPanel = conditionsTab.find("/Panel");
if (!focusedPanel &amp;&amp; focusedCondition) {
	focusedPanel = dragPanel.find("ViewPort/ItemPanel").subnodes[focusedCondition.rank].find("PropertiesPanel").first;
}

if (itemcurrent(tabControl).value != conditionsTab.rank) {
	windowshow(windowfromnode(tabControl.subnodes[itemcurrent(tabControl).value]), 0);
	itemcurrent(tabControl).value = conditionsTab.rank;
	windowshow(windowfromnode(conditionsTab), 1);
	#define TCM_SETCURSEL 0x130c
	sendwindowmessage(windowfromnode(tabControl), TCM_SETCURSEL, conditionsTab.rank - 1, 0);
}
if (focusedPanel) {
	Object titleEdit = focusedPanel.find("/Title");
	string title = getviewtext(focusedPanel);
	keyboardfocus(titleEdit);
	highlightviewtext(titleEdit, 0, title.length, 2);
}
</data></node>
        </node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>tabcontrol</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405cc000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>55555555407c1555</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>aaaaaaab407c0aaa</data></node>
         <node f="42" dt="1"><name>itemcurrent</name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040100000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040440000</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Source pages</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Setup</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000407bc000</data></node>
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
          <node f="42" dt="4"><name>Surround Depth</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000402e0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditSurround</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405e0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040280000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/MeasuredValueEdit</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/surroundDepth</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Specify how many nodes will appear around the outside of the A* area.</data></node>
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
          <node f="42" dt="4"><name>Smooth Rotations</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040440000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/smoothRotations</data></node>
          </data></node>
          <node f="42" dt="4"><name>Snap Dividers to Grid</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040510000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Snap dividers between points of the A* grid</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/snapBetweenGrid</data></node>
          </data></node>
          <node f="42" dt="4"><name>Paths</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="2"><name>viewfocus</name><data>MAIN:/project/model</data></node>
           <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ac000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040580000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000406b8000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>000000004062a000</data></node>
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
}</data></node>
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
           <node f="42" dt="1"><name>spatialy</name><data>00000000406ee000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>55555555407ae555</data></node>
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
             <node f="42" dt="1"><name>valType</name><data>0000000040700000</data>
              <node f="40"><name></name></node>
              <node f="42"><name>objectPath</name></node>
             </node>
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
            <node f="42" dt="2"><name>OnPress</name><data>treenode list = node("../MembersList", c);
string path = getname(rank(items(list), get(itemcurrent(list))));

treenode member = node(path, model());

if (objectexists(member)) {
	treenode navigator = node("@&gt;objectfocus+", c);
	function_s(navigator, "removeMember", member);
	nodefunction(node("../MembersList&gt;refresh",c));
	repaintall();
}
</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Remove the selected member</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\remove.png</data></node>
           </data></node>
           <node f="42" dt="4"><name>MembersList</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405c8000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040618000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040310000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040714000</data></node>
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
         <node f="42" dt="4"><name>Behavior</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000407bc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Path Routing</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000402a0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>ChooseDeepSearch</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040690000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000405e0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42"><name>items</name>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>Right Angles Only</name><data>0000000040000000</data></node>
            <node f="42" dt="1"><name>Diagonals</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>Deep Diagonals</name><data>000000003ff00000</data></node>
           </node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/deepSearch</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Choose a path routing configuration</data></node>
          </data></node>
          <node f="42" dt="4"><name>CollisionAvoidancePanel</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040430000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040790000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040538000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Collision Avoidance</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/enableCollisionAvoidance</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>if(!eventdata)
	function_s(c, "grayWindows", 1);</data></node>
             <node f="442" dt="2"><name>grayWindows</name><data>int gray = param(1) ? !get(c.find("&gt;coldlink+")) : !getchecked(c);

forobjecttreeunder(up(c)) {
	if (a != c) {
		windowgray(windowfromnode(a), gray);
	}
}
</data></node>
             <node f="42" dt="2"><name>OnPress</name><data>function_s(c, "grayWindows");
</data></node>
            </node>
            <node f="42" dt="2"><name>tooltip</name><data>If checked, travelers will allocate nodes in the travel grid as 
part of their travel, preventing travelers from running 
over each other.</data></node>
           </data></node>
           <node f="42" dt="4"><name>Ignore Inactive Members</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040340000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000403c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040618000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/ignoreInactiveMemberCollisions</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>If checked, travelers will travel through nodes allocated to 
other inactive travelers.</data></node>
           </data></node>
           <node f="42" dt="4"><name>Deallocation Time Offset Factor</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040340000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404d8000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040624000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditDeallocTimeOffset</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040674000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/deallocTimeOffset</data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="2"><name>valueType</name><data>time</data></node>
            </node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>StopForTurnsPanel</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000405e8000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040790000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040538000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Stop for Turns</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Travelers will stop and rotate when they need to turn</data></node>
            <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/stopForTurns</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>if(!eventdata)
	function_s(c, "grayWindows", 1);</data></node>
             <node f="442" dt="2"><name>grayWindows</name><data>int gray = param(1) ? !get(c.find("&gt;coldlink+")) : !getchecked(c);

forobjecttreeunder(up(c)) {
	if (a != c) {
		windowgray(windowfromnode(a), gray);
	}
}
</data></node>
             <node f="42" dt="2"><name>OnPress</name><data>function_s(c, "grayWindows");
</data></node>
            </node>
           </data></node>
           <node f="42" dt="4"><name>Turn Speed</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040340000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000403f0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditTurnSpeed</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040674000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000403c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Enter the rotation speed for when stopping to rotate</data></node>
            <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/turnSpeed</data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="2"><name>valueType</name><data>rotationspeed</data></node>
            </node>
           </data></node>
           <node f="42" dt="4"><name>Turn Delay</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040340000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404d8000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditTurnDelay</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040674000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>00000000404c0000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Enter the rotation speed for when stopping to rotate</data></node>
            <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/turnDelay</data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="2"><name>valueType</name><data>time</data></node>
            </node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>Route By Travel Time</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>000000004069c000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Do routing calculations based on the calculated travel time, 
including turn times and time waiting for other travelers.</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/routeByTravelTime</data></node>
          </data></node>
          <node f="42" dt="4"><name>Default Preferred Path Weight</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406da000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>000000004064c000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditPathWeight</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040690000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406d4000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040568000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/defaultPathWeight</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Default path weight for newly created Preferred Paths.</data></node>
          </data>
           <node f="40"><name></name></node></node>
         </node>
         <node f="42" dt="4"><name>Visual</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000407bc000</data></node>
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
setchecked(node("/Show Grid Bounds", up(c)), drawmode &amp; ASTAR_DRAW_MODE_BOUNDS);
setchecked(node("/Show Grid Nodes", up(c)), drawmode &amp; ASTAR_DRAW_MODE_GRID);
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
drawmode += getchecked(node("/Show Grid Bounds", up(c))) ? ASTAR_DRAW_MODE_BOUNDS : 0;
drawmode += getchecked(node("/Show Grid Nodes", up(c))) ? ASTAR_DRAW_MODE_GRID : 0;
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
          <node f="42" dt="4"><name>Show Grid Bounds</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040430000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show A* grid boundaries</data></node>
          </data></node>
          <node f="42" dt="4"><name>Show Grid Nodes</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040508000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040604000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to show A* grid nodes</data></node>
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
           <node f="42" dt="2"><name>tooltip</name><data>Check to show a heat map of the A* grid</data></node>
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
            <node f="42"><name>Percent of Total Traversals</name></node>
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
          <node f="42" dt="4"><name>MaxHeatValueSpinner</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
           <node f="42" dt="2"><name>viewfocus</name><data>../../EditMaxHeatValue</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040703000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000406a0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040320000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data></data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
           <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
           <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
           <node f="42" dt="1"><name>rangemin</name><data>0000000000000000</data></node>
           <node f="42"><name>eventfunctions</name>
            <node f="40"><name></name></node>
            <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
            <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
           </node>
           <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
           <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
          </data></node>
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
          <node f="42" dt="4"><name>Show Travel Threshold</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040704000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040690000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to display the nodes around the highlighted object where
a traveller could end their travel to the object</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/showTravelThreshold</data></node>
          </data></node>
          <node f="42" dt="4"><name>Debug Routing Algorithm</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040720000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040690000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Check to display the nodes around the highlighted object where
a traveller could end their travel to the object</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>@&gt;objectfocus+&gt;variables/debugRoutingAlgorithm</data></node>
           <node f="42"><name>eventfunctions</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata)
	function_s(c, "grayWindows", 1);</data></node>
            <node f="42" dt="2"><name>OnPress</name><data>function_s(c, "grayWindows")</data></node>
            <node f="442" dt="2"><name>grayWindows</name><data>int gray = param(1) ? !c.find("&gt;coldlink+")?.value : !getchecked(c);
windowgray(windowfromnode(c.find("../Completion Percent")), gray);
windowgray(windowfromnode(c.find("../CompletionRatioTracker")), gray);
</data></node>
           </node>
           <node f="42" dt="2"><name>windowtitle</name><data>Debug/Show Routing Algorithm</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          </data></node>
          <node f="42" dt="4"><name>Completion Percent</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040418000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>000000004073f000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) 
	function_s(up(c), "enableHeatMapControls");</data></node>
          </data></node>
          <node f="42" dt="4"><name>CompletionRatioTracker</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405e8000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>000000004060e000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>000000004073c000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>5555555540730555</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
           <node f="42" dt="2"><name>hotlink</name><data>@&gt;objectfocus+&gt;variables/routingAlgorithmCompletionRatio</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>000000003fe00000</data></node>
           <node f="42" dt="1"><name>rangemin</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>rangemax</name><data>000000003ff00000</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>To use this, click on an A* traveler in the model, then move this tracker to 
see the progression of that traveler's last routing algorithm execution.</data></node>
          </data></node>
         </node>
         <node f="42" dt="4"><name>BarrierConditions</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000407bc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000407aa000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
          <node f="42" dt="2"><name>windowtitle</name><data>Barrier Conditions</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Panel</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/DragViewPanel</data></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000407c0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000407b1000</data></node>
           <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>00000000401c0000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>@&gt;objectfocus+&gt;variables/barrierConditions</data></node>
           <node f="42" dt="2"><name>viewfocus</name><data>@&gt;viewfocus+</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42"><name>listItemTemplates</name>
             <node f="40"><name></name></node>
             <node f="42" dt="4"><name>Condition</name><data>
              <node f="40"><name></name></node>
              <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
              <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
              <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
              <node f="42" dt="1"><name>spatialsx</name><data>0000000040240000</data></node>
              <node f="42" dt="1"><name>spatialsy</name><data>00000000404f0000</data></node>
              <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040380000</data></node>
              <node f="42" dt="2"><name>viewfocus</name><data>../../../../../..</data></node>
              <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
              <node f="42"><name>eventfunctions</name>
               <node f="40"><name></name></node></node>
             </data>
              <node f="40"><name></name></node>
              <node f="42" dt="4"><name>Title</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>000000004053c000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
               <node f="42" dt="2"><name>coldlinkname</name><data>../..&gt;objectfocus+</data></node>
              </data></node>
              <node f="42" dt="4"><name>Edit</name><data>
               <node f="40"><name>object</name></node>
               <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
               <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
               <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
               <node f="42" dt="1"><name>spatialsx</name><data>0000000040468000</data></node>
               <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
               <node f="42" dt="1"><name>alignrightmargin</name><data>00000000401c0000</data></node>
               <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/EasyCodeEdit</data></node>
               <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+</data></node>
               <node f="42" dt="2"><name>tooltip</name><data>Define the condition </data></node>
               <node f="42"><name>variables</name>
                <node f="40"><name></name></node>
                <node f="42" dt="2"><name>codedescription</name><data>Barrier Condition</data></node>
                <node f="42" dt="2"><name>picklist</name><data>VIEW:/modules/AStar/PickLists/BarrierCondition</data>
                 <node f="40"><name></name></node></node>
                <node f="42" dt="1"><name>hasDragTarget</name><data>0000000000000000</data></node>
                <node f="42" dt="1"><name>valType</name><data>000000003ff00000</data>
                 <node f="40"><name></name></node>
                 <node f="42"><name>number</name></node>
                </node>
                <node f="42" dt="2"><name>codefocus</name><data>../..&gt;objectfocus+</data></node>
               </node>
              </data>
               <node f="40"><name></name></node></node>
             </node>
            </node>
            <node f="42" dt="2"><name>itemfocus</name><data>&gt;objectfocus+</data></node>
            <node f="42" dt="2"><name>addButtonTooltip</name><data>Add a new condition</data></node>
            <node f="42" dt="1"><name>addButtonViewBeveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="2"><name>removeButtonTooltip</name><data>Remove this condition</data></node>
            <node f="442" dt="2"><name>defaultCondition</name><data>Object traveler = param(1);
return /**/traveler.Type == 1/**direct*/;
</data></node>
           </node>
           <node f="42"><name>eventfunctions</name>
            <node f="40"><name></name></node>
            <node f="442" dt="2"><name>panelFromItem</name><data>treenode item = param(1);
treenode templates = param(2);
return templates.first;</data></node>
            <node f="442" dt="2"><name>destroyItem</name><data>treenode condition = param(1);
treenode panel = param(2);
if (msg("Remove Condition?", "Some objects may reference this condition.\r\nRemoving it cannot be undone.\r\n\r\nContinue?"))
	condition.destroy();
else return 1;
</data></node>
            <node f="442" dt="2"><name>createItem</name><data>treenode conditions = c.find("&gt;objectfocus+");
treenode defaultCondition = c.find("&gt;variables/defaultCondition");
treenode newCondition = createcopy(defaultCondition, conditions);
newCondition.name = "Rule " + string.fromNum(conditions.subnodes.length);
return newCondition;
</data></node>
           </node>
          </data>
           <node f="40"><name></name></node></node>
         </node>
         <node f="42" dt="4"><name>Triggers</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/pages/shared/Triggers</data></node>
          <node f="42" dt="2"><name>objectfocus</name><data>MODEL:/AStarNavigator</data></node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Labels</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/pages/shared/Labels</data></node>
          <node f="42" dt="1"><name>viewwindowopen</name><data>000000003ff00000</data></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000407bc000</data></node>
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
         <node f="42" dt="1"><name>spatialsx</name><data>00000000407cc000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040360000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/BottomButtons</data></node>
        </data></node>
       </node>
       <node f="42" dt="4"><name>DividerProperties</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>00000000406e0000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040606000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040790000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040781000</data></node>
        <node f="42" dt="2"><name>windowtitle</name><data>A* Barrier Properties</data></node>
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
        <node f="42" dt="2"><name>OnClose</name><data></data></node>
        <node f="442" dt="2"><name>OnApply</name><data>treenode tabcontrol = node("../tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnApply",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnApply",rank(tabcontrol,count)));
}</data></node>
        <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
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
        <node f="42" dt="4"><name>editname</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000402c0000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040760000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
         <node f="42" dt="2"><name>coldlinkname</name><data>@&gt;objectfocus+</data></node>
        </data></node>
        <node f="42" dt="4"><name>Attributes</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040762000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040771000</data></node>
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
	
	string type = function_s(focus, "getType");
	
	path = comparetext(type, "AStar::PreferredPath");
	if (path) {
		double pathWeight = function_s(focus, "getWeight");
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

function_s(c, "grayCondition");

forobjecttreeunder(node("/PathWeight", c))
	windowgray(windowfromnode(a), !enable || !path);

forobjecttreeunder(node("/VirtualDistance/editVirtualDistance", c))
	windowgray(windowfromnode(a), !useVirtualDistance);

forobjecttreeunder(node("/PointsEdit", c))
	windowgray(windowfromnode(a), !enable);

forobjecttreeunder(node("/BarrierPoints", c))
	windowgray(windowfromnode(a), !enable);</data></node>
         </node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040418000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040240000</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Condition</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
         </data></node>
         <node f="42" dt="4"><name>ChooseCondition</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040534000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data>Define the condition by which this divider/path will be applied</data></node>
          <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+&gt;variables/conditionRule</data></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/GUIClasses/ChooseCondition</data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node></node>
         </data></node>
         <node f="42" dt="4"><name>Two Way</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
          <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+&gt;variables/isTwoWay</data></node>
          <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	treenode focus = c.find("..&gt;objectfocus+");
	windowgray(windowfromnode(c), isclasstype(focus, "AStar::Bridge"));
}</data></node>
          <node f="42" dt="2"><name>tooltip</name><data>Tells if the object's rule applies both ways</data></node>
         </data></node>
         <node f="42" dt="4"><name>PointsEdit</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000c0240000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>00000000404d8000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040728000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040418000</data></node>
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
           <node f="42" dt="1"><name>spatialx</name><data>000000004055c000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);
double x = get(node("/x", last(pointsNode)));
double y = get(node("/y", last(pointsNode)));

function_s(barrier, "addPoint", x +2, y +2);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", content(pointsNode) -1);
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
           <node f="42" dt="1"><name>spatialx</name><data>00000000405d0000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

if (content(node("&gt;viewfocus+", table)) &lt;= 2) {
	msg("Error", "You must have at least 2 points.", 1);
	return 0;
}

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

function_s(barrier, "removePoint", index-1);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index -2);
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
           <node f="42" dt="1"><name>spatialx</name><data>0000000040622000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>bitmap</name><data>buttons\uparrow_blue.png</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

if (index &lt;= 1)
	return 0;

function_s(barrier, "swapPoints", index -1, index -2);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index -2);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
settableviewselection(table, index -1, 0, index -1, 2);
repaintview(table);</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Move the selected point up in the list</data></node>
          </data></node>
          <node f="42" dt="4"><name>Down</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>000000004065c000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>bitmap</name><data>buttons\downarrow_blue.png</data></node>
           <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;
	
if (index == 0 || index &gt;= content(node("&gt;viewfocus+", table)))
	return 0;

function_s(barrier, "swapPoints", index -1, index);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index);
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
           <node f="42" dt="1"><name>spatialx</name><data>000000004055c000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040380000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>000000004070b000</data></node>
           <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>hotlinkx</name><data>#define POINT_X 1
#define POINT_Y 2
#define POINT_Z 3

treenode focus = node("../..&gt;objectfocus+", c);
treenode table = node("&gt;table", c);

if (!objectexists(focus))
	return 0;

if (!eventdata) {
	clearcontents(table);
	for (int i = 0; i &lt; content(node("&gt;variables/points", focus)); i++) {
		double x = function_s(focus, "getPointCoord", i, POINT_X);
		double y = function_s(focus, "getPointCoord", i, POINT_Y);
		double z = function_s(focus, "getPointCoord", i, POINT_Z);
		
		treenode parent = nodeinsertinto(table);
		treenode xNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(xNode, x);
		treenode yNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(yNode, y);
		treenode zNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(zNode, z);
	}
	if (content(table) &gt;= 1) {
		setname(rank(first(table), POINT_X), "X");
		setname(rank(first(table), POINT_Y), "Y");
		setname(rank(first(table), POINT_Z), "Z");
	}
} else {
	int rebuildMeshes = 0;
	int haveSetZ = 0; // only get to set z once because it a z change applies to everyone
	for (int i = 0; i &lt; content(node("&gt;variables/points", focus)); i++) {
		double x = function_s(focus, "getPointCoord", i, POINT_X);
		double y = function_s(focus, "getPointCoord", i, POINT_Y);
		double z = function_s(focus, "getPointCoord", i, POINT_Z);
		treenode newpoints = rank(table, i+1);
		double newx = get(newpoints.subnodes[POINT_X]);
		double newy = get(newpoints.subnodes[POINT_Y]);
		double newz = get(newpoints.subnodes[POINT_Z]);
		
		if (x != newx || y != newy) {
			rebuildMeshes = 1;
			function_s(focus, "setPointCoords", i, newx, newy, newz);
		} else if (z != newz &amp;&amp; !haveSetZ) {
			rebuildMeshes = 1;
			haveSetZ = 1;
			function_s(focus, "setPointCoords", i, newx, newy, newz);
		}
	}
	
	if (rebuildMeshes) {
		repaintall();
	}	
}</data></node>
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
		
		function_s(barrier, "setActiveIndex", index - 1);
		repaintall();
	}
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>if (!objectexists(i) || i != c)
	applylinks(c, 1);</data></node>
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
           <node f="42" dt="1"><name>cellheight</name><data>0000000040320000</data>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name></name><data>0000000040320000</data></node>
           </node>
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
         <node f="42" dt="4"><name>PathWeight</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000c0240000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>000000004076a000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>alignbottomposition</name><data>00000000403c0000</data></node>
          <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	int isPreferredPath = isclasstype(c.find("..&gt;objectfocus+"), "AStar::PreferredPath");
	windowshow(windowfromnode(c), isPreferredPath);
}</data></node>
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
          <node f="42" dt="4"><name>EditPathWeight</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>000000004055c000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+&gt;variables/pathWeight</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Path Weight</data></node>
          </data>
           <node f="40"><name></name></node></node>
         </node>
         <node f="42" dt="4"><name>VirtualDistance</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>000000004076a000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
           <node f="40"><name></name></node></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>alignbottomposition</name><data>00000000403c0000</data></node>
          <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	int isBridge = isclasstype(c.find("..&gt;objectfocus+"), "AStar::Bridge");
	windowshow(windowfromnode(c), isBridge);
}</data></node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Virtual Distance</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
           <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+&gt;variables/useVirtualDistance</data></node>
           <node f="42"><name>eventfunctions</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>OnPress</name><data>function_s(c, "grayWindows");</data></node>
            <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	setchecked(c, c.find("&gt;coldlink+")?.value);
	function_s(c, "grayWindows");
}
</data></node>
            <node f="442" dt="2"><name>grayWindows</name><data>int useVirtualDistance = getchecked(c);
forobjecttreeunder(c.find("../EditVirtualDistance")) {
	windowgray(windowfromnode(a), !useVirtualDistance);
}
</data></node>
           </node>
           <node f="42" dt="2"><name>tooltip</name><data>Use a virtual distance instead of the actual bridge distance.</data></node>
          </data></node>
          <node f="42" dt="4"><name>EditVirtualDistance</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>00000000405b8000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
           <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
           <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;objectfocus+&gt;variables/virtualDistance</data></node>
           <node f="42" dt="2"><name>tooltip</name><data>Virtual Distance</data></node>
           <node f="42"><name>variables</name>
            <node f="40"><name></name></node>
            <node f="42" dt="2"><name>valueType</name><data>length</data></node>
           </node>
          </data>
           <node f="40"><name></name></node></node>
         </node>
        </node>
        <node f="42" dt="4"><name>BottomButtons</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000407a2000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040360000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>alignbottomposition</name><data>00000000403c0000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/BottomButtons</data></node>
        </data></node>
       </node>
       <node f="42" dt="4"><name>BarrierProperties</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>00000000406e0000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040606000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040790000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000406cc000</data></node>
        <node f="42" dt="2"><name>windowtitle</name><data>A* Barrier Properties</data></node>
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
        <node f="42" dt="2"><name>OnClose</name><data></data></node>
        <node f="442" dt="2"><name>OnApply</name><data>treenode tabcontrol = node("../tabcontrol",c);
iterate(1, content(tabcontrol), 1){
  if (objectexists(node("&gt;PageOnApply",rank(tabcontrol,count))))
     nodefunction(node("&gt;PageOnApply",rank(tabcontrol,count)));
}</data></node>
        <node f="42" dt="2"><name>helptopic</name><data>AStarTool</data></node>
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
        <node f="42" dt="4"><name>editname</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000402c0000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040760000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
         <node f="42" dt="2"><name>coldlinkname</name><data>@&gt;objectfocus+</data></node>
        </data></node>
        <node f="42" dt="4"><name>Attributes</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040450000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040762000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040771000</data></node>
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
	
	string type = function_s(focus, "getType");
	
	path = comparetext(type, "AStar::PreferredPath");
	if (path) {
		double pathWeight = function_s(focus, "getWeight");
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

function_s(c, "grayCondition");

forobjecttreeunder(node("/PathWeight", c))
	windowgray(windowfromnode(a), !enable || !path);

forobjecttreeunder(node("/VirtualDistance/editVirtualDistance", c))
	windowgray(windowfromnode(a), !useVirtualDistance);

forobjecttreeunder(node("/PointsEdit", c))
	windowgray(windowfromnode(a), !enable);

forobjecttreeunder(node("/BarrierPoints", c))
	windowgray(windowfromnode(a), !enable);</data></node>
         </node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000040418000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040240000</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Condition</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040240000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
         </data></node>
         <node f="42" dt="4"><name>ChooseCondition</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040534000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data>Define the condition by which this divider/path will be applied</data></node>
          <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+&gt;variables/conditionRule</data></node>
          <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/GUIClasses/ChooseCondition</data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node></node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>SizingPanel</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>00000000403b0000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000406a0000</data>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>min</name><data>0000000040590000</data></node>
          </node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42"><name>X</name>
            <node f="40"><name></name></node>
            <node f="442" dt="2"><name>loc</name><data>return spatialx(param(1));</data></node>
            <node f="442" dt="2"><name>rot</name><data>return spatialrx(param(1));</data></node>
            <node f="442" dt="2"><name>size</name><data>return spatialsx(param(1));</data></node>
           </node>
           <node f="42"><name>Y</name>
            <node f="40"><name></name></node>
            <node f="442" dt="2"><name>loc</name><data>return spatialy(param(1));</data></node>
            <node f="442" dt="2"><name>rot</name><data>return spatialry(param(1));</data></node>
            <node f="442" dt="2"><name>size</name><data>return spatialsy(param(1));</data></node>
           </node>
           <node f="42"><name>Z</name>
            <node f="40"><name></name></node>
            <node f="442" dt="2"><name>loc</name><data>return spatialz(param(1));</data></node>
            <node f="442" dt="2"><name>rot</name><data>return spatialrz(param(1));</data></node>
            <node f="442" dt="2"><name>size</name><data>return spatialsz(param(1));</data></node>
           </node>
           <node f="42" dt="1"><name>isDirect</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>selectedGroup</name><data>0000000040080000</data></node>
           <node f="42" dt="1"><name>selectedIcon</name><data>0000000040180000</data></node>
           <node f="42" dt="1"><name>xCoordFactor</name><data>000000003fe00000</data></node>
           <node f="42" dt="1"><name>yCoordFactor</name><data>000000003fe00000</data></node>
           <node f="42" dt="1"><name>zCoordFactor</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>cantSampleText</name><data>This is a calculated value that can't be sampled.
Switch to Direct Spatials mode before sampling.</data></node>
           <node f="42" dt="2"><name>changeMessage</name><data></data></node>
          </node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
          <node f="42"><name>splitterx</name></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>convertCoord</name><data>string axis = param(1);
treenode obj = param(2);

double xFactor = getvarnum(c, "xCoordFactor") * xsize(obj); 
double yFactor = -getvarnum(c, "yCoordFactor") * ysize(obj);
double zFactor = getvarnum(c, "zCoordFactor") * zsize(obj);

if (axis == "x")
	return vectorprojectx(obj, xFactor, yFactor, zFactor, up(obj));
if (axis == "y")
	return vectorprojecty(obj, xFactor, yFactor, zFactor, up(obj));
if (axis == "z")
	return vectorprojectz(obj, xFactor, yFactor, zFactor, up(obj));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node>
          <node f="42" dt="4"><name>Labels</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>min</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>max</name><data>0000000040390000</data></node>
            <node f="42" dt="1"><name>desired</name><data>0000000040390000</data></node>
           </node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Loc</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040390000</data></node>
            <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="42" dt="2"><name>OnPress</name><data>createpopup("VIEW:/popups/CoordinateSystem", nodetopath(up(up(c))), nodetopath(c), c, -260, 0, 260, 642);</data>
              <node f="40"><name></name></node></node>
            </node>
            <node f="42" dt="2"><name>bitmap</name><data>bitmaps/CoordinateSystems/Mid6_small.png</data></node>
            <node f="42" dt="2"><name>tooltip</name><data>Select the point on the object where the location will be measured</data></node>
           </data></node>
           <node f="42" dt="4"><name>Size</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040480000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040390000</data></node>
            <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
            <node f="42" dt="2"><name>bitmap</name><data>buttons\resize.png</data></node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>X</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/X</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>0000000040390000</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>55555555404ed555</data>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
           </node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Label</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403c0000</data></node>
            <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditLoc</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
            <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
             <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
             <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "x", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
             <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
             <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "x", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; fabs(stringtonum(getviewtext(c)) - toVal) &gt; 0.0000001)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 0, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = xloc(obj) + data - function_s(sizePanel, "convertCoord", "x", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
             <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Spinner</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
             <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
            </node>
            <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
            <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditSize</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
            <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/size</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
             <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>if (eventdata)
	function_s(c, "applyUndoable");
else return nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
             <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
             <node f="442" dt="2"><name>applyUndoable</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = stringtonum(getviewtext(c));
if ((numtostring(get(focus), 0, precision) != getviewtext(c) &amp;&amp; toVal != get(focus)) || param(1) == 1) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	function_s(ownerobject(focus), "setSizeComponent", focus, toVal);
	set(focus, toVal);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
             <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Spinner</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>../../EditSize</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
             <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
            </node>
            <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
            <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>Y</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/Y</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>aaaaaaaa40552aaa</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>55555555404ed555</data>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
           </node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Label</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403d0000</data></node>
            <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditLoc</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
            <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040490000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
             <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
             <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));								
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "y", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
             <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
             <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "y", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; stringtonum(getviewtext(c)) != toVal)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 1, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = yloc(obj) + data - function_s(sizePanel, "convertCoord", "y", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
             <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Spinner</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040490000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
             <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
            </node>
            <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
            <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditSize</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
            <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/size</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040490000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
             <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>if (eventdata)
	function_s(c, "applyUndoable");
else return nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
             <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
             <node f="442" dt="2"><name>applyUndoable</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = stringtonum(getviewtext(c));
if ((numtostring(get(focus), 0, precision) != getviewtext(c) &amp;&amp; toVal != get(focus)) || param(1) == 1) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	function_s(ownerobject(focus), "setSizeComponent", focus, toVal);
	set(focus, toVal);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
             <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Spinner</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>../../EditSize</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040490000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
             <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
            </node>
            <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
            <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
           </data></node>
          </node>
          <node f="42" dt="4"><name>Z</name><data>
           <node f="40"><name>object</name></node>
           <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
           <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/Z</data></node>
           <node f="42" dt="1"><name>spatialx</name><data>aaaaaaaa40624aaa</data></node>
           <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>spatialsx</name><data>55555555404ed555</data>
            <node f="40"><name></name></node>
            <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
            <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
           </node>
           <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
           <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
           <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
           <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
          </data>
           <node f="40"><name></name></node>
           <node f="42" dt="4"><name>Label</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>00000000403c0000</data></node>
            <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
            <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
           </data></node>
           <node f="42" dt="4"><name>EditLoc</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
            <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
            <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42"><name>variables</name>
             <node f="40"><name></name></node>
             <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
             <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
             <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
            </node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "z", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
             <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
             <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
             <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "z", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; stringtonum(getviewtext(c)) != toVal)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 2, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = zloc(obj) + data - function_s(sizePanel, "convertCoord", "z", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
             <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
            </node>
           </data>
            <node f="40"><name></name></node></node>
           <node f="42" dt="4"><name>Spinner</name><data>
            <node f="40"><name>object</name></node>
            <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
            <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
            <node f="42" dt="1"><name>spatialx</name><data>0000000040488000</data></node>
            <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
            <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
            <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
            <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
            <node f="42" dt="2"><name>tooltip</name><data></data></node>
            <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
            <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
            <node f="42"><name>eventfunctions</name>
             <node f="40"><name></name></node>
             <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
             <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
            </node>
            <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
            <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
            <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
           </data></node>
          </node>
         </node>
        </node>
        <node f="42" dt="4"><name>BottomButtons</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>00000000407a2000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040360000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>alignbottomposition</name><data>00000000403c0000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/BottomButtons</data></node>
        </data></node>
       </node>
      </node>
      <node f="42"><name>PickLists</name>
       <node f="40"><name></name></node>
       <node f="42" dt="2"><name>BarrierCondition</name><data>treenode traveler = param(1);
</data>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>By Traveler Label</name><data>return /**/traveler.type == 1/**direct*/;</data></node>
       </node>
      </node>
      <node f="42"><name>GUIClasses</name>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>ChooseCondition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data></data></node>
        <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>ChooseCondition</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>tooltip</name><data></data></node>
         <node f="42"><name>items</name></node>
         <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>coldlink</name><data>../..&gt;objectfocus+</data></node>
         <node f="42"><name>eventfunctions</name>
          <node f="40"><name></name></node>
          <node f="442" dt="2"><name>coldlinkx</name><data>Object view = c;
if (!eventdata) {
	function_s(c, "refreshList");
}
return objectfocus(c.up).find("+");</data></node>
          <node f="442" dt="2"><name>refreshList</name><data>items(c).subnodes.clear();
treenode rules = Model.find("AStarNavigator&gt;variables/barrierConditions");
treenode nullNode = 0;
treenode first = items(c).subnodes.add();
first.name = "No Condition";
first.value = nullNode;
for (int i = 1; i &lt;= rules.subnodes.length; i++) {
	treenode x = items(c).subnodes.add();
	x.name = rules.subnodes[i].name;
	x.value = rules.subnodes[i];
}
treenode last = items(c).subnodes.add();
last.name = "Add New Condition...";
comborefresh(c);
</data></node>
          <node f="42" dt="2"><name>OnSelect</name><data>int isHotLink = getvarnum(c.up, "isHotLink");
int selected = itemcurrent(c).value;
treenode focus = objectfocus(c.up).find("+");
treenode newRule = 0;
if (selected == items(c).subnodes.length) {
	Object navigator = Model.find("AStarNavigator");
	createview(navigator.attrs.guifocusclass.value, navigator.getPath(), "");
	Object propertiesView = Model.find("VIEW:/active/AStarProperties");
	if (propertiesView) {
		newRule = function_s(propertiesView, "addBarrierCondition");
	}
} 

if (isHotLink) {
	int undoID;
	if (objectexists(undohistory(c.up))) {
		undoID = beginaggregatedundo(c.up, "Changed Barrier Condition");
		createundorecord(c.up, c.up, UNDO_UPDATE_LINKS_ON_UNDO);
	}
	if (newRule)
		focus.value = newRule;
	else
		applylinks(c);
	function_s(c.up, "onApply");

	if (objectexists(undohistory(c.up))) {
		createundorecord(c.up, c.up, UNDO_UPDATE_LINKS_ON_REDO);
		endaggregatedundo(c.up, undoID);
	}
} else if (newRule)
	focus.value = newRule;
	

if (newRule)
	applylinks(c, 1);
</data></node>
         </node>
        </data></node>
        <node f="42" dt="4"><name>More</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightposition</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>OnPress</name><data>treenode focus = c.find("..&gt;objectfocus+");

Object navigator = Model.find("AStarNavigator");
createview(navigator.attrs.guifocusclass.value, navigator.getPath(), "");
Object propertiesView = Model.find("VIEW:/active/AStarProperties");
if (propertiesView) {
	function_s(propertiesView, "selectBarrierCondition", focus.value);
}</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Edit this condition in A* Navigator Properties</data></node>
         <node f="42" dt="2"><name>windowtitle</name><data>...</data></node>
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
     <node f="42" dt="2"><name>AStar</name><data>#define PICK_ASTAR_POINT 6

#define EDITMODE_PREFERRED_PATH 35
#define EDITMODE_DIVIDER 36
#define EDITMODE_ONE_WAY_DIVIDER 37
#define EDITMODE_SOLID_BARRIER 38
#define EDITMODE_BRIDGE 39
#define EDITMODE_MANDATORY_PATH 40
#define EDITMODE_GRID 41
</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/nodevariables/ModelUnitScaling</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000404a0000</data></node>
    <node f="42" dt="2"><name>after</name><data>ThreeDView</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="2"><name>AStarNavigator</name><data>/?AStarNavigator</data>
      <node f="40"><name></name></node>
      <node f="42"><name>substructure</name>
       <node f="40"><name></name></node>
       <node f="42" dt="2"><name>Shape</name><data>&gt;visual/drawsurrogate/1</data>
        <node f="40"><name></name></node>
        <node f="42"><name>size</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name></name><data>9999999a3ff19999</data></node>
         <node f="42" dt="1"><name></name><data>000000003ff00000</data></node>
         <node f="42" dt="1"><name></name><data>9999999a3fc99999</data></node>
        </node>
       </node>
      </node>
      <node f="42"><name>length</name>
       <node f="40"><name></name></node>
       <node f="42" dt="2"><name>nodeWidth</name><data>&gt;variables/grids/1/nodeWidth</data>
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
    <node f="42" dt="1"><name>rank</name><data>00000000402a0000</data></node>
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
      <node f="42" dt="2"><name>windowtitle</name><data>A* Navigation</data></node>
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
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object is blocked on the AStar network</data></node>
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
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object continues on the AStar network after being blocked</data></node>
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
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object is rerouted along a different path on the AStar network</data></node>
      </data></node>
     </node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040180000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStarTraveler</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStarTravelerBridgeData</name>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>OnElevatorBankArrival</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>TaskExecuter</data></node>
         </node>
         <node f="42" dt="2"><name>Elevator Bank</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Elevator Bank</data></node>
          <node f="42" dt="2"><name>Name</name><data>elevatorBank</data></node>
          <node f="42" dt="2"><name>Type</name><data>ElevatorBank</data></node>
         </node>
         <node f="42" dt="2"><name>Dest Floor Z</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Dest Floor Z</data></node>
          <node f="42" dt="2"><name>Name</name><data>destFloorZ</data></node>
          <node f="42" dt="2"><name>Type</name><data>double</data></node>
         </node>
        </node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object arrives at an elevator bank to move between floors</data></node>
      </data></node>
      <node f="42" dt="4"><name>OnElevatorBankContinue</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>TaskExecuter</data></node>
         </node>
         <node f="42" dt="2"><name>Elevator Bank</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Elevator Bank</data></node>
          <node f="42" dt="2"><name>Name</name><data>elevatorBank</data></node>
          <node f="42" dt="2"><name>Type</name><data>ElevatorBank</data></node>
         </node>
        </node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object continues from an elevator bank</data></node>
      </data></node>
      <node f="42" dt="4"><name>OnElevatorEntry</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>TaskExecuter</data></node>
         </node>
         <node f="42" dt="2"><name>Elevator</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Elevator</data></node>
          <node f="42" dt="2"><name>Name</name><data>elevator</data></node>
          <node f="42" dt="2"><name>Type</name><data>ElevatorBank.Elevator</data></node>
         </node>
        </node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object enters an elevator</data></node>
      </data></node>
      <node f="42" dt="4"><name>OnElevatorExit</name><data>
       <node f="40"><name></name></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42"><name>params</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>Current</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Current</data></node>
          <node f="42" dt="2"><name>Name</name><data>current</data></node>
          <node f="42" dt="2"><name>Type</name><data>TaskExecuter</data></node>
         </node>
         <node f="42" dt="2"><name>Elevator</name><data></data>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>Title</name><data>Elevator</data></node>
          <node f="42" dt="2"><name>Name</name><data>elevator</data></node>
          <node f="42" dt="2"><name>Type</name><data>ElevatorBank.Elevator</data></node>
         </node>
        </node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data>Define logic that executes when the object enters an elevator</data></node>
      </data></node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/QuickProperties&gt;variables/propertiesPanels</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040428000</data></node>
    <node f="42" dt="2"><name>after</name><data>AGV Type</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStar Traveler</name><data>
      <node f="40"><name>object</name></node>
      <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040180000</data>
       <node f="40"><name></name></node></node>
      <node f="42" dt="2"><name>guifocusclass</name><data>../../..&gt;variables/QuickPropertiesPanel</data></node>
      <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialsx</name><data>0000000040634000</data></node>
      <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
      <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
     </data>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>AStar Traveler</name><data>
       <node f="40"><name>object</name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
       <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
       <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
       <node f="42" dt="1"><name>spatialsx</name><data>000000004062c000</data></node>
       <node f="42" dt="1"><name>spatialsy</name><data>0000000040418000</data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>isExpanded</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>showRequirements</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>selObj</name><data>treenode te = param(1);
if (!objectexists(te) || !isclasstype(te, "TaskExecuter"))
	return 0;
treenode nav = node("&gt;variables/navigator/1+/~", te);
if (objectexists(nav) &amp;&amp; isclasstype(nav, "AStar::AStarNavigator"))
	return 1;
return 0;
</data></node>
         <node f="442" dt="2"><name>docType</name><data>string docType = gets(documentwindow(param(1)));
return docType == "3D" || docType == "Tree";</data></node>
        </node>
       </node>
       <node f="42" dt="2"><name>undohistory</name><data>..&gt;viewfocus+</data></node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>onSelObjChange</name><data>nodepoint(objectfocus(c), node("&gt;variables/navigator/1+", param(1)));
applylinks(c, 1);
</data></node>
        <node f="442" dt="2"><name>onPropsApply</name><data>applylinks(c, 1);</data></node>
        <node f="442" dt="2"><name>onExpand</name><data>if (param(1)) {// expanded
	applylinks(c, 1);
}
</data></node>
        <node f="42" dt="2"><name>OnUndo</name><data>applylinks(c, 1);
</data></node>
       </node>
       <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
       <node f="42" dt="2"><name>tooltip</name><data></data></node>
       <node f="42" dt="2"><name>windowtitle</name><data>A* Traveler</data></node>
       <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
      </data>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>Use Mandatory Paths</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004062c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>When checked, the A* traveler will always travel along mandatory paths</data></node>
        <node f="42" dt="2"><name>coldlink</name><data>../..&gt;objectfocus+/useMandatoryPath</data></node>
        <node f="42" dt="2"><name>OnPress</name><data>applylinks(c);</data></node>
       </data></node>
      </node>
     </node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040440000</data></node>
    <node f="42" dt="2"><name>after</name><data>TestQueries</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStarBarrierProperties</name><data>
      <node f="40"><name>object</name></node>
      <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040180000</data></node>
      <node f="42" dt="2"><name>guifocusclass</name><data>../../..&gt;variables/QuickPropertiesPanel</data></node>
      <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialsx</name><data>0000000040634000</data></node>
      <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
      <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
     </data>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>BarrierProperties</name><data>
       <node f="40"><name>object</name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="2"><name>resizefocus</name><data></data></node>
       <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>GeneralProperties</name><data>VIEW:/active&gt;Tools/GeneralProperties</data></node>
       </node>
       <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
       <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
       <node f="42" dt="1"><name>spatialsx</name><data>000000004066c000</data></node>
       <node f="42" dt="1"><name>spatialsy</name><data>0000000040640000</data></node>
       <node f="42" dt="2"><name>undohistory</name><data>..&gt;viewfocus+</data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>isExpanded</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>showRequirements</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>selObj</name><data>treenode selObj = param(1);
if (!objectexists(selObj) 
		|| getdatatype(selObj) != DATATYPE_OBJECT 
		|| getpickingdrawfocus(activedocumentnode(), PICK_SECONDARY_OBJECT, 0) != 0)
	return 0;

treenode classAtt = selObj.find("&gt;classes/1");
if (classAtt &amp;&amp; classAtt.name == "AStar::Barrier") {
	return 1; 
}

return 0;
</data></node>
         <node f="442" dt="2"><name>docType</name><data>string docType = gets(documentwindow(param(1)));
return docType == "3D" || docType == "Tree";</data></node>
        </node>
       </node>
       <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>onSelObjChange</name><data>treenode selObj = param(1);

nodepoint(objectfocus(c), selObj);
if (getvarnum(c, "isExpanded")) {
	applylinks(c, 1);
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}</data></node>
        <node f="442" dt="2"><name>onDocViewClick</name><data>if (getvarnum(c, "isExpanded"))
	applylinks(c, 1);</data></node>
        <node f="442" dt="2"><name>onExpand</name><data>if (param(1)) {// expanded
	applylinks(c, 1);
	
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}
</data></node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data></data></node>
       <node f="42" dt="2"><name>windowtitle</name><data>Barrier Properties</data></node>
      </data>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>EditName</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000405e4000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Set the Object's Name</data></node>
        <node f="442" dt="2"><name>hotlinkx</name><data>treenode focus = node("..&gt;objectfocus+", c);

if (eventdata) {
	if (!comparetext(getviewtext(c), getname(focus))) {
		int undo_id = beginaggregatedundo(c, "Modify Object Name");
			setname(focus, getviewtext(c));
			validatename(c, 1, focus);
			if(getname(focus) != getviewtext(c))
				setname(focus, getviewtext(c));
		endaggregatedundo(c, undo_id);
		applytoedits(node("..&gt;viewfocus+", c), focus);
	}
} else {
	string name = getnodename(focus);
	if (comparetext(name,"NULL"))
		setviewtext(c, "");
	else
		setviewtext(c, name);
}	</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	executefsnode(OnKillFocus(c), c);
} </data></node>
        <node f="42" dt="2"><name>OnKillFocus</name><data>if (!content(c))
	applylinks(c);

//Update flow item name
treenode activeDoc = activedocumentnode();
if (objectexists(activeDoc) &amp;&amp; objectexists(documentwindow(activeDoc))) {
	string docType = gets(documentwindow(activeDoc));
	if (comparetext(docType, "FlowItem Bin"))
		applicationcommand("notifydoclistenersonpropsapply", node("..&gt;objectfocus+", c));
}
</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040440000</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>renameNum</name><data>000000003ff00000</data></node>
         <node f="42" dt="2"><name>renameText</name><data></data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>showRenamePopup</name><data>treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
setvarstr(c, "renameText", getviewtext(c));
if (content(selected)) {
	createpopup("VIEW:/popups/RenameWarning", nodetopath(c, 1), nodetopath(c, 1), c, 0, 0, 260, 55);	
	applylinks(c, 1);
}

</data></node>
         <node f="442" dt="2"><name>renameSelectedObjects</name><data>int renameNum = getvarnum(c, "renameNum");
string name = getvarstr(c, "renameText");

treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
for (int r = 1; r &lt;= content(selected); r++) {
	treenode actualObject = tonode(get(rank(selected, r)));
	string newName = concat(name, numtostring(renameNum));
	setname(actualObject, newName);
	renameNum++;
}
applytoedits(node("..&gt;viewfocus+", c), node("..&gt;objectfocus+", c));
repaintall();</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>RenameAll</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040180000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040428000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
        <node f="42" dt="1"><name>alignrightposition</name><data>0000000040440000</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnPress</name><data>function_s(node("../EditName", c), "showRenamePopup");</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="2"><name>tooltip</name><data>Rename all selected objects</data></node>
        <node f="42" dt="2"><name>bitmap</name><data>buttons\_rename.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Condition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
       </data></node>
       <node f="42" dt="4"><name>ChooseCondition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040490000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Define the condition by which this barrier is enabled</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+&gt;variables/conditionRule</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/GUIClasses/ChooseCondition</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>isHotLink</name><data>000000003ff00000</data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>onApply</name><data>function_s(c.up.up.up.up, "applyChangesToSelected", c.find("&gt;objectfocus+"), c);</data></node>
        </node>
       </data></node>
       <node f="42" dt="4"><name>SizingPanel</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>000000004051c000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>min</name><data>0000000040590000</data></node>
        </node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040520000</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42"><name>X</name>
          <node f="40"><name></name></node>
          <node f="442" dt="2"><name>loc</name><data>return spatialx(param(1));</data></node>
          <node f="442" dt="2"><name>rot</name><data>return spatialrx(param(1));</data></node>
          <node f="442" dt="2"><name>size</name><data>return spatialsx(param(1));</data></node>
         </node>
         <node f="42"><name>Y</name>
          <node f="40"><name></name></node>
          <node f="442" dt="2"><name>loc</name><data>return spatialy(param(1));</data></node>
          <node f="442" dt="2"><name>rot</name><data>return spatialry(param(1));</data></node>
          <node f="442" dt="2"><name>size</name><data>return spatialsy(param(1));</data></node>
         </node>
         <node f="42"><name>Z</name>
          <node f="40"><name></name></node>
          <node f="442" dt="2"><name>loc</name><data>return spatialz(param(1));</data></node>
          <node f="442" dt="2"><name>rot</name><data>return spatialrz(param(1));</data></node>
          <node f="442" dt="2"><name>size</name><data>return spatialsz(param(1));</data></node>
         </node>
         <node f="42" dt="1"><name>isDirect</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>selectedGroup</name><data>0000000040080000</data></node>
         <node f="42" dt="1"><name>selectedIcon</name><data>0000000040180000</data></node>
         <node f="42" dt="1"><name>xCoordFactor</name><data>000000003fe00000</data></node>
         <node f="42" dt="1"><name>yCoordFactor</name><data>000000003fe00000</data></node>
         <node f="42" dt="1"><name>zCoordFactor</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>cantSampleText</name><data>This is a calculated value that can't be sampled.
Switch to Direct Spatials mode before sampling.</data></node>
         <node f="42" dt="2"><name>changeMessage</name><data></data></node>
        </node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42"><name>splitterx</name></node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>convertCoord</name><data>string axis = param(1);
treenode obj = param(2);

double xFactor = getvarnum(c, "xCoordFactor") * xsize(obj); 
double yFactor = -getvarnum(c, "yCoordFactor") * ysize(obj);
double zFactor = getvarnum(c, "zCoordFactor") * zsize(obj);

if (axis == "x")
	return vectorprojectx(obj, xFactor, yFactor, zFactor, up(obj));
if (axis == "y")
	return vectorprojecty(obj, xFactor, yFactor, zFactor, up(obj));
if (axis == "z")
	return vectorprojectz(obj, xFactor, yFactor, zFactor, up(obj));</data></node>
        </node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>Labels</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>min</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>max</name><data>0000000040390000</data></node>
          <node f="42" dt="1"><name>desired</name><data>0000000040390000</data></node>
         </node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Loc</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040340000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040390000</data></node>
          <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="42" dt="2"><name>OnPress</name><data>createpopup("VIEW:/popups/CoordinateSystem", nodetopath(up(up(c))), nodetopath(c), c, -260, 0, 260, 642);</data>
            <node f="40"><name></name></node></node>
          </node>
          <node f="42" dt="2"><name>bitmap</name><data>bitmaps/CoordinateSystems/Mid6_small.png</data></node>
          <node f="42" dt="2"><name>tooltip</name><data>Select the point on the object where the location will be measured</data></node>
         </data></node>
         <node f="42" dt="4"><name>Size</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040480000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040390000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040390000</data></node>
          <node f="42" dt="1"><name>aligncenterx</name><data>0000000000000000</data></node>
          <node f="42" dt="2"><name>bitmap</name><data>buttons\resize.png</data></node>
         </data></node>
        </node>
        <node f="42" dt="4"><name>X</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/X</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000040390000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
          <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
         </node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Label</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
          <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
         </data></node>
         <node f="42" dt="4"><name>EditLoc</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
          <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000405dc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
           <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
           <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
          </node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "x", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
           <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
           <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
           <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "x", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; fabs(stringtonum(getviewtext(c)) - toVal) &gt; 0.0000001)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 0, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = xloc(obj) + data - function_s(sizePanel, "convertCoord", "x", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Spinner</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
          <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040624000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
           <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
          </node>
          <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
          <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
         </data></node>
         <node f="42" dt="4"><name>EditSize</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
          <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/size</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000405dc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
           <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
          </node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>coldlinkx</name><data>if (eventdata)
	function_s(c, "applyUndoable");
else return nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));</data></node>
           <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
           <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
           <node f="442" dt="2"><name>applyUndoable</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = stringtonum(getviewtext(c));
if ((numtostring(get(focus), 0, precision) != getviewtext(c) &amp;&amp; toVal != get(focus)) || param(1) == 1) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	function_s(ownerobject(focus), "setSizeComponent", focus, toVal);
	set(focus, toVal);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Spinner</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
          <node f="42" dt="2"><name>viewfocus</name><data>../../EditSize</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040624000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
           <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
          </node>
          <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
          <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
         </data></node>
        </node>
        <node f="42" dt="4"><name>Y</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/Y</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000004054c000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
          <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
         </node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Label</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
          <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
         </data></node>
         <node f="42" dt="4"><name>EditLoc</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
          <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000405dc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
           <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
           <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
          </node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));								
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "y", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
           <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
           <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
           <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "y", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; stringtonum(getviewtext(c)) != toVal)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 1, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = yloc(obj) + data - function_s(sizePanel, "convertCoord", "y", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Spinner</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
          <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040624000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
           <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
          </node>
          <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
          <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
         </data></node>
         <node f="42" dt="4"><name>EditSize</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
          <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/size</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000405dc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
           <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
          </node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>coldlinkx</name><data>if (eventdata)
	function_s(c, "applyUndoable");
else return nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));</data></node>
           <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
           <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
           <node f="442" dt="2"><name>applyUndoable</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = stringtonum(getviewtext(c));
if ((numtostring(get(focus), 0, precision) != getviewtext(c) &amp;&amp; toVal != get(focus)) || param(1) == 1) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	function_s(ownerobject(focus), "setSizeComponent", focus, toVal);
	set(focus, toVal);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Spinner</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
          <node f="42" dt="2"><name>viewfocus</name><data>../../EditSize</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040624000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040488000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
           <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
          </node>
          <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
          <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
         </data></node>
        </node>
        <node f="42" dt="4"><name>Z</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
         <node f="42" dt="2"><name>focus</name><data>../..&gt;variables/Z</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000004061e000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000404e0000</data>
          <node f="40"><name></name></node>
          <node f="42" dt="1"><name>min</name><data>00000000403e0000</data></node>
          <node f="42" dt="1"><name>desired</name><data>00000000404e0000</data></node>
         </node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>alignbottommargin</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
        </data>
         <node f="40"><name></name></node>
         <node f="42" dt="4"><name>Label</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>aligncenterx</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040140000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000402c0000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>00000000402c0000</data></node>
          <node f="42" dt="2"><name>coldlinkname</name><data>../..</data></node>
         </data></node>
         <node f="42" dt="4"><name>EditLoc</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
          <node f="42" dt="2"><name>undohistory</name><data>../../../..</data></node>
          <node f="42" dt="2"><name>focus</name><data>../..&gt;focus+/loc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>00000000405dc000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42"><name>variables</name>
           <node f="40"><name></name></node>
           <node f="42" dt="1"><name>isSampleTarget</name><data>000000003ff00000</data></node>
           <node f="442" dt="2"><name>onSample</name><data>treenode panel = up(up(c));

if(getvarnum(panel, "isDirect"))
	return 1;	

applicationcommand("setcursortext", getvarstr(panel, "cantSampleText"));
return 0;</data></node>
           <node f="42" dt="1"><name>onFocusVal</name><data>0000000000000000</data></node>
          </node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>coldlinkx</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
if(getvarnum(sizePanel, "isDirect"))
	return nodefunction(node("&gt;focus+",c), obj);

if(!eventdata) {
	int precision = get(node("MAIN:/project/environment/settings/precision"));
	setviewtext(c, numtostring(function_s(sizePanel, "convertCoord", "z", obj), 0, precision));
} else
	function_s(c, "applyUndoable");</data></node>
           <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	function_s(c, "applyUndoable", 1);
} </data></node>
           <node f="42" dt="2"><name>OnKillFocus</name><data>function_s(c, "applyUndoable");</data></node>
           <node f="442" dt="2"><name>applyUndoable</name><data>treenode obj = node("../../..&gt;objectfocus+", c);
treenode sizePanel = node("../..", c);
treenode focus = nodefunction(node("&gt;focus+",c), obj);
int precision = get(node("MAIN:/project/environment/settings/precision"));
double toVal = function_s(sizePanel, "convertCoord", "z", obj);
int isChanged = (numtostring(toVal, 0, precision) != getviewtext(c) &amp;&amp; stringtonum(getviewtext(c)) != toVal)
	|| param(1) == 1;
if (isChanged) {
	set(focus, getvarnum(c, "onFocusVal"));
	int undoId = beginaggregatedundo(c, "Modify Object Spatials");
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_UNDO);
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_UNDO);
	double data = stringtonum(getviewtext(c));
	function_s(up(up(c)), "ApplyChangesToSelected", data, 2, 0, c);
	if(!getvarnum(sizePanel, "isDirect"))
		data = zloc(obj) + data - function_s(sizePanel, "convertCoord", "z", obj);
	set(focus, data);
	function_s(ownerobject(focus), "updateResetPosition");
	createundorecord(c, ownerobject(focus), UNDO_UPDATE_LINKS_ON_REDO);
	createundorecord(c, c, UNDO_UPDATE_LINKS_ON_REDO);
	endaggregatedundo(c, undoId);
	repaintall();
}
</data></node>
           <node f="42" dt="2"><name>OnFocus</name><data>treenode focus = nodefunction(node("&gt;focus+",c), node("../../..&gt;objectfocus+", c));
setvarnum(c, "onFocusVal", get(focus));</data></node>
          </node>
         </data>
          <node f="40"><name></name></node></node>
         <node f="42" dt="4"><name>Spinner</name><data>
          <node f="40"><name>object</name></node>
          <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405ec000</data></node>
          <node f="42" dt="2"><name>viewfocus</name><data>../../EditLoc</data></node>
          <node f="42" dt="1"><name>spatialx</name><data>0000000040624000</data></node>
          <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
          <node f="42" dt="1"><name>spatialsx</name><data>0000000040280000</data></node>
          <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
          <node f="42" dt="1"><name>alignrightposition</name><data>0000000040280000</data></node>
          <node f="42" dt="2"><name>tooltip</name><data></data></node>
          <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>step</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>coefficient</name><data>47ae147b3f847ae1</data></node>
          <node f="42" dt="1"><name>exponent</name><data>333333333ff33333</data></node>
          <node f="42"><name>eventfunctions</name>
           <node f="40"><name></name></node>
           <node f="442" dt="2"><name>OnClick</name><data>if (clickcode() == LEFT_PRESS) {
	set(itemcurrent(c),stringtonum(getviewtext(node("&gt;viewfocus+",c))));
	executefsnode(OnFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
if (clickcode() == LEFT_RELEASE) {
	setcursor(1);
	set(node("&gt;editing",c),0);
	executefsnode(OnKillFocus(node("&gt;viewfocus+", c)), node("&gt;viewfocus+", c));
}
</data></node>
           <node f="442" dt="2"><name>OnMouseMove</name><data>if (i) {  // off the spinner
	int y = cursorinfo(c, 6, 2, 0);
	if (get(node("&gt;editing",c))==0) {  // first time falling off the spinner
		setcursor(11);
		set(node("&gt;lastval",c),get(itemcurrent(c)));
		set(node("&gt;lasty",c),y);
		set(node("&gt;editing",c),1);
	}
	
	int monitortop = getsystemmetric(5);
	int monitorbottom = getsystemmetric(6);
	if (y &lt;= monitortop+1) {
		double newy = monitorbottom - 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty",c), newy - y);
		y = newy;
	} else if (y &gt;= monitorbottom-1) {
		double newy = monitortop + 2;
		cursorinfo(0, 7, 2, newy);
		inc(node("&gt;lasty", c), newy - y);
		y = newy;
	}
	int dy = -(y - get(node("&gt;lasty",c)));
	
	double prevvalue = get(node("&gt;lastval",c));
	double newvalue;
	double coefficient = getnodenum(node("&gt;coefficient",c));
	double exponent = getnodenum(node("&gt;exponent",c));
	if (dy &gt; 0)
		newvalue = prevvalue + coefficient*pow(dy,exponent);
	else newvalue = prevvalue - coefficient*pow(-dy,exponent);
	
	if (objectexists(rangemin(c)) &amp;&amp; newvalue&lt;get(rangemin(c)))
		newvalue = get(rangemin(c));
	if (objectexists(rangemax(c)) &amp;&amp; newvalue&gt;get(rangemax(c)))
		newvalue = get(rangemax(c));
	set(itemcurrent(c),newvalue);
	setviewtext(node("&gt;viewfocus+",c), numtostring(newvalue,0,2));
	applylinks(node("&gt;viewfocus+", c));
}
</data></node>
          </node>
          <node f="42" dt="1"><name>editing</name><data>0000000000000000</data></node>
          <node f="42" dt="1"><name>lastval</name><data>47ae147b3fc47ae1</data></node>
          <node f="42" dt="1"><name>lasty</name><data>00000000407c4000</data></node>
         </data></node>
        </node>
       </node>
      </node>
     </node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040448000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStarBarrierProperties</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStarDividerProperties</name><data>
      <node f="40"><name>object</name></node>
      <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040180000</data></node>
      <node f="42" dt="2"><name>guifocusclass</name><data>../../..&gt;variables/QuickPropertiesPanel</data></node>
      <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialsx</name><data>0000000040634000</data></node>
      <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
      <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
     </data>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>DividerProperties</name><data>
       <node f="40"><name>object</name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="2"><name>resizefocus</name><data></data></node>
       <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>GeneralProperties</name><data>VIEW:/active&gt;Tools/GeneralProperties</data></node>
       </node>
       <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
       <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
       <node f="42" dt="1"><name>spatialsx</name><data>000000004066c000</data></node>
       <node f="42" dt="1"><name>spatialsy</name><data>00000000407c1000</data></node>
       <node f="42" dt="2"><name>undohistory</name><data>..&gt;viewfocus+</data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>isExpanded</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>showRequirements</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>selObj</name><data>treenode selObj = param(1);
if (!objectexists(selObj) 
		|| getdatatype(selObj) != DATATYPE_OBJECT)
	return 0;

return isclasstype(selObj, "AStar::Divider");
</data></node>
         <node f="442" dt="2"><name>docType</name><data>string docType = gets(documentwindow(param(1)));
return docType == "3D" || docType == "Tree";</data></node>
        </node>
       </node>
       <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>onSelObjChange</name><data>treenode selObj = param(1);

nodepoint(objectfocus(c), selObj);
if (getvarnum(c, "isExpanded")) {
	applylinks(c, 1);
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}</data></node>
        <node f="442" dt="2"><name>onDocViewClick</name><data>if (getvarnum(c, "isExpanded"))
	applylinks(c, 1);</data></node>
        <node f="442" dt="2"><name>onExpand</name><data>if (param(1)) {// expanded
	applylinks(c, 1);
	
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}
</data></node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data></data></node>
       <node f="42" dt="2"><name>windowtitle</name><data>General Properties</data></node>
      </data>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>EditName</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000405e4000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Set the Object's Name</data></node>
        <node f="442" dt="2"><name>hotlinkx</name><data>treenode focus = node("..&gt;objectfocus+", c);

if (eventdata) {
	if (!comparetext(getviewtext(c), getname(focus))) {
		int undo_id = beginaggregatedundo(c, "Modify Object Name");
			setname(focus, getviewtext(c));
			validatename(c, 1, focus);
			if(getname(focus) != getviewtext(c))
				setname(focus, getviewtext(c));
		endaggregatedundo(c, undo_id);
		applytoedits(node("..&gt;viewfocus+", c), focus);
	}
} else {
	string name = getnodename(focus);
	if (comparetext(name,"NULL"))
		setviewtext(c, "");
	else
		setviewtext(c, name);
}	</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	executefsnode(OnKillFocus(c), c);
} </data></node>
        <node f="42" dt="2"><name>OnKillFocus</name><data>if (!content(c))
	applylinks(c);

//Update flow item name
treenode activeDoc = activedocumentnode();
if (objectexists(activeDoc) &amp;&amp; objectexists(documentwindow(activeDoc))) {
	string docType = gets(documentwindow(activeDoc));
	if (comparetext(docType, "FlowItem Bin"))
		applicationcommand("notifydoclistenersonpropsapply", node("..&gt;objectfocus+", c));
}
</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040440000</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>renameNum</name><data>000000003ff00000</data></node>
         <node f="42" dt="2"><name>renameText</name><data></data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>showRenamePopup</name><data>treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
setvarstr(c, "renameText", getviewtext(c));
if (content(selected)) {
	createpopup("VIEW:/popups/RenameWarning", nodetopath(c, 1), nodetopath(c, 1), c, 0, 0, 260, 55);	
	applylinks(c, 1);
}

</data></node>
         <node f="442" dt="2"><name>renameSelectedObjects</name><data>int renameNum = getvarnum(c, "renameNum");
string name = getvarstr(c, "renameText");

treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
for (int r = 1; r &lt;= content(selected); r++) {
	treenode actualObject = tonode(get(rank(selected, r)));
	string newName = concat(name, numtostring(renameNum));
	setname(actualObject, newName);
	renameNum++;
}
applytoedits(node("..&gt;viewfocus+", c), node("..&gt;objectfocus+", c));
repaintall();</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>RenameAll</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040140000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040180000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040428000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040370000</data></node>
        <node f="42" dt="1"><name>alignrightposition</name><data>0000000040440000</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnPress</name><data>function_s(node("../EditName", c), "showRenamePopup");</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="2"><name>tooltip</name><data>Rename all selected objects</data></node>
        <node f="42" dt="2"><name>bitmap</name><data>buttons\_rename.bmp</data></node>
       </data></node>
       <node f="42" dt="4"><name>Condition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040518000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
       </data></node>
       <node f="42" dt="4"><name>ChooseCondition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405b4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040490000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040140000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Define the condition by which this barrier/path is enabled</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+&gt;variables/conditionRule</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/modules/AStar/GUIClasses/ChooseCondition</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>isHotLink</name><data>000000003ff00000</data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>onApply</name><data>function_s(c.up.up.up.up, "applyChangesToSelected", c.find("&gt;objectfocus+"), c);</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>Two Way</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040538000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
        <node f="42" dt="2"><name>coldlink</name><data>../..&gt;objectfocus+&gt;variables/isTwoWay</data></node>
        <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	treenode focus = c.find("..&gt;objectfocus+");
	windowgray(windowfromnode(c), isclasstype(focus, "AStar::Bridge"));
}</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnPress</name><data>applylinks(c);
treenode focus = node("&gt;coldlink+", c);
function_s(c.up.up.up.up, "applyChangesToSelected", focus, c);</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Tells if the object's rule applies both ways</data></node>
       </data></node>
       <node f="42" dt="4"><name>PointsEdit</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>000000004058c000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>000000004072c000</data></node>
        <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>Points</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040440000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
        </data></node>
        <node f="42" dt="4"><name>Add</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040320000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);
double x = get(node("/x", last(pointsNode)));
double y = get(node("/y", last(pointsNode)));

function_s(barrier, "addPoint", x +2, y +2);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", content(pointsNode) -1);
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
         <node f="42" dt="1"><name>spatialx</name><data>00000000403d0000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040320000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

if (content(node("&gt;viewfocus+", table)) &lt;= 2) {
	msg("Error", "You must have at least 2 points.", 1);
	return 0;
}

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

function_s(barrier, "removePoint", index-1);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index -2);
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
         <node f="42" dt="1"><name>spatialx</name><data>00000000404d0000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040320000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>bitmap</name><data>buttons\uparrow_blue.png</data></node>
         <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;

if (index &lt;= 1)
	return 0;

function_s(barrier, "swapPoints", index -1, index -2);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index -2);
function_s(ownerobject(barrier), "rebuildMeshes");
repaintall();
settableviewselection(table, index -1, 0, index -1, 2);
repaintview(table);</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Move the selected point up in the list</data></node>
        </data></node>
        <node f="42" dt="4"><name>Down</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000004055c000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040320000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>00000000403d0000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>bitmap</name><data>buttons\downarrow_blue.png</data></node>
         <node f="42" dt="2"><name>OnPress</name><data>treenode table = node("../PointsTable", c);
treenode barrier = node("../..&gt;objectfocus+", c);
treenode pointsNode = node("&gt;variables/points", barrier);

int index = gettableviewselection(table,1);

treenode selected = rank(pointsNode, index);
if (!objectexists(selected))
	return 0;
	
if (index == 0 || index &gt;= content(node("&gt;viewfocus+", table)))
	return 0;

function_s(barrier, "swapPoints", index -1, index);
applylinks(table, 1);
refreshview(table);
function_s(barrier, "setActiveIndex", index);
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
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040448000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040710000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>000000004070b000</data></node>
         <node f="42" dt="1"><name>itemcurrent</name><data>0000000000000000</data></node>
         <node f="42" dt="2"><name>hotlinkx</name><data>#define POINT_X 1
#define POINT_Y 2
#define POINT_Z 3

treenode focus = node("../..&gt;objectfocus+", c);
treenode table = node("&gt;table", c);

if (!objectexists(focus))
	return 0;

if (!eventdata) {
	clearcontents(table);
	for (int i = 0; i &lt; content(node("&gt;variables/points", focus)); i++) {
		double x = function_s(focus, "getPointCoord", i, POINT_X);
		double y = function_s(focus, "getPointCoord", i, POINT_Y);
		double z = function_s(focus, "getPointCoord", i, POINT_Z);
		
		treenode parent = nodeinsertinto(table);
		treenode xNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(xNode, x);
		treenode yNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(yNode, y);
		treenode zNode = nodeadddata(nodeinsertinto(parent), DATATYPE_NUMBER);
		set(zNode, z);
	}
	if (content(table) &gt;= 1) {
		setname(rank(first(table), POINT_X), "X");
		setname(rank(first(table), POINT_Y), "Y");
		setname(rank(first(table), POINT_Z), "Z");
	}
} else {
	int rebuildMeshes = 0;
	int haveSetZ = 0; // only get to set z once because it a z change applies to everyone
	for (int i = 0; i &lt; content(node("&gt;variables/points", focus)); i++) {
		double x = function_s(focus, "getPointCoord", i, POINT_X);
		double y = function_s(focus, "getPointCoord", i, POINT_Y);
		double z = function_s(focus, "getPointCoord", i, POINT_Z);
		treenode newpoints = rank(table, i+1);
		double newx = get(newpoints.subnodes[POINT_X]);
		double newy = get(newpoints.subnodes[POINT_Y]);
		double newz = get(newpoints.subnodes[POINT_Z]);
		
		if (x != newx || y != newy) {
			rebuildMeshes = 1;
			function_s(focus, "setPointCoords", i, newx, newy, newz);
		} else if (z != newz &amp;&amp; !haveSetZ) {
			rebuildMeshes = 1;
			haveSetZ = 1;
			function_s(focus, "setPointCoords", i, newx, newy, newz);
		}
	}
	
	if (rebuildMeshes) {
		repaintall();
	}	
}</data></node>
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
		
		function_s(barrier, "setActiveIndex", index - 1);
		repaintall();
	}
}
</data></node>
         <node f="42" dt="2"><name>OnFocus</name><data>if (!objectexists(i) || i != c)
	applylinks(c, 1);</data></node>
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
          <node f="42" dt="1"><name></name><data>00000000404e0000</data></node>
          <node f="42" dt="1"><name></name><data>00000000404e0000</data></node>
          <node f="42" dt="1"><name></name><data>00000000404b8000</data></node>
         </node>
         <node f="42" dt="1"><name>cellheight</name><data>0000000040320000</data>
          <node f="40"><name></name></node></node>
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
       <node f="42" dt="4"><name>PathWeight</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>00000000c0240000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>000000004078f000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
        <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	int isPreferredPath = isclasstype(c.find("..&gt;objectfocus+"), "AStar::PreferredPath");
	windowshow(windowfromnode(c), isPreferredPath);
}</data></node>
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
        <node f="42" dt="4"><name>EditPathWeight</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>000000004055c000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+&gt;variables/pathWeight</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Path Weight</data></node>
         <node f="42" dt="2"><name>OnKillFocus</name><data>applylinks(c);
treenode focus = node("&gt;coldlink+", c);
function_s(c.up.up.up.up.up, "applyChangesToSelected", focus, c);</data></node>
        </data>
         <node f="40"><name></name></node></node>
       </node>
       <node f="42" dt="4"><name>VirtualDistance</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040598000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>00000000401c0000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>000000004078f000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004076c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>beveltype</name><data>0000000000000000</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>alignbottomposition</name><data>00000000403c0000</data></node>
        <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	int isBridge = isclasstype(c.find("..&gt;objectfocus+"), "AStar::Bridge");
	windowshow(windowfromnode(c), isBridge);
}</data></node>
       </data>
        <node f="40"><name></name></node>
        <node f="42" dt="4"><name>Virtual Distance</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>00000000405a4000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000040080000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>000000004057c000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
         <node f="42" dt="2"><name>coldlink</name><data>../../..&gt;objectfocus+&gt;variables/useVirtualDistance</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
         <node f="42"><name>eventfunctions</name>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>OnPress</name><data>applylinks(c);
function_s(c, "grayWindows");
treenode focus = node("&gt;coldlink+", c);
function_s(c.up.up.up.up.up, "applyChangesToSelected", focus, c);</data></node>
          <node f="42" dt="2"><name>coldlinkx</name><data>if (!eventdata) {
	setchecked(c, c.find("&gt;coldlink+")?.value);
	function_s(c, "grayWindows");
}
</data></node>
          <node f="442" dt="2"><name>grayWindows</name><data>int useVirtualDistance = getchecked(c);
forobjecttreeunder(c.find("../EditVirtualDistance")) {
	windowgray(windowfromnode(a), !useVirtualDistance);
}
</data></node>
         </node>
         <node f="42" dt="2"><name>tooltip</name><data>Use a virtual distance instead of the actual bridge distance.</data></node>
        </data></node>
        <node f="42" dt="4"><name>EditVirtualDistance</name><data>
         <node f="40"><name>object</name></node>
         <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
         <node f="42" dt="1"><name>spatialx</name><data>00000000405b8000</data></node>
         <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>spatialsx</name><data>0000000040590000</data></node>
         <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
         <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040350000</data></node>
         <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
         <node f="42" dt="2"><name>objectfocus</name><data>../../..&gt;objectfocus+&gt;variables/virtualDistance</data></node>
         <node f="42" dt="2"><name>undohistory</name><data>../../..</data></node>
         <node f="42" dt="2"><name>tooltip</name><data>Virtual Distance</data></node>
         <node f="42"><name>variables</name>
          <node f="40"><name></name></node>
          <node f="42" dt="2"><name>valueType</name><data>length</data></node>
          <node f="42" dt="1"><name>isHotlink</name><data>000000003ff00000</data></node>
         </node>
         <node f="42"><name>eventfunctions</name>
          <node f="40"><name></name></node>
          <node f="442" dt="2"><name>onApply</name><data>treenode focus = node("&gt;objectfocus+", c);
function_s(c.up.up.up.up.up, "applyChangesToSelected", focus, c);</data></node>
         </node>
        </data>
         <node f="40"><name></name></node></node>
       </node>
      </node>
     </node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040450000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStarDividerProperties</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStarGridProperties</name><data>
      <node f="40"><name>object</name></node>
      <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040180000</data></node>
      <node f="42" dt="2"><name>guifocusclass</name><data>../../..&gt;variables/QuickPropertiesPanel</data></node>
      <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialy</name><data>0000000000000000</data></node>
      <node f="42" dt="1"><name>spatialsx</name><data>0000000040634000</data></node>
      <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
      <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
     </data>
      <node f="40"><name></name></node>
      <node f="42" dt="4"><name>GridProperties</name><data>
       <node f="40"><name>object</name></node>
       <node f="42" dt="3"><name>objectfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="3"><name>viewfocus</name><data><coupling>null</coupling></data></node>
       <node f="42" dt="2"><name>resizefocus</name><data></data></node>
       <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040100000</data>
        <node f="40"><name></name></node>
        <node f="42" dt="2"><name>GeneralProperties</name><data>VIEW:/active&gt;Tools/GeneralProperties</data></node>
       </node>
       <node f="42" dt="1"><name>spatialx</name><data>0000000000000000</data></node>
       <node f="42" dt="1"><name>spatialy</name><data>0000000040350000</data></node>
       <node f="42" dt="1"><name>spatialsx</name><data>000000004066c000</data></node>
       <node f="42" dt="1"><name>spatialsy</name><data>000000004061c000</data></node>
       <node f="42" dt="2"><name>undohistory</name><data>..&gt;viewfocus+</data></node>
       <node f="42"><name>variables</name>
        <node f="40"><name></name></node>
        <node f="42" dt="1"><name>isExpanded</name><data>000000003ff00000</data></node>
        <node f="42" dt="1"><name>showRequirements</name><data>0000000000000000</data>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>selObj</name><data>treenode selObj = param(1);
if (!objectexists(selObj) || getdatatype(selObj) != DATATYPE_SIMPLE)
	return 0;

return isclasstype(selObj, "AStar::Grid");
</data></node>
         <node f="442" dt="2"><name>docType</name><data>string docType = gets(documentwindow(param(1)));
return docType == "3D" || docType == "Tree";</data></node>
        </node>
       </node>
       <node f="42" dt="1"><name>alignrightmargin</name><data>0000000000000000</data></node>
       <node f="42"><name>eventfunctions</name>
        <node f="40"><name></name></node>
        <node f="442" dt="2"><name>onSelObjChange</name><data>treenode selObj = param(1);

nodepoint(objectfocus(c), selObj);
if (getvarnum(c, "isExpanded")) {
	applylinks(c, 1);
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}</data></node>
        <node f="442" dt="2"><name>onDocViewClick</name><data>if (getvarnum(c, "isExpanded"))
	applylinks(c, 1);</data></node>
        <node f="442" dt="2"><name>onExpand</name><data>if (param(1)) {// expanded
	applylinks(c, 1);
	
	if (content(node("../../SelectedList/SelectedPanel/selectedList&gt;items", c))) {
		windowgray(windowfromnode(node("RenameAll", c)), 0);
	} else {
		windowgray(windowfromnode(node("RenameAll", c)), 1);
	}
}
</data></node>
       </node>
       <node f="42" dt="2"><name>tooltip</name><data></data></node>
       <node f="42" dt="2"><name>windowtitle</name><data>A* Grid Properties</data></node>
      </data>
       <node f="40"><name></name></node>
       <node f="42" dt="4"><name>EditName</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>00000000401c0000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000405e4000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Set the Object's Name</data></node>
        <node f="442" dt="2"><name>hotlinkx</name><data>treenode focus = node("..&gt;objectfocus+", c);

if (eventdata) {
	if (!comparetext(getviewtext(c), getname(focus))) {
		int undo_id = beginaggregatedundo(c, "Modify Object Name");
			setname(focus, getviewtext(c));
			validatename(c, 1, focus);
			if(getname(focus) != getviewtext(c))
				setname(focus, getviewtext(c));
		endaggregatedundo(c, undo_id);
		applytoedits(node("..&gt;viewfocus+", c), focus);
	}
} else {
	string name = getnodename(focus);
	if (comparetext(name,"NULL"))
		setviewtext(c, "");
	else
		setviewtext(c, name);
}	</data></node>
        <node f="42" dt="2"><name>undohistory</name><data>../..</data></node>
        <node f="42" dt="2"><name>OnKeyUp</name><data>int k = lastkeyup();

if (k==13) {  // enter
	executefsnode(OnKillFocus(c), c);
} </data></node>
        <node f="42" dt="2"><name>OnKillFocus</name><data>if (!content(c))
	applylinks(c);

//Update flow item name
treenode activeDoc = activedocumentnode();
if (objectexists(activeDoc) &amp;&amp; objectexists(documentwindow(activeDoc))) {
	string docType = gets(documentwindow(activeDoc));
	if (comparetext(docType, "FlowItem Bin"))
		applicationcommand("notifydoclistenersonpropsapply", node("..&gt;objectfocus+", c));
}
</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040240000</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="1"><name>renameNum</name><data>000000003ff00000</data></node>
         <node f="42" dt="2"><name>renameText</name><data></data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>showRenamePopup</name><data>treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
setvarstr(c, "renameText", getviewtext(c));
if (content(selected)) {
	createpopup("VIEW:/popups/RenameWarning", nodetopath(c, 1), nodetopath(c, 1), c, 0, 0, 260, 55);	
	applylinks(c, 1);
}

</data></node>
         <node f="442" dt="2"><name>renameSelectedObjects</name><data>int renameNum = getvarnum(c, "renameNum");
string name = getvarstr(c, "renameText");

treenode selected = node("/SelectedList/SelectedPanel/selectedList&gt;items", up(up(up(c))));
for (int r = 1; r &lt;= content(selected); r++) {
	treenode actualObject = tonode(get(rank(selected, r)));
	string newName = concat(name, numtostring(renameNum));
	setname(actualObject, newName);
	renameNum++;
}
applytoedits(node("..&gt;viewfocus+", c), node("..&gt;objectfocus+", c));
repaintall();</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>Node Spacing</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040418000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000405e0000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
       </data></node>
       <node f="42" dt="4"><name>EditNodeSpacing</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040490000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040418000</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+/nodeWidth</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Enter the spacing between nodes in the A* search grid.</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>valueType</name><data>length</data></node>
         <node f="42" dt="1"><name>spinner</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>isHotlink</name><data>000000003ff00000</data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>onApply</name><data>function_s(c.find("..&gt;objectfocus+"), "makeDirty");</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>Z Position</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040538000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>00000000405e0000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>00000000402e0000</data></node>
       </data></node>
       <node f="42" dt="4"><name>EditZPosition</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowopen</name><data>0000000000000000</data></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040594000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>0000000040574000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>000000004059c000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040418000</data></node>
        <node f="42" dt="2"><name>guifocusclass</name><data>VIEW:/guiclasses/UnitValueEdit</data></node>
        <node f="42" dt="2"><name>objectfocus</name><data>../..&gt;objectfocus+/minPointZ</data></node>
        <node f="42" dt="2"><name>tooltip</name><data>Enter the Z position of the grid</data></node>
        <node f="42"><name>variables</name>
         <node f="40"><name></name></node>
         <node f="42" dt="2"><name>valueType</name><data>length</data></node>
         <node f="42" dt="1"><name>spinner</name><data>0000000000000000</data></node>
         <node f="42" dt="1"><name>isHotlink</name><data>000000003ff00000</data></node>
        </node>
        <node f="42"><name>eventfunctions</name>
         <node f="40"><name></name></node>
         <node f="442" dt="2"><name>onApply</name><data>function_s(c.find("..&gt;objectfocus+"), "makeDirty");</data></node>
        </node>
       </data>
        <node f="40"><name></name></node></node>
       <node f="42" dt="4"><name>SetGridZ</name><data>
        <node f="40"><name>object</name></node>
        <node f="42" dt="1"><name>viewwindowtype</name><data>0000000040590000</data></node>
        <node f="42" dt="1"><name>spatialx</name><data>0000000040080000</data></node>
        <node f="42" dt="1"><name>spatialy</name><data>00000000405d4000</data></node>
        <node f="42" dt="1"><name>spatialsx</name><data>0000000040350000</data></node>
        <node f="42" dt="1"><name>spatialsy</name><data>0000000040350000</data></node>
        <node f="42" dt="2"><name>windowtitle</name><data>Set View Grid Z</data></node>
        <node f="42" dt="2"><name>OnPress</name><data>treenode activedoc = activedocumentnode();

if (get(viewwindowtype(activedoc)) != 2)
	return 0;

double zpos = get(node("../EditZPosition&gt;objectfocus+", c));
set(first(gridplane(activedoc)), zpos);
set(viewpointz(activedoc), zpos);
repaintall();</data>
         <node f="40"><name></name></node></node>
        <node f="42" dt="2"><name>tooltip</name><data>Set the current Grid Z of the 3D view to this position</data></node>
        <node f="42" dt="1"><name>alignrightmargin</name><data>0000000040418000</data></node>
       </data></node>
      </node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/QuickProperties&gt;variables/propertiesPanels/GeneralProperties/GeneralProperties&gt;variables/ignoreClasses</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040140000</data></node>
    <node f="42" dt="2"><name>after</name><data>AGV::ControlArea</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::AStarNavigator</name></node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040180000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStar::AStarNavigator</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::Barrier</name></node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000401c0000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStar::Barrier</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::Divider</name></node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040200000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStar::Divider</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::PreferredPath</name></node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040220000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStar::PreferredPath</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::Bridge</name></node>
    </node>
   </node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040240000</data></node>
    <node f="42" dt="2"><name>after</name><data>AStar::Bridge</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::MandatoryPath</name></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/QuickProperties&gt;variables/propertiesPanels/Labels/Labels&gt;variables/ignoreClasses</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>000000003ff00000</data></node>
    <node f="42"><name>after</name></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::AStarNavigator</name></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/QuickProperties&gt;variables/propertiesPanels/Statistics/Statistics&gt;variables/ignoreClasses</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>000000003ff00000</data></node>
    <node f="42"><name>after</name></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42"><name>AStar::AStarNavigator</name></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/events/OnUpdateModel/Update to 19.0</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>000000003ff00000</data></node>
    <node f="42"><name>after</name></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="442" dt="2"><name>update AStarNavigator structure</name><data>treenode updaterootnode = param(1);
double oldVersion = param(2);

if (oldVersion &gt;= 19.0)
	return 0;

if (updaterootnode != model())
	return 0;

Object navigator = Model.find("AStarNavigator");
if (!navigator)
	return 0;

treenode astarFolder = Model.find("MAIN:/project/library/astar");
Object libNavigator = astarFolder.find("AStarNavigator");
Object surrogate = createcopy(libNavigator.find("&gt;visual/drawsurrogate"), navigator.find("&gt;visual"), 1).first;
surrogate.size = Vec3(1.0, 1.0, 1.0);
navigator.attrs.shape.value = "***";
navigator.attrs.shapeindex.value = 0;
navigator.attrs.guifocusclass.value = "VIEW:/modules/AStar/Pages/AStarProperties";
navigator.find("&gt;variables/grids/1/nodeWidth").value = getvarnum(navigator, "nodeWidth");
clearcontents(navigator.attrs.variables.find("resetposition"));
switch_hidecontents(navigator, 0);
createcopy(libNavigator.attrs.imageindexobject, navigator.attrs.imageindexobject, 1, 0, 0, 1);
createcopy(libNavigator.attrs.imageobject, navigator.attrs.imageobject, 1, 0, 0, 1);
rebindobjectattributes(navigator);

treenode barriers = getvarnode(navigator, "barriers");
Array newObjects;
for (int i = 1; i &lt;= barriers.subnodes.length; i++) {
	treenode barrier = barriers.subnodes[i];
	string class = barrier.find("sdt::attributetree")?.value;
	Object newObj = 0;
	if (class == "AStar::Barrier") {
		newObj = createinstance(astarFolder.find("Barrier"), navigator);
	} else if (class == "AStar::Divider") {
		newObj = createinstance(astarFolder.find("Divider"), navigator);
		newObj.attrs.variables.find("isTwoWay").value = 1;
	} else if (class == "AStar::OneWayDivider") {
		newObj = createinstance(astarFolder.find("Divider"), navigator);
		newObj.attrs.variables.find("isTwoWay").value = 0;
	} else if (class == "AStar::PreferredPath") {
		newObj = createinstance(astarFolder.find("PreferredPath"), navigator);
		newObj.attrs.variables.find("pathWeight").value 
			= barrier.find("/sdt::attributetree/pathWeight")?.value;
	} else if (class == "AStar::Bridge") {
		newObj = createinstance(astarFolder.find("Bridge"), navigator);
		newObj.attrs.variables.find("useVirtualDistance").value 
			= barrier.find("useVirtualDistance")?.value;
		newObj.attrs.variables.find("virtualDistance").value 
			= barrier.find("virtualDistance")?.value;
	} else if (class == "AStar::MandatoryPath") {
		newObj = createinstance(astarFolder.find("MandatoryPath"), navigator);
	}
	if (newObj) {
		newObjects.push(newObj);
		newObj.location = Vec3(0.0, 0.0, 0.0);
		treenode fromPoints = barrier.find("points");
		treenode toPoints = newObj.attrs.variables.find("points");
		toPoints.subnodes.clear();
		while (fromPoints.subnodes.length &gt; 0) {
			if (class != "AStar::Bridge")
				fromPoints.first.find("z").value = 0;
			fromPoints.first.up = toPoints;
		}
			
		function_s(newObj, "updateSpatialsToEncompassPoints");
	}
}

barriers.subnodes.clear();
for (int i = 1; i &lt;= newObjects.length; i++)
	function_s(newObjects[i], "assertNavigator");

updatelocations(navigator);

return 1;
</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/exec/globals/sdtinterfaces</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040180000</data></node>
    <node f="42" dt="2"><name>after</name><data>Task</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="2"><name>AStar::Traveler</name><data>AStar.Traveler</data>
      <node f="40"><name></name></node>
      <node f="42" dt="1"><name>isCoupling</name><data>000000003ff00000</data></node>
     </node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>MAIN:/project/events/OnUpdateModel/Update to 19.1</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>0000000040100000</data></node>
    <node f="42" dt="2"><name>after</name><data>update milestone collectors</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="442" dt="2"><name>update astar conditional barriers</name><data>treenode updaterootnode = param(1);
double oldVersion = param(2);

if (oldVersion &gt;= 19.1)
	return 0;
	
int updated = 0;
treenode conditions = Model.find("AStarNavigator&gt;variables/barrierConditions");
forobjecttreeunder(updaterootnode) {
	if (isclasstype(a, "AStar::Barrier") &amp;&amp; getvarnum(a, "useCondition") != 0) {
		updated = 1;
		int foundMatch = 0;
		treenode condition = getvarnode(a, "condition");
		string value = gets(condition);
		for (int i = 1; i &lt;= conditions.subnodes.length; i++) {
			if (value == gets(conditions.subnodes[i])) {
				foundMatch = 1;
				nodepoint(getvarnode(a, "conditionRule"), conditions.subnodes[i]);
				break;
			}
		}
		if (!foundMatch) {
			treenode newCondition = createcopy(condition, conditions);
			newCondition.name = "Rule " + string.fromNum(conditions.subnodes.length);
			nodepoint(getvarnode(a, "conditionRule"), newCondition);
		}
	}
}

return updated;</data></node>
    </node>
   </node>
  </node>
  <node f="42" dt="2"><name>add</name><data>VIEW:/standardviews/modelingutilities/Toolbox&gt;variables/tools</data>
   <node f="40"><name></name></node>
   <node f="42" dt="3"><name></name><data><coupling>null</coupling></data>
    <node f="40"><name></name></node>
    <node f="42" dt="1"><name>rank</name><data>00000000403e0000</data></node>
    <node f="42" dt="2"><name>after</name><data>AGVNetwork</data></node>
    <node f="42" dt="1"><name>into object</name><data>0000000000000000</data></node>
    <node f="42"><name>data</name>
     <node f="40"><name></name></node>
     <node f="42" dt="4"><name>AStarNavigator</name><data>
      <node f="40"><name></name></node>
      <node f="42" dt="2"><name>objectfocus</name><data>MODEL:/AStarNavigator</data></node>
      <node f="42" dt="2"><name>bitmap</name><data>modules\AStar\bitmaps\astarnavigatorsmaller.png</data></node>
      <node f="42"><name>variables</name>
       <node f="40"><name></name></node>
       <node f="42" dt="2"><name>toolType</name><data>Singleton</data></node>
       <node f="42" dt="1"><name>hasCustomDelete</name><data>000000003ff00000</data></node>
      </node>
      <node f="42"><name>eventfunctions</name>
       <node f="40"><name></name></node>
       <node f="442" dt="2"><name>onDoubleClick</name><data>createview("VIEW:/modules/AStar/Pages/AStarProperties", "MODEL:/AStarNavigator", "MODEL:/AStarNavigator");</data></node>
       <node f="442" dt="2"><name>onDelete</name><data>if (msg("Delete AStarNavigator?", "Delete AStarNavigator?", 0))
{
	destroyobject(node("MODEL:/AStarNavigator"));
	repaintall();
}
</data></node>
      </node>
      <node f="42" dt="2"><name>windowtitle</name><data>A* Navigator</data></node>
     </data>
      <node f="40"><name></name></node></node>
    </node>
   </node>
  </node>
 </node>
 <node f="42" dt="2"><name>release</name><data>19.2</data></node>
 <node f="42" dt="2"><name>revision</name><data>.0</data></node>
 <node f="42" dt="2"><name>flexsim release</name><data>19.2</data></node>
</node></flexsim-tree>
