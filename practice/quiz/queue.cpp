#define SIZE 5

#include <iostream>


using namespace std;

struct Queue{
    int items[SIZE],front,rear;
};
using queue = Queue*;

queue newQueue(){
        queue q = new Queue;
        q->front = -1;
        q->rear = -1;
        return q;
}

bool full(queue q){
    if(q->front == 0 && q->rear == SIZE -1)
        return true;
    if(q->front == q->rear+1)
    return true;

    return false;
}

bool empty(queue q){
    if(q->front == -1)
        return true;

    return false;
}

void enqueue(queue q, int element){
    if(full(q)){//full함수에 대해 공부하기.아마 stl에 다 저장되어있는 함수들인 것 같음.-->nob!여기서 구현.
        cout << endl << "Queue is full" << endl;
        }
    else{
        if(q->front == -1) q->front = 0;
        q->rear = (q->rear+1)%SIZE;
        q->items[q->rear] = element;
        cout << "enqueued: " << element << endl;
    }
}

int dequeue(queue q){
    int element;
    if(empty(q)){//empty함수에 대해서 공부하기.
        cout << "Queue is empty" << endl;
        return(-1);
    }
    else{
        element = q->items[q->front];//element에는 실제 값에 접근을 하여 지금 의 front에 저장되어있는 값을 넣어준뒤.
        if(q->front == q->rear){
            q->front = -1;
            q->rear = -1;
        }//q has only one element;
        else{
            q->front = (q->front +1) % SIZE;//여기서 front값을 앞으로 한칸 땡겨주면된다.
        }
    return element;
    }
}

void display(queue q){
    int i;
    if(empty(q))
        cout << endl << "Empty Queue" << endl;
    else{
        cout << "Front[" << q->front << "]\n";
        cout << "Items: ";
        for(i = q->front; i!=q->rear; i=(i+1)%SIZE)
            cout << q->items[i] << ' ';
        cout << q->items[i];
        cout << endl << "Rear["<< q->rear << "]\n";
    }
}

int main(){
    queue q = newQueue();
    dequeue(q);
    enqueue(q,1);
    enqueue(q,2);
    enqueue(q,3);
    enqueue(q,4);
    enqueue(q,5);
    enqueue(q,6);
    display(q);
    int elem = dequeue(q);
    if(elem != -1)
        cout << "dequeued: " << elem << endl;
    display(q);
    enqueue(q,7);
    display(q);
    enqueue(q,8);
    dequeue(q);
    dequeue(q);
    display(q);
    return 0;
}