/*
C++ program for Huffman Coding
http://practice.geeksforgeeks.org/problems/huffman-encoding/0
http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
*/

#include <iostream>
#include <queue>
using namespace std;


 
// A Huffman tree node
struct MinHeapNode
{
    char data;                // One of the input characters
    unsigned freq;             // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
 
    MinHeapNode(char data, unsigned freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = NULL;
    }
    
    ~MinHeapNode()
    {
        delete left; left = NULL;
        delete right; right = NULL;
    }
};
 
// For comparison of two heap nodes (needed in min heap)
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};


// Prints huffman codes from the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str)
{
    if (root == NULL) return;
    // only has internal nodes with two child
    if (root->left == NULL) {
        // cout << root->data << ": " << str << "\n";
        cout<<str <<' ';
    } else {
        printCodes(root->left, str+"0");
        printCodes(root->right, str+"1");
    }
}
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(string data, int freq[], int size)
{
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    
    MinHeapNode *left, *right, *top;
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        // Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted
        // node as left and right children of this new node. Add
        // this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
 
    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
    cout<<endl;
    top = minHeap.top(); minHeap.pop();
    delete top;
}
 
/* 
// Driver program to test above functions
int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);
 
    HuffmanCodes(arr, freq, size);
 
    return 0;
} 
*/

int main() {
	int T=0;
	cin>>T;
	int freq[26];
	for (int i=0; i<T; i++) {
	    string a;
	    cin>>a;
	    int len = a.size();
	    for (int j=0; j<len; j++) {
	        cin>>freq[j];
	    }
	    HuffmanCodes(a, freq, len);
	}
	return 0;
}