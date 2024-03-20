
/* FOLLOWING CODE IS ONE OF THE IMPLEMENTATION OF RED BLACK TREE IN THE FORM OF TASK MANAGEMENT SYSTEM*/

#include <iostream>
#include <sstream> 
#include <string>
using namespace std;

int counter = 1;
class Assignee
{
private:
public:
    string firstname;
    string secondname;
    string address;
    string DOB;
    string ID;

    // Constructor For Assignee
    Assignee(const string& first, const string& second, const string& address1, const string& dob)
    {

        this->firstname = first;
        this->secondname = second;
        this->address = address1;
        this->DOB = dob;
    }

    string getID() { return ID; }
};
// int Assignee ::counter = 1;


//------------------   ASSIGNEE TREE NODE

struct NodeAssignee
{
    int data;
    // Three pointers
    NodeAssignee* up_parent;
    NodeAssignee* left;
    NodeAssignee* right;

    // 0 for black and 1 will be for red
    int color;
    string firstname;
    string secondname;
    string address;
    string DOB;

    int ID; // for last index of Assignee ID

    string ID2; // Assignee ID

    bool task;
};
//-----------------   TASK TREE NODE
struct NodeTask
{
    int data;
    NodeTask* up_parent;
    NodeTask* left;
    NodeTask* right;
    int color;
    int TaskId;
    string description;
    int prioritylev;
    string AssigneeID;

    // Boolen for the task completion
    bool complete;

};


//----------------   Assignee TREE 
class AssigneeTree
{
private:


    void inorder2helper(stringstream& outp, NodeAssignee* node)
    {
        if (node != randomMemory)
        {
            inorder2helper(outp, node->left);
            outp << "Name: " << node->firstname << " " << node->secondname << ", Address: " << node->address << ", DOB: " << node->DOB << ", Assignee ID: " << node->ID2 << endl;

            inorder2helper(outp, node->right);
        }
    }
    void inorder22helper(stringstream& outp, NodeAssignee* node)
    {
        if (node != randomMemory)
        {
            inorder22helper(outp, node->left);
            outp << node->ID2 << " (" << (node->color == 1 ? "red" : "black") << ")\n";
            inorder22helper(outp, node->right);
        }
    }

    void fixingdeletion(NodeAssignee* uptr, NodeAssignee* temp1ptr)
    {
        if (uptr->up_parent == NULL)
        {
            root = temp1ptr;
        }
        else if (uptr == uptr->up_parent->left)
        {
         //   up->parent = up->right;

            uptr->up_parent->left = temp1ptr;
        }
        else
        {

            uptr->up_parent->right = temp1ptr;
        }
      
        temp1ptr->up_parent = uptr->up_parent;   // setting parent of uptr to temp1 ptr
    }
    string searchTreeHelper(NodeAssignee* node, int key, stringstream& outp)
    {
        if (node != randomMemory) {
            if (key == node->ID)
            {

                outp << "Name: " << node->firstname << " " << node->secondname << ", Address: " << node->address << ", DOB: " << node->DOB << ", Assignee ID: " << node->ID2 << endl;
                return node->address;
            }

            if (key < node->ID)
            {
                return searchTreeHelper(node->left, key, outp);
            }

            return searchTreeHelper(node->right, key, outp);
        }

    }

    void finding(string idd, string id2, NodeTask* node1)
    {
        if (node1->left != NULL || node1->right != NULL)
        {
            finding(idd, id2, node1->left);
            if (node1->AssigneeID == idd)
            {
                node1->AssigneeID = id2;
            }
            finding(idd, id2, node1->right);
        }
    }

    void shifthelper(NodeAssignee* obj, int id1, NodeTask* nodee, string id2)
    {
        if (obj != randomMemory)
        {
            shifthelper(obj->left, id1, nodee, id2);
            if (id1 == obj->ID)
            {
                string idd;
                obj->task = false;
                if (id1 < 10)
                {
                    idd = "A00";
                    idd += to_string(id1);
                }
                else if (id1 >= 10 && id1 < 100)
                {
                    idd = "A0";
                    idd += to_string(id1);
                }
                else
                {
                    idd = "A";
                    idd += to_string(id1);
                }
                finding(idd, id2, nodee);
            }
           
            shifthelper(obj->right, id1, nodee, id2);
        }
    }

