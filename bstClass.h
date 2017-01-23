
#include <stdlib.h>
#ifndef BSTCLASS_H_INCLUDED
#define BSTCLASS_H_INCLUDED


// TODO: Left child is not being re-assigned properly to the tree after deletion -- COMPLETE
class node{
    public:
        node(){
            right_child = NULL;
            left_child = NULL;

        }
        bool isLeaf; // used for the new function that will define the cost of a path
        int leafIndex; // this is useful to be able to update the leafArray function
        int key; // the value
        int depth;
        int height;
        int bf;
        node* right_child;
        node* left_child;
        node* parent;
};
class BST{
    public:
        BST(){ // Use constructor to assign a root NEEDS ERROR CHECKING
            is_Empty = false;
            leafCounter = 0;
            std::cout<<"Enter a root value or enter -9999 to exit: ";

            this->root = new node();
            this->root->depth = 0;

            int usersChoice;
            bool valid = false;
            while(valid != true){

                std::cin>>usersChoice;

                if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore();
                    valid = false;
                    std::cout<<"Wrong input, please select an integer."<<std::endl;
                }else{
                    valid = true;
                }
            }

            this->root->key = usersChoice;
            this->root->right_child = NULL;
            this->root->left_child = NULL;
            this->root->parent = NULL;
            this->root->isLeaf = true; // initialize the root to be a leaf
            this->root->height = 0;
            if(this->root->key == -1){
                std::cout<<"Terminating Binary Search Tree Program\nHave an excellent day!"<<std::endl;
            }

