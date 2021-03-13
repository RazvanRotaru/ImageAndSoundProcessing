## Usage:
  * Compile ShannonFano.cpp
  * Pass a inputfile as an argument
  * Specify "-v" or "--verbose" if you want to print a detailed tree structure

## Details:
  * A DataContainer is firt initialized from the file
  * A EvenlySplitter visitor creates a BST of Nodes from the input data
  * A Print visitor may pass the BST to print its contents
  * A CodeRetriever visitor passes the BST to compute the codes of each symbol
