#include<iostream>
#include<string>
using namespace std;

struct HeapNode {
	char ch;
	int fq;
	HeapNode* left;
	HeapNode* right;
	HeapNode() {
		ch = '#';
		fq = -1;
		left = NULL;
		right = NULL;
	}
};

class Heap {
private:	
	HeapNode** heaparr;
	int size;
	int cap;
public:
	Heap(int cp) {
		heaparr = new HeapNode*[cp];
		cap = cp;
		size = 0;
	}

	void Balance() {
		int i = size;
		while (i != 0 && heaparr[i]->fq < heaparr[(i - 1) / 2]->fq) {
			swap(heaparr[i], heaparr[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
		size++;
	}

	void Insert(char c, int f) {
		heaparr[size] = new HeapNode();
		heaparr[size]->ch = c;
		heaparr[size]->fq = f;
		Balance();
	}

	void Insert(HeapNode* newNode) {
		heaparr[size] = newNode;
		Balance();
	}

	HeapNode* ExtractMin() {
		if (size == 0)
			return __nullptr;

		HeapNode* ret = heaparr[0];
		size--;
		heaparr[0] = heaparr[size];
		Heapify();
		return ret;
	}

	void Heapify() {
		int i = 0;
		while (i < size) {
			int lowest = i;
			if (i * 2 + 1 < size && heaparr[lowest]->fq > heaparr[i * 2 + 1]->fq)
				lowest = i * 2 + 1;
			if (i * 2 + 2 < size && heaparr[lowest]->fq > heaparr[i * 2 + 2]->fq)
				lowest = i * 2 + 2;
			if (lowest == i)
				break;
			swap(heaparr[i], heaparr[lowest]);
			i = lowest;
		}
	}

	int GetSize() const { return size; }

	void Print() {
		for (int i = 0; i < size; ++i) {
			cout << heaparr[i]->ch << "," << heaparr[i]->fq << endl;
		}
	}
};

void dfs(HeapNode* root, string str) {
	if (!root)
		return;
	str.push_back('0');
	dfs(root->left,str);
	str.pop_back();
	if(root->ch!='#')
		cout << root->ch << " " << str << endl;
	str.push_back('1');
	dfs(root->right,str);
}

void HuffmanCodes(char arr[], int freq[], int size) {
	Heap root(size);
	for (int i = 0; i < size; ++i) {
		root.Insert(arr[i], freq[i]);
	}

	root.Print();

	while (root.GetSize() > 1) {
		HeapNode* h1 = root.ExtractMin();
		HeapNode* h2 = root.ExtractMin();

		HeapNode* newNode = new HeapNode();
		newNode->fq = h1->fq + h2->fq;
		newNode->left = h1;
		newNode->right = h2;

		root.Insert(newNode);
	}

	cout << endl;
	HeapNode* curr = root.ExtractMin();
	dfs(curr,"");
}

int main() {
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
	int freq[] = { 5, 9, 12, 13, 16, 45 };

	int size = sizeof(arr) / sizeof(arr[0]);

	HuffmanCodes(arr, freq, size);

	cin.get();
}
