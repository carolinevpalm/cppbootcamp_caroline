/* Implement a single (forward) linked list for integers, your application should be able to:
• Add items to the end of the list
• Remove items from the front the list
• Print the list in the correct order
HINT:
Your application needs a loop in which it takes user’s inputs and acts on them.
Define the structure for the items in the list -- keep the head, nullify the tail and you shall be fine!
https://en.wikipedia.org/wiki/Linked_list */

#include <iostream>

/*class Node {
    int data;
    struct Node *nextp;
    Node() {
        data = 0;
        nextp = nullptr;
    } 
};*/
typedef struct Node {
    int data;
    struct Node *nextp;
}Node_t;

Node_t* findLast(Node_t *head){
    Node_t *last = head; 

    while(last->nextp != nullptr){
        last = last->nextp;
    }
    return last;
}

Node_t* addItem(Node_t *head, int value){
    if(head == nullptr){ //If list is empty
        head = new Node_t;
        head->data = value;
        head->nextp = nullptr;
    }
    else{
        Node_t *newItem = new Node_t;
        Node_t *lastItem = findLast(head);
        newItem->data = value;
        newItem->nextp = nullptr;
        lastItem->nextp = newItem;
    }
    return head;
}

Node_t* findIndexItem(Node_t *head, int index){
    Node_t *indexItem;
    if (index == 0){
        indexItem = nullptr;
    }
    else{
        indexItem = head;
        for(int x = 1; x < index; x++){
            indexItem = indexItem->nextp;
            if(indexItem->nextp == nullptr){ //If we reached the end of the list break (last item is index)
                break;
            }
        }
    }
    return indexItem;
}

Node_t* addItemToIndex(Node_t *head, int value, int index){
    if(head == nullptr){ //If list is empty
        head = new Node_t;
        head->data = value;
        head->nextp = nullptr;
        return head;
    }
    else{
        Node_t *newItem = new Node_t;
        Node_t *priorItem = findIndexItem(head, index);
        if(priorItem == nullptr){
            newItem->data = value;
            newItem->nextp = head;
            return newItem; //newItem becomes new head
        }
        else{
            Node_t *nextItem = priorItem->nextp;
            newItem->data = value;
            newItem->nextp = nextItem;
            priorItem->nextp = newItem;
            return head;
        }
    }
}

Node_t* removeFirstItem(Node_t *head){
    if(head == nullptr){
        return head;
    }
    else{
        Node_t *newHead = head->nextp;
        delete head;
        head = nullptr;
        return newHead;
    }
}

Node_t* removeAllItems(Node_t *head){
    if(head == nullptr){
        return head;
    }
    else{
        Node_t *current = head;
        while(current->nextp != nullptr){
            current = removeFirstItem(current);
        }
        delete current;
        current = nullptr;
        return current;
    }
}

Node_t* removeIndexItem(Node_t *head, int index){
    if(index == 0){
        head = removeFirstItem(head);
    }
    else{
        Node_t *priorItem = findIndexItem(head, index);
        Node_t *removeItem = priorItem->nextp;
        // If item to remove is last, just delete. otherwise redirect first
        if (removeItem->nextp == nullptr){
            priorItem->nextp = nullptr;
            delete removeItem;
            removeItem = nullptr;
        }
        else{
            Node_t *nextItem = removeItem->nextp;
            priorItem->nextp = nextItem;
            delete removeItem;
            removeItem = nullptr;
        }
    }
    return head;
}

void print(Node_t *head){
    if(head == nullptr){
        std::cout << "List is empty!" << std::endl;
    }
    else{
        Node_t *current = head;
        while(current->nextp != nullptr){
            std::cout << current->data << std::endl;
            current = current->nextp;
        }
        std::cout << current->data << std::endl;
    }
}

bool doStuffToList(Node_t **head){
    bool ret = true;
    int selection;
    std::cout << "\nWhat do you want to do to your list?" 
                "\n1. Add a value"
                "\n2. Add a value to index"
                "\n3. Remove first value"
                "\n4. Remove value from index"
                "\n5. Delete list and exit" << std::endl;
    std::cout << "Input action: ";
    std::cin >> selection;
    if (selection == 1){
        std::cout << "Enter value to add to your list: ";
        int value;
        std::cin >> value;
        *head = addItem(*head, value);
        std::cout << "\n--- This is your list: ---" << std::endl;
        print(*head);
        return true;
    }
    else if (selection == 2){
        std::cout << "Enter value to add to your list: ";
        int value;
        std::cin >> value;
        std::cout << "Enter index to add your value: ";
        int index;
        std::cin >> index;
        *head = addItemToIndex(*head, value, index);
        std::cout << "\n--- This is your list: ---" << std::endl;
        print(*head);
        return true;
    }
    else if (selection == 3){
        *head = removeFirstItem(*head);
        std::cout << "\n--- This is your list: ---" << std::endl;
        print(*head);
        return true;
    }
    else if (selection == 4){
        std::cout << "Enter index to remove: ";
        int index;
        std::cin >> index;
        *head = removeIndexItem(*head, index);
        std::cout << "\n--- This is your list: ---" << std::endl;
        print(*head);
        return true;
    }
    else if (selection == 5){
        *head = removeAllItems(*head);
        std::cout << "\n--- This is your list: ---" << std::endl;
        print(*head);
        std::cout << "\nGoodbye!" << std::endl;
        return false;
    }   
}

int main(){

    Node *MyList = nullptr; //initialize linked list
    /*MyList = addItem(MyList, 1);
    MyList = addItem(MyList, 2);
    MyList = addItem(MyList, 3);
    MyList = addItem(MyList, 4);
    MyList = addItem(MyList, 5);
    
    print(MyList);
    std::cout << "----------\n\n";
    MyList = addItemToIndex(MyList,100,2);
    
    print(MyList);
    std::cout << "----------\n\n";

    MyList = removeIndexItem(MyList,2);
    print(MyList);
    std::cout << "----------\n\n";

    MyList = removeIndexItem(MyList,0);
    print(MyList);
    std::cout << "----------\n\n";

    MyList = removeAllItems(MyList);*/

    bool run = true;
    while(run){
        run = doStuffToList(&MyList);
    };

    return 0;
}


