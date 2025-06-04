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
    int customer_image[4];  //‹q‚Ì‰æ‘œ
    int hukidasi_image;  //‚«o‚µ‚Ì‰æ‘œ

private:
    int r_customer;  //ƒ‰ƒ“ƒ_ƒ€‚É‹q‚Ì‰æ‘œ•`‰æ

public:
    CustomerState customer_state;

public:
    Customer();
    void Initialize();
    void Draw() const;
    void Finalize();

    int RandomCustomer();
};

