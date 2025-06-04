#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image(),hukidasi_image(),r_customer()

{

}

void Customer::Initialize()
{
	//customer_image = LoadGraph("Resource/image/student_male01.png");  //�q�̉摜
	LoadDivGraph("Resource/image/b_customer.png", 4, 4, 1, 250.5, 359, customer_image);  //�Q�[�����Ŏg�p����i���o�[�摜(��)
	hukidasi_image = LoadGraph("Resource/image/hukidasi.png");  //�����o���̉摜
}

void Customer::Draw() const
{
	DrawRotaGraph(520, 330, 1.0, 0, customer_image[r_customer], TRUE);  //�q�̉摜
	DrawRotaGraph(820, 250, 0.6, 0, hukidasi_image, TRUE);  //�����o���̉摜
}

void Customer::Finalize()
{
	DeleteGraph(customer_image[0]);
}

int Customer::RandomCustomer()
{
	r_customer = 0 + rand() % 4;
	return 0;
}