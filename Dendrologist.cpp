/**
 * A testbed for an augmented implementation of an AVL tree
 * @author William Duncan, Jaylah Carter
 * @see AVLTree.h 
 * <pre>
 * Date: 99-99-9999
 * CSC 3102 Programming Project # 2
 * Instructor: Dr. Duncan 
 * </pre>
 */

#include <iostream>
#include <cstdlib>  
#include <stdexcept>
#include <iomanip>
#include <fstream> 
#include<algorithm>
#include "AVLTree.cpp"


using namespace std;


int main(int argc, char** argv) 
{
    string usage = "Dendrologist <order-code> <command-file>\n";
    usage += "  <order-code>:\n";
    usage += "  0 ordered by increasing string length, primary key, and reverse lexicographical order, secondary key\n";
    usage += "  -1 for reverse lexicographical order\n";
    usage += "  1 for lexicographical order\n";
    usage += "  -2 ordered by decreasing string\n";
    usage += "  2 ordered by increasing string\n";
    usage += "  -3 ordered by decreasing string length, primary key, and reverse lexicographical order, secondary key\n";
    usage += "  3 ordered by increasing string length, primary key, and lexicographical order, secondary key\n";  
    if (argc != 3)
    {
        cout<<usage<<endl;
        throw invalid_argument("There should be 3 command line arguments.");
    }
    //Complete the implementation of this function
    int orderCode = atoi(argv[1]);
    string fileName = argv[2];

    //validate order code
    if (orderCode < -3 || orderCode > 3 || orderCode == 0)
    {
        cout << usage << endl;
        throw invalid_argument("Invalid order-code.");
    }

    ifstream fin(fileName);
    if (!fin)
    {
        cout << usage << endl;
        throw invalid_argument("Command file does not exist.");
    }

    //create AVL tree
    AVLTree<string> tree;

    string command;
    string word;
    int flag;

    while (fin >> command)
    {
        if (command == "insert")
        {
            fin >> word;
            tree.insert(word);
            cout << "Inserted: " << word << endl;
        }

        else if (command == "delete")
        {
            fin >> word;
            tree.remove(word);
            cout << "Deleted: " << word << endl;
        }

        else if (command == "traverse")
        {
            fin >> flag;

            if (flag == -0)
            {
                cout << "In-Order Traversal:" << endl;
                tree.traverse([](string s){ cout << s << endl; });
            }
            else if (flag == -1)
            {
                cout << "Level-Order Traversal:" << endl;
                tree.levelOrder([](string s){ cout << s << endl; });
            }
            else
            {
                cout << "Parsing error" << endl;
                throw runtime_error("traverse <traversalCode>: traversalCode must be -0 or -1");
            }
        }

        else if (command == "stats")
        {
            cout << "Stats: size = " << tree.size()
                 << ", height = " << tree.height()
                 << ", diameter = " << tree.diameter()
                 << ", complete? = " << (tree.isComplete() ? "true" : "false")
                 << ", full? = " << (tree.isFull() ? "true" : "false")
                 << endl;
        }
    }

    fin.close();

    return 0;
}

