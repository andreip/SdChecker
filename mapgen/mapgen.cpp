#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../Constants.h"

using namespace std;

class Coord {
	float latitude;
	float longitude;

  public:
  	Coord() {
  		latitude = 0;
			longitude = 0;
  	}

		Coord(float latitude, float longitude) {
			this->latitude = latitude;
			this->longitude = longitude;
		}

		Coord(string scoord) {
			this->longitude = stof(scoord.substr(0, scoord.find(" ")));
			this->latitude = stof(scoord.substr(scoord.find(" ")));
		}

	friend std::ostream& operator<< (std::ostream& out, const Coord& z);
};

ostream& operator<<(ostream& out, const Coord& z){
	out << "new google.maps.LatLng("<<z.latitude<<","<<z.longitude<<")";
	return out;
}

void copyFile(ifstream& input, ofstream& output){
	string buffer;
	while (getline(input, buffer)) {
	    output << buffer << '\n';
	}
}

string make_filename( const string& basename, int index, const string& ext )
{
  ostringstream result;
  result << basename << index << ext;
  return result.str();
}

void generateMap(int count, vector<Coord>& stores, vector<Coord>& users, vector<Coord>& newStores) {

	if (newStores.size()<count) {
		cout<<"Error: could not find a new store for the new story query no. "<<count<<endl;
		return;
	}

	ifstream part;
	ofstream map;
	map.open(make_filename("map", count, ".html"));

	part.open("parts/1.html");
	copyFile(part, map);
	part.close();

	for (int i=0; i<stores.size(); i++)
		map<<stores[i]<<","<<endl;

	part.open("parts/2.html");
	copyFile(part, map);
	part.close();

	map<<newStores[count]<<","<<endl;

	part.open("parts/3.html");
	copyFile(part, map);
	part.close();

	for (int i=0; i<users.size(); i++)
		map<<users[i]<<","<<endl;

	part.open("parts/4.html");
	copyFile(part, map);
	part.close();

	map.close();

}

int main() {

	vector<Coord> stores;
	vector<Coord> users;
	vector<Coord> newStores;
	int T, opCode = 0;
	int count = 0;

	// read newStoreCoords
  ifstream newCoords;
	newCoords.open("../newStoreCoords.txt");
	float newLat, newLong;
	while(newCoords>>newLat>>newLong) {
		newStores.push_back(Coord(newLat, newLong));
	}
	newCoords.close();

	// read input
	string buffer;
	while (getline(cin, buffer)) {
			cout<<buffer<<endl;
			opCode = stoi(buffer.substr(0, buffer.find_first_of(" \n")));
			if  (opCode == ADD_USER) {
				buffer = buffer.substr(2);
				buffer = buffer.substr(buffer.find(" ")+1);
				users.push_back(Coord(buffer));
			} else if (opCode == ADD_STORE) {
				buffer = buffer.substr(2);
				buffer = buffer.substr(buffer.find(" ")+1);
				stores.push_back(Coord(buffer));
			} else if (opCode == NEW_STORE_COORDINATES) {
				generateMap(++count, stores, users, newStores);
			}
	}

	return 0;
}
