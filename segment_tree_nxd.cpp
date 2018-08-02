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

	// this is a private api 
	int get_value(int seg_tree_index, int lo, int hi, int nest_level)
	{
		string fn_name = __PRETTY_FUNCTION__ ;
		for (int i = 0; i < nest_level; ++i) {
			cout << "  ";
		}
		cout << "ENTER " << fn_name
			<< " seg_tree_index: " << seg_tree_index
			<< " lo: " << lo
			<< " hi: " << hi
			<< " nest_level: " << nest_level
			<< endl;
		if (lo == seg_tree_pointer[seg_tree_index]->left &&
			hi == seg_tree_pointer[seg_tree_index]->right) {
			for (int i = 0; i < nest_level; ++i) {
				cout << "  ";
			}
			cout << "EXIT " << fn_name
				<< " seg_tree_index: " << seg_tree_index
				<< " lo: " << lo
				<< " hi: " << hi
				<< " nest_level: " << nest_level
				<< endl;
			return seg_tree_pointer[seg_tree_index]->value;
		}
		long mid = (lo + hi) / 2;
		SegmentTreeNode * left =
			seg_tree_pointer[2 * seg_tree_index + 1];
		cout << "left - range : [" << 
			left->left << " - " << left->right << "]" << endl;
		// 0 - 7 => [0 - 3] [4 - 7]
		// 2 - 3
		if (lo >= left->left && hi <= left->right) {
			cout << "INFO " << fn_name << " case : entirely contained in left - recursing " << endl;
			int val1 = get_value(seg_tree_index * 2 + 1, lo, hi, nest_level + 1);
			return val1;
		}
		SegmentTreeNode * right = seg_tree_pointer[2*seg_tree_index+2];
		cout << "right - range : [" << 
			right->left << " - " << right->right << "]" << endl;
		if (lo >= right->left && hi <= right->right) {
			// entirely contained in right
			cout << "INFO " << fn_name << " case : entirely contained in right - recursing " << endl;
			int val2 = get_value(seg_tree_index * 2 + 2, lo, hi, nest_level + 1);
			return val2;
		}
		// partially in left and the rest in right
		cout << "searching for range [ "
			<< lo << " - " << left->right << "]"
			<< " in left " << left->left << " - " << left->right
			<< " AND " << endl;
		int val1 = get_value(seg_tree_index * 2 + 1,
				lo, left->right, nest_level + 1);
		cout << "searching for range [ "
			<< left->right + 1 << " - " << hi << "]"
			<< " in right " << right->left << " - " << right->right
			<< endl;
		int val2 = get_value(seg_tree_index * 2 + 2,
				left->right + 1, hi, nest_level + 1);

		for (int i = 0; i < nest_level; ++i) {
			cout << "  ";
		}
		cout << "EXIT " << fn_name
			<< " seg_tree_index: " << seg_tree_index
			<< " lo: " << lo
			<< " hi: " << hi
			<< " nest_level: " << nest_level
			<< endl;
		return val1 + val2;

	}

	// this is a public api 
	int get_value(int lo, int hi)
	{
		get_value(0, lo, hi, 0);
	}

	void update(int st_index, int start, int end, int value)
	{
		if (seg_tree_pointer[st_index]->left == 
				seg_tree_pointer[st_index]->right) {
			seg_tree_pointer[st_index]->value = value;
			return;
		}

		int mid = (seg_tree_pointer[st_index]->left +
			seg_tree_pointer[st_index]->right)/2,
		    	left = 2 * st_index + 1,
			right = 2* st_index + 2;

		if (end <= mid) {
			// start, end lies entirely in left half
			cout << "update lies in left half: "
				<< seg_tree_pointer[st_index]->left
				<< " - "
				<< seg_tree_pointer[st_index]->right
				<< endl;
			update(left, start, end, value);
		} else if (start >= mid + 1) {
			// start, end lies entirely in right half
			cout << "update lies in right half: "
				<< seg_tree_pointer[st_index]->left
				<< " - "
				<< seg_tree_pointer[st_index]->right
				<< endl;
			update(right, start, end, value);
		} else {
			update(left, start, mid, value);
			update(right, mid+1, end, value);
		}
		seg_tree_pointer[st_index]->value = 
			seg_tree_pointer[left]->value +
			seg_tree_pointer[right]->value;

	}

	void print(int st_index)
	{
		string fn_name = __PRETTY_FUNCTION__ ;
		//cout << "ENTER " << fn_name
		//	<< " left: " << seg_tree_pointer[st_index]->left
		//	<< " right: " << seg_tree_pointer[st_index]->right 
		//	<< endl;
			
		// leaf node
		if (seg_tree_pointer[st_index]->left == 
				seg_tree_pointer[st_index]->right) {
			cout << " " << seg_tree_pointer[st_index]->value;
		} else {
			// non-leaf node will have left and right
			if (st_index < seg_tree_pointer.size()) {
				int left = 2 * st_index+1,
				    right = 2 * st_index + 2;
				print (left);
				print (right);
				cout << " :"
					<< seg_tree_pointer[st_index]->value
					<< ": ";
			}
		}
	}




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
	vector<int> vec { 1,  3,  5,  7,  9, 11, 13
		           , 17, 19, 23, 29
	};

	//int * seg_tree_pointer = 0;
	//allocate_mem(vec, seg_tree_pointer);

	//int start = 0, end = vec.size() - 1;
	//constructSegmentTree(vec, start, end, seg_tree_pointer, 0);
	SegmentTree segtree(vec);
	int v1 = segtree.get_value(0, 6);
	cout << "0-6: " << v1 << endl;
	int v2 = segtree.get_value(1, 3);
	cout << "1-3: " << v2 << endl;
	int v3 = segtree.get_value(2, 5);
	cout << "2-5: " << v3 << endl ;
	int v4 = segtree.get_value(3, 6);
	cout << "3-6: " << v4 << endl ;
	int v5 = segtree.get_value(4, 7);
	cout << "4-7: " << v5 << endl ;
	segtree.print(0);
	cout << endl;
	segtree.update(0, 1, 3, 10);
	segtree.print(0);
	cout << endl;
}


