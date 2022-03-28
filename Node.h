
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"

class Node {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // get row-co-ordinate
   int getRow();

   // get Column-co-ordinate
   int getCol();

   // getters and setters for distance to source
   int getDistanceToS();
   void setDistanceToS(int distanceToS);

   void setRow(int);
   void setCol(int);
   bool equals(Node &);
   // Checks whether this Node is traversable from other Node
   bool isTraversable(Node &other);
   // Returns Up, Right, Down, or Left, depending on where this Node is relative to other Node
   Direction getDirectionTo(Node &other);
   
   // Constructor/Destructor
   Node();
   Node(int row, int col, int distanceToS);
   Node(Node& other);
   ~Node();
    
private:
    int row;
    int col;
    int distanceToS;
};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef Node* NodePtr;

#endif // COSC_ASS_ONE_NODE
