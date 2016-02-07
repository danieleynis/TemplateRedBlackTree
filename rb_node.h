#include <iostream>

template <class T>
class rb_node{
	public:
		rb_node();
		rb_node(const rb_node<T> &to_copy);
		rb_node(const T &data, const int flag);
		rb_node<T>*& get_right();
		rb_node<T>*& get_left();
		rb_node<T>*& get_parent();
		int& get_flag();
		T& get_data();
	private:
		rb_node<T> * right;
		rb_node<T> * left;
		rb_node<T> * parent;
		int flag;
		T data;
};


template <class T>
rb_node<T>::rb_node(){
	right = left = parent = 0;
	flag = '\0';
}


template <class T>
rb_node<T>::rb_node(const rb_node<T> &to_copy){
	flag = to_copy.flag;
	data = to_copy.data;
}


template <class T>
rb_node<T>::rb_node(const T& data, const int flag){
	this->data = data;
	this->flag = flag;
}


template <class T>
rb_node<T>*& rb_node<T>::get_right(){
	return right;
}


template <class T>
rb_node<T>*& rb_node<T>::get_left(){
	return left;
}


template <class T>
rb_node<T>*& rb_node<T>::get_parent(){
	return parent;
}


template <class T>
int& rb_node<T>::get_flag(){
	return flag;
}


template <class T>
T& rb_node<T>::get_data(){
	return data;
}
