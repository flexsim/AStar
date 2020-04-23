#pragma once

namespace AStar {
class AStarNavigator;
class Point;
class Barrier;
class Divider;
class OneWayDivider;
class PreferredPath;
class Bridge;
class MandatoryPath;
class Traveler;
class TravelerBridgeData;
struct AStarPathEntry;
class Grid;
class TemporaryBarrier;
class AStarNode;
struct AStarNodeExtraData;
class BridgeRoutingData;
class ElevatorBridgeRoutingData;
class ElevatorBridge;
#ifdef COMPILING_ASTAR
#define astar_export __declspec(dllexport)
#else
#define astar_export __declspec(dllimport)
#endif

}
