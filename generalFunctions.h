#include <iostream>
#ifndef GENERALFUNCTIONS_H_INCLUDED
#define GENERALFUNCTIONS_H_INCLUDED

using namespace std;
// Helper routines....place these in a separate file
int userInterface(){

    bool programLoop = true;

    cout<<"\t\t\t\t\tWelcome to the Binary Search Tree Program!"<<endl;
    BST* myBST = new BST(); // Create a BST object. Allocate memory with new

    while(programLoop && myBST->is_Empty == false){
        myBST->head = myBST->root;
        int usersChoice;

        if(myBST->root->key == -9999) // break from the entire program
            return 0;

        cout<<"BST CHOICES:\n"<<endl;
        cout<<"1.) Search for a node"<<endl;
        cout<<"2.) Insert a node"<<endl;
        cout<<"3.) Delete a node"<<endl;
        cout<<"4.) Print tree in a given order"<<endl; // I will use, by default, an in-order traversal
        cout<<"5.) Find the depth of a given node in this tree"<<endl;
        cout<<"6.) Find the cost of a path for a given node"<<endl;
        cout<<"7.) Check if this tree is balanced"<<endl;
        cout<<"8.) Quit program"<<endl;
        cout<<"\nPlease select what you wish to do (Correct format is a single integer (1 - 8): ";

        bool valid = false;
        while(valid != true){

            cin>>usersChoice;

            if(cin.fail() || usersChoice > 8 || usersChoice < 1){
                cin.clear();
                cin.ignore();
                valid = false;
                cout<<"Wrong input, please select an integer between 1-8: ";
            }else{
                valid = true;
            }
        }
        int userValue;
        switch(usersChoice){
            case 1: // search
                cout<<"Enter a value to search: ";
                valid = false;
                while(valid != true){

                    cin>>userValue;

                    if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    valid = false;
                    cout<<"Wrong input, please select an integer: ";
                    }else{
                        valid = true;
                    }
                }
                myBST->searchNode(userValue);
            break;
            case 2: // insert
                cout<<"Enter a value to insert: ";
                valid = false;
                while(valid != true){

                    cin>>userValue;

                    if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    valid = false;
                    cout<<"Wrong input, please select an integer: ";
                    }else{
                        valid = true;
                    }
                }
                myBST->insertNode(myBST->head, userValue);
            break;
            case 3: //delete
                cout<<"Enter a value to be deleted: ";
                valid = false;
                while(valid != true){

                    cin>>userValue;

                    if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    valid = false;
                    cout<<"Wrong input, please select an integer: ";
                    }else{
                        valid = true;
                    }
                }
                myBST->deleteNode(userValue);

                if(myBST->is_Empty){
                    cout<<"The entire tree is now empty"<<endl;
                }
            break;
            case 4: // print tree
                cout<<"Descending order:"<<endl;
                myBST->printTree(myBST->root);
                cout<<endl;
            break;
            case 5: // depth of a node
                cout<<"Enter a node to be found: ";
                valid = false;
                while(valid != true){

                    cin>>userValue;

                    if(cin.fail()){
                    cin.clear();
                    cin.ignore();
                    valid = false;
                    cout<<"Wrong input, please select an integer: ";
                    }else{
                        valid = true;
                    }
                }

                if(myBST->searchNode(userValue)){
                    myBST->findDepth(userValue, myBST->head);
                }else{
                    cout<<"NO DEPTH AVAILABLE"<<endl;
                }
            break;
            case 6: // Find the cost...longest and shortest
                myBST->findCost(myBST->head);
            break;
            case 7: // check if the bst is balanced
                myBST->findHeight(myBST->head);
                myBST->head = myBST->root;
                myBST->isBalanced(myBST->head);
            break;
            case 8: // quit
                programLoop = false; // end the loop
            break;

        }

    }
}

#endif // GENERALFUNCTIONS_H_INCLUDED
