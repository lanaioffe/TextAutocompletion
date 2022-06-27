#include <iostream>
#include "Trie.h"

using namespace std;


int main() {

	cout << "let's fun begin" << endl;

	Trie* trie = new Trie();
	trie->insert("sv");
	trie->insert("s");
	//trie->insert("s");
	trie->print();

	cout << "find s " << trie->lookup("s")<< endl;
	cout << "find sv " << trie->lookup("sv") << endl;
	cout << "find svs " << trie->lookup("svs") << endl;

	cout << "delete sv" << trie->remove("sv") << endl;
	trie->print();

	return 0;
}
