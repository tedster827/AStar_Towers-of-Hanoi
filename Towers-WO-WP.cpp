#include <iostream>
#include <vector>
#include <string>

using namespace std;

// This is the univerisal State Struct for all the states in the Towers of Hanoi
struct State {
  string peg1;
  string peg2;
  string peg3;
  int g;
  int h;
  int f;
  bool goal;
};

// This is the State vector holding all of the nodes found in the frontier
vector<State> frontier;

//  h (x)= (the total number of disks of left and middle poles) + 2*（number of disks that in the right pole and smaller than any disk that in left or middle poles）.
int hValue(string p1, string p2, string p3) {
  vector<char> findings;
  int h = 0;
  // If peg 1 isn't empty search for rings
  if(p1 != "0") {
    for(int i = 0; i < p1.length(); i++) {
      if(p1[i] == 'T' || p1[i] == 'M' || p1[i] == 'B') {
        findings.push_back(p1[i]);
        h = h + 1;
      }
    }
  }
  // If peg 2 isn't empty search for rings
  if(p2 != "0") {
    for(int i = 0; i < p2.length(); i++) {
      if(p2[i] == 'T' || p2[i] == 'M' || p2[i] == 'B') {
        findings.push_back(p2[i]);
        h = h + 1;
      }
    }
  }
  // If peg 2 isn't empty search for rings that are smalller than rings on the first and center pegs.
  if(p3 != "0") {
    if(p3[0] == 'T') {
      for(int i = 0; i < findings.size(); i++) {
        if(findings[i] == 'M' || findings[i] == 'B') {
          h = h + 2;
        }
      }
    }
    else if(p3[0] == 'M') {
      for(int i = 0; i < findings.size(); i++) {
        if(findings[i] == 'B') {
          h = h + 2;
        }
      }
    }
  }
  return h;
}

// Optional display function for states
void displayState(State toDisplay) {
  cout << toDisplay.peg1 << " ";
  cout << toDisplay.peg2 << " ";
  cout << toDisplay.peg3 << " " << endl;
  cout << "g: " << toDisplay.g << " ";
  cout << "h: " << toDisplay.h << " ";
  cout << "f: " << toDisplay.f << endl;
  if(toDisplay.goal) {
    cout << "Goal: Yes" << endl;
    return;
  }
  cout << "Goal: No" << endl;
}

// Displaying Frontier
void displayFrontier()
{
  for (int k = 0; k < frontier.size(); k++) {
      if(frontier[k].goal) {
        cout << "Goal State In Frontier!" << endl;
      }
      cout << frontier[k].peg1 << " ";
      cout << frontier[k].peg2 << " ";
      cout << frontier[k].peg3 << " ";
      cout << "| g = " <<frontier[k].g ;
      cout << " h = " <<frontier[k].h ;
      cout << " f = " <<frontier[k].f << endl << endl;
    }
}

// Checking if the node is already in the frontier.
bool inFrontier(string p1, string p2, string p3) {
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].peg1 == p1 && frontier[i].peg2 == p2 && frontier[i].peg3 == p3) {
      return true;
    }
  }
  return false;
}

// Popping function
void findNRemove(string p1, string p2, string p3) {
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].peg1 == p1 && frontier[i].peg2 == p2 && frontier[i].peg3 == p3) {
      frontier.erase(frontier.begin()+i);
    }
  }
}

