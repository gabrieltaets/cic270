#include <iostream>
#include <vector>
#include "File.h"

using namespace std;

vector<double*> vertices;	// all parsed vertices from files
vector<int*> faces;			// all parsed faces from files

// reads faces and vertices from a file
void readFile() {
	string input;
	cout << "File name: ";
	getline(cin, input);
	try {
		File f(input);
		f.readFile(); 
		vector<double*> v_list = f.getVertices();
		vector<int*> f_list = f.getFaces();
		
		// inserts the read vertices at the end of global vertices list 
		vertices.insert(vertices.cend(), v_list.begin(), v_list.end());
		
		// inserts the read faces at the end of global faces list
		faces.insert(faces.cend(), f_list.begin(), f_list.end());
		f.close();
		
		cout << v_list.size() << " vertices read.\n"
			 << f_list.size() << " faces read.\n"
			 << "File read finished.\n";
	} catch(...) {
		cout << "An error occurred while trying to read file.\nFile skipped.\n";	
	}	
}

void writeFile() {
	string input;
	cout << "File name: ";
	getline(cin, input);
	try {
		File f(input);
		f.truncate(); // discards content of selected file
		
		// writes each vertex, one by one, to file
		for(int i = 0; i < vertices.size(); i++){
			f.writeVertex(vertices[i][0], vertices[i][1], vertices[i][2]);
		}
		
		// writes each face, one by one, to file
		for(int i = 0; i < faces.size(); i++){
			f.writeFace(faces[i][0], faces[i][1], faces[i][2]);
		}
		f.close();
		cout << vertices.size() << " vertices written.\n"
			 << faces.size() << " faces written.\n"
			 << "File write complete.\n";
	} catch(...) {
		cout << "An error occurred while trying to save file.\nOperation aborted.\n";
	}
}

void discardData() {
	cout << "Are you sure? (Y/N) ";
	string input;
	getline(cin, input);
	if(input == "Y" || input == "y") {
		// frees memory from dynamically allocated arrays of vertices axes
		for(int i = 0; i < vertices.size(); i++){
			delete[] vertices[i];
		}
		vertices.clear(); // removes all vertices entries from global array
		
		// frees memory from dynamically allocated arrays of faces
		for(int i = 0; i < faces.size(); i++){
			delete[] faces[i];
		}
		faces.clear(); // removes all faces entries from global array
		cout << "Data cleared.\n";
	} else {
		cout << "Data kept.\n";
	}
}

bool menu() {
	cout << "\n[1] Read Wavefront OBJ File\n";
	cout <<   "[2] Write data to Wavefront OBJ File\n";
	cout <<   "[3] Discard data\n";
	cout <<   "[0] Exit\n";
	cout <<   "Select an option: ";
	string input;
	getline(cin, input);
	if(input == "0") return false;
	if(input == "1") readFile();
	else if(input == "2") writeFile();
	else if(input == "3") discardData();	
	else cout << "Invalid option\n\n";
	return true;
}

int main() {
	while(true) {
		if(!menu()) break;
	}
	cout << "\nBye!\n\nMade by Gabriel Taets --- 2017000959\n";
}