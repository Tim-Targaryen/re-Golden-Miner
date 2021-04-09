template<typename T>
struct node {
	node* pred;//ǰ��
	T data;//������
	int rank;//��(��0��ʼ��
	node* succ;//���
	node() {
		T new_one;
		succ = NULL; pred = NULL;
		rank = 0; data = new_one;//�����ʼ��
	};
	~node() {};
};//�ڵ�
template<typename T>
class List
{
private:
	node<T>* header;//ͷ�ڱ�
	node<T>* trailer;//β�ڱ�
public:
	int size;//��С
	List(int n = 0) {
		size = n;
		header = new node<T>; trailer = new node<T>;
		header->succ = trailer; trailer->pred = header;
		header->rank = -1; trailer->rank = -2;//����
		node<T>* temp = NULL;
		node<T>* cntr = header;
		for (int i = 0; i < n; i++) {
			temp = new node<T>;
			temp->rank = i;
			cntr->succ = temp;
			temp->pred = cntr;
			cntr = temp;
		}
		cntr->succ = trailer;
		trailer->pred = cntr;
	}
	void insert_as_front(T& e) {
		node<T>* cntr = new node<T>;
		cntr->data = e; cntr->rank = 0;
		cntr->pred = header; cntr->succ = header->succ;
		header->succ->pred = cntr; header->succ = cntr;
		node<T>* temp = cntr;
		for (int i = 0; cntr->succ!=NULL ; cntr=cntr->succ) cntr->rank = i;
		trailer->rank = -2;
		size++;
	}
	node<T>* at(int n) {
		node<T>* temp = header;
		while (temp->rank != n) temp = temp->succ;
		return temp;
	}//��λ
	T& operator [](int n) {
		return at(n)->data;
	}//��������
	bool insert_pred(int n, T& e) {
		if (n >= size) return false;//�Ƿ�����
		node<T>* temp = at(n);
		node<T>* cntr = new node<T>;
		cntr->data = e; cntr->rank = n;
		cntr->pred = temp->pred; temp->pred->succ = cntr;
		cntr->succ = temp; temp->pred = cntr;
		while (temp->succ != NULL) {
			temp->rank += 1; temp = temp->succ;
		}
		trailer->rank = -2;
		size++;//����
		return true;
	}//ǰ������
	bool insert_succ(int n, T& e) {
		if (n >= size) return false;//�Ƿ�����
		node<T>* temp = at(n);
		node<T>* cntr = new node<T>;
		cntr->data = e; cntr->rank = n;
		cntr->pred = temp->pred; temp->pred->succ = cntr;
		cntr->succ = temp; temp->pred = cntr;
		while (temp->succ != NULL) {
			temp->rank += 1; temp = temp->succ;
		}
		trailer->rank = -2;
		size++;//����
		return true;
	}//��������
	bool remove(int n) {
		if (n >= size) return false;//�Ƿ�ɾ��
		node<T>* temp = at(n);
		node<T>* move = temp;
		temp->pred->succ = temp->succ;
		temp->succ->pred = temp->pred;
		while (move->succ != NULL) {
			move->rank -= 1; move = move->succ;
		}
		trailer->rank = -2;
		delete temp;
		size--;//����
		return true;
	};
	~List() {
		for (int i = 0; i < size; i++) remove(i);
		delete header;
		delete trailer;
	};//����
	template<typename VST>
	void traverse(VST&) {
		for (int i = 0; i < size; i++) VST(at(i)->data);
	};//����������һ�ֺ�������
};//������