void generate(State& current)
{
  findNRemove(current.peg1, current.peg2, current.peg3);
  //   if it is already in the frointer, display "Regenerated"
  //      and then display "Updated f" if f is better
  //          and also replace the old version in the frontier.
  // Otherwise, add the state to the end of frontier
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].peg1 == current.peg1 && frontier[i].peg2 == current.peg2 && frontier[i].peg3 == current.peg3) {
      cout << "Regenerated State" << endl;
      if(frontier[i].f < current.f) {
        cout << "Updated f" << endl;
        current.f = frontier[i].f;
        return;
      }
    }
  }
  State addToFrontier;
  addToFrontier.goal = false;
  // if-then-rules to generate new safe states from current
  // Each if / else if statement follows the same format so please treat this commment as the detail of all if / if else statements
  // The conidtion is checking to see what state it's in by checking the peg strings.
  // These if / if else statement act as a knowledgebase for all the possible configerations of the towers.
  // Each time a new node is seen the hValue function will calcuation it's value.
  // It will also check to see if the expansion has a new vector not in the frontier and add to the frontier vector
  // Comments are also listed for Transitions of states.
  if(current.peg1 == "TMB" && current.peg2 == "0" && current.peg3 == "0") {
    current.g = 1;
    current.h = hValue("TMB", "0", "0");
    current.f = current.h + current.g;
    addToFrontier.peg1 = "MB";
    addToFrontier.peg2 = "T";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 2;
                    // 2 - T To Center
    addToFrontier.h = hValue("MB", "T", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "MB";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "T";
    addToFrontier.g = 2;
                    // 2 -T To End
    addToFrontier.h = hValue("MB", "0", "T");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("TMB", "0", "0");
    return;
  }
  else if(current.peg1 == "MB" && current.peg2 == "0" && current.peg3 == "T") {
    current.g = 2;
    current.h = hValue("MB", "0", "T");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "B";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "T";
    addToFrontier.g = 3;
                    // 3 - M To Center
    addToFrontier.h = hValue("B", "M", "T");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("MB", "0", "T");
    return;
  }
  else if(current.peg1 == "B" && current.peg2 == "M" && current.peg3 == "T") {
    current.g = 3;
    current.h = hValue("B", "M", "T");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "B";
    addToFrontier.peg2 = "TM";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 4;
                    // 4 - T To Center
    addToFrontier.h = hValue("B", "TM", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 4;
                    // < 4 - T To First
    addToFrontier.h = hValue("TB", "M", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("B", "M", "T");
    return;
  }
  else if(current.peg1 == "B" && current.peg2 == "TM" && current.peg3 == "0") {
    current.g = 4;
    current.h = hValue("B", "TM", "0");
    current.f = current.g + current.f;
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TM";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 5;
                    // 5 - B To End
    addToFrontier.h = hValue("0", "TM", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 5;
                    // < 5 - T To First
    addToFrontier.h = hValue("TB", "M", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("B", "TM", "0");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "TM" && current.peg3 == "B") {
    current.g = 5;
    current.h = hValue("0", "TM", "B");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 6;
                    // 6 - T To First \ | /
    addToFrontier.h = hValue("T", "M", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "TB";
    addToFrontier.g = 7;
                    // 6 - T To End>
    addToFrontier.h = hValue("0", "M", "TB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("0", "TM", "B");
    return;
  }
  else if(current.peg1 == "T" && current.peg2 == "M" && current.peg3 == "B") {
    current.g = 6;
    current.h = hValue("T", "M", "B");
    current.f = current.h + current.g;
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "TB";
    addToFrontier.g = 7;
                    // 7 - T To End
    addToFrontier.h = hValue("T", "0", "MB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "MB";
    addToFrontier.g = 7;
                    // 7 - M To End
    addToFrontier.h = hValue("T", "0", "MB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("T", "M", "B");
    return;
  }
  else if(current.peg1 == "T" && current.peg2 == "0" && current.peg3 == "MB") {
    current.g = 7;
    current.h = hValue("T", "0", "MB");
    current.f = current.h + current.g;
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TMB";
    addToFrontier.goal = true;
    addToFrontier.g = 8;
                    // 8 - T To End
    addToFrontier.h = hValue("0", "0", "TMB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "T";
    addToFrontier.peg3 = "MB";
    addToFrontier.g = 8;
                    // < 8 - T To Center
    addToFrontier.h = hValue("0", "T", "MB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("T", "0", "MB");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "0" && current.peg3 == "TMB") {
    current.g = 8;
    current.h = hValue("0", "0", "TMB");
    current.f = current.h + current.g;
    // No Transitions Goal Node
    findNRemove("0", "0", "TMB");
    return;
  }
  // ----------------------------------------------------------------------------------------
  else if(current.peg1 == "0" && current.peg2 == "M" && current.peg3 == "TB") {
    current.g = 7;
    current.h = hValue("0", "M", "TB");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 15;
                    // 15 - T To First
    addToFrontier.h = hValue("T", "M", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TM";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 15;
                    // 15 - T To Center^
    addToFrontier.h = hValue("0", "TM", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("0", "M", "TB");
    return;
  }
  else if(current.peg1 == "M" && current.peg2 == "0" && current.peg3 == "TB") {
    current.g = 13;
    current.h = hValue("M", "0", "TB");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "TB";
    addToFrontier.g = 14;
                    // 14 - M To Center
    addToFrontier.h = hValue("0", "M", "TB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("M", "0", "TB");
    return;
  }
  else if(current.peg1 == "MB" && current.peg2 == "T" && current.peg3 == "0") {
    current.g = 2;
    current.h = hValue("MB", "T", "0");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "B";
    addToFrontier.peg2 = "T";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 3;
                    // 3 - M To End
    addToFrontier.h = hValue("B", "T", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "MB";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "T";
    addToFrontier.g = 3;
                    // 3 - T To End
    addToFrontier.h = hValue("MB", "0", "T");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("MB", "T", "0");
    return;
  }
  else if(current.peg1 == "B" && current.peg2 == "T" && current.peg3 == "M") {
    current.g = 3;
    current.h = hValue("B", "T", "M");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 4;
                    // 4 - T To First
    addToFrontier.h = hValue("TB", "0", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "B";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TM";
    addToFrontier.g = 4;
                    // 4 - T To End
    addToFrontier.h = hValue("B", "0", "TM");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("B", "T", "M");
    return;
  }
  else if(current.peg1 == "TB" && current.peg2 == "0" && current.peg3 == "M") {
    current.g = 4;
    current.h = hValue("TB", "0", "M");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 5;
                    // 5 - M To Center
    addToFrontier.h = hValue("TB", "M", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "B";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TM";
    addToFrontier.g = 5;
                    // < 5 - T To End
    addToFrontier.h = hValue("B", "0", "TM");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("TB", "0", "M");
    return;
  }
  else if(current.peg1 == "B" && current.peg2 == "0" && current.peg3 == "TM") {
    current.g = 4;
    current.h = hValue("B", "0", "TM");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 5;
                    // 5 - T To First >
    addToFrontier.h = hValue("TB", "0", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "B";
    addToFrontier.peg3 = "TM";
    addToFrontier.g = 6;
                    // 6 - B To Center
    addToFrontier.h = hValue("0", "B", "TM");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("B", "0", "TM");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "B" && current.peg3 == "TM") {
    current.g = 6;
    current.h = hValue("0", "B", "TM");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "B";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 6;
                    // 6 - T To First
    addToFrontier.h = hValue("T", "B", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 6;
                    // 6 - T To Center
    addToFrontier.h = hValue("0", "TB", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("0", "B", "TM");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "TB" && current.peg3 == "M") {
    current.g = 6;
    current.h = hValue("0", "TB", "M");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "B";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 7;
                    // 7 - T To First^
    addToFrontier.h = hValue("T", "B", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 7;
                    // 7 - M To First
    addToFrontier.h = hValue("M", "TB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("0", "TB", "M");
    return;
  }
  else if(current.peg1 == "T" && current.peg2 == "B" && current.peg3 == "M") {
    current.g = 6;
    current.h = hValue("T", "B", "M");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "MB";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 7;
                    // \ | / 7 - M To Center
    addToFrontier.h = hValue("T", "MB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 7;
                    // 7 - T To Center
    addToFrontier.h = hValue("0", "TB", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("T", "B", "M");
    return;
  }
  else if(current.peg1 == "TB" && current.peg2 == "M" && current.peg3 == "0") {
    current.g = 5;
    current.h = hValue("TB", "M", "0");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "TB";
    addToFrontier.peg2 = "M";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 6;
                    // 6 - T To End >
    addToFrontier.h = hValue("T", "MB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("TB", "M", "0");
    return;
  }
  else if(current.peg1 == "T" && current.peg2 == "MB" && current.peg3 == "0") {
    current.g = 7;
    current.h = hValue("T", "MB", "0");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "MB";
    addToFrontier.peg3 = "T";
    addToFrontier.g = 8;
                    // 8 - T To End
    addToFrontier.h = hValue("0", "MB", "T");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TMB";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 8;
                    // 8 - T To Center
    addToFrontier.h = hValue("0", "TMB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("T", "MB", "0");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "TMB" && current.peg3 == "0") {
    current.g = 8;
    current.h = hValue("0", "TMB", "0");
    current.f = current.g + current.h;
    // Error State!
    findNRemove("0", "TMB", "0");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "MB" && current.peg3 == "T") {
    current.g = 8;
    current.h = hValue("0", "MB", "T");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "B";
    addToFrontier.peg3 = "T";
    addToFrontier.g = 9;
                    // 9 - M To First
    addToFrontier.h = hValue("M", "B", "T");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("0", "MB", "T");
    return;
  }
  else if(current.peg1 == "M" && current.peg2 == "B" && current.peg3 == "T") {
    current.g = 9;
    current.h = hValue("M", "B", "T");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 10;
                    // 10 - T To Center
    addToFrontier.h = hValue("M", "TB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "TM";
    addToFrontier.peg2 = "B";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 10;
                    // 10 - T To First
    addToFrontier.h = hValue("TM", "B", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("M", "B", "T");
    return;
  }
  else if(current.peg1 == "TM" && current.peg2 == "B" && current.peg3 == "0") {
    current.g = 11;
    current.h = hValue("TM", "B", "0");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "0";
    addToFrontier.g = 11;
                    // 11 - T To Center
    addToFrontier.h = hValue("M", "TB", "0");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "TM";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 11;
                    // 11 - B To End
    addToFrontier.h = hValue("TM", "0", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("TM", "B", "0");
    return;
  }
  else if(current.peg1 == "TM" && current.peg2 == "0" && current.peg3 == "B") {
    current.g = 11;
    current.h = hValue("TM", "0", "B");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TB";
    addToFrontier.g = 12;
                    // 12 - T To End
    addToFrontier.h = hValue("M", "0", "TB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "T";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 12;
                    // 12 - T To Center
    addToFrontier.h = hValue("M", "T", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("TM", "0", "B");
    return;
  }
  else if(current.peg1 == "M" && current.peg2 == "TB" && current.peg3 == "0") {
    current.g = 10;
    current.h = hValue("M", "TB", "0");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "TM";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "B";
    addToFrontier.g = 11;
                    // 11 - T To First
    addToFrontier.h = hValue("TM", "0", "B");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "TB";
    addToFrontier.peg3 = "M";
    addToFrontier.g = 11;
                    // < 11 - M To End
    addToFrontier.h = hValue("0", "TB", "M");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("M", "TB", "0");
    return;
  }
  else if(current.peg1 == "M" && current.peg2 == "T" && current.peg3 == "B") {
    current.g = 12;
    current.h = hValue("M", "T", "B");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "M";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TB";
    addToFrontier.g = 13;
                    // 13 - T To End
    addToFrontier.h = hValue("M", "0", "TB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "T";
    addToFrontier.peg3 = "MB";
    addToFrontier.g = 13;
                    // 13 - M To End
    addToFrontier.h = hValue("0", "T", "MB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("M", "T", "B");
    return;
  }
  else if(current.peg1 == "0" && current.peg2 == "T" && current.peg3 == "MB") {
    current.g = 13;
    current.h = hValue("0", "T", "MB");
    current.f = current.g + current.h;
    addToFrontier.peg1 = "T";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "MB";
    addToFrontier.g = 14;
                    // 14 - T To First >
    addToFrontier.h = hValue("T", "0", "MB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    addToFrontier.peg1 = "0";
    addToFrontier.peg2 = "0";
    addToFrontier.peg3 = "TMB";
    addToFrontier.g = 14;
                    // 14 - T To End
    addToFrontier.h = hValue("0", "0", "TMB");
    addToFrontier.f = addToFrontier.g + addToFrontier.h;
    if(!inFrontier(addToFrontier.peg1, addToFrontier.peg2, addToFrontier.peg3)) {
      frontier.push_back(addToFrontier);
    }
    findNRemove("M", "T", "B");
    return;
  }
}

// This function checks to see what is that best in the froniter
State bestofFrontier(State theBest) {
  // If frontier is not empty; by default the current state should be the best
  if(frontier.size()) {
    theBest.peg1 = frontier[0].peg1;
    theBest.peg2 = frontier[0].peg2;
    theBest.peg3 = frontier[0].peg3;
    theBest.f = frontier[0].f;
    theBest.g = frontier[0].g;
    theBest.h = frontier[0].h;
  }
  // find the best f state in the frontier, remove it, and return it
  for(int i = 0; i < frontier.size(); i++) {
    if(frontier[i].goal) {
      cout << "[Goal In Frontier]: Setting Current State To Goal!" << endl;
      theBest.peg1 = frontier[0].peg1;
      theBest.peg2 = frontier[0].peg2;
      theBest.peg3 = frontier[0].peg3;
      theBest.f = frontier[i].f;
      theBest.g = frontier[i].g;
      theBest.h = frontier[i].h;
      theBest.goal = frontier[i].goal;
      return theBest;
    }
    if(frontier[i].f < theBest.f) {
      cout << "Found Best!" << endl;
      theBest.peg1 = frontier[0].peg1;
      theBest.peg2 = frontier[0].peg2;
      theBest.peg3 = frontier[0].peg3;
      theBest.f = frontier[i].f;
      theBest.g = frontier[i].g;
      theBest.h = frontier[i].h;
      theBest.goal = frontier[i].goal;
    }
  }
  return theBest;
}

// Main Driver Function

int main() {
  int i = 0;
  State current = {"TMB", "0", "0", 0, hValue("TMB", "0", "0"), 3, false}; //T and B is not on center nor end.
  do {
      if(current.goal) {
        cout << "Goal Reached!" << endl;
        break;
      }
      cout << ">>>Expand:" << current.peg1 << " " << current.peg2 << " " << current.peg3 << endl;
      generate(current);
      cout << "Frontier is:" << endl;
      displayFrontier();
      current = bestofFrontier(current);
      i++;
    }while (!current.goal);// end while
  return 0;
}
