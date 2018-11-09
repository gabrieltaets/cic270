#ifndef FILE_H
#define FILE_H
#include <vector>
#include <string>
#include <fstream>

class File {
  private:
    std::fstream file;
    std::string fileName;
    std::vector<double*> verticesList;
    std::vector<int*> facesList;
    
    // Reads three doubles and returns them as a dynamically allocated array.
    double* readVertices();
    
    // Reads three ints and returns them as a dynamically allocated array.
	int* readFaces();
	
	// Appends the text to the end of file stream. Moves stream cursor.
	void append(std::string txt);
	
  public:
    File();
    File(std::string fileName);
    ~File();
    
    // Sets the filename and opens the file stream. DOES NOT READ THE FILE CONTENTS.
    void openFile(std::string fileName);
    
    // Reads file contents and sets vertices and faces lists.
    // Ignores any lines that don't start with either 'v' or 'f'.
    void readFile();
    
    // Clears file content.
    void truncate();
    
    // Returns all vertices read.
    std::vector<double*> &getVertices();
    
    // Returns all faces read.
    std::vector<int*> &getFaces();
    
    // Writes a formatted vertex to the end of the file.
    void writeVertex(double x, double y, double z);
    
    // Writes a formatted face to the end of the file.
    void writeFace(int v1, int v2, int v3);
    
    // Closes file stream. Not really required to call but good practice in order to properly unblock file streams.
    void close();
};

#endif