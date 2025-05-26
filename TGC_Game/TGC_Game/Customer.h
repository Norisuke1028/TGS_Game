#pragma once
enum CustomerState
{
    Entering,  //“ü“X
    Ordering,  //’•¶
    Waiting,   //‘Ò‹@
    Leaving    //‘Ş“X
};

class Customer
{
private:
    int customer_image;  //‹q‚Ì‰æ‘œ
    int hukidasi_image;  //‚«o‚µ‚Ì‰æ‘œ

public:
    CustomerState customer_state;

public:
    Customer();
    void Initialize();
    void Draw();
    void Finalize();
};

