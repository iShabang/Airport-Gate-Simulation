/*Shannon Montoya-Curtin
 * Data class and heap class used for the airport simulation
 * Data class holds all of the information found in an event
 * heap class holds all the functions for the heap data structure 
 * used for data processing. Comparison operators are overloaded for the Data
 * class for easier readability. 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Data{
public:
	int time;
	bool type;
	std::string origin;
	std::string destination;
	int flightNumber;
	int gateNumber;
	Data() : time(0), type(0), origin(""), destination(""), flightNumber(0),
			 gateNumber(0) {}
	Data(int t,bool ty,string o,string d, int f, int g){
		time = t;
		type = ty;
		origin = o;
		destination = d;
		flightNumber = f;
		gateNumber = g;
	}
	bool operator < (Data a){
		return(time < a.time);
	}
	bool operator > (Data a){
		return(time > a.time);
	}
	bool operator <= (Data a){
		return(time <= a.time);
	}
	bool operator >= (Data a){
		return(time >= a.time);
	}
	bool operator == (Data a){
		return(time == a.time);
	}
	void display(){
		cout << "Time: " << time << endl;
		cout << "Type: ";
		if(type) cout << "Departure" << endl;
		else cout << "Arrival" << endl;
		cout << "From: " << origin << endl;
		cout << "Destination: " << destination << endl;
		cout << "Flight Number: " << flightNumber << endl;
		cout << "Gate Number: " << gateNumber << endl;

	}
	friend ostream& operator << (ostream& output, Data &a);
};

template <class type>
class heap{
public:
	heap(int size){
		list.resize(size+1);
		listSize = 0;
	}
	void display(){
		for(int i=1;i<listSize;i++){
			cout << i << ": " << list[i].time << endl;	
		}
	}
	void insert(type  x){
		//cout << "inserting " << x << " into heap" << endl;
		if(isEmpty()){
			list[1] = x;
			listSize++;
		}
		else{
			if(listSize == list.size()-1)
				list.resize(list.size() * 2);
			int hole = ++listSize;
			list[0] = x;
			for(;x<list[hole/2];hole/=2){
				swap(list[hole],list[hole/2]);
			}	
			for(;x==list[hole/2];hole/=2){
				swap(list[hole],list[hole/2]);
			}
			swap(list[hole],list[0]);	
		}
	}
	type deleteMin(){
		type temp = list[1];
		type x = list[listSize];
		listSize--;
		int hole = 1;
		int tempHole;
		if(x < list[hole*2] && x < list[hole*2 + 1]){
				list[hole] = x;
		}
		else{
			for(;x>list[hole*2] or x>list[hole*2 + 1];){
				//cout << "swapping " << hole << " with " << small(hole) << endl;
				tempHole = small(hole);	
				swap(list[hole],list[small(hole)]);
  				if(small(hole)*2 > listSize && small(hole)*2 +1 > listSize){
					break;
				}
				hole = tempHole;
			}
			//cout << tempHole << " gets x" << endl;
			list[tempHole] = x;
		}
		return temp;	
	}
	int small(int hole){
		if(hole*2 <= listSize && hole*2+1 <= listSize){
			if(list[hole*2] < list[hole*2+1])
				return hole*2;
			else
				return hole*2+1;
		}	
		if(hole*2 <= listSize){
			return hole*2;
		}
	}
	void updateSize(){
		listSize++;
	}
	bool isEmpty(){return(listSize==0);}
	int size(){return (listSize);}
	type& operator[](int position){return list[position];}
private:
	vector<type> list;	
	int listSize;
	int maxSize;
};

ostream& operator << (ostream& output, Data &a){

		output << "Time: " << a.time << endl;
		output << "Type: ";
		if(a.type) output << "Departure" << endl;
		else output << "Arrival" << endl;
		output << "From: " << a.origin << endl;
		output << "Destination: " << a.destination << endl;
		output << "Flight Number: " << a.flightNumber << endl;
		output << "Gate Number: " << a.gateNumber << endl;
		return output;
}


