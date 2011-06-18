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
	typedef map<string, Node> listener_node;
	
	struct Ghost {
		vector<string> markers;
		listener_type listener;
	} ghost_t;
	
	struct Node {
		string name;
		listener_node branches;
		listener_list listeners;
		vector<Ghost *> ghosts;
		vector<Ghost *> wanderers;
	} node_t;	
	
	EventEmitter(){};
	~EventEmitter(){};
	
	void addListener(string channel, boost::function<void (T)> listener){		
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
				currNode->ghosts.push_back(ghost);
				currNode = &currNode->branches[*i];
				currNode->name = *i;
			}
		}
		
		currNode->listeners.push_back(listener);
	}
	
	void emit(string channel, T payload){
		listener_list list;
		
		this->getListeners(list, channel);
		
		for(typename listener_list::iterator i = list.begin(); i != list.end(); i++) {
			((listener_type)*i)(payload);
		}
	}
	
	void getListeners(listener_list &listeners, string channel) {
		vector<string> channels;
		boost::split(channels, channel, boost::is_any_of("."));

		Node *currNode = &this->listeners;
		bool found = false;
		
		for (vector<string>::iterator i = channels.begin(); i != channels.end(); i++) {
			found = false;
			
			// if (*i == "*") {
			// 	this->printNode(*currNode);
			// 	for (typename vector<Ghost *>::iterator ii = currNode->ghosts.begin(); ii != currNode->ghosts.end(); ii++) {
			// 		this->printVector((*ii)->markers);
			// 		this->printVector(channels);
			// 		cout << "Compared " << this->compareMarkers((*ii)->markers, channels) << endl;
			// 		if ((ii+1) == currNode->ghosts.end() || this->compareMarkers((*ii)->markers, channels)) {
			// 			listeners.push_back((*ii)->listener);
			// 		}
			// 	}
			// 	listeners.insert(listeners.end(), currNode->listeners.begin(), currNode->listeners.end());
			// 	return;
			// }
			
			if (currNode->branches.find(*i) != currNode->branches.end()) {
				for (typename vector<Ghost *>::iterator ii = currNode->wanderers.begin(); ii != currNode->wanderers.end(); ii++) {
					if (this->compareMarkers((*ii)->markers, channels)) {
						listeners.push_back((*ii)->listener);
					}
				}
				found = true;
				currNode = &currNode->branches[*i];
			} else {
				return;
			}
		}
		
		if (found) {
			listeners.insert(listeners.end(), currNode->listeners.begin(), currNode->listeners.end());
		}
	}
private:
	Node listeners;
	
	bool compareMarkers(vector<string> &a, vector<string> &b){
		int ai = a.size() - 1;

		if (ai < 0)
			return true;
			
		int bi = b.size() - 1;
		
		for (;ai >= 0 && bi >= 0; ai--, bi--){
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
		cout << "Ghost count   : " << node.ghosts.size() << endl;
	}
	
	void printVector(vector<string> &v) {
		cout << endl << "==== Vector " << endl;
		for (vector<string>::iterator i = v.begin(); i != v.end(); i++) {
			cout << *i << endl;
		}
	}
};