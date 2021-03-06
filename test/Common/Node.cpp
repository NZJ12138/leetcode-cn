﻿// Node.cpp 


//////////////////////////////////////////////////////////////////////////
// sample: 
// {"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":{"$id":"6","left":null,"next":null,"right":null,"val":6},"next":null,"right":{"$id":"7","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}
#ifdef NODE_DEFINE_LEETCODE_116_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE
class Node
{
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() {}

	Node(int _val, Node* _left, Node* _right, Node* _next) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;
	}
};

void preorder(const Node* node, int& id, map<string, const Node*>& nodes, map<const Node*, string>& n_s)
{
	auto getNextId = [&id]()
	{ return "\"" + to_string(id++) + "\""; };

	if (node == nullptr) return;
	if (n_s.count(node) != 0) return;
	string s = getNextId();
	nodes[s] = node;
	n_s[node] = s;
	preorder(node->left, id, nodes, n_s);
	preorder(node->right, id, nodes, n_s);
	preorder(node->next, id, nodes, n_s);
}

Node* StringToNode(const string data)
{
	// string to map_string
	vector<map<string, string>> input = StringToVectorMapStringString(data);
	//for (auto um : input)
	//{
	//	for (auto s : um)
	//	{
	//		cout << "[" << s.first << "] = " << s.second << ",\t";
	//	}
	//	cout << endl;
	//}

	// map_string to map_nodes
	map<string, Node*> nodes;
	nodes["null"] = nullptr;
	for (auto um : input)
	{
		string id = um["$id"];
		int val = um.count("val") ? stoi(um["val"]) : 0;
		Node* newNode = new Node(val, nullptr, nullptr, nullptr);
		nodes[id] = newNode;
	}
	for (auto um : input)
	{
		string id = um["$id"];
		nodes[id]->left = nodes[um["left"]];
		nodes[id]->right = nodes[um["right"]];
		nodes[id]->next = nodes[um["next"]];
	}
	return nodes["\"1\""];
}

string NodeToString(const Node* pHead)
{
	// nodes to map_nodes
	map<string, const Node*> nodes2;
	map<const Node*, string> n_s;
	n_s[nullptr] = "null";
	int id = 1;
	preorder(pHead, id, nodes2, n_s);

	// map_nodes to map_string
	vector<map<string, string>> output;
	for (auto n : nodes2)
	{
		const Node* cur = n.second;
		map<string, string> _m;
		_m["$id"] = n.first;
		_m["left"] = n_s[cur->left];
		_m["right"] = n_s[cur->right];
		_m["next"] = n_s[cur->next];
		_m["val"] = to_string(cur->val);
		output.push_back(_m);
	}

	// map_string to string
	string ans = VectorMapStringStringToString(output);
	return ans;
}
#endif

//////////////////////////////////////////////////////////////////////////
// sample:
// [1,2,3,4,5,null,7]
#ifdef NODE_DEFINE_LEETCODE_117_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II
class Node
{
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() {}

	Node(int _val, Node * _left, Node * _right, Node * _next) {
		val = _val;
		left = _left;
		right = _right;
		next = _next;
	}
};

Node* StringToNode(string data)
{
	if (data.empty()) return nullptr;
	if (data[0] == '[') data = data.substr(1, data.size() - 2);
	vector<string> splitData = split(data, ",");
	if (data == "" || splitData[0] == "null") return nullptr;

	Node* root = new Node(stoi(splitData[0].c_str()), nullptr, nullptr, nullptr);
	queue<Node*> qTree;
	qTree.push(root);

	int i = 1;
	while (!qTree.empty())
	{
		Node* qHead = nullptr;
		while (qHead == nullptr)
		{
			if (qTree.empty()) return root;
			qHead = qTree.front();
			qTree.pop();
		}

		auto f = [&qTree](string& s, Node** p)
		{
			while (s.front() == ' ') s = s.substr(1, s.size() - 1);
			while (s.back() == ' ') s.pop_back();
			if (s == "null")
			{
				qTree.push(nullptr);
			}
			else
			{
				*p = new Node(stoi(s.c_str()), nullptr, nullptr, nullptr);
				qTree.push(*p);
			}
		};

		if (i == splitData.size()) return root;
		f(splitData[i], &qHead->left);
		i++;

		if (i == splitData.size()) return root;
		f(splitData[i], &qHead->right);
		i++;
	}
	return root;
}

string NodeToString(Node* root)
{
	string str = "[";

	while (root != nullptr)
	{
		Node* cur = root;
		root = nullptr;
		while (cur != nullptr)
		{
			if (root == nullptr)
			{
				root = (cur->left != nullptr) ? cur->left : cur->right;
			}

			str += to_string(cur->val);
			str += ",";
			cur = cur->next;
		}
		str += "#,";
	}

	int len = str.size();
	while (true)
	{
		if (len > 1 && str.back() == ',') len -= 1;
		else break;
		if (len > 4 && str.substr(len - 4, 4) == "null") len -= 4;
		else break;
	}
	str = str.substr(0, len);
	str += "]";
	return str;
}
#endif

//////////////////////////////////////////////////////////////////////////
// sample:
// [[2,4],[1,3],[2,4],[1,3]]
#ifdef NODE_DEFINE_LEETCODE_133_CLONE_GRAPH
class Node
{
public:
	int val;
	vector<Node*> neighbors;

	Node() {}

	Node(int _val, vector<Node*> _neighbors)
	{
		val = _val;
		neighbors = _neighbors;
	}
};

