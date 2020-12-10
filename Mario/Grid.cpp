#include "Grid.h"
#include "Mario.h"
#include "Camera.h"
#include "Items.h"

Grid* Grid::__instance = NULL;
Grid::Grid() 
{
	
}
Area Grid::FindCell(RECT e)
{
	return {
		int(max(0		, e.top / SizeCell)),
		int(max(0		, e.left / SizeCell)),
		int(min(cols - 1, int(e.right / SizeCell))),
		int(min(rows - 1, int(e.bottom / SizeCell)))
	};
}

void Grid::Init()
{
	
	
	Cells.clear();
	for (int y = 0; y < rows; ++y)
	{
		auto row = std::vector<Cell*>();
		for (int x = 0; x < cols; ++x)
		{
			row.push_back(new Cell(x, y));
		}
		Cells.push_back(row);
	}
	DebugOut(L"Cell %d %d\n", rows, cols);
}
void Grid::LoadObjects(LPGAMEOBJECT& obj, float x, float y)
{
	RECT e;
	e.top = y;
	e.left = x;
	e.right =x+ obj->GetRect().right;
	e.bottom = y+ obj->GetRect().bottom;
	auto area = FindCell(e);
	switch (obj->tag)
	{
	case GROUND:
	{
		
		for (int r = area.TopCell; r <= area.BottomCell; r++)
			for (int c = area.LeftCell; c <= area.RightCell; c++)
			{
				DebugOut(L"[INFO] object static TYPE: %d is add in Cell [%d] [%d]\n", obj->type,r,c);
				Cells[r][c]->staticObjects.insert(obj);
			}
		obj->SetPosition(x, y);
		break;
	}
	case ENEMY:
	{
		for (int r = area.TopCell; r <= area.BottomCell; r++)
			for (int c = area.LeftCell; c <= area.RightCell; c++)
			{
				DebugOut(L"[INFO] object moving TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
				Cells[r][c]->movingObjects.insert(obj);
			}
		obj->SetPosition(x, y);
		break;
	}
	case ITEM:
		for (int r = area.TopCell; r <= area.BottomCell; r++)
			for (int c = area.LeftCell; c <= area.RightCell; c++)
			{
				DebugOut(L"[INFO] object Hidden TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
				Cells[r][c]->staticObjects.insert(obj);
			}
		obj->SetPosition(x, y);
		break;
	default:
		DebugOut(L"[ERR] Invalid object TYPE: %d\n", obj->type);
		break;
	}
}


void Grid::RenderCell()
{
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);
	auto area = FindCell(camera->GetBound());
	
	RECT rect;

	for (int r = area.TopCell; r <= area.BottomCell; r++)
	{
		for (int c = area.LeftCell; c <= area.RightCell; c++)
		{
			LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
			string inforCell = "Static object" + to_string(Cells[r][c]->staticObjects.size()) + "\n";
			inforCell += "Moving object" + to_string(Cells[r][c]->movingObjects.size()) + "\n";
			inforCell += "Cell[ " + to_string(r) + "][" + to_string(c) + "]";
			
			SetRect(&rect, 
					Cells[r][c]->posX * SizeCell,
					Cells[r][c]->posY * SizeCell, 
					Cells[r][c]->posX * SizeCell + SizeCell, 
					Cells[r][c]->posY * SizeCell + SizeCell);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + SizeCell, rect.top+1, 255);
			Game::GetInstance()->Draw(rect.left, rect.top, bbox, rect.left, rect.top, rect.left + 1, rect.top + SizeCell, 255);
			
		}
	}
}

// test
bool Grid::IsOnCam(LPGAMEOBJECT obj)
{
	return (obj->x > camera->cam_x && obj->x < camera->cam_x + camera->GetWidth() && obj->y > camera->cam_y && obj->y < camera->cam_y + camera->GetHeight());
}
void Grid::CalcObjectInViewPort()
{
	auto area = FindCell(camera->GetBound());
	unordered_set<GameObject*> result;
	unordered_set<GameObject*> resultItem;
	for(int r = area.TopCell;r <= area.BottomCell;r++)
	{
		//DebugOut(L"[info] Cell row [%d]\n", r);
		for(int c = area.LeftCell; c <= area.RightCell;c++)
		{
			result.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
			result.insert(Cells[r][c]->movingObjects.begin(), Cells[r][c]->movingObjects.end());
			//DebugOut(L"[info] Object in Cell  [%d]: %d\n",c,Cells[r][c]->staticObjects.size());
			//DebugOut(L"[info] Cell column [%d]\n",c);
			resultItem.insert(Cells[r][c]->staticObjects.begin(), Cells[r][c]->staticObjects.end());
			
		}
	}
	ObjectHolder = { resultItem.begin(), resultItem.end() };
	CurObjectInViewPort = { result.begin(), result.end() };
	//DebugOut(L"[info] Cell left: [%d], top: [%d], right: [%d] bottom: [%d]\n", area.LeftCell, area.TopCell, area.RightCell, area.BottomCell);
	//DebugOut(L"[info] Object in viewport: %d\n", CurObjectInViewPort.size());
}

