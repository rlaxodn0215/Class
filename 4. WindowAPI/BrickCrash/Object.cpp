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
	if (isAble==TRUE)
	{
		int x1 = position.x - radius;
		int y1 = position.y - radius;
		int x2 = position.x + radius;
		int y2 = position.y + radius;

		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, x1, y1, x2, y2);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
	}

}

void Ball::BallActive(const vector<Object*>& blocks,const Vector & vel)
{
	vector<Block*> block;

	for (int i = 0; i < blocks.size(); i++)
	{
		block.push_back((Block*)blocks[i]);
	}

	if (block[this->hideBlockNum]->BlockDead() == TRUE && isAble ==FALSE)
	{
		this->velocity = vel;
		this->isAble = TRUE;
	}
	
	for (int i = 0; i < blocks.size(); i++)
	{
		block.pop_back();
	}

}


BOOL Ball::Collison(const RECT& recView, Object* player, const vector<Object*>& blocks)
{
	Player* play = (Player*)player;

	int velSize = velocity.x * velocity.x + velocity.y * velocity.y;

	//플레이어와 충돌 했을 떄
	if (this->velocity.y > 0) //아래 방향으로 이동
	{
		double xMin = player->GetPos().x - play->GetWidth() / 2;
		double xMax= player->GetPos().x + play->GetWidth() / 2;
		double y= player->GetPos().y - play->GetHeight() / 2;


		if ((position.x>xMin && position.x<xMax) && y-position.y<=radius)
		{

			double OverlapDistance = radius -(y - position.y);
			//position.y -= OverlapDistance;
			double normalY = -1;
			//position.y += OverlapDistance * normalY;
			velocity.y *= -1;

			if (player->GetVel().x)
			{
				velocity.x -= (player->GetVel().x) * 0.3;
			}

			else
			{
				velocity.x += (player->GetVel().x) * 0.2;
			}

			velocity.y = -sqrt(velSize - velocity.x * velocity.x);
		}
	}

	//블록과 충돌 했을때
	for (int i = 0; i < blocks.size(); i++)
	{
		Block* block = (Block*)blocks[i];

		if (block->GetDead() == FALSE && isAble==TRUE)
		{
			double nearX = max(blocks[i]->GetPos().x - block->GetWidth() / 2,
				min(position.x, blocks[i]->GetPos().x + block->GetWidth() / 2));

			double nearY = max(blocks[i]->GetPos().y - block->GetHeight() / 2,
				min(position.y, blocks[i]->GetPos().y + block->GetHeight() / 2));

			Vector nearXY = { nearX,nearY };
			double difference = Length(nearXY, position);

			if (difference <= radius)
			{
				if (difference <= 0.0001)
				{

				}


				Vector normal = { (position.x - nearX) / difference, (position.y - nearY) / difference };

				velocity.x += -2 * velocity.x * normal.x;
				velocity.y += -2 * velocity.y * normal.y;

				/*if (velSize < velocity.x * velocity.x + velocity.y * velocity.y)
				{
					velocity.x *= velSize / (velocity.x * velocity.x + velocity.y * velocity.y);
					velocity.y *= velSize / (velocity.x * velocity.x + velocity.y * velocity.y);
				}*/

				block->SetHp(block->GetHp() - 1);
				play->SetPoint(play->GetPoint() + 100);
				return TRUE;
			}
		}
	}

	//if ((position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius &&
//	position.x >= blocks[i]->GetPos().x - block->GetWidth() - radius / 2) ||
//	(position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius &&
//		position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius))
//{

//	if ((position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius &&
//		position.x >= blocks[i]->GetPos().x + block->GetWidth() / 2) ||
//		(position.x <= blocks[i]->GetPos().x - block->GetWidth() / 2 &&
//			position.x >= blocks[i]->GetPos().x - block->GetWidth() / 2 - radius))
//	{
//		if (position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius &&
//			position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius)
//		{
//			block->SetHp(block->GetHp() - 1);
//			play->SetPoint(play->GetPoint() + 100);
//			velocity.x *= -1;
//			return TRUE;
//		}
//	}

//	if ((position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius &&
//		position.y >= blocks[i]->GetPos().y + block->GetHeight() / 2) ||
//		(position.y <= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius &&
//			position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2))
//	{
//		if (position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius &&
//			position.x >= blocks[i]->GetPos().x - block->GetWidth() / 2 - radius)
//		{
//			block->SetHp(block->GetHp() - 1);
//			play->SetPoint(play->GetPoint() + 100);
//			velocity.y *= -1;
//			return TRUE;
//		}
//	}

//}




//if ((position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius && velocity.y < 0) || 
   //	(position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius && velocity.y > 0))
   //{
   //	if (position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius &&
   //		position.x >= blocks[i]->GetPos().x - block->GetWidth() / 2 - radius)
   //	{
   //		velocity.y *= -1;
   //		return TRUE;
   //	}
   //}

// if ((position.x <= blocks[i]->GetPos().x + block->GetWidth() / 2 + radius && velocity.x < 0) ||
   // (position.x >= blocks[i]->GetPos().x - block->GetWidth() / 2 - radius && velocity.x > 0))
//{
   // if (position.y <= blocks[i]->GetPos().y + block->GetHeight() / 2 + radius &&
   //	 position.y >= blocks[i]->GetPos().y - block->GetHeight() / 2 - radius)
   // {
   //	 velocity.x *= -1;
   //	 return TRUE;
   // }
//}

	//if (difference <= radius)
//{ 
//	if (difference < 0.00001) //공이 블록 안으로 들어왔다.
//	{
//		double minLength = position.x - (blocks[i]->GetPos().x - block->GetWidth() / 2); //왼쪽 
//		int way = 9;


//		if (minLength < (blocks[i]->GetPos().x + block->GetWidth() / 2) - position.x) //오른쪽
//		{
//			minLength = (blocks[i]->GetPos().x + block->GetWidth() / 2) - position.x;
//			way = 3;
//		}

//		if (minLength < (blocks[i]->GetPos().y + block->GetHeight() / 2) - position.y) //아래쪽
//		{
//			minLength = (blocks[i]->GetPos().y + block->GetHeight() / 2) - position.y;
//			way = 6;
//		}

//		if (minLength < (blocks[i]->GetPos().y + block->GetHeight() / 2) - position.y) //위쪽
//		{
//			 minLength = (blocks[i]->GetPos().y + block->GetHeight() / 2) - position.y;
//			 way = 12;
//		}

//		difference= minLength + radius;
//		
//		switch (way)
//		{
//		case 3:
//		{
//			position.x += difference;
//		}
//			break;
//		case 6:
//		{
//			position.y+= difference;
//		}
//			break;
//		case 9:
//		{
//			position.x -= difference;
//		}
//			break;
//		case 12:
//		{
//			position.y -= difference;
//		}
//			break;
//		}

//	}

//	if (position.y >= blocks[i]->GetPos().y + block->GetHeight() / 2 - radius ||
//		position.y <= blocks[i]->GetPos().y - block->GetHeight() / 2 + radius)//위아래에서 충돌
//	{
//		velocity.y *= -1;
//		return TRUE;
//	}

//	else if (position.x <= blocks[i]->GetPos().x - block->GetWidth() / 2 + radius ||
//		position.x >= blocks[i]->GetPos().x + block->GetWidth() / 2 - radius) //좌우에서 충돌
//	{
//		velocity.x *= -1;
//		return TRUE;
//	}

	//Vector normal = { (position.x - nearX) / difference, (position.y - nearY) / difference };
	//velocity.x = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.x;
	//velocity.y = sqrt(velocity.x * velocity.x + velocity.y * velocity.y) * normal.y;



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

	// 플레이어 사망
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

	if (Hp == 1)
	{
		col = RED;
	}

	else if(Hp==2)
	{
		col = ORANGE;
	}

	else if (Hp == 3)
	{
		col = YELLOW;
	}

	else if (Hp == 4)
	{
		col = GREEN;
	}

	else if (Hp == 5)
	{
		col = BLUE;
	}
	else
	{
		dead = TRUE;
	}
}

void Block::Draw(HDC hdc)
{
	if (dead == FALSE)
	{
		int x1 = position.x - width / 2;
		int y1 = position.y - height / 2;
		int x2 = position.x + width / 2;
		int y2 = position.y + height / 2;

		HBRUSH hBrush, oldBrush;
		
		hBrush = NULL;

		if (col == RED)
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
		else if (col == ORANGE)
			hBrush = CreateSolidBrush(RGB(255, 153, 0));
		else if (col == YELLOW)
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
		else if (col == GREEN)
			hBrush = CreateSolidBrush(RGB(0, 255, 153));
		else if (col == BLUE)
			hBrush = CreateSolidBrush(RGB(0, 0, 255));

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, x1, y1, x2, y2);

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
	}
}

BOOL Block::BlockDead()
{
	if (Hp <= 0)
	{
		dead = TRUE;
		return TRUE;
	}

	return FALSE;
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
