#include <iostream>
#include "Trie.h"

using namespace std;


int main() {

	cout << "let's fun begin" << endl;

	Trie* trie = new Trie();
	trie->insert("sv");
	trie->insert("s");
	trie->insert("s");
	trie->insert("svs");
	trie->insert("sveta");
	trie->print();

	/*
	cout << "find s " << trie->lookup("s")<< endl;
	cout << "find sv " << trie->lookup("sv") << endl;
	cout << "find svs " << trie->lookup("svs") << endl;
	*/

	//cout << "delete sv" << trie->remove("sv") << endl;
	//trie->print();

	//cout << "probability s " << trie->probabilityWord("s") << endl;
	//cout << "probability sv " << trie->probabilityWord("sv") << endl;
	//cout << "probability svs " << trie->probabilityWord("svs") << endl;

	cout << "predict for s: " << trie->predict("s") << endl;
	cout << "predict for sv: " << trie->predict("sv") << endl;
	cout << "predict for sve: " << trie->predict("sve") << endl;



	

	return 0;
}
