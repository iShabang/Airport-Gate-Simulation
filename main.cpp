/*Shannon Montoya Curtin
 * Main Program implementing the algorithm for airport simulation. The main function uses a while loop to continuously
 * process the data and outputs a message when the airport is full. The heap data structure is used to hold all of the events and
 * the delete min function is used for processing the top element before putting it back into the stack. 
 */
#include <iostream>
#include <iomanip>
#include "heap.h"
#include "myStack.h"
#include <time.h>
#include <cstdlib>

using namespace std;


void createData(Data*& dataArray, int time, int &flightNum){
	dataArray = new Data[14];
	Data d1(2+(time*60),0,"LAX","JFK",flightNum++,0);
	Data d2(3+(time*60),0,"SMF","RDU",flightNum++,0);
	Data d3(4+(time*60),0,"IAH","MSP",flightNum++,0);
	Data d4(9+(time*60),0,"ABQ","ATL",flightNum++,0);
	Data d5(11+(time*60),0,"SJC","BOS",flightNum++,0);
	Data d6(14+(time*60),0,"PHX","MIA",flightNum++,0);
	Data d7(17+(time*60),0,"SFO","ORD",flightNum++,0);
	Data d8(19+(time*60),0,"SLC","AUS",flightNum++,0);
	Data d9(28+(time*60),0,"TUL","ONT",flightNum++,0);
	Data d10(33+(time*60),0,"LAS","DCA",flightNum++,0);
	Data d11(37+(time*60),0,"BNA","SEA",flightNum++,0);
	Data d12(44+(time*60),0,"MAF","AMA",flightNum++,0);
	Data d13(49+(time*60),0,"HOS","DEN",flightNum++,0);
	Data d14(55+(time*60),0,"ELP","MEM",flightNum++,0);
		
	dataArray[0] = d1;
	dataArray[1] = d2;
	dataArray[2] = d3;
	dataArray[3] = d4;
	dataArray[4] = d5;
	dataArray[5] = d6;
	dataArray[6] = d7;
	dataArray[7] = d8;
	dataArray[8] = d9;
	dataArray[9] = d10;
	dataArray[10] = d11;
	dataArray[11] = d12;
	dataArray[12] = d13;
	dataArray[13] = d14;
}

void setupStack(myStack<int>& gateStack,int& stackSize){
	for(int i=stackSize; i>0; i--)
		gateStack.push(i);
}

string randomDelayType(){
	int test = (1 + rand() % (5));
	switch(test){
		case 1: return "weather";
		case 2: return "waiting for baggage";
		case 3:	return "mechanical issues";
		case 4: return "airtraffic congestion";
		case 5: return "security issues";
	}
}

int randomDelayTime(){ return(20 + rand() % (40 - 20 + 1)); }

bool delayChance(){
	int test = (1 + rand() % 100);
	if(test <= 100 && test >= 60 )return true;
	else return false;
}

void processData(heap<Data>& theHeap,myStack<int>& gateStack){
	Data current = theHeap.deleteMin();
	if(!current.type){
		current.type = 1;
		current.gateNumber = gateStack.pop();
		cout << "Flight #" << current.flightNumber << " arrived from " << current.origin << " Gate Number:  " << current.gateNumber << " Time: " << current.time << endl;
		current.time += 60;
		if(delayChance()){
			cout << "Flight #" << current.flightNumber << " has been delayed due to " << randomDelayType() << endl;
			current.time = current.time + randomDelayTime();
		}
		theHeap.insert(current);
	}
	else{
		cout << "Flight #" << current.flightNumber << " departed to " << current.destination << " Gate Number:  " << current.gateNumber << " Time: " << current.time << endl;
		gateStack.push(current.gateNumber);
	}
	
}


int main(){
	cout << "Airport Simulator" << endl;
	srand(time(NULL));	
	Data* dataArray;
	heap<Data> theHeap(14);
	int time = 0;
	int fullDay = 24;
	int stackSize = 0;
	int flightsPerHour = 14;
	int flights = 0;
	int flightNum = 1000;
	//int temp;
	cout << "Please enter number of gates: "; cin >> stackSize;
	myStack<int> gateStack(stackSize);
	setupStack(gateStack,stackSize);
	//createData(dataArray,time,flightNum);
	//cout << "3" << endl;
	for(;time<fullDay;time++){
	//	cout << "main loop started with time " << time << endl;
		createData(dataArray,time,flightNum);
		for(int i=0;i<flightsPerHour;i++){
			theHeap.insert(dataArray[i]);		
		}
		while(!gateStack.isEmpty() && flights <= theHeap.size()){
	//		cout << "processing data. " << flights << " / " << theHeap.size() << endl;
			processData(theHeap,gateStack);
			flights++;
//			cin >> temp;
		}
		if(gateStack.isEmpty()){
			cout << "Airport Full" << endl;
			return 0;
		}
		flights = 0;
//		delete[] dataArray;	
	}	
	cout << "simulation completed!" << endl;
	cout << "time = " << time << endl;
	delete[] dataArray;	
	return 0;
}
