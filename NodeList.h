#ifndef COSC_ASS_ONE_NODE_LIST
#define COSC_ASS_ONE_NODE_LIST

#include "Node.h"
#include "Types.h"
#include <string>

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
    * For Milestone 4, another constructor that takes the length of nodes is needed
    */
   NodeList(int max_length);

   /*
    * For Milestone 4, getMaxLength method is needed
    */
   int getMaxLength();

   /*
    * For Milestone 3, rather than adding Nodes from nodes[0] to nodes[x] where x is 'G's distance from 'S' and sorting it in reverse order,
    * straight from the beginning add goalNode at the right index and subsequent nodes until startNode is added at nodes[0]
    */
   void addPathNode(NodePtr newNode);

   /*
    * Return nodes in the format below
    * (x1,y1,distance1)(x2,y2,distance2)(x3,y3,distance3)...(xi,yi,distancei)
    */
   std::string stringify();

private:
    Node** nodes;
    // Number of nodes currently in the NodeList
    int length;
    int max_length;



};
typedef NodeList* NodeListPtr;
#endif // COSC_ASS_ONE_NODE_LIST
