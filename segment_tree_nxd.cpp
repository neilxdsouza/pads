#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct SegmentTreeNode {
	int left, right;
	long value;
	SegmentTreeNode(int l, int r, int v): left(l), right(r), value(v)
	{ }
};

struct SegmentTree {
	vector<SegmentTreeNode *> seg_tree_pointer;
	~SegmentTree() {
		for (int i = 0; i < seg_tree_pointer.size(); ++i) {
			delete seg_tree_pointer[i];
			seg_tree_pointer[i] = 0;
		}
	}
	int size;

	void allocate_mem(const vector<int> & v)
	{
		int sz = v.size();
		int tmp = sz, pow = 0;
		do {
			tmp = tmp/2;
			pow += 1;
		} while (tmp > 0);
		long seg_tree_size = 1;
		for (int i = 0; i < pow; ++i) {
			seg_tree_size *= 2;
		}
		seg_tree_size = seg_tree_size*2;
		// seg_tree_size = seg_tree_size*2;
		size = seg_tree_size;
		cout << "created seg_tree of size: " << seg_tree_size << endl;
		//seg_tree_pointer = new int [seg_tree_size];
		seg_tree_pointer.resize(seg_tree_size, 0);
	}

	SegmentTreeNode *  constructSegmentTree(vector<int> & arr,
			int arr_start, int arr_end,
			int segment_tree_node_index)
	{
		std::string fn_name = __PRETTY_FUNCTION__;
		cout << "ENTER " << fn_name
			<< " arr_start: " << arr_start
			<< " arr_end: " << arr_end
			<< " segment_tree_node_index: " << segment_tree_node_index
			<< endl;
		// leaf value
		if (arr_start == arr_end) {
			SegmentTreeNode * seg_tree_node = new
				SegmentTreeNode(arr_start, arr_end, 
					arr[arr_start]);
			cout << "arr[" << arr_start << "] = "
				<< arr[arr_start] 
				<< " goes to index: " << segment_tree_node_index
				<< endl;
			seg_tree_pointer[segment_tree_node_index] =
				seg_tree_node;
			return seg_tree_pointer[segment_tree_node_index];
		}
		// handle non leaf
		long arr_mid = (arr_start + arr_end) / 2;
		SegmentTreeNode * left_node = 
			constructSegmentTree(arr, arr_start, arr_mid,
					2 * segment_tree_node_index + 1);
		SegmentTreeNode * right_node = 
			constructSegmentTree(arr, arr_mid + 1, arr_end,
					2 * segment_tree_node_index + 2);
		SegmentTreeNode * new_node = new SegmentTreeNode(
				arr_start, arr_end,
				left_node->value + right_node->value);
		seg_tree_pointer[segment_tree_node_index] = new_node;
		cout << "merge of : " << 2 * segment_tree_node_index + 1
			<< " and : " << 2 * segment_tree_node_index + 2 << " goes to "
			<< segment_tree_node_index << endl;
		cout << "segment_tree_node_index: "
			<< segment_tree_node_index 
			<< " takes care of range: "
			<< " start: " 
			<< seg_tree_pointer[segment_tree_node_index]->left
			<< " end: " 
			<< seg_tree_pointer[segment_tree_node_index]->right
			<< endl;

		return seg_tree_pointer[segment_tree_node_index];
		
	}

	SegmentTree(vector<int> & arr) {
		allocate_mem(arr);
		constructSegmentTree(arr, 0, arr.size()-1, 0);
	}

	// int get_value(int seg_tree_index, int lo, int hi, int nest_level)
	// {
	// 	string fn_name = __PRETTY_FUNCTION__ ;
	// 	for (int i = 0; i < nest_level; ++i) {
	// 		cout << "  ";
	// 	}
	// 	cout << "ENTER " << fn_name
	// 		<< " seg_tree_index: " << seg_tree_index
	// 		<< " lo: " << lo
	// 		<< " hi: " << hi
	// 		<< " nest_level: " << nest_level
	// 		<< endl;
	// 	if (lo == seg_tree_pointer[seg_tree_index]->left &&
	// 		hi == seg_tree_pointer[seg_tree_index]->right) {
	// 		for (int i = 0; i < nest_level; ++i) {
	// 			cout << "  ";
	// 		}
	// 		cout << "EXIT " << fn_name
	// 			<< " seg_tree_index: " << seg_tree_index
	// 			<< " lo: " << lo
	// 			<< " hi: " << hi
	// 			<< " nest_level: " << nest_level
	// 			<< endl;
	// 		return seg_tree_pointer[seg_tree_index]->value;
	// 	}
	// 	long mid = (lo + hi) / 2;
	// 	SegmentTreeNode * left = seg_tree_pointer[2*seg_tree_index+1];
	// 	if (lo > left->left && lo < left->right) {
	// 	int val1 = get_value(seg_tree_index * 2 + 1, lo, mid, nest_level + 1);
	// 	SegmentTreeNode * right = seg_tree_pointer[2*seg_tree_index+2];
	// 	int val2 = get_value(seg_tree_index * 2 + 2, mid+1, hi, nest_level + 1);
	// 	for (int i = 0; i < nest_level; ++i) {
	// 		cout << "  ";
	// 	}
	// 	cout << "EXIT " << fn_name
	// 		<< " seg_tree_index: " << seg_tree_index
	// 		<< " lo: " << lo
	// 		<< " hi: " << hi
	// 		<< " nest_level: " << nest_level
	// 		<< endl;
	// 	return val1 + val2;

	// }

	// int get_value(int lo, int hi)
	// {
	// 	get_value(0, lo, hi, 0);
	// }




};

//int get_value(int * & seg_tree_pointer, int responsible_for_start_index,
//		int responsible_for_end_index,
//		int lo, int hi)
//{
//	//if (
//	//	responsible_for_start_index == lo &&
//	//	responsible_for_end_index == hi) {
//	//	seg_tree_pointer[	
//	//}
//	
//}


int main()
{
	vector<int> vec { 1, 3, 5, 7, 9 , 11, 13
		// , 17, 19
	};

	//int * seg_tree_pointer = 0;
	//allocate_mem(vec, seg_tree_pointer);

	//int start = 0, end = vec.size() - 1;
	//constructSegmentTree(vec, start, end, seg_tree_pointer, 0);
	SegmentTree segtree(vec);
	// int v1 = segtree.get_value(0, 6);
	// cout << "0-6: " << v1 << endl;
	// int v2 = segtree.get_value(1, 3);
	// cout << "1-3: " << v2 << endl;
	// int v3 = segtree.get_value(2, 5);
	// cout << "2-5: " << v3 << endl ;
}


