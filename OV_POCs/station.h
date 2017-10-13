#ifndef STATION_H
#define STATION_H

#include <string>
#include "object.h"
#include "dataStructs.h"
#include "store.h"

using std::string;

class Game;

class Station : public Object{
public:
	Station();
	Station(string sname); //pseudo constructor for stationProc array and other story/mission based stations

	void setupPInv(); //Setup default player inventory allocations
	void updateItem(int pos, Item it, string operation);

	void createStore(); //Create a store on this station
	void updateStore(); //Update a store on this station

	void changeCMulti(float cmult);

	float getCMulti();

	Item getItem(int pos);
	vector<Item> getItems();

	Store getStore(int pos);
	vector<Store> getStores();

private:
	//int			stSLevel; //Station Level - What is this for?
	//float		stCMulti; //Cost Multiplier

	//vector<Store> stStores; //Stores on this station
	//vector<Inventory> stPlyInv; //Player Station Inventory

};
#endif
