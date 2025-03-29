#include "myQueue.h"
#include "myList.h"
#include <iostream>
#include <random>
#include "polinom.h"
#include "commonHeader.h"
#include "unsortedArray.h"
#include "sortedArray.h"
#include "myHashTable.h"
#include "myAVLtree.h"
#include <string>

int main() {
    unsortedArray<polinom> unsortedTable;
    sortedArray<polinom> sortedTable;
    AVLtree<polinom> treeTable;
    myHashTable<polinom> hashTable;
    Data<polinom> data;

    std::string str;
    char c = 0;
    std::cout << "Hello! " << std::endl;
    while (c != 'q') {
        std::cout << "Type 'f' for find, 'i' for insert, 'd' for delete, 'q' for quit" << std::endl;
        std::cin >> c;
        switch (c)
        {
        case 'f':
            try {
                std::cout << "Enter the key: " << std::endl;
                std::cin >> str;

                data = unsortedTable.find(stringToMyvec(str));
                std::cout << std::endl << "Unsorted array: " << std::endl;
                if (data.key.size() != 0) std::cout << "Data is: " << data.pol << std::endl;
                else std::cout << "There is no data with this key " << std::endl;
                std::cout << "Count of operations: " << unsortedTable.operationsCount << std::endl;

                data = sortedTable.find(stringToMyvec(str));
                std::cout << std::endl << "Sorted array: " << std::endl;
                if (data.key.size() != 0) std::cout << "Data is: " << data.pol << std::endl;
                else std::cout << "There is no data with this key " << std::endl;
                std::cout << "Count of operations: " << sortedTable.operationsCount << std::endl;

                data = treeTable.find(stringToMyvec(str));
                std::cout << std::endl << "AVL tree: " << std::endl;
                if (data.key.size() != 0) std::cout << "Data is: " << data.pol << std::endl;
                else std::cout << "There is no data with this key " << std::endl;
                std::cout << "Count of operations: " << treeTable.operationsCount << std::endl;

                data = hashTable.find(stringToMyvec(str));
                std::cout << std::endl << "Hash table: " << std::endl;
                if (data.key.size() != 0) std::cout << "Data is: " << data.pol << std::endl;
                else std::cout << "There is no data with this key " << std::endl;
                std::cout << "Count of operations: " << hashTable.operationsCount << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "An exception was caught: " << e.what() << std::endl;
            }
            break;
        case 'i':
            try {
                std::cout << "Enter the key: " << std::endl;
                std::cin >> str;
                data.key = stringToMyvec(str);
                std::cout << "To generate polinom type 'g', to enter it manually type 'm': " << std::endl;
                std::cin >> c;
                switch (c)
                {
                case 'g':
                    data.pol = generatePolinom();
                    std::cout << "Generated polinom: " << std::endl << data.pol << std::endl;
                    break;
                case 'm':
                    std::cout << "Enter polinom: " << std::endl;
                    std::cin >> data.pol;
                    break;
                default:
                    std::cout << "Unknown command, generating polinom automatically: " << std::endl;
                    data.pol = generatePolinom();
                    std::cout << "Generated polinom: " << std::endl << data.pol << std::endl;
                    break;
                }

                unsortedTable.ins(data);
                std::cout << std::endl << "Unsorted array: " << std::endl;
                std::cout << "Count of operations: " << unsortedTable.operationsCount << std::endl;

                sortedTable.ins(data);
                std::cout << std::endl << "Sorted array: " << std::endl;
                std::cout << "Count of operations: " << sortedTable.operationsCount << std::endl;

                treeTable.ins(data);
                std::cout << std::endl << "AVL tree: " << std::endl;
                std::cout << "Count of operations: " << treeTable.operationsCount << std::endl;

                hashTable.ins(data);
                std::cout << std::endl << "Hash table: " << std::endl;
                std::cout << "Count of operations: " << hashTable.operationsCount << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "An exception was caught: " << e.what() << std::endl;
            }
            break;
        case 'd':
            try {
                std::cout << "Enter the key: " << std::endl;
                std::cin >> str;

                unsortedTable.del(stringToMyvec(str));
                std::cout << std::endl << "Unsorted array: " << std::endl;
                std::cout << "Count of operations: " << unsortedTable.operationsCount << std::endl;

                sortedTable.del(stringToMyvec(str));
                std::cout << std::endl << "Sorted array: " << std::endl;
                std::cout << "Count of operations: " << sortedTable.operationsCount << std::endl;

                treeTable.del(stringToMyvec(str));
                std::cout << std::endl << "AVL tree: " << std::endl;
                std::cout << "Count of operations: " << treeTable.operationsCount << std::endl;

                hashTable.del(stringToMyvec(str));
                std::cout << std::endl << "Hash table: " << std::endl;
                std::cout << "Count of operations: " << hashTable.operationsCount << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "An exception was caught: " << e.what() << std::endl;
            }
            break;
        case 'q':
            std::cout << "quitting..." << std::endl;
            break;
        default:
            std::cout << "Unknown command, qutting..." << std::endl;
            break;
        }
    }
    
	return 0;
}