            leafArray[leafCounter] = this->root->key; // place the leaf in the array
            //leafCounter++;
            this->root->leafIndex = leafCounter; // set the leafIndex to the current counter
        }
        // General Variables
        bool is_Empty; // value to check if the tree is currently empty
        int leafArray[100]; // using only 100 leaves at this stage******************
        int leafCounter; // this is used to determine how many leaves are currently stored

        // Pointers
        node* root;
        node* head; // keeps track of the current node in use

        // Functions
        node* searchNode(int);
        void insertNode(node*, int);
        void deleteNode(int); // still a bug floating around somewhere
        void printTree(node*);
        // Helper functions for the delete function
        node* findPredecessor(node*);
        node* findSuccessor(node*);

        void findDepth(int, node*);
        int findCost(int, int, node*);
        // Helper functions for findCost
        void printLeaves();
        void findCost(node*); // interface for find cost
        // TODO:
        int isBalanced(node*);
        // Helper functions for isBalanced
        int findHeight(node*);

};
node* BST::searchNode(int key){
       if(key == this->head->key){ // found the node, return the pointer to the node
            std::cout<<"Found node!"<<std::endl;
            return this->head;
       }
       else if(key > this->head->key){ // if the key is larger than the value

            if(this->head->right_child != NULL){ // check if there is a right child to continue search

                this->head = this->head->right_child;
                searchNode(key);
            }
             // if there is not a right child, send back a null value so that only one message is printed
            else if(this->head == this->root){ // this is just in case the tree only has one value
                    std::cout<<"Could not find the node with "<<key<<" as the value"<<std::endl;
                    return NULL;
            }else{
                std::cout<<"Could not find the node with "<<key<<" as the value"<<std::endl;
                return NULL;
            }

       }
       else if(key < this->head->key){ // if the key is less than the value
            if(this->head->left_child != NULL){ // check if there is a left child to continue search

                this->head = this->head->left_child;
                searchNode(key);
            }
            // if there is not a right child, send back a null value so that only one message is printed
            else if(this->head == this->root){ // this is just in case the tree only has one value
                    std::cout<<"Could not find the node with "<<key<<" as the value"<<std::endl;
                    return NULL;
            }else{
                std::cout<<"Could not find the node with "<<key<<" as the value"<<std::endl;
                return NULL;
            }
       }
        else{
            std::cout<<"Could not find the node with "<<key<<" as the value"<<std::endl;
            return NULL;

        }
}
void BST::insertNode(node* pointer, int userValue){ // initially goes into recursion with pointer at ROOT
    /*
    if(pointer == NULL){
        pointer = new node();
        pointer->key = userValue;
        std::cout<<"Value "<<pointer->key<<" was added to tree!"<<std::endl;
        return;
    }
    */
    if(userValue > pointer->key){ // larger than current value
        //std::cout<<"Value is greater than "<<pointer->key<<std::endl;

        if(pointer->right_child == NULL){ // is there a right child?
            pointer->right_child = new node();
            pointer->right_child->height = 0;
            pointer->right_child->parent = pointer; // assign parent to the new right child
            pointer->right_child->key = userValue;
            pointer->right_child->depth = pointer->right_child->parent->depth + 1; // increment the depth with the parents value

            // LEAF EXCHANGE ----------------------------------------------------------------and height increase
            if(pointer->left_child == NULL){ // Leaf counter does not need updated
                pointer->right_child->parent->isLeaf = false; // the parent is no longer a leaf
                pointer->right_child->isLeaf = true; // the new child is now considered a leaf
                pointer->right_child->leafIndex = pointer->leafIndex; // exchange the parent's leaf index to the child's leaf index
                leafArray[pointer->right_child->leafIndex] = pointer->right_child->key; // assign the key of the child to the parent's original place in the array

            }else{ // leaf counter needs updated before assignment
                leafCounter ++;

                pointer->right_child->isLeaf = true; // the new child is now considered a leaf
                pointer->right_child->leafIndex = leafCounter; // exchange the parent's leaf index to the child's leaf index
                leafArray[pointer->right_child->leafIndex] = pointer->right_child->key;
            }
            // LEAF EXCHANGE END --------------------------------------------------------------
            std::cout<<"Value "<<pointer->right_child->key<<" was added to tree!"<<std::endl;
            std::cout<<"The parent value is "<<pointer->right_child->parent->key<<std::endl;
        }
        else{
            pointer = pointer->right_child; // recursive case
            insertNode(pointer, userValue);
        }
    }
    else if(userValue < pointer->key){
        //std::cout<<"Value is less than "<<pointer->key<<std::endl;

        if(pointer->left_child == NULL){ // is there a left child?
            pointer->left_child = new node();
            pointer->left_child->parent = pointer; // assign parent to the new left child
            pointer->left_child->key = userValue; // increment the depth with the parents value
            pointer->left_child->depth = pointer->left_child->parent->depth + 1; // increment the depth

            // LEAF EXCHANGE ----------------------------------------------------------------
            if(pointer->right_child == NULL){
                pointer->left_child->parent->isLeaf = false; // the parent is no longer a leaf
                pointer->left_child->isLeaf = true; // the new child is now considered a leaf
                pointer->left_child->leafIndex = pointer->leafIndex; // exchange the parent's leaf index to the child's leaf index
                leafArray[pointer->left_child->leafIndex] = pointer->left_child->key; // assign the key of the child to the parent's original place in the array

            }else{ // leaf counter needs updated before assignment
                leafCounter ++;

                pointer->left_child->isLeaf = true; // the new child is now considered a leaf
                pointer->left_child->leafIndex = leafCounter; // exchange the parent's leaf index to the child's leaf index
                leafArray[leafCounter] = pointer->left_child->key;
            }
            // LEAF EXCHANGE END --------------------------------------------------------------
            std::cout<<"Value "<<pointer->left_child->key<<" was added to tree!"<<std::endl;
            std::cout<<"The parent value is "<<pointer->left_child->parent->key<<std::endl;
        }
        else{
            pointer = pointer->left_child; // recursive case
            insertNode(pointer, userValue);
        }
    }
    else{
        std::cout<<"Duplicate values cannot exist in this tree."<<std::endl;
        return;
    }
}
// Helper functions to delete **************************
node* BST::findPredecessor(node* pointer){
    if(pointer->right_child){
        findPredecessor(pointer->right_child);
    }
    else{

        return pointer;
    }

}
node* BST::findSuccessor(node* pointer){
    if(pointer->left_child){
        findSuccessor(pointer->left_child);
    }
    else{

        return pointer;
    }

}
// END helper functions to delete ***********************
void BST::deleteNode(int key){
    node* pointer = searchNode(key);
    node* temp;
    // std::cout<<pointer->key<<std::endl;

    if(pointer != NULL){ // Does the node exist?
        if(pointer == this->root && (!pointer->left_child) && (!pointer->right_child)){ // no array changes needed
            is_Empty = true;
            delete pointer;
        }
        else if(pointer->left_child){
            temp = findPredecessor(pointer->left_child); // find the predecessor

            // change the parent
            pointer->key = temp->key;
            if(temp == temp->parent->right_child){
                temp->parent->right_child = NULL;
                 // std::cout<<"Right child of the temp's parent has been assigned to NULL"<<std::endl;
            }
            if(temp == temp->parent->left_child){
                temp->parent->left_child = NULL;
                // std::cout<<"Left child of the temp's parent has been assigned to NULL"<<std::endl;
            }
            if(temp->left_child){ // check for a left child
                temp->left_child->parent = temp->parent; // assign the left child to the temp's parent
                temp->parent->right_child = temp->left_child; // assign the temp's parent's right child to temp's left child
            }
            leafArray[temp->leafIndex] = NULL; // the value in the leafArray from the predecessor must be set to NULL
            // std::cout<<leafArray[temp->leafIndex]<<std::endl;
            delete temp;
        }
        else if(pointer->right_child){
            temp = findSuccessor(pointer->right_child);
             // std::cout<<temp->key<<std::endl;
            // std::cout<<temp->leafIndex<<std::endl;
            //change the parent
            pointer->key = temp->key;
            if(temp == temp->parent->left_child)
                temp->parent->left_child = NULL;
            if(temp->right_child){ // check for a right child
                temp->right_child->parent = temp->parent; // assign the right child to the temp's parent
                temp->parent->left_child = temp->right_child; // assign the temp's parent's left child to temp's right child
            }
            leafArray[temp->leafIndex] = NULL; // the value in the leafArray from the successor must be set to NULL
            delete temp;
        }else{ // If this is a leaf node
            if(pointer->parent->right_child == pointer) // is this node-to-be-deleted the right child of another node?
            {
                pointer->parent->right_child = NULL;
                if(pointer->leafIndex != pointer->parent->leafIndex){
                    leafArray[pointer->leafIndex] = NULL; // set the leaf value in the leaf array to NULL
                }
                else if(pointer->parent->left_child == NULL){ // is the parent now a leaf?
                    leafArray[pointer->parent->leafIndex] = pointer->parent->key;
                }
                delete pointer;
            }else{                                     // is this the parent's left child?
                pointer->parent->left_child = NULL;
                if(pointer->leafIndex != pointer->parent->leafIndex){
                    leafArray[pointer->leafIndex] = NULL; // set the leaf value in the leaf array to NULL
                }
                else if(pointer->parent->right_child == NULL){
                    leafArray[pointer->parent->leafIndex] = pointer->parent->key;
                }
                delete pointer;
            }
        }

    }else{
        std::cout<<"This object does not exist.\nFATAL ERROR"<<std::endl;

    }
        /*if(pointer->left_child != NULL){
            if(pointer->parent->right_child == NULL){
                pointer->left_child->parent = pointer->parent;
                pointer->parent->right_child = pointer->left_child;
            }
            // pointer->left_child->parent = pointer->parent; // This needs to go to the right subtree of the parent
            // pointer->parent->left_child = pointer->left_child;
        }else{
            pointer->parent->left_child = NULL;
        }
        if(pointer->right_child != NULL){

            pointer->right_child->parent = pointer->parent;
            pointer->parent->right_child = pointer->right_child;
        }
        else{
            pointer->parent->right_child = NULL;
        }
        std::cout<<"Deleting node with value "<<pointer->key<<std::endl;
        delete[] pointer;

    }else{
        std::cout<<"Deletion for value "<<key<<" was unsuccessful!"<<std::endl;
    }*/
}
void BST::printTree(node* nPointer){ // go all the way right first, then middle, then last
    if(nPointer->right_child != NULL){
        printTree(nPointer->right_child); // go right

        if(nPointer->left_child != NULL){
            std::cout<<nPointer->key<<std::endl;
            printTree(nPointer->left_child);
        }else{
            std::cout<<nPointer->key<<std::endl;
        }
   }
   else if(nPointer->left_child != NULL){
        std::cout<<nPointer->key<<std::endl;
        printTree(nPointer->left_child);

        if(nPointer->right_child != NULL){
            std::cout<<nPointer->key<<std::endl;
            printTree(nPointer->right_child);
        }
   }
   else{
            std::cout<<nPointer->key<<std::endl;
    }

}
void BST::findDepth(int value, node* pointer){
    if(value == pointer->key){
        std::cout<<"Depth is "<<pointer->depth<<std::endl;
    }
    else if(value > pointer->key){
        findDepth(value, pointer->right_child);
    }else{
        findDepth(value, pointer->left_child);
    }
}
void BST::printLeaves(){ /* THIS FUNCTION IS USED FOR DEBUGGING ONLY*/

        for(int i = 0; i <= leafCounter; i++){
                if(leafArray[i] != NULL)
                    std::cout<<leafArray[i]<<" ";
        }
        std::cout<<std::endl;
}
void BST::findCost(node* pointer){
    int leafPaths[leafCounter + 1];
    int highestPath;
    for(int i = 0; i <= leafCounter; i++){
            if(leafArray[i] != NULL){
                leafPaths[i] = findCost(leafArray[i], 0, pointer);
                std::cout<<"Cost of leaf "<<leafArray[i]<<" is "<<leafPaths[i]<<std::endl;
                if(i == 0){
                    highestPath = leafPaths[i];
                }
                if(leafPaths[i] > highestPath){
                    highestPath = leafPaths[i];
                }
            }
    }
    //int mediate;
//    for(int j = 0; j <= leafCounter + 1; j++){ // bubble sort the leafPaths
//        if(leafPaths[j] > leafPaths[j + 1]){
//            mediate = leafPaths[j];
//            leafPaths[j] = leafPaths[j+1];
//            leafPaths[j + 1] = mediate;
//        }
//    }
    std::cout<<"Most expensive path is: "<<highestPath<<std::endl;
}
int BST::findCost(int value,int costSum, node* pointer){
    if(value > pointer->key){
        costSum += pointer->key;
        findCost(value, costSum, pointer->right_child);
    }
    else if(value < pointer->key){
        costSum += pointer->key;
        findCost(value, costSum, pointer->left_child);
    }
    else{
        costSum += pointer->key;
        return costSum;
    }
}
int BST::isBalanced(node* pointer){
    if(pointer->right_child){ // branch right
        isBalanced(pointer->right_child); // recursive case
        if(pointer->left_child){
            isBalanced(pointer->left_child);
            pointer->bf = abs(pointer->right_child->height - pointer->left_child->height);
            std::cout<<"Balance factor of "<<pointer->key<<" is "<<pointer->bf<<std::endl;
        }else{
            pointer->bf = abs(pointer->right_child->height + 1);
            std::cout<<"Balance factor of "<<pointer->key<<" is "<<pointer->bf<<std::endl;
        }
    }
    else if(pointer->left_child){ // branch left
        isBalanced(pointer->left_child); // recursive case
        if(pointer->right_child){
            isBalanced(pointer->right_child);
            pointer->bf = abs(pointer->left_child->height - pointer->right_child->height);
            std::cout<<"Balance factor of "<<pointer->key<<" is "<<pointer->bf<<std::endl;
        }else{
            pointer->bf = abs(pointer->left_child->height + 1);
            std::cout<<"Balance factor of "<<pointer->key<<" is "<<pointer->bf<<std::endl;
        }
    }else{
        pointer->bf = 0;
        std::cout<<"Balance factor of "<<pointer->key<<" is "<<pointer->bf<<std::endl;
    }

    // OUTPUT
    if(pointer->bf >= 2 && pointer->parent != NULL){
        std::cout<<"This (sub)tree is not balanced"<<std::endl;
    }
    else if(pointer->bf >= 2 && pointer->parent == NULL){
        std::cout<<"This tree is unbalanced"<<std::endl;
    }
    else if(pointer->bf < 2 && pointer->parent !=NULL){
        std::cout<<"This (sub) tree is balanced"<<std::endl;
    }else{
        std::cout<<"This tree is balanced"<<std::endl;
    }
}
int BST::findHeight(node* pointer){
    int tempHeight;
    if(!pointer->left_child && !pointer->right_child){ // is a leaf node
        pointer->height = 0;
        std::cout<<"Height of "<<pointer->key<<" is "<<pointer->height<<std::endl;
        return 0;
    }
    else if(pointer->right_child){ // has a right child
          pointer->height =  1 + findHeight(pointer->right_child);
            //assign left branch
          if(pointer->left_child){
            tempHeight = findHeight(pointer->left_child);
            if(tempHeight > pointer->height){
                pointer->height = tempHeight;
            }
          }

         std::cout<<"Height of "<<pointer->key<<" is "<<pointer->height<<std::endl;
        return pointer->height;
    }
    else{ // has a left child
        pointer->height = 1 + findHeight(pointer->left_child);
        // assign right branch
        if(pointer->right_child){
            tempHeight = findHeight(pointer->right_child);
            if(tempHeight > pointer->height){
                pointer->height = tempHeight;
            }
        }

        std::cout<<"Height of "<<pointer->key<<" is "<<pointer->height<<std::endl;
        return pointer->height;
    }

}

#endif // BSTCLASS_H_INCLUDED
