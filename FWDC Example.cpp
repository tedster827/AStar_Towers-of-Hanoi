#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>  /* to use exit */
using namespace std;


struct state
{
  string items;  // you may change the type to anything
  int g;
  int h;
  int f;
  bool goal;
};

vector<state> frontier;

// Displaying Frontier
void displayFrontier()
{
  for (int k = 0; k < frontier.size(); k++) {
      cout << frontier[k].items << endl;  // may have to change this
      cout << "g = " <<frontier[k].g ;
      cout << " h = " <<frontier[k].h ;
      cout << " f = " <<frontier[k].f << endl << endl;
    }
}

// Checking if the node is already in the frontier.
bool inFrontier(string items) {
  for(int i = 0; i < frontier.size(); i++) {
    if(items == frontier[i].items) {
      return true;
    }
  }
  return false;
}
// Popping function
void findNRemove(string items) {
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].items == items) {
      frontier.erase(frontier.begin()+i);
    }
  }
}

// Populates the states data
state populateState(state current)
{
  // if-then-rules to generate new safe states from current
  if (current.items == "FD||WC") {
    current.h = 2;
    current.g = 1;
    current.f = 3;
  }
  else if (current.items == "D||FWC") {
    current.h = 2;
    current.g = 2;
    current.f = 4;
  }
  else if (current.items == "FWD||C") {
    current.h = 1;
    current.g = 3;
    current.f = 4;
  }
  else if (current.items == "FDC||W") {
    current.h = 1;
    current.g = 3;
    current.f = 4;
  }
  else if (current.items == "W||FDC") {
    current.h = 2;
    current.g = 4;
    current.f = 6;
  }
  else if (current.items == "C||FWD") {
    current.h = 2;
    current.g = 4;
    current.f = 6;
  }
  else if (current.items == "FWC||D") {
    current.h = 1;
    current.g = 5;
    current.f = 6;
  }
  else if (current.items == "WC||FD") {
    current.h = 1;
    current.g = 6;
    current.f = 7;
  }
  //   if it is a goal, display success and exit now.
  else if (current.items == "FWCD||") {
    current.h = 0;
    current.g = 7;
    current.f = 7;
    current.goal = true;
  }
  return current;
}

void generate(state& current)
{
  findNRemove(current.items);
  //   if it is already in the frointer, display "Regenerated"
  //      and then display "Updated f" if f is better
  //          and also replace the old version in the frontier.
  // Otherwise, add the state to the end of frontier
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].items == current.items) {
      cout << "Regenerated State" << endl;
      if(frontier[i].f < current.f) {
        cout << "Updated f" << endl;
        current.f = frontier[i].f;
        return;
      }
    }
  }
  state addToFrontier;
  // if-then-rules to generate new safe states from current
  if (current.items == "||FWDC") {
    current.h = 0;
    current.g = 0;
    current.f = 3;
    addToFrontier.items = "FD||WC";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("||FWDC");
    return;
  }
  else if (current.items == "FD||WC") {
    current.h = 2;
    current.g = 1;
    current.f = 3;
    addToFrontier.items = "D||FWC";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("FD||WC");
    return;
  }
  else if (current.items == "D||FWC") {
    current.h = 2;
    current.g = 2;
    current.f = 4;
    addToFrontier.items = "FWD||C";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    addToFrontier.items = "FDC||W";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("D||FWC");
    return;
  }
  else if (current.items == "FWD||C") {
    current.h = 1;
    current.g = 3;
    current.f = 4;
    addToFrontier.items = "W||FDC";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("FWD||C");
    return;
  }
  else if (current.items == "FDC||W") {
    cout << "In a troubled state." << endl;
    current.h = 1;
    current.g = 3;
    current.f = 4;
    addToFrontier.items = "C||FWD";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("FDC||W");
    return;
  }
  else if (current.items == "W||FDC") {
    current.h = 2;
    current.g = 4;
    current.f = 6;
    addToFrontier.items = "FWC||D";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("W||FDC");
    return;
  }
  else if (current.items == "C||FWD") {
    current.h = 2;
    current.g = 4;
    current.f = 6;
    addToFrontier.items = "FWC||D";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("C||FWD");
    return;
  }
  else if (current.items == "FWC||D") {
    current.h = 1;
    current.g = 5;
    current.f = 6;
    addToFrontier.items = "WC||FD";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("FWC||D");
    return;
  }
  else if (current.items == "WC||FD") {
    current.h = 1;
    current.g = 6;
    current.f = 7;
    addToFrontier.items = "FWCD||";
    if(!inFrontier(addToFrontier.items)) {
      frontier.push_back(populateState(addToFrontier));
    }
    findNRemove("WC||FD");
    return;
  }
  //   if it is a goal, display success and exit now.
  else if (current.items == "FWCD||") {
    current.h = 0;
    current.g = 7;
    current.f = 7;
    current.goal = true;
    return;
  }
}

state bestofFrontier(state theBest)
{
  if(frontier.size()) {
    theBest.items = frontier[0].items;
    theBest.f = frontier[0].f;
    theBest.g = frontier[0].g;
    theBest.h = frontier[0].h;
    return theBest;
  }
  // find the best f state in the frontier, remove it, and return it
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].f < theBest.f) {
      theBest.items = frontier[i].items;
      theBest.f = frontier[i].f;
      theBest.g = frontier[i].g;
      theBest.h = frontier[i].h;
    }
  }
  return theBest;
}

// Main driver function.
int main()
{
  state current = {"||FWDC", 0, 3, 3, false};  // change as needed
  do {
      cout << ">>>Expand:" << current.items << endl;
      generate(current);
      cout << "Frontier is:" << endl;
      displayFrontier();
      current = bestofFrontier(current);
      if(current.goal) {
        cout << "Goal Reached!" << endl;
        break;
      }
    }while (!current.goal);// end while

}
