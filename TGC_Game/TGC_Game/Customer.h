#pragma once
enum CustomerState
{
    Entering,  //���X
    Ordering,  //����
    Waiting,   //�ҋ@
    Leaving    //�ޓX
};

class Customer
{
private:
    int customer_image;  //�q�̉摜
    int hukidasi_image;  //�����o���̉摜

public:
    CustomerState customer_state;

public:
    Customer();
    void Initialize();
    void Draw();
    void Finalize();
};

