#pragma once

class Customer
{
private:
    int customer_image[4];  //�q�̉摜
    int hukidasi_image;  //�����o���̉摜

private:
    int r_customer;  //�����_���ɋq�̉摜�`��

public:
    Customer();
    void Initialize();
    void Draw() const;
    void Finalize();

    int RandomCustomer();
};

