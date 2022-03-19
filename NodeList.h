#ifndef COSC_ASS_ONE_NODE_LIST
#define COSC_ASS_ONE_NODE_LIST

#include "Node.h"
#include "Types.h"

class NodeList {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */
   
   // Create a New Empty List
   NodeList();

   // Clean-up the list
   ~NodeList();

   // Copy Constructor
   // Produces a DEEP COPY of the NodeList
   NodeList(NodeList& other);

   // Number of items in the list
   int getLength();

   // Get a pointer to the ith node in the node list
   NodePtr get(int i);

   // Add a COPY node element to the BACK of the nodelist
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance 
   //    is removed from the list
   void addBack(NodePtr newNode);

   // Checks if the list contains a node with the same co-ordinate
   //    as the given node.
   bool containsNode(NodePtr node);

   // Remove everything from the list
   // Don't forget to clean-up the memory!
   void clear();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   /*
    * For Milestone 3, rather than adding Nodes from nodes[0] to nodes[x] where x is 'G's distance from 'S' and sorting it in reverse order,
    * straight from the beginning add goalNode at the right index and subsequent nodes until startNode is added at nodes[0]
    */
   void addAt(int i, NodePtr newNode);

   /* This is a suggestion of what you could use. */
   /* You can change this code.                   */
private:

   // NodeList: list of node objects
   // You may assume a fixed size for M1, M2, M3
   NodePtr nodes[NODE_LIST_ARRAY_MAX_SIZE];
   // Number of nodes currently in the NodeList
   int length;


};
typedef NodeList* NodeListPtr;
#endif // COSC_ASS_ONE_NODE_LIST
