#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class disk
{
    public:
        char ch;
        unsigned int len;
        
        disk(unsigned int l, char c = '#')
        {
            len = l;
            ch = c;
        }
};

class node
{
    public:
        disk* data;
        node* next;
        
        node()
        {
            data = nullptr;
            next = nullptr;
        }
        
        node(disk* s)
        {
            data = s;
            next = nullptr;
        }
        
        void print()
        {
            for (unsigned int i=0; i<data->len; i++)
            {
                cout<< data->ch;
            }
        }
};

class Stack
{
    node* top;
    unsigned int size;
    string tag;
    public:
        Stack(string t)
        {
            top = new node();
            tag = t;
            size = 0;
        }
        Stack(node* data)
        {
            top = data;
            size = 1;
        }
        
        node* peek() const {return top;}
        unsigned int get_size() const{return size;}
        string get_tag() const {return tag;}
    
        void push(node* n)
        {
            if (size > 0)
            {    
                if (top->data->len > n->data->len)
                {
                    n->next = top;
            
                    top = n;
                }
            }
            else
            {
                top = n;
            }
            size++;
            
            
        }
        void pop()
        {
            if (size > 1)
            {
                node* temp = top;
            
                top = top->next;
            
                delete temp;
            }
            else if (size == 1)
            {
                node* temp = top;
                
                top = nullptr;
                
                delete temp;
            }
            
            size--;
        }
        
        void print()
        {
            if (size > 0)
            {
                node* temp = top;
            
                while (temp != nullptr)
                {
                    temp->print();
                    cout<< endl;
                    temp = temp->next;
                }
            }
            cout<< "______"<< tag;
        }
        
};

// ##################################
// iterative solution of ToH
// for n disks, a total of 2^n-1 moves required
vector<Stack> rods;
size_t steps = 0;

void print_scene()
{
    // print the state
    for (size_t i=0; i<3; i++)
    {
        rods[i].print();
        cout<< endl << endl;
    }
    cout<< "----------------" << endl
        << "- step " << steps << endl
        << "----------------" << endl
                              << endl;
}

void actualMovement(int from, int to)
{
    node* tobemoved = new node( rods[from].peek()->data );
    rods[from].pop();
    rods[to].push(tobemoved);
    // trivial info
    cout<< "move from"<< rods[from].get_tag() << " to" << rods[to].get_tag() << endl << endl;
}

// legal movement conditions are specified
void moveDisk(int from, int to)
{
    // move of disk between from and to
    // not necessarily from 'from' to 'to'
    
    if (rods[to].get_size() == 0 && rods[from].get_size() != 0)
        actualMovement(from, to);

    else if (rods[from].get_size() == 0 && rods[to].get_size() != 0)
        actualMovement(to, from);

    else if (rods[to].peek()->data->len > rods[from].peek()->data->len)
        actualMovement(from, to);

    else if (rods[from].peek()->data->len > rods[to].peek()->data->len)
        actualMovement(to, from);
}

void towerofhanoi(int n, int from, int to, int aux)
{
    // SOLUTION GOES HERE
    steps++;
    // if n is even swap dest and aux
    if (n % 2 == 0)
        swap(to, aux);
    for ( ; steps <= (pow(2, n) - 1); steps++)
    {
        if (steps % 3 == 1)
        {
            moveDisk(from, to);
        }
        else if (steps % 3 == 2)
        {
            moveDisk(from, aux);
        }
        else if (steps % 3 == 0)
        {
            moveDisk(aux, to);
        }
        
        print_scene();
    }
}

int main()
{
    rods.push_back(Stack(" A"));
    rods.push_back(Stack(" B"));
    rods.push_back(Stack(" C"));
    
    size_t n=3; // amount of disks
    
    for (size_t i=n; i>=1; i--)
        rods[0].push(new node(new disk(i)));
    
    print_scene();
    towerofhanoi(n, 0, 2, 1);
    /*
      n, 0, 2, 1 means
      move n disks from A to C using B
      0 = 'A'
      1 = 'B'
      2 = 'C'
    */
    return 0;
}