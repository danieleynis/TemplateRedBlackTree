#include "rb_node.h"

template <class T>
class rb_tree{
	public:
		rb_tree();
		~rb_tree();
		rb_tree(const rb_tree<T> &to_copy);
		void insert_data(T to_add);
		void display_data();
	private:
		rb_node<T>* get_grandparent(rb_node<T> *& N);
		rb_node<T>* get_uncle(rb_node<T> *& N);
		void rotate_left(rb_node<T> *& N);
		void rotate_right(rb_node<T> *& N);
		void insert_data(T to_add, rb_node<T> *& root);
		void insert_case1(rb_node<T> *& N);
		void insert_case2(rb_node<T> *& N);
		void insert_case3(rb_node<T> *& N);
		void insert_case4(rb_node<T> *& N);
		void insert_case5(rb_node<T> *& N);
		void display_data(rb_node<T> * root);
		rb_node<T>*& get_root();
		rb_node<T> * root;
};


template <class T>
rb_tree<T>::rb_tree(){
	root = 0;
}

template <class T>
rb_node<T>*& rb_tree<T>::get_root(){
	return root;
}

template <class T>
void rb_tree<T>::insert_data(T to_add){
	insert_data(to_add, root);
}

template <class T>
void rb_tree<T>::rotate_left(rb_node<T> *& N){
	if(N->get_parent() == 0){
		rb_node<T> * temp = N->get_right();
		N->get_right() = temp->get_left();
		if(temp->get_left())
			temp->get_left()->get_parent() = N;
		temp->get_left() = N;
		get_root() = temp;
		get_root()->get_parent() = NULL;
		N->get_parent() = get_root();
	}
	else{
		rb_node<T> * temp = N->get_parent();
		rb_node<T> * temp2 = N->get_right();
		N->get_right() = temp2->get_left();
		if(temp2->get_left())
			temp2->get_left()->get_parent() = N;
		temp2->get_left() = N;
		N->get_parent() = temp2;
		temp->get_right() = temp2;
		temp2->get_parent() = temp;
	}
}


template <class T>
void rb_tree<T>::rotate_right(rb_node<T> *& N){
	if(N->get_parent() == 0){
		rb_node<T> * temp = N->get_left();
		N->get_left() = temp->get_right();
		if(temp->get_right())
			temp->get_right()->get_parent() = N;
		temp->get_right() = N;
		get_root() = temp;
		get_root()->get_parent() = NULL;
		N->get_parent() = get_root();
	}
	else{
		rb_node<T> * temp = N->get_parent();
		rb_node<T> * temp2 = N->get_left();
		N->get_left() = temp2->get_right();
		if(temp2->get_right())
			temp2->get_right()->get_parent() = N;
		temp2->get_right() = N;
		N->get_parent() = temp2;
		temp->get_left() = temp2;
		temp2->get_parent() = temp;
	}
}	


template <class T>
rb_node<T>* rb_tree<T>::get_grandparent(rb_node<T> *& N){
	if(N != 0 && N->get_parent() != 0)
		return N->get_parent()->get_parent();
	return NULL; //seg fault
}

template <class T>
rb_node<T>* rb_tree<T>::get_uncle(rb_node<T> *& N){
	rb_node<T> * G = get_grandparent(N);
	if(G == 0)
		return NULL;
	if(N->get_parent() == G->get_left())
		return G->get_right();
	return G->get_left();
}

template <class T>
void rb_tree<T>::insert_data(T to_add, rb_node<T> *& root){
	if(!root){
		root = new rb_node<T>(to_add, 1);
		insert_case1(root);
	}
	else if(to_add >= root->get_data()){
		if(root->get_right() == 0){
			root->get_right() = new rb_node<T>(to_add, 1);
			root->get_right()->get_parent() = root; 
			insert_case1(root->get_right());
		}
		else
			insert_data(to_add, root->get_right());
	}
	else if(to_add < root->get_data()){
		if(root->get_left() == 0){
			root->get_left() = new rb_node<T>(to_add, 1);
			root->get_left()->get_parent() = root; 
			insert_case1(root->get_left());
		}
		else
			insert_data(to_add, root->get_left());
	}
}

template <class T>
void rb_tree<T>::insert_case1(rb_node<T> *& N){
	if(N->get_parent() == 0)
		N->get_flag() = 0;
	else
		insert_case2(N);
}

template <class T>
void rb_tree<T>::insert_case2(rb_node<T> *& N){
	if(N->get_parent()->get_flag() == 0)
		return;
	insert_case3(N);
}


template <class T>
void rb_tree<T>::insert_case3(rb_node<T> *& N){
	rb_node<T> * U = get_uncle(N);

	if(U != 0 && U->get_flag() == 1){
		N->get_parent()->get_flag() = 0;
		U->get_flag() = 0;
		rb_node<T> * G = get_grandparent(N);
		G->get_flag() = 1;
		insert_case1(G);
	}
	else
		insert_case4(N);
}


template <class T>
void rb_tree<T>::insert_case4(rb_node<T> *& N){
	rb_node<T> * G = get_grandparent(N);
	if(N == N->get_parent()->get_right() && N->get_parent() == G->get_left()){
		rotate_left(N->get_parent());
		N = N->get_left();
	}
	else if(N == N->get_parent()->get_left() && N->get_parent() == G->get_right()){
		rotate_right(N->get_parent());
		N = N->get_right();
	}
	insert_case5(N);
}


template <class T>
void rb_tree<T>::insert_case5(rb_node<T> *& N){
	rb_node<T> * G = get_grandparent(N);
	N->get_parent()->get_flag() = 0;
	G->get_flag() = 1;
	if(N == N->get_parent()->get_left())
		rotate_right(G);
	else
		rotate_left(G);
}


template <class T>
rb_tree<T>::~rb_tree(){
	//TODO
}


template <class T>
rb_tree<T>::rb_tree(const rb_tree<T> &to_copy){
	//TODO
}


template <class T>
void rb_tree<T>::display_data(){
	display_data(root);
}


template <class T>
void rb_tree<T>::display_data(rb_node<T> * root){
	using namespace std;
	if(!root) return;
	display_data(root->get_left());
	cout << root->get_data() << " " << root->get_flag() 
			  << " Children: ";
	if(root->get_left())
		cout << root->get_left()->get_data() << " ";
	if(root->get_right())
		cout << root->get_right()->get_data() << endl << endl;
			  
	display_data(root->get_right());
}
