#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image(),hukidasi_image(),r_customer()

{

}

void Customer::Initialize()
{
	//customer_image = LoadGraph("Resource/image/student_male01.png");  //客の画像
	LoadDivGraph("Resource/image/b_customer.png", 4, 4, 1, 250.5, 359, customer_image);  //ゲーム内で使用するナンバー画像(赤)
	hukidasi_image = LoadGraph("Resource/image/hukidasi.png");  //吹き出しの画像
}

void Customer::Draw() const
{
	DrawRotaGraph(520, 330, 1.0, 0, customer_image[r_customer], TRUE);  //客の画像
	DrawRotaGraph(820, 250, 0.6, 0, hukidasi_image, TRUE);  //吹き出しの画像
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