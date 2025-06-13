#pragma once

class Customer
{
private:
    int customer_image[4];  //‹q‚Ì‰æ‘œ
    int hukidasi_image;  //‚«o‚µ‚Ì‰æ‘œ

private:
    int r_customer;  //ƒ‰ƒ“ƒ_ƒ€‚É‹q‚Ì‰æ‘œ•`‰æ

public:
    Customer();
    void Initialize();
    void Draw() const;
    void Finalize();

    int RandomCustomer();
};

