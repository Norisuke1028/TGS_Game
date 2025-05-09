#include "Customer.h"
#include "DxLib.h"

Customer::Customer() :
	customer_image()

{

}

void Customer::Initialize()
{
	customer_image = LoadGraph("Resource/image/student_male01.png");  //‹q‚Ì‰æ‘œ
}

void Customer::Draw()
{
	DrawRotaGraph(600, 280, 1.3, 0, customer_image, true);  //‹q‚Ì‰æ‘œ
}

void Customer::Finalize()
{
	DeleteGraph(customer_image);
}
