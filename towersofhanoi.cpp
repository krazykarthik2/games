#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

void spaces(int n)
{
    for (int i = 0; i < n; i++)
        cout << " ";
}
void bars(int n)
{
    for (int i = 0; i < n; i++)
        cout << "I";
}
void empty(int n)
{
    spaces(n);
    cout << "|";
    spaces(n);
}
void number(int num, int n)
{
    spaces(n - num);
    bars(2 * num + 1);
    spaces(n - num);
}
void visualize(const vector<vector<int>> &arr, const vector<int> &sp, int n)
{
    cout << endl;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sp[j] <= i)
            {
                empty(n);
            } // Empty spot
            else
            {
                number(arr[j][i], n);
            }
        }
        cout << endl;
    }
    for (int i = 0; i < 9 * n; i++)
    {
        cout << "-";
    }
    cout << endl;
}

bool moveDisk(vector<vector<int>> &arr, vector<int> &sp, int from, int to, int n)
{
    if (sp[from] == 0 || (sp[to] > 0 && arr[to][sp[to] - 1] < arr[from][sp[from] - 1]))
    {
        cout << "Invalid move!\n";
        return false;
    }
    arr[to][sp[to]] = arr[from][sp[from] - 1];
    arr[from][sp[from] - 1] = 0;
    sp[from]--;
    sp[to]++;
    return true;
}

bool checkVictory(const vector<int> &sp, int n)
{
    return sp[2] == n;
}
// Function to recursively generate the steps for Tower of Hanoi
vector<vector<int>> generatedMoves;
void doMoves(vector<vector<int>> &arr, vector<int> &sp, int n)
{
    for (int i = 0; i < generatedMoves.size(); i++)
    { // For each in generatedMoves
        vector<int> fromTo = generatedMoves[i];
        visualize(arr, sp, n);
        cout<<"moving from "<<fromTo[0]<<" to "<<fromTo[1];
        moveDisk(arr, sp, fromTo[0] - 1, fromTo[1] - 1, n);
    }
}
void generateMoves(int n, int from, int to, int aux)
{

    if (n == 1)
    {
        generatedMoves.push_back({from, to});
        return;
    }
    // Step 1: Move n-1 disks from 'from' to 'aux' using 'to' as auxiliary
    generateMoves(n - 1, from, aux, to);
    // Step 2: Move the nth disk from 'from' to 'to'
    generatedMoves.push_back({from, to});

    // Step 3: Move the n-1 disks from 'aux' to 'to' using 'from' as auxiliary
    generateMoves(n - 1, aux, to, from);
}
void listMoves(){
    for (int i = 0; i < generatedMoves.size(); i++)
    { // For each in generatedMoves
        vector<int> fromTo = generatedMoves[i];
        cout<<fromTo[0]<<"->"<<fromTo[1]<<((i== generatedMoves.size()-1)?"\n":",");
    }
}
int main()
{
    int n;
    cout << "Enter number of beads: ";
    cin >> n;
    cout << "Computer Game?[Y/N]:";
    char computerGame;
    cin >> computerGame;

    vector<vector<int>> arr(3, vector<int>(n, 0)); // Initialize towers
    vector<int> sp = {n, 0, 0};                    // Stack pointers

    // Initialize the first tower with disks
    for (int i = 0; i < n; i++)
    {
        arr[0][i] = n - i; // Largest disk at bottom
    }
    int moves = 0;
    if (computerGame == 'Y' || computerGame == 'y')
    {
        generateMoves(n, 1, 3, 2);
        doMoves(arr, sp, n);
        cout <<endl<< "Finally!" << endl;
        visualize(arr, sp, n);
        int x=1;
        for(int i=0;i<n;i++)x*=2;
        listMoves();
        cout<<"Moves:"<<(x-1)<<endl;
    }
    else
    {
        int from, to;
        while (!checkVictory(sp, n))
        {

            visualize(arr, sp, n);

            cout << "Enter move (from to): ";
            cin >> from >> to;
            cout << endl;

            if (from < 1 || from > 3 || to < 1 || to > 3 || from == to)
            {
                cout << "Invalid input. Please choose between 1, 2, or 3.\n";
                continue;
            }

            // Make the move
            if (!moveDisk(arr, sp, from - 1, to - 1, n))
            {
                cout << "Try again.\n";
            }
            else
            {
                moves++;
            }
        }
        visualize(arr, sp, n);
        cout << "Congratulations! You've solved the Tower of Hanoi!\n in under " << moves << " moves";
        int x = 1;
        for (int i = 0; i < n; i++)
            x *= 2;
        if (moves == x - 1)
            cout << "You have acheived the perfect score with the most minimal steps required\nYou are a genius";
    }
    cout<<"Author:karthikkrazy"<<endl<<"github.com/krazykarthik2";

    return 0;
}
