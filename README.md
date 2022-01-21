# A* Module

This repository contains all of the code and tree data that is used in building and distributing 
FlexSim's A* module. We provide it to our users as an example of how to define a fully functional 
module that integrates into the FlexSim application.

The A* module's core compoment is the well-known A* path finding algorithm. In FlexSim, users can 
create A* grids, and then define barriers within those grids. When TaskExecuters are assigned to 
use the A* navigator for travel, they will find the shortest route that avoids the user-defined 
barriers to get to their desired destinations.

The A* module includes implementations of objects like:
* Block barriers
* Dividers
* Preferred Paths
* Mandatory Paths
* Pattern-based Barriers
* Bridges (direct connections between different points in the grid)
* Elevator Bridges (used by the people module to implement elevators between A* grids)

## Using the A* module

To start using the A* module, clone the repository and checkout the branch that corresponds to the 
version of FlexSim you are working against (e.g. 21.0, 22.0, 22.1, etc.). Then [create a development folder](https://docs.flexsim.com/en/22.0/Reference/DeveloperAdvancedUser/ModuleSDK/QuickStart/) for 
FlexSim, and replace the 
FlexSim\modules\AStar folder from the installed version with your cloned repository.

As of FlexSim version 22.0, the FlexSim development group uses Visual Studio 2019 Professional for 
our development. You should be able to use either Visual Studio 2019, or Visual Studio 2022, and 
either the Professional or Community version, although 
we have not tested it extensively against differing versions. We would suggest not upgrading the 
Platform Toolset when you open the project in Visual Studio 2022, although it may work either way.

Once you have installed the desired Visual Studio version, open the solution found at 
AStarDLL/AStar.sln in the repository. Then go to Build > Build Solution. This should build the 
A* dll such that next time you open FlexSim, your custom-built A* dll will be loaded.

For more information on module development, see [Module SDK](https://docs.flexsim.com/en/22.0/Reference/DeveloperAdvancedUser/ModuleSDK/KeyConcepts/) in the user manual.
