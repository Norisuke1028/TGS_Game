#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image(),hukidasi_image()

{

}

void Customer::Initialize()
{
	customer_image = LoadGraph("Resource/image/student_male01.png");  //�q�̉摜
	hukidasi_image = LoadGraph("Resource/image/hukidasi.png");  //�����o���̉摜
}

void Customer::Draw() const
{
	DrawRotaGraph(550, 330, 1.3, 0, customer_image, TRUE);  //�q�̉摜
	DrawRotaGraph(850, 250, 0.6, 0, hukidasi_image, TRUE);  //�����o���̉摜
}

void Customer::Finalize()
{
	DeleteGraph(customer_image);
}