Node* StringToNode(const string data)
{
	vector<vector<int>> val = StringToVectorVectorInt(data);
	vector<Node*> nodes(val.size(), nullptr);
	int v = 0;
	for (auto& n : nodes)
	{
		n = new Node(++v, vector<Node*>());
	}
	for (size_t i = 0; i < val.size(); i++)
	{
		for (size_t j = 0; j < val[i].size(); j++)
		{
			nodes[i]->neighbors.push_back(nodes[val[i][j] - 1]);
		}
	}
	return nodes[0];
}

string NodeToString(const Node* pHead)
{
	unordered_map<const Node*, int> node_id;
	vector<const Node*> id_node;
	stack<const Node*> st;
	st.push(pHead);
	
	size_t i = 0;
	while (!st.empty())
	{
		auto q = st.top();
		st.pop();

		if (node_id.find(q) != node_id.end()) continue;
		node_id[q] = ++i;
		id_node.push_back(q);
		for (size_t j = q->neighbors.size() - 1; j < q->neighbors.size(); j--)
		{
			st.push(q->neighbors[j]);
		}
	}
	
	vector<vector<int>> val;
	for (auto& n : id_node)
	{
		vector<int> temp;
		for (auto& nei : n->neighbors)
		{
			temp.push_back(node_id[nei]);
		}
		val.push_back(temp);
	}

	string ret = VectorVectorIntToString(val);
	return ret;
}
#endif

//////////////////////////////////////////////////////////////////////////
// sample:
// [[7,null],[13,0],[11,4],[10,2],[1,0]]
#ifdef NODE_DEFINE_LEETCODE_138_COPY_LIST_WITH_RANDOM_POINTER
class Node
{
public:
	int val;
	Node* next;
	Node* random;

	Node() {}

	Node(int _val, Node* _next, Node* _random)
	{
		val = _val;
		next = _next;
		random = _random;
	}
};

Node* StringToNode(const string data)
{
	vector<vector<string>> val = StringToVectorVectorString(data);
	vector<Node*> nodes(val.size(), nullptr);
	for (auto& n : nodes)
	{
		n = new Node(0, nullptr, nullptr);
	}
	for (size_t i = 0; i < val.size(); i++)
	{
		nodes[i]->val = stoi(val[i][0]);
		nodes[i]->next = (i == val.size() - 1) ? nullptr : nodes[i + 1];
		nodes[i]->random = (val[i][1] == "null") ? nullptr : nodes[stoi(val[i][1])];
	}
	return nodes.empty() ? nullptr : nodes[0];
}

string NodeToString(const Node* pHead)
{
	unordered_map<const Node*, int> node_id;
	vector<const Node*> id_node;

	int idx = 0;
	while (pHead != nullptr)
	{
		id_node.push_back(pHead);
		node_id[pHead] = idx++;
		pHead = pHead->next;
	}

	vector<vector<string>> val(id_node.size(), vector<string>(2));
	for (size_t i = 0; i < val.size(); i++)
	{
		val[i][0] = to_string(id_node[i]->val);
		val[i][1] = (id_node[i]->random == nullptr) ? "null" : to_string(node_id[id_node[i]->random]);
	}

	string ret = VectorVectorStringToString(val, false);
	return ret;
}
#endif

//////////////////////////////////////////////////////////////////////////
// sample:
// [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
#ifdef NODE_DEFINE_LEETCODE_430_FLATTEN_A_MULTILEVEL_DOUBLY_LINKED_LIST
class Node
{
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;

	Node() {}

	Node(int _val, Node* _prev, Node* _next, Node* _child)
	{
		val = _val;
		prev = _prev;
		next = _next;
		child = _child;
	}
};

Node* StringToNode(const string data)
{
	vector<string> vs = StringToVectorString(data);

	vector<vector<Node*>> nodes;

	size_t idx = 0;
	size_t space = 0;
	bool newLine = true;
	while (idx < vs.size())
	{
		if (vs[idx] == "null")
		{
			if (!newLine)
			{
				nodes.back().push_back(nullptr);
			}
			space += newLine;
			newLine = true;
		}
		else
		{
			if (newLine)
			{
				nodes.push_back(vector<Node*>());
				for (size_t t = 0; t < space; t++)
				{
					nodes.back().push_back(nullptr);
				}
				newLine = false;
			}

			nodes.back().push_back(new Node(stoi(vs[idx]), nullptr, nullptr, nullptr));
		}
		idx++;
	}

	for (size_t i = 0; i < nodes.size(); i++)
	{
		newLine = true;
		for (size_t j = 0; j < nodes[i].size() - 1; j++)
		{
			if (nodes[i][j] == nullptr) continue;
			if (newLine)
			{
				newLine = false;
				if (i != 0)
				{
					nodes[i - 1][j]->child = nodes[i][j];
				}
			}
			nodes[i][j]->next = nodes[i][j + 1];
			if (nodes[i][j + 1] != nullptr)
			{
				nodes[i][j + 1]->prev = nodes[i][j];
			}
		}
	}

	return nodes.empty() ? nullptr : nodes[0][0];
}

string NodeToString(const Node* pHead)
{
	vector<string> val;
	const Node* cur = pHead;
	const Node* lv_head = pHead;

	while (true)
	{
		while (cur != nullptr)
		{
			val.push_back(to_string(cur->val));
			cur = cur->next;
		}
		val.push_back("null");
		while (lv_head != nullptr && lv_head->child == nullptr)
		{
			val.push_back("null");
			lv_head = lv_head->next;
		}
		if (lv_head == nullptr) break;
		lv_head = lv_head->child;
		cur = lv_head;
	}

	while (val.back() == "null")
	{
		val.pop_back();
	}
	val.push_back("null");

	string ret = VectorStringToString(val, false);
	return ret;
}
#endif