    // For balancing the tree after deletion
    void deleteionfixing_Node(NodeAssignee* node_to_fix)
    {
        NodeAssignee* tempptr;

        // Fixing the red-black tree properties
        for (; node_to_fix != root && node_to_fix->color == 0; ) 
        {
            if (node_to_fix != node_to_fix->up_parent->left) 
            {
                
                tempptr = node_to_fix->up_parent->left; // Handling the case when node_to_fix is not a left child

                
                if (tempptr->color == 1)  // Case:   Fixing a   red-red violation with a right rotation    
                {  
                
                    tempptr->color = 0;

                    node_to_fix->up_parent->color = 1;

                    // Right rotate the nodes to resolve the violation
                    rightRotationAssignee(node_to_fix->up_parent);

                   
                    tempptr = node_to_fix->up_parent->left;  // After rotation, setting tempptr to the fixed node
                }

               
                if (tempptr->right->color == 0 && tempptr->left->color == 0)   // case of : If both children of tempptr are black
                {
                    // Fixing color and moving up the tree
                    tempptr->color = 1;
                    node_to_fix = node_to_fix->up_parent;
                }
                else {
                    // Handling the case when left child of tempptr is black
                    if (tempptr->left->color == 0) 
                    {

                        tempptr->right->color = 0;
                        tempptr->color = 1;
                       leftRotationAssignee(tempptr);

                        tempptr = node_to_fix->up_parent->left;
                    }

                    // Adjusting colors and performing a right rotation
                    tempptr->color = node_to_fix->up_parent->color;
                    node_to_fix->up_parent->color = 0;
                    tempptr->left->color = 0;



                    rightRotationAssignee(node_to_fix->up_parent);
                    node_to_fix = root;
                }
            }
            else
            {
                // Handling the case when node_to_fix is a left child
                tempptr = node_to_fix->up_parent->right;

                // Case: Fixing a red-red violation with a left rotation
                if (tempptr->color == 1) {
                    tempptr->color = 0;


                    node_to_fix->up_parent->color = 1;


                    leftRotationAssignee(node_to_fix->up_parent);
//                    tempptr->color = 1;

                    tempptr = node_to_fix->up_parent->right;
                }

                // If both children of tempptr are black
                if (tempptr->left->color == 0 && tempptr->right->color == 0) {
                    // Fixing color and moving up the tree
                    tempptr->color = 1;
                    node_to_fix = node_to_fix->up_parent;
                }
                else 
                {
                    // Handling the case when right child of tempptr is black
                    if (tempptr->right->color == 0) {
                        tempptr->left->color = 0;


                        //tempptr->color = 1;

                        tempptr->color = 1;

                        rightRotationAssignee(tempptr);

                        tempptr = node_to_fix->up_parent->right;
                    }

                    // Adjusting colors and performing a left rotation
                    tempptr->color = node_to_fix->up_parent->color;


                    node_to_fix->up_parent->color = 0;


                    tempptr->right->color = 0;

                    leftRotationAssignee(node_to_fix->up_parent);
                    node_to_fix = root;
                }
            }
        }

        // Set the color of the root to black after fixing the tree
        node_to_fix->color = 0;


    }


