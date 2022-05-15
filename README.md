# Implement Huffman coding and decoding algorithms.
Name: Ram Chandra Jangir

Roll Number : CS21M517

Registered Mail ID: contactjangir@gmail.com



**How to compile and run the program:**


**Step-1 :**

Clone this project using below command and you will get below list of files.

       git clone https://github.com/contactjangir/huffman.git

       cd huffman

       huffman$ tree
	.
	├── huffman
	├── huffman.c
	├── Makefile
	├── output.txt
	└── README.md

0 directories, 5 files



**Step-2 :**

It is already having a precompiled binary huffman which can be run directly on Ubuntu system.

OR

**How to compile**

	huffman$ make
	gcc -o huffman huffman.c




**Step-3 :**

**How to run this program:**

	huffman$ ./huffman

	Please choose the function by input 1-4

 	  1.Build the Huffman tree
 
 	  2.Encode
 
	  3.Decode
 
 	  4.Exit
 
	Enter your choice: 1

 	Building the Huffman tree
 
	How many element would you like to use : 6

	Please input the 1 th element : a

	Please input the frequency of  1 th element : 5

	Please input the 2 th element : b

	Please input the frequency of  2 th element : 9

	Please input the 3 th element : c

	Please input the frequency of  3 th element : 12

	Please input the 4 th element : d

	Please input the frequency of  4 th element : 13

	Please input the 5 th element : e

	Please input the frequency of  5 th element : 16

	Please input the 6 th element : f

	Please input the frequency of  6 th element : 45

	Done!!! The Huffman tree has been built

	Please choose the function by input 1-4
 
 	  1.Build the Huffman tree
 
 	  2.Encode
 
 	  3.Decode
 
 	  4.Exit

	Enter your choice: 2

	Output of Huffman Coding

	f: 0

	c: 100

	d: 101

	a: 1100

	b: 1101

	e: 111

	Please choose the function by input 1-4

	  1.Build the Huffman tree

	  2.Encode

	  3.Decode

	  4.Exit

	Enter your choice: 3

	Please input the message (0 or 1),ending with # 010010111001101111#

	Decrypted output the Huffman coding is as following: fcdabe

	Please choose the function by input 1-4

	  1.Build the Huffman tree

	  2.Encode

	  3.Decode

	  4.Exit

	  Enter your choice: 4

	huffman$

