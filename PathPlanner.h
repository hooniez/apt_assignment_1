
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"
#include <string>

#define NUM_ADJACENT_CELLS 4
#define NUM_POINTS 2

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MODIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all nodes
   // that the robot can reach with distances
   NodeList* getReachableNodes();

   // Method for Milestone 3
   // Get the path from the startNode to goalNode.
   NodeList* getPath();

   void goalPosition(int row, int col);

   // Sub-functions that make up getReachableNodes()
   bool isReachable(int row, int col);
   void addToOpenList();
   void addToClosedList();
   bool isPointerNodeAssigned();

   // functions created for testing purposes
   NodeListPtr getOpenList();
   NodeListPtr getClosedList();

   // Created for testDeepCopyClosedList()
   NodePtr getGoalNode();

private:
    Env env;
    int rows;
    int cols;
    int nodeListMaxLength;
    NodePtr startNode;
    NodeListPtr openList;
    NodeListPtr closedList;
    NodeListPtr pathList;
    NodePtr pointerNode;
    NodePtr goalNode;
    // The order in which to add new nodes: Up, Right, Down, Left
    static constexpr int searchingOrder[NUM_ADJACENT_CELLS][NUM_POINTS] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
};

#endif // COSC_ASS_ONE_PATH_PLANNING