    NodeAssignee* gettingpredecesoor(NodeAssignee* x)
    {
        NodeAssignee* y = x->left;
        while (y->right != randomMemory)
        {
            y = y->right;
        }
        return y;
    }
    void Helping_delete_node(NodeAssignee* node, int key)
    {
        NodeAssignee* temp1 = randomMemory;
        NodeAssignee* x1;
        NodeAssignee* y1;
        while (node != randomMemory)
        {
            //tempptr->color = 1;
            if (node->ID == key)
            {
                temp1 = node;
            }

            if (node->ID <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (!temp1->task)
        {
            y1 = temp1;
            int temp_color = y1->color;

            if (temp1->left == randomMemory)
            {
                x1 = temp1->right;
                fixingdeletion(temp1, temp1->right);
            }
            else if (temp1->right == randomMemory)
            {


                x1 = temp1->left;
                fixingdeletion(temp1, temp1->left);


            }
            else
            {
                // In testcases taking predecssor so here taking predecssor
                y1 = gettingpredecesoor(temp1);



                temp_color = y1->color;
                x1 = y1->left;

                if (y1->up_parent == temp1)
                {
                    x1->up_parent = y1;
                }
                else
                {

                    fixingdeletion(y1, y1->left);
                    y1->left = temp1->left;
                    y1->left->up_parent = y1;
                }

                fixingdeletion(temp1, y1);


                y1->right = temp1->right;
                y1->right->up_parent = y1;

                y1->color = temp1->color;


            }
            delete temp1;
            if (temp_color == 0)
            {
                deleteionfixing_Node(x1);
            }
        }
    }

    // For balancing the tree after inserting_treeion
    void inserting_treeSet_NODE(NodeAssignee* kptr)
    {
        NodeAssignee* ptr1;
        while (kptr->up_parent->color == 1)
        {
            // RR or RL case
            if (kptr->up_parent == kptr->up_parent->up_parent->right)
            {

                ptr1 = kptr->up_parent->up_parent->left;
                if (ptr1->color == 1)
                {
                    ptr1->color = 0;
                    kptr->up_parent->color = 0;

                    kptr->up_parent->up_parent->color = 1;

                   
                    kptr = kptr->up_parent->up_parent; // setting parent
                }
                else
                {

                    if (kptr == kptr->up_parent->left)
                    {
                        kptr = kptr->up_parent;

                        // right rotate case
                        rightRotationAssignee(kptr);
                        //   kptr->parent = kptr->right;
                    }
                    kptr->up_parent->color = 0;
                    kptr->up_parent->up_parent->color = 1;

                    //k->ptr->up =0
                    leftRotationAssignee(kptr->up_parent->up_parent);
                }
            }
            else
            {
                ptr1 = kptr->up_parent->up_parent->right;

                if (ptr1->color == 1)
                {
                    ptr1->color = 0;
                    kptr->up_parent->color = 0;

                    kptr->up_parent->up_parent->color = 1;


                    kptr = kptr->up_parent->up_parent;
                }
                else // here we rae
                {

                    if (kptr == kptr->up_parent->right)
                    {
                        // setting parent

                          //   kptr->parent = kptr->up->left;
                        kptr = kptr->up_parent;


                        // left rotate case
                        leftRotationAssignee(kptr);
                    }
                    kptr->up_parent->color = 0;

                    kptr->up_parent->up_parent->color = 1;

                    rightRotationAssignee(kptr->up_parent->up_parent);
                }
            }
            if (kptr == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void searchbynameroot(NodeAssignee* node, string first, string second, stringstream& outp)
    {
        if (node != NULL)
        {
            searchbynameroot(node->left, first, second, outp);

            if (node->firstname == first && node->secondname == second)
            {
                outp << "Name: " << node->firstname << " " << node->secondname << ", Address: " << node->address << ", DOB: " << node->DOB << ", Assignee ID: " << node->ID2 << endl;
            }
            searchbynameroot(node->right, first, second, outp);
        }
    }

public:
    NodeAssignee* root;
    NodeAssignee* randomMemory;
    AssigneeTree()
    {
        randomMemory = new NodeAssignee;
        randomMemory->color = 0;
        randomMemory->left = NULL;
        randomMemory->right = NULL;
        root = randomMemory;
    }


    void inorder1(stringstream& outp)
    {
        inorder2helper(outp, this->root);
    }
    void inorder2(stringstream& outp)
    {
        inorder22helper(outp, this->root);
    }
    void searchbyname(string first, string second, stringstream& outp)
    {
        searchbynameroot(this->root, first, second, outp);
    }

    void searchTree(int k, stringstream& output)
    {
        searchTreeHelper(this->root, k, output);
    }

    void shift1(int id1, string id2, NodeTask* node)
    {
        shifthelper(this->root, id1, node, id2);
    }

    NodeAssignee* minimum(NodeAssignee* node)
    {
        while (node->left != randomMemory)
        {
            node = node->left;
        }
        return node;
    }

    NodeAssignee* successor(NodeAssignee* x)
    {
        if (x->right != randomMemory)
        {
            return minimum(x->right);
        }

        NodeAssignee* y = x->up_parent;
        while (y != randomMemory && x == y->right)
        {
            x = y;
            y = y->up_parent;
        }
        return y;
    }

    void leftRotationAssignee(NodeAssignee* node_at_whichrot)
    {
        NodeAssignee* y = node_at_whichrot->right;
        node_at_whichrot->right = y->left;

        if (y->left != randomMemory)
        {
            y->left->up_parent = node_at_whichrot;
        }
        y->up_parent = node_at_whichrot->up_parent;
        if (node_at_whichrot->up_parent == NULL)
        {
            this->root = y;
        }
        else if (node_at_whichrot == node_at_whichrot->up_parent->left)
        {
            node_at_whichrot->up_parent->left = y;
        }
        else
        {
            node_at_whichrot->up_parent->right = y;
        }
        y->left = node_at_whichrot;
        node_at_whichrot->up_parent = y;
    }

    void rightRotationAssignee(NodeAssignee* node_at_whichrota) {
        if (node_at_whichrota == NULL || node_at_whichrota->left == NULL) 
        {

            // Invalid rotation, return without performing any action
            return;
        }

        NodeAssignee* child_node = node_at_whichrota->left;
        node_at_whichrota->left = child_node->right;

        if (child_node->right != NULL) 
        {
            child_node->right->up_parent = node_at_whichrota;
        }

        child_node->up_parent = node_at_whichrota->up_parent;

        if (node_at_whichrota->up_parent == NULL)
        {
            // If node_at_whichrota is the root
            this->root = child_node;
        }
        else if (node_at_whichrota == node_at_whichrota->up_parent->right) 
        {

            node_at_whichrota->up_parent->right = child_node;               

                        
        }
        else {
            node_at_whichrota->up_parent->left = child_node;
        }

        child_node->right = node_at_whichrota;
        node_at_whichrota->up_parent = child_node;
    }


    // inserting_treeing a node
    void inserting_tree(int key, string first1, string second1, string address1, string dob1)
    {
        NodeAssignee* node = new NodeAssignee;
        node->up_parent = NULL;
        node->ID = key;

        if (key < 10)
            node->ID2 = "A00";
        else if (key >= 10 && key < 100)
            node->ID2 = "A0";
        else
            node->ID2 = "A";
        node->ID2 += to_string(key);
        node->address = address1;
        node->firstname = first1;
        node->secondname = second1;
        node->DOB = dob1;
        node->task = false;

        node->left = randomMemory;
        node->right = randomMemory;

        node->color = 1;

        NodeAssignee* temp1 = NULL;
        NodeAssignee* temp2 = this->root;

        // up_parent finding
        while (temp2 != randomMemory)
        {
            temp1 = temp2;


            if (key < temp2->ID) temp2 = temp2->left;
            else temp2 = temp2->right;


        }

        node->up_parent = temp1;

        // actual inserting_treeing
        if (temp1 == NULL)
        {
            root = node;
        }
        else if (node->ID < temp1->ID)
        {
            temp1->left = node;
        }
        else
        {
            temp1->right = node;
        }
        if (node->up_parent == NULL)
        {
            node->color = 0; // o is for black I think
            return;
        }

        if (node->up_parent->up_parent == NULL) // After inserting_treeing just one elemnt of root if root
        {
            return;
        }
        //  cout << node->address;

        inserting_treeSet_NODE(node);
    }


    NodeAssignee* getRoot()
    {
        return this->root;
    }

    void deleteNode(int ID)
    {
        Helping_delete_node(this->root, ID);
    }

    string searchbytaskqueue(NodeAssignee* node, int key)
    {
        if (node == randomMemory || key == node->ID)
        {
            return node->firstname;
        }

        if (key < node->ID)
        {
            return searchbytaskqueue(node->left, key);
        }
        return searchbytaskqueue(node->right, key);
    }
};

class TaskTree
{
private:


    // Inorder
    void inOrderHelper(NodeTask* node, stringstream& outp)
    {
        if (node != randomMemory)
        {
            inOrderHelper(node->left, outp);
            outp << node->TaskId << " (" << (node->color == 1 ? "red" : "black") << ")\n";

            inOrderHelper(node->right, outp);
        }
    }
    void deleteionfixing_Node(NodeTask* x) {
        NodeTask* sptr;

        // Fixing the tree after deletion
        while (x != root && x->color == 0) 
        {


            if (x == x->up_parent->left) 
            
            {
               
                sptr = x->up_parent->right; // Case: x is a left child

                if (sptr->color == 1) 
                { // Case: sibling is red
                   
                    sptr->color = 0;
                    x->up_parent->color = 1;
                    //   x->up->parent = x->right;

                    leftRotationTasktree(x->up_parent);
                    sptr = x->up_parent->right;
                }

                if (sptr->left->color == 0 && sptr->right->color == 0) // Case: both children of sibling are black
                {
                   
                    sptr->color = 1;
                    x = x->up_parent;

                }
                else {
                    if (sptr->right->color == 0) 
                    {
                        // Case: sibling's right child is black
                        sptr->left->color = 0;
                        //   x->up->parent = x->right;
                        sptr->color = 1;


                        rightRotationTasktree(sptr);
                        sptr = x->up_parent->right;
                    }

                    sptr->color = x->up_parent->color;
                    x->up_parent->color = 0;
                    sptr->right->color = 0;

                    //   x->up->parent = x->left;
                    leftRotationTasktree(x->up_parent);
                    x = root;
                }
            }
            else 
            
            
            {
                // Case: x is a right child
                sptr = x->up_parent->left;

                if (sptr->color == 1) 
                {
                    // Case: sibling is red
                    sptr->color = 0;
                    x->up_parent->color = 1;
                    
                    //   x->up->parent = x->right;

                    rightRotationTasktree(x->up_parent);
                    sptr = x->up_parent->left;
                }

                if (sptr->right->color == 0 && sptr->left->color == 0) {
                    // Case: both children of sibling are black
                    sptr->color = 1;

                    x = x->up_parent;
                }
                else 
                {
                    if (sptr->left->color == 0) {
                        // Case: sibling's left child is black

                        sptr->right->color = 0;
                        sptr->color = 1;

                        leftRotationTasktree(sptr);
                        sptr = x->up_parent->left;
                    }
                    sptr->color = x->up_parent->color;
                    x->up_parent->color = 0;
                    sptr->left->color = 0;


                    // right rotate case
                    rightRotationTasktree(x->up_parent);
                    x = root;
                }
            }
        }
        x->color = 0; // Set the color of the final node to black
    }

    void taskQueuehelper(NodeTask* node, stringstream& outp, AssigneeTree obj)
    {

        if (node != randomMemory)
        {
            taskQueuehelper(node->left, outp, obj);
            int lastTwo = 0;
            int length = node->AssigneeID.length();

            // Extract the last two r three or one characters
            string lastTwoDigits = node->AssigneeID.substr(length - 3, 3);
            lastTwo = stoi(lastTwoDigits);

            if (!node->complete)
                outp << "Task ID: " << node->TaskId << ", Description: " << node->description << ", Priority: " << node->prioritylev << ", Assignee: " << obj.searchbytaskqueue(obj.root, lastTwo) << " (" << node->AssigneeID << ")" << endl;
            taskQueuehelper(node->right, outp, obj);
        }
    }



    void fixingdeletion(NodeTask* uptr, NodeTask* vptr)
    {
        // If up is root then simply setting the node
        if (uptr->up_parent == NULL)
        {
            root = vptr;
        }
        // Else finding the node
        else if (uptr == uptr->up_parent->left)
        {
            //sptr->up->parent =
            uptr->up_parent->left = vptr;
        }
        else
        {
            uptr->up_parent->right = vptr;
        }
        vptr->up_parent = uptr->up_parent;
    }

    NodeTask* gettingpredecesoor(NodeTask* x)
    {
        NodeTask* y = x->left;

        while (y->right != randomMemory)
        {
            // presdescor will be the rightmost
            y = y->right;
        }

        return y;
    }


    void Helping_delete_node(NodeTask* node, int key)
    {
        NodeTask* temp1 = randomMemory;
        NodeTask* x;
        NodeTask* y;

        for (; node != randomMemory; ) 
        {
            if (node->TaskId == key) 
            {
                temp1 = node;
            }

            if (node->TaskId < key) 
            {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }


        y = temp1;
        int temp_color = y->color;
        if (temp1->left == randomMemory)
        {
            x = temp1->right;
            fixingdeletion(temp1, temp1->right);
        }
        else if (temp1->right == randomMemory)
        {
            x = temp1->left;
            fixingdeletion(temp1, temp1->left);
        }
        else
        {
            y = gettingpredecesoor(temp1);
            temp_color = y->color;


            x = y->left;
            if (y->up_parent == temp1)
            {
                x->up_parent = y;
            }
            else
            {
                fixingdeletion(y, y->left);
                y->left = temp1->left;
                y->left->up_parent = y;
            }

            fixingdeletion(temp1, y);

            //y->up->parent = y->right
            y->right = temp1->right;
            y->right->up_parent = y;

            y->color = temp1->color;
        }

        delete temp1;
        if (temp_color == 0)
        {

            deleteionfixing_Node(x);
        }
    }

    void Helping_delete_node1(NodeTask* node, int key)
    {
        NodeTask* temp1 = randomMemory;
        NodeTask* temp2;
        NodeTask* temp3;

        while (node != randomMemory)
        {
            if (node->prioritylev == key)
            {
                temp1 = node;
            }

            if (node->prioritylev <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (temp1 == randomMemory)
        {
            cout << "key is not present.....returning" << endl;
            //return key not present
            return;
        }

        temp3 = temp1;
        int temp_color = temp3->color;


        if (temp1->left == randomMemory)
        {
            temp2 = temp1->right;
            fixingdeletion(temp1, temp1->right);

            // temp2 = temp2->up_parent->up_parent->right;


        }
        else if (temp1->right == randomMemory)
        {
            temp2 = temp1->left;
            fixingdeletion(temp1, temp1->left);
        }
        else
        {
            // In test cases it is taking predecssor

            temp3 = gettingpredecesoor(temp1); // so getting predecessor by calling getpredecssor function

            temp_color = temp3->color;


            temp2 = temp3->left;


            if (temp3->up_parent == temp1)
            {
                temp2->up_parent = temp3;
            }
            else
            {
                fixingdeletion(temp3, temp3->left);
                temp3->left = temp1->left;
                temp3->left->up_parent = temp3;


            }

            fixingdeletion(temp1, temp3);

            temp3->right = temp1->right;
            temp3->right->up_parent = temp3;
            temp3->color = temp1->color;
        }
        delete temp1;
        if (temp_color == 0)
        {
            deleteionfixing_Node(temp2);
        }
    }
    // For balancing the tree after inserting_treeion
    void Set_node(NodeTask* kptr) 
    {
        while (kptr != root && kptr->up_parent->color == 1) 
        
        {
            NodeTask* uptr;

            if (kptr->up_parent == kptr->up_parent->up_parent->right) 
            
            {

                // RR or RL case
                uptr = kptr->up_parent->up_parent->left;

                if (uptr->color == 1) {
                    // Case: uncle is red
                    uptr->color = 0;


                    kptr->up_parent->color = 0;
                    kptr->up_parent->up_parent->color = 1;

                    kptr = kptr->up_parent->up_parent;
                }
                else {
                  
                    if (kptr == kptr->up_parent->left)   // Case: uncle is black
                    {

                        kptr = kptr->up_parent;

                        rightRotationTasktree(kptr);
                    }
                    kptr->up_parent->color = 0;
                    kptr->up_parent->up_parent->color = 1;

                    // leftrotate(LR)
                    leftRotationTasktree(kptr->up_parent->up_parent);
                }
            }
            else 
            {
                // LL or LR case
                uptr = kptr->up_parent->up_parent->right;

                if (uptr->color == 1) {
                    
                    uptr->color = 0;// Case: uncle is red
                    kptr->up_parent->color = 0;

                    kptr->up_parent->up_parent->color = 1;
                    kptr = kptr->up_parent->up_parent;
                }
                else
                {
                    
                    if (kptr == kptr->up_parent->right)  // Case: uncle is black
                    
                    {
                        kptr = kptr->up_parent;
                       leftRotationTasktree(kptr);
                    }
                    kptr->up_parent->color = 0;
                    kptr->up_parent->up_parent->color = 1;



                    // right rotate
                    rightRotationTasktree(kptr->up_parent->up_parent);
                }
            }
        }
        // f in any case root color is changed set to 0 (black)
        root->color = 0;

    }


public:

    NodeTask* root;
    NodeTask* randomMemory;
    int counttotal;

    TaskTree()
    {
        randomMemory = new NodeTask;
        randomMemory->color = 0;
        randomMemory->left = NULL;
        randomMemory->right = NULL;
        root = randomMemory;
        counttotal = 0;
    }

    void inorder(stringstream& outp)
    {
        inOrderHelper(this->root, outp);
    }

    void taskQueue(stringstream& outp, AssigneeTree node)
    {
        taskQueuehelper(this->root, outp, node);
    }
    NodeTask* minimum(NodeTask* node)
    {
        while (node->left != randomMemory)
        {
            node = node->left;
        }
        return node;
    }

    NodeTask* maximum(NodeTask* node)
    {
        while (node->right != randomMemory)
        {
            node = node->right;
        }
        return node;
    }
    void rightRotationTasktree(NodeTask* node_at_whichrota) {
        if (node_at_whichrota == NULL || node_at_whichrota->left == NULL)
        {
        
            return;    // Invalid rotation, return without performing any action
        }

        NodeTask* child_node = node_at_whichrota->left;

        node_at_whichrota->left = child_node->right;

        if (child_node->right != NULL) 
        {
            child_node->right->up_parent = node_at_whichrota;
        }

        child_node->up_parent = node_at_whichrota->up_parent;

        if (node_at_whichrota->up_parent == NULL)
        {
            // If node_at_whichrota is the root
            this->root = child_node;
        }
        else if (node_at_whichrota == node_at_whichrota->up_parent->right) 
        {
            node_at_whichrota->up_parent->right = child_node;
        }
        else {
            node_at_whichrota->up_parent->left = child_node;
        }

        child_node->right = node_at_whichrota;
        node_at_whichrota->up_parent = child_node;
    }


    NodeTask* successor(NodeTask* x)
    {
        if (x->right != randomMemory)
        {
            return minimum(x->right);
        }

        NodeTask* y = x->up_parent;
        while (y != randomMemory && x == y->right)
        {
            x = y;
            y = y->up_parent;
        }
        return y;
    }

    void leftRotationTasktree(NodeTask* x) {
        if (x == NULL || x->right == NULL) 
        {
           
            return; // Invalid rotation, return without performing any action
        }


        NodeTask* y = x->right;
        x->right = y->left;

        if (y->left != NULL) 
        {
            y->left->up_parent = x;
        }

        y->up_parent = x->up_parent;

        if (x->up_parent == NULL) 
        {
            
            this->root = y;// If x is the root
        }
        else if (x == x->up_parent->left) 
        {
            x->up_parent->left = y;
        }
        else
        {
            x->up_parent->right = y;
        }

        y->left = x;
        x->up_parent = y;
    }


    // inserting_treeing a node
    void inserting_tree(int TaskId1, string descriptionlevel1, int prioritylevel1, string ID1)
    {
        NodeTask* newnode = new NodeTask;
        newnode->up_parent = NULL;

        newnode->left = randomMemory;
        newnode->right = randomMemory;

        newnode->color = 1;
        newnode->TaskId = TaskId1;
        newnode->description = descriptionlevel1;
        newnode->prioritylev = prioritylevel1;
        newnode->AssigneeID = ID1;
        newnode->complete = false;

        counttotal++;

        NodeTask* temp1 = NULL;
        NodeTask* tempx = this->root;

        // up_parent finding
        while (tempx != randomMemory)
        {
            temp1 = tempx;
            if (prioritylevel1 < tempx->prioritylev)
            {
                tempx = tempx->left;
            }
            else
            {
                tempx = tempx->right;
            }
        }

        newnode->up_parent = temp1;

        // actual inserting_treeing
        if (temp1 == NULL)
        {
            root = newnode;


        }
        else if (newnode->prioritylev < temp1->prioritylev)
        {
            temp1->left = newnode;
        }
        else
        {
            temp1->right = newnode;
        }
        if (newnode->up_parent == NULL)
        {
            newnode->color = 0; // o is for black I think
            return;
        }
        // if only second element on one side
        if (newnode->up_parent->up_parent == NULL) // After inserting_treeing just one elemnt of root if root
        {
            return;
        }
        //   cout << newnode->address;

        Set_node(newnode);
    }

    void inserting_tree1(int taskid, int prioritylevel1)
    {
        NodeTask* node = new NodeTask;
        node->up_parent = NULL;

        node->left = randomMemory;
        node->right = randomMemory;

        node->color = 1;
        node->TaskId = taskid;

        node->prioritylev = prioritylevel1;

        counttotal++;

        NodeTask* temp2 = NULL;
        NodeTask* tempx = this->root;

        // up_parent finding
        for (; tempx != randomMemory; temp2 = tempx) 
        {
            if (prioritylevel1 <= tempx->prioritylev) 
            {
                tempx = tempx->left;
            }
            else 
            {
                tempx = tempx->right;
            }
        }

        node->up_parent = temp2;

        // actual inserting_treeing
        if (temp2 == NULL)
        {
            root = node;
        }


        else if (node->prioritylev <= temp2->prioritylev)
        {
            temp2->left = node;
        }
        else
        {
            temp2->right = node;
        }
        if (node->up_parent == NULL)
        {
            node->color = 0; // o is for black
            return;
        }

        if (node->up_parent->up_parent == NULL) // After inserting_treeing just one elemnt of root if root
        {
            return;
        }
        //   cout << node->address;

        Set_node(node);
    }

    void addT(NodeAssignee* obj2, stringstream& outp, NodeAssignee* randomMemory)
    {
        if (obj2 != randomMemory)
        {
            addT(obj2->left, outp, randomMemory);
            if (!obj2->task)
            {
                outp << "Name: " << obj2->firstname << " " << obj2->secondname << ", Address: " << obj2->address << ", DOB: " << obj2->DOB << ", Assignee ID: " << obj2->ID2 << endl;
            }
            addT(obj2->right, outp, randomMemory);
        }
    }
    NodeTask* getRoot()
    {
        return this->root;
    }

    void deleteNode(int data)
    {
        Helping_delete_node(this->root, data);
    }
    void deleteNode1(int data)
    {
        Helping_delete_node1(this->root, data);
    }

    void assigntask(NodeAssignee* obj, NodeTask* obj2)
    {
        if (obj2 != randomMemory)
        {
            assigntask(obj, obj2->left);
            inorderasignee(obj, obj2->AssigneeID);
            assigntask(obj, obj2->right);
        }
    }
    void inorderasignee(NodeAssignee* obj2, string assigneID)
    {
        if (obj2 != NULL)
        {
            inorderasignee(obj2->left, assigneID);
            if (obj2->ID2 == assigneID)
            {
                obj2->task = true;
            }
            inorderasignee(obj2->right, assigneID);
        }
    }

    void seefor(int priority, NodeTask* obj1, stringstream& outp, AssigneeTree Node)
    {
        if (obj1 != randomMemory)
        {
            seefor(priority, obj1->left, outp, Node);
           
            if (obj1->prioritylev == priority)
            {
                int lastTwo = 0;
                int length = obj1->AssigneeID.length();

                // Extract the last two r three or one characters
                string lastTwoDigits = obj1->AssigneeID.substr(length - 3, 3);
                lastTwo = stoi(lastTwoDigits);
                outp << "Highest Priority Task: Task ID: " << obj1->TaskId << ", Description: " << obj1->description << ", Priority: " << obj1->prioritylev << ", Assignee: " << Node.searchbytaskqueue(Node.root, lastTwo) << " (" << obj1->AssigneeID << ")" << endl;
            }
            seefor(priority, obj1->right, outp, Node);
        }
    }

    void findinghighestpriotask(stringstream& outp, NodeTask* obj1, AssigneeTree node, NodeTask* obj2)
    {
        while (1)
        {
            if (obj1->left != randomMemory)
            {
                obj1 = obj1->left;
            }
            else
            {
                int lastTwo = 0;
                int length = obj1->AssigneeID.length();

                // Extract the last two r three or one characters
                string lastTwoDigits = obj1->AssigneeID.substr(length - 3, 3);
                lastTwo = stoi(lastTwoDigits);
                // outp << "Highest Priority Task: Task ID: " << obj1->TaskId << ", Description: " << obj1->description << ", Priority: " << obj1->prioritylev << ", Assignee: " << node.searchbytaskqueue(node.root, lastTwo) << " (" << obj1->AssigneeID << ")" << endl;
               
                seefor(obj1->prioritylev, obj2, outp, node);
                break;
            }
        }
    }
    void findingtask(string id, stringstream& outp, NodeTask* node1, AssigneeTree node)
    {
        if (node1 != randomMemory)
        {
            int lastTwo = 0;
            int length = node1->AssigneeID.length();

            // Extract the last two r three or one characters
            string lastTwoDigits = node1->AssigneeID.substr(length - 3, 3);
            lastTwo = stoi(lastTwoDigits);

            findingtask(id, outp, node1->left, node);
            if (node1->AssigneeID == id && !node1->complete)
            {
                outp << "Task ID: " << node1->TaskId << ", Description: " << node1->description << ", Priority: " << node1->prioritylev << ", Assignee: " << node.searchbytaskqueue(node.root, lastTwo) << " (" << node1->AssigneeID << ")" << endl;
            }
            findingtask(id, outp, node1->right, node);
        }
    }
    void displaytoaltasks(stringstream& outp)
    {
        outp << "Total Tasks in the System: " << this->counttotal << endl;
    }

    void priorityrange(int start, int end, stringstream& outp, NodeTask* node1, AssigneeTree node)
    {

        if (node1 != randomMemory)
        {

            priorityrange(start, end, outp, node1->left, node);
            if (node1->prioritylev >= start && node1->prioritylev <= end)
            {
                int lastTwo = 0;
                int length = node1->AssigneeID.length();

                // Extract the last two r three or one characters
                string lastTwoDigits = node1->AssigneeID.substr(length - 3, 3);
                lastTwo = stoi(lastTwoDigits);
                outp << "Task ID: " << node1->TaskId << ", Description: " << node1->description << ", Priority: " << node1->prioritylev << ", Assignee: " << node.searchbytaskqueue(node.root, lastTwo) << " (" << node1->AssigneeID << ")" << endl;
            }
            priorityrange(start, end, outp, node1->right, node);
        }
    }
    void findingpror(int taskid, NodeTask* obj)
    {
        if (obj != randomMemory)
        {
            findingpror(taskid, obj->left);
            if (obj->TaskId == taskid)
            {
                obj->complete = true;
                // this->deleteNode1(obj->prioritylev);
                // this->inserting_tree1(obj->TaskId, obj->prioritylev);
                return;
            }
            findingpror(taskid, obj->right);
        }
    }
    /* bool findingid(int priorlev,NodeTask* obj)
     {
         if (obj != randomMemory)
         {


         }

     }*/
    void updatePriority(int taskid, int priorlev, NodeTask* obj, TaskTree obj2)
    {
        if (obj != randomMemory)
        {
            updatePriority(taskid, priorlev, obj->left, obj2);
            if (obj->TaskId == taskid)
            {
                if (!obj->complete) {

                    string desc = obj->description;
                    string Asid = obj->AssigneeID;
                    int taskid = obj->TaskId;

                    obj2.deleteNode1(obj->prioritylev);
                    inserting_tree(taskid, desc, priorlev, Asid);
                   
                    return;
                }
               
            }
            updatePriority(taskid, priorlev, obj->right, obj2);
        }
    }
    void completetaskshelper(stringstream& outp, NodeTask* node1, AssigneeTree node)
    {
        if (node1 != randomMemory)
        {
            completetaskshelper(outp, node1->left, node);
            if (node1->complete)
            {
                int lastTwo = 0;
                int length = node1->AssigneeID.length();

                // Extract the last two characters
                string lastTwoDigits = node1->AssigneeID.substr(length - 3, 3);
                lastTwo = stoi(lastTwoDigits);

                outp << "Task ID: " << node1->TaskId << ", Description: " << node1->description << ", Priority: " << node1->prioritylev << ", Assignee: " << node.searchbytaskqueue(node.root, lastTwo) << " (" << node1->AssigneeID << ")" << endl;
            }
            completetaskshelper(outp, node1->right, node);
        }
    }
};

class taskManagementSystem
{
private:
public:
    AssigneeTree assigneeTask;
    TaskTree tasktree;
    taskManagementSystem()
    {
        counter = 1;
    }
    void addAssignee(const string& first, const string& second, const string& address, const string& dob)
    {
        Assignee obj(first, second, address, dob);
        //  string generatedID = obj.getID();

        int length = obj.ID.length();

        //  int last = stoi(string(1, obj.ID[length - 1]));
        int last = counter;
        counter++;
        assigneeTask.inserting_tree(last, first, second, address, dob);
    }
    void displaybyID(stringstream& outp, string IDd)
    {
        int lastTwo = 0;
        int length = IDd.length();

        // Extract the last two characters
        string lastTwoDigits = IDd.substr(length - 3, 3);
        lastTwo = stoi(lastTwoDigits);

        assigneeTask.searchTree(lastTwo, outp);
    }
    void displaybyname(stringstream& outp, string first, string second)
    {

        assigneeTask.searchbyname(first, second, outp);
    }
    void addTask(int taskID, string description, int prioritylevel, string ID)
    {
        tasktree.inserting_tree(taskID, description, prioritylevel, ID);
        tasktree.assigntask(assigneeTask.root, tasktree.getRoot());
    }
    void AssigneeWithNoTask(stringstream& obj)
    {
        tasktree.addT(assigneeTask.root, obj, assigneeTask.randomMemory);
    }
    void DeleteAssignee(string ID)
    {
        int lastTwo = 0;
        int length = ID.length();

        // Extract the last two r three or one characters
        string lastTwoDigits = ID.substr(length - 3, 3);
        lastTwo = stoi(lastTwoDigits);

        assigneeTask.deleteNode(lastTwo);
    }
    void DisplayAssignee(stringstream& outp)
    {
        assigneeTask.inorder1(outp);
    }
    void AssigneeInOrder(stringstream& outp)
    {
        assigneeTask.inorder2(outp);
    }
    void PrintTreeInorder(stringstream& outp)
    {
        tasktree.inorder(outp);
    }
    void deleteTask(int taskid)
    {
        tasktree.deleteNode(taskid);
    }
    void printTaskQueue(stringstream& outp)
    {
        tasktree.taskQueue(outp, assigneeTask);
    }
    void findHighestPriorityTask(stringstream& outp)
    {
        bool found = true;
        tasktree.findinghighestpriotask(outp, tasktree.root, assigneeTask, tasktree.root);
    }
    void findTasksByAssignee(string id, stringstream& outp)
    {
        int lastTwo = 0;
        int length = id.length();

        // Extract the last two r three or one characters
        string lastTwoDigits = id.substr(length - 3, 3);
        lastTwo = stoi(lastTwoDigits);

        outp << "Tasks Assigned to \"" << assigneeTask.searchbytaskqueue(assigneeTask.root, lastTwo) << " (" << id << ")\":" << endl;
        tasktree.findingtask(id, outp, tasktree.root, assigneeTask);
    }
    void countTotalTasks(stringstream& outp)
    {
        tasktree.displaytoaltasks(outp);
    }
    void searchTasksByPriorityRange(int start, int end, stringstream& outp)
    {
        outp << "Tasks within Priority Range (" << start << " to " << end << "):" << endl;
        tasktree.priorityrange(start, end, outp, tasktree.root, assigneeTask);
    }
    void ShiftTask(string ID1, string ID2)
    {
        int lastTwo = 0;
        int length = ID1.length();

        // Extract the last two r three or one characters
        string lastTwoDigits = ID1.substr(length - 3, 3);
        lastTwo = stoi(lastTwoDigits);

        assigneeTask.shift1(lastTwo, ID2, tasktree.root);
    }
    void completeTask(int taskid)
    {
        tasktree.findingpror(taskid, tasktree.root);
    }

    void updateTaskPriority(int taskid, int priority_level)
    {
        tasktree.updatePriority(taskid, priority_level, tasktree.root, tasktree);

    }
    void displayCompletedTasks(stringstream& outp)
    {
        outp << "Completed Tasks:" << endl;
        tasktree.completetaskshelper(outp, tasktree.root, assigneeTask);
    }
};

