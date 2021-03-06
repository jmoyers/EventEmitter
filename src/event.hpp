#include <string.h>
#include <boost/algorithm/string.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <map>

using namespace std;

template <class T>
class EventEmitter {
public:
   typedef boost::function<void (T)> listener_type;
   typedef vector<listener_type> listener_list;

   struct Node;
   typedef map<string, Node> branch_map;
   
   struct Ghost {
      vector<string> markers;
      listener_type listener;
   } ghost_t;
   
   struct Node {
      string name;
      branch_map branches;
      listener_list listeners;
      vector<Ghost *> wanderers;
   } node_t;   
   
   EventEmitter(){};
   ~EventEmitter(){};
   
   void addListener(string channel, listener_type listener){      
      vector<string> channels;
      boost::split(channels, channel, boost::is_any_of("."));
      
      Node *currNode = &this->listeners;
      
      for (vector<string>::iterator i = channels.begin(); i != channels.end(); i++) {
         Ghost *ghost = new Ghost();
         
         ghost->markers.resize(distance(i+1, channels.end()));
         copy(i+1, channels.end(), ghost->markers.begin());
         
         ghost->listener = listener;
         
         if (*i == "*") {
            currNode->wanderers.push_back(ghost);
            return;
         } else {
            currNode = &currNode->branches[*i];
            currNode->name = *i;
         }
      }
      
      currNode->listeners.push_back(listener);
   }
   
   void emit(string channel, T payload){
      vector<string> channels;
      boost::split(channels, channel, boost::is_any_of("."));

      Node *currNode = &this->listeners;
      bool found = false;

      for (vector<string>::iterator i = channels.begin(); i != channels.end(); i++) {
         found = false;
         if (currNode->branches.find(*i) != currNode->branches.end()) {
            for (typename vector<Ghost *>::iterator ii = currNode->wanderers.begin(); ii != currNode->wanderers.end(); ii++) {
               if (this->compareMarkers((*ii)->markers, channels)) {
                  ((*ii)->listener)(payload);
               }
            }
            found = true;
            currNode = &currNode->branches[*i];
         } else {
            return;
         }
      }

      if (found) {
         for (int i = 0; i < currNode->listeners.size(); i++) {
            currNode->listeners[i](payload);
         }
      }
   }
   
   void removeListener(string channel, listener_type listener) {
      
   }
private:
   Node listeners;
   
   bool compareMarkers(vector<string> &a, vector<string> &b){
      for (int ai = a.size()-1, bi = b.size()-1;ai >= 0 && bi >= 0; ai--, bi--){
         if (a[ai] != b[bi]) {
            return false;
         }
      }   
      return true;
   }
   
   void printNode(Node &node) {
      cout << endl << "==== Node" << endl;
      cout << "Node name     : " << node.name << endl;
      cout << "Listener count: " << node.listeners.size() << endl;
      cout << "Branch count  : " << node.branches.size() << endl;
      cout << "Wanderer count: " << node.wanderer.size() << endl;
   }
   
   void printVector(vector<string> &v) {
      cout << endl << "==== Vector " << endl;
      for (vector<string>::iterator i = v.begin(); i != v.end(); i++) {
         cout << *i << endl;
      }
   }
};