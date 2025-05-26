#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image()

{

}

void Customer::Initialize()
{
	customer_image = LoadGraph("Resource/image/student_male01.png");  //‹q‚Ì‰æ‘œ
	hukidasi_image = LoadGraph("Resource/image/hukidasi.png");  //‚«o‚µ‚Ì‰æ‘œ
}

void Customer::Draw()
{
	DrawRotaGraph(600, 280, 1.3, 0, customer_image, true);  //‹q‚Ì‰æ‘œ
	DrawRotaGraph(900, 200, 0.6, 0, hukidasi_image, true);  //‚«o‚µ‚Ì‰æ‘œ
}

void Customer::Finalize()
{
	DeleteGraph(customer_image);
}
