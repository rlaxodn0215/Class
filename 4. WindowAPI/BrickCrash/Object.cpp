#include "Object.h"

Object::Object()
{
	position = { 0,0 };
	velocity = { 0,0 };
}

Object::Object(Vector & p, Vector & v)
{
	position = p;
	velocity = v;
}

void Object::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
}


Ball::Ball():Object()
{
	isAble = FALSE;
	radius = 0;
	tag = (TAG)BALL;
}

Ball::Ball(Vector & p, Vector & v, int r,int hideBNum):Object(p,v)
{
	if(hideBNum==-1)
		isAble = TRUE;
	else
		isAble = FALSE;

	hideBlockNum = hideBNum;
	radius = r;
	tag = (TAG)BALL;
}

void Ball::Update()
{
	Object::Update();
}

void Ball::Draw(HDC hdc)
{
	if (isAble == TRUE)
	{
		int x1 = position.x - radius;
		int y1 = position.y - radius;
		int x2 = position.x + radius;
		int y2 = position.y + radius;

		Ellipse(hdc, x1, y1, x2, y2);
	}
}


BOOL Ball::Collison(const RECT& recView, Object* player, const vector<Object*>& blocks)
{
	Player* play = (Player*)player;

	//플레이어와 충돌 했을 떄
	if (this->velocity.y > 0) //아래 방향으로 이동
	{
		double xMin = player->GetPos().x - play->GetWidth() / 2;
		double xMax= player->GetPos().x + play->GetWidth() / 2;
		double y= player->GetPos().y - play->GetHeight() / 2;

		if ((position.x>xMin && position.x<xMax) && y-position.y<=radius)
		{
			double OverlapDistance = radius -(y - position.y);
			double normalY = -1;
			position.y += OverlapDistance * normalY;
			velocity.y *= -1;

			velocity.x += (player->GetVel().x)*1;

		}
	}

	//블록과 충돌 했을때
	for (int i = 0; i < blocks.size(); i++)
	{
		Block* block = (Block*)blocks[i];

		if (block->GetDead() == FALSE && isAble==TRUE)
		{
			if (position.x >= blocks[i]->GetPos().x - block->GetWidth() / 2 - radius &&
				position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius)
			{

				if (position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius &&
					position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius)
				{
					Vector normal = { (position.x - nearX) / difference, (position.y - nearY) / difference };

					velocity.x = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.x;
					velocity.y = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.y;
				}

			}

			/*double nearX = max(blocks[i]->GetPos().x - block->GetWidth() / 2,
				min(position.x, blocks[i]->GetPos().x + block->GetWidth() / 2));

			double nearY = max(blocks[i]->GetPos().y - block->GetHeight() / 2,
				min(position.y, blocks[i]->GetPos().y + block->GetHeight() / 2));

			Vector nearXY = { nearX,nearY };
			double difference = Length(nearXY, position);

			if (difference <= radius)
			{ 
				Vector normal = { (position.x - nearX) / difference, (position.y - nearY) / difference };

				velocity.x = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.x;
				velocity.y = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.y;
			}*/
		}
	}

	//윈도우 벽과 충돌했을 때
	if (position.x + radius >= recView.right)
	{
		position.x = recView.right - radius;
		velocity.x *= -1;
		return TRUE;
	}

	else if (position.x - radius <= recView.left)
	{
		position.x = recView.left + radius;
		velocity.x *= -1;
		return TRUE;
	}

	//라이프 차감
	else if (position.y + radius >= recView.bottom)
	{
		position.y = recView.bottom - radius;
		velocity.y *= -1;
		return TRUE;
	}

	else if (position.y - radius <= recView.top)
	{
		position.y = recView.top + radius;
		velocity.y *= -1;
		return TRUE;
	}

	return FALSE;
}

Block::Block():Object()
{
	
	width = height = Hp=0;
	tag = (TAG)BLOCK;
}

Block::Block(Vector & p, Vector & v, int w, int h, int hp):Object(p,v)
{
	width = w;
	height = h;
	Hp = hp;
	col = (COLOR)Hp;
	tag = (TAG)BLOCK;
	dead = FALSE;
}

void Block::Update()
{
	Object::Update();
}

void Block::Draw(HDC hdc)
{
	if (dead == FALSE)
	{
		int x1 = position.x - width / 2;
		int y1 = position.y - height / 2;
		int x2 = position.x + width / 2;
		int y2 = position.y + height / 2;

		Rectangle(hdc, x1, y1, x2, y2);
	}
}

BOOL Block::BlockDead()
{
	if (Hp <= 0)
	{
		dead = TRUE;
	}

	return 0;
}

BOOL Block::Collison(const vector<Object*>& balls)
{
	return 0;
}

Player::Player():Object()
{
	width = height = 0;
	playerName = "no name";
	points = 0;
	tag = (TAG)PLAYER;
}

Player::Player(Vector & p, Vector & v, int w, int h, string name, int point):Object(p,v)
{
	width = w;
	height = h;
	playerName = name;
	points = point;
	tag = (TAG)PLAYER;
}

void Player::Update()
{
	
}

void Player::Draw(HDC hdc)
{
	int x1 = position.x - width / 2;
	int y1 = position.y - height / 2;
	int x2 = position.x + width / 2;
	int y2 = position.y + height / 2;

	Rectangle(hdc, x1, y1, x2, y2);
}

BOOL Player::Collison(const RECT& recView, const vector<Object*>& balls)
{
	//윈도우 벽과 충돌했을 때
	if (position.x + width/2 >= recView.right)
	{
		position.x = recView.right - width / 2;
		return TRUE;
	}

	else if (position.x - width / 2 <= recView.left)
	{
		position.x = recView.left + width / 2;
		return TRUE;
	}
	return FALSE;
}

//Item::Item():Object()
//{
//	IT = (ITEM_TYPE)0;
//	tag = (TAG)ITEM;
//}
//
//Item::Item(Vector & p, Vector & v, ITEM_TYPE it):Object(p,v)
//{
//	IT = it;
//	tag = (TAG)ITEM;
//}
//
//void Item::Update()
//{
//	Object::Update();
//}
//
//void Item::Draw(HDC hdc)
//{
//}
//
//BOOL Item::Collison(const RECT& recView, const Object * player)
//{
//	return 0;
//}
