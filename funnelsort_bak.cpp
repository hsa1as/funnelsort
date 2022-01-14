#include<bits/stdc++.h>
#include<vector>
#define INF 100000007 
#define ll long long
typedef long long T;
using namespace std;
class circ_buffer{
	T *data;
	ll start;
	ll end;
	ll cur_elems;
	ll num_elems;
public:
	circ_buffer(ll _num_elems){
		num_elems = _num_elems;
		data = (T *)malloc(sizeof(T)*num_elems);
		start = 0;
		end = 0;
	}
	void reset(circ_buffer * _buf){
		_buf->start=0;
		_buf->end=0;
		_buf->cur_elems=0;
	}
	int is_full(circ_buffer * _buf){
		if(_buf->cur_elems == _buf->num_elems){
			return 1;
		}
		return 0;
	}
	int is_empty(circ_buffer *_buf){
		return cur_elems==0;
	}
	void insert(circ_buffer *_buf, T elem){
		if(is_full(_buf)){
			start = (start+1)%num_elems;
			end = (end+1)%num_elems;
			*(_buf->data+sizeof(ll)*end)=elem;
			return;
		}
		end = (end+1)%num_elems;
		*(_buf->data+sizeof(ll)*end)=elem;
		cur_elems++;
	}
	T pop(circ_buffer *_buf){
		if(!is_empty(_buf)){
			T pop_el = *(_buf->data + sizeof(ll)*end);
			if(_buf->end==0) _buf->end = _buf->num_elems-1;
			else (_buf->end)--;
			return pop_el;
		}
		return -INF;
	}
	vector<T> to_vector(){
		vector<T> temp;
		ll it = start;
		while(it!=end){
			temp.push_back(*(data+sizeof(ll)*it));
			it++;
		}
		return temp;
	}
	ll ret_size(){
		return cur_elems;
	}
};



class funnel{
	ll k;
	vector<funnel *> left_funnels;
	vector<circ_buffer *> in_buffers;
	funnel * right_funnel;
	vector<circ_buffer *> circ_buffers;
	vector<circ_buffer *> out_buffer;
	void create_funnels(){
		ll no_fun = ceil(sqrt(k));
		ll rtk1 = floor(sqrt(k));
		ll rtk2 = k-rtk1 *(no_fun-1);
		ll i=0;
		for(; i<no_fun-1; i++){
			auto f = new funnel(rtk1);
			for(int j = i*rtk1; j<=(i+1)*rtk1; j++)f->in_buffers.push_back(circ_buffers[j]); 
			left_funnels.push_back(f);
		}
		auto f = new funnel(rtk2);
		for(int j = i*rtk1; j<=i*rtk1 + rtk2;j++)f->in_buffers.push_back(circ_buffers[j]);
		left_funnels.push_back(f);
		auto f2 = new funnel(no_fun);
		for(auto x : left_funnels) f2->in_buffers.push_back(x->out_buffer);
		return;
	}
	void create_buffers(){
		ll no_buf = ceil(sqrt(k));
		for(ll i =0; i<no_buf; i++){
			circ_buffers.push_back(new circ_buffer(ceil(2*sqrt(k)*sqrt(k)*sqrt(k))));
		}	
		return;
	}
public:
	funnel(ll _k){
		k=_k;
		create_funnels();
		create_buffers();
	}
	void sort(){
		if(k==2){
			while(!in_buffers[0]->is_empty() && !in_buffers[1]->is_empty()){
				ll x = in_buffers[0]->pop(), y = in_buffers[1]->pop();
				if(x>y) {
					out_buffer.push(x); out_buffer.push(y);
				}else{
					out_buffer.push(y); out_buffer.push(x);
				}
			}
			for(int i =0; i<2; i++){
				while(!in_buffers[i]->is_empty()){
					out_buffer.push(in_buffers[i]->pop())
				}
			}
		}
		else{
			bool c = true;
			while(c){
				for(auto x: in_buffers){
					if(!x->is_empty()){
						c=true; break;
					}else{c=false;}
				}
				for(ll i =0; i<ceil(sqrt(k)); i++){
					left_funnels[i]->sort();
				}
			}
		}
	}
	/*void init_in_buf(vector<vector<T>> &in_bufs){
		for(auto x : in_bufs) in_buffers.push_back(&x);
	}*/
	void init_in_buf(vector<circ_buffer> &in_bufs){
		for(auto x : in_bufs) in_buffers.push_back(&x);
	}
	
};


int main(){
	cout<<"NoErrors!\n";
}
