// Leetcode: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/
// Write methods to serialize and deserialize a binary tree.

// Approach: Generate a key for each node using 'l' and 'r' characters to indicate it's
// position in the tree. Perform a pre-order traversal to serialize and then deserialize the tree.

#include <string>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using NodeMap = std::unordered_map<std::string, int>;

// Accepted. 32ms. Beats 38.01% of submissions, ties 4.51% of submissions.
class Codec {
public:

	// Based on a pre-order traversal
	void serialize_tree(const TreeNode* root, std::string key, std::string& buf) {
		if (root == nullptr) return;

		if (!buf.empty()) buf.append(1, ',');
		buf.append(key);
		buf.append(1, ',');
		buf.append(std::to_string(root->val));

		serialize_tree(root->left, key + "l", buf);
		serialize_tree(root->right, key + "r", buf);
	}

	void deserialize_tree(TreeNode*& root, std::string key, NodeMap& node_map) {
		auto found = node_map.find(key);
		if (found == node_map.end()) { return; }

		root = new TreeNode(found->second);
		deserialize_tree(root->left, key + "l", node_map);
		deserialize_tree(root->right, key + "r", node_map);
	}

    // Encodes a tree to a single string.
    std::string serialize(const TreeNode* root) {
        std::string buf, key;
        serialize_tree(root, key, buf);
        return buf;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const std::string& data) {
        int start = 0;
        NodeMap node_map;

        while (start < data.size()) {
        	auto offset = data.find(',', start);
        	auto key = data.substr(start, offset-start);
        	
        	start = offset + 1;
        	offset = data.find(',', start);
        	auto end = (offset == std::string::npos) ? data.size() : offset;
        	auto value = std::stol(data.substr(start, end-start));

        	node_map[key] = value;
			start = end + 1;
        }

        TreeNode* root = nullptr;
        deserialize_tree(root, "", node_map);
    	return root;
    }
};

bool test_serialize_deserialize(std::vector<int> values) {
	TreeNode* root = nullptr;
	bst_insert(root, values);

	Codec c;
	auto data = c.serialize(root);

	TreeNode* new_tree = c.deserialize(data);
	return tree_equals(root, new_tree);
}

void test_serialize_deserialize() {
	assert(test_serialize_deserialize({1}));
	assert(test_serialize_deserialize({10,5}));
	assert(test_serialize_deserialize({10,15}));

	assert(test_serialize_deserialize({10,15,5}));
	assert(test_serialize_deserialize({10,15,5,3}));
	assert(test_serialize_deserialize({10,15,5,3,7}));
	assert(test_serialize_deserialize({10,15,5,3,1}));
	assert(test_serialize_deserialize({10,15,5,3,4}));
	assert(test_serialize_deserialize({10,15,5,3,4,20}));
	assert(test_serialize_deserialize({10,9,8,7,6,5}));
	assert(test_serialize_deserialize({10,11,12,13,14,15}));
}

int main(int argc, char** argv) {
	test_serialize_deserialize();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}