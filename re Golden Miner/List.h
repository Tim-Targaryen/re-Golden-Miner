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
		node<T>* at(int n) {
			node<T>* temp = header;
			while (temp->rank != n and temp->succ != NULL) temp = temp->succ;
			return temp;
		}//��λ
		T& operator [](int n) { return at(n)->data; }//��������
		bool insert_pred(int n, T& e) {
			if (n >= size) return false;//�Ƿ�����
			node<T>* temp = at(n);
			node<T>* cntr = new node<T>;
			cntr->data = e; cntr->rank = n;
			cntr->succ = temp; cntr->pred = temp->pred;
			temp->pred->succ = cntr; temp->pred = cntr;
			while (cntr->succ != NULL) {
				cntr->rank += 1; cntr = cntr->succ;
			}
			trailer->rank = -2; size++;//����
			return true;
		}//ǰ������
		bool insert_succ(int n, T& e) {
			if (n >= size) return false;//�Ƿ�����
			node<T>* temp = at(n);
			node<T>* cntr = new node<T>;
			cntr->data = e; cntr->rank = n;
			cntr->pred = temp; cntr->succ = temp->succ;
			temp->succ->pred = cntr; temp->succ = cntr;
			while (cntr->succ != NULL) {
				cntr->rank += 1; cntr = cntr->succ;
			}
			trailer->rank = -2; size++;//����
			return true;
		}//��������
		bool insert_front(T& e) { return insert_succ(-1, e); }
		bool insert_behind(T& e) { return insert_pred(-2, e); }
		bool remove(int n) {
			if (n >= size) return false;//�Ƿ�ɾ��
			node<T>* temp = at(n);
			node<T>* move = temp;
			temp->pred->succ = temp->succ;
			temp->succ->pred = temp->pred;
			while (move->succ != NULL) {
				move->rank -= 1; move = move->succ;
			}
			trailer->rank = -2; delete temp; 
			size--;//����
			return true;
		};
		~List() {
			for (int i = 0; i < size; i++) remove(i);
			delete header; delete trailer;
		};//����	
};//������