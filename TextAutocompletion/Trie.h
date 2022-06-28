#include <iostream>

using namespace std;


struct TrieNode {
	TrieNode* prev;
	TrieNode* next[26];				// for English 26 letters A-Z
	unsigned int count[26];			// for pointer to next letter
	unsigned int total;				// total count for node
	bool final;

	TrieNode() {
		for (int i = 0; i < 26; i++) {
			next[i] = nullptr;
			count[i] = 0;
		}
		prev = nullptr;
		total = 0;
		final = false;
	}


	float probability(int index) {
		//cout << "index " << index << " " << "count " << count[index] << " " << "total " << total << endl;
		return float((count[index])) / total;
	}


};


class Trie {
	TrieNode* root;
	int countWords;

public:
	Trie() {
		root = new TrieNode();
	}
	
	~Trie() {};



	//HINT: буква A-Z это не число 0-N и не может использоваться как индекс в массив
	int getIndex(char ch) {
		ch = tolower(ch);
		if (ch >= 'a' && ch <= 'z') {
			return ch - 'a';
		}
		else return -1;
	}

	char getCharAt(int index) {
		return 'a' + index;
	}


	// insert a word ‘s’ to Trie structure. New nodes created set their ‘total’ field to 1.
	// If the word ‘s’ is already in the tree, there is nothing to insert.
	void insert(const string& s) {
		const char* i = s.c_str();						//pointer to first char in the word
		int index;	
		TrieNode* node = root;

		while (*i != 0) {								//go letter by letter
			
			index = getIndex(*i);
			//cout << "insert letter: " << *i << " " << "index: " << index << endl;

			// do  magic
			node->total++; 
			node->count[index] ++;
			
			if (node->next[index] == nullptr) { 
				TrieNode* newNode = new TrieNode;
				node->next[index] = newNode;
				newNode->prev = node;
			}

			node = node->next[index];
			i++;								
		}

		node->total++;
		if (!node->final) {
			node->final = true;
			countWords++;
		}		
	};


	TrieNode* findLastNode(const string& s) {
		const char* i = s.c_str();
		int index;
		TrieNode* node = root;

		while (*i != 0) {								

			index = getIndex(*i);
			//cout << "find letter: " << *i << " " << "index: " << index << endl;

			if (node->next[index] != nullptr) {
				node = node->next[index];
				i++;
			}
			else return nullptr;								//there is no such a word
		}

		return node;
	}

	
	// search for a word ‘s’ in the Trie and also update probabilities of all nodes traversed 
	// during the search by incrementing their ‘total’ and ‘count’ (if requested)
	// return true if the word ‘s’ was present in the Trie
	bool lookup(const string& s, bool update_count = true){
		const char* i = s.c_str();
		int index;
		TrieNode* node = root;

		while (*i != 0) {								

			index = getIndex(*i);
			//cout << "find letter: " << *i << " " << "index: " << index << endl;

			node->total++;
			node->count[index] ++;

			if (node->next[index] != nullptr) {
				node = node->next[index];
				i++;
			}
			else return false;
		}

		node->total++;
		if (node->final) {
			return true;
		}

		return false;
	}



	// delete a word from Trie structure if there
	// HINT: think about algorithm
	bool remove(const string& s) {
		//findWord();
		const char* i = s.c_str();
		TrieNode* node = findLastNode(s);

		if (node == nullptr) {
			return false;
		}

		//deleteFinal
		if (node->final == true) {						
			node->final == false;
		}

		//if there is no one word following from this node - delete and check previous node
		int isNext = 0;										//how many there are the following words

		while (node->final) {
			int i;
			for (i = 0; i < 26; i++) {
				if (node->next[i] != nullptr) {
					isNext++;									
				}
			}

			if (isNext == 0) {
				node = node->prev;
				delete node->next[i];
			}
			else break;
		}

		countWords--;
		return true;
	}


	// calculate the probability of user to input letters from ‘s’ 
	float probabilityWord(const string& s) {
		float prob = 1;
		const char* i = s.c_str();
		int index;
		TrieNode* node = root;

		while (*i != 0) {
			if (node != nullptr) {
				index = getIndex(*i);
				prob = prob * node->probability(index);
				//cout << "prob " << prob << " " << "index " << index << endl;

				node = node->next[index];
				i++;
			}
			else {					// there is not such word
				prob = 0; 
				i = 0;
			}
		}
		return prob;
	}


	// given string ‘s’ try to predict autocompletion of the string ‘s’ to a valid word
	// traverse the Trie according to string ‘s’ without updating probabilities 
	// and continue traversal for following nodes according to most probabilistic path
	// return a predicted word

	string predict(const string& s) {
		string predictable = s;

		// move on  trie to the last node of the given string
		TrieNode* node = findLastNode(s);

		if (node == nullptr) {
			return predictable;
		}

		// loop till find final { choose the most higher probability for the next letter }
		float prob;
		int index;

		while (node != nullptr){
			prob = 0;
			index = 0;

			for (int i = 0; i < 26; i++) {					//find the highest probability for next letter
				float tmp = node->probability(i);

				if (prob < tmp) {
					prob = tmp;
					index = i;
				}
			}
		
			predictable = predictable + getCharAt(index);		//add letter to string
			node = node->next[index];
			
			if (node->final) {
				break;
			}
		} 

		return predictable;	
	}


	// пройти по дереву и вернуть все слова
	// у каждого слова посчитать вероятность
	// вернуть 3 самых частых
	// 
	// вернуть массив из трех стрингов
	// первые три слова кладем в массив
	// следующее слово считаем вероятность и вставляем в массив вместо слова с меньшей вероятностью
	//string[] predict(){}

	void print() {
		cout << "total words: " << countWords << endl;
		cout << "runs by trie: " << root->total << endl;
		TrieNode* node = root;	
	}



	void printLastNode(Trie* t) {
		//find last node
	}

	// LATER: dump / visualize the Trie structure using XDot (will explain you later)
	// HINT: implement using helper function visualize(TrieNode *next)
	// the XDot database can be also used to restore ready Trie structure from file.
	// void visualize();

private:
	// HINT: implement predict using helper function. The function predicts the most probable 
	// ending for the current node by traversing most probabilistic path and returning 3 most 
	// probable results through the ‘result’ vector.
	//void predict_suffix(TrieNode* current, vector<string>& result);

	

};