template<typename T, typename Pred>
void RemoveObjectIf(unordered_set<T>& container, Pred  del)
{
	for (auto it = container.begin(), end = container.end(); it != end; )
	{
		if (del(*it)) it = container.erase(it);
		else                       it++;
	}
}
void Grid::UpdateStaticObject()
{
	auto area = FindCell(camera->GetBound());
	
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		for (auto& obj : Cells[r][c]->staticObjects)
		{
			if (obj->isDead && obj->child != 0)
			{
				LPGAMEOBJECT item;
				item = Items::CreateItem(obj->child, obj->x, obj->y);
				item->SetPosition(obj->x, obj->y);
				switch (obj->child)
				{
				case LEAF:
					AddMovingObject(item);
					break;
				case RED_MUSHROOM:
					AddMovingObject(item);
					break;
				case GREEN_MUSHROOM:
					AddMovingObject(item);
					break;
				case COIN:
					AddMovingObject(item);
					break;
				default:
					break;
				}
			}
		}
	}

}
void Grid::UpdateCell()
{
	auto area = FindCell(camera->GetBound());
	unordered_set<LPGAMEOBJECT> shouldBeUpdatedObjects;
	bool isDeadObject = false;
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->movingObjects.size() == 0) continue;
		//DebugOut(L"Obj in cell [%d] %d\n", c, Cells[r][c]->movingObjects.size());
		RemoveObjectIf(Cells[r][c]->movingObjects, [&](auto& obj)
		{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->widthBBox;
				e.bottom = obj->y + obj->heightBBox;
				auto objArea = FindCell(e);
				if (obj->canDel) isDeadObject = true;
				if (objArea.TopCell != r || objArea.RightCell != c)
				{
					//DebugOut(L"obj in cell [%d]\n", c);
					shouldBeUpdatedObjects.emplace(obj);
					return true;
				}
				return false;
		});
	}
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		if (Cells[r][c]->staticObjects.size() == 0) continue;
		//DebugOut(L"Obj in cell [%d] %d\n", c, Cells[r][c]->movingObjects.size());
		RemoveObjectIf(Cells[r][c]->staticObjects, [&](auto& obj)
			{
				RECT e;
				e.left = obj->x;
				e.top = obj->y;
				e.right = obj->x + obj->widthBBox;
				e.bottom = obj->y + obj->heightBBox;
				auto objArea = FindCell(e);
				if (obj->canDel)
				{
					return true;
					isDeadObject = true;
				}
				return false;
			});
	}
	for (auto& obj : shouldBeUpdatedObjects)
	{
		RECT e;
		e.left = obj->x;
		e.top = obj->y;
		e.right = obj->x + obj->widthBBox;
		e.bottom = obj->y + obj->heightBBox;
		auto objArea = FindCell(e);
		LOOP(r, objArea.TopCell, objArea.BottomCell)
			LOOP(c, objArea.LeftCell, objArea.RightCell)
			{
				Cells[r][c]->movingObjects.emplace(obj);
				//DebugOut(L"obj move to %d   \n",c);
			}
	}
	if (isDeadObject) RemoveDeadObject();
	CalcObjectInViewPort();

}
void Grid::AddStaticObject(LPGAMEOBJECT obj, float x, float y)
{
	RECT e;
	e.top = y;
	e.left = x;
	e.right = x + obj->widthBBox;
	e.bottom = y + obj->heightBBox;
	auto area = FindCell(e);
	for (int r = area.TopCell; r <= area.BottomCell; r++)
		for (int c = area.LeftCell; c <= area.RightCell; c++)
		{
			//DebugOut(L"[INFO] object moving TYPE: %d is add in Cell [%d] [%d]\n", obj->type, r, c);
			Cells[r][c]->staticObjects.insert(obj);
		}
	obj->SetPosition(x, y);
}
void Grid::AddMovingObject(LPGAMEOBJECT obj)
{
	RECT e;
	e.left = obj->x;
	e.top = obj->y;
	e.right = obj->x + obj->widthBBox;
	e.bottom = obj->y + obj->heightBBox;
	auto area = FindCell(e);
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
			Cells[r][c]->movingObjects.insert(obj);

}

void Grid::RemoveDeadObject() 
{
	auto area = FindCell(camera->GetBound());
	LOOP(r, area.TopCell, area.BottomCell)
		LOOP(c, area.LeftCell, area.RightCell)
	{
		RemoveObjectIf(Cells[r][c]->movingObjects, [](auto obj) {return obj->canDel; });
	}
}

Grid* Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}