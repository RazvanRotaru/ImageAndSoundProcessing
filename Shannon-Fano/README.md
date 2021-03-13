## Usage:
  * Compile ShannonFano.cpp
  * Pass a inputfile as an argument
  * Specify "-v" or "--verbose" if you want to print a detailed tree structure


## Output
  * For a file x.csv a file x_out.csv will be created with the encoded values
  * On console will be printed the total number of bits necessary for the encoding 


## Implementation details:
  * A DataContainer is firt initialized from the file
  * A ShannonFanoSolver visitor passes the DataContainer, the stages of the pass are the following:
     * A EvenlySplitter visitor creates a BST of Nodes from the input data
     * A Print visitor may pass the BST to print its contents
     * A CodeRetriever visitor passes the BST to compute the codes of each symbol
