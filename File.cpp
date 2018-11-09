/* Hello World program */
#include "File.h"
#include <sstream>

double* File::readVertices() {
    double *vertices = new double[3];
    file >> vertices[0] >> vertices[1] >> vertices[2];
    return vertices;
}

int* File::readFaces() {
    int *faces = new int[3];
    file >> faces[0] >> faces[1] >> faces[2];
    return faces;
}

File::~File() {
	
}

File::File(std::string fileName) {
	openFile(fileName);
}    

void File::openFile(std::string fileName){
    this->fileName = fileName;
    file.open(fileName.c_str(), std::fstream::in | std::fstream::out);
    // file not found or some other error
    if(!file.good()) {
    	file.close();
    	// try to create or overwrite file with trunc option
    	file.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    if(file.bad()) throw("Bad File");
}

void File::readFile() {
    if(file.bad()) throw("Bad File");
    while(!file.eof()){
        std::string next;
        
        // get the line identifier
        file >> next;
        if(next == "v") {
            verticesList.push_back(readVertices());
        } else if(next == "f") {
            facesList.push_back(this->readFaces());
        } else {
        	// ignore the rest of the line if the line does not identify a vertex or face
            while(file.peek() != '\n' && !file.eof()) file.ignore(1);
        }
    }
}

void File::append(std::string text) {
	if(file.bad()) throw("Bad File");
	// move cursor to end of file.
	file.seekp(0, std::ios_base::end);
	file << text;
	if(text[text.size()-1] != '\n') file << std::endl;
}

void File::truncate() {
	file.close();
	file.open(fileName.c_str(), std::fstream::in | std::fstream::trunc | std::fstream::out);
	if(file.bad()) throw("Bad File");
}

std::vector<double*> &File::getVertices() {
    return verticesList;
}
    
std::vector<int*> &File::getFaces() {
    return facesList;
}

void File::writeVertex(double x, double y, double z) {
	std::stringstream txt;
	txt << "v " << x << " " << y << " " << z << "\n";
	append(txt.str());
}

void File::writeFace(int v1, int v2, int v3) {
	std::stringstream txt;
	txt << "f " << v1 << " " << v2 << " " << v3 << "\n";
	append(txt.str());
}

void File::close() {
	if(file.is_open()){
		file.close();
	}
}

