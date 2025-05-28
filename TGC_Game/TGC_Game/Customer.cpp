#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image(),hukidasi_image()

{

}

void Customer::Initialize()
{
	customer_image = LoadGraph("Resource/image/student_male01.png");  //‹q‚Ì‰æ‘œ
	hukidasi_image = LoadGraph("Resource/image/hukidasi.png");  //‚«o‚µ‚Ì‰æ‘œ
}

void Customer::Draw() const
{
	DrawRotaGraph(550, 330, 1.3, 0, customer_image, TRUE);  //‹q‚Ì‰æ‘œ
	DrawRotaGraph(850, 250, 0.6, 0, hukidasi_image, TRUE);  //‚«o‚µ‚Ì‰æ‘œ
}

void Customer::Finalize()
{
	DeleteGraph(customer_image);
}
