// Implement Huffman coding and decoding algorithms.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// calculating height of Huffman Tree
#define MAX_TREE_HEIGHT 100

// A Huffman tree node
struct min_heap_node
{

  // input character
  char data;

  // frequency of the input character
  unsigned freq;

  // Left and right child of this node
  struct min_heap_node *left, *right;
};

// A Min Heap: Collection of min-heap (or Huffman tree) nodes
struct min_heap
{

  // Current size of min heap
  unsigned size;

  // capacity of min heap
  unsigned capacity;

  // Array of minheap node pointers
  struct min_heap_node **array;
};

// function to allocate a new min heap node with given character
// and frequency of the character
struct min_heap_node *
new_node (char data, unsigned freq)
{
  struct min_heap_node *temp =
    (struct min_heap_node *) malloc (sizeof (struct min_heap_node));

  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;

  return temp;
}

// function to create a min heap of given capacity
struct min_heap *
create_min_heap (unsigned capacity)
{

  struct min_heap *minHeap =
    (struct min_heap *) malloc (sizeof (struct min_heap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array =
    (struct min_heap_node **) malloc (minHeap->capacity *
				    sizeof (struct min_heap_node *));
  return minHeap;
}

// function to swap two min heap nodes
void
swapMinHeapNode (struct min_heap_node **a, struct min_heap_node **b)
{

  struct min_heap_node *t = *a;
  *a = *b;
  *b = t;
}

// The minHeapify function.
void
minHeapify (struct min_heap *minHeap, int idx)
{

  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size
      && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size
      && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx)
    {
      swapMinHeapNode (&minHeap->array[smallest], &minHeap->array[idx]);
      minHeapify (minHeap, smallest);
    }
}

// function to check if size of heap is 1 or not
int
isSizeOne (struct min_heap *minHeap)
{

  return (minHeap->size == 1);
}

// function to extract minimum value node from heap
struct min_heap_node *
extractMin (struct min_heap *minHeap)
{

  struct min_heap_node *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify (minHeap, 0);

  return temp;
}

// function to insert a new node to Min Heap
void
insert_min_heap (struct min_heap *minHeap, struct min_heap_node *minHeapNode)
{

  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {

      minHeap->array[i] = minHeap->array[(i - 1) / 2];
      i = (i - 1) / 2;
    }

  minHeap->array[i] = minHeapNode;
}

// function to build min heap
void
build_min_heap (struct min_heap *minHeap)
{

  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify (minHeap, i);
}

// function to print an array of size n
void
printArr (int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf ("%d", arr[i]);

  printf ("\n");
}

// function to check if this node is leaf
int
isLeaf (struct min_heap_node *root)
{

  return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct min_heap *
create_and_build_min_heap (char data[], int freq[], int size)
{

  struct min_heap *minHeap = create_min_heap (size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = new_node (data[i], freq[i]);

  minHeap->size = size;
  build_min_heap (minHeap);

  return minHeap;
}

// function to build Huffman tree
struct min_heap_node *
build_huffman_tree (char data[], int freq[], int size)
{
  struct min_heap_node *left, *right, *top;

  // Step 1: Create a min heap of capacity
  // equal to size. Initially, there are
  // modes equal to size.
  struct min_heap *minHeap = create_and_build_min_heap (data, freq, size);

  // Iterate while size of heap doesn't become 1
  while (!isSizeOne (minHeap))
    {

      // Step 2: Extract the two minimum
      // freq items from min heap
      left = extractMin (minHeap);
      right = extractMin (minHeap);

      // Step 3: Create a new internal
      // node with frequency equal to the
      // sum of the two nodes frequencies.
      // Make the two extracted node as
      // left and right children of this new node.
      // Add this node to the min heap
      // '$' is a special value for internal nodes, not used
      top = new_node ('$', left->freq + right->freq);

      top->left = left;
      top->right = right;

      insert_min_heap (minHeap, top);
    }

  // Step 4: The remaining node is the
  // root node and the tree is complete.
  return extractMin (minHeap);
}

// function to print huffman codes from the root of Huffman Tree.
void
printCodes (struct min_heap_node *root, int arr[], int top)
{

  // Assign 0 to left edge and recur
  if (root->left)
    {

      arr[top] = 0;
      printCodes (root->left, arr, top + 1);
    }
  // Assign 1 to right edge and recur
  if (root->right)
    {

      arr[top] = 1;
      printCodes (root->right, arr, top + 1);
    }
  // If this is a leaf node, then
  // it contains one of the input
  // characters, print the character
  // and its code from arr[]
  if (isLeaf (root))
    {

      printf ("%c: ", root->data);
      printArr (arr, top);
    }
}

void
decode_huffman (struct min_heap_node *root, char s[])
{
  char ans[1000];
  int k = 0;
  struct min_heap_node *curr = root;
  for (int i = 0; i < strlen (s); i++)
    {
      if (s[i] == '0')
	curr = curr->left;
      else
	curr = curr->right;

      // reached leaf node
      if (curr->left == NULL && curr->right == NULL)
	{
	  ans[k] = curr->data;
	  k++;
	  curr = root;
	}
    }
  printf ("\nDecrypted output the Huffman coding is as following: ");
  printf ("%s", ans);
}

int
main ()
{

  int arr[MAX_TREE_HEIGHT], top = 0;

  char input[100];
  int freq[100];

  struct min_heap_node *root;

  int size;

  while (1)
    {
      printf ("\nPlease choose the function by input 1-4");
      printf ("\n 1.Build the Huffman tree");
      printf ("\n 2.Encode");
      printf ("\n 3.Decode");
      printf ("\n 4.Exit");
      int c;
      printf ("\nEnter your choice: ");
      scanf ("%d", &c);

      if (c == 1)
	{
	  printf ("\n Building the Huffman tree");
	  printf ("\nHow many element would you like to use : ");
	  scanf ("%d", &size);
	  for (int i = 0; i < size; i++)
	    {
	      printf ("\nPlease input the %d th element : ", i + 1);
	      scanf (" %c", &input[i]);
	      printf ("\nPlease input the frequency of  %d th element : ",
		      i + 1);
	      scanf ("%d", &freq[i]);
	    }
	  root = build_huffman_tree (input, freq, size);
	  printf ("\nDone!!! The Huffman tree has been built\n");
	}
      else if (c == 2)
	{
	  printf ("Output of Huffman Coding \n");
	  printCodes (root, arr, top);
	}
      else if (c == 3)
	{
	  printf ("\nPlease input the message (0 or 1),ending with # ");
	  char p[100];
	  scanf ("%s", p);
	  decode_huffman (root, p);
	}
      else if (c == 4)
	{
	  break;
	}
    }

  return 0;
}
